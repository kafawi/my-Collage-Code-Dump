<?php require_once 'dbconn.php'; ?>
<?php require_once 'helper.php'; ?>
<?php require_once '../phpseclib/Crypt/RSA.php';?>
<?php
    require_once __DIR__ . '/../phpseclib/Math/BigInteger.php';
    require_once __DIR__ . '/../vendor/autoload.php';

    if(chkLogin()){
    } else {
        header("Location: ../index.php");
    }
    $email = "Error";
    $gitlabtoken = "T9vR1dDi9MbXdPs8uoHk";
?>
<?php

    if(isset($_POST['createProject'])){
//        print_r($_POST);

        $email = getSessionMail();
        $projectName = filter_var($_POST['projectName'], FILTER_SANITIZE_STRING);
        $publicKey = filter_var($_POST['publicKey'], FILTER_SANITIZE_STRING);

        //Auth User
        $client = \Gitlab\Client::create('https://gitlab.informatik.haw-hamburg.de')
                    ->authenticate($gitlabtoken, \Gitlab\Client::AUTH_URL_TOKEN)
        ;

        //Preconfigure Options

        $projectHash= substr(md5(openssl_random_pseudo_bytes(20)),-8);


        $CDRname = "CDR " . $projectName ." ". $projectHash;
        $CACname = "CAC " . $projectName ." ". $projectHash;

        $CDRdesc = 'CIES CDR for ' . $email;
        $CACdesc = 'CIES CAC for ' . $email;

        //Create Projects
        $cdrproject = new \Gitlab\Model\Project;
        //$cacproject = new \Gitlab\Model\Project;
        $cac_stable_fork_url = "https://gitlab.informatik.haw-hamburg.de/api/v4/projects/1588/fork";
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $cac_stable_fork_url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_POST, true);
        curl_setopt($ch, CURLOPT_POSTFIELDS,"");
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('PRIVATE-TOKEN: ' . $gitlabtoken));

        $server_output = curl_exec($ch);
        $httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
        curl_close($ch);

        if ($httpcode == 201) {
            $resultArray = json_decode($server_output, true);
            $cacprojectid = $resultArray["id"];
            $cacproject = \Gitlab\Model\Project::fromArray($client, $resultArray);
        } else if ($httpcode == 409) {
            throw new Exception('Projekt Erstellung fehlgeschlagen. HTTP Code: ' . $httpcode . "\n"
            . "Ein vorhandes Projekt blockt die Erstellung eines weiteren Forks der Projektstandardeinstellungen\n"
            . "Kontaktieren Sie einen Systemadmin.");
        }
        else {
            throw new Exception('Projekt Erstellung fehlgeschlagen. HTTP Code: ' . $httpcode);
        }
        /*$cacproject = \Gitlab\Model\Project::create($client, $CACname, array(
          'description' => $CACdesc,
          'issues_enabled' => false
        ));*/

        $cacproject->update(array(
        'name' => $CACname,
        'description' => $CACdesc,
        'issues_enabled' => false
        ));

        $cdrproject = \Gitlab\Model\Project::create($client, $CDRname, array(
          'description' => $CDRdesc,
          'issues_enabled' => false
        ));

        //Fork from TCAC
        //No Forks currently possible due to Auth Issues
        //$cacproject->forkFrom(1545);

        //Create SSH Keys
        $rsa = new Crypt_RSA();
        $rsa->setPublicKeyFormat(CRYPT_RSA_PUBLIC_FORMAT_OPENSSH);
        extract($rsa->createKey());
        $cdrprojectpublickey = $publickey;
        $cdrprojectprivatekey = $privatekey;

        $rsa = new Crypt_RSA();
        $rsa->setPublicKeyFormat(CRYPT_RSA_PUBLIC_FORMAT_OPENSSH);
        extract($rsa->createKey());
        $cacprojectpublickey = $publickey;
        $cacprojectprivatekey = $privatekey;

        $rsa = new Crypt_RSA();
        $rsa->setPublicKeyFormat(CRYPT_RSA_PUBLIC_FORMAT_OPENSSH);
        extract($rsa->createKey());
        $clonecdrpublickey = $publickey;
        $clonecdrprivatekey = $privatekey;

        $rsa = new Crypt_RSA();
        $rsa->setPublicKeyFormat(CRYPT_RSA_PUBLIC_FORMAT_OPENSSH);
        extract($rsa->createKey());
        $updatecacpublickey = $publickey;
        $updatecacprivatekey = $privatekey;

        //Add Public Key to Deploy Keys of the CDR so the user can access it with the private key
        $cdrproject->addDeployKey('Usergate', $cdrprojectpublickey, true);

        //Add the Public Key to Deploy Keys of the CAC so the CDR can push through a webhook
        $cacproject->addDeployKey('CDR Push Gate', $cacprojectpublickey, true);

        //Add Public Key to Deploy Keys of the CDR so the CAC can clone the CDR into his Pipeline
        $cdrproject->addDeployKey('Clone CDR Gate'), $clonecdrpublickey, false);

        //Add Public Key to Deploy Keys of the CAC so the cies main can update its pipeline yaml ...
        $cacproject->addDeployKey('Update CAC Gate'), $updatecacpublickey, true);

        //Get ID of projects
        $pager = new \Gitlab\ResultPager($client);
        $projectiddump = $pager->fetch($client->api('projects'),'all',[['owned' => boolval(0), 'order_by' => 'created_at']]);
        $cdrprojectid = $projectiddump[1]["id"];
        $cacprojectid = $projectiddump[0]["id"];

        //Look for Project SSH Link
        $cdrprojectlink = $projectiddump[1]["ssh_url_to_repo"];
        $cacprojectlink = $projectiddump[0]["ssh_url_to_repo"];

        //Add Variables to CAC
        $srcdir = "src/"
        $client->api('projects')->addVariable($cacprojectid, "USER_MAIL", $email);
        $client->api('projects')->addVariable($cacprojectid, "CDR_NAME", $projectName);
        $client->api('projects')->addVariable($cacprojectid, "CDR_ID", $cdrprojectid);
        $client->api('projects')->addVariable($cacprojectid, "CAC_ID", $cacprojectid);
        $client->api('projects')->addVariable($cacprojectid, "CDR_URL", $cdrprojectlink);
        $client->api('projects')->addVariable($cacprojectid, "SRC_DIR", $srcdir);
        $client->api('projects')->addVariable($cacprojectid, "gitlabtoken", $gitlabtoken);
        $client->api('projects')->addVariable($cacprojectid, "SSH_KEY_CLONE_CDR", $clonecdrprivatekey);

        //Add Webhook for pushing from the CDR to the CAC
        //Build Hook Style https://gitlab.informatik.haw-hamburg.de/api/v4/projects/1045/trigger/pipeline?token="token"
        $hook = 'https://gitlab.informatik.haw-hamburg.de/api/v4/projects/' . $cacprojectid . '/trigger/pipeline?token=' . $gitlabtoken;
        $cdrproject->addHook($hook);




        $insRec  = new MongoDB\Driver\BulkWrite;
        $insRec->insert([
        	'name' =>$projectName,
        	'cdr_name'=>$CDRname,
        	'cac_name'=>$CACname,
        	'email'=>$email,
        	'projectpublickey'=>$cdrprojectpublickey,
        	'cdrprivatekey'=>$cdrprojectprivatekey,
        	'cacprivatekey'=>$cacprojectprivatekey,
        	'cacpublickey'=>$cacprojectpublickey,
        	'clone_cdr_publickey'=>$clonecdrpublickey,
        	'clone_cdr_privatekey'=>$clonecdrprivatekey,
        	'update_cac_publickey'=>$updatecacpublickey,
        	'update_cac_privatekey'=>$updatecacprivatekey,
        	'cdr_url' =>$cdrprojectlink,
        	'cac_url' =>$cacprojectlink,
        	'CAC_ID'=>$cacprojectid,
        	'CDR_ID'=>$cdrprojectid
            'src_dir'=>$srcdir
        ]);
        $writeConcern = new MongoDB\Driver\WriteConcern(MongoDB\Driver\WriteConcern::MAJORITY, 1000);
        $result       = $manager->executeBulkWrite('userdata.projects', $insRec, $writeConcern);



        if($result->getInsertedCount()){
            header("Location: ../project.php");
        } else{
            header("Location: ../project.php");
        }
    }


?>
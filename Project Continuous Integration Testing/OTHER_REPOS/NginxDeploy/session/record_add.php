<?php
  require_once('dbconn.php');
  $name         = '';
  $mail         = '';
  $password     = '';
  $flag         = 0;
  if(isset($_POST['btn'])){
      $name        = $_POST['name'];
      $mail        = $_POST['mail'];
      $password    = $_POST['password'];

      if(!$name || !$mail || !$password){
        $flag = 5;
      }else{
          $filter = ['name' => ['$eq' => $name]];
           $options = [
              'projection' => ['_id' => 0],
           ];
           $query = new MongoDB\Driver\Query($filter, $options);
           $rowsname = $manager->executeQuery('userdata.credentials', $query);
           $filter = ['mail' => ['$eq' => $mail]];
           $query = new MongoDB\Driver\Query($filter, $options);
           $rowsemail = $manager->executeQuery('userdata.credentials', $query);
          
            $countername = 0;
            $counteremail = 0;
          
            foreach ($rowsname as $row) {
                $countername = $countername + 1;
            }
            foreach ($rowsemail as $row) {
                $counteremail = $counteremail + 1;
            }
            
          if($countername == 0 && $counteremail == 0)
            {
                $hashed_password = password_hash($password, PASSWORD_DEFAULT);
              
                $insRec       = new MongoDB\Driver\BulkWrite;
                $insRec->insert(['name' =>$name, 'mail'=>$mail, 'password'=>$hashed_password]);
                $writeConcern = new MongoDB\Driver\WriteConcern(MongoDB\Driver\WriteConcern::MAJORITY, 1000);
                $result       = $manager->executeBulkWrite('userdata.credentials', $insRec, $writeConcern);

                if($result->getInsertedCount()){
                $flag = 3;
                } else{
                    $flag = 2;
                }
            } else if($countername > 0 && $counteremail == 0) {
                $flag = 6;
            } else if($countername == 0 && $counteremail > 0) {
                $flag = 7;
            } else {
                $flag = 8;
            }
      }
  }
  header("Location: ../register.php?flag=$flag");
  exit;

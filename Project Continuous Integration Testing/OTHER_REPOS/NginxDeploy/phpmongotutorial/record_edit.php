<?php
  require_once('dbconn.php');
  $name = '';
  $mail        = '';
  $password     = '';
  $flag         = 0;
  if(isset($_POST['btn'])){
      $name = $_POST['name'];
      $mail        = $_POST['mail'];
      $password     = $_POST['password'];
      $id           = $_POST['id'];

      if(!$name || !$mail || !$password || !$id){
        $flag = 5;
      }else{
          $hashed_password = password_hash($password, PASSWORD_DEFAULT);
          
          $insRec       = new MongoDB\Driver\BulkWrite;
          $insRec->update(['_id'=>new MongoDB\BSON\ObjectID($id)],['$set' =>['name' =>$name, 'mail'=>$mail, 'password'=>$hashed_password]], ['multi' => false, 'upsert' => false]);
          $writeConcern = new MongoDB\Driver\WriteConcern(MongoDB\Driver\WriteConcern::MAJORITY, 1000);
          $result       = $manager->executeBulkWrite('userdata.credentials', $insRec, $writeConcern);
          if($result->getModifiedCount()){
            $flag = 3;
          }else{
            $flag = 2;
          }
      }
  }
  header("Location: index.php?flag=$flag");
  exit;

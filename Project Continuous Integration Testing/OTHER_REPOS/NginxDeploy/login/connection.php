<?php
    require '../vendor/autoload.php'; // include Composer's autoloader
    try{
    

    $mongo = new MongoDB\Client('mongodb://mongodb.cies-mongodeploy.svc.cluster.local:27017');
     //echo "Connection to database Successfull!";echo"<br />";

    $db = $mongo->loginreg;
    //echo "Databse loginreg selected";
    $collection = $db->userdata; 
    //echo "Collection userdata Selected Successfully";
    }
    catch (Exception $e){
        die("Error. Couldn't connect to the server. Please Check");
    }
       session_start();
?>
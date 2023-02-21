<?php require_once 'dbconn.php'; ?>
<?php require_once 'helper.php'; ?>
<?php
    
    if(chkLogin()){
        header("Location: index.php");
    }
?>
<?php

    if(isset($_POST['login'])){
//        print_r($_POST);
      
        
        $email = $_POST['email'];
        $upass = $_POST['pass'];
        
        //Get the user which E-Mail Equals the one.
        $filter = ['mail' => ['$eq' => $email]];
        $options = [
              'projection' => ['_id' => 0],
        ];
        $query = new MongoDB\Driver\Query($filter, $options);
        $rowsname = $manager->executeQuery('userdata.credentials', $query);
        
        $counter = 0;
        
        foreach ($rowsname as $row) {
                $counter = $counter + 1;
                $passfromdb = $row->password;
        }
        
        //var_dump($query);
        if($counter == 0 || $counter >= 2){
            $flag = 9;
            header("Location: ../register.php");
        } else {
                $pass = $passfromdb;
                if(password_verify($upass,$pass)){
                    $var = setsession($email);
                    if($var){
                        
                    header("Location: ../index.php");
                    }
                    else{
                        echo "Login Error";
                    }
                } else{
                    echo "You have entered a wrong password";
                    echo "<br>";
                    echo "Either <a href='register.php'>Register</a> with the new Email ID or <a href='login.php'>Login</a> with an already registered ID";
                }
        } 
    }
    

?>
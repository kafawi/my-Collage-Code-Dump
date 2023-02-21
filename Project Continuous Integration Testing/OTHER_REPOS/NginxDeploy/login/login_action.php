<?php require_once 'connection.php'; ?>
<?php require_once 'library.php'; ?>
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
        
        foreach ($rowsname as $row) {
                $counter = $counter + 1;
                $passfromdb = $row->password;
        }
        
        //var_dump($query);
        if($counter == 0 || ){
            $flag = 9;
        } else {
                $pass = $passfromdb;
                if(password_verify($upass,$pass)){
                    $var = setsession($email);
                    if($var){
                        
                    header("Location: home.php");
                    }
                    else{
                        echo "Some error";
                    }
                }
                else{
                    echo "You have entered a wrong password";
                    echo "<br>";
                    echo "Either <a href='register.php'>Register</a> with the new Email ID or <a href='login.php'>Login</a> with an already registered ID";
                }
                
            
        
        }
    }
    

?>
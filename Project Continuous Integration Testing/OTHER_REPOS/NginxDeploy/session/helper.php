<?php
    if (session_status() == PHP_SESSION_NONE) {
        session_start();
    }
    require_once 'dbconn.php';
    
    function setsession($mail){        
        $_SESSION["userLoggedIn"] = 1;
        //global $collection;
        //$temp = $collection->findOne(array('Email Address'=> $email));
        $name = 'Temp';
        $_SESSION["name"] = $name;
        $_SESSION["mail"] = $mail;
        return true;
    }
    
    function chkLogin(){
        
        if (isset($_SESSION["userLoggedIn"])) {
            if($_SESSION["userLoggedIn"]== 1) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    
    function getSessionMail(){
        return $_SESSION["mail"];
    }
    
    function removeall(){
        unset($_SESSION["userLoggedIn"]);
        unset($_SESSION["name"]);
        unset($_SESSION["mail"]);
        return true;
    }

?>
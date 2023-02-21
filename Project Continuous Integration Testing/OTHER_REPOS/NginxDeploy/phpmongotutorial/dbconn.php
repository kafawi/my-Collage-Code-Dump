<?php
ini_set('display_errors','true');
error_reporting(E_ALL);

$messages = array(
	1=>'Record deleted successfully',
	2=>'Error occured. Please try again.', 
	3=>'Record saved successfully.',
    4=>'Record updated successfully.', 
    5=>'All fields are required.',
    6=>'User already exists.',
    7=>'E-Mail already in use.',
    8=>'Make sure you are not already registered.'    );


$mongoDbname  =  'userdata';
$mongoTblName =  'credentials';
$manager     =   new MongoDB\Driver\Manager("mongodb://mongodb.cies-mongodeploy.svc.cluster.local:27017");
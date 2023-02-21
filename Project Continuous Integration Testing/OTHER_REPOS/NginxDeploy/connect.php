

<?php
require 'vendor/autoload.php'; // include Composer's autoloader

$mongo = new MongoDB\Client('mongodb://10.32.92.39:27017');
try 
{
    $dbs = $mongo->listDatabases();
}
catch (MongoDB\Driver\Exception\ConnectionTimeoutException $e)
{
    echo "This is not working!";
    // PHP cannot find a MongoDB server using the MongoDB connection string specified
    // do something here
}
?>

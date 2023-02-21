

<?php
require 'vendor/autoload.php'; // include Composer's autoloader

$mongo = new MongoDB\Client('mongodb://mongodb.cies-mongodeploy.svc.cluster.local:27017');
try 
{
    $dbs = $mongo->listDatabases();
}
catch (MongoDB\Driver\Exception\ConnectionTimeoutException $e)
{
    echo "This is not working!\n";
    
    $ip = gethostbyname('mongodb.cies-mongodeploy.svc.cluster.local');

echo $ip;
    // PHP cannot find a MongoDB server using the MongoDB connection string specified
    // do something here
}
?>

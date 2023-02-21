<?php
require_once('dbconn.php');
$id    = $_GET['id'];
$result = array();
if($id){
  $filter = ['_id' => new MongoDB\BSON\ObjectID($id)];
  $options = [
   'projection' => ['_id' => 0],
];
  $query = new MongoDB\Driver\Query($filter,$options);
  $cursor = $manager->executeQuery('userdata.credentials', $query);
  foreach($cursor as $row){
    $result ['name'] = $row->name;
    $result ['mail']        = $row->mail;
    $result ['password']     = $row->password;
    $result ['id']           = $id;
  }
  echo json_encode($result);
}

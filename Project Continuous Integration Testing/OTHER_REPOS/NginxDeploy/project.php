<?php
require_once './session/helper.php';
    if(chkLogin()){
        
    } else {
        header("Location: index.php");
    }
    
require_once('./session/dbconn.php');
$flag    = isset($_GET['flag'])?intval($_GET['flag']):0;
$message ='';
if($flag){
  $message = $messages[$flag];
}

//Get User Mail
$useremail = getSessionMail();

//Query for Project List
$filter = ['email' => ['$eq' => $useremail]];
$options = [
              'projection' => ['_id' => 0],
           ];

$query = new MongoDB\Driver\Query($filter, $options);
$cursor = $manager->executeQuery('userdata.projects', $query);

?>

<!DOCTYPE HTML>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" type="image/png" sizes="32x32" href="/img/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="/img/favicon-16x16.png">

    <title>CIES by TeSSA</title>

    <!-- Bootstrap core CSS -->
    <link href="/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="jumbotron.css" rel="stylesheet">
  </head>

  <body>

    <?php
      include_once 'nav.php';
    ?>
    
    <hr>

    <?php if(chkLogin()):?>
        <div class="container">
            <h3>Project Overview</h3>
            <form class="form-horizontal" method="post" action="./session/create_project_action.php">
                <div class="form-group">
                    <label class="sr-only" for="exampleInputEmail3">Project Name</label>
                    <input type="text" class="form-control" id="projectName" name="projectName" placeholder="Project Name" required>
                </div>
                <div class="form-group">
                    <label class="sr-only" for="exampleInputEmail3">Project Name</label>
                    <input type="text" class="form-control" id="publicKey" name="publicKey" placeholder="Public Key" required>
                </div>
                <button type="submit" name="createProject" class="btn btn-success">Create Project</button>
            </form>
            <hr>
            <table class="table">
              <thead class="thead-light">
                <tr>
                  <th scope="col">#</th>
                  <th scope="col">Project Name</th>
                  <th scope="col">SSH Git Link</th>
                  <th scope="col">Access Key</th>
                  <th scope="col">Logs</th>
                </tr>
              </thead>
              <tbody>
                <?php
                $i =1;
                foreach ($cursor as $row) {
                    $projectname = $row->name;
                    $projectpublickey = $row->projectpublickey;
                    $projectsshlink = $row->cdr_url;
                ?>
                  <tr>
                  <th scope="row"><?=$i?></th>
                  <td><?=$projectname?></td>
                  <td><?=$projectsshlink?></td>
                  <td><?php echo wordwrap($$projectpublickey,40)?></td>
                  <td>Your Logs And Options Window</td>
                  </tr>
                <?php $i++;  
                    } 
                ?>
                
              </tbody>
            </table>
        </div>
    <?php else: ?>
      <div class="container">
        <h1 class="display-3">Error Accessing this page! Please Login.</h1>
        <p><a class="btn btn-primary btn-lg" href="/index.php" role="button">Home &raquo;</a></p>
      </div>
    <?php endif;?>
    
    

      <hr>
      <?php
        include_once 'footer.php';
      ?>

    </div> <!-- /container -->


    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script>window.jQuery || document.write('<script src="../../../../assets/js/vendor/jquery.min.js"><\/script>')</script>
    <script src="/bootstrap/popper/popper.min.js"></script>
    <script src="/bootstrap/js/bootstrap.min.js"></script>
  </body>
</html>

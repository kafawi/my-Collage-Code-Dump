<?php
require_once './session/helper.php';
    if(chkLogin()){
        header("Location: index.php");
    }
require_once('./session/dbconn.php');
$flag    = isset($_GET['flag'])?intval($_GET['flag']):0;
$message ='';
if($flag){
  $message = $messages[$flag];
}
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

        include_once 'main_banner.php';
    ?>
    <?php
    if(removeAll()):?>
        <div class="container">
            Logout successful.
        </div>
    <?php else: ?>
        <div class="container">
            Logout failed.
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
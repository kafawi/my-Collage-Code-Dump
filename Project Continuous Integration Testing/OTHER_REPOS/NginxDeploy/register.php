<?php
require_once './session/helper.php';
require_once('./session/dbconn.php');
$flag_f = filter_input(INPUT_GET, "flag", FILTER_SANITIZE_SPECIAL_CHARS);
$flag    = isset($flag_f)?intval($flag_f):0;
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
    ?>
    <div class="container">
      <h1 class="display-4">Register an User Account</h1>
      <!--<a href="#description_registration" data-toggle="collapse">more &raquo;</a>-->
      <div id="description_registration">
        <p>
          With the registration you gain access to the CIES Analysis Plattform.
          There you can manage your settings and see the history of past analysis runs.
          Registration is free but for now only available to students at HAW Hamburg.
        </p>
      </div>

      <!-- Example row of columns -->
        <p>
            <?php if($flag == 2 || $flag == 5 || $flag == 6 ||  $flag == 7 || $flag == 8 ){ ?>
            <div class="alert alert-danger"><?php echo $message; ?></div>
            <?php  } elseif($flag && $flag != 2 ){ ?>
            <div class="alert alert-success"><?php echo $message; ?></div>
            <?php  } ?>
        </p>
        <form id="form1" name="form1" action="./session/record_add.php" method="post">
            <div class="form-group">
                <label for="exampleInputEmail1">Username</label>
                <input type="text" class="form-control" id="name" name="name" placeholder="Enter username">
            </div>
            <div class="form-group">
                <label for="exampleInputEmail1">Email address</label>
                <input type="email" class="form-control" id="mail" name="mail" aria-describedby="emailHelp" placeholder="Enter email">
                <!--<small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small> -->
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Password</label>
                <input type="password" class="form-control" id="password" name="password" placeholder="Password">
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="checkbox" class="form-check-input" id="DataProtectionRegulations">
                    I have read and understood the <a href="/datenschutz.php">Privacy Policy</a>.
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="checkbox" class="form-check-input" id="Licence">
                    I agree to the <a href="/termsofuse.php">Terms of Use</a>.
                </label>
            </div>
            <button type="submit" name='btn' id='btn' class="btn btn-primary">Register</button>
        </form>

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

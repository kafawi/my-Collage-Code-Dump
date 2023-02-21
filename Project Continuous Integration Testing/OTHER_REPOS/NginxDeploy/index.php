<?php 
require_once './session/helper.php';
?>
<!DOCTYPE html>
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
    <link rel="stylesheet" type="text/css" href="//cdnjs.cloudflare.com/ajax/libs/cookieconsent2/3.0.3/cookieconsent.min.css" />
<script src="//cdnjs.cloudflare.com/ajax/libs/cookieconsent2/3.0.3/cookieconsent.min.js"></script>
<script>
window.addEventListener("load", function(){
window.cookieconsent.initialise({
  "palette": {
    "popup": {
      "background": "#000"
    },
    "button": {
      "background": "#f1d600"
    }
  },
  "theme": "classic",
  "content": {
    "dismiss": "Got it!"
  }
})});
</script>
  </head>

  <body>
    <?php
      include_once 'nav.php';

      include_once 'main_banner.php';
    ?>
    <div class="container">
      <!-- Example row of columns -->
      <div class="row">
        <div class="col-md-4">
          <h2>Easy to Use!</h2>
          <p>You register your project. We do the integration into the analysis pipeline. Your project will be automatically checked on each commit with our toolset and you will get the report.</p>
          <!--<p><a class="btn btn-secondary" href="#" role="button">View details &raquo;</a></p>-->
        </div>
        <div class="col-md-4">
          <h2>State of the Art Analysis!</h2>
          <p>As a researching group we integrate the latest analysis techniques in our toolset. Your project will directly benefit from each improvement without additional effort from your side.</p>
          <!-- <p><a class="btn btn-secondary" href="#" role="button">View details &raquo;</a></p> -->
       </div>
        <div class="col-md-4">
          <h2>Reporting</h2>
          <p>All findings will be reported via our own web interface. You can also get a detailed report via email.</p>
          <!-- <p><a class="btn btn-secondary" href="#" role="button">View details &raquo;</a></p> -->
        </div>
      </div>

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

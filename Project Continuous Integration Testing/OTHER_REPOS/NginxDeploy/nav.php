<nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
<a class="navbar-brand" href="/index.php"><img src="/img/CIES.PNG" width="30" height="30" />CIES</a>

  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>

  <div class="collapse navbar-collapse" id="navbarsExampleDefault">
    <ul class="navbar-nav mr-auto">
      <li class="nav-item active">
        <a class="nav-link" href="/index.php">Home <span class="sr-only">(current)</span></a>
      </li>
 <?php if(!chkLogin()):?>
      <li class="nav-item">
        <a class="nav-link" href="/register.php">Register</a>
        <!--<div class="dropdown-menu" aria-labelledby="dropdown01">
          <a class="dropdown-item" href="/anmeldung.php">Projekt zum Testen anmelden</a>
          <a class="dropdown-item" href="#">Coming Soon!</a>
        </div> -->
      </li>
<?php endif; ?>
      <li class="nav-item">
        <a class="nav-link" href="https://gitlab.informatik.haw-hamburg.de/CIES/">Contribute</a>
      </li>

      <li class="nav-item">
        <a class="nav-link" href="https://tessa.haw-hamburg.de/">TeSSA</a>
      </li>
    </ul>
        <?php if(chkLogin()):?>
            <ul class="nav navbar-nav navbar-right">
                <li class="nav-item">
                    <a class="nav-link" href="/project.php"> Projects</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link" href="/logout.php"> Logout</a>
                </li>
            </ul>
        <?php else: ?>
            <ul class="nav navbar-nav navbar-right">
                <li class="nav-item">
                    <a class="nav-link" href="/login.php"> Login</a>
                </li>
            </ul>
        <?php endif;?>        
  </div>
</nav>

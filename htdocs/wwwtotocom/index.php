<?php

if(isset($_GET['nom']) && !empty($_GET['nom'])) {
    $nom = $_GET['nom'];
    $password = $_GET['password'];
    $display = "";
    $display2 = "none";
}
else {
    if(isset($_POST['nom']) && !empty($_POST['nom'])) {
        $nom = $_POST['nom'];
        $password = $_POST['password'];
        $display = "none";
        $display2 = "";
    }
    else {
        $nom = "";
        $password = "";
        $display = "none";
        $display2 = "none";
    }
}


?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <title>Document</title>
</head>
<body style="background-color: lightgrey;">
    <div class="container" style="margin-top: 50px;">
        <div class="row">
            <div class="col-6">
                <h1>Méthode GET</h1>
                <form method="get" action="">
                    <div class="mb-3">
                        <label for="exampleInputEmail1" class="form-label">Donner votre Nom</label>
                        <input type="text" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" name="nom">
                    </div>
                    <div class="mb-3">
                        <label for="exampleInputPassword1" class="form-label">Password</label>
                        <input type="password" class="form-control" id="exampleInputPassword1" name="password">
                    </div>
                    <button type="submit" class="btn btn-primary">Submit</button>
                </form>
                <div class="answer" style="display: <?=$display?>">
                    <p style="margin-top: 20px;">Bravo votre nom est : <strong><?=$nom?></strong> et votre mot de passe est <strong><?=$password?></strong></p>
                </div>
            </div>
            <div class="col-6">
                <h1>Méthode POST</h1>
                <form method="post" action="">
                    <div class="mb-3">
                        <label for="exampleInputEmail1" class="form-label">Donner votre Nom</label>
                        <input type="text" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" name="nom">
                    </div>
                    <div class="mb-3">
                        <label for="exampleInputPassword1" class="form-label">Password</label>
                        <input type="password" class="form-control" id="exampleInputPassword1" name="password">
                    </div>
                    <button type="submit" class="btn btn-primary">Submit</button>
                </form>
                <div class="answer" style="display: <?=$display2?>">
                    <p style="margin-top: 20px;">Bravo votre nom est : <strong><?=$nom?></strong> et votre mot de passe est <strong><?=$password?></strong></p>
                </div>
            </div>
        </div>
    </div>





    <!-- Bootstrap JS bundle -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
</body>
</html>
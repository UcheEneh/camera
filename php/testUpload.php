<?php
$target = "Images/";
$target = $target . basename( $_FILES['fileToUpload']['name']) ;
$uploadOk = 1;

//Size condition: not more than 10MB
if ($_FILES["fileToUpload"]["size"] > 10000000) {
    echo "Sorry, your file is too large. <br>";
    $uploadOk = 0;
}

echo $_FILES["fileToUpload"]["size"];

//This is our limit file type condition
if ($uploaded_type =="text/php") {
        echo "No PHP files<br>";
        $uploadOk = 0;
}

echo $_FILES["fileToUpload"]["type"];

//Here we check that $ok was not set to 0 by an error
if ($uploadOk == 0) {
        echo "Sorry your file was not uploaded";
}

//If everything is ok we try to upload it
else {
        if(move_uploaded_file($_FILES['fileToUpload']['tmp_name'], $target)) {
                echo "The file successfully ". basename( $_FILES['fileToUpload']['name']). " has been uploaded";
        }
        else {
                echo "Sorry, there was a problem uploading your file.";
        }
}

?>
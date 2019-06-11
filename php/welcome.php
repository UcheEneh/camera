<html>
<body>

<!--
Welcome <?php echo $_POST["name"]; ?><br>
Your email address is: <?php echo $_POST["email"]; ?>
-->


Welcome <?php 

require "conn.php";

$target_dir = "Images/";
$target_file = $target_dir . basename($_FILES['fileToUpload']['name']) ;
$uploadOk = 1;



// Check if file already exists or if file is empty
if (file_exists($target_file)) { //this is first because if file is empty this condition would still be satisfied

    if ($_FILES['fileToUpload']['size'] == 0 && $_FILES['fileToUpload']['error'] == 0){
            echo "Sorry, no image selected to upload. <br>";
            $uploadOk = 0;
    }
    else{
            echo "Sorry, file ". basename($_FILES['fileToUpload']['name']). " already exists. <br>";
            $uploadOk = 0;
    }           
}

//Size condition: not more than 10MB
if ($_FILES["fileToUpload"]["size"] > 10000000) {
    echo "Sorry, your file is too large. <br>";
    $uploadOk = 0;
}

//This is our limit file type condition
if ($_FILES["fileToUpload"]["type"] == "php") {
        echo "No PHP files <br>";
        $uploadOk = 0;
}

//Here we check that $ok was not set to 0 by an error
if ($uploadOk == 0) {
        echo "Sorry your file was not uploaded <br>";
}

//If everything is ok we try to upload it to server and database
else {
        if(move_uploaded_file($_FILES['fileToUpload']['tmp_name'], $target_file)) {
                echo "The file ". basename( $_FILES['fileToUpload']['name']). " has been successfully uploaded to server <br>";
                
                
                // prepare and bind
                $stmt = mysqli_prepare($conn, "INSERT INTO info2 (name,category,date,image) VALUES (?, ?, ?, ?)");             
                
                // set parameters and execute
                $name = $_POST["name"];
                $category = $_POST["category"];
                $date = $_POST["date"];
                $image = basename($_FILES['fileToUpload']['name']);
                
                // bind parameters for markers 
                mysqli_stmt_bind_param($stmt, "ssss", $name, $category, $date, $image);
                
                
                // execute query 
                if (!mysqli_stmt_execute($stmt)) {
                        echo("Database error description: " . mysqli_error($conn));
                }
                else {
                        echo "Saved into Database <br>"; 
                        
                        // close statement 
                        mysqli_stmt_close($stmt);
                }
        }
        else {
                echo "Sorry, there was a problem uploading your file. <br>";
        }
}

?>



<div class = "gallery">
<h2> Uploaded Images </h2>

<?php      

//-------------------SHOW IMAGE FROM DATABASE / SERVER

//require 'conn.php';

$mysql_qry = "select * from info2;";
//$mysql_qry = "select * from info2 where name like '$user_name' and category like '$user_category';";
//$mysql_qry = "select * from info2 order by uploaded_on desc;";

$result = mysqli_query($conn, $mysql_qry); 




if (mysqli_num_rows($result) > 0) {
    // output data of each row
    while($row = mysqli_fetch_assoc($result)) {
        //$imageURL = $target_dir . $row["image"];
        $imageURL = 'Images/' . $row["image"];
?>

        <img src="<?php echo $imageURL; ?>"/>

<?php
        echo "id: " . $row["id"]. ", Name: " . $row["name"]. ", Category: " . $row["category"].  ", Date: " . $row["date"].  ", Path: " . $row["image"]. "<br>";
    }
} else {
?>

        <p> No result found </p>

<?php
}

mysqli_close($conn);       
?>
</div>

</body>
</html>
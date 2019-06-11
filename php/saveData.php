<?php
require "conn.php";

// prepare and bind
$stmt = mysqli_prepare($conn, "INSERT INTO info2 (name,category,date,image) VALUES (?, ?, ?, ?)");


// set parameters and execute
$name = $_GET["name"];
$category = $_GET["category"];
$date = $_GET["date"];
$image = $_GET["image"];

// bind parameters for markers 
mysqli_stmt_bind_param($stmt, "sssb", $name, $category, $date, $image);


// execute query 
if (!mysqli_stmt_execute($stmt)) {
        echo("Error description: " . mysqli_error($conn));
}
else {
        echo "Saved into Database" . "<br>"; 
        
        // close statement 
        mysqli_stmt_close($stmt);
}



/*
$insert = "insert into info2 (name,category,date,image) values ('$name', '$category', '$date', $image)";

if (!mysqli_query($conn, $insert)) {
        echo("Error description: " . mysqli_error($conn));
}
else {
        echo "Saved into Database" . "<br>"; 
}
*/



mysqli_close($conn);

?>
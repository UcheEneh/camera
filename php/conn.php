<?php

$db_name = "2896427_db";
$mysql_username = "2896427_db";
$mysql_password = "Awardspace1!";
$server_name = "fdb24.awardspace.net";

$conn = mysqli_connect($server_name, $mysql_username, $mysql_password, $db_name); 

// Check connection
if (!$conn) {
    die("Database Failed: " . mysqli_connect_error());
}
//else {
//	echo "Database Connected" . "<br>"; 
//}

?>
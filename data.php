<?php
include ('connection.php');
$sql_insert = "INSERT INTO ethernet.data (vehicle) VALUES ('".$_GET["vehicle"]."')";
if(mysqli_query($con,$sql_insert))
{
echo "Done";
mysqli_close($con);
}
else
{
echo "error is ".mysqli_error($con );
}
?>
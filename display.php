<?php
$url=$_SERVER['REQUEST_URI'];
header("Refresh: 5; URL=$url"); // Refresh the webpage every 5 seconds
?>
<html>
<head>
<title>Arduino Ethernet Database</title>
</head>
<body>
<table border="0" cellspacing="0" cellpadding="4">
<tr>
<td class="table_titles">Vrijeme</td>
<td class="table_titles">Vozilo</td>
</tr>
<?php
include('connection.php');
$result = mysqli_query($con,'SELECT * FROM data ORDER BY id DESC');
// Process every record
$oddrow = true;
while($row = mysqli_fetch_array($result))
{
if ($oddrow)
{
$css_class=' class="table_cells_odd"';
}
else
{
$css_class=' class="table_cells_even"';
}
$oddrow = !$oddrow; 
echo "<tr>";
echo "<td '.$css_class.'>" . $row['event'] . "</td>";
echo "<td '.$css_class.'>" . $row['vehicle'] . "</td>";
echo "</tr>"; 
}
 
// Close the connection
mysqli_close($con);
?>
</table>
</body>
</html>
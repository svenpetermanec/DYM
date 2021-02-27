<?php
    include_once 'connection.php';
?>
<html>
<head></head>
<body>
    
<pre>ID  Vrijeme ulaska      Vrijeme izlaska</pre>
<?php
    $option=$_POST['option'];
    $query="SELECT * FROM vjezba WHERE (ID = $option) ORDER BY ulazak DESC";
    $response=mysqli_query($connection, $upit);
    $check=mysqli_num_rows($response);
    
    if($check>0){
        while($red=mysqli_fetch_assoc($response)){
            echo $red['ID'] ." ".$red['entry'] ." ".$red['exit']."<br>";
        }
    }
?>
</body>
</html>
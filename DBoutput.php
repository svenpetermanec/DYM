<?php
    include_once 'connection.php';
?>

<!DOCTYPE html>
<html>
<head></head>
<body>
<pre>ID  Vrijeme ulaska      Vrijeme izlaska</pre>
<?php
    $upit="SELECT * FROM vjezba ORDER BY entery DESC";
    $rezultati=mysqli_query($connection, $upit);
    $provjera=mysqli_num_rows($rezultati);
    
    if($provjera>0){
        while($red=mysqli_fetch_assoc($rezultati)){
            echo $red['ID'] ." ".$red['entry'] ." ". $red['exit']."<br>";
        }
    }
?>
<form method="POST" action="filtar.php">
    <select name="option" id="opcija">
        <option>--</option>
        <option value="99">99</option>
        <option value="37">37</option>
        <option value="14">14</option>
    </select>
    <button type="submit" name="submit" value="submit">SUBMIT</button>
</form>
</body>
</html>
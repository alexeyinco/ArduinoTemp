<?php 
$myFile = "../txt/out-1.txt";
$fh = fopen($myFile, 'r');
$theData = fread($fh, filesize($myFile));
fclose($fh);
if  ( $theData == 1)
{
 echo " <p class='on'>ON</p>";
}

if  ( $theData == 0)
{
 echo "<p class='off'>OFF</p>";
}

?>
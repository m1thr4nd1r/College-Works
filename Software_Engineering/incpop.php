<?php
include_once 'controller.php';

$cidade=$_GET["q"];
//$dbname= "500820db2"; 
//$usuario="500820";
//$password="viajante"; 
$dbname= "viajantesemdestino"; 
$usuario="root";
$password="";

if (conectaDB($dbname,$usuario,$password))
{
    incrementarPopularidade($cidade);
    fechaDB();
}
?>
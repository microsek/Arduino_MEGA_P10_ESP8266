<?PHP 
include("config.inc.php");

	for($i=1;$i<=3;$i++)
  {
    $qry= mysql_query("select * from 1101_real where real_id='".$i."'");
    $fetch=mysql_fetch_array($qry);
    $text[$i]=$fetch["real_text"];
  }
	$qry= mysql_query("select * from 1101_speed where id='1'");
	$fetch=mysql_fetch_array($qry);
 echo "<".$text[3]."[".$fetch["speed"]."]";
 //echo "<".$text[1].",".$text[2].",".$text[3]."[".$fetch["speed"]."]>";
	//echo "SPEED=".$fetch["speed"];
  	//echo"".$text["1"].",".$text["2"].",".$text["3"].",".$fetch["speed"].".";
?>
<?php 
	$host="localhost";  // กำหนด host
	$username="root";  // กำหนด username
	$pass_word=""; // กำหนด Password
	$db="1101"; // กำหนดชื่อฐานข้อมูล
	$Conn = mysql_connect( $host,$username,$pass_word) or die ("ติดต่อฐานข้อมูลไม่ได้");// ติดต่อฐานข้อมูล
	mysql_query("SET NAMES utf8",$Conn); // set กำหนดมาตราฐาน
	mysql_select_db($db) or die("เลือกฐานข้อมูลไม่ได้");  // เลือกฐานข้อมูล 
	mysql_query("SET character_set_results=utf8", $Conn);
	mysql_query("SET character_set_client=utf8", $Conn);
	mysql_query("SET character_set_connection=utf8", $Conn);
	mysql_query('SET CHARACTER SET utf8', $Conn);
	mysql_query('SET collation_connection = utf8_general_ci', $Conn);
	date_default_timezone_set('Asia/Bangkok');
?>
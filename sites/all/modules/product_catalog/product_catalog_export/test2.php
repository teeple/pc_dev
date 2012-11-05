<?php
function view_get_field_value_by_label($v , $w , $d)
{
return 1;
}

$s = '$arr = array( "MON", "TUE" , "WED" , "THU" , "FRI" , "SAT" , "SUN" );
$str = NULL;
foreach($arr as $week)
{
	if(view_get_field_value_by_label($view , $week , $data) == 1)
	{
		if($str == "")
			$str = strtolower($week);
		else
			$str = $str.",". strtolower ($week);
	}
}
echo $str;';


create_function('', $s);

?>

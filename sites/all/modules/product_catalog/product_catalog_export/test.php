<?php
$s = '$arr = [ 'MON', 'TUE' , 'WED' , 'THU' , 'FRI' , 'SAT' , 'SUN' ];
$str = NULL;
foreach($arr as $week)
{
	if(view_get_field_value_by_label($view , $week , $data) == 1)
	{
		if($str == '')
			$str = strtolower($week);
		else
			$str = $str.','. strtolower ($week);
	}
}
echo $str;'

create_function(NULL , $s);
?>

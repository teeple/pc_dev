<?php

function ocs_test_case_json( $nid, $data)
{
	$node = node_load( $nid);
	$field = field_info_instances( 'node', $node->type);

	$obj = array();
	foreach( $field as $key => $value) {
		$v = $node->$key;
		$obj[ $value['label']] = is_array( $v) ? ( empty($v) ? null : $v['und'][0]['value']) : $v;
//		$obj[ $value['label']] = $v;
	}

//	$output = print_r( $obj);
//	$output = drupal_json_encode( $obj);
	if (strnatcmp(phpversion(),'5.4') >= 0) {
		$output = json_encode( $obj, JSON_PRETTY_PRINT);
	}
	else {
		$output = json_format( json_encode( $obj));
	}

	return $output;
}

// Pretty print some JSON 
function json_format($json) 
{ 
    $tab = "  "; 
    $new_json = ""; 
    $indent_level = 0; 
    $in_string = false; 

    $json_obj = json_decode($json); 

    if($json_obj === false) 
        return false; 

    $json = json_encode($json_obj); 
    $len = strlen($json); 

    for($c = 0; $c < $len; $c++) 
    { 
        $char = $json[$c]; 
        switch($char) 
        { 
            case '{': 
            case '[': 
                if(!$in_string) 
                { 
                    $new_json .= $char . "\n" . str_repeat($tab, $indent_level+1); 
                    $indent_level++; 
                } 
                else 
                { 
                    $new_json .= $char; 
                } 
                break; 
            case '}': 
            case ']': 
                if(!$in_string) 
                { 
                    $indent_level--; 
                    $new_json .= "\n" . str_repeat($tab, $indent_level) . $char; 
                } 
                else 
                { 
                    $new_json .= $char; 
                } 
                break; 
            case ',': 
                if(!$in_string) 
                { 
                    $new_json .= ",\n" . str_repeat($tab, $indent_level); 
                } 
                else 
                { 
                    $new_json .= $char; 
                } 
                break; 
            case ':': 
                if(!$in_string) 
                { 
                    $new_json .= ": "; 
                } 
                else 
                { 
                    $new_json .= $char; 
                } 
                break; 
            case '"': 
                if($c > 0 && $json[$c-1] != '\\') 
                { 
                    $in_string = !$in_string; 
                } 
            default: 
                $new_json .= $char; 
                break;                    
        } 
    } 

    return $new_json; 
} 
<?php
function ocs_admin_run_testcase( $type, $nid)
{
    if ( $type == 'ocs') {
        print ocs_testcase_for_ocs( $nid);
    }
}

function ocs_testcase_for_ocs( $nid)
{
    // content type test_case_ocs
    $node = node_load( $nid);

    $url = 'http://' . $node->field_ts_host['und'][0]['value'] . $node->field_ts_api['und'][0]['value']; 

    $output = '';
    $field = NULL;
    // get test data
    foreach( $node->field_ts_test_data['und'] as $key => $value) {
        $ts_data = node_load( $value);
        if ( $field == NULL) $field = field_info_instances( 'node', $ts_data->type);

        $data = ocs_build_ts_json( $ts_data, $field);
        $response = http_post_data( $url, ocs_json_encode($data));
        $output += $response;

        dpm( $response);
    }

    return $url . $output;
}

function ocs_test_case_json( $nid, $data)
{
	$node = node_load( $nid);
	$field = field_info_instances( 'node', $node->type);
    return ocs_build_ts_json( $node, $field);
}

function ocs_build_ts_json( $node, $field=NULL)
{
    if ( $field == NULL) {
        $field = field_info_instances( 'node', $node->type);
    }

	$obj = array();
	foreach( $field as $key => $value) {
		$v = $node->$key;
		$obj[ $value['label']] = is_array( $v) ? ( empty($v) ? null : $v['und'][0]['value']) : $v;
//		$obj[ $value['label']] = $v;
	}

    return $obj;
}

function ocs_json_encode( $obj)
{
    /*
	$output =  (strnatcmp(phpversion(),'5.4') >= 0) ?  
        json_encode( $obj, JSON_PRETTY_PRINT) :
		json_format( json_encode( $obj));
        */
    $output = json_encode( $obj);

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

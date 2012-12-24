<?php

function ocs_admin_run_api( $param1, $param2)
{
    print '{"result":"success"}';
}


function ocs_admin_run_testcase( $type, $nid, $tc)
{
    if ( $type == 'ocs') {
        if ( $nid == 'count') {
            // ajax/test/ocs/count/[nid]
            // return the number of test cases 
            $node = node_load( $tc);
            print json_encode( $node->field_ts_test_data['und']);
        }
        else {
            // ajax/test/ocs/[nid]/[testcase nid]
            if ( $tc == '0')
                print ocs_run_all_testcase_for_ocs( $nid);
            else
                print ocs_run_one_testcase_for_ocs( $nid, $tc);
        }
    }
}

function ocs_run_one_testcase_for_ocs( $nid, $tc_nid)
{
    // content type test_case_ocs
    $node = node_load( $nid);

    $url = 'http://' . $node->field_ts_host['und'][0]['value'] . $node->field_ts_api['und'][0]['value']; 

    $ts_data = node_load( $tc_nid);
    $field = &drupal_static( __FUNCTION__ . $ts_data->type);;
    if ( empty($field)) {
        $field = field_info_instances( 'node', $ts_data->type);
    }

    $output = ocs_run_testcase_http( $url, $ts_data, $field);
    $output['url'] = current_path();
    $output['nid'] = $nid;
    $output['tc_nid'] = $tc_nid;

    return json_encode($output);
}


function ocs_run_all_testcase_for_ocs( $nid)
{
    // content type test_case_ocs
    $node = node_load( $nid);

    $url = 'http://' . $node->field_ts_host['und'][0]['value'] . $node->field_ts_api['und'][0]['value']; 

    $output = array();
    $field = NULL;
    // get test data
    foreach( $node->field_ts_test_data['und'] as $key => $value) {
        $ts_data = node_load( $value);
        if ( $field == NULL) $field = field_info_instances( 'node', $ts_data->type);

        $output[] = ocs_run_testcase_http( $url, $ts_data, $field);
    }

    return json_encode($output);
}


function ocs_run_testcase_http( $url, $ts_data, $field)
{
    $data = ocs_build_ts_json( $ts_data, $field);

    $pattern = '/\[(\w+)\]/';
    while ( preg_match( $pattern, $url, $match)) {
        // $match[0] == matched string, find in the value array
        $key = substr( $match[0], 1, -1);
        if ( array_key_exists( $key, $data)) {
            // replace one the variable pattern found
            $url = preg_replace( $pattern, $data[$key], $url, 1); 
        }

    }

    /*
    $response = http_parse_message( http_post_data( $url, ocs_json_encode($data), array("timeout"=>1), $info));

    $output = array(
        'effective_url' => $info['effective_url'],
        'response' => $response->body,
        'response_code' => $info['response_code'],
        'total_time' => $info['total_time']);

    */
	$body = json_encode( array( 'subscriptoin' => array( $data))); 
    $response = drupal_http_request( $url, array( 
				'method' => 'POST',
				'data' => $body,
				'timeout'=>1));

	dpm( 'http body:' . $body);

    $output = array( 'response' => $response);

    // build output
    return $output;
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

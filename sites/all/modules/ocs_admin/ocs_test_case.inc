<?php

function ocs_admin_run_api( $param1, $param2)
{
    print '{"result":"success"}';
}


function ocs_admin_run_testcase( $type, $test_suite, $tc_nid, $tc_idx)
{
    if ( $type == 'ocs') {
		// ajax/test/ocs/[testsuite nid]/[testcase nid]/[testcase idx]
		print ocs_run_all_testcase_for_ocs( $test_suite, $tc_nid, $tc_idx);
    }
}

/*	not used anymore
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

    $output = ocs_run_testcase_http( $url, $ts_data, $field, $node->field_ts_method['und'][0]['value'],
			$node->field_ts_json_prefix['und'][0]['value'], $node->field_ts_json_suffix['und'][0]['value']);
    $output['url'] = current_path();
    $output['nid'] = $nid;
    $output['tc_nid'] = $tc_nid;

    return json_encode($output);
}
*/


function ocs_run_all_testcase_for_ocs( $ts_nid, $tc_nid, $tc_idx)
{
	$tc_idx = (int)$tc_idx;

	// load test suite
	$ts = node_load( $ts_nid);
	$host = $ts->field_ts_host['und'][0]['value'];
	if ( substr( $host, -1) != '/') $host .= '/';

	$data_to_replace = isset($ts->field_ts_test_suite_data['und']) ? $ts->field_ts_test_suite_data['und'][0]['value'] : NULL;
	$json_data = json_decode( $data_to_replace, TRUE);
	/*
	if ( !empty($data_to_replace) && empty( $json_data)) {
		drupal_set_message('Invalid json format in Test Suite Data', 'error');
	}
	*/

    // content type test_case_ocs
    $tc = node_load( $tc_nid);

	//dpm( $tc, 'test');

    $url = 'http://' . $host . $tc->field_ts_api['und'][0]['value']; 

    $field = NULL;
	$output = NULL;
	$test_result = array();
    // get test data
    if( isset( $tc->field_ts_test_data['und'][$tc_idx])) {
        $ts_data = node_load( $tc->field_ts_test_data['und'][$tc_idx]['nid']);
		if ( $ts_data->type == 'test_result_online_charging' || $ts_data->type == 'test_result_sms_charging') {
			$test_result = ocs_build_ts_json( $ts_data, field_info_instances( 'node', $ts_data->type));
			//dpm( $test_result, 'test result');

			// for test_result_online_charging type, read test data again
			$ts_data = node_load( $ts_data->field_ts_test_case['und'][0]['nid']);
		}

        if ( $field == NULL) $field = field_info_instances( 'node', $ts_data->type);

        $output = ocs_run_testcase_http( $url, $ts_data, $field, $tc->field_ts_method['und'][0]['value'],
				$tc->field_ts_json_prefix['und'][0]['value'], $tc->field_ts_json_suffix['und'][0]['value'], $json_data);
    }
	else if ( isset( $tc->field_ts_call_test['und'][$tc_idx])) {
		// get template
		$ts_data = node_load( $tc->field_ts_call_test_template['und'][0]['nid']);
        if ( $field == NULL) $field = field_info_instances( 'node', $ts_data->type);

		$cdata = entity_load_single( 'field_collection_item', $tc->field_ts_call_test['und'][$tc_idx]['value']);
		$test_result = ocs_build_ts_json( $cdata, field_info_instances('field_collection_item', 'field_ts_call_test'));

		// refine call_data
		$test_result['destId'] = $test_result['dialed'];	// add another key : destId as same as dialed
		// recalculate end time
		$stime = new DateTime( $test_result['startTime']);
		$etime = $stime->add( new DateInterval('PT'. $test_result['duration'] .'S'));
		$test_result['endTime'] = $etime->format('YmdHis');

        $output = ocs_run_testcase_http( $url, $ts_data, $field, $tc->field_ts_method['und'][0]['value'],
				$tc->field_ts_json_prefix['und'][0]['value'], $tc->field_ts_json_suffix['und'][0]['value'], 
				array_merge( $json_data, $test_result));
	}
	else {
		$output = array( 'error' => 'TC-'. $tc_idx . ' Not found');
	}

	//dpm( json_encode($output), 'result');

    return json_encode( array_merge( $output, array( 'tc' => $tc_idx, 'test_result' => json_encode($test_result))));
}


function ocs_run_testcase_http( $url, $ts_data, $field, $method = 'POST', $prefix='', $suffix='', $replace_data=array())
{
	// dpm( $replace_data, 'replace data');

	$data = ocs_build_ts_json( $ts_data, $field, $replace_data);

    $pattern = '/\[(\w+)\]/';
    while ( preg_match( $pattern, $url, $match)) {
        // $match[0] == matched string, find in the value array
        $key = substr( $match[0], 1, -1);

		// replace one the variable pattern found
        if ( array_key_exists( $key, $replace_data)) {
            $url = preg_replace( $pattern, $replace_data[$key], $url, 1); 
		}
		else if ( array_key_exists( $key, $data)) {
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
	$body = ($method == 'POST') ? $prefix . json_encode( $data) . $suffix : NULL; 
    $response = drupal_http_request( $url, array( 
				'method' => $method,
				'data' => $body,
				'headers' => array('Content-Type' => 'application/json', 'Accept' => 'application/json'),
				'timeout'=>1));

	//dpm( 'http body:' . $body);
	//dpm( $response, 'response');

    $output = array( 'response' => $response, 'test_data' => json_encode( $data));

    // build output
    return $output;
}


function ocs_build_ts_json( $node, $field=NULL, $replace_data=NULL)
{
    if ( $field == NULL) {
        $field = field_info_instances( 'node', $node->type);
    }

	$obj = array();
	foreach( $field as $key => $value) {
		$v = $node->$key;
		$label = $value['label'];

		if ( array_key_exists( $label, $replace_data)) {
			$va = $replace_data[$label];
		}
		else if ( is_array( $v)) {
			if ( empty($v)) {
				$va = null;
			}
			else {
				if ( $value['widget']['module'] == 'field_collection') {
					$field_node = entity_load_single( 'field_collection_item', $v['und'][0]['value']);
					$va = ocs_build_ts_json( $field_node, field_info_instances('field_collection_item', $value['field_name']), $replace_data);
				}
				else if ( $value['widget']['module'] == 'number') {
					$va = intval( $v['und'][0]['value']);
				}
				else if ( isset( $v['und'][0]['date_type']) && $v['und'][0]['date_type'] == 'datetime') {
					$date = new DateTime( $v['und'][0]['value']);
					$va = $date->format( 'YmdHis');
				}
				else {
					$va = $v['und'][0]['value'];
				}
			}
		}
		else {
			$va = $v;
		}

		$obj[ $label] = $va;
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

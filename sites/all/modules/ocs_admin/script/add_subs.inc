#!/usr/bin/env drush                      
<?php

$case = array(
		array( '428880300001696', '100000136020', '97688000011'),
		array( '428880300001697', '100000136021', '97688000012'),
		array( '428880300001698', '100000136022', '97688000005'),
		array( '428880300001699', '100000136023', '97688000006'),
		array( '428880300001700', '100000136024', '97688000007'),
		array( '428880300001701', '100000136025', '97688000008'),
		array( '428880300001702', '100000136026', '97688000009'),
		array( '428880300001694', '100000136018', '97688003002'),
		array( '428880300001695', '100000136019', '97688003004'),
		array( '428880300001693', '100000136017', '97688003000'),
		array( '428880300001690', '100000136013', '97687003000'),
		array( '428880300001691', '100000136014', '97688003001'),
		array( '428880300001692', '100000136015', '97688003003'),
		);

$nl = '
';

$test = array( 13500, 13499, 54379, 54421, 60015, 54372);

$user = array(
		"subscription_key" => "428880111011135", 
		"user_key" => "97688788899", 
		"product_id" => "fce_prepaid_A", 
		"origId" => "97688788899", 
		"accountId" => "97688788899" 
		);

foreach( $case as $t) {
	$user['subscription_key'] = $t[0];
	$user['accountId'] = $user['origId'] = $user['user_key'] = $t[2];
	$user['entr_no'] = $t[1];

	foreach( $test as $nid) {
		$tc = node_load( $nid);

		// subscribe
		$template = node_load( $tc->field_ts_test_data['und'][0]['nid']);

		$output = ocs_run_testcase_http( 
				'http://10.21.8.70:8085/'. $tc->field_ts_api['und'][0]['value'],
				$template, NULL, $tc->field_ts_method['und'][0]['value'], 
				$tc->field_ts_json_prefix['und'][0]['value'],
				$tc->field_ts_json_suffix['und'][0]['value'], $user);

		$response = $output['response'];
		$result = json_decode( $response->data);
		if ( $result->result_code != '0') {
			print $tc->title . ' : FAIL' . $nl;
			print_r( $output);
		}
		else {
			print $tc->title . ' : SUCCESS' . $nl;
//			print_r( $output);
		}
	}
}


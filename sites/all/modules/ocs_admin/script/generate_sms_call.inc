#!/usr/bin/env drush                      
<?php

$case = array(
array('   4. MOBICOM','97688778899','976991111','Voice','2013-01-05 15:00','60','60'),
array('   5. MOBI_WLL','97688778899','97695111111','Voice','2013-01-05 15:00','60','60'),
array('   6. SKYTEL','97688778899','97691141111','Voice','2013-01-05 15:00','60','60'),
array('   7. SKY_WLL','97688778899','97696111111','Voice','2013-01-05 15:00','60','60'),
array('  13. UNITEL','97688778899','97688909693','Voice','2013-01-05 15:00','60','0'),
array('  14. UNITEL_VOIP','97688778899','97689111111','Voice','2013-01-05 15:00','60','0'),
array('  15. UNITEL_new','97688778899','97686111111','Voice','2013-01-05 15:00','60','0'),
array('  16. MTC_INT','97688778899','001821097971731','Voice','2013-01-05 15:00','60','594'),
array('  17. SKY_INT','97688778899','002821097971731','Voice','2013-01-05 15:00','60','568'),
array('  18. MOBI_INT','97688778899','003821097971731','Voice','2013-01-05 15:00','60','450'),
array('  31. RAY_INT','97688778899','005821097971731','Voice','2013-01-05 15:00','60','565'),
array('  36. G-Mobile','97688778899','97698111111','Voice','2013-01-05 15:00','60','60'),
array('  43. G_Mobile','97688778899','97693111111','Voice','2013-01-05 15:00','60','60'),
array('  60. UNI_INT','97688778899','008821097971731','Voice','2013-01-05 15:00','60','605'),
array('  73. MOBI_NEW','97688778899','97694111808','Voice','2013-01-05 15:00','60','60'),
array('  76. G_Mobile_97','97688778899','97697151808','Voice','2013-01-05 15:00','60','60'),
array('  89. UNITEL TIMEID2 22~24','97688778899','97688909693','Voice','2013-01-07 5:00','60','0'),
array('  90. UNITEL TIMEID2 HOLIDAY 22~24','97688778899','97688909693','Voice','2013-01-07 5:00','60','0'),
array('  91. UNITEL_VOIP TIMEID2 22~24','97688778899','97689111111','Voice','2013-01-07 5:00','60','0'),
array('  92. UNITEL_VOIP TIMEID2 HOLIDAY 22~24','97688778899','97689111111','Voice','2013-01-07 5:00','60','0'),
array('  93. UNITEL_new TIMEID2 22~24','97688778899','97686111111','Voice','2013-01-07 5:00','60','0'),
array('  94. UNITEL_new TIMEID2 HOLIDAY 22~24','97688778899','97686111111','Voice','2013-01-07 5:00','60','0'),
array('  95. MTC_INT TIMEID2 20~24','97688778899','001821097971731','Voice','2013-01-07 5:00','60','528'),
array('  96. RAY_INT TIMEID2 20~24','97688778899','005821097971731','Voice','2013-01-07 5:00','60','510'),
array('  97. SKY_INT TIMEID2 00~06','97688778899','002821097971731','Voice','2013-01-07 5:00','60','488'),
array('  98. MOBI_INT TIMEID2 00~09','97688778899','003821097971731','Voice','2013-01-07 5:00','60','360'),
array('  99. UNI_INT TIMEID2 00~09','97688778899','008821097971731','Voice','2013-01-07 5:00','60','495'),
		);

$subs = array(
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

$user = array(
		"subscription_key" => "428880111011135", 
		"user_key" => "97688788899", 
		"product_id" => "fce_prepaid_A", 
		"origId" => "97688788899", 
		"accountId" => "97688788899" 
		);


foreach( $subs as $s) {
	$user['subscription_key'] = $s[0];
	$user['user_key'] = $user['origId'] = $user['accountId'] = $s[2];

	// first recharge
	recharge( $user);

	foreach( $case as $tc) {
		$node = _get_node_by_title( $tc[0]);

		$stime = new DateTime();
		$node->field_ts_starttime['und'][0]['value'] = $stime->format('YmdHis');
		$duration = rand( 3, 300);
		$etime = $stime->add( new DateInterval('PT'.$duration.'S'));
		$node->field_ts_endtime['und'][0]['value'] = $etime->format('YmdHis');

		$output = ocs_run_testcase_http( 'http://10.21.8.70:8085/ocs/subscriber/' . $user['user_key'] . '/directdebit', $node, NULL, 'POST', '', '', $user);
		$response = $output['response'];
		$result = json_decode( $response->data);
		if ( $result->result_code != '0') {
			print $tc[0] . ' : FAIL' . $nl;
			print_r( $output);
			if ( $result->result_reason == 'NOT_ENOUGH_BALANCE') {
				recharge( $user);
			}
		}
		else {
			print $tc[0] . ' : SUCCESS' . $nl;
		}
	}
}

function recharge( $user)
{
	$nl = '
';
	$test_case = array( 60015, 54372);
	foreach( $test_case as $nid) {

		/*
		$recharge_template = node_load( 60016);
		$recharge_template->field_recharge_type['und'][0]['value'] = 3;

		$output = ocs_run_testcase_http( 'http://10.21.8.70:8085/ocs/subscriber/' . $user['subscription_key'] . '/recharge', 
				$recharge_template, NULL, 'POST', '{"recharge":', '}', $user);
				*/
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
		}
	}
}


// return array of nodes
function _get_node_by_title( $title)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'test_case_sms_charging')
		->propertyCondition('title', $title)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

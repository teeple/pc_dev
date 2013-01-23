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

$nl = '
';

foreach( $case as $tc) {
	$node = _get_node_by_title( $tc[0]);
	if ( empty( $node)) {
		$node = ocs_admin_get_new_node('test_case_sms_charging');
		print 'New node '.$nl;
		$node->title = $tc[0];
	}
	else {
		print 'Existing node '. $node->title.$nl;
	}

	$node->field_ts_accountid['und'][0]['value'] = $tc[1];
	$node->field_ts_origid['und'][0]['value'] = $tc[1];
	$node->field_ts_destid['und'][0]['value'] = $tc[2];
	$node->field_ts_unit['und'][0]['value'] = 1;
	$node->field_ts_default_charge['und'][0]['value'] = $tc[6];
	$node->field_ts_serviceid['und'][0]['value'] = 201;

	$stime = new DateTime( $tc[4]);
	$node->field_ts_starttime['und'][0]['value'] = $stime->format('YmdHis');
	print_r( $stime);
	$etime = $stime->add( new DateInterval('PT'.$tc[5].'S'));
	print_r( $etime);
	$node->field_ts_endtime['und'][0]['value'] = $etime->format('YmdHis');

	/* sms service info */
	if ( empty($node->field_ts_smsserviceinfo)) {
		$vs = entity_create('field_collection_item', array('field_name' => 'field_ts_smsserviceinfo'));
		$vs->setHostEntity( 'node', $node);
	}
	else {
		$vs = entity_load_single( 'field_collection_item', $node->field_ts_smsserviceinfo['und'][0]['value']);
	}

	$vs->field_ts_isroaming['und'][0]['value'] = 0;
	$vs->field_ts_sccpaddr['und'][0]['value'] = "";
	$vs->field_ts_msgtype['und'][0]['value'] = 12;
	$vs->save();

	node_save( $node);
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

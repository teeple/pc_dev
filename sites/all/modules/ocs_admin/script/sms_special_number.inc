<?php

$sp_list = _get_sms_special();
$nl = '
';

// get special number plan
foreach( $sp_list as $category => $child) {
	// get special number plan for this category
	$splan = _get_node_by_title( 'number_special', 'FCE_SMS_SP_' . $category);
	if ( empty( $splan)) {
		$splan = ocs_admin_get_new_node( 'number_special');
		$splan->title = 'FCE_SMS_SP_' . $category;

		print 'New number special : ' . $splan->title . $nl;
	}
	else {
		print 'Existing number special : ' . $splan->title . $nl;
	}
	$splan->field_target_usage_type['und'][0]['tid'] = 4636;
	node_save( $splan);

	foreach( $child as $rating => $list) {
		foreach( $list as $value) {
			$factor = _get_node_by_title( 'numberspecialfactors', $splan->title . ':' . $value['ruleName'] . ':' . $rating);
			if ( empty( $factor)) {
				$factor = ocs_admin_get_new_node( 'numberspecialfactors');
				$factor->title = $splan->title . ':' . $value['ruleName'] . ':' . $rating;

				print 'New factor : ' . $factor->title . $nl;
			}
			else {
				print 'Existing factor : ' . $factor->title . $nl;
			}

			$factor->field_ref_numberspecial['und'][0]['nid'] = $splan->nid;
			$factor->field_rating_group['und'][0]['value'] = $rating;
			$factor->field_ref_type_of_call['und'][0]['tid'] = 1516;	// outgoing sms
			$factor->field_prefix['und'][0]['value'] = $value['called'];	// outgoing sms

			node_save( $factor);
		}

		// add rate
		$rate = _get_node_by_title( 'numberspecialrate', $splan->title . ':' . $rating);
		if ( empty( $rate)) {
			$rate = ocs_admin_get_new_node( 'numberspecialrate');
			$rate->title = $splan->title . ':' . $rating;

			print 'New Rate : ' . $rate->title . $nl;
		}
		else {
			print 'Existing Rate : ' . $rate->title . $nl;
		}

		$rate->field_ref_numberspecial['und'][0]['nid'] = $splan->nid;
		$rate->field_tree_tid['und'][0]['value'] = 1873;
		$rate->field_connection_fee['und'][0]['value'] = $rating;
		$rate->field_rating_group['und'][0]['value'] = $rating;

		node_save( $rate);
	}
}


function _get_sms_special()
{
	db_set_active('fce');

	$fields = array(
		'ruleName', 'called', 'user_category', 'sms_special_price'
	);
	$table = 'sms_special_number';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
        ->orderBy( 'user_category')
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		if ( $record['user_category']) {
			$records[ $record['user_category']][$record['sms_special_price']][] = $record;
		}
		else {
			$records[ 'All'][$record['sms_special_price']][] = $record;
		}
	}

	db_set_active('default');

	return $records;
}

// return array of nodes
function _get_node_by_title( $bundle, $title)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $bundle)
		->propertyCondition('title', $title)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

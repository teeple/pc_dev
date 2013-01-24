<?php

$country_list = _get_country_list();

$roam_list = _get_roaming_country();
//print_r( $roam_list);
$nl = '
';

// get special number plan
foreach( $roam_list as $rm) {
	// get special number plan for this category
	$country = $country_list[ $rm['roaming_country']]['country_name'];
	$splan = _get_node_by_title( 'roaming_country', $country);
	if ( empty( $splan)) {
		$splan = ocs_admin_get_new_node( 'roaming_country');
		$splan->title = $country;

		print 'New roaming country : ' . $splan->title . $nl;

		$splan->field_prefix_multiple['und'][0]['value'] = $rm['called'];
		$splan->field_exit_code['und'][0]['value'] = $rm['ruleName'];
	}
	else {
		print 'Existing roaming country : ' . $splan->title . $nl;

		/*
		unset( $splan->field_prefix_multiple['und']);
		unset( $splan->field_exit_code['und']);
		*/
		//print_r( array_get_value( $splan->field_prefix_multiple, FALSE));
		if ( ! array_search( $rm['called'], array_get_value( $splan->field_prefix_multiple, FALSE))) {
			$splan->field_prefix_multiple['und'][] = array( 'value' => $rm['called']);
			$splan->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
			print 'Add additional prefix : ' . $rm['called'] . $nl;
		}
	}
	$splan->field_country_code['und'][0]['value'] = $rm['roaming_country'];

	node_save( $splan);
}

function _get_country_list()
{
	db_set_active('fce');

	$fields = array(
		'ruleName', 'country_prefix', 'country_name', 'time_zone'
	);
	$table = 'intl_country_code';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[$record['ruleName']] = $record;
	}

	db_set_active('default');

	return $records;
}

function _get_roaming_country()
{
	db_set_active('fce');

	$fields = array(
		'ruleName', 'called', 'roaming_country'
	);
	$table = 'roaming_exit_code';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[] = $record;
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

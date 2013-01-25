<?php

$country_list = _get_country_list();

$roam_list = _get_roaming_country();
$carrier_list = _get_roaming_carrier();
print_r( $carrier_list);
$nl = '
';

// get special number plan
foreach( $carrier_list as $country_code => $r) {
	// get special number plan for this category
	$country = $country_list[$country_code]['country_name'];
	$rm_country = _get_node_by_title( 'roaming_country', $country);
	if ( empty( $rm_country)) {
		print 'ERROR : Roaming country not found : ' . $country . $nl;
		continue;
	}


	foreach( $r as $carrier => $v) {

		$c = _get_node_by_title( 'roaming_carrier', $carrier);
		if ( empty( $c)) {
			$c = ocs_admin_get_new_node( 'roaming_carrier');
			$c->title = $carrier;

			print 'New roaming carrier : ' . $c->title . $nl;
		}
		else {
			print 'Existing roaming carrier : ' . $c->title . $nl;
		}

		$c->field_ref_roaming_country['und'][0]['nid'] = $rm_country->nid;

		unset( $c->field_prefix_multiple['und']);
		foreach( $v as $rec) {
			$c->field_prefix_multiple['und'][] = array( 'value' => $rec['NPA_prefix']);
		}

		node_save( $c);
	}
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

function _get_roaming_carrier()
{
	db_set_active('fce');

	$fields = array(
			'ruleName', 'roaming_country', 'NPA_prefix', 'regionFlag'
	);
	$table = 'intl_call_type';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[$record['roaming_country']][$record['ruleName']][] = $record;
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

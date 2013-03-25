<?php

$reset_prefix = FALSE;

while ($arg = drush_shift()) {
	if ( $arg == 'reset') $reset_prefix = TRUE;
}

$country_list = _get_country_list();
print_r( $country_list);

$nl = '
';

foreach( $country_list as $key => $country) {
	// get special number plan for this category
	$rm = _get_roaming_country( $key);
	if ( empty( $rm)) {
		$rm = ocs_admin_get_new_node( 'roaming_country');
		$rm->title = $country['COUNTRY_NAME'];

		print 'New roaming country : ' . $rm->title . $nl;

		$rm->field_prefix_multiple['und'][0]['value'] = $country['INTL_PREFIX'];
		$rm->field_exit_code['und'][0]['value'] = '';
	}
	else {
		print 'Existing roaming country : ' . $rm->title . $nl;

		if ( $reset_prefix) {
			unset( $rm->field_prefix_multiple['und']);
			unset( $rm->field_exit_code['und']);
		}

		//print_r( array_get_value( $splan->field_prefix_multiple, FALSE));
		if ( ! array_search( $country['INTL_PREFIX'], array_get_value( $rm->field_prefix_multiple, FALSE))) {
			$rm->field_prefix_multiple['und'][] = array( 'value' => implode( '', explode(' ',$country['INTL_PREFIX'])));
//			$rm->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
			print 'Add additional prefix : ' . $country['INTL_PREFIX'] . $nl;
		}
	}
	$rm->field_country_code['und'][0]['value'] = $country['ISO_COUNTRY_CD'];
	$rm->field_country_code_3['und'][0]['value'] = $country['COUNTRY_CD'];

	node_save( $rm);
}

function _get_country_list()
{
	db_set_active('csdb');

	$fields = array(
			'COUNTRY_CD', 'ISO_COUNTRY_CD', 'COUNTRY_NAME', 'INTL_PREFIX',
	);
	$table = 'roaming_country';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[$record['ISO_COUNTRY_CD']] = $record;
	}

	db_set_active('default');

	return $records;
}

// return array of nodes
function _get_roaming_country( $country_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_country')
		->fieldCondition('field_country_code', 'value', $country_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

<?php

$reset_prefix = FALSE;
$print_json = FALSE;

while ($arg = drush_shift()) {
	if ( $arg == 'reset') $reset_prefix = TRUE;
	if ( $arg == 'json') $print_json = TRUE;
}

$partner_list = _get_partner_list();
if ( $print_json) {
	print json_encode( $partner_list);
	return;
}

print_r( $partner_list);

$nl = '
';

foreach( $partner_list as $key => $partner) {
	// get special number plan for this category
	$rm = _get_roaming_partner( $key);
	if ( empty( $rm)) {
		$rm = ocs_admin_get_new_node( 'roaming_carrier');

		print 'New roaming partner : ' . $rm->title . $nl;

		//$rm->field_prefix_multiple['und'][0]['value'] = $partner['INTL_PREFIX'];
	}
	else {
		print 'Existing roaming partner : ' . $rm->title . $nl;

		if ( $reset_prefix) {
			unset( $rm->field_prefix_multiple['und']);
		}

		//print_r( array_get_value( $splan->field_prefix_multiple, FALSE));
		/*
		if ( ! array_search( $partner['INTL_PREFIX'], array_get_value( $rm->field_prefix_multiple, FALSE))) {
			$rm->field_prefix_multiple['und'][] = array( 'value' => implode( '', explode(' ',$partner['INTL_PREFIX'])));
//			$rm->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
			print 'Add additional prefix : ' . $partner['INTL_PREFIX'] . $nl;
		}
		*/
	}
	$rm->title = str_replace( '"', '', $partner['COMPANY_NAME']);
	$rm->field_partner_code['und'][0]['value'] = $partner['PARTNER_ID'];
	$rm->field_description['und'][0]['value'] = $partner['DESC'];
	$rm->field_ref_roaming_country['und'][0]['nid'] = _get_country_nid( $partner['NATIONAL_CD']);

	node_save( $rm);
}

function _get_partner_list()
{
	db_set_active('csdb');

	$fields = array(
			'PARTNER_ID', 'PRM_KD_CD', 'PRM_KD_DTL_CD', 'PRM_STATE_CD', 'COMPANY_NAME', 'COMPANY_SHORT_NAME', 'NATIONAL_CD', 'URL', 'OFFICE_TEL_NO', 'FAX_NO', 
			'ADDRESS', 'CONTRACTOR', 'E_MAIL', 'STAFF', 'DESCR', 'REG_DATE'
	);
	$table = 'roaming_partner';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[$record['PARTNER_ID']] = $record;
	}

	db_set_active('default');

	return $records;
}

function _get_country_nid( $country_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_country')
		->fieldCondition('field_country_code_3', 'value', $country_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		return $nids[0];
	}

	return NULL;
}

// return array of nodes
function _get_roaming_partner( $partner_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_carrier')
		->fieldCondition('field_partner_code', 'value', $partner_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

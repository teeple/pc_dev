<?php

$reset_prefix = FALSE;
$plan = NULL;

while ($arg = drush_shift()) {
	if ( $arg == 'reset') $reset_prefix = TRUE;
	if ( $arg == 'plan') $plan = drush_shift();
}

$rate_list = _get_roaming_rate_list();
print_r( $rate_list);

$nl = '
';

if ( $plan == NULL) {
	print 'Invalid Plan'. $nl;
	return;
}

foreach( $rate_list as $key => $rate) {
	$plmn = '';
	if ( strstr( $key, 'HPMN')) {
		print "Home PLMN: ";
		$plmn = 'HPLMN';
	}
	else if ( strstr( $key, 'VPMN')) {
		print "Visit PLMN: ";
		$plmn = 'VPLMN';
	}
	else if ( strstr( $key, 'Cus')) {
		print "Other PLMN: ";
		$plmn = 'OtherPLMN';
	}
	else {
		continue;
	}

	// get special number plan for this category
	$rm = _get_roaming_rate( $key);
	if ( empty( $rm)) {
		$rm = ocs_admin_get_new_node( 'roaming_ratinggroup');

		$rm->title = 'roaming_rg:TR::' . $plmn;
		$rm->field_rating_group['und'][0]['value'] = $key;
		print 'New roaming rate : ' . $key . $nl;

		//$rm->field_prefix_multiple['und'][0]['value'] = $rate['INTL_PREFIX'];
	}
	else {
		print 'Existing roaming rate : ' . $key . $nl;

		//print_r( array_get_value( $splan->field_prefix_multiple, FALSE));
		/*
		if ( ! array_search( $rate['INTL_PREFIX'], array_get_value( $rm->field_prefix_multiple, FALSE))) {
			$rm->field_prefix_multiple['und'][] = array( 'value' => implode( '', explode(' ',$rate['INTL_PREFIX'])));
//			$rm->field_exit_code['und'][] = array( 'value' => $rm['ruleName']);
			print 'Add additional prefix : ' . $rate['INTL_PREFIX'] . $nl;
		}
		*/
	}
	$partner = _get_roaming_partner( $key);
	$rm->field_ref_roaming_country['und'][0]['nid'] = $partner->field_ref_roaming_country['und'][0]['nid'];
	$rm->field_ref_roaming_carrier['und'][0]['nid'] = $partner->nid;
	/*
	$rm->field_ref_roaming_type['und'][0]['nid'] = _get_country_nid( $rate['NATIONAL_CD']);
	$rm->field_ref_roaming_plan['und'][0]['nid'] = _get_country_nid( $rate['NATIONAL_CD']);
	$rm->field_ref_type_of_call['und'][0]['nid'] = _get_country_nid( $rate['NATIONAL_CD']);
	*/

	node_save( $rm);
}

function _get_roaming_rate_list()
{
	db_set_active('csdb');

	$fields = array(
			 'INVENTORY_ITEM_ID', 'VALD_STRT_DT', 'PROD_CD', 'FTR_CD', 'RATE_DV_CD', 'IOCLL_DV_CD', 'CALLING_ZONE_CD', 'CALLED_ZONE_CD', 'RATE_APLY_LVL_CD', 'RATE_APLY_DV_CD', 
			 'UAGE_APPLY_DV_CD', 'RATE_APLY_TIMEBAND_CD', 'RATE_APLY_INTERVAL_CD', 'RATE_APLY_CYCL_DV_CD', 'RATE_APLY_KD_CD', 'RATE_APLY_UNIT_CD', 'RATE_APLY_UNIT', 'RATE', 
			 'SPND_RATE', 'INIT_RATE_CYCLE_DURATION', 'INIT_RATE_APLY_UNIT_CD', 'INIT_RATE_APLY_UNIT', 'INIT_RATE', 'VALD_END_DT', 'RATE_DACAL_DV_CD', 'RATE_DTL_DV_CD'
	);
	$table = 'roaming_rate';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	while( $record = $result->fetchAssoc()) {
		$records[$record['PROD_CD']][] = $record;
	}

	/*
	$records = array();
	$result = db_query( 'select * from roaming_rate where prod_cd like :prod', array( ':prod' => '%Customer%'));
	while( $record = $result->fetchAssoc()) {
		$records[$record['PROD_CD']] = $record;
	}
		*/

	db_set_active('default');

	return $records;
}

function _get_roaming_partner( $prod_code)
{
	$str = explode( '_', $prod_code);

	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_carrier')
		->fieldCondition('field_partner_code', 'value', $str[0])
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

// return array of nodes
function _get_roaming_rate( $rate_code)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_ratinggroup')
		->fieldCondition('field_rating_group', 'value', $rate_code)
		->execute();

	if ( count( $result) > 0) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

<?php

$reset_flag = FALSE;
$plan_name = NULL;
$product_name = NULL;
$tariff_name = NULL;

// check arguments
while ($arg = drush_shift()) {
	if ( $arg == 'reset') $reset_flag = TRUE;
	if ( $arg == 'product') $product_name = drush_shift();
	if ( $arg == 'tariff') $tariff_name = drush_shift();
}

if ( $plan_name == NULL || $product_name == NULL || $tariff_name ) {
	print 'Invalid Format'. $nl;
	print 'Usage: <command> [reset] product <product name> tariff <tariff name>'. $nl;
	return;
}

/* get product node */
$nids = ocs_get_nodes_by_title( 'simpleproductoffering', $product_name);
if ( count( $nids) != 1) {
	print 'Invalid product '. $product_name;
	print_r( $nids);
	return;
}

$product = node_load( $nids[0]);

/* get tariff node */
$nids = ocs_get_nodes_by_title( 'tariffplan', $tariff_name);
if ( count( $nids) != 1) {
	print 'Invalid tariff '. $tariff_name;
	print_r( $nids);
	return;
}

$tariff = node_load( $nids[0]);

/* get roaming plan node */
$nid = $tariff->field_ref_roaming_plan['und'][0]['nid'];
$plan = node_load( $nid);


/* read rate list from DB */
$rate_list = _get_roaming_rate_list();
print_r( $rate_list);

/* get terms */
$terms = ocs_get_terms('roaming_type');
$roaming_type = array();
foreach( $terms as $tid => $term) {
	$roaming_type[$term->name] = $tid;
}

/* get terms: calltype */
$terms = ocs_get_terms('calltype');
$call_type = array();
foreach( $terms as $tid => $term) {
	$call_type[$term->name] = $tid;
}

// get terms : unit_of_measure 
$terms = ocs_get_terms('unit_of_measure');
$unit_measure = array();
foreach( $terms as $tid => $term) {
	$unit_measure[$term->name] = $tid;
}

// get terms : unif_of_range
$terms = ocs_get_terms('unit_of_range');
$unit_range = array();
foreach( $terms as $tid => $term) {
	$unit_range[$term->name] = $tid;
}



$nl = '
';

if ( $reset_flag ) {
	unset( $plan->field_ref_roaming_ratinggroup['und']);
}

foreach( $rate_list as $key => $rate) {
	$plmn = '';
	if ( strstr( $key, 'HPMN')) {
		print "Home PLMN: ";
		$plmn = 'HPLMN';
		$calltype = 'ROAMING_HOME_CALL';
	}
	else if ( strstr( $key, 'VPMN')) {
		print "Visit PLMN: ";
		$plmn = 'VPLMN';
		$calltype = 'ROAMING_CALL_TO_NATIONAL';
	}
	else if ( strstr( $key, 'Cus')) {
		print "Other PLMN: ";
		$plmn = 'Other PLMN';
		$calltype = 'ROAMING_OTHER_COUNTRY';
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
	$rm->field_ref_roaming_plan['und'][0]['nid'] = $plan->nid;

	if ( ! array_search( $rm->nid, array_get_value( $plan->field_ref_roaming_ratinggroup, FALSE))) {
		$plan->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $rm->nid);
	}
	$rm->field_ref_roaming_type['und'][0]['tid'] = $roaming_type[$plmn];
	$rm->field_ref_type_of_call['und'][0]['tid'] = $call_type[$calltype];

	node_save( $rm);

	// add tariff
	$rate_title = $tariff_name . '_' . $key;
	$nids = ocs_get_nodes_by_title( 'rate', $rate_title);
	if ( empty( $nids)) {
		$rate = ocs_admin_get_new_node( 'rate');
		$rate->title = $rate_title;
	}
	else {
		$rate = node_load( $nids[0]);
	}

	$rate->field_range_units['und'][0]['tid'] = $unit_range['Seconds'];
	$rate->field_uom_units['und'][0]['tid'] = $unit_measure['Seconds'];
	$rate->ref_tariffplan['und'][0]['nid'] = $tariff->nid;
	$rate->ref_tree_tid['und'][0]['nid'] = $tariff->nid;

	node_save( $rate);
}
node_save( $plan);

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


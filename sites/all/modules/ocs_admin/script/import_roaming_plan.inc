<?php

define( 'RoamingHCC', 1031);
define( 'RoamingIVC', 1032);
define( 'RoamingLVC', 1033);

define( 'RoamingSMS', 1036);
define( 'RoamingRSMS', 1037);
define( 'RoamingGPRS', 1038);


$nl = '
';

$reset_flag = FALSE;
$product_name = NULL;
$tariff_name = NULL;
$sms_tariff_name = NULL;

// check arguments
while ($arg = drush_shift()) {
	if ( $arg == 'reset') $reset_flag = TRUE;
	if ( $arg == 'product') $product_name = drush_shift();
	if ( $arg == 'tariff') {
		$tariff_name = drush_shift();
		$sms_tariff_name = drush_shift();
	}
}

if ( $product_name == NULL || $tariff_name == NULL || $sms_tariff_name == NULL) {
	print 'Invalid Format'. $nl;
	print 'Usage: <command> [reset] product <product name> tariff <tariff name> <sms tariff name>'. $nl;
	return;
}

/* get product node */
$nids = ocs_get_nodes_by_title( 'simpleproductoffering', $product_name);
if ( count( $nids) != 1) {
	print 'Invalid product '. $product_name . $nl;
	print_r( $nids);
	return;
}

$product = node_load( $nids[0]);

/* get tariff node */
$tariff = _get_tariff_plan( $product->nid, $tariff_name);
if ( empty( $tariff)) {
	print 'Invalid tariff '. $tariff_name . $nl;
	return;
}

/* get roaming plan node */
$nid = $tariff->field_ref_roaming_plan['und'][0]['nid'];
$plan = node_load( $nid);

/* get SMS tariff node */
$sms_tariff = _get_tariff_plan( $product->nid, $sms_tariff_name);
if ( empty( $sms_tariff)) {
	print 'Invalid SMS tariff '. $sms_tariff_name . $nl;
	return;
}

/* get roaming plan node */
$nid = $sms_tariff->field_ref_roaming_plan['und'][0]['nid'];
$sms_plan = node_load( $nid);


/* read rate list from DB */
$rate_list = _get_roaming_rate_list();
//print_r( $rate_list);

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

// get terms : usagetargetdomain
$terms = ocs_get_terms('usagetargetdomain');
$domain = array();
foreach( $terms as $tid => $term) {
	$domain[$term->name] = $tid;
}

// get terms : tpl_tariffplan_voice
$tree_tid = array();
foreach( array( 'voice', 'sms') as $type) {
	$terms = ocs_get_terms('tpl_tariffplan_' . $type);
	foreach( $terms as $tid => $term) {
		if ( $term->name == 'Basic Rate' && $term->field_ref_usage_target_domain['und'][0]['tid'] == $domain['roaming']) {
			$tree_tid[$type] = $tid;
			break;
		}
	}
}

if ( $reset_flag ) {
	// remove all rating groups
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'roaming_ratinggroup')
		->fieldCondition('field_ref_roaming_plan', 'nid', $plan->nid)
		->execute();

	foreach( array_keys( $result['node']) as $nid) {
		print 'Remove rating group : '. $nid . $nl;
		node_delete( $nid);
	}

	unset( $plan->field_ref_roaming_ratinggroup['und']);

	// remove all rates
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'rate')
		->fieldCondition('field_ref_tariffplan', 'nid', $tariff->nid)
		->execute();

	foreach( array_keys( $result['node']) as $nid) {
		print 'Remove rate : '. $nid . $nl;
		node_delete( $nid);
	}

	// remove all rate mapping
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'basicrate_roaming')
		->fieldCondition('field_ref_tariffplan', 'nid', $tariff->nid)
		->execute();

	foreach( array_keys( $result['node']) as $nid) {
		print 'Remove rate mapping : '. $nid . $nl;
		node_delete( $nid);
	}

	return;
}

foreach( $rate_list as $key => $records) {
	if ( strstr( $key, 'Customer') == NULL) {
		continue;
	}

	// customer tariff has key with format '<Partner Name>_Customer'

	print_r( $records);

	foreach( $records as $rec) {
		$plmn = '';
		if ( $rec['IOCLL_DV_CD'] == '2') { // incoming call
			print "Incoming : ";
			$plmn = 'Incoming';
			$calltype = 'ROAMING_RECEIVE_CALL';
		}
		else {
			if ( $rec['FTR_CD'] == RoamingHCC ) {
				print "Home PLMN: ";
				$plmn = 'HPLMN';
				$calltype = 'ROAMING_HOME_CALL';
			}
			else if ( $rec['FTR_CD'] == RoamingIVC ) {
				print "Other PLMN: ";
				$plmn = 'Other PLMN';
				$calltype = 'ROAMING_OTHER_COUNTRY';
			}
			else if ( $rec['FTR_CD'] == RoamingLVC ) {
				print "Visit PLMN: ";
				$plmn = 'VPLMN';
				$calltype = 'ROAMING_CALL_TO_NATIONAL';
			}
			else if ( $rec['FTR_CD'] == RoamingRSMS ) {
				print 'Roaming Incoming SMS: ';
				$plmn = 'Incoming SMS';
				$calltype = 'ROAMING_SMS_RECEIVE';
			}
			else if ( $rec['FTR_CD'] == RoamingSMS ) {
				print 'Roaming Outgoing SMS: ';
				$plmn = 'Outgoing SMS';
				$calltype = 'ROAMING_SMS_SENT';
			}
			else if ( $rec['FTR_CD'] == RoamingGPRS ) {
				// TODO implement roaming GPRS
				print 'Roaming GPRS : Not implmented'. $nl;
				continue;
			}
			else {
				print 'Warning : invalid FTR_CD ' . $rec['FTR_CD'] . $nl;
				continue;
			}
		}

		$list = explode( '_', $key);
		$partner_code = $list[0];

		$partner = _get_roaming_partner( $partner_code);
		if ( empty( $partner)) {
			print 'Invalid Partner : ' . $key . $nl;
			continue;
		}

		// get special number plan for this category
		$rate_code = str_replace( ' ', '_', $partner_code . '_' . $plmn);
		$rm = _get_roaming_rate( $rate_code);
		if ( empty( $rm)) {
			$rm = ocs_admin_get_new_node( 'roaming_ratinggroup');

			$rm->title = 'roaming_rg:TR::' . $plmn;
			$rm->field_rating_group['und'][0]['value'] = $rate_code;
			print 'New roaming group : ' . $rate_code . $nl;
		}
		else {
			print 'Existing roaming group : ' . $rate_code . $nl;
			$rm->title = 'roaming_rg:TR::' . $plmn;
		}
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
		$rate_title = (strstr( $plmn, 'SMS') ? $sms_tariff_name : $tariff_name) . '_' . $rate_code;
		$nids = ocs_get_nodes_by_title( 'rate', $rate_title);
		if ( empty( $nids)) {
			$rate = ocs_admin_get_new_node( 'rate');
			$rate->title = $rate_title;
			print 'New roaming rate : ' . $rate_title . $nl;
		}
		else {
			print 'Existing roaming rate : ' . $rate_title . $nl;
			$rate = node_load( $nids[0]);
		}

		//print_r( $rec);

		$rate->field_range_units['und'][0]['tid'] = $unit_range['Seconds'];
		$rate->field_uom_units['und'][0]['tid'] = $unit_measure['Seconds'];
		if ( strstr( $plmn, 'SMS')) {
			$tariff_nid = $sms_tariff->nid;

			$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_nid;
			$rate->field_ref_tree_tid['und'][0]['value'] = $tree_tid['sms'];
			$rate->field_price['und'][0]['value'] = floatval($rec['RATE']);
		}
		else {
			$tariff_nid = $tariff->nid;

			if ( isset( $rate->field_charge_collection['und'][0]['value'])) {
				$vs = entity_load_single( 'field_collection_item', $rate->field_charge_collection['und'][0]['value']);
			}
			else {
				$vs = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
				$vs->setHostEntity( 'node', $rate);
			}

			$vs->field_range_start['und'][0]['value'] = 0;
			$vs->field_uom_amount['und'][0]['value'] = $rec['RATE_APLY_UNIT'];
			$vs->field_price_amount_float['und'][0]['value'] = floatval($rec['RATE']);

			$vs->save();

			$rate->field_ref_tariffplan['und'][0]['nid'] = $tariff_nid;
			$rate->field_ref_tree_tid['und'][0]['value'] = $tree_tid['voice'];
		}

		node_save( $rate);

		// add mapping
		// tariff mapping
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'node')
			->entityCondition('bundle', 'basicrate_roaming')
			->fieldCondition('field_ref_tariffplan', 'nid', $tariff_nid)
			->fieldCondition('field_rating_group', 'value', $rate_code)
			->execute();

		if ( count( $result) == 1) {
			$nids = array_keys( $result['node']);
			$node = node_load( $nids[0]);
			$node->field_ref_rate['und'][0]['nid'] = $rate->nid;

			node_save( $node);
		}
		else if ( count($result) == 0) { 
			$mapping = ocs_admin_get_new_node( 'basicrate_roaming');
			$mapping->field_ref_tariffplan['und'][0]['nid'] = $tariff_nid;
			$mapping->field_ref_rate['und'][0]['nid'] = $rate->nid;
			$mapping->field_rating_group['und'][0]['value'] = $rate_code;

			node_save( $mapping);
		}
		else {	// too many mapping
			print 'Invalid tariff mapping '. $nl;
			print_r( $result['node']);
		}
	}
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

function _get_tariff_plan( $nid, $tariff_name)
{
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'tariffplan')
		->propertyCondition('title', $tariff_name)
		->fieldCondition('field_ref_product', 'nid', $nid)
		->execute();

	if ( count( $result) == 1) {
		$nids = array_keys( $result['node']);
		$node = node_load( $nids[0]);
		return $node;
	}

	return NULL;
}

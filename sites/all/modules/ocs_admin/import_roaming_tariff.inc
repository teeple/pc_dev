<?php
define( 'INVENTORY_ITEM_ID', '0');
define( 'VALD_STRT_DT', '1');
define( 'PROD_CD', '2');
define( 'FTR_CD', '3');
define( 'RATE_DV_CD', '4');
define( 'IOCLL_DV_CD', '5');
define( 'RATE_APLY_LVL_CD', '6');
define( 'RATE_APLY_DV_CD', '7');
define( 'UAGE_APPLY_DV_CD', '8');
define( 'RATE_APLY_TIMEBAND_CD', '9');
define( 'RATE_APLY_INTERVAL_CD', '10');
define( 'RATE_APLY_CYCL_DV_CD', '11');
define( 'RATE_APLY_UNIT_CD', '12');
define( 'RATE_APLY_UNIT	', '13');
define( 'RATE', '14');
define( 'INIT_RATE_CYCLE_DURATION', '15');
define( 'INIT_RATE_APLY_UNIT_CD', '16');
define( 'INIT_RATE_APLY_UNIT', '17');
define( 'INIT_RATE', '18');
define( 'VALD_END_DT', '19');

$tariff = array(
array(114933,"2013/03/19 00:00:00","KORSK_Customer",1031,33,1,2,2,NULL,NULL,NULL,4,303,60,5,0,303,10,1,"9999/12/31 23:59:59"),
array(114938,"2013/03/19 00:00:00","KORSK_Customer",1031,33,2,2,2,NULL,NULL,NULL,4,303,60,2,NULL,NULL,NULL,NULL,"9999/12/31 23:59:59"),
array(114940,"2013/03/19 00:00:00","KORSK_Customer",1033,33,0,2,2,NULL,NULL,NULL,4,303,60,2,120,303,60,0,"9999/12/31 23:59:59"),
array(114941,"2013/03/19 00:00:00","KORSK_Customer",1036,33,1,2,2,NULL,NULL,NULL,4,202,1,0.5,NULL,NULL,NULL,NULL,"9999/12/31 23:59:59"),
array(114942,"2013/03/19 00:00:00","KORSK_Customer",1036,33,2,2,2,NULL,NULL,NULL,4,202,1,0,NULL,NULL,NULL,NULL,"9999/12/31 23:59:59"),
array(114943,"2013/03/19 00:00:00","KORSK_Customer",1038,33,0,2,2,NULL,NULL,NULL,4,402,2,3,NULL,NULL,NULL,NULL,"9999/12/31 23:59:59"),
);

$country_list = _get_country_list();

$roam_list = _get_roaming_country();
$carrier_list = _get_roaming_carrier();
print_r( $tariff);

$roaming_type = array( 'HPLMN' => 2749, 
		'VPLMN' => 2750,
		'otherPLMN' => 2751, 
		'INCOMING' => 2752
		);
$nl = '
';

$roaming_plan = _get_node_by_title( 'roaming_plan', 'imported_roaming_plan');
if ( empty( $roaming_plan)) {
	$roaming_plan = ocs_admin_get_new_node( 'roaming_plan');
	$roaming_plan->title = 'FCE_Roaming_Plan';
	node_save( $roaming_plan);
}

unset( $roaming_plan->field_ref_roaming_ratinggroup['und']);

/*
foreach( $tariff as $category => $child) {
	print 'category : ' . $category . $nl;
	foreach( $child as $country_code => $data) {
		print 'country : ' . $country_code . $nl;

		$country = $country_list[$country_code]['country_name'];
		$rm_country = _get_node_by_title( 'roaming_country', $country);
		if ( empty( $rm_country)) {
			print 'ERROR : Roaming country not found : ' . $country . $nl;
			continue;
		}

		foreach( $data as $carrier => $rate_list) {
			print 'carrier : ' . $carrier . $nl;

			if ( ! empty( $carrier)) {
				$ca = _get_node_by_title( 'roaming_carrier', $carrier);
				if ( empty( $ca)) {
					print 'ERROR: Roaming carrier not found: ' . $carrier . $nl;
				}
			}

			foreach( $rate_list as $rate) {
				print_r( $rate);

				$rate_node = _get_node_by_title( 'roaming_ratinggroup', 'roaming_rg:' . $country_code . ':' . $carrier . ':' . $rate['roaming_type']);
				if ( empty( $rate_node)) {
					$rate_node = ocs_admin_get_new_node('roaming_ratinggroup');
					$rate_node->title = 'roaming_rg:' . $country_code . ':' . $carrier . ':' . $rate['roaming_type'];
					print 'New Rate : ' . $rate_node->title . $nl;

					$rate_node->field_ref_roaming_country['und'][0]['nid'] = $rm_country->nid;
					if ( ! empty( $carrier)) {
						$rate_node->field_ref_roaming_carrier['und'][0]['nid'] = $ca->nid;
					}
					$rate_node->field_ref_roaming_type['und'][0]['tid'] = $roaming_type[ $rate['roaming_type']];
					$rate_node->field_rating_group['und'][0]['value'] = $rate['ruleName'];
					$rate_node->field_ref_roaming_plan['und'][0]['nid'] = $roaming_plan->nid;
					$rate_node->field_ref_type_of_call['und'][0]['tid'] = 1511;

					node_save( $rate_node);

				}
				else {
					print 'Existing Rate : ' . $rate_node->title . $nl;

					if ( $rate_node->field_ref_roaming_country['und'][0]['nid'] != $rm_country->nid) 
						print 'roaming country mismatch' . $nl;
					if ( ! empty( $carrier)) {
						if ( $rate_node->field_ref_roaming_carrier['und'][0]['nid'] != $ca->nid) 
							print 'roaming carrier mismatch' . $nl;
					}
					if ( $rate_node->field_ref_roaming_type['und'][0]['tid'] != $roaming_type[ $rate['roaming_type']])
						print 'roaming type mismatch' . $nl;
					if ( $rate_node->field_rating_group['und'][0]['value'] != $rate['ruleName'])
						print 'roaming rating group type mismatch' . $nl;
				}

				$roaming_plan->field_ref_roaming_ratinggroup['und'][] = array( 'nid' => $rate_node->nid);

				// save rate
				$ra = _get_node_by_title( 'rate', 'roaming_rate:' . $rate['ruleName']);
				if ( empty( $ra)) {
					$ra = ocs_admin_get_new_node('rate');
					$ra->title = 'roaming_rate:' . $rate['ruleName'];
					$ra->field_range_units['und'][0]['tid'] = 390;
					$ra->field_uom_units['und'][0]['tid'] = 451;
					$ra->field_ref_tariffplan['und'][0]['nid'] = 64243;
					$ra->field_ref_tree_tid['und'][0]['value'] = 2754;

					if ( $rate['ruleName'] == 'FREE')
						$price = array( 60, 0);
					else
						$price = split( '_', $rate['ruleName']);

					$vs = entity_create('field_collection_item', array('field_name' => 'field_charge_collection'));
					$vs->setHostEntity( 'node', $ra);
					$vs->field_range_start['und'][0]['value'] = 0;
					$vs->field_uom_amount['und'][0]['value'] = $price[0];
					$vs->field_price_amount_float['und'][0]['value'] = floatval( $price[1]) / 100.0;
					$vs->save();

					node_save( $ra);
				}

				// tariff mapping
				$query = new EntityFieldQuery();
				$result = $query->entityCondition('entity_type', 'node')
					->entityCondition('bundle', 'basicrate_roaming')
					->fieldCondition('field_ref_tariffplan', 'nid', 64243)
					->fieldCondition('field_rating_group', 'value', $rate['ruleName'])
					->execute();

				if ( count( $result) > 0) {
					$nids = array_keys( $result['node']);
					$node = node_load( $nids[0]);
					$node->field_ref_rate['und'][0]['nid'] = $ra->nid;
					node_save( $node);
				}
				else {
					print 'Tariff mapping not found : rule=' . $rate['ruleName'] . $nl;
				}
			}
		}
	}
	node_save( $roaming_plan);
	return;
}

return;
*/

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

function _get_roaming_tariff()
{
	db_set_active('fce');

	$fields = array(
			'ruleName', 'roaming_type', 'user_category', 'roaming_time_id', 'roaming_country', 'roaming_carrier', 'rating_group' 
	);
	$table = 'roaming_voice_tariff_decision';

	$query = db_select( $table, 'v');
	$result = $query->fields( 'v', $fields)
		->execute();

	$records = array();
	while( $record = $result->fetchAssoc()) {
		$records[$record['user_category']][$record['roaming_country']][$record['roaming_carrier']][] = $record;
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

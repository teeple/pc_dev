<?php

require( 'script_common.inc');

$h = array_flip( array( 'category', 'service_domain', 'prdtype', 'name', 'id', 'custtype', 'billtype', 'short_code'));

$data = array(
'X,Mobile,Main,CPPS Fam90,cpps_fam90,Group,Prepaid,c1',
'W,Mobile,Main,CPPS 86,cpps_86,Group,Prepaid,c2',
'O,Mobile,Main,Okta Experience Zone O,okta_experience_zone_o,Personal,Prepaid,o1',
'I,Mobile,Main,Univision I,univision_i,Personal,Prepaid,u1',
'G,Mobile,Main,ID Offnet 40SMS,id_offnet_40sms,Personal,Prepaid,i1',
'F,Mobile,Main,DOPIN 86C,dopin_86c,Personal,Prepaid,d1',
'D,Mobile,Main,DOPIN Old,dopin_old,Personal,Prepaid,d2',
'A,Mobile,Main,CPPS Onnet Free,cpps_onnet_free,Group,Prepaid,c3',
'C,Mobile,Main,CDOPIN,cdopin,Group,Prepaid,c4',
'Z,Mobile,Main,CPPS,cpps,Group,Prepaid,c5',
'K,Mobile,Main,VoIP 77 -2,voip_77_2,Personal,Prepaid,v1',
'J,Mobile,Main,VoIP 77-1,voip_77_1,Personal,Prepaid,v2',
'R,Mobile,Main,Second Tariff,second_tariff,Personal,Prepaid,s1',
'P,Mobile,Main,PPS Live Modem,pps_live_modem,Personal,Prepaid,p1',
'Q,Mobile,Main,Easy Tour,easy_tour,Personal,Prepaid,e1',
'S,Mobile,Main,New Life,new_life,Personal,Prepaid,n1',
'Y,Mobile,Main,ID,id,Personal,Prepaid,i2',
'E,Mobile,Main,DOPIN Valid 90 Days,dopin_90_days,Personal,Prepaid,d3',
'B,Mobile,Main,DOPIN,dopin,Personal,Prepaid,d4',
'M,Mobile,Main,Happy Life Valid 90 Days,happy_life_90_days,Personal,Prepaid,h1',
'N,Mobile,Main,Happy Life,happy_life,Personal,Prepaid,h2',
	);

$attr = array(
		'all' => array(
			'attribute_featurecode' => array( 
				'type' => 'prdattributefeaturecode',
				'value' => 'ACT_PREPAID'),
			'attribute_subscriber_lifecycle_scheme' => array(
				'type' => 'treenodelifecyclescheme',
				'value' => 'E2E_Mobile Prepaid'),
			),

		'happy_life' => array(
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '120000', '199999'),
					array( '88', '210000', '229999'),
					array( '88', '240000', '299999'),
					array( '88', '310000', '399999'),
					array( '88', '420000', '489999'),
					array( '88', '500000', '599999'),
					array( '88', '610000', '699999'),
					array( '88', '710000', '789999'),
					array( '88', '810000', '879999'),
					array( '88', '890000', '999999'),
					array( '89', '120000', '299999'),
					array( '89', '350000', '389999'),
					array( '89', '400000', '409999'),
					array( '89', '420000', '489999'),
					array( '89', '500000', '589999'),
					array( '89', '600000', '689999'),
					array( '89', '700000', '769999'),
					array( '89', '780000', '789999'),
					array( '89', '800000', '879999'),
					array( '86', '120000', '599999'),
					array( '86', '700000', '999999'),
					/*
					8812-8899 (not included:8823, 8820, 8830, 8840, 8841, 8849, 8860, 8870, 8879, 8888)
					8912-8929, 8935-8938, 8940, 8942-8948, 8950-8958, 8960-8968, 8970-8976, 8978, 8980-8987, 
					8612-8659, 8670-8699
					*/
					),
				)
			)
		);

// get voca terms
$voca_list = array( 'custdvcd', 'billtype', 'prdtype', 'featurecode', 'tpl_default_tree_mobile');
$term = array();
foreach( $voca_list as $voca) {
	if ( substr( $voca, 0, 4) == 'tpl_') {
		$terms = ocs_get_terms( $voca);
		foreach( $terms as $t) {
			$term[$voca][$t->field_rel_type['und'][0]['value']] = $t->tid;
		}
	}
	else {
		$term[$voca] = ocs_get_terms_tid( $voca);
	}
}

// check argument
$arg_product_id = drush_shift();

//print_r( $header);
$idx = 0;
foreach( $data as $item) {
	$d = explode( ',', $item);

	$prd_id = $d[$h['id']];
	$title = $d[$h['name']];

	if ( !empty( $arg_product_id) && $prd_id != $arg_product_id ) 
		continue;

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $title)
		->execute();

	if ( empty( $result)) {
		printf( "Add NEW product : %s\n", $title);
		$p = ocs_admin_get_new_node( 'simpleproductoffering');

		// product name and description
		$p->title = $title;
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);
		printf( "Existing product : %s\n", $title);
	}

	$p->field_product_type['und'][0]['tid'] = $term['prdtype']['Main'];
	$p->field_description['und'][0]['value'] = t( 'FCE(@c) @t ', array( '@c' => $d[$h['category']], '@t' => $title));

	// product id
	$p->field_product_id['und'][0]['value'] = $prd_id;

	// short code
	$p->field_short_code['und'][0]['value'] = $d[$h['short_code']];

	// bill type
	$p->field_billing_type['und'][0]['tid'] = $term['billtype']['Prepaid'];

	// market : default value (unitel)

	// customer type : personal (default)
	$p->field_customer_type['und'][0]['tid'] = $term['custdvcd'][$d[$h['custtype']]];

	// customer sub type : personal 

	// customer sub type

	node_save( $p);

	// add attributes
	$attr_list = array_merge( $attr['all'], isset($attr[$prd_id]) ? $attr[$prd_id] : array());
	foreach( $attr_list as $key => $val) {
		switch( $key) {
			case 'attribute_featurecode':
				$node = get_attr( $p, $val['type'], $term['tpl_default_tree_mobile'][$key], $val['value']);
				$node->field_ref_service_feature_code['und'][0]['tid'] = $term['featurecode'][$val['value']];
				node_save( $node);
				break;
			case 'attribute_allowed_prefix' :
				$node = get_attr( $p, $val['type'], $term['tpl_default_tree_mobile'][$key], 'Allowed');
				set_allowed_prefix( $node, $val['value']);
				break;
			case 'attribute_subscriber_lifecycle_scheme':
				$nids = ocs_get_nodes_by_title( 'lifecyclescheme', $val['value']);
				if ( empty( $nids)) {
					printf("  No Lifecycle scheme was found. name=%s\n", $val['value']);
				}
				else {
					$node = get_attr( $p, $val['type'], $term['tpl_default_tree_mobile'][$key], $val['value']);
					$node->title = $val['value'];
					$node->field_lifecycle_scheme['und'][0]['nid'] = $nids[0];
					node_save( $node);
				}
				break;
		}
	}

	// add tariff plan
	foreach( array( 'voice', 'sms') as $type) {
		$tariffplan_name = $prd_id . '_' . $type . '_2013-01-01';
		$nids = ocs_get_nodes_by_title( 'tariffplan', $tariffplan_name);
		if ( empty( $nids)) {
			$tariffplan = ocs_admin_get_new_node( 'tariffplan');
			$tariffplan->title = $tariffplan_name;

			printf("  New tariff plan %s\n", $tariffplan_name);
		}
		else {
			$tariffplan = node_load( $nids[0]);

			printf("  Existing tariff plan %s\n", $tariffplan_name);
		}

		$tariffplan->field_ref_product['und'][0]['nid'] = $p->nid;
		$tariffplan->field_ref_tree_tid['und'][0]['value'] = $term['tpl_default_tree_mobile']['usage_' . $type];
		$tariffplan->field_tree_child_voca_name['und'][0]['value'] = 'tpl_tariffplan_' . $type;
		$tariffplan->field_valid_date_ymd['und'][0] = array(
				'value' => '2013-01-01 00:00:00',
				'timezone' => 'Asia/Ulaanbaatar',
				'timezone_db' => 'Asia/Ulaanbaatar',
				'date_type' => 'datetime',
				);
		$tariffplan->field_valid_date_hour['und'][0]['value'] = '00';

		node_save( $tariffplan);
	}

}

function set_allowed_prefix( $node, $prefix_list)
{
	$prefix_to_delete = array();
	foreach( $node->field_prefix_range['und'] as $i => $entity_id) {
		$p = entity_load_single( 'field_collection_item', $entity_id);
		$found = false;
		foreach( $prefix_list as $idx => $pfx) {
			if ( $pfx[0] == $p->field_base_prefix['und'][0]['value'] &&
				$pfx[1] == $p->field_prefix_range_start['und'][0]['value'] &&
				$pfx[2] == $p->field_prefix_range_end['und'][0]['value']) {
				/*
				printf("Existing Prefix %s %s %s\n", $p->field_base_prefix['und'][0]['value'],
					$p->field_prefix_range_start['und'][0]['value'],
					$p->field_prefix_range_end['und'][0]['value']);
					*/
				unset( $prefix_list[$idx]);
				$found = true;
				break;
			}
		}

		if ( ! $found) {
			// delete
			entity_delete( 'field_collection_item', $entity_id);
			$prefix_to_delete[] = $i;

			printf("  Remove Prefix %s %s %s\n", $p->field_base_prefix['und'][0]['value'],
				$p->field_prefix_range_start['und'][0]['value'],
				$p->field_prefix_range_end['und'][0]['value']);
		}
	}


	// remove old prefix list
	//print_r( $prefix_to_delete);
	foreach( $prefix_to_delete as $idx) {
		unset( $node->field_prefix_range['und'][$idx]);
	}
	node_save( $node);

	// add new prefix
	//print_r( $prefix_list);
	if ( empty( $prefix_list)) {
		printf("  No new prefix\n");
	}
	foreach( $prefix_list as $idx => $pfx) {
		$p = entity_create('field_collection_item', array('field_name' => 'field_prefix_range'));
		$p->setHostEntity( 'node', $node);
		$p->field_base_prefix['und'][0]['value'] = $pfx[0];
		$p->field_prefix_range_start['und'][0]['value'] = $pfx[1];
		$p->field_prefix_range_end['und'][0]['value'] = $pfx[2];
		$p->save();

		printf("  Add Prefix %s %s %s\n", $p->field_base_prefix['und'][0]['value'],
			$p->field_prefix_range_start['und'][0]['value'],
			$p->field_prefix_range_end['und'][0]['value']);
	}
	node_save( $node);
}

function get_attr( $product, $type, $tree_tid, $val)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition('field_ref_product', 'nid', $product->nid)
		->fieldCondition('field_ref_tree_tid', 'value', $tree_tid)
		->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		$node->title = $val;
		$node->field_ref_product['und'][0]['nid'] = $product->nid;
		$node->field_ref_tree_tid['und'][0]['value'] = $tree_tid;
		printf("  New attribute type=%s title=%s\n", $type, $node->title);
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
	}

	return $node;
}

function counter_info( $name)
{
	// find the counter
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'counter')
		->propertyCondition('title', $name)
		->execute();

	if ( empty( $result)) {
		return NULL;
	}
	$nid = array_pop( array_keys( $result['node']));
	return node_load( $nid);
}

function get_attribute( $type, $nid, $tid)
{
	// actionpriceallowanceonetime
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition('field_ref_product', 'nid', $nid)
		->fieldCondition('field_ref_tree_tid', 'value', $tid)
		->execute();

	if ( empty( $result)) {
		$p = ocs_admin_get_new_node( $type);

		// set ref product 
		$p->field_ref_product['und'][0]['nid'] = $nid;

		// set tree tid
		$p->field_ref_tree_tid['und'][0]['value'] = $tid;
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);
	}

	return $p;
}

function print_result( $node, $str)
{
	if ( property_exists( $node, 'nid')) {
		printf( "Existing %s\n", $str);
	}
	else {
		printf( "New %s\n", $str);
	}
}
	
function check_subscription_bonus( $product, $tid, $bonus, $counter)
{
	global $term;

	// actionpriceallowanceonetime
	$p = get_attribute( 'actionpriceallowanceonetime', $product->nid, $tid);

	$p->title = $bonus . ' MB';
	$p->field_title_2nd['und'][0]['value'] = $p->title;

	print_result( $p, 'Bonus : ' . $p->title);
	node_save( $p);

	// actionsetcounteronbonus
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'actionsetcounteronbonus')
		->fieldCondition('field_ref_source_action', 'nid', $p->nid)
		->fieldCondition('field_ref_counter', 'nid', $counter->nid)
		->execute();

	if ( empty( $result)) {
		$c = ocs_admin_get_new_node( 'actionsetcounteronbonus');

		$c->field_ref_source_action['und'][0]['nid'] = $p->nid;
		$c->field_ref_counter['und'][0]['nid'] = $counter->nid;
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$c = node_load( $nid);
	}
	
	$c->field_amount['und'][0]['value'] = $bonus ;		// MB to bytes
	$c->field_add_or_replace['und'][0]['tid'] = $term['counterset_addorreplace']['Replace'] ;	// replace
	$c->field_startdate_option1['und'][0]['tid'] = $term['day_option']['start']['Now'];
	$c->field_enddate_option1['und'][0]['tid'] = $term['day_option']['end']['+ N Date(D,W,M,Y)'];
	$c->field_enddate_option3['und'][0]['value'] = 30;	// 30 days
	$c->field_enddate_option4['und'][0]['tid'] = $term['day_option']['unit']['Day'];

	node_save( $c);
}

function check_counter_list( $product, $tid, $counter)
{
	// find the counter
	$p = get_attribute( 'prdcounterlist', $product->nid, $tid);
	$p->title = 'PrdCounterList';

	if ( empty( $p->field_counter_list)) {
		$p->field_counter_list['und'][0]['nid'] = $counter->nid;
	}
	else if( array_search( $counter->nid, array_get_value( $p->field_counter_list)) === FALSE) {
		$p->field_counter_list['und'][] = array( 'nid' => $counter->nid);
		printf( "Add counter %s to the Existing counter list : %s\n", $counter->title, $p->title);
	}

	node_save( $p);
}


function check_subscription_fee( $product, $tid, $price)
{
	// find the price
	$p = get_attribute( 'actionpricechargeonetime', $product->nid, $tid);
	$p->title = 'Charge ' . $price ;
	$p->field_price_amount_float['und'][0]['value'] = $price;
	print_result( $p, 'Subscription Fee : ' . $p->title);

	node_save( $p);
}



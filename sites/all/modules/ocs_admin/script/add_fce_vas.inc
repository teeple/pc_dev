<?php

require( 'script_common.inc');

$h = array_flip( explode( ',', 'id,name,Status,type,Price,Feature'));

$data = array(
'MSL_P,Missed call log,Active,Daily,40,MSL',
'HOLD_P,Call Hold supplementary services for a susscriber,Active,Free,0,HOLD',
'GPRS_P,GPRS Service,Active,Free,0,GPRS',
'IV_P,Intl voice,Active,Free,0,',
'CID_P,Caller ID (Call Screening),Active,per each,0,',
'CH_P,Call Holding Service(Aaaoa? aooaeaaa oeeo),Active,Free,0,',
'RV_P,Roaming Voice,Active,Free,0,',
'VMS_P,Voice Message Service,Active,Free,0,',
'COLR_P,Supplemantary Service ,Active,Free,0,',
'SMSMT_P,Terminating SMS,Active,per each,0,',
'CRBT_P,Uni Music (Ayeaooo aioei ?a?o),Active,Daily,40,',
'SPINI_2_P,Call Restrict (Aa?ao aooaeaaaa eia oeeo),Active,Free,0,',
'CFNRC_P,Call Forwarding on Mobile Subscriber Not Reachable,Active,per each,0,',
'CFU_P,Call Forwarding-Unconditinal (Aooaeaaa oee?vveyo-oooa),Active,per each,0,',
'ODBINFO_P,Barring Information Call,Active,Free,0,',
'CWAIT_P,Call Waiting,Active,Free,0,',
'BOPRC_2_P,BOPRC(ENT) (entertainment),Active,per each,0,',
'CLIR_P,Identification restriction service,Active,per each,20,',
'DND_1_P,Incoming Call Suspension directly  (I?io aooaeaaa oaao),Active,Free,0,',
'ECT_P,Explicit Call Transfer,Active,Free,0,',
'PLMNSS_P,PLMN specific supplementary services (PLMN specific SS),Active,Free,0,',
'TPLGPRS_P,Modify subscriber\'s GPRS service parameters with 160,Active,Free,0,',
'MPTY_P,Multiparty Service,Active,per each,0,',
'CFB_P,Call Forwarding-Busy (Aooaeaaa oee?vveyo-caaave),Active,per each,0,',
'CFNRY_P,Call Forwarding No Answer (Aooaeaaa oee?vveyo-oa?eoeaaave),Active,per each,0,',
'WAP_P,Wireless Application Protocol,Active,Free,0,',
'BOIC_EXHC_P,Conference Call(Oaeaoii oo?ae),Active,Free,0,',
'BOPRC_P,BOPRC(INFO),Active,per each,0,',
'COLP_P,Connected Line Identification,Active,Free,0,',
'CLIP_P,Calling Line Identification ,Active,Free,0,',
'FAX_P,Fax Data,Active,Monthly,0,',
'SMSMO_P,Originate SMS,Active,per each,0,',
'DBIC_P,Barring Of Incoming Call,Active,Free,0,',
'DBOC_P,Barring Of Outgoing Call,Active,Free,0,',
'WSC_P,WebSelfCare,Active,per each,1000,',
'WSCS_P,WebSelfCare Secure,Active,Monthly,0,',
'CRBTP_P,CRBT Plus,Active,Daily,15,',
'CRBTF_P,CRBT Free,Active,Monthly,0,',
'CRBTPF_P,CRBT Plus Free,Active,Monthly,0,',
'VCALL_P,Video Call,Active,Free,0,',
'PDOWN_P,Package Upgrade fee,Active,Free,0,',
'ULOAN_P,UnitLoan/UnitGift,Active,Free,0,',
'USSD_P,USSD Checking,Active,Free,0,',
'ACT BAOC_P,Action Barring Of Outgoing Call,Active,Free,0,',
'MSL_R,Missed call log,Active,Monthly,1200,',
'HOLD_R,Call Hold supplementary services for a susscriber,Active,Free,0,',
'GPRS_R,GPRS Service,Active,Free,0,',
'IV_R,Intl voice,Active,Free,0,',
'CID_R,Caller ID (Call Screening),Active,per each,0,',
'CH_R,Call Holding Service(Aaaoa? aooaeaaa oeeo),Active,Free,0,',
'RV_R,Roaming Voice,Active,Free,0,',
'VMS_R,Voice Message Service,Active,Free,0,',
'COLR_R,Supplemantary Service ,Active,Free,0,',
'SMSMT_R,Terminating SMS,Active,per each,0,',
'CRBT_R,Uni Music (Ayeaooo aioei ?a?o),Active,Monthly,1200,',
'SPINI_2_R,Call Restrict (Aa?ao aooaeaaaa eia oeeo),Active,Free,0,',
'CFNRC_R,Call Forwarding on Mobile Subscriber Not Reachable,Active,per each,0,',
'CFU_R,Call Forwarding-Unconditinal (Aooaeaaa oee?vveyo-oooa),Active,per each,0,',
'ODBINFO_R,Barring Information Call,Active,Free,0,',
'CWAIT_R,Call Waiting,Active,Free,0,',
'BOPRC_2_R,BOPRC(ENT) (entertainment),Active,per each,0,',
'CLIR_R,Identification restriction service,Active,per each,20,',
'DND_1_R,Incoming Call Suspension directly  (I?io aooaeaaa oaao),Active,Free,0,',
'ECT_R,Explicit Call Transfer,Active,Free,0,',
'PLMNSS_R,PLMN specific supplementary services (PLMN specific SS),Active,Free,0,',
'TPLGPRS_R,Modify subscriber\'s GPRS service parameters with 160,Active,Free,0,',
'MPTY_R,Multiparty Service,Active,per each,0,',
'CFB_R,Call Forwarding-Busy (Aooaeaaa oee?vveyo-caaave),Active,per each,0,',
'CFNRY_R,Call Forwarding No Answer (Aooaeaaa oee?vveyo-oa?eoeaaave),Active,per each,0,',
'WAP_R,Wireless Application Protocol,Active,Free,0,',
'BOIC_EXHC_R,Conference Call(Oaeaoii oo?ae),Active,Free,0,',
'BOPRC_R,BOPRC(INFO),Active,per each,0,',
'COLP_R,Connected Line Identification,Active,Free,0,',
'CLIP_R,Calling Line Identification ,Active,Free,0,',
'FAX_R,Fax Data,Active,Monthly,0,',
'SMSMO_R,Originate SMS,Active,per each,0,',
'DBIC_R,Barring Of Incoming Call,Active,Free,0,',
'DBOC_R,Barring Of Outgoing Call,Active,Free,0,',
'WEBSMS_R,Web to SMS ,Active,Monthly,1200,',
'WSC_R,WebSelfCare,Active,Monthly,1000,',
'WSCS_R,WebSelfCare Secure,Active,Monthly,0,',
'CRBTP_R,CRBT Plus,Active,Monthly,450,',
'CRBTF_R,CRBT Free,Active,Monthly,0,',
'CRBTPF_R,CRBT Plus Free,Active,Monthly,0,',
'VCALL_R,Video Call,Active,Free,0,',
'ULOAN_R,UnitLoan/UnitGift,Active,Free,0,',
'USSD_R,USSD Checking,Active,Free,0,',
'ACT BAOC_R,Action Barring Of Outgoing Call,Active,Free,0,',
'SIM_REF_P,SIM  Card Refresh,NO,per each,3000,',
'TST_1_P,TUMUR_SVC,NO,Free,0,',
'TEST_P,TEST Service,NO,per each,20,',
'WEBSMS_P,Web to SMS ,NO,Monthly,1200,',
'SIM_REF_R,SIM  Card Refresh,NO,per each,8000,',
'TST_1_R,TUMUR_SVC,NO,Free,0,',
'TEST_R,TEST Service,NO,per each,20,',
'PDOWN_R,Package Downgrade fee,NO,Free,5000,',
	);

$attr = array(
		/*
		'all' => array(
			'attribute_featurecode' => array( 
				'type' => 'prdattributefeaturecode',
				'value' => 'ACT_PREPAID'),
			'attribute_subscriber_lifecycle_scheme' => array(
				'type' => 'treenodelifecyclescheme',
				'value' => 'E2E_Mobile Prepaid'),
			),
			*/

		);

// get voca terms
$voca_list = array( 'custdvcd', 'billtype', 'prdtype', 'featurecode', 'tpl_default_tree_mobile', 
		'prdexpiredate', 'countermainoraccu', 'specialdateoptions', 'specialenddateoptions', 
		'counterset_addorreplace', 'unitofmeasure_enddate');
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

	$title = $d[$h['id']];
	$prd_id = strtolower( $title);

	if ( !empty( $arg_product_id) && $prd_id != $arg_product_id ) 
		continue;

	//print_r( $term['prdtype']);

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $title)
		->fieldCondition('field_product_type', 'tid', $term['prdtype']['VAS'])
		->execute();

	if ( empty( $result)) {
		printf( "Add NEW product : %s\n", $title);
		$p = ocs_admin_get_new_node( 'simpleproductoffering');

		// product name and description
		$p->title = $title;
		$p->field_product_type['und'][0]['tid'] = $term['prdtype']['VAS'];
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);
		printf( "Existing product : %s\n", $title);
	}

	$p->field_description['und'][0]['value'] = $d[$h['name']];

	// product id
	$p->field_product_id['und'][0]['value'] = $prd_id;

	// short code
	$p->field_short_code['und'][0]['value'] = substr( $prd_id, 0, 8);

	// bill type
	if ( substr( $title, -2) == '_P')
		$p->field_billing_type['und'][0]['tid'] = $term['billtype']['Prepaid'];
	else
		$p->field_billing_type['und'][0]['tid'] = $term['billtype']['Postpaid'];

	// market : default value (unitel)

	// customer type : personal (default)
	$p->field_customer_type['und'][0]['tid'] = $term['custdvcd'][$d[$h['custtype']]];

	// customer sub type : personal 

	node_save( $p);

	// add feature code
	$feature = $d[$h['Feature']];
	if ( ! empty( $feature) && strlen( $feature) > 0) {
		if ( isset( $term['featurecode'][$feature])) {
			$node = get_attr( $p, 'prdattributefeaturecode', 
				$term['tpl_default_tree_mobile']['attribute_featurecode'], $feature);
			$node->field_ref_service_feature_code['und'][0]['tid'] = $term['featurecode'][$feature];
			node_save( $node);
		}
		else {
			printf("  Unknown feature code : %s\n", $feature);
		}
	}

	// add price
	$bill_type = $d[$h['type']];
	$price = $d[$h['Price']];
	if ( ($bill_type == 'Daily' || $bill_type == 'Monthly') && $price > 0) {
		$node = get_attr( $p, 'actionpricechargerecurringdefaul', 
			$term['tpl_default_tree_mobile']['nonusage_fee_recurring_default']);
		$node->field_price_amount_float['und'][0]['value'] = $price;
		$node->field_pricing_cycle_type['und'][0]['value'] = ($bill_type == 'Daily') ? '1' : '2';
		node_save( $node);
	}
}

return;


function get_attr_cond( $type, $title, $field_cond)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type);

	if ( $field_cond) {
		foreach( $field_cond as $cond) {
			$query->fieldCondition( $cond[0], $cond[1], $cond[2]);
		}
	}
	$result = $query->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		printf("  New attribute type=%s title=%s\n", $type, $title);
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
	}

	return $node;
}

function get_attr( $product, $type, $tree_tid, $title = NULL, $field_cond = NULL)
{
	// find the attribute
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type)
		->fieldCondition('field_ref_product', 'nid', $product->nid)
		->fieldCondition('field_ref_tree_tid', 'value', $tree_tid);

	if ( $field_cond) {
		foreach( $field_cond as $cond) {
			$query->fieldCondition( $cond[0], $cond[1], $cond[2]);
		}
	}
	$result = $query->execute();

	if ( empty( $result)) {
		$node = ocs_admin_get_new_node( $type);
		if ( $title) $node->title = $title;
		$node->field_ref_product['und'][0]['nid'] = $product->nid;
		$node->field_ref_tree_tid['und'][0]['value'] = $tree_tid;
		printf("  New attribute type=%s title=%s\n", $type, $node->title);
	}
	else {
		$node = node_load( array_pop( array_keys( $result['node'])));
		printf("  Existing attribute type=%s title=%s\n", $type, $node->title);
	}

	return $node;
}

function get_counter( $counter_id)
{
	// find the counter
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'counter')
		->fieldCondition('field_counter_id', 'value', $counter_id)
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


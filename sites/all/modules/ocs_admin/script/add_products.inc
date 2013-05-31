<?php

require( 'script_common.inc');

$header = explode( ',', "PrdType,Package Type,Category,Active Period,Grade Period,Price,Package(MB),Package Flag,Package Name,,Prepaid Speed,Postpaid Speed,SMS msg,update user,update date,add tariff,SMS buy,min usage,rollover option,chagne flag,threshod 1,threshold 2,threshold 3,treatment,deposit,threshold corp 1,threshold corp 2,threhold corp3,,,,,,");
$header = array_flip( $header);

$package_info = Array(
"Additional,1,NSDM,30,10,12000,1024,M,LiveInternet 1G-PS 8823 Only,0,13,32,1,boloroo,20120910104542,0.01,Y,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,2,NSDM,30,10,17000,2048,M,LiveInternet 2G-PS 8823 only,0,13,32,2,dulguun_n,20111125141822,0.01,Y,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,3,NSDM,30,10,24000,4096,M,LiveInternet 4G-PS 8823 only,0,13,32,3,dulguun_n,20111128102848,0.01,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,4,NSDM,30,10,32000,8192,M,LiveInternet 8G-PS 8823 only,0,13,32,4,dulguun_n,20111128102855,0.01,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,5,NSDM,30,0,12000,10240,M,Live Internet 10G Unitel my life,0,11,32,5,dulguun_n,20111128102920,0.01,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,6,NSDM,30,10,0,1024,M,1GB free package for unitel staff,0,13,32,,dulguun_n,20111128102924,0.04,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,7,NSDM,30,10,0,40960,M,40GB free package for techinical use ,0,13,32,,dulguun_n,20111128142332,0,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,8,NSDM,30,10,0,3072,M,LiveInternet 3G Free -PS For MCS,0,13,32,,dulguun_n,20111128142338,0.01,Y,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,9,NSDM,30,30,6000,500,A,Live internet additional,0,0,0,QWE,tamir,20100302192513,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,10,N,0,0,30000,1024,M,BlackBerry BIS Discount sale for Unitel staff,0,13,36,,tamir,20130228113307,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,11,N,0,0,30000,5,M,BlackBerry BIS pack-1,0,13,36,,boloroo,20120524100526,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,12,N,0,0,40000,255,M,BlackBerry BIS pack-2,0,13,36,,boloroo,20120524100508,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,13,N,0,0,60000,1024,M,BlackBerry BIS pack-3,0,13,36,,boloroo,20120524100611,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,14,N,0,0,35000,5,M,BlackBerry BES pack-1,0,13,36,,boloroo,20120524100602,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,15,N,0,0,45000,255,M,BlackBerry BES pack-2,0,13,36,,boloroo,20120524100557,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,16,N,0,0,65000,1024,M,BlackBerry BES pack-3,0,13,36,,boloroo,20120524100622,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,17,NSDM,30,10,12000,1024,M,LiveInternet 1GB regular,0,13,32,1024,dulguun_n,20111128142426,0.08,Y,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,18,NSDM,30,10,17000,2048,M,LiveInternet 2GB regular,0,13,32,2048,dulguun_n,20111128142434,0.08,Y,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,19,NSDM,30,10,24000,4096,M,LiveInternet 4GB regular,0,13,32,4096,dulguun_n,20111128142443,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,20,NSDM,30,10,32000,8192,M,LiveInternet 8GB regular,0,13,32,8196,dulguun_n,20111128142448,0.08,N,0,N,1,0,0,0,0,,,,,,,Songodog 9000,,,20000",
"Additional,21,NSDM,30,10,0,10240,M,10GB free package for techinical use,0,13,32,,dulguun_n,20111128142454,0.01,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,29,NSDM,30,0,0,1024,M,1GB free for Handset Lease (12 month),0,13,32,,dulguun_n,20130517160154,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,30,N,30,10,30000,1024,M,BlackBerry BIS Free pack for Unitel staff,0,13,36,,boloroo,20120524100634,0.01,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,33,N,0,0,40000,999999,M,BlackBerry BIS pack-2 Unlimited,0,13,36,,boloroo,20120524100640,0.08,N,0,N,2,0,0,0,0,,,,,,,,,,",
"Additional,34,N,30,10,35000,1024,M,BB BES+ dotood heregceend 1G,0,13,36,,boloroo,20120524100658,0.01,N,0,Y,2,0,0,0,0,,,,,,,,,,",
"Additional,35,NSDM,30,10,0,100,A,Live Internet SD 100mb Additional,0,13,32,,dulguun_n,20111128142514,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,40,NSDM,30,10,12000,10240,M,Oyunlag Oyutan - Surguuliudiin WiFi,0,13,32,,dulguun_n,20111128142520,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,41,NSDM,30,10,0,25,M,M2M Data pack-1,0,13,84,,boloroo,20130130114436,0.04,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,42,NSDM,30,10,0,50,M,M2M Data pack-2,0,13,84,,boloroo,20130130114447,0.04,N,0,N,1,20000,25000,30000,0,,,,,,,,,,",
"Additional,43,NSDM,0,0,19900,999999,M,PS Unlimited pack,0,13,84,,boloroo,20130130114458,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,44,NSDM,0,0,0,999999,M,PS Unlimited pack free,0,13,84,,boloroo,20130130114506,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,45,NSDM,30,10,12000,8192,M,HUAWEI 8GB pack,0,13,32,81921,dulguun_n,20111128142526,0.08,N,0,N,1,0,0,0,0,,,,,,,,,,",
"Additional,46,NSDM,30,10,18090,999999,S,UNLIMITED + GreenBerry,0,13,84,,boloroo,20130130114524,0.08,N,0,N,1,50000,50000,50000,,25000,25000,25000,25000,,,,,,",
"Additional,47,NSDM,30,10,0,5,S,GreenBerry free ,0,13,32,,dulguun_n,20120208162049,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,48,NSDM,30,10,9000,5,S,GreenBerry package-1,0,13,32,,dulguun_n,20111128142538,0.08,N,0,N,1,10000,15000,20000,,0,3000,5000,10000,,,,,,",
"Additional,49,NSDM,30,10,15000,300,S,GreenBerry package-2,0,13,32,,dulguun_n,20111128142543,0.08,N,0,N,1,20000,25000,30000,,0,5000,10000,15000,,,,,,",
"Additional,50,N,0,0,25000,300,M,Premium BB+BES,0,13,36,,boloroo,20111216173622,0.08,N,0,Y,2,0,0,0,0,0,0,0,0,,,,,,",
"Additional,51,N,0,0,0,300,M,Premium BB Free,0,13,36,,boloroo,20111216173123,0.08,N,0,N,2,0,0,0,0,0,0,0,0,,,,,,",
"Additional,52,N,0,0,20000,300,M,Premium BB+BIS,0,13,36,,boloroo,20111216173613,0.08,N,0,N,2,0,0,0,0,0,0,0,0,,,,,,",
"Additional,53,N,0,0,30000,300,M,SIngle BIS pack,0,13,36,,boloroo,20111216173630,0.08,N,0,N,2,0,0,0,,0,0,0,0,,,,,,",
"Additional,54,N,0,0,35000,300,M,Single BES pack,0,13,36,,boloroo,20111216173638,0.08,N,0,N,2,0,0,0,0,0,0,0,0,,,,,,",
"Additional,55,NSDM,0,0,9000,300,S,GreenBerry pack-MUIS,0,13,32,,dulguun_n,20111128142615,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,56,NSDM,0,0,0,0,S,GreenBerry for Yaria 30000,0,13,32,,boloroo,20120228115752,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,57,NSDM,30,10,0,0,S,GreenBerry free package for unitel staff,0,13,32,,amartaivan,20111214135425,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,58,NSDM,0,0,0,999999,S,Unlimited+GB For 8888 only,0,13,84,,boloroo,20130130114556,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,59,N,0,0,0,300,M,Blackberry For 8888 Only,0,13,36,,boloroo,20120524100730,0.08,N,0,N,2,0,0,0,0,0,0,0,0,,,,,,",
"Additional,60,NSDM,0,0,0,4096,M,Tablet 8888 for 8823 only,0,13,32,,amartaivan,20120216155236,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,61,NSDM,30,0,0,10,A,TRIAL 10MB Free FORAllSubs 201205-1231,0,13,32,,boloroo,20120604130117,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,62,NSDM,30,0,909,50,M,STARTER-50MB,0,13,32,,boloroo,20120605101738,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,63,NSDM,30,0,2727,200,M,ASCEND-200MB,0,13,32,,boloroo,20120605101744,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,64,NSDM,30,0,10909,1024,M,SMART-1GB,0,13,32,,boloroo,20120605101752,0.08,N,0,N,1,30000,30000,30000,0,15000,15000,15000,15000,,,,,,",
"Additional,65,NSDM,30,0,18090,999999,M,UNLIMITED,0,13,84,,boloroo,20130130114609,0.08,N,0,N,1,50000,50000,50000,0,25000,25000,25000,25000,,,,,,",
"Additional,66,NSDM,0,0,909,50,A,Nemelt bagts-50MB,0,13,32,,boloroo,20120919170315,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,67,NSDM,0,0,2727,200,A,Nemelt bagts-200MB,0,13,32,,boloroo,20120919170324,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,70,NSDM,0,0,0,0,M,M2M KhaanBank APN,0,13,70,,boloroo,20120515141004,0.04,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,71,NSDM,30,10,0,0,S,Greenberry free for Corporate,0,13,32,,amartaivan,20120524122412,0.08,Y,0,Y,1,,,,,0,0,0,0,,,,,,",
"Additional,72,N,0,0,0,999999,M,Premium Data unlmited free,0,13,32,,tamir,20120618110035,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,73,NSDM,0,0,10000,999999,M,Premium Data (premium&package3) TEMP,0,13,32,,galbadral_b,20120618125259,0.08,Y,0,Y,1,,,,,0,0,0,0,,,,,,",
"Additional,74,NSDM,0,0,20000,999999,M,Premium Data (package2) TEMP,0,13,32,,galbadral_b,20120618125357,0.08,Y,0,Y,1,,,,,0,0,0,0,,,,,,",
"Additional,75,NSDM,0,0,0,999999,A,Premium Data (MyLife) TEMP,0,13,32,,galbadral_b,20120618134508,0.08,Y,0,Y,1,,,,,0,0,0,0,,,,,,",
"Additional,76,NSDM,30,0,0,1024,A,SUMMER PROMOTION 1GB 8823 only,0,13,32,,boloroo,20120630171034,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,77,NSDM,30,0,0,50,A,ONLINE PROMOTION 50MB,0,13,32,50 DATA,boloroo,20120910172635,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,78,NSDM,0,0,0,100,A,ONLINE PROMOTION 100MB,0,13,32,100 DATA,boloroo,20120910172644,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,79,NSDM,0,0,0,1024,A,ONLINE PROMOTION 1GB,0,13,32,1024 DATA,boloroo,20120910172652,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,80,NSDM,30,0,10909,1024,M,SMART-1GB ONLY CORP,0,13,32,,boloroo,20120920144411,0.08,N,0,N,1,30000,30000,30000,0,0,15000,15000,15000,,,,,,",
"Additional,81,NSDM,30,0,18090,999999,M,UNLIMITED ONLY CORP,0,13,84,,boloroo,20130130114642,0.08,N,0,N,1,50000,50000,50000,0,0,25000,25000,25000,,,,,,",
"Additional,82,NSDM,30,0,18090,999999,S,UNLIMITED + GreenBerry ONLY CORP,0,13,84,,boloroo,20130130114648,0.08,N,0,N,1,50000,50000,50000,0,0,25000,25000,25000,,,,,,",
"Additional,83,N,30,14,12000,4096,M,Mobile Dealer - 4GB,0,13,32,,tamir,20130213110836,0.01,N,0,N,1,0,0,0,1000,0,0,0,0,,,,,,",
"Additional,84,N,0,0,0,200,A,Free 200MB for eunitel promotion,0,15,34,,batzaya_t,20130401114739,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
"Additional,85,N,0,0,0,500,M,Free 500MB for eunitel promotion,0,15,34,,batzaya_t,20130401114837,0.08,N,0,N,1,0,0,0,0,0,0,0,0,,,,,,",
	);

$nl = '
';

// get voca terms
global $term;
$term = ocs_get_all_terms();

//print_r( $header);
$idx = 0;
foreach( $package_info as $package) {
	$info = explode( ',', $package);

	// product type
	$type = $info[ $header['PrdType']];
	if ( ! isset( $term['PrdType'][$type])) {
		println( 'Invalid product type : ' . $type);
		continue;
	}

	$title = 'OLD ' . $info[ $header['Package Name']];

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $title)
		->fieldCondition('field_product_type', 'tid', $term['PrdType'][$type])
		->execute();

	if ( empty( $result)) {
		println( 'Add NEW product : ' . $title);
		$p = ocs_admin_get_new_node( 'simpleproductoffering');

		// product type
		$p->field_product_type['und'][0]['tid'] = $term['PrdType'][$type];

		// product name and description
		$p->title = $title;
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);
		println( 'Existing product : ' . $title);
	}

	$p->field_description['und'][0]['value'] = 'FCE: ' . $info[ $header['Package Name']] ;

	// product id
	$p->field_product_id['und'][0]['value'] = 'packet_package_' . $info[ $header['Package Type']];

	// short code
	$p->field_short_code['und'][0]['value'] = 'pp_' . $info[ $header['Package Type']];

	// bill type
	$p->field_billing_type['und'][0]['tid'] = $term['BillType']['Prepaid'];

	// market : default value (unitel)

	// customer type : personal (default)

	// customer sub type : personal 

	// expire date type
	$p->field_expire_date_type['und'][0]['tid'] = $term['PrdExpireDate']['Month'];

	// expire date
	$p->field_expire_date['und'][0]['value'] = '1';

	// product sub type
	$p->field_product_sub_type['und'][0]['tid'] = $term['PrdSubType']['Normal'];

	// customer sub type
	$p->field_customer_group_type['und'][0]['tid'] = $term['CustKdCd']['Personal'];

	node_save( $p);

	$counter = counter_info( 'packet_package');

	// check counter list
	check_counter_list( $p, $term['tpl_default_tree_mobile']['Counter'], $counter);

	// check subscription fee
	check_subscription_fee( $p, $term['tpl_default_tree_mobile']['nonusage_subscription_charge'], $info[ $header['Price']]);

	// check bonus
	check_subscription_bonus( $p, $term['tpl_default_tree_mobile']['nonusage_subscription_bonus'], $info[ $header['Package(MB)']], $counter);

	$idx ++;
	println('>> ' . $idx . ' << ============');
//	if ( $idx == 1) break;
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
		println( 'Existing ' . $str);
	}
	else {
		println( 'New ' . $str);
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
		printf( 'Add counter %s to the Existing counter list : %s', $counter->title, $p->title);
		println();
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



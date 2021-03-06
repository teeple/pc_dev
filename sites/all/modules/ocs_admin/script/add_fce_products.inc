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
'C,Mobile,Main,CDOPIN,61,Group,Prepaid,c4',
'Z,Mobile,Main,CPPS,40,Group,Prepaid,c5',
'K,Mobile,Main,VoIP 77 -2,voip_77_2,Personal,Prepaid,v1',
'J,Mobile,Main,VoIP 77-1,voip_77_1,Personal,Prepaid,v2',
'R,Mobile,Main,Second Tariff,28,Personal,Prepaid,s1',
'P,Mobile,Main,PPS Live Modem,16,Personal,Prepaid,p1',
'Q,Mobile,Main,Easy Tour,33,Personal,Prepaid,e1',
'S,Mobile,Main,New Life,4,Personal,Prepaid,n1',
'Y,Mobile,Main,ID,30,Personal,Prepaid,i2',
'E,Mobile,Main,DOPIN Valid 90 Days,34,Personal,Prepaid,d3',
'B,Mobile,Main,DOPIN,12,Personal,Prepaid,d4',
'M,Mobile,Main,Happy Life Valid 90 Days,27,Personal,Prepaid,h1',
'N,Mobile,Main,Happy Life,1,Personal,Prepaid,h2',
	);

$ah = array_flip( explode( ',', 'Purchasable Categories,Validity,Counter ID,Price,Min,Count,MB,Unit,Package Name,Short Code,SMS buy,SMS Number,Purchasable again?,Un-purchasable?,Is counter transferrable?,Recurring?,Comment,,,,'));

$ap_data = array(
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,-,1102,120GG,-,-,50,,PacketPackage_50,D1,Y,1415,Y,N,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,30,302,1000TG,-,-,50,,PurchasePackage_50M (Starter),B1,Y,1423,Y,N,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,30,302,3000TG,-,-,200,,PurchasePackage_200M (Ascend),B2,Y,1423,Y,N,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,30,302,12000TG,-,-,1024,,PurchasePackage_1G (Smart),B3,Y,1423,Y,N,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,30,54,19900TG,-,-,2000,,PurchasePackage_UnLmt (Unlimited),B4,Y,1423,N,N,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,30,302,0,-,-,1024,,NewYearPacket_1GB_1M,-,N,-,-,N,?,Y,temporary promotional,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,-,702,0,-,-,247,,PacketPackage247,-,Y,-,-,N,?,N,temporary promotional,,,,',
'N|Y|G|S|A|Z|X|M,1,67,1000TG,-,-,1024,,PacketPackageDaily,DATA,Y,1416,Y,N,?,N,expires on next day at 06:00am,,,,',
'N|Y|G|B|S|A|Z|X|C|M,7,1002,400GG,-,-,200,,PacketPackageGG_200,D2,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,3,1004,100GG,10,-,-,,FreeCallTimeGG_10,C1,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,7,1004,500GG,50,-,-,,FreeCallTimeGG_50,C2,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,1,1006,125GG,-,100,-,,FreeSmsGG_100,M1,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W,7,1006,300GG,-,500,-,,FreeSmsGG_500,M2,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|S|A|Z|X|M,1,68,1000TG,1440,-,-,,FreeCallTimeDaily,CALL,Y,1416,Y,N,?,N,expires on next day at 06:00am,,,,',
'N|Y|G|S|A|Z|X|M,1,69,1000TG,-,500,-,,FreeSmsDaily,SMS,Y,1416,Y,N,?,N,expires on next day at 06:00am,,,,',
'N|Y|G|S|A|Z|X|M,30,2104,2000TG,20,-,-,,CallTimeMonthly20_1,M1,Y,1416,Y,N,?,N,,,,,',
',,1606,,-,200,-,,SmsMonthly200_1,,,,,,?,,,,,,',
'N|Y|G|S|A|Z|X|M,30,2104,3000TG,30,-,-,,CallTimeMonthly30_2,M2,Y,1416,Y,N,?,N,,,,,',
',,1606,,-,300,-,,SmsMonthly300_2,,,,,,?,,,,,,',
'N|Y|G|S|A|Z|X|M,30,2104,5000TG,100,-,-,,CallTimeMonthly100_3,C1,Y,1416,Y,N,?,N,,,,,',
',,1606,,-,100,-,,SmsMonthly100_3,,,,,,?,,,,,,',
'N|Y|G|S|A|Z|X|M,30,2104,10000TG,300,-,-,,CallTimeMonthly300_4,C2,Y,1416,Y,N,?,N,,,,,',
',,1606,,-,300,-,,SmsMonthly300_4,,,,,,?,,,,,,',
'N|Y|G|B|S|A|Z|X|C|M,5,1004,300GG,30,-,-,,FreeCallTimeGG_30,C3,Y,1415,N,Y,?,N,,,,,',
'N|Y|G|B|S|A|Z|X|C|M,4,1006,200GG,-,300,-,,FreeSmsGG_300,M3,Y,1415,N,Y,?,N,,,,,',
'-,30,-,150GG,-,-,-,,Free_CRBT,V1,Y,1415,N,N,?,N,,,,,',
'-,30,-,150GG,-,-,-,,Free_MCL,V2,Y,1415,N,N,?,N,,,,,',
'B|C|E|F|A|D|G|M|N|R|S|X|Y|Z,1,1404,0,30,-,-,,Birthday_Call,-,N,-,N,N,?,N,happens once a year (promotional),,,,',
',,1106,,-,30,-,,Birthday_Sms,,,,,,?,,,,,,',
',,502,,-,-,30,,Birthday_Data,,,,,,?,,,,,,',
'?,30,-,1200TG,-,-,-,,CRBTMonthly_1,M1,Y,1456,Y,N,?,Y,,,,,',
'?,90,-,3000TG,-,-,-,,CRBTMonthly_3,M3,Y,1456,Y,N,?,Y,,,,,',
'?,180,-,5500TG,-,-,-,,CRBTMonthly_6,M6,Y,1456,Y,N,?,Y,,,,,',
'?,360,-,10000TG,-,-,-,,CRBTMonthly_12,M12,Y,1456,Y,N,?,Y,,,,,',
',3,-,50GG,,,,,UrgooCinema,B1,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,BayanUlgii_StarCinema,K4,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Darkhan_StarCinema,K1,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Darkhan_DDKaraoke,K2,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Khovd_AmusementPark,K5,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Khovd_SwimmingPool,K6,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Khovd_Cinema,K7,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,Zavkhan_Cinema,K8,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,MongolianPaintballCommittee,P1,Y,1415,N,Y,?,N,once a day,,,,',
',3,-,50GG,,,,,AmusementPark_Automat,B3,Y,1415,N,Y,?,N,once a day,,,,',
',3,,50GG,,,,,AmusementPark_ScaryHouse,B7,Y,1415,N,Y,?,N,once a day,,,,',
',-,-,0TG,,,,,Minii nutag (VPN),<zip code>,,1441,N,Y,?,N,,,,,',
',-,,0,,,,,Uloan,<amount>,,1444,N,N,?,N,upto 1000TG,,,,',
',-,,0,,,,,Unit_Transfer(PS to PPS),<phno>,,1444,Y,N,?,Y,upto 10000TG can be transferred,,,,',
',,,550TG,,,,,Close 5 /family&friends/,<PhoneNumber>,Y,1445,Y,N,?,N,Send free messages upto 4 members,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,3,,,,3,,,Call Me,<PhoneNumber>,N,1447,N,Y,?,Y,"Sends "Call me" messages to specified numbers for free until next Recharge",,,,',
',-,,50TG,-,-,-,,U-Media_enable,on2,Y,1433,N,Y,?,Y,Umedia service,,,,',
',-,-,0,-,-,-,,U-Media_disable,off2,Y,1433,N,Y,?,Y,Umedia service,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,,,50TG,,,,,NumberSearch_PS,d <4digits>,Y,101010,Y,N,?,N,Search available post numbers,,,,',
'N|Y|G|B|S|A|Z|X|C|E|F|M|W|Q,,,50TG,,,,,NumberSearch_PPS,u <4digits>,Y,,Y,N,?,N,Search available Prepaid numbers,,,,',
',,,,,,,,VoiceGreeting,,Y,1435,,,?,,,,,,',
',,,,,,,1500TG,DopinStar,-,N,1443,Y,Y,?,N,Recharges selected phone with 1500 unit| Every time Owner recharges dopin phone with 15|000,,,,',
',,,350TG,,,,,ID_couple,Xoc 350| Xoc <PhoneNumber>,Y,1441,N,N,?,N,Detailed information here,,,,',
'Y,1,-,250TG,,40,,,ID_SMS_Package_onnet,250,Y,1441,N,N,?,N,Detailed information here,,,,',
'Y,1,-,300TG,,40,,,ID_SMS_Package_offnet,300,Y,1441,N,N,?,N,Detailed information here,,,,',
'Z,30,,10000TG,,,,,ONNET_VOICE /CPPS only/,10000,Y,1441,N,N,?,N,Detailed information here,,,,',
',,,50TG,,,,,Jokes,0,Y,2012,Y,N,?,N,,,,,',
',,,50TG,,,,,Greetings,1,Y,2012,Y,N,?,N,,,,,',
',,,50TG,,,,,Fortune Teller,9,Y,2012,Y,N,?,N,,,,,',
',,,50TG,,,,,Horoscope,<birthday>,Y,101010,Y,N,?,N,,,,,',
',,,50TG,,,,,Hair cut day,0,Y,101010,Y,N,?,N,,,,,',
',,,50TG,,,,,Love Letters & Short Poems,Single Letter,Y,247,Y,N,?,N,,,,,',
',-,,0,,,,,GroupSMS,,,172288,Y,N,?,Y,,,,,',
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

		// happy life
		'1' => array(	
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
			),
			// happy life 90 days
		'27' => array(	
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
					),
				),
			),
			// DOPIN
		'12' => array(	
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '200000', '209999'),
					array( '88', '300000', '309999'),
					array( '88', '400000', '409999'),
					array( '88', '600000', '609999'),
					array( '88', '700000', '709999'),
					array( '89', '690000', '699999'),
					array( '89', '890000', '999999'),
					array( '86', '600000', '699999'),
					array( '88', '120000', '999999'),
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
					),
				),
				/*
				Special: 8820,8830,8840,8860,8870,8969,8989-8999,8660-8669
				Normal: 8812-8899 
				8912-8929, 8935-8938, 8940, 8942-8948, 8950-8958, 8960-8968, 8970-8976, 8978, 8980-8987, 
				8612-8659, 8670-8699
				*/
			),
			// DOPIN 90 days
		'34' => array(	
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '200000', '299999'),
					array( '88', '300000', '399999'),
					array( '88', '400000', '499999'),
					array( '88', '600000', '699999'),
					array( '88', '700000', '799999'),
					array( '89', '690000', '699999'),
					array( '89', '890000', '999999'),
					array( '86', '600000', '699999'),
					array( '88', '120000', '999999'),
					array( '89', '120000', '299999'),
					array( '89', '350000', '389999'),
					array( '89', '400000', '409999'),
					array( '89', '420000', '489999'),
					array( '89', '420000', '489999'),
					array( '89', '500000', '589999'),
					array( '89', '600000', '689999'),
					array( '89', '700000', '769999'),
					array( '89', '780000', '789999'),
					array( '89', '800000', '879999'),
					array( '86', '120000', '599999'),
					array( '86', '700000', '999999'),
					),
				),
				/*
				Special: 8820,8830,8840,8860,8870,8969,8989-8999,8660-8669
				Normal: 8812-8899 
				8912-8929, 8935-8938, 8940, 8942-8948, 8950-8958, 8960-8968, 8970-8976, 8978, 8980-8987, 
				8612-8659, 8670-8699
				*/
			),
			// CPPS
		'40' => array(	
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '120000', '199999'),
					array( '88', '210000', '229999'),
					array( '88', '240000', '299999'),
					array( '88', '310000', '399999'),
					array( '88', '410000', '499999'),
					array( '88', '610000', '699999'),
					array( '88', '710000', '879999'),
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
					),
				),
					/*
					8812-8899 (not included:8823, 8820, 8830, 8840, 8860, 8870, 8888)
					8912-8929, 8935-8938, 8940, 8942-8948, 8950-8958, 8960-8968, 8970-8976, 8978, 8980-8987,
					8612-8659, 8670-8699
					*/
			),			// CDOPIN
		'61' => array(	
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '200000', '209999'),
					array( '88', '300000', '309999'),
					array( '88', '400000', '409999'),
					array( '88', '600000', '609999'),
					array( '88', '700000', '709999'),
					array( '89', '690000', '699999'),
					array( '89', '890000', '999999'),
					array( '86', '600000', '699999'),
					array( '88', '120000', '999999'),
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
					),
				),
			),

			// PPS live modem
		'16' => array(	
			'attribute_allowed_prefix' => array(
				'type' => 'prdattributeprefixrangeallowed',
				'value' => array( 
					array( '88', '230000', '239999'),
					array( '89', '410000', '419999'),
					),
				),
					/*
					8823, 8941
					*/
			),
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

// main product category list
$main_product_category = array();

//print_r( $header);
$idx = 0;
foreach( $data as $item) {
	$d = explode( ',', $item);

	$prd_id = $d[$h['id']];
	$title = $d[$h['name']];

	$main_product_category[$d[$h['category']]] = $title;

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
	unset( $p->field_exclusiveness_others['und']);

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
		add_tariff_plan( $p, $type);
	}

}

return;

// add VAS, Additional Product
foreach( $ap_data as $item) {
	$d = explode( ',', $item);

	$title = $d[$ah['Package Name']];
	$title_a = explode( ' ', $title);
	$prd_id = strtolower( $title_a[0]);

	if ( !empty( $arg_product_id) && $prd_id != $arg_product_id ) 
		continue;

	// find the product
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->propertyCondition('title', $title)
		->execute();

	if ( empty( $result)) {
		printf( "Add NEW product : %s %s\n", $title, $prd_id);
		$p = ocs_admin_get_new_node( 'simpleproductoffering');

		// product name and description
		$p->title = $title;
	}
	else {
		$nid = array_pop( array_keys( $result['node']));
		$p = node_load( $nid);
		printf( "Existing product : %s %s\n", $title, $prd_id);
	}

	$p->field_product_type['und'][0]['tid'] = $term['prdtype']['Additional'];
	$p->field_description['und'][0]['value'] = t( 'FCE PPS Package @t @c', 
				array( '@t' => $title, '@c' => $d[$ah['Comment']]));

	// product id
	$p->field_product_id['und'][0]['value'] = $prd_id;

	// short code
	$p->field_short_code['und'][0]['value'] = substr( $d[$ah['Short Code']], 0, 8);

	// bill type
	$p->field_billing_type['und'][0]['tid'] = $term['billtype']['Prepaid'];

	// market : default value (unitel)

	// customer type : personal (default)
	$p->field_customer_type['und'][0]['tid'] = $term['custdvcd']['Personal'];

	// customer sub type : personal 

	// customer sub type

	// expire date
	$validity = $d[$ah['Validity']];
	if ( is_numeric( $validity)) {
		$p->field_expire_date_type['und'][0]['tid'] = $term['prdexpiredate']['Day'];
		$p->field_expire_date['und'][0]['value'] = $validity;
	}


	// add counter
	$counter_id = $d[$ah['Counter ID']];
	$counter = get_counter( $counter_id);
	if ( $counter ) {
		$node = get_attr( $p, 'prdcounterlist', $term['tpl_default_tree_mobile']['counter'], 'PrdCounterList');
		$node->field_counter_list['und'][0]['nid'] = $counter->nid;
		node_save( $node);
		printf("  add counter : %s\n", $counter->title);

		$node = get_attr( $p, 'treenodecounter', $term['tpl_default_tree_mobile']['counter_main'], NULL,
				array( array( 'field_ref_counter', 'nid', $counter->nid)));
		$node->field_ref_counter['und'][0]['nid'] = $counter->nid;
		$node->field_main_or_accumulated['und'][0]['tid'] = $term['countermainoraccu']['Main'];
		$node->field_startdate_option1['und'][0]['tid'] = $term['specialdateoptions']['Now'];
		$node->field_enddate_option1['und'][0]['tid'] = $term['specialenddateoptions']['Unlimited'];
		$node->field_unlimited_threshold['und'][0]['value'] = 0;
		node_save( $node);
		printf("  attach counter to charging : %s\n", $counter->title);

	}

	// price
	$price = $d[$ah['Price']];
	if ( is_numeric( $price) || empty($price)) {
		$unit = 'TG';
		$amount = empty($price) ? 0 : $price;
	}
	else {
		$unit = substr( $price, -2);
		$amount = substr( $price, 0, -2);
	}

	if ( $unit == 'GG') {
		$p->field_point_for_subscription['und'][0]['value'] = $amount;
		printf("  price : %s GG\n", $amount);
	}
	else {
		$charge = get_attr( $p, 'actionpricechargeonetime', $term['tpl_default_tree_mobile']['nonusage_subscription_charge'], 'Charge '. $amount);
		$charge->field_price_amount_float['und'][0]['value'] = $amount;
		node_save( $charge);
		printf("  price : %s TG\n", $amount);

		unset( $p->field_point_for_subscription);

		if ( substr( $p->title, 0, strlen( 'PurchasePackage_UnLmt')) == 'PurchasePackage_UnLmt') {
			// for unlimited product
			// add data tariff plan
			$tariffplan = add_tariff_plan( $p, 'data');

			// add 100% discount
			$node = get_attr_cond( 'actionpricediscountfactors', '100%discount', array(
						array( 'field_ref_product', 'nid', $p->nid),
						array( 'field_ref_tree_tid', 'value', $term['tpl_default_tree_mobile']['treeNodeCustomDiscount']),
						array( 'field_ref_tree_nid', 'nid', $tariffplan->nid),
						));
			$node->field_ref_product['und'][0]['nid'] = $p->nid;
			$node->field_ref_tree_tid['und'][0]['value'] = $term['tpl_default_tree_mobile']['treeNodeCustomDiscount'];
			$node->field_ref_tree_nid['und'][0]['nid'] = $tariffplan->nid;
			$node->field_discount_['und'][0]['value'] = 100;
			$node->title = 'discount 100%';
			node_save( $node);

			printf("  discount 100 %%\n");
		}
		else if ( $counter) {
			foreach( array( 'Min', 'Count', 'MB', 'Unit') as $unit) {
				$amount = $d[$ah[$unit]];
//				printf("  %s %s\n", $unit, $amount);
				if ( !empty($amount) && is_numeric( $amount)) {
					if ( $unit == 'MB') $amount *= 1024*1024;
					else if ( $unit == 'Min') $amount *= 60;

					$node = get_attr_cond( 'actionsetcounter', 'ActionSetCounter', array(
						array( 'field_ref_counter', 'nid', $counter->nid),
						array( 'field_ref_source_action', 'nid', $charge->nid),
						));
					$node->field_ref_counter['und'][0]['nid'] = $counter->nid;
					$node->field_ref_source_action['und'][0]['nid'] = $charge->nid;
					$node->field_amount['und'][0]['value'] = $amount;
					$node->field_add_or_replace['und'][0]['tid'] = $term['counterset_addorreplace']['Add'];
					$node->field_startdate_option1['und'][0]['tid'] = $term['specialdateoptions']['Now'];

					if ( is_numeric( $validity)) {
						$node->field_enddate_option1['und'][0]['tid'] = $term['specialenddateoptions']['+ N Date(D,W,M,Y)'];
						$node->field_enddate_option3['und'][0]['value'] = $validity;
						$node->field_enddate_option4['und'][0]['tid'] = $term['unitofmeasure_enddate']['Day'];
					}
					else {
						$node->field_enddate_option1['und'][0]['tid'] = $term['specialenddateoptions']['Unlimited'];
					}

					node_save( $node);
					printf("  set subscription bonus %d %s\n", $amount, $unit);
				}
			}
		};
	}
		 

	node_save( $p);

	// set exclusiveness
	$category_list = explode( ',', 'X,W,O,I,G,F,D,A,C,Z,K,J,R,P,Q,S,Y,E,B,M,N');
	$purchase_category = $d[$ah['Purchasable Categories']];
	$result = array_diff( $category_list, explode( '|', $purchase_category));
	foreach( $result as $category) {
		$nids = ocs_get_nodes_by_title( 'simpleproductoffering', $main_product_category[$category]);
		if ( empty( $nids)) {
			printf("  Main product %s for category %s not found\n", $main_product_category[$category], $category);
		}
		else if ( count( $nids) > 1) {
			printf("  Too many main products %s for category %s : %d\n", $main_product_category[$category], $category, count( $nids));
		}
		else {
			if ( strlen( $purchase_category) > 0 && $purchase_category != '-') {
				$product = node_load( $nids[0]);
				$product->field_exclusiveness_others['und'][] = array( 'nid' => $p->nid);
				node_save( $product);
				printf("  Exclusive to main product %s\n", $product->title);
			}
		}
	}
}

function add_tariff_plan( $product, $type)
{
	$tariffplan_name = $product->field_product_id['und'][0]['value'] . '_' . $type . '_2013-01-01';
	$tariffplan = get_attr( $product, 'tariffplan', $term['tpl_default_tree_mobile']['usage_' . $type], $tariffplan_name);

	$tariffplan->field_tree_child_voca_name['und'][0]['value'] = 'tpl_tariffplan_' . $type;
	$tariffplan->field_valid_date_ymd['und'][0] = array(
			'value' => '2013-01-01 00:00:00',
			'timezone' => 'Asia/Ulaanbaatar',
			'timezone_db' => 'Asia/Ulaanbaatar',
			'date_type' => 'datetime',
			);
	$tariffplan->field_valid_date_hour['und'][0]['value'] = '00';

	node_save( $tariffplan);

	return $tariffplan;
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



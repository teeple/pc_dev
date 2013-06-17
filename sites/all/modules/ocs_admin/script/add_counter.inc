<?php

$h = "Counter ID,Total Users,Counter Name,Explanation";
$counter = array(
'0,789086,Remains,bundle_code 51 ????',
'1,4963,FreeRemains,',
'2,8695,PacketPackage,',
'3,72699,FreeGprs,',
'4,59955,FreeCallTime,',
'5,0,FreeVideoCallTime,',
'6,72022,FreeSms,',
'7,17884,FreeMms,',
'8,86627,FreeCrbt,',
'11,990225,TotalUsedMoney,',
'12,274882,UsedFreeCallTime,',
'13,0,UsedFreeVideoCallTime,',
'14,253913,UsedFreeSms,',
'15,942082,UsedSmsPerDay,',
'23,298723,AttemptOfCall,',
'24,946687,TotalRflMoney,',
'25,946690,TotalRflCount,',
'26,934524,RefillMoneyPerDay,',
'27,934539,RefillCntPerDay,',
'28,4741,UnitTransferAday,',
'42,287433,TotalUnitTransferMon,',
'44,925626,LoyaltyPoint,Loyalty Point Campaigne. Main Counter. Need to implement and migrate.',
'45,437190,RefillMoneyPerMon,',
'46,910108,ActivationDays,Loyalty Point Campaigne. Activation days Counter. Need to implement and migrate.',
'47,288043,LoyaltyMonthFlag,Loyalty Point Campaigne',
'48,999766,LoyaltyFlag,Loyalty Point Campaigne',
'53,395781,LoyaltyPointOnMon,Loyalty Point Campaigne',
'54,5956,PacketPackageLmtl,Bundle_code 18',
'57,8124,OnCard2Flag,"Ongoing Promotion. 365 days, 100 tug target users\' Flag indicator."',
'58,109515,packetExhaustSmsFlag,"Need to ask to Uangel. This Flag indicates that when Package finishes, the noti SMS sent 1 time."',
'59,356855,UpibMsgFlag,Need to ask Uangel. This Flag indicates that the provision was sent once to BS.',
'64,1852,StarUbb,Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule',
'65,459,UbbCounter2,Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule',
'67,26811,PacketPackageDaily,bundle_code 83',
'68,44482,FreeCallTimeDaily,bundle_code 81',
'69,10261,FreeSmsDaily,bundle_code 82',
'104,405866,FreeCallTimeBorLt,"Ongoing BOR Promotion. Now used for BOR of 3,18,43, 6, 19, 44 cardtypes. Need to implement in PC."',
'247,32022,Valentine247SMS,"Bundle_code 79, 92. Ongoing Promotion. It is the Flag that indicates SMS 100% discount from  Voice Couple discount."',
'249,180479,Bor4ReconnFlag,"bundle_code 63. Bor4Reconn Promo, Finishes on 30th June."',
'250,197911,Bor4Msg,"Bor4Reconn Promo, Finishes on 30th June."',
'251,11364,Bu30Min,Ongoing Promotion. Used for Nauriz Promo until the end of 2013. naurizubb_condition2.rule',
'301,754,FreeRemainsE,churnprotect deer ashiglaj baigaa. Just need to migrate. No expire time. ',
'302,41563,PacketPackageP,"bundle_code 15, 16, 17, 55, 56, 57, 58"',
'306,123356,FreeSmsFF,"bor_promotion, FF members Bonus SMS"',
'401,594,FreeRemainsRur,"? 2012 on duustal 12, 14, 16, 25, geh met Rural card-uudad ugch baisan. Just need to migrate.",Yuc h gesen haagaad uzne charging deer¡¦',
'502,101218,PacketPackageBD,bundle_code 33. Dopin Birthday Bonus with 1 day expire time',
'504,7795,FreeCallTimeBor,BOR-t bsan odoo bhgui bna. Just need to migrate. No expire time.',
'506,4160,FreeSmsBor,"24, 26, 27 cardtype-uudad ugch baisan. Just need to migrate. No expire time."',
'601,5170,FreeRemainsOnCard2,"365 udur, 100 tug uramshuulal. Ongoing Promotion."',
'702,19037,PacketPackage247,"Bundle_code 80, 93. No Expire time."',
'704,1071,FreeCallTimeFriday,Odoo hurtel hereglegchiin dansand bna. Just need to migrate. No expire time. Onnet.',
'706,2785,FreeSmsFriday,Odoo hurtel hereglegchiin dansand bna. Just need to migrate. No expire time. Onnet.',
'801,60935,FreeRemainsMoon,"Bundle_code 76, 77, 78. 7 days Expire time. Onnet Voice, SMS. Tsagaan Sariin Kartniih."',
'901,92132,FreeRemains21,Bor4Reconn. Ongoing Promotion. 14 days expire time.',
'1002,4459,PacketPackageGG,"Bundle_code 61, 96."',
'1004,50642,FreeCallTimeGG,"Bundle_code 10, 11, 59, 94."',
'1006,37542,FreeSmsGG,"Bundle_code 12, 13, 60, 95."',
'1102,22127,PacketPackageGG2,"Bundle_code 14, 62."',
'1106,99983,FreeSmsBD,Bundle_code 32. Dopin Bday.',
'1404,95202,FreeCallTimeBD,Bundle_code 31. Dopin Bday.',
'1406,27,FreeSmsBU,ub_rural.rule Finished on April 31st. Counter expires 90 days. Just need to migrate.',
'1606,1826,FreeSmsMonthly,"Bundle_code 85, 87, 89, 91"',
'1706,1085,FreeSms818,Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC.',
'2104,670,FreeCallTimeMonthly,"Bundle_code 84, 86, 88, 90. Expire days 30."',
'2204,353,FreeCallTime818,Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC.',
	);

global $user;

$term = array();
$term['counter_type'] = ocs_get_terms_tid( 'countertype');

foreach( $counter as $data) {
	$d = explode( ',', $data);
	$name = $d[2];
	$nids = ocs_get_nodes_by_title( 'counter', $name);
	if ( empty( $nids)) {
		$node = ocs_admin_get_new_node('counter');
		printf( "New Counter %s\n", $name);
		$node->title = $name;
	}
	else if ( count( $nids) == 1) {
		$node = node_load( $nids[0]);
		printf("Existing counter : %s\n", $name);
	}
	else {
		printf("%d counters are found with name %s\n", count( $nids), $name);
		return;
	}

	$node->field_description['und'][0]['value'] = $d[3];
	$node->field_counter_id['und'][0]['value'] = $d[0];
	$node->field_counter_type['und'][0]['tid'] = ($d[0]<10) ? $term['counter_type']['Basic'] : $term['counter_type']['Optional'];

	node_save( $node);

}

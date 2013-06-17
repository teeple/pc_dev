<?php

$h = array_flip( explode( '|', 'Counter ID|Total Users|Counter Name|Explanation|Billing Type|Counter Type|Scale|Service Domain|Unit Type|Counter Group|Default Usage Type|Comment'));

$counter = array(
'2|8695|PacketPackage||Prepaid|Basic|1|Mobile|Byte|Packet_Package|packet|',
'3|72699|FreeGprs||Prepaid|Basic|1|Mobile|Byte|Free_gprs|packet|',
'6|72022|FreeSms||Prepaid|Basic|1|Mobile|Count|Free_sms|sms|',
'7|17884|FreeMms||Prepaid|Basic|1|Mobile|Count|Free_mms|mms|',
'8|86627|FreeCrbt||Prepaid|Basic|1|Mobile|Count|Free_crbt|crbt|',
'14|253913|UsedFreeSms||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'15|942082|UsedSmsPerDay||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'23|298723|AttemptOfCall||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'25|946690|TotalRflCount||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'27|934539|RefillCntPerDay||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'28|4741|UnitTransferAday||Prepaid|Optional|1|Mobile|Count|Usage|-|',
'42|287433|TotalUnitTransferMon||Prepaid|Optional|1|Mobile|Money|Usage||money type에 scale이 1로 설정되어있음. 마이그레이션 시 확인 필요',
'44|925626|LoyaltyPoint|Loyalty Point Campaigne. Main Counter. Need to implement and migrate.|Prepaid|Optional|1|Mobile|Point|Point|loyalty_point_deduct|',
'46|910108|ActivationDays|Loyalty Point Campaigne. Activation days Counter. Need to implement and migrate.|Prepaid|Optional|1|Mobile|Count|HISTORY|-|"In CBS, ActivationDays will be calcurated based on now - creation day for subscription. so it does\'t need to migrate. (UNITEL)"',
'47|288043|LoyaltyMonthFlag|Loyalty Point Campaigne|Prepaid|Optional|1|Mobile|Count|History|-|',
'48|999766|LoyaltyFlag|Loyalty Point Campaigne|Prepaid|Optional|1|Mobile|Count|History|-|',
'53|395781|LoyaltyPointOnMon|Loyalty Point Campaigne|Prepaid|Optional|1|Mobile|Point|Usage|-|',
'54|5956|PacketPackageLmtl|Bundle_code 18|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'57|8124|OnCard2Flag|"Ongoing Promotion. 365 days, 100 tug target users\' Flag indicator."|Prepaid|Optional|1|Mobile|Count|History|-|',
'58|109515|packetExhaustSmsFlag|"Need to ask to Uangel. This Flag indicates that when Package finishes, the noti SMS sent 1 time."|Prepaid|Optional|1|Mobile|Count|History|-|',
'59|356855|UpibMsgFlag|Need to ask Uangel. This Flag indicates that the provision was sent once to BS.|Prepaid|Optional|1|Mobile|Count|History|-|',
'64|1852|StarUbb|Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule|Prepaid|Optional|1|Mobile|Count|Usage||',
'65|459|UbbCounter2|Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule|Prepaid|Optional|1|Mobile|Count|Usage||',
'67|26811|PacketPackageDaily|bundle_code 83|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'69|10261|FreeSmsDaily|bundle_code 82|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'247|32022|Valentine247SMS|"Bundle_code 79, 92. Ongoing Promotion. It is the Flag that indicates SMS 100% discount from  Voice Couple discount."|Prepaid|Optional|1|Mobile|Count|History|-|',
'249|180479|Bor4ReconnFlag|"bundle_code 63. Bor4Reconn Promo, Finishes on 30th June."|Prepaid|Optional|1|Mobile|Count|History|-|',
'250|197911|Bor4Msg|"Bor4Reconn Promo, Finishes on 30th June."|Prepaid|Optional|1|Mobile|Count|History|-|Need to check unit type and counter group for this counter (UNITEL)',
'251|11364|Bu30Min|Ongoing Promotion. Used for Nauriz Promo until the end of 2013. naurizubb_condition2.rule|Prepaid|Optional|1|Mobile|Count|History|-|Need to check unit type and counter group for this counter (UNITEL)',
'302|41563|PacketPackageP|"bundle_code 15, 16, 17, 55, 56, 57, 58"|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'306|123356|FreeSmsFF|"bor_promotion, FF members Bonus SMS"|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'502|101218|PacketPackageBD|bundle_code 33. Dopin Birthday Bonus with 1 day expire time|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'506|4160|FreeSmsBor|"24, 26, 27 cardtype-uudad ugch baisan. Just need to migrate. No expire time."|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'702|19037|PacketPackage247|"Bundle_code 80, 93. No Expire time."|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'706|2785|FreeSmsFriday|Odoo hurtel hereglegchiin dansand bna. Just need to migrate. No expire time. Onnet.|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'1002|4459|PacketPackageGG|"Bundle_code 61, 96."|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'1006|37542|FreeSmsGG|"Bundle_code 12, 13, 60, 95."|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'1102|22127|PacketPackageGG2|"Bundle_code 14, 62."|Prepaid|Optional|1|Mobile|Byte|Packet_Package|packet|',
'1106|99983|FreeSmsBD|Bundle_code 32. Dopin Bday.|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'1406|27|FreeSmsBU|ub_rural.rule Counter is valid till AUG 2|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'1606|1826|FreeSmsMonthly|"Bundle_code 85, 87, 89, 91"|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'1706|1085|FreeSms818|Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule. No expire time. Just need to migrate.|Prepaid|Optional|1|Mobile|Count|Free_sms|sms|',
'4|59955|FreeCallTime||Prepaid|Basic|10|Mobile|Sec|Free_calltime|voice|',
'5|0|FreeVideoCallTime||Prepaid|Basic|10|Mobile|Sec|Free_calltime|voice|',
'12|274882|UsedFreeCallTime||Prepaid|Optional|10|Mobile|Sec|Usage|-|',
'13|0|UsedFreeVideoCallTime||Prepaid|Optional|10|Mobile|Sec|Usage|-|',
'68|44482|FreeCallTimeDaily|bundle_code 81|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'104|405866|FreeCallTimeBorLt|"Ongoing BOR Promotion. Now used for BOR of 3,18,43, 6, 19, 44 cardtypes. Need to implement in PC."|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'504|7795|FreeCallTimeBor|BOR-t bsan odoo bhgui bna. Just need to migrate. No expire time.|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'704|1071|FreeCallTimeFriday|Odoo hurtel hereglegchiin dansand bna. Just need to migrate. No expire time. Onnet.|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'1004|50642|FreeCallTimeGG|"Bundle_code 10, 11, 59, 94."|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'1404|95202|FreeCallTimeBD|Bundle_code 31. Dopin Bday.|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'1904|1664|FreeCallTimeBU|ub_rural.rule Counter is valid till AUG 2|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'2104|670|FreeCallTimeMonthly|"Bundle_code 84, 86, 88, 90. Expire days 30."|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'2204|353|FreeCallTime818|Ongoing Nauriz Promotion until the end of 2013. Need to implement in PC. naurizubb_bonus.rule. No expire time. Just need to migrate.|Prepaid|Optional|10|Mobile|Sec|Free_calltime|voice|',
'0|789086|Remains|bundle_code 51 ????|Prepaid|Basic|1000|Mobile|Money|Remains|All|',
'1|4963|FreeRemains||Prepaid|Basic|1000|Mobile|Money|Free_remains|"voice,sms,crbt,pcket,mms,vas_daily"|"Need to check vas_daily (non usage) (UANGEL)',
'11|990225|TotalUsedMoney||Prepaid|Optional|1000|Mobile|Money|Usage|-|',
'24|946687|TotalRflMoney||Prepaid|Optional|1000|Mobile|Money|Usage|-|',
'26|934524|RefillMoneyPerDay||Prepaid|Optional|1000|Mobile|Money|Usage|-|',
'45|437190|RefillMoneyPerMon||Prepaid|Optional|1000|Mobile|Money|Usage|-|',
'301|754|FreeRemainsE|churnprotect deer ashiglaj baigaa. Just need to migrate. No expire time. |Prepaid|Optional|1000|Mobile|Money|Free_remains|"voice,sms,packet,crbt "|',
'401|594|FreeRemainsRur|"? 2012 on duustal 12, 14, 16, 25, geh met Rural card-uudad ugch baisan. Just need to migrate."|Prepaid|Optional|1000|Mobile|Money|Free_remains|"voice,sms,packet,crbt,idd,vas_daily"|"Need to check idd,vas_daily"',
'601|5170|FreeRemainsOnCard2|"365 udur, 100 tug uramshuulal. Ongoing Promotion."|Prepaid|Optional|1000|Mobile|Money|Free_remains|"voice,sms"|',
'801|60935|FreeRemainsMoon|"Bundle_code 76, 77, 78. 7 days Expire time. Onnet Voice, SMS. Tsagaan Sariin Kartniih."|Prepaid|Optional|1000|Mobile|Money|Free_remains|"voice,sms"|',
'901|92132|FreeRemains21|Bor4Reconn. Ongoing Promotion. 14 days expire time.|Prepaid|Optional|1000|Mobile|Money|Free_remains|"voice,sms,crbt,pcket,mms,vas_daily"|Need to check vas_daily',
);

global $user;

$term = array();

$term_list = array( 'countertype', 'scale_type', 'counterunit', 'countergroup');
foreach( $term_list as $name) {
	$term[$name] = ocs_get_terms_tid( $name);
}

foreach( $counter as $data) {
	$d = explode( '|', $data);

	$name = $d[$h['Counter Name']];
	$nids = ocs_get_nodes_by_title( 'counter', $name);
	if ( empty( $nids)) {
		$node = ocs_admin_get_new_node('counter');
		printf( "New Counter %s\n", $name);
		$node->title = $name;
	}
	else if ( count( $nids) == 1) {
		$node = node_load( $nids[0]);
		printf("Existing counter : %s nid=%d\n", $name, $node->nid);
	}
	else {
		printf("%d counters are found with name %s\n", count( $nids), $name);
		return;
	}

	/*
	printf( "counter type = %s, %s\n", $h['Counter Type'], $d[$h['Counter Type']]);
	printf( "scale type = %s, %s\n", $h['Scale'], $d[$h['Scale']]);
	print_r( $term['counter_type']);
	print_r( $term['scale_type']);
	*/
	print_r( $term['counterunit']);
	printf( "unit type = %s, %s\n", $h['Unit Type'], $d[$h['Unit Type']]);

	print_r( $term['countergroup']);
	printf( "counter group = %s, %s\n", $h['Counter Group'], $d[$h['Counter Group']]);

	$node->field_description['und'][0]['value'] = substr( $d[$h['Explanation']], 0, 60);
	$node->field_counter_id['und'][0]['value'] = $d[$h['Counter ID']];
	$node->field_counter_type['und'][0]['tid'] = $term['countertype'][$d[$h['Counter Type']]];
	$node->field_scale['und'][0]['tid'] = $term['scale_type'][$d[$h['Scale']]];
	$node->field_counter_unit_type['und'][0]['tid'] = $term['counterunit'][$d[$h['Unit Type']]];
	$group = strtoupper( $d[$h['Counter Group']]);
	$node->field_counter_group['und'][0]['tid'] = $term['countergroup'][$group];

	node_save( $node);

}

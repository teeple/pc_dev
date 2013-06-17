<?php

$data = array(
'Domestic|Airport_1128_PSTN|9761128',
'Domestic|G-MOBILE|97693,97697,97698',
'Domestic|G-Mobile_53_WLL|97653',
'Domestic|G-Mobile_78_VOIP|97678',
'Domestic|GOV_9200|9769200',
'Domestic|Gov_5126_PSTN|9765126',
'Domestic|Gov_6226_VOIP|9766226',
'Domestic|Incomnet_1181_PSTN|9761181',
'Domestic|MOBICOM|97699,97695,97694',
'Domestic|Mobicom_55_WLL|9765515,9765525',
'Domestic|Mobinet_75_VOIP|97675',
'Domestic|MTC_PSTN|97601,97670,976113,976116,976114',
'Domestic|MTC_50_PSTN|97650',
'Domestic|Railway_PSTN|97602,9762125,9762124',
'Domestic|Sky_76_VOIP|97676',
'Domestic|SKYTEL|97691,97696',
'Domestic|UNITEL|97688,97686,97689',
'Domestic|Univision_77_VOIP|97677',
'Domestic|MonSat_79_VOIP|97679',
'International|003_Mobi_Garts|003',
'International|001_MTC_Garts|001',
'International|005_Ray_Garts|005',
'International|002_Skytel_Garts|002',
'International|008_Unitel_Garts|008',
'International|1668_Unitel_Garts|9761668',
'International|1687_Mglcom_Garts|9761687',
'International|SMS (International)|976008',
);

global $user;

$term = array();

$term_list = array( 'prefix_type');
foreach( $term_list as $name) {
	$term[$name] = ocs_get_terms_tid( $name);
}

foreach( $data as $item) {
	$d = explode( '|', $item);

	$name = $d[1];
	$nids = ocs_get_nodes_by_title( 'carrier_mobile', $name);
	if ( empty( $nids)) {
		$node = ocs_admin_get_new_node('carrier_mobile');
		printf( "New Carrier %s\n", $name);
		$node->title = $name;
	}
	else if ( count( $nids) == 1) {
		$node = node_load( $nids[0]);
		printf("Existing Carrier : %s nid=%d\n", $name, $node->nid);
	}
	else {
		printf("%d Carrier are found with name %s\n", count( $nids), $name);
		return;
	}

	$node->field_ref_prefix_type['und'][0]['tid'] = $term['prefix_type'][$d[0]];
	unset( $node->field_prefix_multiple['und']);
	$pfx_list = explode( ',', $d[2]);
	foreach( $pfx_list as $pfx) {
		$node->field_prefix_multiple['und'][] = array( 'value' => $pfx);
	}
	node_save( $node);
}

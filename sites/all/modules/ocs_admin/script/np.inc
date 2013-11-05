<?php

$np2 = node_load( 265027);	// voip
/*
foreach( $np2->field_ref_idd_ratinggroup['und'] as $nid) {
	node_delete( $nid['nid']);
}
*/
unset( $np2->field_ref_idd_ratinggroup['und']);

$rg_list = array();

$np = node_load( 132088);
foreach( $np->field_ref_idd_ratinggroup['und'] as $nid) {
	$rg = node_load( $nid['nid']);
	printf("%s %s\n", $rg->title, $rg->field_rating_group['und'][0]['value']);

	$nids = ocs_get_nids_by_cond( 'idd_ratinggroup', array(
		array( 'field_ref_numberingplan_idd', 'nid', 265027),
		array( 'field_rating_group', 'value', $rg->field_rating_group['und'][0]['value'])));
	if ( count( $nids) == 1) {
		$idd = node_load( $nids[0]);
		printf("existing rating group %s\n", $rg->field_rating_group['und'][0]['value']);
		$rg_list[] = array( 'nid' => $nids[0]);
	}
	else if ( count( $nids) == 0) {
		$idd = ocs_admin_get_new_node( 'idd_ratinggroup');
		$idd->field_prefix = $rg->field_prefix;
		$idd->field_ref_numberingplan_idd['und'][0]['nid'] = 265027;
		$idd->field_rating_group = $rg->field_rating_group;
		$idd->field_area_name = $rg->field_area_name;
		$idd->field_service_type_of_provider['und'][0]['tid'] = 409;
		$idd->field_ref_carrier_mobile = $rg->field_ref_carrier_mobile;
		node_save( $idd);
		printf("new rating group %s\n", $rg->field_rating_group['und'][0]['value']);
		$rg_list[] = array( 'nid' => $idd->nid);
	}
	else {
		printf(">> ERROR\n");
		exit;
	}
}

$np2->field_ref_idd_ratinggroup['und'] = $rg_list;
node_save( $np2);

<?php

$nids = ocs_get_nids_by_cond( 'basicrate_idd', array(
			array( 'field_ref_tariffplan', 'nid', 177431),
			));

foreach( $nids as $nid) {
	$map = node_load( $nid);

	$rate = node_load( $map->field_ref_rate['und'][0]['nid']);

	$rg_nids = ocs_get_nids_by_cond( 'basicrate_idd', array( 
			array( 'field_ref_tariffplan', 'nid', 263962),
			array( 'field_rating_group', 'value', $map->field_rating_group['und'][0]['value']),
			array( 'field_ref_timetablefactors', 'nid', $map->field_ref_timetablefactors['und'][0]['nid']),
//			array( 'field_ref_tariffplan_idd_carrier', 'nid', $map->field_ref_tariffplan_idd_carrier['und'][0]['nid']),
			));

	printf( "%d %s %d %s\n", count( $rg_nids), $map->field_rating_group['und'][0]['value'], $rate->nid, $rate->title);
	/*
	foreach( $rg_nids as $nid) {
		$rg = node_load( $nid);
		printf("%d| %s %s:%s %s:%s\n", $nid, $rg->field_rating_group['und'][0]['value'],
				$rg->field_ref_timetablefactors['und'][0]['nid'],
				$map->field_ref_timetablefactors['und'][0]['nid'],
				$rg->field_ref_tariffplan_idd_carrier['und'][0]['nid'],
				$map->field_ref_tariffplan_idd_carrier['und'][0]['nid']);
	}
	*/

	if ( count( $rg_nids) > 1) {
		printf("  => Invalid\n");
	}
	else if ( count( $rg_nids) == 1) {
	}
	else {
		$ca = node_load( $map->field_ref_tariffplan_idd_carrier['und'][0]['nid']);

		$carrier_nids = ocs_get_nids_by_cond( 'tariffplan_idd_carrier', array(
			array( 'field_ref_tariffplan', 'nid', 263962),
			array( 'field_ref_carrier_mobile', 'nid', $ca->field_ref_carrier_mobile['und'][0]['nid']),
			array( 'field_ref_timetable_idd', 'nid', $ca->field_ref_timetable_idd['und'][0]['nid']),
			));

		$rate_nids = ocs_get_nids_by_cond( 'rate', array(
			array( 'property', 'title', $rate->title),
			array( 'field_ref_tariffplan', 'nid', 263962), 
			));
		if ( count( $rate_nids) == 1 && count($carrier_nids) == 1) {
			printf("  => mapping not found %d\n", count( $rate_nids));
			$rg = ocs_admin_get_new_node( 'basicrate_idd');
			$rg->field_ref_tariffplan['und'][0]['nid'] = 263962;
			$rg->field_rating_group = $map->field_rating_group;
			$rg->field_ref_timetablefactors = $map->field_ref_timetablefactors;
			$rg->field_ref_tariffplan_idd_carrier['und'][0]['nid'] = $carrier_nids[0];
			$rg->field_ref_rate['und'][0]['nid'] = $rate_nids[0];
			node_save( $rg);
		}
	}
}



<?php

$nids = ocs_get_nids_by_cond( 'rate', array());
foreach( $nids as $nid)
{
	$r = node_load( $nid);
	printf("%d %s\n", $nid, $r->title);

	if ( isset( $r->field_charge_collection['und'][0])) {
		$p = entity_load_single( 'field_collection_item', $r->field_charge_collection['und'][0]['value']);
		if ( $p->field_range_start['und'][0]['value'] != '0') {
			$t = node_load( $r->field_ref_tariffplan['und'][0]['nid']);
			printf(" --> Invalid rate 1 : %s %s\n", $p->field_range_start['und'][0]['value'], $t->title);
		}
	}
	if ( isset( $r->field_charge_collection['und'][1])) {
		$p = entity_load_single( 'field_collection_item', $r->field_charge_collection['und'][1]['value']);
		if ( $p->field_range_start['und'][0]['value'] != '60') {
			$t = node_load( $r->field_ref_tariffplan['und'][0]['nid']);
			printf(" --> Invalid rate 2 : %s %s\n", $p->field_range_start['und'][0]['value'], $t->title);
		}
	}
}

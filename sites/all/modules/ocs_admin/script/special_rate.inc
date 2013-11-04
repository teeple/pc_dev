<?php

$rate = array(
'10',
'13.63',
'14',
'18.18',
'20',
'25',
'27.27',
'30',
'36.36',
'40',
'45.45',
'50',
'90.9',
'118',
'136.36',
'181.18',
'181.81',
'200',
'227.23',
'227.27',
'227.72',
'230',
'250',
'254.54',
'272.27',
'272.72',
'272.73',
'281.81',
'300',
'309.09',
'318.18',
'327.27',
'350',
'354.54',
'360',
'363.36',
'363.63',
'381.81',
'409.09',
'409.9',
'418.18',
'445.45',
'450',
'454.45',
'454.54',
'500',
'550',
'636.36',
'807.27',
	);

foreach( $rate as $name) {
	$nids = ocs_get_nids_by_cond( 'numberspecialrate', array(
		array( 'property', 'title', $name),
		array( 'field_ref_numberspecial', 'nid', 261126),
		));

	if ( count( $nids) > 0) {
		foreach( $nids as $nid) {
		}
	}
	else {
		$r = ocs_admin_get_new_node('numberspecialrate');
		$r->title = $name;
		$r->field_ref_numberspecial['und'][0]['nid'] = 261126;
		$r->field_ref_tree_tid['und'][0]['value'] = 1873;
		$r->field_connection_fee['und'][0]['value'] = $name;
		$r->field_rating_group['und'][0]['value'] = $name;
		node_save( $r);
		printf("Add new node : %s\n", $name);
	}
}

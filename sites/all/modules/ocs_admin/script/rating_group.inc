<?php

/*
$nids= ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
			array('field_ref_roaming_plan', 'nid', 178198)));
			*/
$nids= ocs_get_nids_by_cond( 'roaming_ratinggroup', array(
			array('field_ref_roaming_plan', 'nid', 177431)));

$c = count( $nids);
printf("%d records\n", count( $nids));

foreach( $nids as $nid) {
	$node = node_load( $nid);
	$rg = $node->field_rating_group['und'][0]['value'];
	printf("%d] rating group %s %s\n", $c--, $node->title, $rg);
	$node->field_ref_roaming_plan['und'][0]['nid'] = 93491;
	node_save( $node);
}



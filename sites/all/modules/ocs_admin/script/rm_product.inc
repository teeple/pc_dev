<?php
require_once( 'script_common.inc');

// check argument
$prd_id = NULL;
$prd_id = drush_shift();
/*
while( $arg = drush_shift()) {
	if ( $arg == 'f') 
}
*/

if ( $prd_id == NULL) {
	printf( "Usage: <product id>\n");
	return;
}

if ( $prd_id == 'all') {
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', 'simpleproductoffering')
		->execute();

	if ( empty( $result)) {
		printf("No products are found\n");
	}
	else {
		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);
			printf( "Remove product : %s\n", $node->title);
			rm_product( $node->field_product_id['und'][0]['value']);
		}
	}
}
else {
	printf( "Remove product : %s\n", $prd_id);
	rm_product( $prd_id);
}

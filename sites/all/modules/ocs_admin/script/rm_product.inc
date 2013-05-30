<?php
require( 'script_common.inc');

// check argument
$prd_id = NULL;
$prd_id = drush_shift();
/*
while( $arg = drush_shift()) {
	if ( $arg == 'f') 
}
*/

if ( $prd_id == NULL) {
	println( 'Usage: <product id>');
	return;
}

println( 'Remove product : '. $prd_id);

// find the product
$query = new EntityFieldQuery();
$result = $query->entityCondition('entity_type', 'node')
	->entityCondition('bundle', 'simpleproductoffering')
	->fieldCondition('field_product_id', 'value', $prd_id)
	->execute();

if ( empty( $result)) {
	println( 'Product not found: '. $prd_id);
	return;
}

$idx = 0;
foreach( array_keys( $result['node']) as $nid) {
	$p = node_load( $nid);
	println( 'Remove Product : ' . $p->title);

	// dump all of its child node
	$view = views_get_view('list_product_child_node');
	$view->set_display('panel_pane_3');
	$view->set_arguments(array('0' => $p->nid));
	$view->execute();

	foreach($view->result as $record){
		$childNode = node_load($record->nid);

		switch( $childNode->type) {
			case 'tariffplan' :
				break;
			default:
				delChildAction( $childNode);
				break;
		}

		node_delete( $record->nid);
		printf( "  %s  %s\n", $childNode->type, $childNode->title);
	}

	node_delete( $p->nid);
}


function delChildAction( $child)
{
	$actionSetView = views_get_view('query_actionset_children');
	$actionSetView->set_display('panel_pane_1');
	$actionSetView->set_arguments(array('0' => $child->nid));
	$actionSetView->execute();

	foreach($actionSetView->result as $actionSetRecord){
		$targetActionSetNode = node_load($actionSetRecord->nid);

		$type = $child->type . ':' . $targetActionSetNode->type;
		printf( "  %s  %s\n", $type, $childNode->title);
		
		node_delete( $actionSetRecord->nid);
	}
}

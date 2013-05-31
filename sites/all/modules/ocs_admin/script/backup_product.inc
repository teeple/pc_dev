<?php

require( 'script_common.inc');

// check argument
$fname = NULL;
$fname = drush_shift();
$prd_id = drush_shift();

if ( $fname == NULL) {
	println( 'Usage: <file name> [product_id]');
	return;
}

println( 'Backup to file:'. $fname);

// open file
$fp = fopen( $fname, 'w+');
if ( $fp === FALSE) {
	println( 'Fail to write file '. $fname);
	return;
}


global $term;
$term = ocs_get_all_terms();
fwriteln( $fp, '# term');
fwriteln( $fp, serialize( $term));

// find the product
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
	->entityCondition('bundle', 'simpleproductoffering');

if ( ! empty( $prd_id)) {
	$query->fieldCondition( 'field_product_id', 'value', $prd_id);
}

$result = $query->execute();

$idx = 0;
foreach( array_keys( $result['node']) as $nid) {
	$p = node_load( $nid);
	println( 'Product : ' . $p->title);

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
				writeChildAction( $fp, $childNode);
				break;
		}

		printf( "  %s:%s\n", $childNode->type, $childNode->title);
		fwriteln( $fp, '# ' . $childNode->type . ':data' );
		fwriteln( $fp, serialize( $childNode));
	}

	fwriteln( $fp, '# ' . $p->type);
	fwriteln( $fp, serialize( $p));
}

fclose($fp);


function writeChildAction( $fp, $child)
{
	$actionSetView = views_get_view('query_actionset_children');
	$actionSetView->set_display('panel_pane_1');
	$actionSetView->set_arguments(array('0' => $child->nid));
	$actionSetView->execute();

	foreach($actionSetView->result as $actionSetRecord){
		$targetActionSetNode = node_load($actionSetRecord->nid);

		$type = $child->type . ':' . $targetActionSetNode->type;
		printf( "  %s:%s\n", $type, $childNode->title);
		fwriteln( $fp, '# '. $type);
		fwriteln( $fp, serialize( $targetActionSetNode));
	}
}

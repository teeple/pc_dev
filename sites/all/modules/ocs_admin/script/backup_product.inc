<?php

// check argument
$fname = NULL;
$fname = drush_shift();
$prd_id = drush_shift();

if ( $fname == NULL) {
	printf( "Usage: <file name> [product_id]\n");
	return;
}

printf( "Backup to file:%s/%s\n", DRUPAL_ROOT, $fname);

// open file
$fp = fopen( $fname, 'w+');
if ( $fp === FALSE) {
	printf( "Fail to write file:%s\n", $fname);
	return;
}


global $term;
$term = ocs_get_all_terms();
fwrite( $fp, "# term\n");
fwrite( $fp, serialize( $term)."\n");

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
	printf( "Product : %s\n", $p->title);

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
		fwrite( $fp, '# ' . $childNode->type . ":data\n" );
		fwrite( $fp, serialize( $childNode)."\n");
	}

	fwrite( $fp, '# ' . $p->type . "\n");
	fwrite( $fp, serialize( $p)."\n");
    $idx ++;
}

fclose($fp);
printf( "\nBackup finished\n");
printf( "  Number of products : %d\n", $idx); 
printf( "  Backup file        : %s/%s\n", DRUPAL_ROOT, $fname);


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
		fwrite( $fp, '# '. $type."\n");
		fwrite( $fp, serialize( $targetActionSetNode)."\n");
	}
}

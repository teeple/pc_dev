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

// backup taxonomy
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'taxonomy_term');
$result = $query->execute();

printf( "Backup Taxonomy\n");
$voca = array();
foreach( array_keys( $result['taxonomy_term']) as $tid) {
	$p = taxonomy_term_load( $tid);
	$voca[ $p->vocabulary_machine_name][$p->tid] = $p;
}
fprintf( $fp, "# taxonomy\n");
fprintf( $fp, "%s\n", serialize( $voca));


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

	$childList = array();
	foreach($view->result as $record){
		$childList[] = $record->nid;
	}

	foreach( $childList as $nid) {
		$childNode = node_load($nid);

		switch( $childNode->type) {
			case 'tariffplan' :
				break;
			default:
				writeChildAction( $fp, $childNode);
				break;
		}

		printf( "  %d:%s:%s\n", $childNode->nid, $childNode->type, $childNode->title);
		fprintf( $fp, "# tree_tid:%d:%s\n", $childNode->field_ref_tree_tid['und'][0]['value'], $childNode->type);
		fprintf( $fp, "%s\n", serialize( $childNode));

		while( isset($childNode->field_parent_node['und'])) {
			$parentNid = $childNode->field_parent_node['und'][0]['nid'];
			if ( array_search( $parentNid, $childList) !== FALSE) break;

			// save parent node
			$childNode = node_load( $parentNid);
			printf( "    %d:%s:%s\n", $childNode->nid, $childNode->type, $childNode->title);
			fprintf( $fp, "# parent:%d:%s\n", $childNode->nid, $childNode->type);
			fprintf( $fp, "%s\n", serialize( $childNode));
		}
	}

	fprintf( $fp, "# %s\n", $p->type);
	fprintf( $fp, "%s\n", serialize( $p));
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
		printf( "    %s:%s\n", $type, $childNode->title);
		fprintf( $fp, "# action:%d:%s\n", $child->nid, $type);
		fprintf( $fp, "%s\n", serialize( $targetActionSetNode));
	}
}

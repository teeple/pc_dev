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

backupTaxonomy( $fp);

// backup other node types
$node_list = array(
 'carrier_mobile',
 'numberingplan_domestic',
 'domestic_ratinggroup',
 'timetable',
 'timetablefactors',
 'timetablefactorsslot',
 'unittransfer',
 'unittransferfactor',
 'counter',
 'lifecyclescheme',
 'ocs_account_state',
 'ocs_events',
 'ocs_global_config',
 'ocs_message_group',
 'ocs_messages',
 'ocs_param',
 'ocs_state_machine',
 'ocs_svc_perm',
 'ocs_transition_actions',
 );

foreach( $node_list as $type) {
	backupNodes( $fp, $type);
}

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
	printf( "\nProduct : %s\n", $p->title);

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
				writeTariffPlan( $fp, $childNode);
				break;
			default:
				writeChildAction( $fp, $childNode);
				break;
		}

		printf( "  tree_tid:%d:%s:%s\n", $childNode->nid, $childNode->type, $childNode->title);
		fprintf( $fp, "# tree_tid:%d:%s\n", $childNode->field_ref_tree_tid['und'][0]['value'], $childNode->type);
		fprintf( $fp, "%s\n", serialize( $childNode));

		while( isset($childNode->field_parent_node['und'])) {
			$parentNid = $childNode->field_parent_node['und'][0]['nid'];
			if ( array_search( $parentNid, $childList) !== FALSE) break;

			// save parent node
			$childNode = node_load( $parentNid);
			printf( "    parent:%d:%s:%s\n", $childNode->nid, $childNode->type, $childNode->title);
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
		printf( "    action:%d:%s:%s\n", $child->nid, $type, $childNode->title);
		fprintf( $fp, "# action:%d:%s\n", $child->nid, $type);
		fprintf( $fp, "%s\n", serialize( $targetActionSetNode));
	}
}

function writeTariffPlan( $fp, $child)
{
	//create children for the new tariffplan
	//covers for basicrate_domestic, basicrate_idd, basicrate_data,basicrate_roaming,tariffplan_idd_carrier,rate content type        
	$view = views_get_view('query_tariffplan_children');
	$view->set_display('panel_pane_1');
	$view->set_arguments(array('0' => $child->nid));
	$view->execute(); 
	
	$basicRates = array();
	$newTariffplanIddCarriers = array();
	$newRates = array();
	
	foreach($view->result as $record){
		$targetChildNode = node_load($record->nid);

		$type = $targetChildNode->type;
		printf( "    tariff:%d:%s:%s\n", $targetChildNode->nid, $type, $targetChildNode->title);
		fprintf( $fp, "# tariff:%d:%s\n", $targetChildNode->nid, $type);
		fprintf( $fp, "%s\n", serialize( $targetChildNode));
	}

	//covers for actionpricechargefactors, actionpricediscountfactors, treenodespecialnumberscheme,
	//treenodepacketpredefined,treenodepacketdynamic,actionblockfactors, basicrate_data content type
	$view = views_get_view('query_tariffplan_children');
	$view->set_display('panel_pane_2');
	$view->set_arguments(array('0' => $child->nid));
	$view->execute(); 

	foreach($view->result as $record){
	   	$targetChildNode = node_load($record->nid);

		$type = $targetChildNode->type;
		printf( "    tariff_child:%d:%s:%s\n", $targetChildNode->nid, $type, $targetChildNode->title);
		fprintf( $fp, "# tariff_child:%d:%s\n", $targetChildNode->nid, $type);
		fprintf( $fp, "%s\n", serialize( $targetChildNode));
		
		/*
	   if(isset($targetChildNode->field_charge_collection)){
			_clone_field_collection('node',$targetChildNode,$childNode,'field_charge_collection');
	   }
	   if(isset($targetChildNode->field_discount_collection)){
			_clone_field_collection('node',$targetChildNode,$childNode,'field_discount_collection');
	   }
	   _clone_nested_child_node($targetChildNode,$childNode);
	   */
	}
}

function backupTaxonomy( $fp)
{
	// backup taxonomy
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'taxonomy_term');
	$result = $query->execute();

	printf( "\nBackup Taxonomy\n");
	$voca = array();
	foreach( array_keys( $result['taxonomy_term']) as $tid) {
		$p = taxonomy_term_load( $tid);
		$voca[ $p->vocabulary_machine_name][$p->tid] = $p;
	}
	fprintf( $fp, "# taxonomy\n");
	fprintf( $fp, "%s\n", serialize( $voca));
}

function backupNodes( $fp, $type)
{
	printf("\nBackup node type %s\n", $type);

	fprintf( $fp, "# node:0:%s\n", $type);
	fprintf( $fp, "%s\n", serialize("begin"));

	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
		->entityCondition('bundle', $type);

	$result = $query->execute();

	$idx = 0;
	if ( !empty( $result)) {

		foreach( array_keys( $result['node']) as $nid) {
			$node = node_load( $nid);

			printf( "  %s : %s\n", $node->type, $node->title);
			fprintf( $fp, "# node:%d:%s\n", $nid, $node->type);
			fprintf( $fp, "%s\n", serialize( $node));

			$idx ++;
		}
	}

	fprintf( $fp, "# node:0:%s\n", $type);
	fprintf( $fp, "%s\n", serialize("end"));

	printf("Node type:%s backuped nodes:%d\n", $type, $idx);
}

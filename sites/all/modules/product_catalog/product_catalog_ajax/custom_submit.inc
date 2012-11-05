<?php 
function product_catalog_ajax_custom_submit() {
	global $user;

	$type = $_POST['type'];
	$tariffplanNid = $_POST['tariffplanNid'];
	$selected_nid  = $_POST['selected_nid'];
		
	switch($type){
		case 'select_numberingplan_domestic':
			$tariffplanNode = node_load($tariffplanNid);
			$oldNumberingplanNid = isset($tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid'])
			? $tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid'] : NULL;
			$newNumberingplanNid = current($selected_nid);
			$tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid'] = $newNumberingplanNid;				
			node_save($tariffplanNode);
			
			if($oldNumberingplanNid == NULL || $oldNumberingplanNid != $newNumberingplanNid){
				_create_basicrate_node($type,$tariffplanNode);
			}
			break;
		case 'select_numberingplan_idd':
			$tariffplanNode = node_load($tariffplanNid);
			$oldNumberingplanNid = isset($tariffplanNode->field_ref_numberingplan_idd['und'][0]['nid'])
			? $tariffplanNode->field_ref_numberingplan_idd['und'][0]['nid'] : NULL;
			$newNumberingplanNid = current($selected_nid);
			$tariffplanNode->field_ref_numberingplan_idd['und'][0]['nid'] = $newNumberingplanNid;
			node_save($tariffplanNode);
				
			if($oldNumberingplanNid == NULL || $oldNumberingplanNid != $newNumberingplanNid){
				_create_basicrate_node($type,$tariffplanNode);
			}
			break;
		case 'select_timetable_domestic':
			$tariffplanNode = node_load($tariffplanNid);
			$oldTimetableNid = isset($tariffplanNode->field_ref_timetable_domestic['und'][0]['nid'])
							? $tariffplanNode->field_ref_timetable_domestic['und'][0]['nid'] : NULL;
			$newTimetableNid = current($selected_nid);
			$tariffplanNode->field_ref_timetable_domestic['und'][0]['nid'] = $newTimetableNid;			
			node_save($tariffplanNode);
			
			if($oldTimetableNid == NULL || $oldTimetableNid != $newTimetableNid){
				_create_basicrate_node($type,$tariffplanNode);
			}
			
			break;
		case 'select_timetable_idd':
			$tariffplanNode = node_load($tariffplanNid);
			$oldTimetableNid = isset($tariffplanNode->field_ref_timetable_idd['und'][0]['nid'])
								? $tariffplanNode->field_ref_timetable_idd['und'][0]['nid'] : NULL;
			$newTimetableNid = current($selected_nid);
			$tariffplanNode->field_ref_timetable_idd['und'][0]['nid'] = $newTimetableNid;				
			node_save($tariffplanNode);
			
			if($oldTimetableNid == NULL || $oldTimetableNid != $newTimetableNid){
				_create_basicrate_node($type,$tariffplanNode);
			}
			
			break;
	}
	
	$renderOutput = '';
	$output[] = $renderOutput;
	$output = ajax_render($output);

	print $output;
	exit;
}

function _create_basicrate_node($type,$tariffplanNode){
	global $user;
	
	switch($type){
		case 'select_timetable_domestic':
		case 'select_numberingplan_domestic':
			$targetTimetableFieldName = 'field_ref_timetable_domestic';
			$targetCreatedContentType = 'basicrate_domestic';
			$targetRatingGroupViewDisplay = 'panel_pane_1';
			$targetRatingGroupViewArgNid = array('0' => $tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid']);
			break;
		case 'select_timetable_idd':
		case 'select_numberingplan_idd':
			$targetTimetableFieldName = 'field_ref_timetable_idd';
			$targetCreatedContentType = 'basicrate_idd';
			$targetRatingGroupViewDisplay = 'panel_pane_2';
			$targetRatingGroupViewArgNid = array('0' => $tariffplanNode->field_ref_numberingplan_idd['und'][0]['nid']);
			break;
	}
	
	//delete old children
	$view = views_get_view('list_basicrate');
	$view->set_display('panel_pane_1');
	$view->set_arguments(array('0' => $targetCreatedContentType,'1' => $tariffplanNode->nid));
	$view->execute();
	$delNids = array();
		
	foreach($view->result as $item){
		$delNids[] = $item->nid;
	}
	
	node_delete_multiple($delNids);
	
	//add new children
	//1. search used rating group
	$ratingGroupView = views_get_view('list_ratinggroup');
	$ratingGroupView->set_display($targetRatingGroupViewDisplay);
	$ratingGroupView->set_arguments($targetRatingGroupViewArgNid);
	$ratingGroupView->execute();
	$ratingGroups = array();
	foreach($ratingGroupView->result as $item){
		$ratingGroups[] = $item->field_field_rating_group[0]['raw']['value'];
	}
	
	//2. search timetablefactors
	$evalStr = '$timetableNode = node_load($tariffplanNode->'.$targetTimetableFieldName.'[\'und\'][0][\'nid\']);';
	eval($evalStr);
	
	//3. create basicrate nodes
	foreach($ratingGroups as $ratingGroup){		
		foreach($timetableNode->field_ref_timetablefactors['und'] as $timetableFactor){
			
			$node = new StdClass();
			$node->uid = $user->uid;
			$node->language = 'und';
			$node->type = $targetCreatedContentType;
			$node->field_ref_tariffplan['und'][0]['nid'] = $tariffplanNode->nid;
			$node->field_ref_timetablefactors['und'][0]['nid'] = $timetableFactor['nid'];
			$node->field_basicrate_ratinggroup['und'][0]['value'] = $ratingGroup;
			node_save($node);				
		}
	}
}
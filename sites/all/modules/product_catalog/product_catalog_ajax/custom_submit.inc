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
				_create_domestic_basicrate_node($type,$tariffplanNode);
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
				_create_tariffplan_idd_carrier($tariffplanNode,$newNumberingplanNid);
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
				_create_domestic_basicrate_node($type,$tariffplanNode);
			}
			
			break;
        /*
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
         */        
	}
	
	$renderOutput = '';
	$output[] = $renderOutput;
	$output = ajax_render($output);

	print $output;
	exit;
}

function _create_tariffplan_idd_carrier($tariffplanNode,$newNumberingplanNid){
    global $user;
    $targetCreatedContentType = 'basicrate_idd';
    
    //delete old tariffplan_idd_carrier
    $tariffplanIddCarrierView = views_get_view('list_tariffplan_idd_carrier');
    $tariffplanIddCarrierView->set_display('panel_pane_1');
    $tariffplanIddCarrierView->set_arguments(array('0' => $tariffplanNode->nid));
    $tariffplanIddCarrierView->execute();
    
    $delNids = array();
    foreach($tariffplanIddCarrierView->result as $item){
        $delNids[] = $item->nid;
    }
    node_delete_multiple($delNids);
    
    //delete old basicrate
    _delete_all_basicrate_in_tariffplan_by_type($targetCreatedContentType,$tariffplanNode->nid);
    
    //find new carriers in numberingplan
    $carriersView = views_get_view('list_carriers_in_numberingplan_idd');
    $carriersView->set_display('panel_pane_1');
    $carriersView->set_arguments(array('0' => $newNumberingplanNid));
    $carriersView->execute();
    $carriers = array();
    foreach($carriersView->result as $record){
        $carriers[] = $record->node_field_data_field_ref_carrier_mobile_nid;
    }
    
    //create new tariffplan_idd_carrier
    $tariffplan_idd_carriers = array();
    foreach($carriers as $carrier){
        $tariffplanIddCarrierNode = new StdClass();
        $tariffplanIddCarrierNode->uid = $user->uid;
        $tariffplanIddCarrierNode->language = 'und';
        $tariffplanIddCarrierNode->type = 'tariffplan_idd_carrier';
        $tariffplanIddCarrierNode->field_ref_tariffplan['und'][0]['nid'] = $tariffplanNode->nid;
        $tariffplanIddCarrierNode->field_ref_carrier_mobile['und'][0]['nid'] = $carrier;
        node_save($tariffplanIddCarrierNode);   
        $tariffplan_idd_carriers[] = array('nid' => $tariffplanIddCarrierNode->nid);
    }
    $tariffplanNode = node_load($tariffplanNode->nid);
    $tariffplanNode->field_ref_tariffplan_idd_carrier['und'] = $tariffplan_idd_carriers;
    node_save($tariffplanNode);   
}

function _create_domestic_basicrate_node($type,$tariffplanNode){
	global $user;
	
	switch($type){
		case 'select_timetable_domestic':
		case 'select_numberingplan_domestic':
			$targetTimetableFieldName = 'field_ref_timetable_domestic';
            $targetCreatedContentType = 'basicrate_domestic';
			$targetQueryArgNid = array('0' => $tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid']);
            $targetQueryNumberingPlanType = 'numberingplan_domestic';
            $targetQueryJoinNumberingPlanTableName = 'field_data_field_ref_numberingplan_domestic';
            $targetQueryJoinNumberingPlanFieldName = 'field_ref_numberingplan_domestic_nid';
            $targetQueryRatingGroupType = 'domestic_ratinggroup';
			break;        
	}
	
	//delete old children	
	_delete_all_basicrate_in_tariffplan_by_type($targetCreatedContentType,$tariffplanNode->nid);
	
	//add new children
	//1. search used rating group
	$query = db_select('node', 'n');
    $query->condition('n.type', $targetQueryNumberingPlanType,'=');
    $query->condition('n.nid',$targetQueryArgNid,'=');
    $query->join($targetQueryJoinNumberingPlanTableName,'plan','n.nid = plan.'.$targetQueryJoinNumberingPlanFieldName);
    $query->condition('plan.bundle',$targetQueryRatingGroupType,'=');
    $query->join('field_data_field_rating_group','rg','plan.entity_id = rg.entity_id');
    $query->fields('rg',array('field_rating_group_value'));
    $query->distinct();
    $query->orderBy('rg.field_rating_group_value', 'ASC');
    
    $result = $query->execute();
    $ratingGroups = array();
    while($record = $result->fetchAssoc()) {
            $ratingGroups[] = current($record);
    } 
    
	//2. search timetablefactors
	$evalStr = '$timetableNode = node_load($tariffplanNode->'.$targetTimetableFieldName.'[\'und\'][0][\'nid\']);';
	eval($evalStr);    
	
	foreach($ratingGroups as $ratingGroup){		
		foreach($timetableNode->field_ref_timetablefactors['und'] as $timetableFactor){
			
			$node = new StdClass();
			$node->uid = $user->uid;
			$node->language = 'und';
			$node->type = $targetCreatedContentType;
			$node->field_ref_tariffplan['und'][0]['nid'] = $tariffplanNode->nid;
			$node->field_ref_timetablefactors['und'][0]['nid'] = $timetableFactor['nid'];
			$node->field_rating_group['und'][0]['value'] = $ratingGroup;
            $node->field_rating_group['und'][0]['safe_value'] = $ratingGroup;
			node_save($node);				
		}
	}    
}

function _delete_all_basicrate_in_tariffplan_by_type($targetCreatedContentType,$tariffplanNodeNid){
    $view = views_get_view('list_basicrate');
    $view->set_display('panel_pane_1');
    $view->set_arguments(array('0' => $targetCreatedContentType,'1' => $tariffplanNodeNid));
    $view->execute();
    $delNids = array();
        
    foreach($view->result as $item){
            
        $delNids[] = $item->nid;
    }
    
    node_delete_multiple($delNids);
}

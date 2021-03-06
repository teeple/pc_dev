<?php 

function _get_tariffplan_idd_carrier_by_carrier($tariffplan_nid,$carrier_nid){
  $tariffplan_idd_carrier_nodes = _get_tariffplan_idd_carrier_node($tariffplan_nid);
  foreach($tariffplan_idd_carrier_nodes as $tariffplan_idd_carrier_node_key => $tariffplan_idd_carrier_node_value){
    if($tariffplan_idd_carrier_node_value['carrier']['nid'] == $carrier_nid){
      return $tariffplan_idd_carrier_node_key;
    }
  }
}

function create_tariffplan_idd_carrier_by_carrier($numberingplan_nid,$carrier_nid,$node_nid){
  //find if carrier nid is new or not in the numberingplan
  $is_carrier_exist = _is_carrier_exist_in_numberingplan_idd($numberingplan_nid,$carrier_nid,$node_nid);
  if(!$is_carrier_exist){
    //find tariffplan which uses the numberingplan
    $tariffplans = _get_tariffplan_by_numberingplan_idd($numberingplan_nid);  
    foreach($tariffplans as $tariffplan_nid){
      //create new tariffplan_idd_carrier
      $tariffplan_node = node_load($tariffplan_nid);     
      _create_tariffplan_idd_carrier_by_carrier($tariffplan_node,$carrier_nid);
    }
  }
}

function _idd_ratinggroup_create_handler($form,$form_state){
  $node_nid = $form_state['values']['nid'];
  $numberingplan_nid = $form_state['values']['field_ref_numberingplan_idd']['und'][0]['nid'];
  $carrier_nid = $form_state['values']['field_ref_carrier_mobile']['und'][0]['nid'];
  
  create_tariffplan_idd_carrier_by_carrier($numberingplan_nid,$carrier_nid,$node_nid);
}

function _create_tariffplan_idd_carrier_by_carrier($tariffplan_node,$carrier_nid){
  global $user;
  
  $tariffplan_idd_carrier_node = new StdClass();
  $tariffplan_idd_carrier_node->uid = $user->uid;
  $tariffplan_idd_carrier_node->language = 'und';
  $tariffplan_idd_carrier_node->type = 'tariffplan_idd_carrier';
  $tariffplan_idd_carrier_node->field_ref_tariffplan['und'][0]['nid'] = $tariffplan_node->nid;
  $tariffplan_idd_carrier_node->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_nid;
  node_save($tariffplan_idd_carrier_node);   
  
  $tariffplan_idd_carriers = $tariffplan_node->field_ref_tariffplan_idd_carrier['und'];
  $tariffplan_idd_carriers[] = array('nid' => $tariffplan_idd_carrier_node->nid);
  
  $tariffplan_node = node_load($tariffplan_node->nid);
  $tariffplan_node->field_ref_tariffplan_idd_carrier['und'] = $tariffplan_idd_carriers;
  node_save($tariffplan_node);  
}

function _get_tariffplan_by_numberingplan_idd($numberingplan_nid){
  $tariffplans = array();
  $view_result = views_get_view_result('list_tariffplan', 'panel_pane_1', $numberingplan_nid);
  foreach($view_result as $item){
    $tariffplans[] = $item->nid;
  }
  return $tariffplans;
}

function _is_carrier_exist_in_numberingplan_idd($numberingplan_nid,$carrier_nid,$exclude_nid){
  $view_result = views_get_view_result('list_carrier_in_numberingplan_idd', 'panel_pane_1', $numberingplan_nid,$carrier_nid,$exclude_nid);
  if(count($view_result) > 0){
    return TRUE;
  }else{
    return FALSE;
  }
}

function _get_idd_ratinggroup_iin_tariffplan($numberingplan_nid,$carrier_nid){
  $query = db_select('field_data_field_rating_group', 'rg');
  $query->condition('rg.bundle', 'idd_ratinggroup','=');
  $query->join('field_data_field_ref_numberingplan_idd','idd','rg.entity_id = idd.entity_id');
  $query->condition('idd.field_ref_numberingplan_idd_nid',$numberingplan_nid,'=');
  $query->join('field_data_field_ref_carrier_mobile','carrier','rg.entity_id = carrier.entity_id');
  $query->condition('carrier.field_ref_carrier_mobile_nid',$carrier_nid,'=');
  $query->fields('rg',array('field_rating_group_value'));
  $query->distinct();
  $query->orderBy('rg.field_rating_group_value', 'ASC');
 
  $result = $query->execute();
  $ratingGroups = array();
  while($record = $result->fetchAssoc()) { 
    $rating_group = current($record);
    $ratingGroups[$rating_group] = $rating_group;
  } 
  
  return $ratingGroups;
}

function _get_roaming_ratinggroup_in_tariffplan($tariffplanNode){
  $targetCreatedContentType = 'basicrate_roaming';
  $targetQueryArgNid = array('0' => $tariffplanNode->field_ref_roaming_plan['und'][0]['nid']);
  
  //1. search used rating group
  $query = db_select('node', 'n');
  $query->condition('n.type', 'roaming_plan','=');
  $query->condition('n.nid',$targetQueryArgNid,'='); 
  $query->join('field_data_field_ref_roaming_plan','plan','n.nid = plan.field_ref_roaming_plan_nid');
  $query->condition('plan.bundle','roaming_ratinggroup','=');
  $query->join('field_data_field_rating_group','rg','plan.entity_id = rg.entity_id');
  $query->join('field_data_field_ref_roaming_type','roamingtype','plan.entity_id = roamingtype.entity_id');
  $query->join('taxonomy_term_data','term','roamingtype.field_ref_roaming_type_tid = term.tid');
  
  //filter ratinggroup based on usage type
  $vocaName = $tariffplanNode->field_tree_child_voca_name['und'][0]['value'];
  switch($vocaName){
      case 'tpl_tariffplan_voice':
          $allowedRoamingType = array('HPLMN','VPLMN','Other PLMN','Incoming');
          break;
      case 'tpl_tariffplan_sms':
          $allowedRoamingType = array('SMS Incoming','SMS Outgoing');
          break;
  }
  $query->condition('term.name',$allowedRoamingType,'in');
  $query->fields('rg',array('field_rating_group_value'));
  $query->distinct();
  $query->orderBy('rg.field_rating_group_value', 'ASC');
  
  $result = $query->execute();
  
  $ratingGroups = array();
  while($record = $result->fetchAssoc()) {
    $rating_group = current($record);
    $ratingGroups[$rating_group] = $rating_group;
  }   
  
  return $ratingGroups;
}

function _get_domestic_ratinggroup_in_tariff_plan($tariffplanNode){
  $ratingGroups = array();  
  
  $targetQueryArgNid = array('0' => $tariffplanNode->field_ref_numberingplan_domestic['und'][0]['nid']);
  $targetQueryNumberingPlanType = 'numberingplan_domestic';
  $targetQueryJoinNumberingPlanTableName = 'field_data_field_ref_numberingplan_domestic';
  $targetQueryJoinNumberingPlanFieldName = 'field_ref_numberingplan_domestic_nid';
  $targetQueryRatingGroupType = 'domestic_ratinggroup';
  
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
  
  while($record = $result->fetchAssoc()) {
    $rating_group = current($record);
    $ratingGroups[$rating_group] = $rating_group;
  }
  
  return $ratingGroups;
}

function _get_domestic_incoming_ratinggroup_in_tariff_plan($tariffplanNode){
  $ratingGroups = array();  
  
  $targetQueryArgNid = array('0' => $tariffplanNode->field_numberingplan_d_incoming['und'][0]['nid']);
  $targetQueryNumberingPlanType = 'numberingplan_domestic';
  $targetQueryJoinNumberingPlanTableName = 'field_data_field_ref_numberingplan_domestic';
  $targetQueryJoinNumberingPlanFieldName = 'field_ref_numberingplan_domestic_nid';
  $targetQueryRatingGroupType = 'domestic_ratinggroup';
  
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
  
  while($record = $result->fetchAssoc()) {
    $rating_group = current($record);
    $ratingGroups[$rating_group] = $rating_group;
  }
  
  return $ratingGroups;
}

function _get_timetablefactor($timetable_nid){
  $timetable_factor = array();
  
  $viewResult = views_get_view_result('list_timetablefactors', 'panel_pane_2', $timetable_nid);
  foreach($viewResult as $item){
    $timetable_factor[$item->node_field_data_field_ref_timetablefactors_nid] = $item->node_field_data_field_ref_timetablefactors_title;
  }
  
  return $timetable_factor;
}

function _create_mapped_basicrate_node_roaming($form,$form_state){
  global $user;
  $target_content_type = 'basicrate_roaming';
  
  //get requried info from form  
  $tariffplan_nid = $form_state['build_info']['args'][1];
  $ref_tree_tid = $form_state['build_info']['args'][2];
  $rate_nid = $form_state['values']['field_ref_rate']['und'][0]['nid'];
    
  $rating_groups = array();
  
  foreach($form_state['values']['field_map_rating_group']['und'] as $item){
    $rating_groups[] = $item['value'];
  }
    
  //get basicrate node already exist
  $already_exist_basic_rate_node = array();
  
  $view_result = views_get_view_result('list_basicrate', 'panel_pane_5', $tariffplan_nid);
  foreach($view_result as $item){
    $item_rating_group = $item->field_data_field_rating_group_field_rating_group_value;
    $already_exist_basic_rate_node[$item_rating_group] = $item->nid;
  }
 
  $delete_nids = array();
  
  //create new node or update
  foreach($rating_groups as $rating_group){
    if($rate_nid == NULL){
      if(isset($already_exist_basic_rate_node[$rating_group])){
        $delete_nids[] = $already_exist_basic_rate_node[$rating_group];
      }
    }else{
      if(isset($already_exist_basic_rate_node[$rating_group])){//update
        $node = node_load($already_exist_basic_rate_node[$rating_group]);
        $node->field_ref_rate['und'][0]['nid'] = $rate_nid; 
        node_save($node);  
      }else{//create
        $node = new StdClass();
        $node->uid = $user->uid;
        $node->language = 'und';
        $node->type = $target_content_type;
        $node->field_ref_tariffplan['und'][0]['nid'] = $tariffplan_nid;
        $node->field_rating_group['und'][0]['value'] = $rating_group;
        $node->field_rating_group['und'][0]['safe_value'] = $rating_group;
        $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
        node_save($node);  
      }  
    }
  }

  if(!empty($delete_nids)){
    node_delete_multiple($delete_nids);
  }
}

function _create_mapped_basicrate_node_idd($form,$form_state){
  global $user;
  $target_content_type = 'basicrate_idd';
  $tariffplan_idd_carrier_nid = $form_state['values']['field_ref_tariffplan_idd_carrier']['und'][0]['nid'];
  
  //get requried info from form  
  $tariffplan_nid = $form_state['build_info']['args'][1];
  $ref_tree_tid = $form_state['build_info']['args'][2];
  $rate_nid = $form_state['values']['field_ref_rate']['und'][0]['nid'];
    
  $rating_groups = array();
  $timetable_factors = array();
  
  foreach($form_state['values']['field_map_rating_group']['und'] as $item){
    $rating_groups[] = $item['value'];
  }
  
  foreach($form_state['values']['field_ref_timetablefactors']['und'] as $item){
    $timetable_factors[] = $item['nid'];
  }
  
  //get basicrate node already exist
  $already_exist_basic_rate_node = array();
  
  $view_result = views_get_view_result('list_basicrate', 'panel_pane_3', $tariffplan_nid);
  foreach($view_result as $item){
    $item_rating_group = $item->field_data_field_rating_group_field_rating_group_value;
    $item_timetable_factor =$item->_field_data['nid']['entity']->field_ref_timetablefactors['und'][0]['nid'];
    $already_exist_basic_rate_node[$item_rating_group][$item_timetable_factor] = $item->nid;
  }
 
  $delete_nids = array();
  
  //create new node or update
  foreach($rating_groups as $rating_group){
    foreach($timetable_factors as $timetable_factor){
      if($rate_nid == NULL){
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){
          $delete_nids[] = $already_exist_basic_rate_node[$rating_group][$timetable_factor];
        }
      }else{
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){//update
          $node = node_load($already_exist_basic_rate_node[$rating_group][$timetable_factor]);
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid; 
          node_save($node);  
        }else{//create
          $node = new StdClass();
          $node->uid = $user->uid;
          $node->language = 'und';
          $node->type = $target_content_type;
          $node->field_ref_tariffplan['und'][0]['nid'] = $tariffplan_nid;
          $node->field_ref_timetablefactors['und'][0]['nid'] = $timetable_factor;
          $node->field_rating_group['und'][0]['value'] = $rating_group;
          $node->field_rating_group['und'][0]['safe_value'] = $rating_group;
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
          $node->field_ref_tariffplan_idd_carrier['und'][0]['nid'] = $tariffplan_idd_carrier_nid;
          node_save($node);  
        }  
      }      
    }
  }

  if(!empty($delete_nids)){
    node_delete_multiple($delete_nids);
  }
}

function _create_mapped_basicrate_node_domestic($form,$form_state){
  global $user;
  $target_content_type = 'basicrate_domestic';
  
  //get requried info from form  
  $tariffplan_nid = $form_state['build_info']['args'][1];
  $ref_tree_tid = $form_state['build_info']['args'][2];
  $rate_nid = $form_state['values']['field_ref_rate']['und'][0]['nid'];
    
  $rating_groups = array();
  $timetable_factors = array();
  
  foreach($form_state['values']['field_map_rating_group']['und'] as $item){
    $rating_groups[] = $item['value'];
  }
  
  foreach($form_state['values']['field_ref_timetablefactors']['und'] as $item){
    $timetable_factors[] = $item['nid'];
  }
  
  //get basicrate node already exist
  $already_exist_basic_rate_node = array();
  
  $view_result = views_get_view_result('list_basicrate', 'panel_pane_2', $target_content_type, $tariffplan_nid);
  foreach($view_result as $item){
    $item_rating_group = $item->field_data_field_rating_group_field_rating_group_value;
    $item_timetable_factor =$item->_field_data['nid']['entity']->field_ref_timetablefactors['und'][0]['nid'];
    $already_exist_basic_rate_node[$item_rating_group][$item_timetable_factor] = $item->nid;
  }
 
  $delete_nids = array();
  
  //create new node or update
  foreach($rating_groups as $rating_group){
    foreach($timetable_factors as $timetable_factor){
      if($rate_nid == NULL){
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){
          $delete_nids[] = $already_exist_basic_rate_node[$rating_group][$timetable_factor];
        }
      }else{
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){//update
          $node = node_load($already_exist_basic_rate_node[$rating_group][$timetable_factor]);
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid; 
          node_save($node);  
        }else{//create
          $node = new StdClass();
          $node->uid = $user->uid;
          $node->language = 'und';
          $node->type = $target_content_type;
          $node->field_ref_tariffplan['und'][0]['nid'] = $tariffplan_nid;
          $node->field_ref_timetablefactors['und'][0]['nid'] = $timetable_factor;
          $node->field_rating_group['und'][0]['value'] = $rating_group;
          $node->field_rating_group['und'][0]['safe_value'] = $rating_group;
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
          node_save($node);  
        }  
      }      
    }
  }

  if(!empty($delete_nids)){
    node_delete_multiple($delete_nids);
  }
}

function _create_mapped_basicrate_node_domestic_incoming($form,$form_state){
  global $user;
  $target_content_type = 'basicrate_domestic_incoming';
  
  //get requried info from form  
  $tariffplan_nid = $form_state['build_info']['args'][1];
  $ref_tree_tid = $form_state['build_info']['args'][2];
  $rate_nid = $form_state['values']['field_ref_rate']['und'][0]['nid'];
    
  $rating_groups = array();
  $timetable_factors = array();
  
  foreach($form_state['values']['field_map_rating_group']['und'] as $item){
    $rating_groups[] = $item['value'];
  }
  
  foreach($form_state['values']['field_ref_timetablefactors']['und'] as $item){
    $timetable_factors[] = $item['nid'];
  }
  
  //get basicrate node already exist
  $already_exist_basic_rate_node = array();
  
  $view_result = views_get_view_result('list_basicrate', 'panel_pane_2', $target_content_type, $tariffplan_nid);
  foreach($view_result as $item){
    $item_rating_group = $item->field_data_field_rating_group_field_rating_group_value;
    $item_timetable_factor =$item->_field_data['nid']['entity']->field_ref_timetablefactors['und'][0]['nid'];
    $already_exist_basic_rate_node[$item_rating_group][$item_timetable_factor] = $item->nid;
  }
 
  $delete_nids = array();
  
  //create new node or update
  foreach($rating_groups as $rating_group){
    foreach($timetable_factors as $timetable_factor){
      if($rate_nid == NULL){
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){
          $delete_nids[] = $already_exist_basic_rate_node[$rating_group][$timetable_factor];
        }
      }else{
        if(isset($already_exist_basic_rate_node[$rating_group][$timetable_factor])){//update
          $node = node_load($already_exist_basic_rate_node[$rating_group][$timetable_factor]);
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid; 
          node_save($node);  
        }else{//create
          $node = new StdClass();
          $node->uid = $user->uid;
          $node->language = 'und';
          $node->type = $target_content_type;
          $node->field_ref_tariffplan['und'][0]['nid'] = $tariffplan_nid;
          $node->field_ref_timetablefactors['und'][0]['nid'] = $timetable_factor;
          $node->field_rating_group['und'][0]['value'] = $rating_group;
          $node->field_rating_group['und'][0]['safe_value'] = $rating_group;
          $node->field_ref_rate['und'][0]['nid'] = $rate_nid;
          node_save($node);  
        }  
      }      
    }
  }

  if(!empty($delete_nids)){
    node_delete_multiple($delete_nids);
  }
}

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
			  _delete_all_basicrate_in_tariffplan_by_type('basicrate_domestic',$tariffplanNode->nid);
			}
			break;
		case 'select_numberingplan_domestic_incoming':
			$tariffplanNode = node_load($tariffplanNid);
			$oldNumberingplanNid = isset($tariffplanNode->field_numberingplan_d_incoming['und'][0]['nid'])
			? $tariffplanNode->field_numberingplan_d_incoming['und'][0]['nid'] : NULL;
			$newNumberingplanNid = current($selected_nid);
			$tariffplanNode->field_numberingplan_d_incoming['und'][0]['nid'] = $newNumberingplanNid;				
			node_save($tariffplanNode);
			
			if($oldNumberingplanNid == NULL || $oldNumberingplanNid != $newNumberingplanNid){
			  _delete_all_basicrate_in_tariffplan_by_type('basicrate_domestic_incoming',$tariffplanNode->nid);
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
			  _delete_all_basicrate_in_tariffplan_by_type('basicrate_domestic',$tariffplanNode->nid);
			}
			break;
		case 'select_timetable_domestic_incoming':
			$tariffplanNode = node_load($tariffplanNid);
			$oldTimetableNid = isset($tariffplanNode->field_ref_timetable_domestic_inc['und'][0]['nid'])
							? $tariffplanNode->field_ref_timetable_domestic_inc['und'][0]['nid'] : NULL;
			$newTimetableNid = current($selected_nid);
			$tariffplanNode->field_ref_timetable_domestic_inc['und'][0]['nid'] = $newTimetableNid;			
			node_save($tariffplanNode);
			
			if($oldTimetableNid == NULL || $oldTimetableNid != $newTimetableNid){
			  _delete_all_basicrate_in_tariffplan_by_type('basicrate_domestic_incoming',$tariffplanNode->nid);
			}
			break;
    case 'select_roamingplan':
        $tariffplanNode = node_load($tariffplanNid);
        $oldRoamingplanNid = isset($tariffplanNode->field_ref_roaming_plan['und'][0]['nid'])
        ? $oldRoamingplanNid->field_ref_roaming_plan['und'][0]['nid'] : NULL;
        $newRoamingplanNid = current($selected_nid);
        $tariffplanNode->field_ref_roaming_plan['und'][0]['nid'] = $newRoamingplanNid;
        node_save($tariffplanNode);
            
        if($oldRoamingplanNid == NULL || $oldRoamingplanNid != $newRoamingplanNid){
          _delete_all_basicrate_in_tariffplan_by_type('basicrate_roaming',$tariffplanNode->nid);
        }
        break;
    }
	
	$renderOutput = '';
	$output[] = $renderOutput;
	$output = ajax_render($output);

	print $output;
	exit;
}

function _get_carriers_in_numbering_plan($numberingplan_nid){
  $carriersView = views_get_view('list_carriers_in_numberingplan_idd');
  $carriersView->set_display('panel_pane_1');
  $carriersView->set_arguments(array('0' => $numberingplan_nid));
  $carriersView->execute();
  $carriers = array();
  foreach($carriersView->result as $record){
    $carriers[$record->node_field_data_field_ref_carrier_mobile_nid] = $record->node_field_data_field_ref_carrier_mobile_title;
  }
  
  return $carriers;
}

function _get_tariffplan_idd_carrier_node($tariffplan_nid){
  $tariffplanIddCarrierView = views_get_view('list_tariffplan_idd_carrier');
  $tariffplanIddCarrierView->set_display('panel_pane_1');
  $tariffplanIddCarrierView->set_arguments(array('0' => $tariffplan_nid));
  $tariffplanIddCarrierView->execute();
  
  $nodes = array();
  foreach($tariffplanIddCarrierView->result as $item){
    $nodes[$item->nid] = array('carrier' => array('nid' => $item->field_field_ref_carrier_mobile[0]['raw']['nid'],
                                                  'name' => $item->field_field_ref_carrier_mobile[0]['rendered']['#markup']
                                            ),
                               'timetable' => array('nid' => $item->node_field_data_field_ref_timetable_idd_nid
                                              )
                         );
  }
  
  return $nodes;
}

function _create_tariffplan_idd_carrier($tariffplanNode,$newNumberingplanNid){
    global $user;
    $targetCreatedContentType = 'basicrate_idd';
    
    //delete old tariffplan_idd_carrier
    $tariffplan_idd_carriers = _get_tariffplan_idd_carrier_node($tariffplanNode->nid);
    
    foreach($tariffplan_idd_carriers as $key => $item){
      $delNids[] = $key;
    }
    node_delete_multiple($delNids);
    
    //delete old basicrate
    _delete_all_basicrate_in_tariffplan_by_type($targetCreatedContentType,$tariffplanNode->nid);
    
    //find new carriers in numberingplan
    $carriers = _get_carriers_in_numbering_plan($newNumberingplanNid);
    
    //create new tariffplan_idd_carrier
    $tariffplan_idd_carriers = array();
    foreach($carriers as $key => $value){
        $tariffplanIddCarrierNode = new StdClass();
        $tariffplanIddCarrierNode->uid = $user->uid;
        $tariffplanIddCarrierNode->language = 'und';
        $tariffplanIddCarrierNode->type = 'tariffplan_idd_carrier';
        $tariffplanIddCarrierNode->field_ref_tariffplan['und'][0]['nid'] = $tariffplanNode->nid;
        $tariffplanIddCarrierNode->field_ref_carrier_mobile['und'][0]['nid'] = $key;
        node_save($tariffplanIddCarrierNode);   
        $tariffplan_idd_carriers[] = array('nid' => $tariffplanIddCarrierNode->nid);
    }
    $tariffplanNode = node_load($tariffplanNode->nid);
    $tariffplanNode->field_ref_tariffplan_idd_carrier['und'] = $tariffplan_idd_carriers;
    node_save($tariffplanNode);   
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

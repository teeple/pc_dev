<?php
function product_catalog_form_node_delete($node){
	$childNodes = get_nested_children_nids($node->nid);

	switch($node->type){
		case 'simpleproductoffering':
			//상품 삭제시 cleanup 작업  
			//default basic counters
			//default attributes
			//tariff plan
			$view = views_get_view('list_product_child_node');
			$view->set_display('panel_pane_1');
			$view->set_arguments(array('0' => $node->nid));
			$view->execute();
			foreach($view->result as $item){
				$childNodes[] = $item->nid;
			}			
			break;
		case 'numberingplan_idd':
			//find idd_ratinggroup nodes
			if(!empty($node->field_ref_idd_ratinggroup)){
				foreach($node->field_ref_idd_ratinggroup['und'] as $child){
					$childNodes[] = $child['nid'];
				}
                unset($node->field_ref_idd_ratinggroup);
                node_save($node);
			}
			break;				
		case 'numberingplan_domestic':	
			//find domestic_ratinggroup nodes		
			if(!empty($node->field_ref_domestic_ratinggroup)){
				foreach($node->field_ref_domestic_ratinggroup['und'] as $child){
					$childNodes[] = $child['nid'];
				}
                unset($node->field_ref_domestic_ratinggroup);
                node_save($node);
			}
			break;	
        case 'roaming_plan':  
            if(!empty($node->field_ref_roaming_ratinggroup)){
                foreach($node->field_ref_roaming_ratinggroup['und'] as $child){
                    $childNodes[] = $child['nid'];
                }
                unset($node->field_ref_roaming_ratinggroup);
                node_save($node);
            }
            break;  
		case 'domestic_ratinggroup':
			// unlink numberingplan_domestic's link
			if(isset($node->field_ref_numberingplan_domestic['und'][0]['nid'])){
    			$parent = node_load($node->field_ref_numberingplan_domestic['und'][0]['nid']);				
    			$searchTargets = $parent->field_ref_domestic_ratinggroup['und'];
    			$totalSearchTargets = count($searchTargets);
    			for($i = 0; $i < $totalSearchTargets; $i++){
    				if($searchTargets[$i]['nid'] == $node->nid){
    					unset($searchTargets[$i]);
    					break;
    				}
    			}
    			$parent->field_ref_domestic_ratinggroup['und'] = $searchTargets;				
    			node_save($parent);			
            }
			break;	
		case 'idd_ratinggroup':
			// unlink numberingplan_idd's link
			if(isset($node->field_ref_numberingplan_idd['und'][0]['nid'])){
    			$parent = node_load($node->field_ref_numberingplan_idd['und'][0]['nid']);
    			$searchTargets = $parent->field_ref_idd_ratinggroup['und'];
    			$totalSearchTargets = count($searchTargets);
    			for($i = 0; $i < $totalSearchTargets; $i++){
    				if($searchTargets[$i]['nid'] == $node->nid){
    					unset($searchTargets[$i]);
    					break;
    				}
    			}
    			$parent->field_ref_idd_ratinggroup['und'] = $searchTargets;
    			node_save($parent);
            }
			break;
        case 'roaming_ratinggroup':
            if(isset($node->field_ref_roaming_plan['und'][0]['nid'])){
                $parent = node_load($node->field_ref_roaming_plan['und'][0]['nid']);
                $searchTargets = $parent->field_ref_roaming_ratinggroup['und'];
                $totalSearchTargets = count($searchTargets);
                for($i = 0; $i < $totalSearchTargets; $i++){
                    if($searchTargets[$i]['nid'] == $node->nid){
                        unset($searchTargets[$i]);
                        break;
                    }
                }
                $parent->field_ref_roaming_ratinggroup['und'] = $searchTargets;
                node_save($parent);
            }
            break;
		case 'timetable':
			//delete child nodes
			if(!empty($node->field_ref_timetablefactors)){
				foreach($node->field_ref_timetablefactors['und'] as $child){
					$childNodes[] = $child['nid'];
				}
			}
			$view = views_get_view('list_timetablefactorsslot');
			$view->set_display('panel_pane_1');
			$view->set_arguments(array('0' => $node->nid));
			$view->execute();
			
			foreach($view->result as $timetablefactorsslot){
				$childNodes[] = $timetablefactorsslot->nid;
			}
			
			break;
		case 'counter':
			//unittransfer view
			$unitTransferView = views_get_view('list_unittransfer');
			$unitTransferView->set_display('panel_pane_1');
			$unitTransferView->execute();
			$counterNode = $node;
			
			//카운터를 사용하는 다른 컨텐츠 들에 대한 처리도 해 주어야 할듯..상품같은..			
			//unit transfer			
			foreach($unitTransferView->result as $item){
				$unitTransferNode = node_load($item->nid);
				$unitTransferFactorsCount = count($unitTransferNode->field_ref_unittransferfactors['und']);
				for($i=0;$i<$unitTransferFactorsCount;$i++){
					$factorNode = node_load($unitTransferNode->field_ref_unittransferfactors['und'][$i]['nid']);
					if(isset($factorNode->field_ref_counter['und'][0]['nid'])){
						if($factorNode->field_ref_counter['und'][0]['nid'] == $counterNode->nid){
							node_delete($factorNode->nid);
							unset($unitTransferNode->field_ref_unittransferfactors['und'][$i]);
						}
					}
				}				
			}
					
			break;
	}
	
	$childNodes = array_unique($childNodes); 
	if(!empty($childNodes)){
		node_delete_multiple($childNodes);
	}
}

function _unlink_conditionfactors_from_sp_rule($param){

	$rule = node_load($param['rule_nid']);
	$condition_nid = $param['condition_nid'];

	if(isset($rule->field_ref_condition_factors)){
		$countLink = count($rule->field_ref_condition_factors['und']);
		for($i = 0;$i < $countLink ;$i++){
			if($rule->field_ref_condition_factors['und'][$i]['nid'] == $condition_nid){
				unset($rule->field_ref_condition_factors['und'][$i]);
				break;
			}
		}
	}

	$temp_path = current_path();
	$temp_path = explode('/conditions/',$temp_path);
	$redirect_path = $temp_path[0].'/edit';

	node_save($rule);
	node_delete($condition_nid);

	//redirect to previous page

	if(isset($redirect_path)){
		drupal_goto($redirect_path);
	}
}

function _unlink_conditionfactors_from_rule($param){
	$rule = node_load($param['rule_nid']);
	$condition_nid = $param['condition_nid'];

	if(isset($rule->field_ref_condition_factors)){
		$countLink = count($rule->field_ref_condition_factors['und']);
		for($i = 0;$i < $countLink ;$i++){
			if($rule->field_ref_condition_factors['und'][$i]['nid'] == $condition_nid){
				unset($rule->field_ref_condition_factors['und'][$i]);
				break;
			}
		}
	}

	$temp_path = current_path();
	$temp_path = explode('/conditions/',$temp_path);
	$redirect_path = $temp_path[0].'/edit';

	node_save($rule);

	node_delete($condition_nid);

	//redirect to previous page

	if(isset($redirect_path)){
		drupal_goto($redirect_path);
	}
}

function _unlink_actionpricefactor_from_sp_rule($param) {
	$rule = node_load($param['rule_nid']);

	switch($param['price_type']) {
		case 'CHARGE':
			$targetFieldName = 'field_ref_action_charge';
			break;
		case 'DISCOUNT':
			$targetFieldName = 'field_ref_action_discount';
			break;
		case 'ALLOWANCE':
			$targetFieldName = 'field_ref_action_allowance';
			break;
			break;
	}

	$command_search = '$search_items=$rule->'.$targetFieldName.'[\'und\'];';
	eval($command_search);

	$searchItemLength = count($search_items);
	for($i = 0; $i<$searchItemLength;$i++){
		if($search_items[$i]['nid'] == $param['action_nid']){
			unset($search_items[$i]);
			break;
		}
	}

	$command_replace = '$rule->'.$targetFieldName.'[\'und\'] = $search_items;';
	eval($command_replace);

	node_save($rule);
	node_delete($param['action_nid']);

	//redirect to previous page
	$temp_path = current_path();
	$temp_path = explode('/actions/',$temp_path);
	$redirect_path = $temp_path[0].'/edit';

	if(isset($redirect_path)){
		drupal_goto($redirect_path);
	}
}

function _unlink_actionpricefactor_from_rule($param) {
	$rule = node_load($param['rule_nid']);

	switch($param['price_type']) {
		case 'CHARGE':
			$targetFieldName = 'field_ref_action_charge';
			break;
		case 'DISCOUNT':
			$targetFieldName = 'field_ref_action_discount';
			break;
		case 'ALLOWANCE':
			$targetFieldName = 'field_ref_action_allowance';
			break;
			break;
	}

	$command_search = '$search_items=$rule->'.$targetFieldName.'[\'und\'];';
	eval($command_search);

	$searchItemLength = count($search_items);
	for($i = 0; $i<$searchItemLength;$i++){
		if($search_items[$i]['nid'] == $param['action_nid']){
			unset($search_items[$i]);
			break;
		}
	}

	$command_replace = '$rule->'.$targetFieldName.'[\'und\'] = $search_items;';
	eval($command_replace);

	node_save($rule);
	node_delete($param['action_nid']);

	//redirect to previous page
	$temp_path = current_path();
	$temp_path = explode('/actions/',$temp_path);
	$redirect_path = $temp_path[0].'/edit';

	if(isset($redirect_path)){
		drupal_goto($redirect_path);
	}
}

function _unlink_from_parent($params){
	if(isset($params['parent_nid']) && isset($params['target_field'])){

		$parent = node_load($params['parent_nid']);
		$targetField = $params['target_field'];


		$command_search = '$search_items=$parent->'.$targetField.'[\'und\'];';
		eval($command_search);

		$searchItemLength = count($search_items);
		for($i = 0; $i<$searchItemLength;$i++){
			if($search_items[$i]['nid'] == $params['child_nid']){
				unset($search_items[$i]);
				break;
			}
		}

		$command_replace = '$parent->'.$targetField.'[\'und\'] = $search_items;';
		eval($command_replace);

		node_save($parent);
	}
	node_delete($params['child_nid']);

	if($params['redirect']){
		//redirect to previous page
		$redirect_path = drupal_get_destination();

		if(isset($redirect_path)){
			drupal_goto($redirect_path['destination']);
		}
	}
}

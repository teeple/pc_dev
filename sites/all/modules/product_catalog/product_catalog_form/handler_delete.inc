<?php

function node_delete_handler_to_touch_product($node){
    $productNode = find_parent_product($node);
    if($productNode != NULL){
        _touch_product($productNode->nid);
    }
    //touch_product($node);
};

function product_catalog_form_node_delete($node){
    $childNodes = get_nested_children_nids($node->nid);

	switch($node->type){
		case 'productgroup':
			$viewResultMainSelected = views_get_view_result('list_product_group_main_selected', 'panel_pane_4', $node->nid);
			foreach($viewResultMainSelected as $item) {
				$childNodes[] = $item->nid;
			}
			break;
			
		case 'productchange':
			$viewResultSubSelected = views_get_view_result('list_product_change_sub_selected', 'panel_pane_4', $node->nid);
			foreach($viewResultSubSelected as $item) {
				$childNodes[] = $item->nid;
			}
			$viewResultCounterSelected = views_get_view_result('list_product_change_counter_selected', 'panel_pane_4', $node->nid);
			foreach($viewResultCounterSelected as $item) {
				$childNodes[] = $item->nid;
			}
			break;
			
	    case 'domestic_ratinggroup':
	      $rating_group = $node->field_rating_group['und'][0]['value'];
	      $numberingplan_nid = $node->field_ref_numberingplan_domestic['und'][0]['nid'];
	      _delete_basicrate_domestic_by_ratinggroup($numberingplan_nid,$rating_group,$node->nid);
	      break;
	    case 'idd_ratinggroup':
	      $rating_group = $node->field_rating_group['und'][0]['value'];
	      $numberingplan_nid = $node->field_ref_numberingplan_idd['und'][0]['nid'];
        $carrier_nid = $node->field_ref_carrier_mobile['und'][0]['nid'];
        $node_nid = $node->nid;
        
        $del_nids = array();
        $is_carrier_exist = _is_carrier_exist_in_numberingplan_idd($numberingplan_nid,$carrier_nid,$node_nid);
        if(!$is_carrier_exist){//if carrier no longer exist
          //delete all tariffplan_idd_carrier and basicrate_idd for the carrier
          $tariffplans = _get_tariffplan_by_numberingplan_idd($numberingplan_nid);
          foreach($tariffplans as $tariffplan_nid){
            $tariffplan_idd_carrier_nid = _get_tariffplan_idd_carrier_by_carrier($tariffplan_nid,$carrier_nid);
            $del_nids[] = $tariffplan_idd_carrier_nid;
            $basicrate_idd_view_result = views_get_view_result('list_basicrate_idd', 'panel_pane_2', $tariffplan_idd_carrier_nid);
            foreach($basicrate_idd_view_result as $basicrate_item){
              $del_nids[] = $basicrate_item->nid;
            }
          }
        }else{//if carrier exist
          //check wheter ratinggroup exist or not
          _delete_basicrate_idd_by_ratinggroup($numberingplan_nid,$rating_group,$carrier_nid,$node_nid);
        }
        
        if(!empty($del_nids)){
          node_delete_multiple($del_nids);
        }
        
	      break;
      case 'roaming_ratinggroup':
        $rating_group = $node->field_rating_group['und'][0]['value']; 
        $numberingplan_nid = $node->field_ref_roaming_plan['und'][0]['nid'];
        $node_nid = $node->nid;
        
        _delete_basicrate_roaming_by_ratinggroup($numberingplan_nid,$rating_group,$node_nid);
        break;
      case 'timetablefactors':
        $timetablefactor_nid = $node->nid;
        $del_nids = array();
        
        $view_result= views_get_view_result('list_timetablefactor_reference', 'panel_pane_1', $timetablefactor_nid);
        foreach($view_result as $item){
          $del_nids[] = $item->nid;
        }
        
        if(!empty($del_nids)){
          node_delete_multiple($del_nids);
        }
        
        break;
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
		/*case 'lifecyclescheme':
            if(!empty($node->field_lifecycle_states)){
                foreach($node->field_lifecycle_states['und'] as $child){
                    $childNodes[] = $child['nid'];
                }
                unset($node->field_lifecycle_states);
                node_save($node);
            }
            break;
         */
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
			
			/*
			//dsm($node, 'node');
			// 지울려는 해당 counter를 참조하고 있는 content type이 존재하는지 
			$view = views_get_view('list_reverse_reference_items');
			$view->set_display('panel_pane_1');
			$view->set_arguments($node->nid);
			$view->execute();
			
			//dsm($view->result, 'view_result');
			if(!empty($view->resut)) {
				drupal_set_message("You should remove the items referencing this counter",'error');
				drupal_form_error("You should remove the items referencing this counter");
				return;
			}
			drupal_set_message("You should remove the items referencing this counter",'error');
			form_set_error("You should remove the items referencing this counter");
			return;
			
			//카운터를 사용하는 다른 컨텐츠 들에 대한 처리도 해 주어야 할듯..상품같은..			
			//unit transfer			
			foreach($unitTransferView->result as $item){
				$unitTransferNode = node_load($item->nid);
                if(isset($unitTransferNode->field_ref_unittransferfactors['und'])){
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
			}
			*/
			
			break;
        case 'thresholdscheme':
            //thresholdschemefactors..
            $view = views_get_view('list_thresholdschemefactors');
            $view->set_display('panel_pane_1');
            $view->set_arguments(array('0' => $node->nid));
            $view->execute();
            
            foreach($view->result as $item){
                $childNodes[] = $item->nid;
            }
            break;
        case 'depositscheme':
            //depositschemefactors..
            $view = views_get_view('list_depositschemefactors');
            $view->set_display('panel_pane_1');
            $view->set_arguments(array('0' => $node->nid));
            $view->execute();
            
            foreach($view->result as $item){
                $childNodes[] = $item->nid;
            }
            
            //depositschemeadjustment
            $view = views_get_view('list_depositschemeadjustment');
            $view->set_display('panel_pane_1');
            $view->set_arguments(array('0' => $node->nid));
            $view->execute();
            
            foreach($view->result as $item){
                $childNodes[] = $item->nid;
            }
            break;
        case 'unittransfer':
            //unittransfer_factors
            $view = views_get_view('list_unit_transfer_factor');
            $view->set_display('panel_pane_1');
            $view->set_arguments(array('0' => $node->nid));
            $view->execute();
            
            foreach($view->result as $item){
                $childNodes[] = $item->nid;
            }
            break;
        case 'vouchercardtype':
        case 'tariffplan':
        case 'roaming_plan':
        case 'number_special':
        case 'numberingplan_idd':
        case 'numberingplan_domestic':  
            _add_defered_delete($node);
            break;

    }
	
	$childNodes = array_unique($childNodes); 
	if(!empty($childNodes)){
		node_delete_multiple($childNodes);
	}
}

function _add_defered_delete($node){
    global $user;
    module_load_include('inc', 'node', 'node.pages');
    
    $deferedNode = new StdClass();
    $deferedNode->uid = $user->uid;
    $deferedNode->type = 'defereddelete';
    $deferedNode->language = 'und';
    $deferedNode->field_node_type['und'][0]['value'] = $node->type;
    $deferedNode->field_deleted_node['und'][0]['nid'] = $node->nid;
    
    node_save($deferedNode);
}

function _cleanup_defered_delete(){
    $deleteNids = array();
    $deferedNodes = node_load_multiple(NULL, array('type' => 'defereddelete'));
    
    foreach($deferedNodes as $deferedNode){
        $parentNid = $deferedNode->field_deleted_node['und'][0]['nid'];
        $parentType = $deferedNode->field_node_type['und'][0]['value'];
        
        switch($parentType){
            case 'vouchercardtype':
                $deleteNids = _cleanup_voucher_card_type($parentNid);
                break;
            case 'tariffplan':
                $deleteNids = _cleanup_tariffplan($parentNid);
                break;
            case 'roaming_plan':
                $deleteNids = _cleanup_roaming_plan($parentNid);
                break;
            case 'number_special':
                $deleteNids = _cleanup_number_special($parentNid);
                break;
            case 'numberingplan_idd':
                $deleteNids = _cleanup_numberingplan_idd($parentNid);
                break;
            case 'numberingplan_domestic':  
                $deleteNids = _cleanup_numberingplan_domestic($parentNid);
                break;
        }
        
        $deleteNids[] = $deferedNode->nid;
        $deleteNids = array_unique($deleteNids); 
        if(!empty($deleteNids)){
            node_delete_multiple($deleteNids);
        }
    }
    
}

function _cleanup_numberingplan_domestic($planNid){
    $deleteNids = array();
    
    //NumberSpecialFactors    
    $view = views_get_view('list_numberingplan_domestic_ratinggroup');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $planNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }

    return $deleteNids;
}

function _cleanup_numberingplan_idd($planNid){
    $deleteNids = array();
    
    //NumberSpecialFactors    
    $view = views_get_view('list_numberingplan_idd_ratinggroup');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $planNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }

    return $deleteNids;
}

function _cleanup_number_special($numberSpNid){
    $deleteNids = array();
    
    //NumberSpecialFactors    
    $view = views_get_view('list_numberspecial_child_node');
    $view->set_display('panel_pane_6');
    $view->set_arguments(array('0' => $numberSpNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }

    //NumberSpecialRate 
    $view = views_get_view('list_numberspecial_child_node');
    $view->set_display('panel_pane_7');
    $view->set_arguments(array('0' => $numberSpNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }
    return $deleteNids;
}

function _cleanup_roaming_plan($planNid){
    $deleteNids = array();
    
    //roaming_ratinggroup    
    $view = views_get_view('list_roaming_plan_ratinggroup');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $planNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }

    return $deleteNids;
}

function _cleanup_tariffplan($planNid){
    $deleteNids = array();
    
    //covers for basicrate_domestic, basicrate_idd, basicrate_data,basicrate_roaming,tariffplan_idd_carrier,rate content type        
    $view = views_get_view('query_tariffplan_children');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $planNid));
    $view->execute(); 
    
    foreach($view->result as $record){
        $deleteNids[] = $record->nid;
    }

    //covers for actionpricechargefactors, actionpricediscountfactors, treenodespecialnumberscheme,
    //treenodepacketpredefined,treenodepacketdynamic,actionblockfactors, basicrate_data content type
    $view = views_get_view('query_tariffplan_children');
    $view->set_display('panel_pane_4');
    $view->set_arguments(array('0' => $planNid));
    $view->execute(); 
    foreach($view->result as $record){
       $deleteNids[] = $record->nid;
    }

    return $deleteNids;
}

function _cleanup_voucher_card_type($voucherNid){
    $deleteNids = array();
    
    //loyaltypoint
    $loyaltyPointView = views_get_view('list_vouchercardtype_delete');
    $loyaltyPointView->set_display('panel_pane_1');
    $loyaltyPointView->set_arguments(array('0' => $voucherNid));
    $loyaltyPointView->execute();
    
    foreach($loyaltyPointView->result as $loyaltyPoint){
        $deleteNids[] = $loyaltyPoint->nid;
        //loyaltypointfactors
        $loyaltyPointFactorsView = views_get_view('list_vouchercardtype_delete');
        $loyaltyPointFactorsView->set_display('panel_pane_2');
        $loyaltyPointFactorsView->set_arguments(array('0' => $loyaltyPoint->nid));
        $loyaltyPointFactorsView->execute();
        foreach($loyaltyPointFactorsView->result as $loyaltyPointFactors){
            $deleteNids[] = $loyaltyPointFactors->nid;
        }
    }
    
    //treenodecounterforvoucher
    $treeNodeCounterForVoucherView = views_get_view('list_vouchercardtype_delete');
    $treeNodeCounterForVoucherView->set_display('panel_pane_3');
    $treeNodeCounterForVoucherView->set_arguments(array('0' => $voucherNid));
    $treeNodeCounterForVoucherView->execute();
    foreach($treeNodeCounterForVoucherView->result as $treeNodeCounterForVoucher){
        $deleteNids[] = $treeNodeCounterForVoucher->nid;
    }
    
    //treenodeproductforvoucher
    $treeNodeProductForVoucherView = views_get_view('list_vouchercardtype_delete');
    $treeNodeProductForVoucherView->set_display('panel_pane_4');
    $treeNodeProductForVoucherView->set_arguments(array('0' => $voucherNid));
    $treeNodeProductForVoucherView->execute();
    foreach($treeNodeProductForVoucherView->result as $treeNodeProductForVoucher){
        $deleteNids[] = $treeNodeProductForVoucher->nid;
        //treenodecounterforvoucherprd
        $treeNodeCounterForVoucherPrdView = views_get_view('list_vouchercardtype_delete');
        $treeNodeCounterForVoucherPrdView->set_display('panel_pane_5');
        $treeNodeCounterForVoucherPrdView->set_arguments(array('0' => $treeNodeProductForVoucher->nid));
        $treeNodeCounterForVoucherPrdView->execute();
        foreach($treeNodeCounterForVoucherPrdView->result as $treeNodeCounterForVoucherPrd){
            $deleteNids[] = $treeNodeCounterForVoucherPrd->nid;
        }
        //actionsetnotification
        $actionSetNotificationView = views_get_view('list_vouchercardtype_delete');
        $actionSetNotificationView->set_display('panel_pane_6');
        $actionSetNotificationView->set_arguments(array('0' => $treeNodeProductForVoucher->nid));
        $actionSetNotificationView->execute();
        foreach($actionSetNotificationView->result as $actionSetNotification){
            $deleteNids[] = $actionSetNotification->nid;
        }
    }
    
    return $deleteNids;
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

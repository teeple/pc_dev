<?php
function _load_tree_item_mixed_with_node_and_term($rootNode,$grandParentNode=NULL){
	$children = array(
			'attr' => array('id' => 'node_'.$rootNode->nid,
					'node_type' => $rootNode->type,
					'rel' => $rootNode->type,
					'weight' => isset($rootNode->field_weight['und'][0]['value'])?$rootNode->field_weight['und'][0]['value']:0,
			),
			'data' => $rootNode->title,
	);
	
    $filterTerm = FALSE;
	switch($rootNode->type){
		case 'simpleproductoffering':
			$vocaName = _get_vocabulary_name('simpleproductoffering', $rootNode);
            $children['state'] = 'open';
            $filterTerm = TRUE;
            $productTypeTerm = taxonomy_term_load($rootNode->field_product_type['und'][0]['tid']);
            $billTypeTerm = taxonomy_term_load($rootNode->field_billing_type['und'][0]['tid']);
            $notAllowedCombinationStr = $productTypeTerm->name.'_'.$billTypeTerm->name;
            break;			
		case 'tariffplan':
            $filterTerm = TRUE;
            $productNode = node_load($rootNode->field_ref_product['und'][0]['nid']);
            $serviceDomainTerm = taxonomy_term_load($productNode->field_service_type_of_provider['und'][0]['tid']);
            if($serviceDomainTerm->name ==='Cross'){
                $notAllowedCombinationStr = $serviceDomainTerm->name;
            }else{
                $productTypeTerm = taxonomy_term_load($productNode->field_product_type['und'][0]['tid']);
                $billTypeTerm = taxonomy_term_load($productNode->field_billing_type['und'][0]['tid']);
                $notAllowedCombinationStr = $productTypeTerm->name.'_'.$billTypeTerm->name;
            }
            $vocaName = $rootNode->field_tree_child_voca_name['und'][0]['value'];
            
            break;
		case 'vouchercardtype':
			$vocaName = $rootNode->field_tree_child_voca_name['und'][0]['value'];
            break;
		case 'number_special':
			$vocaName = 'tpl_numberspecial';
			break;
        default :
			$vocaName = NULL;
	}
	
	$vocabulary = taxonomy_vocabulary_machine_name_load($vocaName);
	
	$tree  = taxonomy_get_tree($vocabulary->vid);
    
    $skipParents = array();
	foreach($tree as $item){
		$term = taxonomy_term_load($item->tid);
        
        if($term->name == 'Roaming'){ //skip roaming term in case of not prepaid
            if($grandParentNode != NULL){
                if($grandParentNode->type == 'simpleproductoffering'){
                    $productBillTypeTerm = taxonomy_term_load($grandParentNode->field_billing_type['und'][0]['tid']);
                    if($productBillTypeTerm->name != 'Prepaid'){
                        continue;
                    }
                }
            }
        }       
        
        if($filterTerm){//filter tree item based on product type and billing type
            //check parent is already removed from tree
            if(isset($term->parents[0])){
                if(in_array($term->parents[0],$skipParents)){
                    $skipParents[] = $term->tid;
                    continue;
                }
            }
            
            //check combination is not allowed
            $notAllowedCombination = array();
            if(isset($term->field_not_visible['und'])){
                foreach($term->field_not_visible['und'] as $notAllowed){
                    $notAllowedCombination[] = $notAllowed['value'];
                }
                if(in_array($notAllowedCombinationStr,$notAllowedCombination)){
                    $skipParents[] = $term->tid;
                    continue;
                }
            }
        }
        
		$itemArray = array(
				'attr' => array('id' => 'term_'.$item->tid.'_'.$rootNode->nid,
						'node_type' => 'term',
						'rel' => isset($term->field_rel_type['und'][0]['value'])?$term->field_rel_type['und'][0]['value']:"",
						'weight' => $item->weight,
				),
				'data' => $item->name
		);
		
        if(isset($term->field_rel_type['und'][0]['value'])){
        	 switch($term->field_rel_type['und'][0]['value']) {
        		 case 'attribute':
        		 case 'attribute_packaged':
        		 case 'counter':
        		 case 'nonusage':
        		 case 'usage':
        		 		$itemArray['state'] = 'open';
        		 		break;
        	 }
        }
	 		
		if(isset($term->field_qtabs_loading['und'][0]['value'])){
			$loadingInfo = field_collection_item_load($term->field_qtabs_loading['und'][0]['value']);
			//$qtabType = $loadingInfo->field_tab_type['und'][0]['value'];
			$viewName = $loadingInfo->field_tab_content['und'][0]['value'];
			$displayName = $loadingInfo->field_view_display['und'][0]['value'];
			$argsInfo = $loadingInfo->field_view_arguments['und'][0]['value'];

			$param = array();
			$argsInfo = explode('/',$argsInfo);

			foreach($argsInfo as $argument){
				if(strpos($argument, '$productNid') !== FALSE){
					if(isset($rootNode->field_ref_product['und'][0]['nid'])){
						$param[] = $rootNode->field_ref_product['und'][0]['nid'];
					}else{
						$param[] = $rootNode->nid;
					}
				}else if(strpos($argument, '$refTreeTid') !== FALSE){
					$param[] = $item->tid;
				}else if(strpos($argument, '$refTreeNid') !== FALSE){
					$param[] = $rootNode->nid;
				}else if(strpos($argument, '$voucherCardTypeNid') !== FALSE){
					$param[] = $rootNode->nid;
				}else if(strpos($argument, '$numberSpecialNid') !== FALSE){
					$param[] = $rootNode->nid;
				}
				else{
					$param[] = $argument;
				}
			}
			
			//load attached child node
			$view = views_get_view($viewName);
            $view->set_display($displayName);
			$view->set_arguments($param);
			$view->execute();
			
			foreach($view->result as $child){
				
				if($child->node_type == 'tariffplan'){
					$childNode = node_load($child->nid);
					$itemArray['children'][] = _load_tree_item_mixed_with_node_and_term($childNode,$rootNode);
				} else {
					$itemArray['children'][] = get_children_stored_procedure($child->nid,'term_'.$item->tid.'_'.$rootNode->nid);
				}
			}
		}
			
		if($item->parents[0] === '0'){
			$itemArray['attr']['parent_nid'] = 'node_'.$rootNode->nid;
			$children['children'][] = $itemArray;
		}else{
			$itemArray['attr']['parent_nid'] = 'term_'.$item->parents[0].'_'.$rootNode->nid;
			$keyPath = array_searchRecursive_get_key_path('term_'.$item->parents[0].'_'.$rootNode->nid,$children,true);
            
            if(!empty($keyPath)){
    			$keyString = '$children';
    			$keyPathLength = count($keyPath);
    			for($i = 0; $i < $keyPathLength -2; $i++){
    				if(is_numeric($keyPath[$i])){
    					$keyString .= '['.$keyPath[$i].']';
    				}else{
    					$keyString .= '[\''.$keyPath[$i].'\']';
    				}
    			}
    			$keyString .= '[\'children\'][] = $itemArray;';
    			eval($keyString);
            }
		}
	}	
	return $children;
}

function get_root($nid) {
    $parent_nid = get_parent_nid($nid);

    while($parent_nid != -1) {
        $nid = $parent_nid;
        $parent_nid = get_parent_nid($nid);
    }

    return $nid;
}

function get_parent_nid($nid) {

    $node = node_load($nid);

    if(isset($node->field_parent_node) && isset($node->field_parent_node['und'][0]['nid'])) {
        return $node->field_parent_node['und'][0]['nid'];
    }
    return -1;
}

function get_nested_children_nids($nid){
	$item = array();
	$viewData = get_viewdata('query_tree_by_root_nid', $nid);

	foreach ($viewData as $viewRow) {
		$item[] = $viewRow['nid'];
		$item[] = get_nested_children_nids($viewRow['nid']);
		$item = array_filter($item);
    }
    return $item;
}

function get_1st_children_nids_by_in_tree($root_nid, $refTreeTid) {
	$item = array();
	$viewData = get_viewdata('list_tree_term_child_node_for_product', $root_nid, $refTreeTid);
	
	foreach($viewData as $viewRow) {
		$item[] = $viewRow['nid'];
	}
	
	return $item;
	
}

function get_product_nids_from_noderefernce($oldChildrenNids){

    $retArray = array();

    foreach($oldChildrenNids as $nid){
        $node = node_load($nid);
        $retArray[] = $node->field_ref_node['und'][0]['nid'];
    }

    return $retArray;
}

function _get_rel_type_by_usage_type($tariffplan_machinename) {

	$machineNames = explode('_', $tariffplan_machinename);
	$length = count($machineNames);
	$usageType = $machineNames[$length-1];
	
	switch($usageType) {
	case 'data':
		$rel_type_suffix = '_usage_data';
		break;
	case 'mms':
		$rel_type_suffix = '_usage_mms';
		break;
	case 'sms':
		$rel_type_suffix = '_usage_sms';
		break;
	case 'voice':
		$rel_type_suffix = '_usage_voice';
		break;
	case 'deduct':
		$rel_type_suffix = '_usage_loyalty_point_deduct';
		break;
	case 'crbt':
		$rel_type_suffix = '_usage_crbt';
		break;
	case 'vod':
		$rel_type_suffix = '_usage_vod';
		break;
	}
	
	return $rel_type_suffix;
}

function _get_rel_type_by_nonusage_type($tempRelType) {
	$tempRelTypes = explode('_', $tempRelType);
	$length = count($tempRelTypes);
	
	$nonUsageType = $tempRelTypes[$length-2];
	switch($nonUsageType) {
		case 'recurring':
		case 'fee':
			$rel_type_suffix = '_nonusage_recurring';
			break;
		case 'subscription':
			$rel_type_suffix = '_nonusage_subscription';
			break;
		case 'unsubscription':
			$rel_type_suffix = '_nonusage_unsubscription';
			break;
		case 'activation':
			$rel_type_suffix = '_nonusage_activation';
			break;
		case 'recharge':
			$rel_type_suffix = '_nonusage_recharge';
			break;
		case 'usageend':
			$rel_type_suffix = '_nonusage_usageend';
			break;
	}
	return $rel_type_suffix;
}

function _get_rel_type_on_condition($item) {
	
	$parent = node_load($item->parent_nid);
	$treeTerm = taxonomy_term_load($parent->field_ref_tree_tid['und'][0]['value']);
	
	$rel_type = 'conditioncommonand';
	
	switch($treeTerm->name) {
	  case 'Penalty':
	  	$tempRelType = $treeTerm->field_rel_type['und'][0]['value'];
	  	$rel_type .= _get_rel_type_by_nonusage_type($tempRelType);
	  	break;
	  	
	  case 'Charge': 
		  $tempRelType = $treeTerm->field_rel_type['und'][0]['value'];
		  
		  if($tempRelType == 'treeNodeCustomCharge') {
		  		$rel_type .= _get_rel_type_by_usage_type($treeTerm->vocabulary_machine_name);
		  } else {
		  		$rel_type .= _get_rel_type_by_nonusage_type($tempRelType);
		  }
		  break;
		  
		case 'Discount':
			$tempRelType = $treeTerm->field_rel_type['und'][0]['value'];
			
		  if($tempRelType == 'treeNodeCustomDiscount') {
					$rel_type .= _get_rel_type_by_usage_type($treeTerm->vocabulary_machine_name);
		  } else {
		  		$rel_type .= _get_rel_type_by_nonusage_type($tempRelType);
		  }
		  break;
			
		case 'Bonus':
			$tempRelType = $treeTerm->field_rel_type['und'][0]['value'];
			$rel_type .= _get_rel_type_by_nonusage_type($tempRelType);
			
			break;
			
		case 'Block':
			$tempRelType = $treeTerm->field_rel_type['und'][0]['value'];
			
			if($tempRelType == 'treeNodeCustomBlock') {
					$rel_type .= _get_rel_type_by_usage_type($treeTerm->vocabulary_machine_name);
			}
			break;
			
		case 'Predefined':
		case 'Dynamic':
		case 'DefaultQoS':
			$rel_type .= _get_rel_type_by_usage_type($treeTerm->vocabulary_machine_name);
			break;
			
		default:
			break;
	}
	
	return $rel_type;
}

function get_children_stored_procedure($nid,$parentId=NULL){
	$result = array();
	
	$stored_procedure_query = "call pc_dev.getTreeDataView(:nid);";
	$stored_procedure_result = db_query($stored_procedure_query,array(':nid' => $nid))->fetchAll();
	
  foreach($stored_procedure_result as $item){
    
    switch($item->content_type) {
    	case 'conditioncommonand':
    		$item->rel_type = _get_rel_type_on_condition($item);
    		break;
    }
    
		$itemArray = array(
			'attr' => array('id' => 'node_'.$item->nid,
					'node_type' => $item->content_type,
					'rel' => $item->rel_type,
					'weight' => $item->weight
			),
			'data' => $item->title
		);
		
		if($item->parent_nid === '0' || $item->nid == $nid){
			$itemArray['attr']['parent_nid'] = ($parentId != NULL) ? $parentId :NULL;
			$result = $itemArray;
		}else{
			$itemArray['attr']['parent_nid'] = 'node_'.$item->parent_nid;
			$keyPath = array_searchRecursive_get_key_path('node_'.$item->parent_nid,$result,true);
			if($keyPath[0] != 'children'){
				$result['children'][] = $itemArray;
			}else{
				$keyString = '$result';
				$keyPathLength = count($keyPath);
				for($i = 0; $i < $keyPathLength -2; $i++){
					if(is_numeric($keyPath[$i])){
						$keyString .= '['.$keyPath[$i].']';
					}else{
						$keyString .= '[\''.$keyPath[$i].'\']';
					}					
				}
				$keyString .= '[\'children\'][] = $itemArray;';
				eval($keyString);
			}
			
		}		
	}
	
	return $result;
}

// 해당 nid의 type에 따라서 하위의 node를 적절히 가져온다.
//
function get_children($nid) {

    $node = node_load($nid);
    $loadChildren = TRUE;

    error_log('nid: '.$nid. ' type: '.$node->type);
    
    switch($node->type){
    	case 'defaulttreenode':
    		$term = taxonomy_term_load($node->field_ref_tree_node_tid['und'][0]['value']);
			// $relType = $term->description;
            if( !empty($term->field_rel_type) 
                && isset($term->field_rel_type['und'][0]['value'])) {
			    $relType = $term->field_rel_type['und'][0]['value'];
            } else {
                $relType = '';
            }

        	if($relType == '')$relType = $node->type;
	    	$nodeTitle = $term->name;	    	
    		break;

        case 'treenodecounter':
            $refNode = node_load($node->field_ref_counter['und'][0]['nid']);
            
            $nodeTitle = $refNode->title;
            $main_or_accumulated = taxonomy_term_load($refNode->field_main_or_accumulated['und'][0]['tid']);
            $counter_type = taxonomy_term_load($refNode->field_counter_type['und'][0]['tid']);
            $relType = 'treenode_' . $refNode->type .'_'.strtolower($main_or_accumulated->name).'_'.strtolower($counter_type->name);

            break;
    	case 'treenodewithnodereference':
    		$refNode = node_load($node->field_ref_node['und'][0]['nid']);

            //error_log('ref node nid: '.$refNode->nid);

            switch($refNode->type) {
                /*
                case 'counter':
                    $main_or_accumulated = taxonomy_term_load($refNode->field_main_or_accumulated['und'][0]['tid']);
                    $counter_type = taxonomy_term_load($refNode->field_counter_type['und'][0]['tid']);
                    $relType = 'treenode_' . $refNode->type .'_'.strtolower($main_or_accumulated->name).'_'.strtolower($counter_type->name);
                    break;
                */
                case 'simpleproductoffering':
                    $loadChildren = FALSE;
                	$relType = 'treenode_' . $refNode->type;
                    break;
                case 'timetable':
                	$loadChildren = FALSE;
                	$relType = 'treenode_' . $refNode->type;
                	break;
    		    default:
                    $relType = 'treenode_' . $refNode->type;
                    break;
            }
    		// $nodeTitle = $node->title;
            $nodeTitle = $refNode->title;
    		break;
    	case 'treenodegeneral':
    		$nodeTitle = $node->title;
    		$relType = $node->field_rel_type['und'][0]['value'];
    		break;
    	default:
    		$nodeTitle = $node->title;
    		$relType = $node->type;
    		break;
    }
    
    $item = array(
        'attr' => array('id' => $node->nid, 'node_type' => $node->type
    				  , 'rel' => $relType
    				  , 'weight' => isset($node->field_weight['und'][0]['value'])?$node->field_weight['und'][0]['value']:0
    				  , 'parent_nid' => isset($node->field_parent_node['und'][0]['nid']) ? $node->field_parent_node['und'][0]['nid'] : NULL    				  
    			 ), 
        'data' => $nodeTitle,
    );
    
    if($loadChildren){
	    $viewData = get_viewdata('query_tree_by_root_nid', $node->nid);
    }else{
    	$viewData = array();
    }

    if(count($viewData) == 0) {
        $item['children'] = NULL;
    } else {
        foreach ($viewData as $viewRow) {
            $item['children'][] = get_children($viewRow['nid']);
        }
    }

    return $item;
}

function get_viewdata($viewName, $nid, $additionalParam=NULL) {
    $results = array();

    $view = views_get_view($viewName);
    $view->set_arguments(array('0'=> $nid,'1' => $additionalParam));
    $view->execute();
    $results = objectToArray($view->result);
 
    return $results;
}

function add_js_settings_after_node_save($node){
	
	if(isset($node->field_parent_node['und'][0]['nid'])){
		$parentId = 'node_'.$node->field_parent_node['und'][0]['nid'];
	}else if(isset($node->field_ref_tree_tid['und'][0]['value'])){
		$parentId = 'term_'.$node->field_ref_tree_tid['und'][0]['value'];		
		// if(isset($node->field_ref_tree_nid['und'][0]['nid'])){
		if(!empty($node->field_ref_tree_nid['und'])){
			$parentId .= '_'.$node->field_ref_tree_nid['und'][0]['nid'];
		}else{
			$parentId .= '_'.$node->field_ref_product['und'][0]['nid'];
		} 		
	}else{
		$parentId = NULL;
	}
	
	if($node->type == 'tariffplan'){
	    $productNode = node_load($node->field_ref_product['und'][0]['nid']);
		$js_data = _load_tree_item_mixed_with_node_and_term($node,$productNode);		
	}else{
		$js_data = get_children_stored_procedure($node->nid,$parentId);
	}
	
	$js_data['content_type'] = $node->type;
	
	$js_settings = array(
		'success' => TRUE,
		'data' => $js_data,
		'parent_nid' => $parentId
	);
	
	drupal_add_js(array('product_catalog_ajax_result' => $js_settings), 'setting');
    
    return $js_settings;
}

function add_js_settings_after_node_update($node) {
	
	if($node->type == 'prdcounterlist') {
	    $rootNode = node_load($node->field_ref_product['und'][0]['nid']);
    	$children = _load_tree_item_mixed_with_node_and_term($rootNode);
		$js_data = json_encode($children);
	} else {
		$js_data = array(
			'nid' => 'node_'.$node->nid,
			'title' => $node->title
	   	);
	}
	
	$js_settings = array(
		'success' => TRUE,
		'data' => $js_data,
		// 'parent_nid' => $parentId
		'parent_nid' => !empty($parentId)? $parentId: NULL
	);
	
	drupal_add_js(array('product_catalog_ajax_result' => $js_settings), 'setting');
}
/*
function add_js_settings_after_node_update($node){
	$js_settings = array(
		'success' => TRUE,
		'data' => array('nid' => 'node_'.$node->nid
					   ,'title' => $node->title
					   ,'content_type' => $node->type
					   )
	);
	drupal_add_js(array('product_catalog_ajax_result' => $js_settings), 'setting');	
}
 
 */

function load_required_js_css_before_ajax_load(){
	$js_added = drupal_static( __FUNCTION__, FALSE);
    if ( !$js_added ) {
        $js_added = TRUE;
         
    	//date popup
    	date_popup_add();
        drupal_add_js(drupal_get_path('module', 'date_popup') .'/date_popup.js');
        
        //tabledrag
        drupal_add_js(base_path().'misc/tabledrag.js');
        drupal_add_js(base_path().'misc/tableheader.js');    
        
        //vbo
        drupal_add_js(drupal_get_path('module', 'views_bulk_operations').'/js/views_bulk_operations.js');
        
        //quick tab
        $qTabPath = drupal_get_path('module', 'quicktabs');
        drupal_add_js($qTabPath.'/js/quicktabs.js');
        drupal_add_css($qTabPath.'/css/quicktabs.css');
        //drupal_add_css($qTabPath.'/quicktabs_tabstyles/tabstyles/zen/zen-rtl.css');
        drupal_add_css($qTabPath.'/quicktabs_tabstyles/tabstyles/zen/zen.css');
        
        //views
        drupal_add_js(drupal_get_path('module', 'views').'/js/ajax_view.js'); 
    
        // editable fields
        $editablefields_path = drupal_get_path('module', 'editablefields');
        drupal_add_js($editablefields_path . '/editablefields.js');
        
        // ctools auto submit
        drupal_add_js(drupal_get_path('module', 'ctools').'/js/auto-submit.js');
        
        //field conditional state    
        drupal_add_js(base_path().'misc/states.js');
    	
    	$arrangeFieldsPath = drupal_get_path('module', 'arrange_fields');
    	drupal_add_js($arrangeFieldsPath.'/js/arrange_fields.js');
    	drupal_add_css($arrangeFieldsPath.'/css/arrange_fields.css');
    	
    	//drupal_add_js($fieldConditionalStatePath.'/js/required_conditional_state.js');       
      //drupal_add_js($fieldConditionalStatePath.'/js/settings_form.js');
        
    	//jstree
    	drupal_add_js(libraries_get_path('jstree') . '/jquery.jstree.js');
    	drupal_add_js(libraries_get_path('jquery-loadmask') . '/jquery.loadmask.min.js');
    	drupal_add_css(libraries_get_path('jquery-loadmask') . '/jquery.loadmask.css');
    	
        //flot for chart
    	$floatPath = libraries_get_path('flot');
    	drupal_add_js($floatPath.'/jquery.flot.js');
    	
    	//product catalog tree
    	$product_catalog_tree_path = drupal_get_path('module', 'product_catalog_tree');
    	drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_context_sub_menu.js',
            array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>100)
        );
        drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_type_setting.js',
            array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>200)
        );
        
        drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_context_menu_setting.js',
            array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>300)
        );
        
    	/*
    	$paths = explode('/', current_path());
    	$serviceDomains = array('Mobile', 'IPTV', 'VoIP', 'Broadband', 'Satellite', 'Dummy', 'Cross');
    	if(!empty($paths) && $paths[0] == 'product_designer') {
    	  $serviceDomain = 'Mobile';
    	  if(in_array($paths[1], $serviceDomains)) {
	    		$serviceDomain = $paths[1];
	    	} 
	    	
				$jsContextMenuSettingsPath = '/js/product_catalog_tree_context_menu_setting_'.$serviceDomain.'.js';
				drupal_add_js($product_catalog_tree_path  . $jsContextMenuSettingsPath,
                    array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight' => 300)
                );
				
    	} else {
    		drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_context_menu_setting_Common.js',
                array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>300)
            );
    	}
        */
    	drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_operation.js',
            array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>400)
        );
    	drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree_flot.js');
    	drupal_add_js($product_catalog_tree_path  . '/js/product_catalog_tree.js',
            array('type'=>'file','scope'=>'header','group'=>JS_DEFAULT,'everypage'=>TRUE,'weight'=>500)
        );
        
    	//ctools collapsible div
    	$ctoolsPath = drupal_get_path('module', 'ctools');
    	drupal_add_js($ctoolsPath. '/js/collapsible-div.js');
    	drupal_add_css($ctoolsPath.'/css/collapsible-div.css');
    	
    	//product catalog selectable
    	$product_catalog_selectable_path = drupal_get_path('module', 'product_catalog_selectable');
    	drupal_add_js($product_catalog_selectable_path . '/js/product_catalog_selectable.js');
    	
    	// module multiselect
    	//$product_catalog_multiselect_path = drupal_get_path('module', 'multiselect');
    	//drupal_add_js($product_catalog_multiselect_path . '/multiselect.js');
    	//drupal_add_css($product_catalog_multiselect_path. '/multiselect.css');
        
        // jQuery multiselect
        $jQuery_ui_multiselect_path = drupal_get_path('module', 'jquery_ui_multiselect_widget'); 
        drupal_add_js($jQuery_ui_multiselect_path . '/jquery-ui-multiselect-widget/src/jquery.multiselect.min.js');
        drupal_add_js($jQuery_ui_multiselect_path . '/jquery-ui-multiselect-widget/src/jquery.multiselect.filter.min.js');
        drupal_add_js($jQuery_ui_multiselect_path . '/jquery_ui_multiselect_widget.js');
        drupal_add_css($jQuery_ui_multiselect_path. '/jquery_ui_multiselect_widget.css');
        drupal_add_css($jQuery_ui_multiselect_path. '/jquery-ui-multiselect-widget/jquery.multiselect.css');
        drupal_add_css($jQuery_ui_multiselect_path. '/jquery-ui-multiselect-widget/jquery.multiselect.filter.css');
    }
}

function _get_max_weight_in_children($parentNid){
	$view = views_get_view('query_tree_max_weight_by_root_nid');
    $view->set_arguments(array('0' => $parentNid));
    $view->execute();
    
    $weightStep = 100;
    
    if(empty($view->result[0]->field_field_weight)){
        $weight = 0;	
    } else{
        $weight = $view->result[0]->field_field_weight[0]['raw']['value'] + $weightStep;
    }
    
    return $weight;
}

function _add_command_after_dismiss_modal($refNodeNid,$refTreeTid,$defaultTabIndex){
	
	if(empty($refTreeTid)) {
		$nodeId = 'node_'.$refNodeNid;	
	} else {
		$nodeId = 'term_'.$refTreeTid.'_'.$refNodeNid;	
	}
	$params = array();
	$params[] = $nodeId;

	if(!empty($defaultTabIndex)){
		$params[] = $defaultTabIndex;
	}
	
	return ajax_command_invoke(NULL, 'reloadTreeContentDivFromDrupal', $params);
}

function _basicrate_timetablefactors_custom_form($form, &$form_state){
	//price unit
	$priceUnitOptions = _get_select_option_from_vocabulary('unit_of_price');	
	$form['price_unit'] = array(
		'#type' => 'select',
		'#title' => t('Price Unit'),
        '#options' => $priceUnitOptions,
		'#weight' => 2,
	);
	
	//uom unit
	$uomUnitOptions = _get_select_option_from_vocabulary('unit_of_measure');	
	$form['uom_unit'] = array(
		'#type' => 'select',
		'#title' => t('UnitOfMeasure unit'),
        '#options' => $uomUnitOptions,
		'#weight' => 3,
	);
	
	//timetablefactors
	$form['timetablefactors_fieldset'] = array(
    	'#type' => 'fieldset',
		'#title' => 'Timetable Factors', 
	    '#weight' => 4, 
	    '#collapsible' => TRUE, 
		'#collapsed' => FALSE,
    	'#prefix' => '<div id="timetablefactors_wrapper">',
    	'#suffix' => '</div>'
    );
	$timetableNid = $form_state['build_info']['args'][1]->nid;
	
	$parentNode = node_load($form_state['build_info']['args'][0]->field_parent_node['und'][0]['nid']);
	switch($parentNode->field_rel_type['und'][0]['safe_value']){
		case 'basicrate_idd_ratinggroup':
			$viewResult = views_get_view_result('list_timetablefactors', 'panel_pane_3',array('0'=>$form_state['build_info']['args'][0]->nid));
			break;
		case 'basicrate_domestic_ratinggroup':
			$viewResult = views_get_view_result('list_timetablefactors', 'panel_pane_4',array('0'=>$form_state['build_info']['args'][0]->nid));
			break;
	}
	    
    $rows = array();
    $viewCount = count($viewResult);
    
    foreach($viewResult as $item){
    	$priceDefaultValue = isset($item->field_field_price_amount)?$item->field_field_price_amount[0]['raw']['value']:'';
    	$uomDefaultValue = isset($item->field_field_uom_amount)?$item->field_field_uom_amount[0]['raw']['value']:'';
    	$priceAmount = '<input type="text" id="price_amount_'.$item->nid.'" name="price_amount_'.$item->nid.'" value="'.$priceDefaultValue.'"/>';
    	$uomAmount = '<input type="text" id="uom_amount_'.$item->nid.'" name="uom_amount_'.$item->nid.'" value="'.$uomDefaultValue.'"/>';
    	
	    switch($parentNode->field_rel_type['und'][0]['safe_value']){
			case 'basicrate_idd_ratinggroup':
				$carrier = $item->field_field_carrier_idd[0]['rendered']['#title'];
				break;
			case 'basicrate_domestic_ratinggroup':
				$carrier = $item->field_field_carrier_domestic[0]['rendered']['#title'];
				break;
		}
		
    	$rows[] = array(    	
    		$carrier,
    		$item->field_field_basicrate_ratinggroup[0]['raw']['value'],
    		$item->node_field_data_field_ref_timetablefactors_title,
    		$item->field_field_holiday[0]['raw']['value'],
    		$item->field_field_week_mon[0]['raw']['value'],
    		$item->field_field_week_tue[0]['raw']['value'],
    		$item->field_field_week_wed[0]['raw']['value'],
    		$item->field_field_week_thu[0]['raw']['value'],
    		$item->field_field_week_fri[0]['raw']['value'],
    		$item->field_field_week_sat[0]['raw']['value'],
    		$item->field_field_week_sun[0]['raw']['value'],
    		$item->field_field_timeslot_from_hour[0]['raw']['value'].':'.$item->field_field_timeslot_from_minutes[0]['raw']['value'],
    		$item->field_field_timeslot_to_hour[0]['raw']['value'].':'.$item->field_field_timeslot_to_minutes[0]['raw']['value'],
    		array('data' => $priceAmount),
    		array('data' => $uomAmount)
    	);
    }

    $header = _basicrate_timetablefactors_custom_form_get_table_header();
	$tableThemeResult = _basicrate_timetablefactors_custom_form_get_table_output($header,$rows);
	
	$form['timetablefactors_fieldset']['timetablefactors'] = array(
		'#type' => 'markup',
		'#markup' => $tableThemeResult,
		'#weight' => 0
	);
    
	$form['actions'] = array(
		'#weight' => 100
	);
	$form['actions']['submit'] = array(
    	'#type' => 'submit',
	    '#value' => 'Submit',
	    '#submit' => array('_basicrate_timetablefactors_custom_form_submit'),	
		'#validate' => array('_basicrate_timetablefactors_custom_form_validate'),	
		'#weight' => 0,
	);
	$form['#prefix'] = '<div id="form_content">';
	$form['#suffix'] = '</div>';           
    $form['actions']['submit']['#ajax'] = array(
        'wrapper' => 'form_content',
        'callback' => '_basicrate_timetablefactors_custom_form_submit_callback',
        'method' => 'replace',
        'effect' => 'fade',
    );
	
    return $form;
}

function _basicrate_timetablefactors_custom_form_submit_callback($form, &$form_state){
	$form_state['rebuild'] = TRUE;
    return $form;
}

function _basicrate_timetablefactors_custom_form_submit($form, &$form_state){
	$input = $form_state['input'];
	
	$nids = array();
	$priceAmount = array();
	$priceUnit = $input['price_unit'];
	$uomAmount = array();
	$uomUnit = $input['uom_unit'];
	
	$inputKeys = array_keys($input);
	foreach($inputKeys as $item){
		if(strpos($item,'price_amount_') === 0){
			$temp = explode('price_amount_',$item);
			$nids[] = $temp[1];
			$priceAmount[$temp[1]] = $input[$item];
		}
		if(strpos($item,'uom_amount_') === 0){
			$temp = explode('uom_amount_',$item);
			$uomAmount[$temp[1]] = $input[$item];
		}
	}
	
	foreach($nids as $item){
		$node = node_load($item);
		$node->field_price_amount['und'][0]['value'] = $priceAmount[$item];
		$node->field_price_units['und'][0]['tid'] = $priceUnit;
		$node->field_uom_amount['und'][0]['value'] = $uomAmount[$item];
		$node->field_uom_units['und'][0]['tid'] = $uomUnit;
		node_save($node);
	}
}

function _basicrate_timetablefactors_custom_form_validate($form, &$form_state){
	if(!$form_state['values']['price_unit']){
		form_set_error('price_unit','price_unit is not selected'); 
	}
	if(!$form_state['values']['uom_unit']){
		form_set_error('uom_unit','uom_unit is not selected');
	}
}

function _get_select_option_from_vocabulary($vocaName){
	$vocabulary = taxonomy_vocabulary_machine_name_load($vocaName);
	$termTree = taxonomy_get_tree($vocabulary->vid);
	$options = array();
	$options[] = '==SELECT==';
	foreach($termTree as $item){
		$options[$item->tid] = $item->name;
	}	
	return $options;
}

function _basicrate_timetablefactors_custom_form_get_table_header(){
	$header = array(
		array('data' => 'Carrier'),
		array('data' => 'Rating Group'),
    	array('data' => 'Name'),
        array('data' => 'Holiday'),
        array('data' => 'MON'),
        array('data' => 'TUE'),
        array('data' => 'WED'),
        array('data' => 'THU'),
        array('data' => 'FRI'),
        array('data' => 'SAT'),
        array('data' => 'SUN'),
        array('data' => 'From'),
        array('data' => 'To'),
        array('data' => 'Price'),
        array('data' => 'Unit of Measure amount'),
    );    
    return $header;
}

function _basicrate_timetablefactors_custom_form_get_table_output($header,$rows){
	$tableArgs = array(
	    'header' => $header,
	    'rows' => $rows,
	    'sticky' => 'sticky',
	    'empty' => 'There are no timetablefactors',
	    'attributes' => array(),
	    'colgroups' => array(),
	    'caption' => NULL,
    );    
    $tableThemeResult = theme_table($tableArgs);    
    return $tableThemeResult;
}

function _create_node_form_in_tree($contentType,$parentType,$parentNid,$weight,$rootNid,$refTreeNid){
	global $user;
	ctools_include('node.pages', 'node', '');
	
	switch ($contentType){
		default:
			$node = (object) array(
					'uid' => $user->uid,
					'name' => (isset($user->name) ? $user->name : ''),
					'type' => $contentType,
					'language' => 'und',
					'field_weight' => array('und' => array(0 => array('value' => $weight))),
					'field_ref_product' => array('und' => array(0 => array('nid' => $rootNid))),
					'field_ref_numberspecial' => array('und' => array(0 => array('nid' => ($contentType == 'tariffplan')?NULL:$rootNid))),
					'field_ref_tree_nid' => array('und' => array(0 => array('nid' => $refTreeNid))),
			);
			
			if($parentType == 'node'){
				$node->field_parent_node['und'][0]['nid'] = $parentNid;
			}else{
				$node->field_ref_tree_tid['und'][0]['value'] = $parentNid;
			}
			
			$form_state['root_nid'] = $rootNid;			
			
			$form_state['build_info']['args'] = array($node);
			$form = drupal_build_form($contentType . '_node_form', $form_state);
			
			$formRender = drupal_render($form);
			break;
	}	
	
	return $formRender;
}

function _edit_node_form_in_tree($nid, $additionalParams){
	module_load_include('inc','node','node.pages');
	$node = node_load($nid);
	
	if($node->type === 'treenodewithnodereference'){
		$realNode = node_load($node->field_ref_node['und'][0]['nid']);
		if($realNode->type === 'timetable'){
			$form_state['build_info']['args'] = array($node);
			$form = drupal_build_form('_basicrate_timetablefactors_custom_form', $form_state);
		}
	}else{		
		// $form_state['build_info']['args'] = array($node);
		$form_state['build_info']['args'][] = $node;
		$form_state['build_info']['args'][] = $additionalParams;
		
		$form = drupal_build_form($node->type . '_node_form', $form_state);
	}
	
	$formRender = drupal_render($form);
	
	return $formRender;
}
?>

<?php
function get_children_for_export($nid) {
    $node = node_load($nid);
    
    $item = array(         
    	'data' => _create_export_data_by_content_type($node),
    );
    
    $viewData = get_viewdata('query_tree_by_root_nid', $node->nid);
    
    if(count($viewData) == 0) {
        //$item['children'] = NULL;
    } else {
        foreach ($viewData as $viewRow) {
            _create_export_meta_data_by_content_type($node,$item);
        	$item['children'][] = get_children_for_export($viewRow['nid']);
        }
    }

    return $item;
}

function _make_json_string($termName,$export_item_list){
	switch($termName){
		case 'COUNTER':
			$jsonString = export_counter($export_item_list);
			break;
		case 'PRODUCT':
			$jsonString = export_product($export_item_list);
			break;
		case 'VOUCHER':
			$jsonString = export_voucher_cardtype($export_item_list);
			break;
		case 'CONTENT':
			$jsonString = export_content_rateid($export_item_list);
			break; 
		case 'DEPOSIT_SCHEME':
    	$jsonString = export_deposit_scheme($export_item_list);
      break;
		case 'THRESHOLD_SCHEME':
    	$jsonString = export_threshold_scheme($export_item_list);
      break;
		case 'LIFECYCLE_SCHEME' :
			$jsonString = export_lifecycle_scheme($export_item_list);
			break;
		case 'MESSAGES':
			$jsonString = export_message($export_item_list);
			break;
    case 'TV_CHANNEL':
    	$jsonString = export_tvchannel($export_item_list);
      break;
		case 'EXCLUSIVENESS':
			$jsonString = export_exclusiveness($export_item_list);
			break;
		case 'RATING_RULES':
			$jsonString = rating_rules_export_all();
			break;
		case 'PCRF_COMMON_DATA':
			$jsonString = json_encode(rating_rules_export_by_content_type('pcrf_rule_export',  array()));
			break;
		case 'OCS_GLOBAL_CONFIG':
			$jsonString = export_ocs_config();
			break;
		
	}
	
	return $jsonString;
}

// function export_json($tid,$termName,$refNid=NULL){
function export_json($export_type,$export_nid=NULL){

	$export_item_list = array();
	if(!empty($export_nid)) {
		$export_item_list = array(node_load($export_nid));
  } 
  
	$jsonString = _make_json_string($export_type,$export_item_list);
	$output = _indent_json_string($jsonString);
	return $output;
}

function export_deploy($export_type,$export_item_list, $target){
	global $user;
	
	if(count($export_item_list) == 1) {
		$export_item_list = array($export_item_list);
	}
	$jsonString = _make_json_string($export_type,$export_item_list);
	
	$exportTypeTerm = current(taxonomy_get_term_by_name($export_type));
	
	// Create History Record
	$historyNode = new StdClass();
  $historyNode->uid = $user->uid;
  $historyNode->type = 'export_history';
  $historyNode->language = 'und';

	$exportItemNids = array_keys($export_item_list);
	$index=0;
	foreach($exportItemNids as $nid) {
		$historyNode->field_reference_node['und'][$index++]['nid'] = $nid;
	}
	
  $historyNode->field_export_data['und'][0]['safe_value'] = $jsonString;
  $historyNode->field_export_data['und'][0]['value'] = $jsonString;
  
  $historyNode->field_export_type['und'][0]['tid'] = $exportTypeTerm->tid;

	//send deploy request
	$options = array();
	$options['method'] = 'POST';
	$options['headers']['content-type']= 'application/json';
	$options['headers']['User-Agent'] = 'Product Catalog';
	$options['data'] = $jsonString;
	
    if($target == 'testbed'){
        $targetItem = $exportTypeTerm->field_export_url_testbed['und'];
    }else if($target == 'commercial'){
        $targetItem = $exportTypeTerm->field_export_url_commercial['und'];
    }
    $historyNode->field_export_target['und'][0]['value'] = $target;
    $historyNode->field_export_target['und'][0]['safe_value'] = $target;
    
	foreach($targetItem as $item){
		$url = $item['safe_value'];
		$result = drupal_http_request($url, $options);
		 
		dsm($result,'deploy result');

		if($result->code === '200'){
			//$historyNode = node_load($historyNodeNid);
			//if(strpos($result->request,'/cs/') !== FALSE) $historyNode->field_deployed_cs['und'][0]['value'] = TRUE;
			//if(strpos($result->request,'/ocs/') !== FALSE) $historyNode->field_deployed_ocs['und'][0]['value'] = TRUE;
			//if(strpos($result->request,'/crm/') !== FALSE) $historyNode->field_deployed_crm['und'][0]['value'] = TRUE;
			//node_save($historyNode);
		}
        
        unset($result->request);
        $resultString = json_encode($result);
        $historyNode->field_export_result['und'][] = array('value' => $resultString,'safe_value' => $resultString);
	}
	node_save($historyNode);
	
	$redirect_url = 'lifecycles/history/'.$exportTypeTerm->tid;
	drupal_goto($redirect_url);
}

function _get_export_type_by_content_type($content_type) {
	$export_types = array('simpleproductoffering' => 'PRODUCT',
												'counter'								=> 'COUNTER',
												'vouchercardtype'				=> 'VOUCHER',
												'depositscheme'					=> 'DEPOSIT_SCHEME',
												'thresholdscheme'				=> 'THRESHOLD_SCHEME',
												'lifecyclescheme'				=> 'LIFECYCLE_SCHEME',
												'unittransfer'					=> 'UNIT_TRANSFER_SCHEME',
												'ocs_messages'					=> 'MESSAGES',
												'ocs_message_group'			=> 'MESSAGES',
												'tvchannel'							=> 'TV_CHANNEL',
												'contentrateid'					=> 'CONTENT'
	);
	
	return $export_types[$content_type];
}

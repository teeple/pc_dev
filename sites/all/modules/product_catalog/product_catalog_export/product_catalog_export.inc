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

function _make_json_string($termName,$exportItemNids = NULL,$target=NULL){

	$jsonString = '';
	switch($termName){
		case 'COUNTER':
			$jsonString = export_counter($exportItemNids);
			break;
			
		case 'PRODUCT_GROUP':
			$jsonString = export_product_group($exportItemNids);
			break;
			
		case 'PRODUCT_CHANGE_SCHEME':
			$jsonString = export_product_change_scheme($exportItemNids);
			break;
			
		case 'PRODUCT':
		case 'ARCHIVE':
		case 'AUDIT':
			$jsonString = export_product($exportItemNids,$target);
			break;
			
		case 'VOUCHER':
			$jsonString = export_voucher_cardtype($exportItemNids);
			break;
		case 'UNITTRANSFER_SCHEME':
			$jsonString = export_unittransfer_scheme($exportItemNids);
			break;
		case 'CONTENT':
			$jsonString = export_content_rateid($exportItemNids);
			break; 
		case 'DEPOSIT_SCHEME':
			$jsonString = export_deposit_scheme($exportItemNids);
      break;
		case 'THRESHOLD_SCHEME':
    	$jsonString = export_threshold_scheme($exportItemNids);
      break;
		case 'LIFECYCLE_SCHEME' :
			$jsonString = export_lifecycle_scheme($exportItemNids);
			break;
		case 'MESSAGES':
			$jsonString = export_message($exportItemNids);
			break;
		case 'LIFECYCLE_STATUS':	// bhtak 13/3/24 for CRM, export status list
			$jsonString = export_lifecycle_status($exportItemNids);
			break;
    case 'TV_CHANNEL':
    	$jsonString = export_tvchannel($exportItemNids);
      break;
		case 'EXCLUSIVENESS':
			$jsonString = export_exclusiveness($exportItemNids);
			break;
		case 'RATING_RULES':
			$jsonString = rating_rules_export_all();
			break;
		case 'PCRF_COMMON_DATA':
			$jsonString = pcrf_common_data_export();
			break;
		case 'OCS_GLOBAL_CONFIG':
			$jsonString = export_ocs_config();
			break;
	}
	
	return $jsonString;
}

// function export_json($tid,$termName,$refNid=NULL){
function export_json($export_type,$exportItemNid=NULL){

	$jsonString = _make_json_string($export_type,$exportItemNid);
	$output = _indent_json_string($jsonString);
	return $output;
}

function _get_export_base_url($target){
    if($_SERVER['SERVER_ADDR'] === '192.168.1.63' || $_SERVER['SERVER_ADDR'] === '127.0.0.1'){
        $exportIPTerm = taxonomy_get_term_by_name('Development', 'export_ip');
    }else{
        if($target == 'testbed'){
            $exportIPTerm = taxonomy_get_term_by_name('Testbed', 'export_ip');
        }else{
            $exportIPTerm = taxonomy_get_term_by_name('Commercial', 'export_ip');
        }
    }
    $exportIPTerm = current($exportIPTerm);
    $baseURL = $exportIPTerm->field_export_ip['und'][0]['value'];
    
    return $baseURL;
}

function export_deploy($export_type, $export_item_list = NULL, $target, $redirectFlag = TRUE) {
	global $user;
	$baseURL = _get_export_base_url($target);
	
   	$exportItemNids = !empty($export_item_list)? array_keys($export_item_list): array();
   	
	$failedValidation = FALSE;
    switch($export_type){
        case 'PRODUCT':
            foreach($exportItemNids as $exportItemNid){
                $checkValid = validate_product($exportItemNid);
                if($checkValid['is_valid'] == FALSE){
                    $failedValidation = TRUE;
                    break;
                }
            }
            break;
       	case 'PRODUCT_GROUP':
       	   foreach($exportItemNids as $exportItemNid){
       	               $checkValid = validate_product($exportItemNid);
       	               if($checkValid['is_valid'] == FALSE){
       	                   $failedValidation = TRUE;
       	                   break;
       	               }
       	           }
       	           break;
       		break;
    }
    
    if($failedValidation == TRUE){
        $message = $checkValid['base_type'] . ' '. $checkValid['title'] . ':' . $checkValid['reason'];
        drupal_set_message($message, 'error');
        
    }else{
    
    	dsm($export_type, 'export_type');
    	$exportTypeTerm = current(taxonomy_get_term_by_name($export_type));
        
        $jsonString = _make_json_string($export_type,$exportItemNids,$target);
        
    	// Create History Record
    	$historyNode = new StdClass();
        $historyNode->uid = $user->uid;
        $historyNode->type = 'export_history';
        $historyNode->language = 'und';
    
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
    	$options['timeout'] = 120;
    	
    	if(empty($export_item_list)) {
    		if($target == 'testbed'){
    	      $targetItem = $exportTypeTerm->field_export_url_testbed['und'];
    	  } else if($target == 'commercial'){
    	      $targetItem = $exportTypeTerm->field_export_url_commercial['und'];
    	  }
    	  
    	} else {
    		if($target == 'testbed'){
    		      $targetItem = $exportTypeTerm->field_export_url_testbed_by_id['und'];
    		} else if($target == 'commercial'){
    		      $targetItem = $exportTypeTerm->field_export_url_commercial_by_i['und'];
    		}
    	}
    	
    	$historyNode->field_export_target['und'][0]['value'] = $target;
        $historyNode->field_export_target['und'][0]['safe_value'] = $target;
      
    	foreach($targetItem as $item){
    		$url = $baseURL.$item['safe_value'];
    		$result = drupal_http_request($url, $options);
            
            dsm($url,'url');		 
            dsm($result,'deploy result');
    
    		if($result->code === '200'){
    		    $resultData = json_decode($result->data);
                //dsm($resultData,'result data');
    			//$historyNode = node_load($historyNodeNid);
    			$historyNode->field_ocs_result_code['und'][0]['value'] = isset($resultData->OCS->result_code)?$resultData->OCS->result_code:"";
                $historyNode->field_ocs_result_reason['und'][0]['value'] = isset($resultData->OCS->result_reason)?$resultData->OCS->result_reason:"";
                $historyNode->field_cs_result_code['und'][0]['value'] = isset($resultData->CS->result_code)?$resultData->CS->result_code:"";
                $historyNode->field_cs_result_reason['und'][0]['value'] = isset($resultData->CS->result_reason)?$resultData->CS->result_reason:"";
                $historyNode->field_crm_result_code['und'][0]['value'] = isset($resultData->CRM->result_code)?$resultData->CRM->result_code:"";
                $historyNode->field_crm_result_reason['und'][0]['value'] = isset($resultData->CRM->result_reason)?$resultData->CRM->result_reason:"";
    			//node_save($historyNode);
    		}else{
    		    $historyNode->field_ocs_result_reason['und'][0]['value'] = 'Fail';
                $historyNode->field_cs_result_reason['und'][0]['value'] = 'Fail';
                $historyNode->field_crm_result_reason['und'][0]['value'] = 'Fail';
            }
            
    		unset($result->request);
            $resultString = json_encode($result);
            $historyNode->field_export_result['und'][] = array('value' => $resultString,'safe_value' => $resultString);
    	}
    	node_save($historyNode);
    	
    	// $redirect_url = 'lifecycles/history/'.$exportTypeTerm->tid;
    	if($redirectFlag) {
    		$redirect_url = 'lifecycles/history/'.$export_type;
	    	drupal_goto($redirect_url);
	    }
   }
}

function _get_export_type_by_content_type($content_type) {
	$export_types = array('simpleproductoffering' => 'PRODUCT',
												'counter'								=> 'COUNTER',
												'vouchercardtype'				=> 'VOUCHER',
												'depositscheme'					=> 'DEPOSIT_SCHEME',
												'thresholdscheme'				=> 'THRESHOLD_SCHEME',
												'lifecyclescheme'				=> 'LIFECYCLE_SCHEME',
												'unittransfer'					=> 'UNITTRANSFER_SCHEME',
												'ocs_messages'					=> 'MESSAGES',
												'ocs_message_group'			=> 'MESSAGES',
												'tvchannel'							=> 'TV_CHANNEL',
												'contentrateid'					=> 'CONTENT',
												'productgroup'					=> 'PRODUCT_GROUP',
												'productchange'					=> 'PRODUCT_CHANGE_SCHEME'
	);
	
	return $export_types[$content_type];
}

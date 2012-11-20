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

function _make_json_string($termName,$refNid=NULL){
	switch($termName){
		case 'COUNTER':
			$jsonString = export_counter();
			break;
		case 'PRODUCT':
			$jsonString = export_product($refNid);
			break;
		case 'RATING_RULES':
			$jsonString = rating_rules_export_all();
			break;
		case 'VOUCHER':
			$jsonString = export_voucher_cardtype();
			break;
		case 'CONTENT':
			$jsonString = export_content_rateid();
			break; 
        case 'DEPOSIT_SCHEME':
            $jsonString = export_deposit_scheme();
            break;
        case 'THRESHOLD_SCHEME':
            $jsonString = export_threshold_scheme();
            break;
	}
	
	return $jsonString;
}

function export_json($tid,$termName,$refNid=NULL){
	$jsonString = _make_json_string($termName,$refNid);
	$output = _indent_json_string($jsonString);
	return $output;
}

function export_deploy($tid,$termName,$refNid=NULL){
	global $user;
	$jsonString = _make_json_string($termName,$refNid);
	
	//create history record
	$historyNode = new StdClass();
    $historyNode->uid = $user->uid;
    $historyNode->type = 'export_history';
    $historyNode->language = 'und';
    if($refNid != NULL){
    	$historyNode->field_reference_node['und'][0]['nid'] = $refNid;
    }
    $historyNode->field_export_data['und'][0]['safe_value'] = $jsonString;
    $historyNode->field_export_data['und'][0]['value'] = $jsonString;
    $historyNode->field_export_type['und'][0]['tid'] = $tid;
    node_save($historyNode);
    $historyNodeNid = $historyNode->nid;
    
	//send deploy request
	$term = taxonomy_term_load($tid);
	$options = array();
	$options['method'] = 'POST';
	$options['headers']['content-type']= 'application/json';
	$options['headers']['User-Agent'] = 'Product Catalog';
	$options['data'] = $jsonString;
	
	
	foreach($term->field_export_url['und'] as $item){
		$url = $item['safe_value'];
		$result = drupal_http_request($url, $options); 
		//TODO: 寃곌낵 ��� �� 媛������� ��� ����댄� 異���댁� �� 
		//dsm($url,'url');
		//dsm($options,'request options');
		dsm($result,'deploy result');
		if($result->code === '200'){
			$historyNode = node_load($historyNodeNid);
			if(strpos($result->request,'/cs/') !== FALSE) $historyNode->field_deployed_cs['und'][0]['value'] = TRUE;
			if(strpos($result->request,'/ocs/') !== FALSE) $historyNode->field_deployed_ocs['und'][0]['value'] = TRUE;
			if(strpos($result->request,'/crm/') !== FALSE) $historyNode->field_deployed_crm['und'][0]['value'] = TRUE;
			node_save($historyNode);
		}
	}
	
	$redirect_url = 'lifecycles/history/'.$tid;
	drupal_goto($redirect_url);
	
}

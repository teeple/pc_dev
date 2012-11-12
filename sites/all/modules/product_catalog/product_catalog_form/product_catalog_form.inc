<?php
function _get_vocabulary_name($contentType, $productNode, $serviceType = NULL){
	
// dsm($contentType, 'contentType');
// dsm($productNode, 'productNode');
// dsm($$serviceType, 'serviceType');
	
	$reserved_voca_name = array(
			'simpleproductoffering' => array(
					'Cross' => array(
								'Main' => 	array(	'Postpaid' => 'tpl_default_tree_cross_main',
													'Prepaid'  	=> 'tpl_default_tree_cross_main',
													'Hybrid' => 'tpl_default_tree_cross_main'
											),
								),
					'IPTV' => array(
								'Main' 		=> array(	'Postpaid' => 'tpl_default_tree_iptv_main_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_iptv_main_prepaid',
														'Hybrid'     => 'tpl_default_tree_iptv_main_hybrid'
											),
								'Additional' => array(	'Postpaid' => 'tpl_default_tree_iptv_additional_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_iptv_additional_prepaid'
											),
								'VAS' 		=> array(	'Postpaid' => 'tpl_default_tree_iptv_vas_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_iptv_vas_prepaid'
											),
								),
					'Mobile' => array(
								'Main' 		=> array(	'Postpaid' => 'tpl_default_tree_mobile_main_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_mobile_main_prepaid',
														'Hybrid'     => 'tpl_default_tree_mobile_main_hybrid'
											),
								'Additional' => array(	'Postpaid' => 'tpl_default_tree_mobile_additional_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_mobile_additional_prepaid'
											),
								'VAS' 		=> array(	'Postpaid' => 'tpl_default_tree_mobile_vas_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_mobile_vas_prepaid'
											),
								),
					'Broadband' => array(
								'Main' 		=> array(	'Postpaid' => 'tpl_default_tree_broadband_main_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_broadband_main_prepaid',
														'Hybrid'     => 'tpl_default_tree_broadband_main_hybrid'
											),
								'Additional' => array(	'Postpaid' => 'tpl_default_tree_broadband_additional_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_broadband_additional_prepaid'
											),
								'VAS'		=> array(	'Postpaid' => 'tpl_default_tree_broadband_vas_postpaid',
														'Prepaid'  	=> 'tpl_default_tree_broadband_vas_prepaid'
											),
								),
					'VoIP' => array(
								'Main' => array('Postpaid' => 'tpl_default_tree_voip_main_postpaid',
												'Prepaid'  	=> 'tpl_default_tree_voip_main_prepaid',
												'Hybrid'   => 'tpl_default_tree_voip_main_hybrid'
										),
							),
					'Satellite' => array(
								'Main' => array('Postpaid' => 'tpl_default_tree_satellite_main_postpaid',
												'Prepaid'  	=> 'tpl_default_tree_satellite_main_prepaid',
												'Hybrid'   => 'tpl_default_tree_satellite_main_hybrid'
										),
							),
					'Dummy' => array(
								'Main' => array('Postpaid' => 'tpl_default_tree_dummy_main_postpaid',
												'Prepaid'  	=> 'tpl_default_tree_dummy_main_prepaid',
												'Hybrid'   => 'tpl_default_tree_dummy_main_hybrid'
										),
							),
				),
			
			
			'tariffplan' => array(
					"Mobile" => array(
							'Voice' => 'tpl_tariffplan_mobile_voice',
							'SMS'   => 'tpl_tariffplan_mobile_sms',
							'Data'  => 'tpl_tariffplan_mobile_data',
						),
					
					"IPTV" => array(
							'VOD' => 'tpl_tariffplan_mobile_vod',
						),
						
				),
	);
	
	//load taxonomy
	$serviceDomainTerm = taxonomy_term_load($productNode->field_service_type_of_provider['und'][0]['tid']);
	$serviceDomain = $serviceDomainTerm->name;
	
	$productTypeTerm = taxonomy_term_load($productNode->field_product_type['und'][0]['tid']);
	$productType = $productTypeTerm->name;
	
	$billingTypeTerm = taxonomy_term_load($productNode->field_billing_type['und'][0]['tid']);
	$billingType = $billingTypeTerm->name;
	
	switch($contentType) {
		case 'simpleproductoffering':
			$voca_name = $reserved_voca_name[$contentType][$serviceDomain][$productType][$billingType];
			break;
		case 'tariffplan':
			$voca_name = $reserved_voca_name[$contentType][$serviceDomain][$serviceType];
			break;
	}
// dsm($voca_name, 'voca_name');
	return $voca_name;
}

function _condition_select_form($form, &$form_state) {

	$form['condition_type'] = array(
       '#type' => 'select',
       '#title' => t('Condition Type'),
       '#options' => array(
			'==SELECT==',
			'common' => array('conditioncommoncounterfactors' => 'Counter'),
			'what' => array('conditionwhaturlgroupfactors' => 'URLGroup','conditionwhatqos' => 'QoS','conditionwhatcustomfactors' => 'Custom'),
			'when' => array('conditionwhendayfactors' => 'Day','conditionwhendurationfactors' => 'Duration','conditionwhentimeslotfactors' => 'Timeslot'
							,'conditionwhenweekfactors' => 'Week','conditionwhencustomfactors' => 'Custom'),
			'where'=> array('conditionwherecountryfactors' => 'Country','conditionwherenetworkfactors' => 'Network',
							'conditionwherezonefactors' => 'Zone','conditionwherecustomfactors' => 'Custom'),
	        'Who'  => array('conditionwhomemberfactors' => 'Member','conditionwhonumberfactors' => 'Number',
	        				'conditionwhoprefixfactors' => 'Prefix','conditionwhocustomfactors' => 'Custom')
	   ),
	   '#ajax' => array(
	   'callback' => 'ajax_condition_select_form_callback',
	   'wrapper' => 'condition_form_wrapper',
	   ),
        '#description' => t('Select a type of condition for the rule.'),
	);

	return $form;
}

function ajax_condition_select_form_callback($form, $form_state) {

	$condition_type = $form_state['values']['condition_type'];
    $current_path = current_path();
    $rule_nid = $form_state['rule_nid'];

    $rule = node_load($rule_nid);

    if($rule->type == 'rule') {
    	if(isset($form_state['parent_name'])){
    		$redirect_url = 'designer/rules/'.$rule_nid.'/conditions/add/'.$condition_type;
    	}else{
        	$redirect_url = 'common/rules/'.$rule_nid.'/conditions/add/'.$condition_type;
    	}
    } else {
        $redirect_url = 'common/number_sp_rule/'.$rule_nid.'/conditions/add/'.$condition_type;
    }
    // $redirect_url = $condition_type;

    ctools_include('ajax');
    ctools_add_js('ajax-responder');
    $commands[] = ctools_ajax_command_redirect($redirect_url);
    print ajax_render($commands);
    exit;
}

function _load_node_form($buildType,$nodeType=NULL,$nid=NULL,$params=NULL){
	global $user;
	module_load_include('inc', 'node', 'node.pages');

	switch($buildType){
		case 'create':
			if($nodeType == NULL){
				//set error message
				drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
				return;
			}
			$node = new StdClass();
			$node->uid = $user->uid;
			$node->type = $nodeType;
			$node->language = 'und';

			//numbering plan idd duplex link
			if(isset($params['numberingplan_idd_nid'])){
				$node->field_ref_numberingplan_idd['und'][0]['nid'] = $params['numberingplan_idd_nid'];
			}
			//numbering plan domestic duplex link
			if(isset($params['numberingplan_domestic_nid'])){
				$node->field_ref_numberingplan_domestic['und'][0]['nid'] = $params['numberingplan_domestic_nid'];
			}

			node_object_prepare($node);
			break;
		case 'edit':
			if($nid == NULL){
				//set error message
				drupal_set_message($message = 'Can not find nid for Node.', $type = 'error');
				return;
			}
			$node = node_load($nid);
			break;
		default:
			//set error message
			drupal_set_message($message = 'Can not find buildType.', $type = 'error');
			return;
			break;
	}

	$form_state = array();

	if(!empty($params)){
		$paramKeys = array_keys($params);
		$paramValues = array_values($params);
		$numberOfParams = count($paramKeys);
		for($i = 0; $i < $numberOfParams; $i++){
			$form_state[$paramKeys[$i]] = $paramValues[$i];
		}
	}

	$form_state['build_info']['args'] = array($node);
	$formName = $nodeType.'_node_form';
	$form = drupal_build_form($formName, $form_state);

	$output = drupal_render($form);
	return $output;
}

function make_taxonomy_view_form($form, &$form_state, $productNid, $vocabularyName){

	$vocabulary = taxonomy_vocabulary_machine_name_load($vocabularyName);
	//tree 를 가져올 때, sorting 되서 가져 오는 듯..
	$tree = taxonomy_get_tree($vocabulary->vid);
	$current_path = base_path().current_path();

	//load product
	$product = node_load($productNid);

    $event_list = array();

    $addBasicRate = FALSE;

	switch($vocabularyName){
		case 'service_of_nonusage':
			$temp_path = explode('/nonusage',$current_path);
			$current_path = $temp_path[0].'/nonusage';

            $viewName = 'query_nonusage_nid_by_product_nid';

			break;

		case 'service_of_usage':
			$temp_path = explode('/usage',$current_path);
			$current_path = $temp_path[0].'/usage';

            $viewName = 'query_usage_nid_by_product_nid';

            $addBasicRate = TRUE;
			break;
	}

    $view = views_get_view($viewName);
    $view->set_arguments(array('0'=>$productNid));
    $view->execute();

    $temp_array_result =$view->result;
    foreach($temp_array_result as $item) {
       $array_temp = objectToArray($item);
       $nid = array_shift($array_temp);
       $tid = array_shift($array_temp);
       $event_list[$tid] = $nid;
    }

	$header = array(
		array('data' => 'Event'),
		array('data' => 'Rule'),
	);
	$rows = array();
	foreach($tree as $item){
		$countDepth = $item->depth;
		$markup = '';
		for($i = 0; $i < $countDepth; $i++){
			$markup = $markup.'&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
		}

		if(!empty($event_list[$item->tid])){
			if($addBasicRate){
				$ruleContext = '<a href="'.$current_path.'/basic/'.$event_list[$item->tid].'">Rate</a>&nbsp;&nbsp;&nbsp;<a href="'.$current_path.'/additional/'.$event_list[$item->tid].'">Rule</a>';
			}else{
				$ruleContext = '<a href="'.$current_path.'/'.$event_list[$item->tid].'">Rule</a>';
			}
		}else{
			$ruleContext = '';
		}
		$rows[] = array(
			$markup.$item->name,
			$ruleContext,
		);

	}

	$args = array(
        'header' => $header,
        'rows' => $rows,
        'sticky' => 'sticky',
        'empty' => 'it is empty..',
        'attributes' => array(),
        'colgroups' => array(),
        'caption' => '',
	);

	$theme_table_result = theme_table($args);

	$form['terms'] = array(
        '#type' => 'markup',
        '#markup' => $theme_table_result
	);
	//$form = taxonomy_overview_vocabularies($form);
	return $form;
}

function _get_condition_type_human_readible($type) {

    $condition_type_1 = substr($type, 0, -7); // remove suffix 'factors'
    $pattern = array( '/conditionwhat/', '/conditionwhen/', '/conditionwho/', '/conditionwhere/');
    $replacement = '';
    return preg_replace($pattern, $replacement, $condition_type_1);
}

function _load_node_form_without_render($buildType,$nodeType=NULL,$nid=NULL,$params=NULL){
	global $user;
	module_load_include('inc', 'node', 'node.pages');

	switch($buildType){
		case 'create':
			if($nodeType == NULL){
				//set error message
				drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
				return;
			}
			$node = new StdClass();
			$node->uid = $user->uid;
			$node->type = $nodeType;
			$node->language = 'und';

			//numbering plan duplex link
			if(isset($params['numberingplan_idd_nid'])){
				$node->field_ref_numberingplan_idd['und'][0]['nid'] = $params['numberingplan_idd_nid'];
			}

			node_object_prepare($node);
			break;
		case 'edit':
			if($nid == NULL){
				//set error message
				drupal_set_message($message = 'Can not find nid for Node.', $type = 'error');
				return;
			}
			$node = node_load($nid);
			break;
		default:
			//set error message
			drupal_set_message($message = 'Can not find buildType.', $type = 'error');
			return;
			break;
	}

	$form_state = array();

	if(!empty($params)){
		$paramKeys = array_keys($params);
		$paramValues = array_values($params);
		$numberOfParams = count($paramKeys);
		for($i = 0; $i < $numberOfParams; $i++){
			$form_state[$paramKeys[$i]] = $paramValues[$i];
		}
	}

	$form_state['build_info']['args'] = array($node);
	$formName = $nodeType.'_node_form';
	$form = drupal_build_form($formName, $form_state);

	return $form;
}

function numberingplan_domestic_view_form($form, &$form_state) {	
	$view = views_get_view('list_numberingplan_domestic_ratinggroup');
	$view->execute_display('panel_pane_2', array('0' => $form_state['param']['plan_nid']));
	$output = $view->render();
		
	$form['view'] = array(
		'#type' => 'markup',
		'#markup' => $output,
	);	
	return $form;
}

function depositscheme_view_form($form, &$form_state) {
	$output = '<div><h2>Deposit Scheme Factors</h2></div>' ;
	$view = views_get_view('list_depositschemefactors');
	$view->execute_display('panel_pane_2', array('0' => $form_state['param']['depositscheme_nid']));
	$output .= $view->render();
	
	$output .= '<hr>';
	$output .= '<div><h2>Deposit Scheme Adjustment</h2></div>';
	$view = views_get_view('list_depositschemeadjustment');
	$view->execute_display('panel_pane_2', array('0' => $form_state['param']['depositscheme_nid']));
	$output .= $view->render();
	
	$form['view'] = array(
			'#type' => 'markup',
			'#markup' => $output,
	);
	
	return $form;
}

function thresholdscheme_view_form($form, &$form_state) {
	$view = views_get_view('list_thresholdschemefactors');
	$view->execute_display('panel_pane_2', array('0' => $form_state['param']['thresholdscheme_nid']));
	$output .= $view->render();

	$form['view'] = array(
			'#type' => 'markup',
			'#markup' => $output,
	);

	return $form;
}

function numberingplan_idd_view_form($form, &$form_state) {
	$view = views_get_view('list_numberingplan_idd_ratinggroup');
	$view->execute_display('panel_pane_2', array('0' => $form_state['param']['plan_nid']));
	$output = $view->render();

	$form['view'] = array(
			'#type' => 'markup',
			'#markup' => $output,
	);
	return $form;
}

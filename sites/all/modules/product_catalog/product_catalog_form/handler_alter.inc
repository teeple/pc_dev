<?php
function _unset_menu_items(&$form,$formId){
	unset($form['menu']);
	unset($form['path']);
	unset($form['author']);
	unset($form['comment_settings']);
	unset($form['options']);
	unset($form['additional_settings']);
	unset($form['actions']['preview']);
	unset($form['revision_information']);
	
	$unsetDeleteButton = TRUE;
	
	switch($formId){
		case 'numberingplan_domestic_node_form':
		case 'numberingplan_idd_node_form':
		case 'carrier_mobile_node_form':
			$unsetDeleteButton = FALSE;
			//dsm($form);
			break;
	}
	
	if($unsetDeleteButton)unset($form['actions']['delete']);
	
}

function _add_ajax_submit_callback($form_id,&$form){
	$change = FALSE;
	//dsm($form_id);
    $changeEachRow = FALSE;
    
	switch($form_id){
		case 'conditionwhatcustomfactors_node_form':
		case 'conditionwhaturlgroupfactors_node_form':
		case 'conditionwhencustomfactors_node_form':
		case 'conditionwhendurationfactors_node_form':
		case 'conditionwhendayfactors_node_form':
		case 'conditionwhentimeslotfactors_node_form':
		case 'conditionwhenholidayfactors_node_form':
		case 'conditionwhenweekfactors_node_form':
		case 'conditionwherecountryfactors_node_form':
		case 'conditionwherecustomfactors_node_form':
		case 'conditionwherenetworkfactors_node_form':
		case 'conditionwherezonefactors_node_form':
		case 'conditionwhocustomfactors_node_form':
		case 'conditionwhomemberfactors_node_form':
		case 'conditionwhonumberfactors_node_form':
		case 'conditionwhoprefixfactors_node_form':
		case 'conditioncommoncounterfactors_node_form':
		case 'conditionwhatqos_node_form':
		case 'conditioncommoncarrieridd_node_form':
        case 'conditioncommoncarrierdomestic_node_form':
        case 'conditioncommonratinggroup_node_form':
        case 'conditioncommontimetablefactors_node_form':
        case 'actionpricediscountfactors_node_form':
        case 'actionpriceallowancefactors_node_form':
        case 'actionpricechargefactors_node_form': 
        case 'actionpricechargeonetime_node_form':
        case 'actionpricechargerecurring_node_form':
        case 'actionpricediscount_node_form':
        case 'actionpriceallowance_node_form':
        case 'tariffplan_node_form':
        case 'numberspecialfactors_node_form':
        case 'treenodecounter_node_form':
        case 'prdattributeprefixrangeallowed_node_form':
        case 'prdattributeprefixrangenotallowe_node_form':
        case 'unittransferfactors_node_form':
        case 'conditionwhatservicetypefactors_node_form':       
        case 'number_special_node_form':
        case 'prdattributefeaturecode_node_form':
        case 'prdattributebenefit_node_form':
        case 'loyaltypoint_node_form':        
        case 'actionbonustransfer_node_form':
        case 'conditionwhatcalltype_node_form':
        case 'conditionwhatcounter_node_form':        	
        	$change = TRUE;
        	break;
        	
        case 'views_form_list_treenodecounterforvoucher_panel_pane_1':
            $changeEachRow = TRUE;
            break;
        case 'vouchercardtype_node_form':
        case 'unittransfer_node_form':
            if(isset($form['nid']['#value'])) { // edit
                $change = TRUE;
            }
            break;
        case 'simpleproductoffering_node_form':
        	if(isset($form['nid']['#value'])) { //edit
        	$change = TRUE;
        	}
        	break;
	}

	if($change){
		unset($form['actions']['submit']['#submit']);
	    unset($form['#validate']);
	    $form['actions']['submit']['#id'] = 'submit-in-ajax-callback';
	    $form['#prefix'] = '<div id="form_content">';
	    $form['#suffix'] = '</div>';           
	
	    $form['actions']['submit']['#ajax'] = array(
	        'wrapper' => 'form_content',
	        'callback' => 'edit_pane_callback',
	        'method' => 'replace',
	        'effect' => 'fade',
	        //'parameters' => array('haha' => 'hoho')
	    );
	}

    /*
    if($changeSpecial) {
		unset($form['actions']['submit']['#submit']);
	    unset($form['#validate']);
    }
    */
}

function edit_pane_callback($form, &$form_state){

	$newNode = node_load($form['nid']['#value']);
    $form_state['values']['changed'] = $newNode->changed;

    node_form_validate($form, $form_state);

    if(!form_get_errors()) {
        node_form_submit($form, $form_state);

        foreach($form_state['ajax_actions'] as $functionName) {
            $evalString = $functionName.'($form, $form_state);';
            eval($evalString);
        }
    } 
    $form_state['rebuild'] = TRUE;
    return $form;
}

function product_catalog_form_form_alter(&$form, &$form_state, $form_id) {
	// dsm('--- form alter --');
	// dsm($form_id);
// dsm($form, 'form_alter: '.$form['#form_id']);
// dsm($form_state, 'form_state');
    // error_log('form_id: '. $form_id);
    if(isset($form['#attributes']) && gettype($form['#attributes']['class']) == 'array') {
    	$form['#attributes']['class'][] = 'myform';
    	
    }
    
    switch($form_id){
		case 'views_exposed_form':
			switch($form['#id']) {
				case 'views-exposed-form-list-vouchercardtype-panel-pane-1':
					$form['field_ref_voucher_type_tid']['#options']['All'] = '- type -';
					break;
				case 'views-exposed-form-list-counter-panel-pane-1':
					$form['field_billing_type_counter_tid']['#options']['All'] = '- billtype -';
					$form['field_service_domain_tid']['#options']['All'] = '- domain -';
					break;
			}
			// $form['field_ref_voucher_type_tid'] 
			
			break;
		case 'views_form_list_counter_for_vouchercardtype_panel_pane_2':
			unset($form['actions']['submit']);
			break;
			
		case 'views_form_list_basicrate_panel_pane_2':
			unset($form['actions']['submit']);
			
			//get related rates..
			$tariffplanNid = $form_state['build_info']['args'][0]->args[1];
			$refTreeTid = $form_state['build_info']['args'][0]->args[2];
			
			$rateView = views_get_view('list_rates');
			$rateView->set_display('panel_pane_2');
			$rateView->set_arguments(array('0' => $tariffplanNid, '1' => $refTreeTid));
			$rateView->execute();
			
			$rateOptions = array();
			$rateOptions['_none' ] = '- None -';
			foreach($rateView->result as $rateItem){
				$rateOptions[$rateItem->nid] = $rateItem -> node_title;
			}
			
			$rowCount = count($form['field_ref_rate']);
			for($i=0;$i<$rowCount;$i++){
				$form['field_ref_rate'][$i]['field_ref_rate']['und']['#options'] = $rateOptions;
			}
			
			break;
        case 'views_form_list_treenodecounterforvoucher_panel_pane_1';
            //dsm($form, 'form');
            unset($form['actions']);
            break;
            
            
        case 'depositscheme_node_form':
        	// unset($form['field_service_domain']);
        	unset($form['field_ref_depositschemefactors']);
        	unset($form['field_ref_depositschemeadjustmen']);
        	unset($form['rdf_mapping']);
        	unset($form['body']);
        	
        	_unset_menu_items($form,$form_id);
        	break;
        	
        case 'thresholdscheme_node_form':
        	_unset_menu_items($form, $form_id);
        	break;
        	
        case 'thresholdschemefactors_node_form':
        	$form['field_ref_thresholdscheme']['#type'] = 'hidden';
        	_unset_menu_items($form, $form_id);
        	break;
        	
        	
        case 'vouchercardtype_node_form':
        	
        	//$form['field_tree_child_voca_name']['und']['#default_value'][0] = 'tbl_vouchercardtype';
        	$form['field_tree_child_voca_name']['#type'] = 'hidden';
        	_unset_menu_items($form,$form_id);
            
            if(!isset($form['nid']['#value'])){
			    $form['actions']['submit']['#submit'][] = '_vouchercardtype_submit_handler';			
			    $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            }
            break;
            
        case 'loyaltypoint_node_form':
        	
        	// loyaltypoint에 사용되는 counter는 point용 counter만 볼 수 있도록 한다.
        	// counter_group이 Point인 것들만 리스팅한다.
        	//
        	$viewResult = views_get_view_result('list_counter_for_vouchercardtype','panel_pane_3');
        	
        	$counters = array();
        	$counters['_none'] = '- None -';
        	foreach($viewResult as $record) {
        		$counters[$record->nid] = $record->node_title;
        	}
        	$form['field_ref_counter']['und']['#options'] = $counters;
        	
        	unset($form['field_ref_vouchercardtype']);
        	_unset_menu_items($form, $form_id);
        	break;
        	
        case 'loyaltypointfactors_node_form':
        	unset($form['field_ref_loyaltypoint']);
        	_unset_menu_items($form, $form_id);
        	break;
        	
        case 'prdattributeprefixrangeallowed_node_form':
        case 'prdattributebenefit_node_form':
        case 'prdattributeprefixrangenotallowe_node_form':
        case 'prdattributefeaturecode_node_form':
            $form['field_parent_node']['#type'] = 'hidden';
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            _unset_menu_items($form,$form_id);
            break;
            
        case 'treenodecounter_node_form':
            $form['title']['#type'] = 'hidden';
            $form['field_ref_counter']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_main_or_accumulated']['#type'] = 'hidden';
            
            _unset_menu_items($form,$form_id);

            // 기존 counter list를 가져오는 부분은 없애고, 현재 선택된 counter중에서만 next counter를 찾기 위함
            $siblings = array();
            unset($form['field_rollover_next_counter']['und']['#options']);
            $form['field_rollover_next_counter']['und']['#options'] = array('_none' => '- None -');
            $viewResult = views_get_view_result('list_treenodecounter', 'panel_pane_1', array('0' => $form['nid']['#value']));
            foreach($viewResult as $item){
                // sibling에 자신은 제외 
                if($item->nid != $form['nid']['#value']) {
                    $form['field_rollover_next_counter']['und']['#options'][$item->nid] =  $item->node_field_data_field_ref_counter_title;
                }
            }
            break;
        case 'conditionwhatcalltype_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'counter_node_form':
            unset($form['field_parent_node']);
            unset($form['field_weight']);
			_unset_menu_items($form,$form_id);
			
// dsm($form, 'form');
// dsm($form_state, 'form_state');
// 생성 시
			if(!isset($form['nid']['#value'])){
				$view = views_get_view('query_counter_max_id');
				$view->execute();
				$viewResult = $view->result;
				
				foreach($viewResult as $record) {
					$maxCounterId = view_get_field_value_by_label($view	, 'max_counter_id', $record);
				}
				$form['field_counter_id']['und'][0]['value']['#default_value'] = $maxCounterId + 1;
			}
			
			$form['actions']['submit']['#submit'][] = '_common_counter_submit_handler';
			$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            break;

		case 'simpleproductoffering_node_form':
			if(isset($form['field_r_prodofferingrel']))unset($form['field_r_prodofferingrel']);
			if(isset($form['field_r_productspecification']))unset($form['field_r_productspecification']);
			if(isset($form['field_r_prodspeccharvalueuse']))unset($form['field_r_prodspeccharvalueuse']);
			if(isset($form['field_r_productofferingprice']))unset($form['field_r_productofferingprice']);
			if(isset($form['field_r_productofferingprice']))unset($form['field_r_productofferingprice']);
			
			unset($form['field_product_type']);
			unset($form['field_parent_node_for_rp']);
			unset($form['field_weight_for_ratingpriority']);
			unset($form['field_weight']);
			unset($form['field_ref_nonusage']);
			unset($form['field_ref_usage']);
			unset($form['field_ref_counter']);
			unset($form['field_ref_number_sp_allowed']);
			unset($form['field_ref_number_sp_forbidden']);
			unset($form['field_parent_node']);
			unset($form['field_tpl_voca_machine_name']);
			_unset_menu_items($form,$form_id);	
			
			// only for create
			//
			if(!isset($form['nid']['#value'])){
				$form['field_service_type_of_provider']['und']['#default_value'][0] = $form_state['service_domain_tid'];
				_alter_simpleproductoffering_node_form($form, $form_state);
			}
			
			break;
		case 'balance_node_form':
		case 'context_admin_node_form_wrapper':
		case 'prodoffernonusagesubitem_node_form':

		// sub factors
		case 'conditionwhatservicetypefactors_node_form':
		case 'conditionwhatcustomfactors_node_form':
		case 'conditionwhaturlgroupfactors_node_form':
		case 'conditionwhencustomfactors_node_form':
		case 'conditionwhendurationfactors_node_form':
		case 'conditionwhendayfactors_node_form':
		case 'conditionwhentimeslotfactors_node_form':
		case 'conditionwhenholidayfactors_node_form':

		case 'conditionwhenweekfactors_node_form':
		case 'conditionwherecountryfactors_node_form':
		case 'conditionwherecustomfactors_node_form':
		case 'conditionwherenetworkfactors_node_form':
		case 'conditionwherezonefactors_node_form':
		case 'conditionwhocustomfactors_node_form':
		case 'conditionwhomemberfactors_node_form':
		case 'conditionwhonumberfactors_node_form':
		case 'conditionwhoprefixfactors_node_form':
		case 'conditioncommoncounterfactors_node_form':
		case 'conditionwhatqos_node_form':

			_unset_menu_items($form,$form_id);
			unset($form['field_weight']);
			unset($form['field_parent_node']);
			//$form['actions']['submit']['#submit'][] = '_condition_submit_handler';
			//$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            break;

		case 'conditionwhaturlgroups_node_form':
		case 'conditionwhatcustom_node_form':
		case 'conditionwhencustom_node_form':
		case 'conditionwhenday_node_form':
		case 'conditionwhenduration_node_form':
		case 'conditionwhentimeslot_node_form':
		case 'conditionwhenweek_node_form':
		case 'conditionwherecountry_node_form':
		case 'conditionwherecustom_node_form':
		case 'conditionwherenetwork_node_form':
		case 'conditionwherezone_node_form':
		case 'conditionwhocustom_node_form':
		case 'conditionwhomember_node_form':
		case 'conditionwhonumber_node_form':
		case 'conditionwhoprefix_node_form':
			_unset_menu_items($form,$form_id);
			//$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
			//$form['actions']['submit']['#submit'][] = '_condition_submit_handler';
			break;
		case 'feeds_import_form':
			$form['#submit'][] = 'product_catalog_form_form_redirect_handler';
			break;
		case 'area_code_node_form':
			_unset_menu_items($form,$form_id);
			break;
		case 'number_special_node_form':
			$form['actions']['submit']['#submit'][] = '_number_special_submit_handler';			
			_unset_menu_items($form,$form_id);
			unset($form['field_parent_node']);
            unset($form['field_weight']);
			break;
		case 'views_form_list_area_ratinggroup_panel_pane_1':
			unset($form['actions']['submit']['#suffix']);
			break;

        case 'number_ratinggroup_node_form':
			$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
			unset($form['field_ref_number_sp_rule']);
			_unset_menu_items($form,$form_id);
            break;
        case 'number_special_rule_node_form':
            unset($form['field_ref_action_charge']);
            unset($form['field_ref_action_discount']);
            unset($form['field_ref_action_allow']);
            unset($form['field_ref_action_system']);
			$form['actions']['submit']['#submit'][] = '_number_sp_rule_submit_handler';
			$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            unset($form['field_ref_condition_factor']);
            _unset_menu_items($form,$form_id);
            break;      
        case 'actionpricefactors_node_form':
            _alter_field_action_price_factors($form, $form_state);
			$form['actions']['submit']['#submit'][] = '_rule_actionprice_submit_handler';
			$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
			_unset_menu_items($form,$form_id);
            break;

        case 'carrier_node_form':
			$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            unset($form['field_ref_prefix']);
            unset($form['field_ref_rating_group']);
            unset($form['field_service_type_of_provider']);
            unset($form['field_service_type_of_carrier']);
			_unset_menu_items($form,$form_id);

            break;
        case 'prefix_node_form':
            // only for create
            //
            if(!isset($form['nid']['#value'])){
                $form['actions']['submit']['#submit'][] = '_prefix_link_to_carrier';
            }
        	_unset_menu_items($form,$form_id);
        	unset($form['field_ref_area_code']);
        	break;

        case 'rule_node_form':
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';

			// only for create
            //
            if(!isset($form['nid']['#value'])){

                if(isset($form_state['ratinggroup_nid'])){
                    $form['actions']['submit']['#submit'][] = '_rule_link_to_rattinggroup';
                } else if (isset($form_state['nonusage_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_rule_link_to_nonusage';
                } else if (isset($form_state['usage_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_rule_link_to_usage';
                } else if (isset($form_state['counter_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_rule_link_to_counter';
                }
            }
            unset($form['field_ref_condition_factors']);
            unset($form['field_ref_action_charge']);
            unset($form['field_ref_action_discount']);
            unset($form['field_ref_action_allowance']);
            unset($form['field_ref_action_system']);
            _unset_menu_items($form,$form_id);
            break;
        case 'rating_group_node_form':
			// only for create
            //
            if(!isset($form['nid']['#value'])){
                $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_carrier';
            }
        	unset($form['field_ref_rule']);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'numberingplan_idd_node_form':
        	unset($form['field_ref_idd_ratinggroup']);
        	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
        	_unset_menu_items($form,$form_id);
        	break;        
        case 'idd_ratinggroup_node_form':
        	// only for create
            //
            if(!isset($form['nid']['#value'])){
                if(isset($form_state['numberingplan_idd_nid'])){
                    $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_numberingplan_idd';
                }
            }
            //unset($form['field_ref_numberingplan_idd']);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'basicrate_idd_node_form':
        	unset($form['title']);
            unset($form['field_ref_condition_idd']);
            unset($form['revision_information']);
            unset($form['field_parent_node']);
            unset($form['field_weight']);

            // only for create
            //
            if(!isset($form['nid']['#value'])){
                $form['actions']['submit']['#submit'][] = '_basicrate_idd_link_to_usage';
            }
        	_unset_menu_items($form,$form_id);
            break; 
        case 'basicrate_domestic_node_form':
        	unset($form['title']);
            unset($form['revision_information']);
            unset($form['field_parent_node']);
            unset($form['field_weight']);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'numberingplan_domestic_node_form':
        	
        	//unset($form['field_ref_domestic_ratinggroup']);
        	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
        	unset($form['field_ref_domestic_ratinggroup']);
        	_unset_menu_items($form,$form_id);
        	break;

        case 'depositschemefactors_node_form':
        case 'depositschemeadjustment_node_form':
        	_unset_menu_items($form,$form_id);
        	$form['field_ref_depositscheme']['#type'] = 'hidden';
        	
        	break;
        	
        case 'domestic_ratinggroup_node_form':
        	// only for create
            //
            if(!isset($form['nid']['#value'])){
                if(isset($form_state['numberingplan_domestic_nid'])){
                    $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_numberingplan_domestic';
                }
            }
            //unset($form['field_ref_numberingplan_domestic']);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'country_code_node_form':
        	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
        	_unset_menu_items($form,$form_id);
        	break;
        case 'timetable_node_form':
        	_unset_menu_items($form,$form_id);
        	unset($form['field_ref_timetablefactors']);
        	//dsm($form,'form');
        	if(!isset($form['nid']['#value'])){
        		$form['actions']['submit']['#submit'][] = 'timetable_submit_handler';
        	}
        	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
        	break;
        case 'timetablefactors_node_form':
        	unset($form['field_timeslot']['und'][0]['_remove']);
			_unset_menu_items($form,$form_id);
        	// only for create
            //
            if(!isset($form['nid']['#value'])){
                if(isset($form_state['timetable_nid'])){
                    $form['actions']['submit']['#submit'][] = '_timetablefactors_link_to_timetable';
                }
            }
        	break;
        case 'conditioncommoncarrieridd_node_form':
        case 'conditioncommoncarrierdomestic_node_form':
        case 'conditioncommonratinggroup_node_form':
        case 'conditioncommontimetablefactors_node_form':
        case 'actionpricediscountfactors_node_form':
        	unset($form['field_parent_node']);
            unset($form['field_weight']);            
        	_unset_menu_items($form,$form_id);
        	$form['field_ref_product']['#type'] = 'hidden';
        	$form['field_ref_tree_tid']['#type'] = 'hidden';
        	$form['field_ref_tree_nid']['#type'] = 'hidden';
            break;
        case 'actionbonustransfer_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	_unset_menu_items($form,$form_id);
        	$form['field_ref_product']['#type'] = 'hidden';
        	break;        
        case 'conditionwhatcounter_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	$form['field_ref_product']['#type'] = 'hidden';
        	_unset_menu_items($form,$form_id);
    		if(!isset($form['nid']['#value'])){
				$rootNid = $form_state['root_nid'];
            }else{
            	$rootNid = $form['#node']->field_ref_product['und'][0]['nid'];
            }
           
        	unset($form['field_ref_treenodecounter']['und']['#options']);
        	$form['field_ref_counter']['und']['#options']['_none'] = '- None -';
        	
        	$productCountView = views_get_view('list_treenodecounter');
        	$productCountView->set_display('panel_pane_2');
        	$productCountView->set_arguments(array(0 => $rootNid ));
			$productCountView->execute();
        	$counters = $productCountView->result;
        	
        	//dsm($counters,'counters');
            foreach($counters as $counter){
            	$form['field_ref_treenodecounter']['und']['#options'][$counter->nid] = $counter->node_field_data_field_ref_counter_title;
            }        	
        	
        	break;
        case 'actionpriceallowance_node_form':
        case 'actionpriceallowancefactors_node_form':
        	$form['field_allow_start']['#type'] = 'hidden';
        	$form['field_allow_interval']['#type'] = 'hidden';
        	$form['field_allow_interval_unit']['#type'] = 'hidden';
        	
        	
        	unset($form['field_parent_node']);
            unset($form['field_weight']);         
            $form['field_ref_product']['#type'] = 'hidden';
        	$form['field_ref_tree_tid']['#type'] = 'hidden';
        	$form['field_ref_tree_nid']['#type'] = 'hidden';
        	_unset_menu_items($form,$form_id);
        	//dsm($form);
			// only for create
            //
            if(!isset($form['nid']['#value'])){
				$rootNid = $form_state['root_nid'];
            }else{
            	$rootNid = $form['#node']->field_ref_product['und'][0]['nid'];
            }
            
        	unset($form['field_ref_counter']['und']['#options']);
        	$form['field_ref_counter']['und']['#options']['_none'] = '- None -';
        	
        	$productCountView = views_get_view('list_treenodecounter');
        	$productCountView->set_display('panel_pane_2');
        	$productCountView->set_arguments(array(0 => $rootNid ));
			$productCountView->execute();
        	$counters = $productCountView->result;
        	
        	//dsm($counters,'counters');
            foreach($counters as $counter){
            	$form['field_ref_counter']['und']['#options'][$counter->nid] = $counter->node_field_data_field_ref_counter_title;
            }
            //dsm($form);
        	break;        
        case 'actionpricechargefactors_node_form':
        	unset($form['field_parent_node']);
            unset($form['field_weight']);
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_ref_tree_nid']);            
            _unset_menu_items($form,$form_id);        
            $form['chart_button'] = array(
            		'#type' => 'markup',
            		'#markup' => '<input id="chart_show" type="button" value="Refresh Chart"/>',
            		'#weight' => 199
            );
             
            $form['chart_fieldset'] = array(
            		'#type' => 'fieldset',
            		'#title' => 'Chart',
            		'#weight' => 200,
            );
            $form['chart_fieldset']['chart'] = array(
            		'#type' => 'markup',
            		//'#markup' => '<div id="flot_div" class="hidden" style="height:500px;width:90%;" ></div>',
            		'#markup' => '<div id="flot_div" style="height:500px;width:90%;" ></div>',
            		'#weight' => 0
            );
            break;
        case 'actionpricediscount_node_form':
        case 'actionpricechargeonetime_node_form':
        case 'actionpricechargerecurring_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	unset($form['field_ref_product']);
        	unset($form['field_ref_tree_tid']);
        	_unset_menu_items($form,$form_id);
          	break;
        case 'tariffplan_node_form':
			unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = hidden;
            $form['field_ref_tree_tid']['#type'] = hidden;
            unset($form['field_tree_child_voca_name']);
            unset($form['field_ref_numberingplan_domestic']);
            unset($form['field_ref_numberingplan_idd']);
            unset($form['field_ref_timetable_domestic']);
            unset($form['field_ref_timetable_idd']);
            _unset_menu_items($form,$form_id);
            
            if(!isset($form['nid']['#value'])){
            	$productNode = node_load($form_state['build_info']['args'][0]->field_ref_product['und'][0]['nid']);
            	
            	/*
            	$voca_name = 'tpl_';
            	$serviceDomainTerm = taxonomy_term_load($productNode->field_service_type_of_provider['und'][0]['tid']);
            	$voca_name .= strtolower($serviceDomainTerm->name) . '_' . strtolower($serviceTypeTerm->name) . '_tariffplan' ;
            	*/
            	$serviceTypeTerm = taxonomy_term_load($form_state['build_info']['args'][0]->field_ref_tree_tid['und'][0]['value']);
            	$voca_name = _get_vocabulary_name('tariffplan', $productNode, $serviceTypeTerm->name);
            	$form_state['build_info']['args'][0]->field_tree_child_voca_name['und'][0]['value'] = $voca_name;
            	
            	
            	$form_state['ajax_actions'][] = '_node_save_handler_for_add_js_settings_after_node_save'; 
            }

        	break;
        case 'numberspecialfactors_node_form':
        	unset($form['field_parent_node']);
            unset($form['field_weight']);            
            _unset_menu_items($form,$form_id);
        	break;
        case 'unittransfer_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	_unset_menu_items($form,$form_id);
        	unset($form['field_ref_unittransferfactors']);
        	if(!isset($form['nid']['#value'])){
        		$form['actions']['submit']['#submit'][] = '_unittransfer_submit_handler';        		
        	}
        	break;
        case 'unittransferfactors_node_form':
        	unset($form['field_parent_node']);
        	unset($form['field_weight']);
        	_unset_menu_items($form,$form_id);
        	unset($form['field_ref_counter']);
        	 
        	break;
        case 'rate_node_form':
        	unset($form['field_ref_tariffplan']);
        	unset($form['field_ref_tree_tid']);
        	
        	$form['chart_button'] = array(
        			'#type' => 'markup',
        			'#markup' => '<input id="chart_show" type="button" value="Refresh Chart"/>',
        			'#weight' => 199
        	);
        	
        	$form['chart_fieldset'] = array(
        		'#type' => 'fieldset',
        		'#title' => 'Chart',        		       							
	    		'#weight' => 200,
        	);        	
        	$form['chart_fieldset']['chart'] = array(
				'#type' => 'markup',
        		//'#markup' => '<div id="flot_div" class="hidden" style="height:500px;width:90%;" ></div>',
        		'#markup' => '<div id="flot_div" style="height:500px;width:90%;" ></div>',
        		'#weight' => 0
        	);
        	_unset_menu_items($form,$form_id);
        	break;
        case 'carrier_mobile_node_form':
        	_unset_menu_items($form,$form_id);
        	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
        	break;
        case 'treenodevouchercardforproduct_node_form':
        	_unset_menu_items($form,$form_id);
        	$form['field_ref_product']['#type'] = 'hidden';
        	$form['field_ref_tree_tid']['#type'] = 'hidden';        	
        	break;
        /*
        case 'views_form_list_numberingplan_domestic_for_product_default':
            unset($form['actions']['submit']['#submit']);
            unset($form['#validate']);
        	 $form['actions']['submit']['#ajax'] = array(
		        'wrapper' => 'form_content',
		        'callback' => 'edit_pane_callback',
		        'method' => 'replace',
		        'effect' => 'fade',
		        //'parameters' => array('haha' => 'hoho')
		    );
        	break;
        */
	}
	//dsm($form_id);
	_add_ajax_submit_callback($form_id,$form);
	return $form;
}

function ajax_example_add_more_add_one($form, $form_state) {
    return $form['names_fieldset'];
}

function ajax_example_add_more_remove_one() {
    $form_state['num_names']++;
    $form_state['rebuild'] = TRUE;
}

function _alter_field_action_price_factors(&$form,&$form_state) {

	if(isset($form['nid']['#value'])) { //Edit
		$form_state['rule_nid'] = $form_state['build_info']['args'][1]['rule_nid'];
		$form_state['price_type'] = $form_state['build_info']['args'][1]['price_type'];
	}

	$priceType = $form_state['price_type'];
	$rule = node_load($form_state['rule_nid']);

    $array_unset_items = array();
    $array_required = array();

	switch($priceType){
		case 'CHARGE':
            $array_unset_items = array(
                'field_allow_start',
                'field_allow_interval',
                'field_allow_interval_unit',
                'field_threshold',
                'field_threshold_unit',
                'field_ref_counter'
            );
            $array_required = array(
			    'field_range_start',
			    'field_range_end',
			    'field_range_units'
            ); 

            // action price 제약 사항..
            // 확실해 지기 전까지 제약사항 풀어 둠
            /*
            if(!isset($form['nid']['#value'])) { //create
	            if( count($rule->field_ref_action_charge) == 0){ //define constraint
	            	$form['field_range_start']['und'][0]['value']['#default_value'] = 0;
	            	$form['field_range_start']['und'][0]['value']['#disabled'] = TRUE;
	            }else{
	            	$temp = end($rule->field_ref_action_charge['und']);
	            	$last = node_load($temp['nid']);

	            	$form['field_range_start']['und'][0]['value']['#default_value'] = $last->field_range_end['und'][0]['value'];
	            	$form['field_range_start']['und'][0]['value']['#disabled'] = TRUE;
	            	$form['field_range_units']['und']['#value'] = $last->field_range_units['und'][0]['tid'];
	            	$form['field_range_units']['und']['#disabled'] = TRUE;
	            	$form['field_uom_units']['und']['#value'] = $last->field_uom_units['und'][0]['tid'];
	            	$form['field_uom_units']['und']['#disabled'] = TRUE;
	            	$form['field_price_units']['und']['#value'] = $last->field_price_units['und'][0]['tid'];
	            	$form['field_price_units']['und']['#disabled'] = TRUE;
	            }
            }
            */
            break;
		case 'DISCOUNT':
            $array_unset_items = array(
                'field_allow_start',
                'field_allow_interval',
                'field_allow_interval_unit',
                'field_ref_counter',
            );
			break;
		case 'ALLOWANCE':
			$array_unset_items = array(
                'field_range_start',
			    'field_range_end',
			    'field_range_units'
            );
            $array_required = array(
                'field_allow_start',
                'field_allow_interval',
                'field_allow_interval_unit',
            );
			break;
	}

    foreach($array_unset_items as $item) {
        unset($form[$item]);
    }
    //required 제약 사항 일단 주석으로 막아 둠
    /*
    foreach($array_required as $item) {
        $form[$item]['und'][0]['value']['#required'] = TRUE;
        $form[$item]['und']['#required'] = TRUE;
    }
	*/
    unset($form['field_action_price_factor_type']);
}


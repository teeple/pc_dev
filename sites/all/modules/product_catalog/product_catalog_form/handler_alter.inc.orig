<?php
function _unset_menu_items(&$form, $formId) {
    unset($form['menu']);
    unset($form['path']);
    unset($form['author']);
    unset($form['comment_settings']);
    unset($form['options']);
    unset($form['additional_settings']);
    unset($form['actions']['preview']);
    unset($form['revision_information']);

    $unsetDeleteButton = TRUE;

    switch($formId) {
        case 'numberingplan_domestic_node_form' :
        case 'numberingplan_idd_node_form' :
        case 'carrier_mobile_node_form' :
        case 'packetdynamicl4_node_form' :
        case 'packetdynamicchargingrule_node_form' :
        case 'packetpredefinedchargingrule_node_form' :
        case 'roaming_country_node_form' :
        case 'roaming_carrier_node_form' :
        case 'roaming_plan_node_form' :
        case 'counter_node_form':
        case 'depositscheme_node_form' :
        case 'thresholdscheme_node_form' :
        case 'tvchannel_node_form' :
        case 'lifecyclescheme_node_form' :
        case 'timetable_node_form' :
        case 'servicefeaturecode_node_form' :
        case 'servicefeaturecodescheme_node_form':
        case 'unittransfer_node_form':
            $unsetDeleteButton = FALSE;
            break;
    }
    if ($unsetDeleteButton)
        unset($form['actions']['delete']);
}

function _disable_form_elements(&$form, $fields) {

	foreach($fields as $field) {
		$command = '$form[\'' . $field ."']['und']['#disabled'] = TRUE;";
		eval($command);
	}
}

function _unset_form_elements(&$form, $fields) {
	foreach($fields as $field) {
		$command = 'unset($form[\'' . $field ."']);";
		eval($command);
	}
}

function _hidden_form_elements(&$form, $fields) {
	foreach($fields as $field) {
		$command = '$form[\'' . $field ."']['#type'] = 'hidden';";
		eval($command);
	}
}

function _ajax_counter_type_validate($form, &$form_state) {
	$counter = node_load($form_state['values']['field_ref_counter']['und'][0]['nid']);
	$counterTypeTerm = taxonomy_term_load($counter->field_counter_type['und'][0]['tid']);
	
	if($counterTypeTerm->name == 'Rollover') {
		unset($form['field_startdate_option1']);
		
	}
	// $form_state['rebuild'] = TRUE;
	return $form;
}

function _add_ajax_submit_callback($form_id, &$form) {
    $change = FALSE;
    $changeEachRow = FALSE;

    switch($form_id) {
    	case 'devicemodel_node_form':
    	case 'conditionwhatcustomfactors_node_form' :
        case 'conditionwhaturlgroupfactors_node_form' :
        case 'conditionwhencustomfactors_node_form' :
        case 'conditionwhendurationfactors_node_form' :
        case 'conditionwhendayofmonth_node_form' :
        case 'conditionwhendayfactors_node_form' :
        case 'conditionwhentimeslotfactors_node_form' :
        case 'conditionwhencallingzonetime_node_form' :
        case 'conditionwhenholidayfactors_node_form' :
        case 'conditionwhenactivedays_node_form' :
        case 'conditionwhenweekfactors_node_form' :
        case 'conditionwhencustomerbirthday_node_form' :
        case 'conditionwhencompanybirthday_node_form' :
        case 'conditionwhenstatechangedate_node_form' :
        case 'conditionwhenbillingdate_node_form' :
        case 'conditionwherecountryfactors_node_form' :
        case 'conditionwherecustomfactors_node_form' :
        case 'conditionwhereissamezone_node_form' :
        case 'conditionwherenetworkfactors_node_form' :
        case 'conditionwherecallerzone_node_form' :
        case 'conditionwherecalleezone_node_form' :
        case 'conditionwhereclientip_node_form' :
        case 'conditionwheremacaddress_node_form' :
        case 'conditionwheredevicetype_node_form' :
        case 'conditionwhererattype_node_form' :
        case 'conditionwheresgsn_node_form' :
        case 'conditionwhocustomfactors_node_form' :
        case 'conditionwhomemberfactors_node_form' :
        case 'conditionwhonumberfactors_node_form' :
        case 'conditionwhosubscribermdn_node_form' :
        case 'conditionwhosubscriberstatus_node_form' :
        case 'conditionwhocalledcarrier_node_form' :
        case 'conditionwhoprefixfactors_node_form' :
        case 'conditionwhocustomerlevel_node_form' :
        case 'conditioncommoncounterfactors_node_form' :
        case 'conditionwhatqos_node_form' :
        case 'conditioncommoncarrieridd_node_form' :
        case 'conditionwhatcardtype_node_form' :
        case 'conditionwhatmainproduct_node_form' :
        case 'conditioncommoncarrierdomestic_node_form' :
        case 'conditioncommonratinggroup_node_form' :
        case 'conditioncommontimetablefactors_node_form' :
        case 'actionpricediscountfactors_node_form' :
        case 'actionpriceallowancefactors_node_form' :
        case 'actionpricechargefactors_node_form' :
        case 'actionpricechargeonetime_node_form' :
        case 'actionpricechargerecurring_node_form' :
        case 'actionpricechargerecurringdefaul_node_form':
        case 'actionpricediscount_node_form' :
        case 'actionpriceallowance_node_form' :
        case 'actionblockfactors_node_form' :
        case 'tariffplan_node_form' :
        case 'treenodeproductforvoucher_node_form' :
        case 'treenodecounter_node_form' :
        case 'prdattributeprefixrangeallowed_node_form' :
        case 'prdattributeprefixrangenotallowe_node_form' :
        case 'prdnonusagerecurringchargescheme_node_form' :
        case 'prdnonusagerecurringbonusscheme_node_form' :
        case 'prdnonusagerollover_node_form' :
        case 'prdnonusagerechargeblock_node_form' :
        case 'unittransferfactor_node_form' : 
        case 'conditionwhatusagetypefactors_node_form' :
        case 'conditionwhatnonusagetypefactors_node_form' :
        case 'prdattributefeaturecode_node_form' :
        case 'prdattributebenefit_node_form' :
        case 'loyaltypoint_node_form' :
        case 'actionbonustransfer_node_form' :
        case 'conditionwhatcalltype_node_form' :
        case 'conditionwhatservicedomain_node_form' :
        case 'conditionwhatcounter_node_form' :
        case 'conditionwhatratinggroup_node_form' :
        case 'conditionwhatcounterfortracking_node_form' :
        case 'conditionwhensubscriptionday_node_form' :
        case 'conditionwhatincomingcall_node_form' :
        case 'conditionwhereserviceid_node_form' :
        // case 'conditionwhatcardtype_node_form':
        case 'conditionwhenactivationday_node_form' :
        case 'numberspecialrate_node_form' :
        case 'actionpriceallowanceonetime_node_form' :
        case 'actionpriceallowancerecurring_node_form' :
        case 'actionpricecugdiscountfactors_node_form':
        case 'treenodeotheronetimecharge_node_form' :
        case 'treenodeotheronetimechargediscou_node_form' :
        case 'treenodepacketdynamic_node_form' :
        case 'treenodepacketdefaultqos_node_form' :        
        case 'basicrate_data_node_form' :
        case 'prdattributerequireddevice_node_form' :
        case 'prdattributenumbersaving_node_form' :
        case 'prdcounterlist_node_form':
        case 'conditionwhatcontentprice_node_form':
        case 'conditionwhoroamingcarrier_node_form':
        case 'conditionwhereroamingcountry_node_form':
        case 'conditionwhereroamingzone_node_form':
        case 'conditionwhatroamingtype_node_form':
        case 'conditionwhenvaliddate_node_form':
        case 'backupandmigrateconfiguration_node_form':
        case 'ocs_global_config_node_form':
            $change = TRUE;
            break;

        case 'views_form_list_treenodecounterforvoucher_panel_pane_1' :
            $changeEachRow = TRUE;
            break;
        case 'vouchercardtype_node_form' :
        case 'unittransfer_node_form' :
        case 'number_special_node_form' :
            if (isset($form['nid']['#value'])) {// edit
                $change = TRUE;
            }
            break;
        case 'simpleproductoffering_node_form':
        	unset($form['field_is_cloned']);
            if (isset($form['nid']['#value'])) {// edit
                $change = TRUE;
            }
            //$paths = explode('/', current_path());
            //if($paths[0] == 'relation') $change = FALSE;
            break;
    }
    
    if ($change) {
        unset($form['actions']['submit']['#submit']);
        unset($form['#validate']);
        unset($form['#action']);
        $form['actions']['submit']['#id'] = 'submit-in-ajax-callback';
        $form['#prefix'] = '<div id="form_content">';
        $form['#suffix'] = '</div>';

        $form['actions']['submit']['#ajax'] = array('wrapper' => 'form_content', 'callback' => 'edit_pane_callback', 'method' => 'replace', 'effect' => 'fade',
        );
    }
}

function edit_pane_callback($form, &$form_state) {

    $newNode = node_load($form['nid']['#value']);
    $form_state['values']['changed'] = $newNode -> changed;

    node_form_validate($form, $form_state);

		if(!empty($form_state['values']['field_negative'])) {
			if($form_state['values']['field_negative']['und'][0]['value'] == 1) {
				$form_state['values']['field_rating_operation']['und'][0]['tid'] = 84; // Rating Operation = notin
			} else {
				$form_state['values']['field_rating_operation']['und'][0]['tid'] = 81; // Rating Operation = is equal to
			}
		}
		
    if (!form_get_errors()) {
        node_form_submit($form, $form_state);
        //error_log('node_form_submit');
        if(isset($form_state['ajax_actions'])){
            foreach ($form_state['ajax_actions'] as $functionName) {
                $evalString = $functionName . '($form, $form_state);';
                eval($evalString);
            }
        }
    }
    $form_state['rebuild'] = TRUE;
    return $form;
}

function product_catalog_form_form_alter(&$form, &$form_state, $form_id) {

	
	load_required_js_css_before_ajax_load();

    if ((isset($form['#attributes']) && isset($form['#attributes']['class'])) && gettype($form['#attributes']['class']) == 'array') {
        $form['#attributes']['class'][] = 'myform';
    }
    
    switch($form_id) {
    		case 'views_form_ocs_svc_perm_panel_pane_1':
				dpm( $form, 'form ');

				// TODO: state service permission
    			$lifecycleScheme = node_load($form_state['build_info']['args'][0]->args[0]);
    			$svcDomainTid = $lifecycleScheme->field_service_domain['und'][0]['tid'];
    			
				$view = views_get_view('list_calltype');
				$view->set_display('panel_pane_2');
				$view->set_arguments(array('0'=>$svcDomainTid));
				$view->execute();
				
				$options = array();
				$group = array();
				foreach($view->result as $record) {
					$subgroup1 = $record->field_field_sub_group1[0]['raw']['value'];
					$subgroup2 = $record->field_field_sub_group2[0]['raw']['value'];
					$options[$record->tid] = t( '<span class="@class">@svc</span>', 
							array( '@class' => t( 'ocs_svc_perm @1 @2', array( '@1' => $subgroup1, '@2' => $subgroup2)),
								'@svc' => $record->taxonomy_term_data_name));
					$group[$subgroup1][$subgroup2] = 1;
				}

				/*
				$legend = '';
				foreach( $group as $key => $values) {
					foreach( array_keys( $values) as $v) {
						$legend .= t('<div>@k,@v</div>', array( '@k' => $key, '@v' => $v));
					}
				}
				*/

				foreach( array_keys( $form['field_service_permission']) as $key) {
					/*
					foreach( array_keys( $options) as $subgroup) {
						$form['field_service_permission'][$key]['field_service_permission'][$subgroup] = 
							$form['field_service_permission'][$key]['field_service_permission']['und'];
						$form['field_service_permission'][$key]['field_service_permission'][$subgroup]['#options'] = $options[$subgroup];
					}
					*/
					//unset( $form['field_service_permission'][$key]['field_service_permission']['und']);
					$form['field_service_permission'][$key]['field_service_permission']['und']['#options'] = $options;
				//	$form['field_service_permission'][$key]['field_service_permission']['#suffix'] .= $legend;
				}

				// filter feature codes
				$view = views_get_view('list_service_feature_code');
				$view->set_display('list_feature_code');
				$view->set_arguments(array('0'=>$svcDomainTid, '1'=>'Lifecycle'));
				$view->execute();
				
				$options = array();
				foreach($view->result as $record) {
					$subgroup1 = $record->field_field_sub_group1[0]['raw']['value'];
					$subgroup2 = $record->field_field_sub_group2[0]['raw']['value'];
					$options[$record->tid] = t( '<span class="@class">@svc</span>', 
							array( '@class' => t( 'ocs_svc_perm @1 @2', array( '@1' => $subgroup1, '@2' => $subgroup2)),
								'@svc' => $record->taxonomy_term_data_name));
				}

				foreach( array_keys( $form['field_feature_codes']) as $key) {
					$form['field_feature_codes'][$key]['field_feature_codes']['und']['#options'] = $options;
				}

    			break;
            case 'backup_migrate_ui_manual_backup_load_profile_form':
                $form['profile']['#type'] = 'hidden';
                break;
            case 'backup_migrate_ui_manual_backup_form':
                $form['source']['#type'] = 'hidden';
                $form['file']['compression']['#type'] = 'hidden';
                $form['file']['encryption']['#type'] = 'hidden';
                $form['file']['token_help']['#type'] = 'hidden';
                $form['destinations']['#type'] = 'hidden';
                $form['file']['destination']['#type'] = 'hidden';
                $form['destination']['destination_id']['#type'] = 'hidden';
                $form['destination']['#type'] = 'hidden';
                $form['save_settings']['#type'] = 'hidden';
                $form['save_options']['#type'] = 'hidden';
                $form['advanced']['notify_success_enable']['#type'] = 'hidden';
                $form['advanced']['notify_success_email']['#type'] = 'hidden';
                $form['advanced']['notify_failure_enable']['#type'] = 'hidden';
                $form['advanced']['notify_failure_email']['#type'] = 'hidden';
                $form['advanced']['#collapsed'] = FALSE;
                break;
    		case 'devicemodel_node_form':
    				_unset_menu_items($form, $form_id);
    				$form['title']['und']['#disabled'] = TRUE;
    				$form['field_model_code']['und']['#disabled'] = TRUE;
    				$form['field_model_class']['und']['#disabled'] = TRUE;
    				$form['field_model_class_code']['und']['#disabled'] = TRUE;
    				break;
    				
    		case 'article_node_form';
    		    _unset_menu_items($form, $form_id);
    		    
    		    unset($form['field_image']);
    		    unset($form['body']);
    		    unset($form['body']['und'][0]['#columns'][2]);
    		    break;
        case 'views_exposed_form' :
            switch($form['#id']) {
                case 'views-exposed-form-list-vouchercardtype-panel-pane-1' :
                    $form['field_ref_voucher_type_tid']['#options']['All'] = '- type -';
                    break;
                case 'views-exposed-form-list-counter-panel-pane-1' :
                    $form['field_billing_type_counter_tid']['#options']['All'] = '- billtype -';
                    $form['field_service_domain_tid']['#options']['All'] = '- domain -';
                    break;
            }
            // $form['field_ref_voucher_type_tid']

            break;
        case 'views_form_list_counter_for_vouchercardtype_panel_pane_2' :
            unset($form['actions']['submit']);
            break;

        case 'views_form_list_basicrate_panel_pane_2' :
            unset($form['actions']['submit']);

            //get related rates..
            $tariffplanNid = $form_state['build_info']['args'][0] -> args[1];
            $refTreeTid = $form_state['build_info']['args'][0] -> args[2];

            $rateView = views_get_view('list_rates');
            $rateView -> set_display('panel_pane_2');
            $rateView -> set_arguments(array('0' => $tariffplanNid, '1' => $refTreeTid));
            $rateView -> execute();

            $rateOptions = array();
            $rateOptions['_none'] = '- None -';
            foreach ($rateView->result as $rateItem) {
                $rateOptions[$rateItem -> nid] = $rateItem -> node_title;
            }

            $rowCount = count($form['field_ref_rate']);
            for ($i = 0; $i < $rowCount; $i++) {
                $form['field_ref_rate'][$i]['field_ref_rate']['und']['#options'] = $rateOptions;
            }
            break;
        case 'views_form_list_basicrate_panel_pane_3' :
        case 'views_form_list_basicrate_panel_pane_5' :
            unset($form['actions']['submit']);

            //get related rates..
            $tariffplanNid = $form_state['build_info']['args'][0] -> args[0];
            $refTreeTid = $form_state['build_info']['args'][0] -> args[1];

            $rateView = views_get_view('list_rates');
            $rateView -> set_display('panel_pane_2');
            $rateView -> set_arguments(array('0' => $tariffplanNid, '1' => $refTreeTid));
            $rateView -> execute();

            $rateOptions = array();
            $rateOptions['_none'] = '- None -';
            foreach ($rateView->result as $rateItem) {
                $rateOptions[$rateItem -> nid] = $rateItem -> node_title;
            }

            $rowCount = count($form['field_ref_rate']);
            for ($i = 0; $i < $rowCount; $i++) {
                $form['field_ref_rate'][$i]['field_ref_rate']['und']['#options'] = $rateOptions;
            }
            break;
        case 'views_form_list_tariffplan_idd_carrier_panel_pane_1' :
            unset($form['actions']['submit']);
            break;
        case 'views_form_list_treenodecounterforvoucher_panel_pane_1' :
            unset($form['actions']);
            break;
        case 'conditionwhenactivationday_node_form' :
        case 'conditionwhensubscriptionday_node_form' :
        case 'conditionwhenactivedays_node_form' :
        case 'conditionwhencustomerbirthday_node_form' :
        case 'conditionwhencompanybirthday_node_form' :
        case 'conditionwhenstatechangedate_node_form' :
        case 'conditionwhenbillingdate_node_form' :
        case 'conditionwhoroamingcarrier_node_form':
        case 'conditionwhereroamingcountry_node_form':
        case 'conditionwhereroamingzone_node_form':
        case 'conditionwhatroamingtype_node_form':
        case 'conditionwhererattype_node_form' :
        case 'conditionwheresgsn_node_form' :
        case 'conditionwhenvaliddate_node_form':
            _unset_menu_items($form, $form_id);
            $form['field_weight']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            break;
            
        case 'conditionwhatservicedomain_node_form':
		        $form['field_weight']['#type'] = 'hidden';
		        $form['field_parent_node']['#type'] = 'hidden';
		        _unset_menu_items($form, $form_id);
		        break;

	   case 'conditionwhatmainproduct_node_form':
	        $form['field_weight']['#type'] = 'hidden';
	        $form['field_parent_node']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            
            $parentNode = node_load($form['#node']->field_parent_node['und'][0]['nid']);
	        $productNode = find_parent_product($parentNode);
            $args = array(
                '0' => $productNode->field_service_type_of_provider['und'][0]['tid'],
                '1' => $productNode->field_service_operator['und'][0]['tid'],
                '2' => $productNode->field_billing_type['und'][0]['tid'],
                '3' => $productNode->field_customer_type['und'][0]['tid']
            );
            
			$tempView = views_get_view('list_product_for_cond_main_product');
			$tempView->set_display('panel_pane_1');
			$tempView->set_arguments($args);
			$tempView->execute();
             
            $options = array();
    	    foreach($tempView->result as $item){
    	        $options[$item->nid] = $item->node_title;
    	    }
	    
	       $form['field_main_product']['und']['#options'] = $options;
	    break;
		        
        case 'conditionwhatcardtype_node_form' :
            $form['field_weight']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            /*
             unset($form['actions']);

             $form['custom_markup'] = array('#type'=> 'markup',
             '#markup' => "<input type='hidden' id='cardtype_parent_nid' value='".$form['#node']->field_parent_node['und'][0]['nid']."'></input>
             <input type='hidden' id='cardtype_nid' value='".$form['#node']->nid."'></input>
             <input type='hidden' id='cardtype_weight' value='".$form['#node']->field_weight['und'][0]['value']."'></input>",
             '#weight' => 200,
             );
             $form['multiselect_custom'] = array('#type'=> 'markup',
             '#markup' => "<input type='button' id='multiselect_custom_button_cardtype' value='Save'></input>",
             '#weight' => 100,
             );
             */
            break;
            
        case 'holidaylist_specific_node_form' :
        case 'holidaylist_repeatable_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_holidaylist']['#type'] = 'hidden';
            // in case create
            if (!isset($form['nid']['#value'])) {
                $form['field_ref_holidaylist']['und'][0]['nid']['#default_value'] = $form_state['holidaylist_nid'];
            }
            break;

        case 'depositscheme_node_form' :
            unset($form['field_ref_depositschemefactors']);
            unset($form['field_ref_depositschemeadjustmen']);
            unset($form['rdf_mapping']);
            unset($form['body']);

            _unset_menu_items($form, $form_id);
            break;

        case 'thresholdscheme_node_form' :
        case 'backupandmigrateconfiguration_node_form':
            _unset_menu_items($form, $form_id);
            break;

        case 'thresholdschemefactors_node_form' :
            $form['field_ref_thresholdscheme']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            break;

        case 'vouchercardtype_node_form' :

            //$form['field_tree_child_voca_name']['und']['#default_value'][0] = 'tbl_vouchercardtype';
            $form['field_tree_child_voca_name']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);

            unset($form['field_active_period']);
            unset($form['field_grace_period']);

			// Create
			if (!isset($form['nid']['#value'])) {
				
				$viewResult = views_get_view_result('query_vouchercardtype_max_id', 'panel_pane_1');
				if(sizeof($viewResult) > 0) {
					$maxVoucherId = current($viewResult)->field_field_voucher_id[0]['raw']['value'];
				} else {
					$maxVoucherId = 10000;
				}
				
				$form['field_voucher_id']['und'][0]['value']['#default_value'] = $maxVoucherId + 1;
				$form['field_voucher_id']['und']['#disabled'] = TRUE;
				
				$form['actions']['submit']['#submit'][] = '_vouchercardtype_submit_handler';
              	$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
              
            // Edit  
            } else {
            	$form['field_ref_voucher_type']['und']['#disabled'] = TRUE;
            	$form['field_voucher_id']['und']['#disabled'] = TRUE;
            	$form['field_service_operator']['und']['#disabled'] = TRUE;
            }
            
            break;

        case 'treenodeproductforvoucher_node_form' :
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_weight']);
            unset($form['field_ref_vouchercardtype']);

            _unset_menu_items($form, $form_id);
            break;

        case 'loyaltypoint_node_form' :

            // loyaltypoint���ъ���� counter��point��counter留�蹂������濡����.
            // counter_group��Point��寃��留�由ъ������
            //
            $viewResult = views_get_view_result('list_counter_for_vouchercardtype', 'panel_pane_3');

            $counters = array();
            $counters['_none'] = '- None -';
            foreach ($viewResult as $record) {
                $counters[$record -> nid] = $record -> node_title;
            }
            $form['field_ref_counter']['und']['#options'] = $counters;

            unset($form['field_ref_vouchercardtype']);
            _unset_menu_items($form, $form_id);
            break;

        case 'loyaltypointfactors_node_form' :
            unset($form['field_ref_loyaltypoint']);
            _unset_menu_items($form, $form_id);
            break;

        case 'prdattributeprefixrangeallowed_node_form' :
        case 'prdattributeprefixrangenotallowe_node_form' :
            $form['field_parent_node']['#type'] = 'hidden';
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            break;
        case 'prdattributefeaturecode_node_form' :
            $form['field_parent_node']['#type'] = 'hidden';
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            
            break;

        case 'prdattributebenefit_node_form' :
            $product = node_load($form_state['product_nid']);
            $prdTypeTerm = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);

            $form['field_parent_node']['#type'] = 'hidden';
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);

            break;

        case 'locationfactor_node_form' :
        case 'homezonefactor_node_form' :
            _unset_menu_items($form, $form_id);
            break;

        case 'prdnonusagerechargeblock_node_form' :
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            $basicCounterList = array();

            $productNid = $form_state['product_nid'];
            
            $basicCounterList = array();
            $basicCounterList = _get_default_basic_counters($productNid);
            
            $existingCounterList = _get_existing_counter_list($productNid);

            foreach ($basicCounterList as $key => $value) {
                $mergedCounterList[$key] = $value;
            }
            foreach ($existingCounterList as $key => $value) {
                $mergedCounterList[$key] = $value;
            }
            $form['field_counter_for_max_count']['und']['#options'] = $mergedCounterList;
            $form['field_counter_for_max_amount']['und']['#options'] = $mergedCounterList;

            _unset_menu_items($form, $form_id);
            break;

        case 'prdnonusagerecurringchargescheme_node_form' :
        		$productNode = node_load($form['#node'] -> field_ref_product['und'][0]['nid']);
            $productTypeTerm = taxonomy_term_load($productNode -> field_product_type['und'][0]['tid']);
            $productBillingTypeTerm = taxonomy_term_load($productNode->field_billing_type['und'][0]['tid']);
            
            if ($productTypeTerm -> name !== 'Main') {
                $form['#fieldgroups']['group_recurring_day'] -> format_type = 'hidden';
                $form['field_charging_day_type']['#type'] = 'hidden';
                $form['field_rcrr_charging_day_monthly']['#type'] = 'hidden';
                $form['field_rcrr_charging_day_week']['#type'] = 'hidden';
            }
            
            if($productBillingTypeTerm->name == 'Prepaid') {
            		unset($form['field_charging_cycle_type']['und']['#options'][3]);
            		unset($form['field_charging_cycle_type']['und']['#options'][4]);
            }
            
            unset($form['field_ref_product']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            
            break;
        case 'prdnonusagerecurringbonusscheme_node_form' :
            unset($form['field_ref_product']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            break;

        case 'prdnonusagerollover_node_form' :
            unset($form['actions']);
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            _unset_menu_items($form, $form_id);

            // in case of update
            $form['custom'] = array('#type' => 'markup', '#markup' => "<input type='hidden' id='rollover_nid' value='" . $form['nid']['#value'] . "'></input>
							<input type='hidden' id='rollover_weight' value='" . $form['#node'] -> field_weight['und'][0]['value'] . "'></input>
							<input type='hidden' id='rollover_ref_product' value='" . $form['#node'] -> field_ref_product['und'][0]['nid'] . "'></input>
							<input type='hidden' id='rollover_ref_tree_nid' value='" . $form['#node'] -> field_ref_tree_nid['und'][0]['nid'] . "'></input>
							<input type='hidden' id='rollover_ref_tree_tid' value='" . $form['#node'] -> field_ref_tree_tid['und'][0]['value'] . "'></input>", '#weight' => 200, );
            $form['multiselect_custom'] = array('#type' => 'markup', '#markup' => "<input type='button' id='multiselect_custom_button_rollover' value='Save'></input>", '#weight' => 100, );

            $productNid = $form['#node'] -> field_ref_product['und'][0]['nid'];

            $basicCounterList = array();
            $basicCounterList = _get_default_basic_counters($productNid);
            
            $existingCounterList = _get_existing_counter_list($productNid);

            foreach ($basicCounterList as $key => $value) {
                $mergedCounterList[$key] = $value;
            }
            foreach ($existingCounterList as $key => $value) {
                $mergedCounterList[$key] = $value;
            }

            $options = $mergedCounterList;
            $element = $form['field_counter_list']['und'];

            $items = $form_state['build_info']['args'][0] -> field_counter_list['und'];

            $widget = _multiselect_build_widget_code($options, $items, $element, NULL);
            $form['field_counter_list']['und']['#prefix'] = $widget['prefix_pre'] . $widget['prefix_options'] . $widget['prefix_post'];
            $form['field_counter_list']['und']['#options'] = $mergedCounterList;

            break;

        case 'prdcounterlist_node_form' :
            //unset($form['actions']);
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            _unset_menu_items($form, $form_id);
            
            $form['field_parent_node']['#type'] = 'hidden';
            
            $counterList = _get_available_counter_list($form_state['product_nid']);
            $form['field_counter_list']['und']['#options'] = $counterList;
            break;

        case 'counter_node_form' :
            $counterTypeTerm = current(taxonomy_get_term_by_name($form_state['counter_type'], 'countertype'));
            $form['field_weight_for_unittransfer']['#type'] = 'hidden';
            
            // Create
            if(!isset($form['nid']['#value'])) {
            
            	if($counterTypeTerm->name == 'Basic' || $counterTypeTerm->name == 'Optional') {
	            	$viewResult = views_get_view_result('query_counter_max_id', 'panel_pane_1');
	            	$maxCounterId = $viewResult[0] -> field_field_counter_id[0]['raw']['value'] + 1;
	            	
            	} else if($counterTypeTerm->name == 'Rollover') {
	            	$viewResult = views_get_view_result('query_counter_max_id', 'panel_pane_2');
	            	if (!empty($viewResult)) {
	            	    $maxCounterId = $viewResult[0] -> field_field_counter_id[0]['raw']['value'] + 100;
	            	} else {
	            	    $maxCounterId = 1000000;
	            	}
            	}
            	
          		$form['field_counter_type']['und']['#default_value'] = $counterTypeTerm -> tid;
          		$form['field_counter_type']['und']['#disabled'] = TRUE;
          	  
          	  $form['field_counter_id']['und'][0]['value']['#default_value'] = $maxCounterId;
          	  $form['field_counter_id']['und']['#disabled'] = TRUE;
          	  
          	  //billtype에 따라 counter group 제한하도록 ajax handler 추가 
          	  $form['field_counter_group']['und']['#prefix'] = '<div id="counter_group">';
          	  $form['field_counter_group']['und']['#postfix'] = '</div>';
          	  
          	  $form['field_billing_type_counter']['und']['#ajax'] = array(
          	      'callback' => 'counter_bill_type_change_callback',
          	      'wrapper' => 'counter_group'  
          	  );
            	
            } else {
	            $disabledFields = array(// 'field_scale', 
	            												'field_counter_type',
	            												'field_service_domain',
	            												'field_billing_type_counter',
	            												'field_counter_unit_type',
	            												'field_counter_group'
	            									);
            	foreach ($disabledFields as $field) {
            		$command = '$form[\'' . $field ."']['und']['#disabled'] = TRUE;";
            		eval($command);
            	}
            }
            
            unset($form['field_weight']);
            unset($form['field_parent_node']);

            _unset_menu_items($form, 'counter_node_form');
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            break;

        case 'treenodecounter_node_form' :
            $refTreeTerm = taxonomy_term_load($form['field_ref_tree_tid']['und'][0]['value']['#default_value']);

            if ($refTreeTerm -> name == 'Charging') {
                $form['field_counter']['#type'] = 'hidden';
                $form['field_startdate_option1']['#type'] = 'hidden';
                $form['field_enddate_option1']['#type'] = 'hidden';
                $form['field_enddate_option2']['#type'] = 'hidden';
                $form['field_enddate_option3']['#type'] = 'hidden';
                $form['field_enddate_option4']['#type'] = 'hidden';
                unset($form['#groups']);
                unset($form['#fieldgroups']);
                unset($form['#group_children']);

            } else if ($refTreeTerm -> name == 'Accumulating') {
                $form['field_threshold_on_counter']['#type'] = 'hidden';
                $productNid = $form['#node'] -> field_ref_product['und'][0]['nid'];

                $tempView = views_get_view('list_treenodecounter');
                $tempView->set_display('panel_pane_5');
                $tempView->set_arguments(array('0' => $productNid, '1' => 'Main'));
                $tempView->execute();
                
                $options = array();
                foreach($tempView->result as $treeNodeCounterItem){
                    $options[$treeNodeCounterItem->node_field_data_field_ref_counter_nid]
                        = $treeNodeCounterItem->node_field_data_field_ref_counter_title;
                }
                
                if(isset($options[$form['#node']->field_ref_counter['und'][0]['nid']])){
                    unset($options[$form['#node']->field_ref_counter['und'][0]['nid']]);
                }
                
                $form['field_counter']['und']['#options'] = $options;

            }

            $form['title']['#type'] = 'hidden';
            $form['field_ref_counter']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_main_or_accumulated']['#type'] = 'hidden';

            _unset_menu_items($form, $form_id);

            break;
        case 'conditionwhatcalltype_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call']['und']['#options'] = $options;
            break;
        case 'prddowngradepenalty_node_form':
            $form['field_ref_product']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            $options = _get_product_exclusive_list($form['#node']->field_ref_product['und'][0]['nid']);
            
            //remove already set as exclusive product
            $productNode = node_load($form['#node']->field_ref_product['und'][0]['nid']);
            if(isset($productNode->field_exclusiveness['und'])){
                foreach($productNode->field_exclusiveness['und'] as $item){
                    unset($options['list'][$item['nid']]);
                }
            }
            
            $form['field_ref_target_product']['und']['#options'] = $options['list'];
            break;
        case 'simpleproductoffering_node_form' :
        		
        		$disabledItems = array();
						$hiddenItems = array();
						/*
        		$hiddenItems = array('field_next_join_product', 'field_next_join_confirm');
						*/
						$unsetItems = array('field_r_prodofferingrel', 
        												'field_r_productspecification',
        												'field_r_prodspeccharvalueuse',
        												'field_r_productofferingprice',
        												'field_version',
        												'field_is_bundle',
        												'field_roaming_allowed',
																'field_offering_status',
																'field_parent_node_for_rp',
																'field_weight_for_ratingpriority',
																'field_weight',
															'field_ref_product',
																'field_parent_node',
																'field_tpl_voca_machine_name',
																'field_parent_node_for_hr',
																'field_weight_for_hierarchy');
					  // in case Create
            if (!isset($form['nid']['#value'])) {
            
                $paths = explode('/', current_path());
                $productTypeTerm = current(taxonomy_get_term_by_name($paths[2], 'prdtype'));
                $form['field_product_type']['und']['#default_value'][0] =  $productTypeTerm -> tid;
                $serviceTypeTerm = taxonomy_get_term_by_name($paths[1], 'svcdomain');
                $form['field_service_type_of_provider']['und']['#default_value'][0] =  current($serviceTypeTerm) -> tid;
                
                $hiddenItems = array_merge($hiddenItems, array('field_product_type', 'field_service_type_of_provider'));
                
                $productTypeName = $form_state['product_type_name'];
                if($productTypeName != 'CUG') {
                	$hiddenItems[] = 'field_cug_member_counter';
                	$unsetItems[] = 'field_cug_group_type';
                	$unsetItems[] = 'field_cug_customer_type';
                	unset($form['#fieldgroups']['group_cug']);
	              	unset($form['#groups']['group_cug']);
                }
                
                if($productTypeTerm->name != 'Main') {
                
                	if($productTypeTerm->name == 'CUG') {
                		$form['field_billing_type']['und']['#default_value'] = 680;
                		$disabledItems[] = 'field_billing_type';
                	} else {
	                	// Hybrid Delete
	                	unset($form['field_billing_type']['und']['#options'][680]);
	                }
                }
                
                
            // in case Edit
            } else {
            		$hiddenItems = array_merge($hiddenItems, array('field_product_type',
            													'field_service_type_of_provider'));
            													
            		$disabledItems = array_merge($disabledItems, array( //'field_billing_type',
            														'field_price_units',
            														'field_product_id'));
             		
             		$productTypeTid = $form['field_product_type']['und']['#default_value'][0];
             		$productTypeName = $form['field_product_type']['und']['#options'][$productTypeTid];
             		
             		if($productTypeName != 'CUG' ) {
             			$hiddenItems[] = 'field_cug_member_counter';
             			$unsetItems[] = 'field_cug_group_type';
             			$unsetItems[] = 'field_cug_customer_type';
	              	unset($form['#groups']['group_cug']);
									unset($form['#fieldgroups']['group_cug']);
             		} else {
             			$disabledItems[] = 'field_cug_customer_type';
             			$disabledItems[] = 'field_cug_group_type';
             		}
             		
					$svcDomainTid = $form['field_service_type_of_provider']['und']['#default_value'][0];

					$billingTypeTid = $form['field_billing_type']['und']['#default_value'];
					$svcOperatorTid = $form['field_service_operator']['und']['#default_value'];
					$customerTypeTid = $form['field_customer_type']['und']['#default_value'];

					if($productTypeName != 'Main') {

						$args = array('0' => $svcDomainTid, 
									'1' => $productTypeTid,
									'2' => $billingTypeTid,
									'3' => $svcOperatorTid,
									'4' => $customerTypeTid);

						$view = views_get_view('list_product_for_nextjoin');
						$view->set_display('panel_pane_2');
						$view->set_arguments($args);
						$view->execute();

						$viewResult = $view->result;

						$options = array();
						foreach($viewResult as $item) {
							$options[$item->nid] = view_get_field_value_by_label($view, 'PHP', $item);
						}
							$form['field_next_join_product']['und']['#options'] = $options;
						}
          }

            $productTypeTid = $form['field_product_type']['und']['#default_value'][0];

            if($form['field_product_type']['und']['#options'][$productTypeTid] == 'Main') {
            		$unsetItems[] = 'field_product_sub_type';
            }
            
            _unset_menu_items($form, $form_id);

            $firstPathName = current(explode('/', current_path()));
            if ($firstPathName == 'relation') {
                $form['title']['#type'] = 'hidden';
                
                $unsetItems = array_merge($unsetItems,
												array('field_description',
													'field_offering_status',
													'field_version',
													'field_billing_type',
													'field_validfor_product',
													'field_service_operator',
													'field_billing_cycle',
													'field_product_id',
													'field_customer_type',
													'field_customer_group_type',
													'field_is_bundle',
													'field_deferred_subscription_flag',
													'field_price_units',
													'field_treatment_price_amount',
													'field_treatment_day',
													'field_contract_period',
													'field_roaming_allowed',
													'field_cug_member_counter',
													'field_short_code',
													'field_next_join_product',
													'field_expire_date_type',
													'field_expire_date',
													'field_field_deferred_subscriptio',
													'field_hlr_template_id'));
                
                $options = _get_product_exclusive_list($form['nid']['#value']);
                $form['field_exclusiveness']['und']['#options'] = $options['list'];
				
                $view = views_get_view('list_product_in_exclusive');
								$view->set_display('panel_pane_3');
								$view->set_arguments($options['args']);
								$view->execute();
								
								$viewResult = $view->result;
								
								// $options = array('- None -');
								$options = array();
								foreach($viewResult as $item) {
										$options[$item->nid] = view_get_field_value_by_label($view, 'PHP', $item);
								}
				
								$form['field_exclusiveness_others']['und']['#options'] = $options;
                
            } else {
            		$unsetItems = array_merge($unsetItems, array('field_exclusiveness',
            												'field_exclusiveness_others'));
            }
            
            switch($productTypeName){
                case 'Main':
                		unset($form['#groups']['group_next_join']);
                		unset($form['#fieldgroups']['group_next_join']);
                    break;
                default :
										$form['field_cug_group_type']['#type'] = 'container';
                		break;
            }
            
            _unset_form_elements($form, $unsetItems);
            _hidden_form_elements($form, $hiddenItems);
            _disable_form_elements($form, $disabledItems);
            
            break;
            
        case 'balance_node_form' :
        case 'context_admin_node_form_wrapper' :
        case 'prodoffernonusagesubitem_node_form' :

        // sub factors
        case 'conditionwherecallerzone_node_form' :
        case 'conditionwherecalleezone_node_form' :
        case 'conditionwhereclientip_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_weight']);
            unset($form['field_parent_node']);
            $form['field_rating_operation']['#type'] = 'hidden';
            break;
        case 'conditionwhatusagetypefactors_node_form' :
        case 'conditionwhatnonusagetypefactors_node_form' :
        case 'conditionwhatcustomfactors_node_form' :
        case 'conditionwhatincomingcall_node_form' :
        case 'conditionwhaturlgroupfactors_node_form' :
        case 'conditionwhencustomfactors_node_form' :
        case 'conditionwhendayofmonth_node_form' :
        case 'conditionwhendayfactors_node_form' :
        case 'conditionwhentimeslotfactors_node_form' :
        case 'conditionwhencallingzonetime_node_form':
        case 'conditionwhenholidayfactors_node_form' :

        case 'conditionwhenweekfactors_node_form' :
        case 'conditionwherecountryfactors_node_form' :
        case 'conditionwherecustomfactors_node_form' :
        case 'conditionwherenetworkfactors_node_form' :
        case 'conditionwhereissamezone_node_form' :
        case 'conditionwheremacaddress_node_form' :
        case 'conditionwheredevicetype_node_form' :
        case 'conditionwhereserviceid_node_form' :
        case 'conditionwhocustomfactors_node_form' :
        case 'conditionwhocalledcarrier_node_form' :
        case 'conditionwhomemberfactors_node_form' :
        case 'conditionwhonumberfactors_node_form' :
        case 'conditionwhoprefixfactors_node_form' :
        case 'conditionwhosubscribermdn_node_form' :
        case 'conditioncommoncounterfactors_node_form' :
        case 'conditionwhatqos_node_form' :
        case 'tvchannel_node_form' :
        case 'conditionwhocustomerlevel_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_weight']);
            unset($form['field_parent_node']);
            break;
        case 'conditionwhosubscriberstatus_node_form' :
            // Edit
            if (!empty($form['nid']['#value'])) {

            } else {// Create
                $productNid = $form_state['root_nid'];
                $view = views_get_view('list_lifecycle_scheme');
                $view -> set_display('panel_pane_5');
                $view -> set_arguments(array('0' => $productNid));
                $view -> execute();

                // lifecycle scheme이 선택되어 있지 않을때.
                if (empty($view -> result)) {
                    unset($form['actions']);
                    unset($form['field_subscriber_status']);
                    //$form['chart_button'] = array('#type' => 'markup', '#markup' => '<h3> You should select lifecycle scheme First! </h3>', );
                } else {
                    $options = array();
                    foreach ($view->result as $record) {
                        $statusNid = $record -> field_field_lifecycle_states[0]['raw']['nid'];
                        $statusName = $record -> field_field_lifecycle_states[0]['rendered']['#title'];
                        $options[$statusNid] = $statusName;

                    }
                    $form['field_subscriber_status']['und']['#options'] = $options;
                }
            }
            _unset_menu_items($form, $form_id);
            unset($form['field_weight']);
            unset($form['field_parent_node']);
            break;

        case 'conditionwhendurationfactors_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_weight']);
            unset($form['field_parent_node']);

            $first_day_this_month = date('Y-m-01 00:00:00');
            $lst_day_of_month = date('Y-m-t 23:59:00');

            if (!isset($form['nid']['#value'])) {
                $form['field_duration']['und'][0]['#default_value']['value'] = $first_day_this_month;
                $form['field_duration']['und'][0]['#default_value']['value2'] = $lst_day_of_month;
            }

            break;

        case 'conditionwhaturlgroups_node_form' :
        case 'conditionwhatcustom_node_form' :
        case 'conditionwhencustom_node_form' :
        case 'conditionwhenday_node_form' :
        case 'conditionwhentimeslot_node_form' :
        case 'conditionwhenweek_node_form' :
        case 'conditionwherecountry_node_form' :
        case 'conditionwherecustom_node_form' :
        case 'conditionwherenetwork_node_form' :
        case 'conditionwherezone_node_form' :
        case 'conditionwhocustom_node_form' :
        case 'conditionwhomember_node_form' :
        case 'conditionwhonumber_node_form' :
        case 'conditionwhoprefix_node_form' :
        case 'conditionwheremacaddress_node_form' :
        case 'conditionwheredeivcetype_node_form' :
            _unset_menu_items($form, $form_id);
            //$form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            //$form['actions']['submit']['#submit'][] = '_condition_submit_handler';
            break;
        case 'conditionwhenduration_node_form' :
            _unset_menu_items($form, $form_id);
            break;
        case 'feeds_import_form' :
            $form['#submit'][] = 'product_catalog_form_form_redirect_handler';
            break;
        case 'area_code_node_form' :
            _unset_menu_items($form, $form_id);
            //for select all carrier.
            $form['field_ref_carrier_mobile']['und']['#options']['_none'] = 'All';
            break;
        case 'number_special_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_parent_node']);
            unset($form['field_weight']);

            if (!isset($form['nid']['#value'])) {
                // $form['actions']['submit']['#submit'][]  = 'product_catalog_form_form_redirect_handler';
            } else {
                $form['field_target_usage_type‎']['und']['#disabled'] = TRUE;
            }
            break;
        case 'views_form_list_area_ratinggroup_panel_pane_1' :
            unset($form['actions']['submit']['#suffix']);
            break;

        case 'number_ratinggroup_node_form' :
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            unset($form['field_ref_number_sp_rule']);
            _unset_menu_items($form, $form_id);
            break;
        case 'number_special_rule_node_form' :
            unset($form['field_ref_action_charge']);
            unset($form['field_ref_action_discount']);
            unset($form['field_ref_action_allow']);
            unset($form['field_ref_action_system']);
            $form['actions']['submit']['#submit'][] = '_number_sp_rule_submit_handler';
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            unset($form['field_ref_condition_factor']);
            _unset_menu_items($form, $form_id);
            break;
        case 'actionpricefactors_node_form' :
            _alter_field_action_price_factors($form, $form_state);
            $form['actions']['submit']['#submit'][] = '_rule_actionprice_submit_handler';
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            _unset_menu_items($form, $form_id);
            break;

        case 'carrier_node_form' :
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            unset($form['field_ref_prefix']);
            unset($form['field_ref_rating_group']);
            unset($form['field_service_type_of_provider']);
            unset($form['field_service_type_of_carrier']);
            _unset_menu_items($form, $form_id);
            break;
        case 'prefix_node_form' :
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                $form['actions']['submit']['#submit'][] = '_prefix_link_to_carrier';
            }
            _unset_menu_items($form, $form_id);
            unset($form['field_ref_area_code']);
            break;

        case 'rule_node_form' :
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';

            // only for create
            //
            if (!isset($form['nid']['#value'])) {

                if (isset($form_state['ratinggroup_nid'])) {
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
            _unset_menu_items($form, $form_id);
            break;
        case 'rating_group_node_form' :
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_carrier';
            }
            unset($form['field_ref_rule']);
            _unset_menu_items($form, $form_id);
            break;
        case 'numberingplan_idd_node_form' :
            unset($form['field_ref_idd_ratinggroup']);
            // $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            _unset_menu_items($form, $form_id);
            break;
        case 'idd_ratinggroup_node_form' :
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                if (isset($form_state['numberingplan_idd_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_numberingplan_idd';
                }
            }
            $form['field_ref_numberingplan_idd']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            //for selecting all carrier
            $newOptions = array();
            $newOptions['_none'] = 'All';
            
            //filter only idd carrier
            $view = views_get_view('list_carrier_mobile');
            $view -> set_display('panel_pane_3');
            $view -> set_arguments(array('0' => 'International'));
            $view -> execute();
            foreach($view->result as $item){
                $newOptions[$item->nid] = $item->node_title;
            }
            
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call']['und']['#options'] = $options;
            
            $form['field_ref_carrier_mobile']['und']['#options'] = $newOptions;
            break;
        case 'basicrate_idd_node_form' :
            unset($form['title']);
            unset($form['field_ref_condition_idd']);
            unset($form['revision_information']);
            unset($form['field_parent_node']);
            unset($form['field_weight']);

            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                $form['actions']['submit']['#submit'][] = '_basicrate_idd_link_to_usage';
            }
            _unset_menu_items($form, $form_id);
            break;
        case 'basicrate_domestic_node_form' :
            unset($form['title']);
            unset($form['revision_information']);
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);

            break;
        case 'numberingplan_domestic_node_form' :
            unset($form['field_ref_domestic_ratinggroup']);
            _unset_menu_items($form, $form_id);
            break;
            
        case 'roaming_plan_node_form' :
            unset($form['field_ref_roaming_ratinggroup']);
            _unset_menu_items($form, $form_id);
            break;
            
        case 'depositschemefactors_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_depositscheme']['#type'] = 'hidden';
            $form['field_is_default_factor']['#type'] = 'hidden';
            
            $depositSchemeFactorNode = node_load($form['nid']['#value']);
            
            if (!isset($form['nid']['#value'])) {// create
              $depositSchemeNode = node_load($form_state['build_info']['args'][0] -> field_ref_depositscheme['und'][0]['nid']);
              $serviceDomainTid = $depositSchemeNode -> field_service_domain['und'][0]['tid'];
              $form['field_thismonth_accu_counter']['#type'] = 'hidden';

							$options = array();
							$options['_none'] = '- None -';
							              
              $counterUnitType = $form_state['values']['field_counter_unit_type']['und'][0]['tid'];
              if(!empty($counterUnitType)) {
	              $view = views_get_view('list_counter');
	              $view -> set_display('panel_pane_10');
	              $view -> set_arguments(array('0' => $serviceDomainTid,
	              														'1' => $counterUnitType)
	              											);
	              $view -> execute();
	              
	              foreach ($view->result as $item) {
	              		$options[$item->nid] = view_get_field_value_by_label($view, 'PHP', $item);
	              }
	            }
	            
              $form['field_ref_thres_counter_acc']['und']['#options'] = $options;
              $form['field_ref_thres_counter_limit']['und']['#options'] = $options;
              
              

            } else {// edit
			  			$depositSchemeNode = node_load($depositSchemeFactorNode->field_ref_depositscheme['und'][0]['nid']);
              $serviceDomainTid = $depositSchemeNode->field_service_domain['und'][0]['tid'];
              
              $isDefaultFactor = $form_state['build_info']['args'][0]->field_is_default_factor['und'][0]['value'];
              
              if ($isDefaultFactor == 1) {
                  $form['title']['#disabled'] = TRUE;

                  // Only rollover counters
                  $view = views_get_view('list_counter');
                  $view -> set_display('panel_pane_12');
                  $view -> set_arguments(array('0' => $serviceDomainTid));
                  $view -> execute();

                  $options = array();
                  $options['_none'] = '- None -';
                  foreach ($view->result as $item) {
                      $options[$item -> nid] = $item -> node_title;
                  }
                  $form['field_thismonth_accu_counter']['und']['#options'] = $options;

              } else {
                  $form['field_thismonth_accu_counter']['#type'] = 'hidden';
              }

              $counterUnitType = $form_state['values']['field_counter_unit_type']['und'][0]['tid'];
              if(empty($counterUnitType)) {
              	$counterUnitType = $form_state['build_info']['args'][0]->field_counter_unit_type['und'][0]['tid'];
              }
              
              $view = views_get_view('list_counter');
              $view -> set_display('panel_pane_10');
              $view -> set_arguments(array('0' => $serviceDomainTid,
              														'1' => $counterUnitType)
              											);
              $view -> execute();
              
              $options = array();
              $options['_none'] = '- None -';
              foreach ($view->result as $item) {
              		$options[$item->nid] = view_get_field_value_by_label($view, 'PHP', $item);
              }
              
              $form['field_ref_thres_counter_acc']['und']['#options'] = $options;
              $form['field_ref_thres_counter_limit']['und']['#options'] = $options;
              
            }
            
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call_mul']['und']['#options'] = $options;
             
            $form['field_ref_thres_counter_acc']['#prefix'] = '<div id="deposit_counter_set">';
            $form['field_ref_thresholdscheme']['#prefix'] = '</div>';
            
            $form['field_counter_unit_type']['und']['#ajax'] = array(
                'callback' => 'deposit_counter_callback',
                'wrapper' => 'deposit_counter_set',
            );
            
            break;
            
        case 'depositschemeadjustment_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_depositscheme']['#type'] = 'hidden';

            break;

        case 'domestic_ratinggroup_node_form' :
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                if (isset($form_state['numberingplan_domestic_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_ratinggroup_link_to_numberingplan_domestic';
                }
            }
            $form['field_ref_numberingplan_domestic']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            //for selecting all carrier
            $newOptions = array();
            $newOptions['_none'] = 'All';
            
            //filter only domestic carrier
            $view = views_get_view('list_carrier_mobile');
            $view -> set_display('panel_pane_3');
            $view -> set_arguments(array('0' => 'Domestic'));
            $view -> execute();
            foreach($view->result as $item){
                $newOptions[$item->nid] = $item->node_title;
            }
            $form['field_ref_carrier_mobile']['und']['#options'] = $newOptions;
            
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call']['und']['#options'] = $options;
            
            //for select all area
            $form['field_ref_area_code_from']['und']['#options']['_none'] = 'All';
            $form['field_ref_area_code_to']['und']['#options']['_none'] = 'All';
            break;
        case 'country_code_node_form' :
            $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            _unset_menu_items($form, $form_id);
            break;
        case 'timetable_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_ref_timetablefactors']);
            if (!isset($form['nid']['#value'])) {
                $form['actions']['submit']['#submit'][] = 'timetable_submit_handler';
            }
            // $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
            break;
        case 'timetablefactors_node_form' :
            unset($form['field_timeslot']['und'][0]['_remove']);
            _unset_menu_items($form, $form_id);
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                if (isset($form_state['timetable_nid'])) {
                    $form['actions']['submit']['#submit'][] = '_timetablefactors_link_to_timetable';
                }
            }
            break;
        case 'actionblockfactors_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            break;
        case 'conditioncommoncarrieridd_node_form' :
        case 'conditioncommoncarrierdomestic_node_form' :
        case 'conditioncommonratinggroup_node_form' :
        case 'conditioncommontimetablefactors_node_form' :
        case 'actionpricediscountfactors_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';

            $parentTerm = taxonomy_term_load($form_state['build_info']['args'][0] -> field_ref_tree_tid['und'][0]['value']);
            if ($parentTerm -> vocabulary_machine_name != 'tpl_tariffplan_voice') {//for single price such as sms
                unset($form['field_range_units']);
                unset($form['field_uom_units']);
                unset($form['field_discount_collection']);
            } else {
                $termTid = array_search('Seconds', $form['field_range_units']['und']['#options']);
                $form_state['build_info']['args'][0] -> field_range_units['und'][0]['tid'] = $termTid;
                unset($form['field_discount_']);
                $form['field_range_units']['und']['#default_value'] = $termTid;
                $form['field_range_units']['und']['#disabled'] = TRUE;
            }
            break;
       
        case 'actionpricecugdiscountfactors_node_form':
        		unset($form['field_parent_node']);
        		unset($form['field_weight']);
        		_unset_menu_items($form, $form_id);
        		//unset($form['field_ref_product']);
                //unset($form['field_ref_tree_tid']);
                //unset($form['field_ref_tree_nid']);
        		$form['field_ref_product']['#type'] = 'hidden';
        		$form['field_ref_tree_tid']['#type'] = 'hidden';
        		$form['field_ref_tree_nid']['#type'] = 'hidden';
        		
        		break;
       		
        case 'actionbonustransfer_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            break;

				case 'conditionwhatratinggroup_node_form' :
						unset($form['field_parent_node']);
						unset($form['field_weight']);
						_unset_menu_items($form, $form_id);
						break;
						
        case 'conditionwhatcounter_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            if (!isset($form['nid']['#value'])) {
                $rootNid = $form_state['root_nid'];
            } else {
                $rootNid = $form['#node'] -> field_ref_product['und'][0]['nid'];
            }

            // $existingCounterList = _get_existing_counter_list($form_state['product_nid']);
            $existingCounterList = _get_existing_counter_list($rootNid);
						$basicCounterList = _get_default_basic_counters($form_state['root_nid']);
						$counterList = $existingCounterList + $basicCounterList;
						
						$counterList = array_unique($counterList);
						
            //$form['field_ref_counter']['und']['#options'] = $existingCounterList;
            $form['field_ref_counter']['und']['#options'] = $counterList;
            break;

        case 'conditionwhatcounterfortracking_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);

            break;

        case'actionpriceallowanceonetime_node_form' :
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';

            _unset_menu_items($form, $form_id);

            break;

        case 'actionpriceallowancerecurring_node_form' :
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';

            _unset_menu_items($form, $form_id);
            break;

        case 'actionpriceallowance_node_form' :
        case 'actionpriceallowancefactors_node_form' :
            $form['field_allow_start']['#type'] = 'hidden';
            $form['field_allow_interval']['#type'] = 'hidden';
            $form['field_allow_interval_unit']['#type'] = 'hidden';

            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            // only for create
            //
            if (!isset($form['nid']['#value'])) {
                $rootNid = $form_state['root_nid'];
            } else {
                $rootNid = $form['#node'] -> field_ref_product['und'][0]['nid'];
            }

            unset($form['field_ref_counter']['und']['#options']);
            $form['field_ref_counter']['und']['#options']['_none'] = '- None -';

            $productCountView = views_get_view('list_treenodecounter');
            $productCountView -> set_display('panel_pane_2');
            $productCountView -> set_arguments(array(0 => $rootNid));
            $productCountView -> execute();
            $counters = $productCountView -> result;

            foreach ($counters as $counter) {
                $form['field_ref_counter']['und']['#options'][$counter -> nid] = $counter -> node_field_data_field_ref_counter_title;
            }
            break;
        case 'actionpricechargefactors_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            unset($form['field_ref_product']);
            unset($form['field_ref_tree_tid']);
            unset($form['field_ref_tree_nid']);
            _unset_menu_items($form, $form_id);

            $parentTerm = taxonomy_term_load($form_state['build_info']['args'][0] -> field_ref_tree_tid['und'][0]['value']);
            switch($parentTerm->vocabulary_machine_name){
                case 'tpl_tariffplan_sms':
                    $termTid = array_search('Counts', $form['field_uom_units']['und']['#options']);
                    $form_state['build_info']['args'][0] -> field_uom_units['und'][0]['tid'] = $termTid;
                    $form['field_uom_units']['und']['#default_value'] = $termTid;
                    $form['field_uom_units']['und']['#disabled'] = TRUE;
                    unset($form['field_charge_collection']);
                    unset($form['field_range_units']);
                    break;
                case 'tpl_tariffplan_data':
                    $termTid = array_search('Bytes', $form['field_uom_units']['und']['#options']);
                    $form_state['build_info']['args'][0] -> field_uom_units['und'][0]['tid'] = $termTid;
                    $form['field_uom_units']['und']['#default_value'] = $termTid;
                    $form['field_uom_units']['und']['#disabled'] = TRUE;
                    unset($form['field_charge_collection']);
                    unset($form['field_range_units']);
                    break;
                default:
                    $termTid = array_search('Seconds', $form['field_range_units']['und']['#options']);
                    $form_state['build_info']['args'][0] -> field_range_units['und'][0]['tid'] = $termTid;
                    $form['field_range_units']['und']['#default_value'] = $termTid;
                    $form['field_range_units']['und']['#disabled'] = TRUE;
    
                    $termTid = array_search('Seconds', $form['field_uom_units']['und']['#options']);
                    $form_state['build_info']['args'][0] -> field_uom_units['und'][0]['tid'] = $termTid;
                    $form['field_uom_units']['und']['#default_value'] = $termTid;
                    $form['field_uom_units']['und']['#disabled'] = TRUE;
    
                    unset($form['field_price']);
                    break;
            }
            break;
        case 'actionpricediscount_node_form' :
        case 'actionpricechargeonetime_node_form' :
        case 'actionpricechargerecurring_node_form' :
        case 'actionpricechargerecurringdefaul_node_form':
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            
            // in case EDIT
            if (isset($form['nid']['#value'])) {
                $product = node_load($form_state['build_info']['args'][0] -> field_ref_product['und'][0]['nid']);
                $currencyTid = $product -> field_price_units['und'][0]['tid'];
                
            // Create
            } else {
                if (!empty($form_state['root_nid'])) {
                    $product = node_load($form_state['root_nid']);
                    $currencyTid = $product -> field_price_units['und'][0]['tid'];

					$form['field_recurring_charge_id']['#type'] = 'hidden';
                    $form['field_recurring_charge_id']['und'][0]['value']['#default_value'] = $product->field_product_id['und'][0]['value'] . '_' . time();
                }
                
            }

            if (isset($currencyTid)) {
                $currencyTerm = taxonomy_term_load($currencyTid);
                $form['field_price_amount']['und'][0]['value']['#field_suffix'] = $currencyTerm -> name;
            } else {
                // drupal_set_message(t('First ! you should set currency in product edit page'));
            }

            _unset_menu_items($form, $form_id);
            break;
            
        case 'actionsetcounter_node_form' :
        
            $form['field_ref_source_action']['#type'] = 'hidden';
            $productNid = $form_state['product_nid'];
            
            $basicCounterList = array();
            $basicCounterList = _get_default_basic_counters($productNid);
            $existingCounterList = _get_existing_counter_list($productNid);
            
            $mergedCounterList = $basicCounterList + $existingCounterList;
            $form['field_ref_counter']['und']['#options'] = $mergedCounterList;

            _unset_menu_items($form, $form_id);
            
            $form['field_enddate_option1']['#prefix'] = '<div id="actionsetcounter_fields_wrapper">';
            $form['field_enddate_option2']['#postfix'] = '</div>';
            
            $form['field_ref_counter']['und']['#ajax'] = array(
                'callback' => 'actionsetcounter_ajax_callback',
                'wrapper' => 'actionsetcounter_fields_wrapper'
            );
            break;
        case 'roaming_ratinggroup_node_form' :
            $form['field_ref_roaming_plan']['#type'] = 'hidden';
            $form['field_ref_roaming_type']['und']['#options']['_none'] = 'SMS Outgoing';
            
            _unset_menu_items($form, $form_id);
            $carrierOptions = array();
            $carrierOptions['_none'] = ' - None -';
            $zoneOptions = array();
            $zoneOptions['_none'] = ' - None -';
            
            $roamingCountryNid = NULL;
            $roamingCarrierNid = NULL;
            $roamingTypeTid = NULL;
            if(isset($form_state['values'])){
                $roamingCarrierNid = $form_state['values']['field_ref_roaming_carrier']['und'][0]['nid'];
                $roamingCountryNid = $form_state['values']['field_ref_roaming_country']['und'][0]['nid'];
                $roamingTypeTid = $form_state['values']['field_ref_roaming_type']['und'][0]['tid'];
            }else{
                if (isset($form['nid']['#value'])) {
                    $roamingCarrierNid = $form_state['build_info']['args'][0]->field_ref_roaming_carrier['und'][0]['nid'];    
                    $roamingCountryNid = $form_state['build_info']['args'][0]->field_ref_roaming_country['und'][0]['nid'];    
                    $roamingTypeTid = $form_state['build_info']['args'][0]->field_ref_roaming_type['und'][0]['tid'];    
                }
            }
            
            $view = views_get_view('list_roaming_carrier');
            $view->set_display('panel_pane_3');
            $view->set_arguments(array('0' => $roamingCountryNid));
            $view->execute(); 
            foreach($view->result as $item){
                $carrierOptions[$item->nid] = $item->node_title;
            } 
            $form['field_ref_roaming_carrier']['und']['#options'] = $carrierOptions;
            //$form['field_ref_roaming_carrier']['und']['#default_value'] = $form_state['values']['field_ref_roaming_carrier']['und'][0]['nid'];
            if(isset($roamingTypeTid)){
                $roamingTypeTerm = taxonomy_term_load($roamingTypeTid);
                switch($roamingTypeTerm->name){
                   case 'Other PLMN':
                       $options = array();
                       $options['_none'] = '- None -';
                        
                       $view = views_get_view('list_roaming_zone');
                       $view->set_display('panel_pane_3');
                       $view->set_arguments(array('0' => $roamingCarrierNid));
                       $view->execute(); 
                       foreach($view->result as $item){
                           $zoneOptions[$item->nid] = $item->node_title;
                       } 
                       $form['field_roaming_zone']['und']['#options'] = $zoneOptions;
                       break;
                   default:
                       unset($form['field_roaming_zone']);
                       break;
                }
            } 
           
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call']['und']['#options'] = $options;
                
            // add custom id for ajax
            $form['field_ref_roaming_carrier']['und']['#prefix'] = '<div id="custom_roaming_ratinggroup_carrier">';
            $form['field_ref_roaming_carrier']['und']['#postfix'] = '</div>';
             
            // add ajax callback
            $form['field_ref_roaming_country']['und']['#ajax'] = array(
                'callback' => 'roaming_options_callback_carrier',
                'wrapper' => 'custom_roaming_ratinggroup_carrier'
            );
            
            $form['field_roaming_zone']['und']['#prefix'] = '<div id="custom_roaming_ratinggroup_zone">';
            $form['field_roaming_zone']['und']['#postfix'] = '</div>';
            
            $form['field_ref_roaming_type']['und']['#ajax'] = array(
                'callback' => 'roaming_options_callback_zone',
                'wrapper' => 'custom_roaming_ratinggroup_zone'
            );
            $form['field_ref_roaming_carrier']['und']['#ajax'] = array(
                'callback' => 'roaming_options_callback_zone',
                'wrapper' => 'custom_roaming_ratinggroup_zone'
            );
            
            break;
            
        case 'actionsetbonusonrecurringcharge_node_form' :
        
            $form['field_ref_source_action']['#type'] = 'hidden';
            $productNid = $form_state['product_nid'];

						$basicCounterList = array();
						$existingCounterList = array();
						
            $product = node_load($productNid);
            
            $billingTypeTerm = taxonomy_term_load($product -> field_billing_type['und'][0]['tid']);
            if ($billingTypeTerm -> name == 'Postpaid') {
                $tempTerm = taxonomy_get_term_by_name('Prepaid', 'billtypecounter');
                $existingCounterList = _get_existing_counter_list($productNid,  current($tempTerm) -> tid);

            } else {
                $basicCounterList = _get_default_basic_counters($productNid);
                $existingCounterList = _get_existing_counter_list($productNid);

            }
            $mergedCounterList = $basicCounterList + $existingCounterList;
            
            $form['field_ref_counter']['und']['#options'] = $mergedCounterList;
            /*
            $form['field_ref_counter']['#ajax'] = 
            	array('callback' => '_ajax_counter_type_validate',
            				'event' => 'change');
            */
            
            _unset_menu_items($form, $form_id);
            break;

        case 'actionsetcounteronbonus_node_form' :
        	
            $form['field_ref_source_action']['#type'] = 'hidden';
            $productNid = $form_state['product_nid'];

            $product = node_load($productNid);
            $billingTypeTerm = taxonomy_term_load($product -> field_billing_type['und'][0]['tid']);
            if ($billingTypeTerm -> name == 'Postpaid') {
                $tempTerm = taxonomy_get_term_by_name('Prepaid', 'billtypecounter');
                $existingCounterList = _get_existing_counter_list($productNid,  current($tempTerm) -> tid);

            } else {
                $basicCounterList = array();
                $basicCounterList = _get_default_basic_counters($productNid);
                
                $existingCounterList = _get_existing_counter_list($productNid);

            }
            
            $mergedCounterList = $basicCounterList + $existingCounterList;
            $form['field_ref_counter']['und']['#options'] = $mergedCounterList;
            
            $form['field_ref_counter']['#ajax'] = 
            	array('callback' => '_ajax_counter_type_validate',
            				'event' => 'change');
            
            _unset_menu_items($form, $form_id);
            break;

        case 'tariffplan_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_product']['#type'] = hidden;
            $form['field_ref_tree_tid']['#type'] = hidden;
            unset($form['field_tree_child_voca_name']);
            unset($form['field_ref_numberingplan_domestic']);
            unset($form['field_ref_numberingplan_idd']);
            unset($form['field_ref_timetable_domestic']);
            unset($form['field_ref_tariffplan_idd_carrier']);
            unset($form['field_ref_numberspecial']);
            unset($form['field_ref_roaming_plan']);
            _unset_menu_items($form, $form_id);

            if (!isset($form['nid']['#value'])) {
                $relTypeTerm = taxonomy_term_load($form_state['build_info']['args'][0] -> field_ref_tree_tid['und'][0]['value']);

                $productNode = node_load($form_state['build_info']['args'][0] -> field_ref_product['und'][0]['nid']);
                $serviceDomainTerm = taxonomy_term_load($productNode -> field_service_type_of_provider['und'][0]['tid']);
                $serviceTypeTerm = taxonomy_term_load($form_state['build_info']['args'][0] -> field_ref_tree_tid['und'][0]['value']);

                $ref_voca_name = _get_vocabulary_name('tariffplan', $productNode, $serviceTypeTerm -> name);
                $form_state['build_info']['args'][0] -> field_tree_child_voca_name['und'][0]['value'] = $ref_voca_name;
            }

            $form_state['ajax_actions'][] = '_node_save_handler_for_add_js_settings_after_node_save';
            break;
            
        case 'numberspecialfactors_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_numberspecial']['#type'] = 'hidden';
            _unset_menu_items($form, $form_id);
            
            $options = array();
            $options['_none'] = '- None -';
            
            $view = views_get_view('list_number_special_rate');
            $view->set_display('panel_pane_1');
            $view->set_arguments(array('0' => $form['#node']->field_ref_numberspecial['und'][0]['nid']));
            $view->execute(); 
            foreach($view->result as $item){
                $options[$item->nid] = $item->node_title;
            }
            
            $form['field_ref_numberspecialrate']['und']['#options'] = $options;
            
            //calltype
            $options = _get_call_type_options();
            $form['field_ref_type_of_call']['und']['#options'] = $options;
            break;
            
        case 'numberspecialrate_node_form' :
            unset($form['field_parent_node']);
            unset($form['field_weight']);
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_numberspecial']['#type'] = 'hidden';

            //unset unused unit type
            $optionKeys = array_keys($form['field_range_units']['und']['#options']);
            forEach($optionKeys as $key){
                if($form['field_range_units']['und']['#options'][$key] === 'MBytes'){
                    unset($form['field_range_units']['und']['#options'][$key]);
                }
            }
            $optionKeys = array_keys($form['field_uom_units']['und']['#options']);
            forEach($optionKeys as $key){
                if($form['field_uom_units']['und']['#options'][$key] === 'Bytes'){
                    unset($form['field_uom_units']['und']['#options'][$key]);
                }
            }
          
            unset($form['field_range_units']['und']['#options'][391]);
            $numberSpecialNode = node_load($form['#node'] -> field_ref_numberspecial['und'][0]['nid']);

            if (isset($numberSpecialNode -> field_target_usage_type['und'][0]['tid'])) {
                $usageTypeTerm = taxonomy_term_load($numberSpecialNode -> field_target_usage_type['und'][0]['tid']);
                if ($usageTypeTerm -> name == 'SMS') {
                    unset($form['field_charge_collection']);
                    unset($form['field_range_units']);
                    unset($form['field_uom_units']);
                }
            }
            _unset_menu_items($form, $form_id);
            break;
        case 'unittransfer_node_form' :
            _unset_menu_items($form, $form_id);
            unset($form['field_ref_unittransferfactors']);
            //if (!isset($form['nid']['#value'])) {
            //    $form['actions']['submit']['#submit'][] = '_unittransfer_submit_handler';
            //}
            break;
        case 'unittransferfactor_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_counter_group']['#type'] = 'hidden';
            $form['field_counter_group']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_parent_node']['#type'] = 'hidden';
            
            $options = array();
            $options['_none'] = '- None -';
            $view = views_get_view('list_counter');
            $view->set_display('panel_pane_15');
            $view->set_arguments(array('0' => $form['field_counter_group']['und']['#default_value'][0]));
            $view->execute(); 
            foreach($view->result as $item){
                $options[$item->nid] = $item->node_title;
            }
            
            $form['field_target_counter_for_ut']['und']['#options'] = $options;
            
            $form['field_enddate_option1']['#type'] = 'hidden';
            $form['field_startdate_option1']['#type'] = 'hidden';
            $form['field_enddate_option4']['#type'] = 'hidden';
            $form['field_enddate_option2']['#type'] = 'hidden';
            
            break;
        case 'rate_node_form' :
            unset($form['field_ref_tariffplan']);
            unset($form['field_ref_tree_tid']);

            if (isset($form_state['build_info']['args'][0] -> field_ref_tariffplan)) {
                $tariffPlan = node_load($form_state['build_info']['args'][0] -> field_ref_tariffplan['und'][0]['nid']);
                $product = node_load($tariffPlan -> field_ref_product['und'][0]['nid']);
                $currencyTerm = taxonomy_term_load($product -> field_price_units['und'][0]['tid']);
                $currencyName = $currencyTerm -> name;
            }
            unset($form['field_price_units']);
            $form['Currency'] = array('#type' => 'markup', '#markup' => '<div class="form-item"> <label>Currency </label>' . $currencyName . '</div>', '#weight' => 2);

            $parentTerm = taxonomy_term_load($form_state['build_info']['args'][0] -> field_ref_tree_tid['und'][0]['value']);

            switch($parentTerm->vocabulary_machine_name){
                case 'tpl_tariffplan_sms':
                    unset($form['field_range_units']);
                    unset($form['field_uom_units']);
                    unset($form['field_charge_collection']);
                    break;
                case 'tpl_tariffplan_data':
                    unset($form['field_range_units']);
                    unset($form['field_uom_units']);
                    unset($form['field_charge_collection']);
                    break;
                default:
                    $optionKeys = array_keys($form['field_range_units']['und']['#options']);
                    forEach($optionKeys as $key){
                        if($form['field_range_units']['und']['#options'][$key] === 'MBytes'){
                            unset($form['field_range_units']['und']['#options'][$key]);
                        }
                    }
                    $optionKeys = array_keys($form['field_uom_units']['und']['#options']);
                    forEach($optionKeys as $key){
                        if($form['field_uom_units']['und']['#options'][$key] === 'Bytes'){
                            unset($form['field_uom_units']['und']['#options'][$key]);
                        }
                    }
                    
                    unset($form['field_price']);
                    /*
                    $form['chart_button'] = array('#type' => 'markup', '#markup' => '<input id="chart_show" type="button" value="Refresh Chart"/>', '#weight' => 199);
    
                    $form['chart_fieldset'] = array('#type' => 'fieldset', '#title' => 'Chart', '#weight' => 200, );
                    $form['chart_fieldset']['chart'] = array('#type' => 'markup',
                    //'#markup' => '<div id="flot_div" class="hidden" style="height:500px;width:90%;" ></div>',
                    '#markup' => '<div id="flot_div" style="height:500px;width:90%;" ></div>', '#weight' => 0);
                    */
                    break;
            }
            _unset_menu_items($form, $form_id);
            break;
            
        case 'carrier_mobile_node_form' :
            _unset_menu_items($form, $form_id);
            break;
        case 'treenodevouchercardforproduct_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            break;
        case 'lifecyclescheme_node_form' :
            _unset_menu_items($form, $form_id);
            break;
        case 'packetdynamicchargingrule_node_form' :
            //calltype
            $options = _get_call_type_options();
            $form['field_sid_type_of_call']['und']['#options'] = $options;
             _unset_menu_items($form, $form_id);
            break;
        case 'packetdynamicl4_node_form' :
        case 'packetsgsn_node_form':
        case 'packetpredefinedchargingrule_node_form' :
        case 'roaming_country_node_form' :
        case 'roaming_carrier_node_form' :
            _unset_menu_items($form, $form_id);
            break;
        case 'roaming_zone_node_form':
            unset($form['field_roaming_carrier']);
            _unset_menu_items($form, $form_id);
            break;
        case 'treenodeotheronetimecharge_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_ref_otherontimecharge']['#type'] = 'hidden';

            // in case EDIT
            if (isset($form['nid']['#value'])) {
                $product = node_load($form_state['build_info']['args'][0] -> field_ref_product['und'][0]['nid']);
                $currencyTid = $product -> field_price_units['und'][0]['tid'];

            } else {
                if (!empty($form_state['root_nid'])) {
                    $product = node_load($form_state['root_nid']);
                    $currencyTid = $product -> field_price_units['und'][0]['tid'];
                }
            }

            if (isset($currencyTid)) {
                $currencyTerm = taxonomy_term_load($currencyTid);
                $form['field_price_amount']['und'][0]['value']['#field_suffix'] = $currencyTerm -> name;
            } else {
                // drupal_set_message(t('First ! you should set currency in product edit page'));
            }

            $custom_title = $form['title']['#default_value'];
            $form['custom_title'] = array('#type' => 'markup', '#markup' => '<h3>' . $custom_title . '</h3>', '#weight' => 0);
            break;
        case 'treenodeotheronetimechargediscou_node_form':
        		_unset_menu_items($form, $form_id);
        		$form['field_weight']['#type'] = 'hidden';
        		$form['field_ref_product']['#type'] = 'hidden';
        		$form['field_ref_tree_tid']['#type'] = 'hidden';
        		$form['field_ref_otherontimecharge']['#type'] = 'hidden';
        		$form['field_parent_node']['#type'] = 'hidden';
        		
        		break;    
        case 'treenodepacketdynamic_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            $form['field_ref_tariffplan']['#type'] = 'hidden';
            $form['field_ref_packet_dynamic']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';

            $ruleNode = node_load($form_state['build_info']['args'][0] -> field_ref_packet_dynamic['und'][0]['nid']);
            $l4Text = '';

            if (isset($ruleNode -> field_ref_packet_dynamic_l4)) {
                foreach ($ruleNode->field_ref_packet_dynamic_l4['und'] as $item) {
                    $l4Node = node_load($item['nid']);
                    $l4Text .= $l4Node -> title . '<br/>';
                }
            }

            $l4Node = node_load($ruleNode -> field_ref_packet_dynamic_l4['und'][0]['nid']);
            $meteringMethodTerm = taxonomy_term_load($ruleNode -> field_ref_metering_method['und'][0]['tid']);

            $refAttributeMarkupStr = '<div class="form-item">';
            $refAttributeMarkupStr .= '<table >';
            $refAttributeMarkupStr .= '<tr><td width="150px">' . '<label>L4</label></td><td>' . $l4Text . '</td></tr>';
            $refAttributeMarkupStr .= '<tr><td width="150px">' . '<label>Rating Group</label></td><td>' . $ruleNode -> field_rating_group_integer['und'][0]['value'] . '</td></tr>';
            $refAttributeMarkupStr .= '<tr><td width="150px">' . '<label>SID</label></td><td>' . $ruleNode -> field_sid['und'][0]['value'] . '</td></tr>';
            $refAttributeMarkupStr .= '</table>';
            $refAttributeMarkupStr .= '</div>';
            $form['ref_attribute'] = array('#type' => 'markup', '#markup' => $refAttributeMarkupStr, '#weight' => -100);
            break;
        case 'treenodepacketdefaultqos_node_form':
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            $form['field_ref_tariffplan']['#type'] = 'hidden';
            $form['field_ref_packet_dynamic']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
        
        		break;    
        case 'basicrate_data_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_ref_tree_nid']['#type'] = 'hidden';
            $form['field_ref_tariffplan']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            break;
        case 'prdattributerequireddevice_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            $form['field_ref_device_class']['#type'] = 'hidden';
            break;
        case 'prdattributenumbersaving_node_form' :
            _unset_menu_items($form, $form_id);
            $form['field_ref_product']['#type'] = 'hidden';
            $form['field_ref_tree_tid']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            break;
        case 'servicefeaturecode_node_form':
            _unset_menu_items($form, $form_id);
            $newServiceDomainOptions = array();
            $keys = array_keys($form['field_service_domain']['und']['#options']);
            $values = array_values($form['field_service_domain']['und']['#options']);
            $count = count($values);
            for($i=0;$i<$count;$i++){
                if($values[$i] === 'Cross' || $values[$i] == 'Dummy') continue;
                $newServiceDomainOptions[$keys[$i]] = $values[$i];
            }
            $form['field_service_domain']['und']['#options'] = $newServiceDomainOptions;
            break;
        case 'conditionwhatcontentprice_node_form':
            _unset_menu_items($form, $form_id);
            $form['field_parent_node']['#type'] = 'hidden';
            $form['field_weight']['#type'] = 'hidden';
            
            $options = array();
            $options['_none'] = '- None -';
            $view = views_get_view('list_rating_operation');
            $view->set_display('panel_pane_1');
            $view->execute(); 
            foreach($view->result as $item){
                $options[$item->tid] = $item->taxonomy_term_data_name;
            }
            $form['field_rating_operation']['und']['#options'] = $options;
            
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
    _add_ajax_submit_callback($form_id, $form);
    return $form;
}

function counter_bill_type_change_callback($form,$form_state){
		$counterTypeTerm = taxonomy_term_load($form_state['values']['field_counter_type']['und'][0]['tid']);
		$billTypeTerm = taxonomy_term_load($form_state['values']['field_billing_type_counter']['und'][0]['tid']);
		
		$counterGroupTermNames = array();
		if($billTypeTerm->name == 'Postpaid') {
			switch($counterTypeTerm->name) {
				case 'Basic':
					$counterGroupTermNames = array('REMAINS');
					foreach($counterGroupTermNames as $termName) {
						$term = current(taxonomy_get_term_by_name($termName, 'countergroup'));
						$options[$term->tid] = $term->name;
					};
					$form['field_counter_group']['und']['#options'] = $options;
					
					break;
				case 'Optional':
					$counterGroupTermNames = array('Threshold', 'Usage');
					foreach($counterGroupTermNames as $termName) {
						$term = current(taxonomy_get_term_by_name($termName, 'countergroup'));
						$options[$term->tid] = $term->name;
					};
					$form['field_counter_group']['und']['#options'] = $options;
					break;
			}
		}
		
    $returnStr = '<div id="counter_group">';
    $returnStr .= drupal_render($form['field_counter_group']);
    $returnStr .= '</div>';
    
    return $returnStr;
}

function actionsetcounter_ajax_callback($form, &$form_state){
    /*
    $form_state['hhhhhh'] = TRUE;
    $form_state['rebuild'] = TRUE;
    */
    $counterNode = node_load($form_state['values']['field_ref_counter']['und'][0]['nid']);
    $counterTypeTerm = taxonomy_term_load($counterNode->field_counter_type['und'][0]['tid']);
    
    if($counterTypeTerm->name !== 'Rollover'){
        $returnStr .= drupal_render($form['field_enddate_option1']);
        $returnStr .= drupal_render($form['field_startdate_option1']);
        $returnStr .= drupal_render($form['field_enddate_option3']);
        $returnStr .= drupal_render($form['field_enddate_option4']);
        $returnStr .= drupal_render($form['field_enddate_option2']);
        $returnStr .= drupal_render($form['actions']);
    }else{
        $returnStr = '<div id="actionsetcounter_fields_wrapper">';
        $returnStr .= drupal_render($form['actions']);
        $returnStr .= '</div>';
    }
    return $returnStr;
}

function deposit_counter_callback($form,$form_state) {

  $depositSchemeNode = node_load($form_state['build_info']['args'][0] -> field_ref_depositscheme['und'][0]['nid']);
  $serviceDomainTid = $depositSchemeNode -> field_service_domain['und'][0]['tid'];

	// set other counters only basic, optional counters
	$view = views_get_view('list_counter');
	$view -> set_display('panel_pane_10');
	$view -> set_arguments(array('0' => $serviceDomainTid,
															'1' => $form_state['values']['field_counter_unit_type']['und'][0]['tid'])
												);
	$view -> execute();
	
	$options = array();
	$options['_none'] = '- None -';
	foreach ($view->result as $item) {
			// $options[$item->nid] = view_get_field_value_by_label($view, 'Title', $item);
			$options[$item->nid] = $item -> node_title. '[' . $item->field_field_counter_unit_type[0]['rendered']['#title'] . ',' . $item->field_field_counter_id[0]['rendered']['#markup'] . ']';
	}
	$form['field_ref_thres_counter_acc']['und']['#options'] = $options;
	$form['field_ref_thres_counter_limit']['und']['#options'] = $options;
	
//	$renderStr = '<div id="deposit_counter_set">';
	$renderStr .= drupal_render($form['field_ref_thres_counter_acc']);
	$renderStr .= drupal_render($form['field_ref_thres_counter_limit']);
//	$renderStr .= '</div>';

	$form_state['rebuild'] = TRUE;
	
	return $renderStr;
}

function roaming_options_callback_carrier($form,$form_state){
    $roamingCountryNid = $form_state['values']['field_ref_roaming_country']['und'][0]['nid'];
    $view = views_get_view('list_roaming_carrier');
    $view->set_display('panel_pane_3');
    $view->set_arguments(array('0' => $roamingCountryNid));
    $view->execute(); 
    foreach($view->result as $item){
        $options[$item->nid] = $item->node_title;
    } 
    $form['field_ref_roaming_carrier']['und']['#options'] = $options;
    $renderStr = '<div id="custom_roaming_ratinggroup_carrier">';
    $renderStr .= drupal_render($form['field_ref_roaming_carrier']);
    $renderStr .= '</div>';
    
    return $renderStr;
    //$commands[] = ajax_command_replace("#custom_roaming_ratinggroup_carrier", $renderStr);
    //return array('#type' => 'ajax', '#commands' => $commands);
}

function roaming_options_callback_zone($form,$form_state){
    $roamingCarrierNid = $form_state['values']['field_ref_roaming_carrier']['und'][0]['nid'];
    $roamingTypeTid = $form_state['values']['field_ref_roaming_type']['und'][0]['tid'];
    $roamingTypeTerm = taxonomy_term_load($roamingTypeTid);
    switch($roamingTypeTerm->name){
       case 'Other PLMN':
           $options = array();
           $options['_none'] = '- None -';
           
           $zoneView = views_get_view('list_roaming_zone');
           $zoneView->set_display('selection');
           $zoneView->set_arguments(array('0' => $roamingCarrierNid));
           $zoneView->execute(); 
           foreach($zoneView->result as $item){
               $options[$item->nid] = $item->node_title;
           } 
           $form['field_roaming_zone']['und']['#options'] = $options;
           break;
       default:
           unset($form['field_roaming_zone']);
           break;
    }
    
    $renderStr = '<div id="custom_roaming_ratinggroup_zone">';
    $renderStr .= drupal_render($form['field_roaming_zone']);
    $renderStr .= '</div>'; 
   
    return $renderStr;
    //$commands[] = ajax_command_replace("#custom_roaming_ratinggroup", $renderStr);
    //return array('#type' => 'ajax', '#commands' => $commands);
}

// prdcounterlist에 있는 counter list를 리턴한다.
// 
function _get_existing_counter_list($productNid) {

    $view = views_get_view('list_prdcounterlist');
    $view -> set_display('panel_pane_2');
    $view -> set_arguments(array('0' => $productNid));
    $view -> execute();

    $counterList = array();

    foreach ($view->result as $record) {
        $existingCounterList[] = view_get_field_value_by_label($view, 'qtabConfigNid', $record);
    }

    $args[0] = join('+', $existingCounterList);

    $view = views_get_view('query_list_counter');
    $view -> set_display('panel_pane_3');
    $view -> set_arguments($args);
    $view -> execute();

    $retArray = array();
    foreach ($view->result as $record) {
    		$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
    		// $retArray[$record -> nid] = '';
        
     }

    return $retArray;
}

function _get_available_counter_list($productNid, $existingCounterNids) {
    
    $product = node_load($productNid);

    $term_billing_type_product = taxonomy_term_load($product -> field_billing_type['und'][0]['tid']);
    $term_product_type = taxonomy_term_load($product -> field_product_type['und'][0]['tid']);

    $args = array();

    // counter type (Basic ,Optional or all)
    /*
    if ($term_product_type -> name == 'Main') {
        $args[0] = 'all';
    } else {
        $temp1Term = taxonomy_get_term_by_name('Optional', 'countertype');
        $temp2Term = taxonomy_get_term_by_name('Rollover', 'countertype');
        $args[0] =  current($temp1Term) -> tid . '+' .  current($temp2Term) -> tid;
    }
    */
    
    // counter type : 모든 counter가 보이도록 함
    $temp1Term = taxonomy_get_term_by_name('Optional', 'countertype');
    $temp2Term = taxonomy_get_term_by_name('Rollover', 'countertype');
    $args[0] =  current($temp1Term) -> tid . '+' .  current($temp2Term) -> tid;
    // $args[0] = 'all';
    
    // service domain
    $args[1] = $product -> field_service_type_of_provider['und'][0]['tid'];

    if ($term_billing_type_product -> name == 'Hybrid' || $term_billing_type_product -> name == 'Postpaid') {
        $args[2] = 'all';
        
    } else {
        $term_billing_type_counter = taxonomy_get_term_by_name($term_billing_type_product -> name, 'billtypecounter');
        $args[2] =  current($term_billing_type_counter) -> tid;
        
    }

    if (isset($existingCounterNids)) {
        $args[3] = join('+', $existingCounterNids);
    }

    $view = views_get_view('query_list_counter');
    $view -> set_display('panel_pane_1');
    $view -> set_arguments($args);
    $view -> execute();

    $retArray = array();
    foreach ($view->result as $record) {
    	$retArray[$record -> nid] = view_get_field_value_by_label($view, 'PHP', $record);
    }

    return $retArray;
}

function ajax_example_add_more_add_one($form, $form_state) {
    return $form['names_fieldset'];
}

function ajax_example_add_more_remove_one() {
    $form_state['num_names']++;
    $form_state['rebuild'] = TRUE;
}

function _alter_field_action_price_factors(&$form, &$form_state) {

    if (isset($form['nid']['#value'])) {//Edit
        $form_state['rule_nid'] = $form_state['build_info']['args'][1]['rule_nid'];
        $form_state['price_type'] = $form_state['build_info']['args'][1]['price_type'];
    }

    $priceType = $form_state['price_type'];
    $rule = node_load($form_state['rule_nid']);

    $array_unset_items = array();
    $array_required = array();

    switch($priceType) {
        case 'CHARGE' :
            $array_unset_items = array('field_allow_start', 'field_allow_interval', 'field_allow_interval_unit', 'field_threshold', 'field_threshold_unit', 'field_ref_counter');
            $array_required = array('field_range_start', 'field_range_end', 'field_range_units');

            // action price ��� �ы�..
            // �����吏�린 ���吏�����ы� ��� ��
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
        case 'DISCOUNT' :
            $array_unset_items = array('field_allow_start', 'field_allow_interval', 'field_allow_interval_unit', 'field_ref_counter', );
            break;
        case 'ALLOWANCE' :
            $array_unset_items = array('field_range_start', 'field_range_end', 'field_range_units');
            $array_required = array('field_allow_start', 'field_allow_interval', 'field_allow_interval_unit', );
            break;
    }

    foreach ($array_unset_items as $item) {
        unset($form[$item]);
    }
    //required ��� �ы� �쇰� 二쇱��쇰� 留�� ��
    /*
     foreach($array_required as $item) {
     $form[$item]['und'][0]['value']['#required'] = TRUE;
     $form[$item]['und']['#required'] = TRUE;
     }
     */
    unset($form['field_action_price_factor_type']);
}

function _get_call_type_options(){
    //filter calltype based on service domain
    $view = views_get_view('list_calltype');
    $view -> set_display('panel_pane_1');
    //$view -> set_arguments(array('0' => $serviceDomainTid));
    $view -> execute();

    $options = array();
    //$options['_none'] = '- None -';
    foreach ($view->result as $item) {
        $str = $item->taxonomy_term_data_name . ' [';
        $str .= isset($item->taxonomy_term_data_field_data_field_service_domain_name)?$item->taxonomy_term_data_field_data_field_service_domain_name:'Not defined';
        $str .= ',';
        $str .= isset($item->field_field_sub_group1[0]['raw']['value'])?$item->field_field_sub_group1[0]['raw']['value']:'Not defined';
        $str .= ',';
        $str .= isset($item->field_field_sub_group2[0]['raw']['value'])?$item->field_field_sub_group2[0]['raw']['value']:'Not defined';
        $str .= ']';
        $options[$item->tid] = $str;
    }
    
    return $options;
}

function _get_product_exclusive_list($productNid){
    $product = node_load($productNid);
    $svcDomainTid = $product->field_service_type_of_provider['und'][0]['tid'];
    $billingTypeTid = $product->field_billing_type['und'][0]['tid'];
    $svcOperatorTid = $product->field_service_operator['und'][0]['tid'];
    $customerTypeTid = $product->field_customer_type['und'][0]['tid'];
    
    $options = array();
    
    $args = array('0' => $svcDomainTid,
                  '1' => $svcOperatorTid,
                  '2' => $billingTypeTid,
                  '3' => $customerTypeTid );
    $options['args'] = $args;
    
    $view = views_get_view('list_product_in_exclusive');
    $view->set_display('panel_pane_2');
    $view->set_arguments($args);
    $view->execute();
    
    $viewResult = $view->result;
    
    foreach($viewResult as $item) {
            $options['list'][$item->nid] = view_get_field_value_by_label($view, 'PHP', $item);
    }
    unset($options['list'][$productNid]);
    
    return $options;
}

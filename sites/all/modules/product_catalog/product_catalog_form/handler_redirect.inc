<?php
function product_catalog_form_form_redirect_handler(&$form, &$form_state){
	$redirect_url = '';
	switch($form['#form_id']){
		case 'simpleproductoffering_node_form':
		case 'balance_node_form':
		case 'conditionwhaturlgroupfactors_node_form':
		case 'context_admin_node_form_wrapper':
		case 'prodoffernonusagesubitem_node_form':
		case 'conditionwhaturlgroupfactors_node_form':
		case 'conditionwhatcustomfactors_node_form':
		case 'conditionwhencustomfactors_node_form':
		case 'conditionwhendurationfactors_node_form':
		case 'conditionwhendayfactors_node_form':
		case 'conditionwhentimeslotfactors_node_form':
		case 'conditionwhenweekfactors_node_form':
		case 'conditionwherecountryfactors_node_form':
		case 'conditionwherecustomfactors_node_form':
		case 'conditionwherenetworkfactors_node_form':
		case 'conditionwherezonefactors_node_form':
		case 'conditionwhocustomfactors_node_form':
		case 'conditionwhomemberfactors_node_form':
		case 'conditionwhonumberfactors_node_form':
		case 'conditionwhoprefixfactors_node_form':
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
		case 'conditionwhatqos_node_form':
        case 'conditioncommoncounterfactors_node_form':
            // rule에 포함된 condition을 처리할 경우에
            // common, product 관련 rule 처리에서
            if(isset($form_state['rule_nid']) ||
                isset($form_state['build_info']['args'][1]['rule_nid'])) {
                $temp_current_path = current_path();

                $current_path_array = explode('/conditions/', $temp_current_path);
                $current_path = $current_path_array[0];

                //product 에서..
                if(isset($form_state['parent_name'])){
                	$redirect_url = $current_path.'/edit'.'/'.$form_state['parent_name'];
                }
                //common에서
                else{
               		$redirect_url = $current_path.'/edit';
                }

            }
			break;

		case 'area_code_node_form':
			$redirect_url = 'common/area_code';
			break;
        case 'area_ratinggroup_node_form':
			$redirect_url = 'common/area_ratinggroup';
			break;
		case 'feeds_import_form':
			switch($form['#importer_id']){
				case 'area_code_importer':
					$redirect_url = 'common/area_code';
					break;
				case 'area_ratinggroup_importer':
					$redirect_url = 'common/area_ratinggroup';
					break;
			}
			break;
		/*
		case 'number_special_node_form':
			// create
            //
            if(!isset($form['nid']['#value'])){
				$redirect_url = 'common/number_special/'.$form_state['values']['nid'];
            }
			break;
		case 'number_ratinggroup_node_form':
			$redirect_url = 'common/number_ratinggroup';
			break;
		case 'number_special_rule_node_form':
			$redirect_url = 'common/number_sp_rule/'.$form_state['values']['nid'].'/edit';
			break;
		*/
        case 'actionpricefactors_node_form':

            $rule = node_load($form_state['rule_nid']);

            if($rule->type == 'rule') {

                //$redirect_url = 'common/rules/'.$form_state['rule_nid'].'/edit';

            } else {
                $redirect_url = 'common/number_sp_rule/'.$form_state['rule_nid'].'/edit';
            }
            break;

        case 'carrier_node_form':
            if(!isset($form['nid']['#value'])){
                $redirect_url = 'common/carrier/'.$form_state['service_type_of_provider'].'/'.$form_state['service_type_of_carrier'].'/'.$form_state['values']['nid'].'/edit/attribute';
            } else {
                $redirect_url = 'common/carrier/'.$form_state['service_type_of_provider'].'/'.$form_state['service_type_of_carrier'];
            }
            break;

        case 'rule_node_form':
            // create
            //
            if(!isset($form['nid']['#value'])){

                if(isset($form_state['ratinggroup_nid'])) {
                    $redirect_url = 'common/rules/'.$form_state['values']['nid'].'/edit';
                } else if(isset($form_state['nonusage_nid']) || isset($form_state['usage_nid'])) {
                    $redirect_url = 'designer/rules/'.$form_state['values']['nid'].'/edit/designer';
                } else if(isset($form_state['counter_nid'])) {
                    $redirect_url = 'designer/rules/'.$form_state['values']['nid'].'/edit/designer';
                }

            // edit
            } else {

                if(isset($form_state['ratinggroup_nid'])) {
                    $redirect_url = 'common/rules/'.$form_state['values']['nid'].'/edit';
                } else if (isset($form_state['nonusage_nid']) || isset($form_state['usage_nid'])){
                    $redirect_url = 'designer/rules/'.$form_state['values']['nid'].'/edit/designer';
                } else if (isset($form_state['counter_nid'])) {
                    $redirect_url = 'designer/rules/'.$form_state['values']['nid'].'/edit/designer';
                }
            }
            break;
       case 'numberingplan_idd_node_form':
       	   	$redirect_url = 'common/numberingplan_idd/'.$form_state['values']['nid'].'/ratinggroup#quickset-qtabs_common_data=4';
        	break;
       case 'numberingplan_domestic_node_form':
       	   	$redirect_url = 'common/numberingplan_domestic/'.$form_state['values']['nid'].'/ratinggroup#quickset-qtabs_common_data=3';
        	break;
        case 'country_code_node_form':
       	   	$redirect_url = 'common/country_code';
        	break;        
        case 'timetable_node_form':
        	$redirect_url = 'common/timetable/'.$form_state['values']['nid'].'/timetablefactors#quickset-qtabs_common_data=5';
        	break;
        case 'vouchercardtype_node_form':
            $redirect_url = 'common/vouchercardtype/edit/'.$form_state['values']['nid'];
            break;
        case 'counter_node_form':
        	$redirect_url = 'common/counter/edit/'.$form_state['values']['nid'].'#quickset-qtabs_common_data=1';
        	break;
        case 'carrier_mobile_node_form':
        	$redirect_url = 'common/carrier_mobile/'.$form_state['values']['nid'].'#quickset-qtabs_common_data=11';
        	break;
        	
	}

	if(!empty($redirect_url)){
		$form_state['redirect'] = 'http://'.$_SERVER['HTTP_HOST'].base_path().$redirect_url;
	}
}
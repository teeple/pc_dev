<?php
function _create_export_data_by_content_type($node){
	$data = array();
	
	switch($node->type){
		case 'simpleproductoffering':
			//Attribute
			//TODO: char, charuse 도 향후 포함되어야됨.
			$data['type'] = 'Product';			
			$data['product_name'] = $node->title;
			// $data['product_id'] = $node->field_id['und'][0]['safe_value'];
			$data['product_id'] = $node->nid;
			$data['Description']
			= isset($node->field_description[0])? $node->field_description[0]['raw']['safe_value']:'';
			$data['Status']
			= isset($node->field_offering_status[0])? $node->field_offering_status[0]['rendered']['#title']:'';
			/*
			$data['value']['ValidFor'] = array(
				'From' => isset($node->field_valid_for[0])? $node->field_valid_for[0]['raw']['value']:'',
			    'To' => isset($node->field_valid_for[0])? $node->field_valid_for[0]['raw']['value2']:'',
			);
			*/
			break;
    	case 'defaulttreenode':
    		$term = taxonomy_term_load($node->field_ref_tree_node_tid['und'][0]['value']);	
    		$relType = $term->description;
    		switch($relType){
    			case 'carrier_idd':
    				$data['type'] = 'Carrier_IDD';    				
					$data['carrier_idd_name'] = $term->name;
    				break;
    			case 'carrier_domestic':
    				$data['type'] = 'Carrier_Domestic';    				
					$data['carrier_domestic_name'] = $term->name;
    				break;    			
    			default:
    				$data['type'] = $term->name;    				
    				break;
    		}
    		break;
    	case 'tariffplan':
    		$data['type'] = $node->type;    		
    		if(isset($node->field_valid_for['und'][0]['value2'])){
    			$op = 'between';
    			$validFor = $node->field_valid_for['und'][0]['value'].'~'.$node->field_valid_for['und'][0]['value2'];
    		}else{
    			$op = '>=';
    			$validFor = $node->field_valid_for['und'][0]['value'];
    		}    		
    		$data['tariffplan_name'] = $node->title;
    		$data['ValidFor'] = array(
    			'op' => $op,
    			'value' => $validFor
    		);    		
    		break;
        case 'treenodecounter':
            $refCounter = node_load($node->field_ref_counter['und'][0]['nid']);
            $data['counter_name'] = $refCounter->title;
            $data['type'] = $refCounter->type;
            $data['code'] = $refCounter->field_code['und'][0]['value'];

            break;
    	case 'treenodewithnodereference':
    		$refNode = node_load($node->field_ref_node['und'][0]['nid']);
            switch($refNode->type) {
                case 'counter':
                    //$main_or_accumulated = taxonomy_term_load($refNode->field_main_or_accumulated['und'][0]['tid']);
                    //$counter_type = taxonomy_term_load($refNode->field_counter_type['und'][0]['tid']);
                    //$relType = 'treenode_' . $refNode->type .'_'.strtolower($main_or_accumulated->name).'_'.strtolower($counter_type->name);
                    break;
                default:
             		$data['type'] = $refNode->type;             		
		    		$data[$refNode->type.'_name'] = $refNode->title;       
                    break;
            }    		
    		break;
    	case 'treenodegeneral':
    		$data['type'] = $node->field_rel_type['und'][0]['value'];    		
    		$data['ratinggroup'] = $node->field_value['und'][0]['safe_value'];    		
    		break;
    	case 'basicrate_idd':
    	case 'basicrate_domestic':
    		$data['type'] = $node->type;    		
    		$data[$node->type.'_name'] = $node->title;
    		if(isset($node->field_ref_timetablefactors['und'][0]['nid'])){
    			$timetablefactor = node_load($node->field_ref_timetablefactors['und'][0]['nid']);
    			$data['timetablefactor_name'] = $timetablefactor->title;
    		}
    		if(isset($node->field_price_amount['und'][0]['value'])){
    			$data['price_amount'] = $node->field_price_amount['und'][0]['value'];
    		}
    		if(isset($node->field_price_units['und'][0]['tid'])){
    			$priceUnitTerm = taxonomy_term_load($node->field_price_units['und'][0]['tid']);
    			$data['price_unit'] = $priceUnitTerm->name;
    		}
    		if(isset($node->field_uom_amount['und'][0]['value'])){
    			$data['uom_amount'] = $node->field_uom_amount['und'][0]['value'];
    		}
    		if(isset($node->field_uom_units['und'][0]['tid'])){
	    		$uomUnitTerm = taxonomy_term_load($node->field_uom_units['und'][0]['tid']);
	    		$data['uom_unit'] = $uomUnitTerm->name;
    		}
    		break;    	
    	case 'actionpricechargefactors':
    		$priceCollectionView = views_get_view('list_price_collection_items');
			$priceCollectionView->set_arguments(array(0=>$node->nid));
			$priceCollectionView->execute();
			$prices = $priceCollectionView->result;
			
			foreach($prices as $priceItem){
				foreach($priceItem->field_field_charge_collection[0]['rendered']['#rows'] as $chargeCollectionItem){
					$data[] = array(
						'type' => $node->type,
						'range_unit' => $priceItem->field_field_range_units[0]['raw']['taxonomy_term']->name,
						'price_unit' => $priceItem->field_field_price_units[0]['raw']['taxonomy_term']->name,
						'uom_unit' => $priceItem->field_field_uom_units[0]['raw']['taxonomy_term']->name,
					
						'range_start' => $chargeCollectionItem['data'][0]['data']['#items'][0]['value'],
						'range_end' => $chargeCollectionItem['data'][1]['data']['#items'][0]['value'],
						'price_amount' => $chargeCollectionItem['data'][2]['data']['#items'][0]['value'],
						'uom_amount' => $chargeCollectionItem['data'][3]['data']['#items'][0]['value'],				
					);
				}
			}
			break;			
    	case 'conditionwhatqos':
    		$data['type'] = $node->type;
    		$level = array();    		
    		foreach($node->field_ref_qos_level['und'] as $qosItem){
    			$term = taxonomy_term_load($qosItem['tid']);
    			$level[] = $term->name;
    		}    		
    		$temp = $level;
    		$data['what_qos_level'] = $level;
    		break;    		
       case 'conditionwhatusagetypefactors':
    		$data['type'] = $node->type;
            $serviceTypeTerm = taxonomy_term_load($node->field_ref_usage_type['und'][0]['tid']);
    		$data['what_service_type'] = isset($serviceTypeTerm)? $serviceTypeTerm->name : null;
    		break;  
    	case 'conditionwhaturlgroupfactors':
    		$data['type'] = $node->type;
    		$urls = array();
    		foreach($node->field_url['und'] as $urlItem){
    			$urls[] = $urlItem['url'];
    		}
    		$data['what_url'] = $urls;
    		break;
    	case 'conditionwhatcustomfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_rating_factor['und'][0])){
	    		$ratingFactorTerm = taxonomy_term_load($node->field_rating_factor['und'][0]['tid']);
	    		$data['what_custom_rating_factor'] = $ratingFactorTerm->name;
    		}
    		if(isset($node->field_rating_operation['und'][0])){
    			$ratingOperationTerm = taxonomy_term_load($node->field_rating_operation['und'][0]['tid']);
	    		$data['what_custom_rating_op'] = $ratingOperationTerm->name;
    		}
    		if(isset($node->field_value['und'][0])){
    			$data['what_custom_rating_value'] = $node->field_value['und'][0]['safe_value'];
    		}
    		break;
    	case 'conditionwhendayfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_custom_date['und'][0])){
	    		$data['when_day'] = substr($node->field_custom_date['und'][0]['value'],0,10);
    		}
    		break;
    	case 'conditionwhendurationfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_duration['und'][0])){
    			$data['when_duration'] = $node->field_duration['und'][0]['value'].'~'.$node->field_duration['und'][0]['value2'];
    		}
    		break;
    	case 'conditionwhenholidayfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_is_holiday['und'][0])){
	    		if($node->field_is_holiday['und'][0]['value']){
	    			$data['when_holiday'] = true;
	    		}else{
	    			$data['when_holiday'] = false;
	    		}
    		}
    		break;
    	case 'conditionwhentimeslotfactors':
    		$data['type'] = $node->type;
    		foreach($node->field_timeslot['und'] as $timeslotItem){
    			$fromHour = $timeslotItem['from']['hour'];
    			$fromMinute = $timeslotItem['from']['minute'];
    			$toHour = $timeslotItem['to']['hour'];
    			$toMinute = $timeslotItem['to']['minute'];
    			$fromHour = _fill_blank_string_for_timeslot($fromHour);
    			$fromMinute = _fill_blank_string_for_timeslot($fromMinute);
    			$toHour = _fill_blank_string_for_timeslot($toHour);
    			$toMinute = _fill_blank_string_for_timeslot($toMinute);
    			$data['when_timeslot'] = $fromHour.':'.$fromMinute.'~'.$toHour.':'.$toMinute;
    		}
    		break;
    	case 'conditionwhenweekfactors':
    		$data['type'] = $node->type;
    		$week = array();
    		foreach($node->field_week['und'] as $weekItem){
    			$weekTerm = taxonomy_term_load($weekItem['tid']);
    			$week[] = $weekTerm->name;
    		}
    		$data['when_week'] = $week;
    		break;
    	case 'conditionwherecountryfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_ref_country_code['und'][0])){
    			$countryNode = node_load($node->field_ref_country_code['und'][0]['nid']);
	    		$data['where_countrycode'] = $countryNode->field_country_code['und'][0]['safe_value'];
    		}
    		break;
    	case 'conditionwherenetworkfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_ref_newtork_type['und'][0])){
    			$networkTerm = taxonomy_term_load($node->field_ref_newtork_type['und'][0]['tid']);
	    		$data['where_network'] = $networkTerm->name;
    		}
    		break;
    	case 'conditionwherecustomfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_rating_factor['und'][0])){
    			$ratingFactorTerm = taxonomy_term_load($node->field_rating_factor['und'][0]['tid']);
	    		$data['where_custom_rating_factor'] = $ratingFactorTerm->name;
    		}
    		if(isset($node->field_rating_operation['und'][0])){
    			$ratingOperationTerm = taxonomy_term_load($node->field_rating_operation['und'][0]['tid']);
	    		$data['where_custom_rating_op'] = $ratingOperationTerm->name;
    		}
    		if(isset($node->field_value['und'][0])){
    			$data['where_custom_rating_value'] = $node->field_value['und'][0]['safe_value'];
    		}
    		break;
    	case 'conditionwhonumberfactors':
    		$data['type'] = $node->type;
    		$phoneNumbers = array();
    		foreach($node->field_phone_number['und'] as $phoneNumber){
    			$phoneNumbers[] = $phoneNumber['safe_value'];
    		}
    		$data['who_number'] = $phoneNumbers;
    		break;
    	case 'conditionwhoprefixfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_prefix['und'][0])){
    			$data['who_prefix'] = $node->field_prefix['und'][0]['safe_value'];
    		}
    		break;
    	case 'conditionwhocustomfactors':
    		$data['type'] = $node->type;
    		if(isset($node->field_rating_factor['und'][0])){
    			$ratingFactorTerm = taxonomy_term_load($node->field_rating_factor['und'][0]['tid']);
    			$data['who_custom_rating_factor'] = $ratingFactorTerm->name;
    		}
    		if(isset($node->field_rating_operation['und'][0])){
	    		$ratingOperationTerm = taxonomy_term_load($node->field_rating_operation['und'][0]['tid']);
	    		$data['who_custom_rating_op'] = $ratingOperationTerm->name;
    		}
    		if(isset($node->field_value['und'][0])){
    			$data['who_custom_rating_value'] = $node->field_value['und'][0]['safe_value'];
    		}
    		break;
    	case 'actionpricediscountfactors':
    		$thresholdUnitTerm = taxonomy_term_load($node->field_threshold_unit['und'][0]['tid']);
    		
			$priceCollectionView = views_get_view('list_price_collection_items');
			$priceCollectionView->set_arguments(array(0=>$node->nid));
			$priceCollectionView->execute();
			$prices = $priceCollectionView->result;
			
			foreach($prices as $priceItem){
				foreach($priceItem->field_field_charge_collection[0]['rendered']['#rows'] as $chargeCollectionItem){
					$data[] = array(
						'type' => $node->type,
						'range_unit' => $priceItem->field_field_range_units[0]['raw']['taxonomy_term']->name,
						'price_unit' => $priceItem->field_field_price_units[0]['raw']['taxonomy_term']->name,
						'uom_unit' => $priceItem->field_field_uom_units[0]['raw']['taxonomy_term']->name,
					
						'range_start' => $chargeCollectionItem['data'][0]['data']['#items'][0]['value'],
						'range_end' => $chargeCollectionItem['data'][1]['data']['#items'][0]['value'],
						'price_amount' => $chargeCollectionItem['data'][2]['data']['#items'][0]['value'],
						'uom_amount' => $chargeCollectionItem['data'][3]['data']['#items'][0]['value'],			

						'threshold' => $node->field_threshold['und'][0]['value'],
						'threshold_unit' => $thresholdUnitTerm->name,
					);
				}
			}
    		break;
    	case 'actionpriceallowancefactors':
    		$data['type'] = $node->type;
    		$priceUnitTerm = taxonomy_term_load($node->field_price_units['und'][0]['tid']);
    		$data['price_unit'] = $priceUnitTerm->name;    		
    		$data['price_amount'] = $node->field_price_amount['und'][0]['value'];
    		$data['allow_start'] = $node->field_allow_start['und'][0]['value'];
    		$allowIntervalUnitTerm = taxonomy_term_load($node->field_allow_interval_unit['und'][0]['tid']);
    		$data['allow_interval_unit'] = $allowIntervalUnitTerm->name;
    		$data['allow_interval'] = $node->field_allow_interval['und'][0]['value'];
    		$data['threshold'] = $node->field_threshold['und'][0]['value'];
    		$thresholdUnitTerm = taxonomy_term_load($node->field_threshold_unit['und'][0]['tid']);
    		$data['threshold_unit'] = $thresholdUnitTerm->name;
    		$treeNodeCounter = node_load($node->field_ref_counter['und'][0]['nid']);
    		$realCounterNode = node_load($treeNodeCounter->field_ref_counter['und'][0]['nid']);
    		$data['target_counter_code'] = $realCounterNode->field_code['und'][0]['value'];
    		break;
    	default:
    		$data['type'] = $node->type;	    		
    		break;
    }
    
	return $data;
}

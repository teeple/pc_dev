<?php
function _create_export_meta_data_by_content_type($node=NULL,&$item,$metaType=NULL){
	$stringMaxLength = 60;
	
	if($node != NULL){
		switch($node->type){
			case 'defaulttreenode':
				$term = taxonomy_term_load($node->field_ref_tree_node_tid['und'][0]['value']);	
	    		$relType = $term->description;
	    		switch($relType){
	    			case 'dtn_mobile_usage':
	    				$item['meta'] = array(
	    					array('name' => 'numberingplan_domestic_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
	    					array('name' => 'numberingplan_idd_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
	    					array('name' => 'carrier_domestic_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
	    					array('name' => 'carrier_idd_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
	    					array('name' => 'ratinggroup','condition' => true, 'type' => 'integer'),
	    					array('name' => 'timetable_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
	    					array('name' => 'timetablefactor_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength), 
	    				);
	    				break;   
	    				default:
				    		if($term->name === 'Number Special'){
				    			$item['meta'] = array(
				    				array('name' => 'number_special_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
				    			);
				    		}
	    				break;	    					
	    		}
				break;		
		}
	}else if($metaType != NULL){
		switch($metaType){
			case 'numberspecial':
				$item['meta'] = array(
					array('name' => 'number_special_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ns_factor_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'ns_factor_ratinggroup','condition' => false, 'type' => 'integer'),
					array('name' => 'ns_rate_ratinggroup','condition' => true, 'type' => 'integer', 'default_op' => 'in'),
					array('name' => 'range_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength),
					array('name' => 'price_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength),
					array('name' => 'uom_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength),
				);
				break;
			case 'domestic_npa':
				$item['meta'] = array(
					array('name' => 'service_type','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'carrier_domestic_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'npa_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'npa_toc','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),	
				);
				break;
			case 'domestic_area':
				$item['meta'] = array(
					array('name' => 'area_toc','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'area_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'area_code','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),
				);
				break;
			case 'domestic_ratinggroup':
				$item['meta'] = array(
					array('name' => 'carrier_domestic_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'same_zone','condition' => true, 'type' => 'boolean'),
					array('name' => 'from_area_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'to_area_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ratinggroup','condition' => false, 'type' => 'integer'),
				);
				break;
			case 'idd_exit':
				$item['meta'] = array(
					array('name' => 'service_type','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'carrier_domestic_name','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'exit_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'exit_toc','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),
				);
				break;
			case 'idd_country':
				$item['meta'] = array(
					array('name' => 'country_toc','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'country_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'country_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'country_new_toc','condition' => false, 'type' => 'string','maxlength' => $stringMaxLength),
				);
				break;
			case 'idd_ratinggroup':
				$item['meta'] = array(
					array('name' => 'ratinggroup_toc','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ratinggroup_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'area_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ratinggroup','condition' => false, 'type' => 'integer'),
				);
				break;
			case 'idd_ratinggroup':
				$item['meta'] = array(
					array('name' => 'ratinggroup_toc','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ratinggroup_prefix','condition' => true, 'type' => 'string','default_op' => 'startswith', 'maxlength' => $stringMaxLength),
					array('name' => 'area_code','condition' => true, 'type' => 'string','maxlength' => $stringMaxLength),
					array('name' => 'ratinggroup','condition' => false, 'type' => 'integer'),
				);
				break;			
			case 'product_custom':
				$firstArray = array_slice($item, 0, 1);
				$lastArray = array_slice($item,1);
				$addingArray = array();
				
				//condition what
				$keyPath = array_searchRecursive_get_key_path('conditionwhatqos',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'what_qos_level','condition' => true, 'type' => 'integer', 'default_op' => 'in');
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhaturlgroupfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'what_url','condition' => true, 'type' => 'string', 'default_op' => 'in','maxlength' => $stringMaxLength);
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhatcustomfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'what_custom_rating_factor','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_op','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_value','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
				}
				
				//condition when
				$keyPath = array_searchRecursive_get_key_path('conditionwhendayfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'when_day','condition' => true, 'type' => 'date');
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhendurationfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'when_duration','condition' => true, 'type' => 'duration', 'default_op' => 'between');
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhenholidayfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'when_holiday','condition' => true, 'type' => 'boolean');
				}				
				$keyPath = array_searchRecursive_get_key_path('conditionwhentimeslotfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'when_timeslot','condition' => true, 'type' => 'timeslot', 'default_op' => 'between');
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhenweekfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'when_week','condition' => true, 'type' => 'day_of_week', 'default_op' => 'in');
				}	 
				
				//conditino where
				$keyPath = array_searchRecursive_get_key_path('conditionwherecountryfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'where_countrycode','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
				}   	
	    		$keyPath = array_searchRecursive_get_key_path('conditionwherenetworkfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'where_network','condition' => true, 'type' => 'string', 'default_op' => 'in', 'maxlength' => $stringMaxLength);
				} 
	    		$keyPath = array_searchRecursive_get_key_path('conditionwherecustomfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'what_custom_rating_factor','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_op','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_value','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
				} 
				
				//condition who
				$keyPath = array_searchRecursive_get_key_path('conditionwhonumberfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'who_number','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhoprefixfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'who_prefix','condition' => true, 'type' => 'string', 'default_op' => 'startswith', 'maxlength' => $stringMaxLength);
				}
				$keyPath = array_searchRecursive_get_key_path('conditionwhocustomfactors',$item,true);
				if(!empty($keyPath)){
					$addingArray['meta'][] = array('name' => 'what_custom_rating_factor','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_op','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					$addingArray['meta'][] = array('name' => 'what_custom_rating_value','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
				}
				
				//actionpricechargefactors
				$keyPath = array_searchRecursive_get_key_path('actionpricechargefactors',$item,true);
				if(!empty($keyPath)){
					$tempKeyPath = array_searchRecursive_get_key_path('range_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);	
					}
					$tempKeyPath = array_searchRecursive_get_key_path('price_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_unit','condition' => false, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('uom_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'uom_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('range_start',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_start','condition' => true, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('range_end',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_end','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('price_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_amount','condition' => false, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('uom_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'uom_amount','condition' => false, 'type' => 'integer');
					}
				}
				
				//actionpricediscountfactors
				$keyPath = array_searchRecursive_get_key_path('actionpricediscountfactors',$item,true);
				if(!empty($keyPath)){
					$tempKeyPath = array_searchRecursive_get_key_path('range_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);	
					}
					$tempKeyPath = array_searchRecursive_get_key_path('price_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_unit','condition' => false, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('uom_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'uom_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('range_start',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_start','condition' => true, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('range_end',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_end','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('price_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_amount','condition' => false, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('uom_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'uom_amount','condition' => false, 'type' => 'integer');
					}
					
					$tempKeyPath = array_searchRecursive_get_key_path('threshold',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'threshold','condition' => true, 'type' => 'integer', 'default_op' => '<=');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('threshold_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'threshold_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
				}
				
				//actionpriceallowancefactors
				$keyPath = array_searchRecursive_get_key_path('actionpriceallowancefactors',$item,true);
				if(!empty($keyPath)){
					$tempKeyPath = array_searchRecursive_get_key_path('price_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_unit','condition' => false, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}					
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_amount','condition' => false, 'type' => 'integer');
					}	
					$tempKeyPath = array_searchRecursive_get_key_path('threshold',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'threshold','condition' => true, 'type' => 'integer', 'default_op' => '<=');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('threshold_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'threshold_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('allow_start',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'allow_start','condition' => true, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('allow_interval',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'allow_interval','condition' => true, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('allow_interval_unit',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'allow_interval_unit','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('target_counter',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'target_counter_code','condition' => false, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
				}
			
				//dtn_mobile_voice
				$keyPath = array_searchRecursive_get_key_path('dtn_mobile_voice',$item,true);
				if(!empty($keyPath)){
					$tempKeyPath = array_searchRecursive_get_key_path('range_start',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_start','condition' => true, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('range_end',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'range_end','condition' => true, 'type' => 'string', 'maxlength' => $stringMaxLength);
					}
					$tempKeyPath = array_searchRecursive_get_key_path('price_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'price_amount','condition' => false, 'type' => 'integer');
					}
					$tempKeyPath = array_searchRecursive_get_key_path('uom_amount',$addingArray,true);
					if(empty($tempKeyPath)){
						$addingArray['meta'][] = array('name' => 'uom_amount','condition' => false, 'type' => 'integer');
					}
				}
				
	    		$item = array_merge($firstArray,$addingArray,$lastArray);
	    		break;
	    		
		}
	}
}

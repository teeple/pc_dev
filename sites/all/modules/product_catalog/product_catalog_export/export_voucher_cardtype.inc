<?php

function _array_voucher_cardtype($exportItemNids = NULL, $isExternalAPI = FALSE) {
    $jsonData = array();
    $jsonData_common = array();

    //fetch data
    if (!empty($exportItemNids) && count($exportItemNids) > 1) {
        $exportItemNids = join('+', $exportItemNids);
    }

    if (is_array($exportItemNids) && empty($exportItemNids)) {
        $exportItemNids = NULL;
    }

    $args = array();
    $args = array('0' => $exportItemNids);

    $view = views_get_view('list_vouchercardtype_export');
    $view -> set_display('panel_pane_1');
    $view -> set_arguments($args);
    $view -> execute();

    $viewResult = $view -> result;
    $jsonRecord_vouchers = array();
	
	foreach ($viewResult as $record) {
	
        $jsonRecord['id'] = isset($record -> field_field_voucher_id) ? $record -> field_field_voucher_id[0]['rendered']['#markup'] : null;
        $jsonRecord['title'] = isset($record -> node_title) ? $record -> node_title : null;
        $jsonRecord['price'] = !empty($record -> field_field_price_amount_float) ? $record -> field_field_price_amount_float[0]['raw']['value'] : null;
        $jsonRecord['voucher_type'] = _add_commoncode($record -> field_field_ref_voucher_type);
        $jsonRecord['description'] = !empty($record -> field_field_description_long) ? $record -> field_field_description_long[0]['rendered']['#markup'] : null;

	    $jsonRecord['service_operator'] = _add_commoncode($record -> field_field_service_operator);
        $jsonRecord['use_area'] = !empty($record -> field_field_use_area) ? $record -> field_field_use_area[0]['rendered']['#markup'] : null;
        $jsonRecord['number_grade'] = !empty($record->field_field_number_grade)? _get_common_code($record -> field_field_number_grade[0]['raw']['taxonomy_term']) : null;
        $jsonRecord['charge'] = _voucher_cardtype_charge( $record->nid);
        
        $node = node_load($record->nid);
        
        $validStart = isset($record -> field_field_valid_date_ymd_w_enddate[0]['raw']['value']) ? $record -> field_field_valid_date_ymd_w_enddate[0]['raw']['value'] : '0001-01-01 00:00:00';
        $validEnd = isset($record -> field_field_valid_date_ymd_w_enddate[0]['raw']['value2']) ? $record -> field_field_valid_date_ymd_w_enddate[0]['raw']['value2'] : '9999-12-31 23:59:59';
        
        if (!empty($validEnd)) {
            $tempArr = explode(' ', $validEnd);
            $validEnd = $tempArr[0] . ' 23:59:59';

        } else {
            $validEnd = '9999-12-31 23:59:59';
        }

        $validFor = $validStart . ' ~ ' . $validEnd;
        $jsonRecord['valid_for'] = $validFor;

        if ($record -> field_field_ref_voucher_type[0]['rendered']['#title'] == 'Discount') {
            if ( isset($record->field_field_ref_product_for_disvoucher[0]['raw']['nid'])) {
				$mappingProduct = node_load($record -> field_field_ref_product_for_disvoucher[0]['raw']['nid']);

            //dsm($mappingProduct, 'mappingProduct');
            // $jsonRecord['mapping_product'] = !empty($record->field_field_product_id) ? $record->field_field_product_id[0]['raw']['value']: null;
				$jsonRecord['mapping_product'] = !empty($mappingProduct -> field_product_id) ? $mappingProduct -> field_product_id['und'][0]['value'] : null;
			}

            $saleTypeArr = array();
            if (!empty($record -> field_field_sale_type)) {
                foreach ($record->field_field_sale_type as $saleType) {
                    $saleTypeArr[] = $saleType['rendered']['#title'];
                }
                $jsonRecord['sale_type'] = $saleTypeArr;

            } else {
                $jsonRecord['sale_type'] = null;
            }

            $listProduct = views_get_view_result('list_treenodeproductfordisvoucher', 'panel_pane_1', $record -> nid);
            $ret_product = array();
            foreach ($listProduct as $product) {
                $originalProductNode = node_load($product -> node_field_data_field_ref_product_nid);

                if (!empty($originalProductNode)) {
                    $tmpProduct['product_id'] = $originalProductNode -> field_product_id['und'][0]['safe_value'];
                    $tmpProduct['product_name'] = $product -> node_title;
                    $ret_product[] = $tmpProduct;
                }
            }

        } else {
            //default recharge amount
            $rechargeAmountList = array();
            $amountResult = views_get_view_result('list_counter_for_vouchercardtype', 'panel_pane_4', $record -> nid);
            foreach($amountResult as $amount){
                if(isset($rechargeAmountList[$amount->taxonomy_term_data_field_data_field_service_domain_tid])){
                    $rechargeAmountList[$amount->taxonomy_term_data_field_data_field_service_domain_tid] 
                        += $amount->field_field_amount[0]['raw']['value'];
                }else{
                    $rechargeAmountList[$amount->taxonomy_term_data_field_data_field_service_domain_tid] 
                        = $amount->field_field_amount[0]['raw']['value'];
                }
            }
            foreach($rechargeAmountList as $key=>$value){
                $serviceDomainTerm = taxonomy_term_load($key);    
                $jsonRecord['service_domain'][] = array(
                    'service_domain' => _get_common_code($serviceDomainTerm),
                    'recharge_amount' => strval($value)
                );
            }
        
            $listProduct = views_get_view_result('list_treenodeproductforvoucher', 'panel_pane_1', $record -> nid);
            $ret_product = array();
            foreach ($listProduct as $product) {
                $originalProductNode = node_load($product -> node_field_data_field_ref_product_nid);

                if (!empty($originalProductNode)) {
                    $tmpProduct['product_id'] = $originalProductNode -> field_product_id['und'][0]['safe_value'];
                    $tmpProduct['product_name'] = $product -> node_title;
                    $tmpProduct['valid_period'] = !empty($product -> field_field_valid_period) ? $product -> field_field_valid_period[0]['raw']['value'] : null;
                    $tmpProduct['active_period'] = !empty($product -> field_field_active_period) ? $product -> field_field_active_period[0]['raw']['value'] : null;
                    $tmpProduct['grace_period'] = !empty($product -> field_field_grace_period) ? $product -> field_field_grace_period[0]['raw']['value'] : null;
                    
                    //amount for product
                    $rechargeAmount = 0;
                    $amountResult = views_get_view_result('list_treenodecounterforvoucherprd', 'panel_pane_3', $product -> nid);
                    foreach($amountResult as $amount){
                        $rechargeAmount += $amount->field_field_amount[0]['raw']['value'];
                    }
                    $tmpProduct['recharge_amount'] = strval($rechargeAmount);
                    
                    $ret_product[] = $tmpProduct;
                }
            }

        }
        
        if (empty($ret_product)) {
            $jsonRecord['products'] = null;

        } else {
            $jsonRecord['products'] = $ret_product;
        }
        $jsonRecord_vouchers[] = $jsonRecord;
        $voucherIds[] = $jsonRecord['id'];
    }
	
	if (!empty($exportItemNids)) {
        $jsonData_common['resources'] = array_values($voucherIds);
    } else {
        $jsonData_common['resources'] = array();
    }
		
    $jsonData['ifvalues'] = $jsonData_common;
    $jsonData['vouchers'] = $jsonRecord_vouchers;

    return $jsonData;
}

function _json_voucher_cardtype($exportItemNids = NULL) {
    $retArray = array();
    $jsonData = _array_voucher_cardtype($exportItemNids);

    $retArray = $jsonData;
    $retArray['rating_rules'] = array();

    $arr = array();
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_vouchercardtype", $exportItemNids);
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_counter_for_vouchercardtype", $exportItemNids);
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_loyaltypointfactors", $exportItemNids);
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_voucher_product", $exportItemNids);
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "list_treenodecounterforvoucherprd", $exportItemNids);
    $arr[] = rating_rules_export_by_content_type_and_item_name("rating_rule_export", "rating_loyalty_notification", $exportItemNids);

    foreach ($arr as $a) {
        foreach ($a as $t => $v) {
            $retArray['rating_rules'][$t] = $v;
        }
    }

    return json_encode($retArray);
}

function _voucher_cardtype_charge( $nid)
{
	$charge = array();

	$nids = ocs_get_nids_by_cond('treenodecounterforvoucher', array(
		array( 'field_ref_vouchercardtype', 'nid', $nid),
	));
	if ( ! empty( $nids)) {
		foreach( $nids as $nid) {
			$c = node_load( $nid);
			if ( isset($c->field_amount['und']) && $c->field_amount['und'][0]['value'] > 0) {
				$t = taxonomy_term_load($c->field_counter_sub_unit_type['und'][0]['tid']);
				if ( $t->name == 'Money') {
					$charge[] = $c->field_amount['und'][0]['value'] . ' MNT';
				}
				else {
					$counter = node_load( $c->field_ref_counter['und'][0]['nid']);
					$charge[] = $c->field_amount['und'][0]['value'] . ' ' . $counter->title;
				}
			}
		}
	}

	return implode( ', ', $charge);
}

<?php

function _product_group_for_export($exportItemNids = NULL, $isExternalAPI = FALSE) {
    $retData = array();
    $retDataTmp = array();
    $productNids = array();

    if (count($exportItemNids) == 1) {
        $exportItemNids = array($exportItemNids);
    }
    
    foreach ($exportItemNids as $nid) {
        $node = node_load($nid);
        
        $productGroup = array();
        $retDataTmp[] = $product;
    }
    
    if(!$isExternalAPI) {
	    if (!empty($productNids)) {
	        $retData['ifvalues']['resources'] = array_values($productNids);
	    } else {
	        $retData['ifvalues']['resources'] = '';
	    }
	  }
	  
    $retData['product_groups'] = $retDataTmp;

    return $retData;
}

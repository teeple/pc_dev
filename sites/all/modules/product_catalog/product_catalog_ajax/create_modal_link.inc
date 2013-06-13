<?php 
function _create_modal_mapping_link($contentType,$title,$params){
  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();
  
  $add_url = '/product_catalog_ajax/nojs/add_modal/'.$contentType;
  foreach($params as $param){
    $add_url .= '/'.$param;
  }
  
  $add_class_2 = 'ctools-use-modal ctools-modal-add-item-modal-style';
  
  $link_string = '<div><a href="'.$add_url.'" class='.$add_class_2.'>'.$title.'</a></div>';
  
  return $link_string;
}

function _create_modal_upload_link($contentType,$params) {
	/*
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	$upload_url = '/product_catalog_ajax/nojs/upload_modal/'.$contentType;
	foreach($params as $param){
		$upload_url .= '/'.$param;
	}
	*/
	switch($contentType) {
		case 'locationfactor':
			$upload_url = '/import/location_cellid_importer#quickset-qtabs_common_data=7';
			break;
		case 'devicemodel':
			$upload_url = '/import/imei_prefix_importer#quickset-qtabs_common_data=5';
			break;
			
	}
	
	$add_class_1 = 'add-link-in-rightpane';
	// $add_class_2 = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div class='.$add_class_1.'><a href="'.$upload_url.'" >Upload</a></div>';
	
	return $link_string;
}

function _create_modal_add_link($contentType,$params){
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	$add_url = '/product_catalog_ajax/nojs/add_modal/'.$contentType;
	foreach($params as $param){
		$add_url .= '/'.$param;
	}
	
	$add_class_1 = 'add-link-in-rightpane';
	$add_class_2 = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div class='.$add_class_1.'><a href="'.$add_url.'" class='.$add_class_2.'>Add</a></div>';
	
	return $link_string;	
}

function _create_modal_select_link($contentType, $params) {
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	$select_url = '/product_catalog_ajax/nojs/select_modal/'.$contentType;
	foreach($params as $param){
		$select_url .= '/'.$param;
	}
	
	$add_class_1 = 'add-link-in-rightpane';
	$add_class_2 = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div class='.$add_class_1.'><a href="'.$select_url.'" class='.$add_class_2.'>Add</a></div>';
	
	return $link_string;
}

function _create_modal_edit_link($contentType,$params){ 
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
		
	$edit_url = '/product_catalog_ajax/nojs/edit_modal/'.$contentType;
	foreach($params as $param){
		$edit_url .= '/'.$param;
	}
	
	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div><a href="'.$edit_url.'" class='.$link_class.'>edit</a></div>';
	echo $link_string;	
}

function _create_modal_delete_link($contentType,$params){ 
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
		
	$delete_url = 'product_catalog_ajax/delete_from_view';
	foreach($params as $param){
		$delete_url .= '/'.$param;
	}
	
	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	$delete_output = l(t('delete'), $delete_url, array('attributes' => array('class' => array('use-ajax'))));
	
	$link_string = '<div>'.$delete_output.'</div>';
	echo $link_string;	
}

function _create_modal_edit_delete_link($contentType,$params){ 
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
		
	$edit_url = '/product_catalog_ajax/nojs/edit_modal/'.$contentType;
	foreach($params as $param){
		$edit_url .= '/'.$param;
	}
	
	$delete_url = 'product_catalog_ajax/delete_from_view';
	foreach($params as $param){
		$delete_url .= '/'.$param;
	}
	
	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$delete_output = l(t('delete'), $delete_url, array('attributes' => array('class' => array('use-ajax'))));
		
	$link_string = '<div><a href="'.$edit_url.'" class='.$link_class.'>edit</a>&nbsp;'.$delete_output.'</div>';
	echo $link_string;
}

function _create_modal_form_view_link($linkTitle,$formName,$params){
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	$url = '/product_catalog_ajax/view_modal/'.$formName;
	foreach($params as $param){
		$url .= '/'.$param;
	}
	
	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div><a href="'.$url.'" class='.$link_class.'>'.$linkTitle.'</a></div>';
	echo $link_string;	
}

function _create_modal_form_view_link_by_page($linkTitle,$contentType, $params){
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	$url = '/product_catalog_ajax/modal_view_link/'.$contentType;
	foreach($params as $param){
		$url .= '/'.$param;
	}
	
	$link_class = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div><a href="'.$url.'" class='.$link_class.'>'.$linkTitle.'</a></div>';
	echo $link_string;
}


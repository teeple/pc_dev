<?php 

function _create_modal_add_link($contentType,$params){
	ctools_include('ajax');
	ctools_include('modal');
	ctools_modal_add_js();
	
	error_log('here');
	$add_url = '/product_catalog_ajax/nojs/add_modal/'.$contentType;
	foreach($params as $param){
		$add_url .= '/'.$param;
	}
	
	$add_class_1 = 'add-link-in-rightpane';
	$add_class_2 = 'ctools-use-modal ctools-modal-add-item-modal-style';
	
	$link_string = '<div class='.$add_class_1.'><a href="'.$add_url.'" class='.$add_class_2.'>Add</a>';
	
	return $link_string;	
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
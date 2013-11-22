<?php

function product_catalog_form_theme($existing, $type, $theme, $path)
{
	return array(
    'product_catalog_form_offering_simple_nonusage' => array(
        'file' => 'product_catalog_form.inc',
        'render element' => 'form',
		),
		'product_catalog_form_product_priority' => array(
	    'render element' => 'element'
	  )
	);
}

function theme_product_catalog_form_product_priority($vars) {
	$element = $vars['element'];
  //drupal_add_tabledrag('product_priority_form', 'order', 'sibling', 'rank-weight'); // needed for table dragging
  drupal_add_tabledrag('product_priority_form', 'order', 'sibling', 'rank-weight', NULL, NULL, FALSE);
  $header = array(
    'name' => t('Name'), 
    'product_type' => t('Product Type'),
    'billing_type' => t('Billing Type'),
    'weight' => t('Priority'),
  );
  
  $rows = array();
  foreach (element_children($element) as $key) {
    $row = array();
    
    $row['data'] = array();
    foreach ($header as $fieldname => $title) {
      $row['data'][] = drupal_render($element[$key][$fieldname]);
      $row['class'] = array('draggable'); // needed for table dragging
    }
    $rows[] = $row;
  }
  
  return theme('table', array(
    'header' => $header, 
    'rows' => $rows,
    'attributes' => array('id' => 'product_priority_form'), // needed for table dragging
  ));
}
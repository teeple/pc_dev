<?php

function ocs_migrate_fce_carrier($form, &$form_state)
{
    db_set_active('fce');

    $query = db_select( 'carrier', 'c');
    $result = $query
        ->fields( 'c', array( 'ruleName', 'prefix'))
        ->execute();

    $output = '<thead><tr><td>Carrier</td><td>Prefix</td></tr></thead>';
    $output .= '<tbody>';
    $records = array();        
    while( $record = $result->fetchAssoc()) {
    	$records[] = array( 
    		'carrier' => $record['ruleName'],
			'prefix' => $record['prefix']);
		$output .= '<tr><td>'.$record['ruleName'].'</td><td>'.$record['prefix'].'</td></tr>';
    }
    $output .= '</tbody>';
    
    $form['#carrier'] = $records;
    
    db_set_active( 'default');
        

    $form['carrier'] = array(
		'#type' => 'fieldset',
		'#title' => 'Carrier',
		'#collapsible' => TRUE,
	);
	
	// $form['carrier']['remove'] = array(
		// '#type' => 'radios',
		// '#title' => 'remove all existing data',
		// '#options' => array( 'No', 'Yes'),
		// '#default_value' => '1'
	// );
// 	
	$form['carrier']['data'] = array(
		'#type' => 'markup',
		'#markup' => '<table>'.$output.'</table>'
	);
	
	$form['actions'] = array('#type' => 'actions');
	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);

	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);

	return $form;
}

function ocs_migrate_fce_carrier_submit( $form, &$form_state)
{
	$values = $form_state['values'];
	if ( $values['op'] == 'Save') {
		dpm( $values, 'values');
		
		// if ( $values['remove'] == '1') {
			// dpm( 'remove all mobile carrier instances.');
// 			
			// // remove all existing values
	       	// $items = entity_load( 'node', FALSE, array( 'type' => 'carrier_mobile'));
	       	// foreach( array_keys( $items) as $nid) {
				// node_delete( $nid);	       		
	       	// }
        // }
        
        // add entities
        foreach( $form['#carrier'] as $carrier) {
	        $node = ocs_admin_get_new_node('carrier_mobile');
    		$node->title = $carrier['carrier'];
    		$prefix = entity_create('field_collection_item', array('field_name' => 'field_prefix_collection'));
    		$prefix->setHostEntity('node', $node);

		    $prefix->field_prefix = array(
        		'und' => array(
            		'0' => array(
                		'value' => $carrier['prefix'],
		            )
        		)
    		);

		    $prefix->save();
		    node_save( $node);
        }
	}
}


function ocs_migrate_fce_area($form, &$form_state)
{
    db_set_active('fce');

    $query = db_select( 'area', 'a');
    $result = $query
        ->fields( 'a', array( 'carrier', 'ruleName' , 'second_prefix', 'region_code', 'rating_group' ))
		->orderBy('carrier', 'DESC')
        ->execute();
		
    $output = '<thead><tr><td>Carrier</td><td>Area Name</td><td>Prefix</td><td>Region Code</td><td>Rating Group</td></tr></thead>';
    $output .= '<tbody>';
    $records = array();        
    while( $record = $result->fetchAssoc()) {
    	$records[] = $record;
    	
    	$output .= '<tr>';
    	foreach( array_keys( $record) as $key) {
    		$output .= '<td>'.$record[$key].'</td>';
    	}
    	$output .= '</tr>';
    }
    $output .= '</tbody>';
    
    $form['#area'] = $records;
    
    db_set_active( 'default');
    
    $form['actions'] = array('#type' => 'actions');
	    
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
 
	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);
        
    $form['carrier'] = array(
		'#type' => 'fieldset',
		'#title' => 'Area',
		'#collapsible' => TRUE,
	);
	
	// $form['carrier']['remove'] = array(
		// '#type' => 'radios',
		// '#title' => 'remove all existing data',
		// '#options' => array( 'No', 'Yes'),
		// '#default_value' => '1',
	// );
	
	$form['carrier']['data'] = array(
		'#type' => 'markup',
		'#markup' => '<table>'.$output.'</table>'
	);
	

	return $form;
}

function ocs_migrate_fce_area_submit( $form, &$form_state)
{
	$values = $form_state['values'];
	if ( $values['op'] == 'Save') {
		dpm( $values, 'values');
		
		// if ( $values['remove'] == '1') {
			// dpm( 'remove all area instances.');
// 			
			// // remove all existing values
	       	// $items = entity_load( 'node', FALSE, array( 'type' => 'area_code'));
	       	// foreach( array_keys( $items) as $nid) {
	       		// dpm( 'node '.$nid.' deleted.');
				// node_delete( $nid);	       		
	       	// }
        // }
        
        // add entities
        foreach( $form['#area'] as $r) {
	        $node = ocs_admin_get_new_node('area_code');
    		$node->title = $r['ruleName'];
    		$node->field_prefix['und'][0]['value'] = $r['second_prefix'];
    		$node->field_area_code['und'][0]['value'] = $r['region_code'];
    		
    		$items = entity_load( 'node', FALSE, array( 'type' => 'carrier_mobile', 'title' => $r['carrier']));
    		if ( count($items) == 1) {
    			$nids = array_keys($items);
    			$node->field_ref_carrier_mobile['und'][0]['nid'] = $nids[0];
    		}
			else {
				dpm( 'Carrier not found: '.$r['carrier']);
			}
    		node_save( $node);
        }
	}
}


function ocs_migrate_fce_timetable($form, &$form_state)
{
    db_set_active('fce');

    $query = db_select( 'voice_time_table', 'a');
    $result = $query
        ->fields( 'a', array( 'carrier', 'ruleName' , 'holiday' , 'week' , 'timeLower' , 'timeUpper'))
        ->orderBy( 'carrier')
        ->orderBy( 'ruleName')
        ->execute();
		
    $output = '<thead><tr><td>Carrier</td><td>Name</td><td>Holiday</td><td>Week</td><td>From</td><td>To</td></tr></thead>';
    $output .= '<tbody>';
    $records = array();        
    while( $record = $result->fetchAssoc()) {
    	$records[] = $record;
    	
    	$output .= '<tr>';
    	foreach( array_keys( $record) as $key) {
    		$output .= '<td>'.$record[$key].'</td>';
    	}
    	$output .= '</tr>';
    }
    $output .= '</tbody>';
    
    $form['#timetable'] = $records;
    
    db_set_active( 'default');
    
    $form['actions'] = array('#type' => 'actions');
	    
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
 
	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);
        
    $form['carrier'] = array(
		'#type' => 'fieldset',
		'#title' => 'Area',
		'#collapsible' => TRUE,
	);
	
	// $form['carrier']['remove'] = array(
		// '#type' => 'radios',
		// '#title' => 'remove all existing data',
		// '#options' => array( 'No', 'Yes'),
		// '#default_value' => '1',
	// );
	
	$form['carrier']['data'] = array(
		'#type' => 'markup',
		'#markup' => '<table>'.$output.'</table>'
	);
	

	return $form;
}

function ocs_migrate_fce_timetable_submit( $form, &$form_state)
{
	$values = $form_state['values'];
	if ( $values['op'] == 'Save') {
		dpm( $values, 'values');
		
		// if ( $values['remove'] == '1') {
			// dpm( 'remove all area instances.');
// 			
			// // remove all existing values
	       	// $items = entity_load( 'node', FALSE, array( 'type' => 'area_code'));
	       	// foreach( array_keys( $items) as $nid) {
	       		// dpm( 'node '.$nid.' deleted.');
				// node_delete( $nid);	       		
	       	// }
        // }
        
        // add entities
		// manual migration
	}
}



function ocs_migrate_fce_voiceplan($form, &$form_state, $category='A')
{
	// $category = isset( $form_state['values']['category']) ? $form_state['values']['category'] : 'A';
	$carrier = ocs_load_all_carrier();
    
    // dpm( $category, 'category:');
    // dpm( $form_state['values'], 'values');
    
    db_set_active('fce');

    $fields = array(  'user_category', 'called_carrier', 'ruleName','isDDD' , 'rating_group'  , 
        	'time_id' , 'is_video' , 'second_prefix');
    $query = db_select( 'voice_tariff_decision', 'v');
//    $query->join('area', 'a', 'a.carrier = v.called_carrier');
    $result =$query 
        ->fields( 'v', $fields)
//        ->fields( 'a', array( 'ruleName' , 'second_prefix', 'region_code', 'rating_group'))
		// ->condition('v.user_category', array( $category, NULL), 'IN')
		->where( 'user_category is null or user_category = :category', array( ':category' => $category))
        ->orderBy('v.called_carrier')
		->orderBy('v.user_category')
        ->orderBy('v.ruleName')
        ->execute();
		
    $output = '<thead><tr>';
    foreach( $fields as $field) {
    	$output .= '<td>'.$field.'</td>';
    }
    $output .= '<td>Region Flag</td>';
    $output .= '<td>Rating Groups</td>';
    $output .= '</tr></thead>';
    $output .= '<tbody>';
    $records = array();        
    while( $record = $result->fetchAssoc()) {
    	
    	$output .= '<tr>';
    	foreach( array_keys( $record) as $key) {
    		$output .= '<td>'.$record[$key].'</td>';
    	}
    	$c = $record['called_carrier'];
    	$output .= '<td>'.$carrier[$c]['regionFlag'].'</td>';
    	$output .= '<td>'.implode( ',', array_keys( $carrier[$c]['rating_group'])).'</td>';
    	$output .= '</tr>';

    	$record['regionFlag'] = $carrier[$c]['regionFlag'];    	
    	$records[] = $record;
    }
    $output .= '</tbody>';
    
    $form['#rule'] = $records;
    $form['#carrier'] = $carrier;
    
    dpm( $records, 'tariff');
    dpm( $carrier, 'carrier');
    
    db_set_active( 'default');
    
    $form['category'] = array(
    	'#type' => 'select',
    	'#title' => 'Select User Category to migrate',
    	'#options' => drupal_map_assoc( array('A',
'B',
'C',
'D',
'E',
'F',
'G',
'I',
'J',
'K',
'M',
'N',
'O',
'P',
'Q',
'S',
'W',
'X',
'Y',
'Z',
	)),
		'#default_value' => $category,
		// '#ajax' => array(
			// 'callback' => 'ocs_ajax_select_user_category',
			// 'wrapper' => 'ocs_ajax_user_category_div',
		// ),
	);
	
	$form['remove'] = array(
		'#type' => 'radios',
		'#options' => array( 'No', 'Yes'),
		'#default_value' => '0',
		'#title' => 'Remove all existing data',
	);
	
	$form['check'] = array(
		'#type' => 'radios',
		'#options' => array( 'No', 'Yes'),
		'#default_value' => '1',
		'#title' => 'Check Only',
	);
        

    // $form['carrier'] = array(
		// '#type' => 'fieldset',
		// '#title' => 'Area',
		// '#prefix' => '<div id="ocs_ajax_user_category_div">',
		// '#suffix' => '</div>',
	// );
	
	$form['data'] = array(
		'#type' => 'markup',
		'#title' => 'Rule data',
		'#markup' => '<table>'.$output.'</table>',
		'#prefix' => '<div id="ocs_ajax_user_category_div">',
		'#suffix' => '</div>',
	);
	
	$form['actions'] = array('#type' => 'actions');
        
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
 
	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
	);
        
	
	return $form;
}

function ocs_ajax_select_user_category( $form, &$form_state)
{
	return $form['data'];	
}

function ocs_migrate_fce_voiceplan_submit( $form, &$form_state)
{
	$values = $form_state['values'];
	if ( $values['op'] == 'Save') {
		dpm( $values, 'values');

		// remove all 'domestic_ratinggroup'
		
		if ( $values['remove'] == '1') {
			$items = entity_load( 'node', FALSE, array( 'type' => 'domestic_ratinggroup', 'title' => 'domestic_ratinggroup'));
    		foreach( array_keys($items) as $nid) {
    			$node = $items[$nid];
    			dpm( $node, t('Domestic rating group @id is removed', array( '@id' => $nid)));
    			node_delete( $nid);
			}
		}
		
		// find 'FCE Numbering Plan'
		$plan = 'FCE Numbering Plan';
		$items = entity_load( 'node', FALSE, array( 'type' => 'numberingplan_domestic', 'title' => $plan));
    	if ( count($items) == 1) {
    		$nids = array_keys($items);
    		
    		// numberingplan_domestic node
    		$np = $items[$nids[0]];
    		
    		// remove all ratinggroup fields
    		unset( $np->field_ref_domestic_ratinggroup);
    		
    		// add rating group records
    		$carrier = $form['#carrier'];
    		foreach( $form['#rule'] as $rule) {
    			//dpm( $rule, 'rule');
    			
    			$list = entity_load( 'node', FALSE, array( 'type' => 'carrier_mobile', 'title' => $rule['called_carrier']));
    			if ( count($list) == 1) {
    				$carrier_nids = array_keys($list);
				}
				else {
					dpm( 'Carrier not found: ' . $rule['called_carrier']);
					continue;
				}
    			
    			$rating_group = $rule['called_carrier'] . '_' . $rule['rating_group'];

    			// search the rating group first
    			$query = new EntityFieldQuery();
				$result = $query->entityCondition('entity_type', 'node')
						->entityCondition('bundle', 'domestic_ratinggroup')
						->fieldCondition( 'field_rating_group', 'value', $rating_group)
						->execute();

				$results = ( !empty($result)) ? array_keys( $result['node']) : array();
				
				if ( count( $results) > 1) {
					dpm( 'Invalid Rating Group:' . $rating_group);
						
					foreach( $results as $nid) {
						$node = node_load( $nid);
						dpm( $node, 'rating group');
					}
					continue;
				}
				
				if ( $values['check'] == '1') {
    				// check if the rating group exist
    				if ( count( $results) == 0) {
    					dpm( 'Rating group not found: '.$rating_group);
    				}
					continue;
				}
				else {
					if ( count( $results) > 0) {
						// rating group exist already
						$r = node_load( $results[0]);
						
						// compare values
						if ( $r->field_ref_numberingplan_domestic['und'][0]['nid'] != $np->nid ||
							$r->field_service_type_of_provider['und'][0]['tid'] != 406 ||	// Mobile
							$r->field_ref_carrier_mobile['und'][0]['nid'] != $carrier_nids[0] ||
							$r->field_is_samezone['und'][0]['tid'] != 1988 ||	// All
							$r->field_rating_group['und'][0]['value'] != $rating_group) {
								
							dpm( $r, 'Rating group value mismatch');
						}
					}
					else {
						// make new rating group
						$r = ocs_admin_get_new_node('domestic_ratinggroup' );
						$r->title = 'domestic_ratinggroup';
						$r->field_ref_numberingplan_domestic['und'][0]['nid'] = $np->nid;
						$r->field_service_type_of_provider['und'][0]['tid'] = 406;	// Mobile
						$r->field_ref_carrier_mobile['und'][0]['nid'] = $carrier_nids[0];
						$r->field_is_samezone['und'][0]['tid'] = 1988;	// All
						$r->field_rating_group['und'][0]['value'] = $rating_group;

						node_save( $r);

						$np->field_ref_domestic_ratinggroup['und'][] = array( 'nid' => $r->nid);
					}

				}

			}

			node_save( $np);
		}
		else {
			dpm( 'Numbering plan not found: '.$plan);
		}
	}
}

function ocs_load_all_carrier()
{
	$carrier = &drupal_static(__FUNCTION__, NULL);
	if (empty($carrier)) {
		db_set_active('fce');

    	$fields = array(  'ruleName', 'prefix', 'regionFlag');
    	$query = db_select( 'carrier', 'c');
    	$result =$query->fields( 'c', $fields)
        	->orderBy('ruleName')
        	->execute();

    	$carrier = array();        
    	while( $record = $result->fetchAssoc()) {
    		$carrier[$record['ruleName']] = $record;
    	}
    	
    	$fields = array(  'ruleName', 'carrier', 'second_prefix', 'rating_group', 'region_code');
    	$query = db_select( 'area', 'a');
    	$result =$query->fields( 'a', $fields)
        	->orderBy('ruleName')
        	->execute();

    	$area = array();        
    	while( $record = $result->fetchAssoc()) {
    		$carrier[$record['carrier']]['rating_group'][$record['rating_group']] = $record;
		}
    	
		db_set_active('default');
	}
	
	return $carrier;
        		
}

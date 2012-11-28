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
        ->orderBy('carrier', 'DESC')
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



function ocs_migrate_fce_voiceplan($form, &$form_state)
{
    db_set_active('fce');

    $query = db_select( 'voice_tariff_decision', 'a');
    $result = $query
        ->fields( 'a', array(  'called_carrier' ,'ruleName' , 'isDDD' , 'rating_group' , 'user_category' , 
        	'time_id' , 'is_video' , 'second_prefix'))
        ->orderBy('called_carrier', 'DESC')
        ->execute();
		
    $output = '<thead><tr><td>Carrier</td><td>Rule</td><td>isDDD</td><td>Rating Group</td><td>Category</td><td>time_id</td>'.
    	'<td>is_video</td><td>Prefix</td></tr></thead>';
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

function ocs_migrate_fce_voiceplan_submit( $form, &$form_state)
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

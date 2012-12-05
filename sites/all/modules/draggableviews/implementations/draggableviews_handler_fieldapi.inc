<?php

/**
 * @file
 * The default implementation for draggableviews.
 */

/*
 * Default Implementation with FieldAPI fields
 */
class draggableviews_handler_fieldapi extends draggableviews_handler {
  function init($field_name, &$view) {
    parent::init($field_name, $view);
    $this->field           = $view->field[$field_name];
  }

  function save($nid, $value) {
    $node = node_load($nid);

    $field_name = $this->field->field;

    // Get field.
    if (!isset($node->$field_name)) {
      // This note doesn't this field.
      return;
    }
    $field = &$node->$field_name;

    if (!isset($value)) {
      // Sometimes there is no value available (e.g. a root node without a parent).
      $value = 0;
    }

    $field_type = $this->field->options['type'];
    $language = $node->language;

    // Differ between certain field types.
    switch ($field_type) {
      case 'node_reference_default':
      case 'node_reference_plain':
      case 'node_reference_node':
        // If there is a new value save it in the field.
        if ($value != 0) {
          $field['und'][0]['nid'] = $value;
        }
        // Check if the field contains a value that should be removed. 
        elseif ($value == 0 && isset($field['und'][0]['nid']) && !empty($field['und'][0]['nid'])) {
          $field = array();
        }
        break;

      default:
      case 'number_integer':
        $field[$language][0]['value'] = $value;
        break;
    }
    node_save($node);
  }



  /**
   * Returns the field value of the given node.
   * Usually this is used to get the weight and the parent id.
   *
   * The expected field (weight or parent) has to be set in $this->field;
   *
   * @param int $value node id
   * @return int
   */
  function get($value) {

    // Get the field name
    $field_name = $this->field->table . "_" . $this->field->real_field;

    // Views allows only 60 chars for the field name
    if (strlen($field_name) > 60) {
      $field_name = substr($field_name, 0, 60);
    }

	// Search for the nid and return the value from of the Views result
    foreach ($this->view->result as $result) {
    	
     if ($result->nid == $value) {
     	
		// views의 에러 때문에 수정했음. 따라서, 이 view의 priority를 조정하면 동작하지 않음.
		if($field_name == 'field_data_field_parent_node_for_hr_field_parent_node_for_hr') {
			return empty($result->field_field_parent_node_for_hr) ? 0 : $result->field_field_parent_node_for_hr[0]['raw']['nid'];
		} else {
		return empty($result->$field_name) ? 0 : $result->$field_name;
			
		} 
      }
    }

    return 0;
  }



}

<?php

require_once( 'ocs_param.inc');

class OcsAction
{
    private $options;       // select options
    private $selected_value;
    private $params;

    function OcsAction() 
    {
        $items = entity_load('node', FALSE, array('type' => 'ocs_actions'));
        $this->options = array();
        $this->options['0'] = 'No Action';
        foreach( $items as $item) {
//         	dpm( $item, 'action');
            $client = taxonomy_term_load( $item->field_ocs_client_id['und'][0]['tid']);
            $title = array_flatten( $item->field_ocs_description);
//            	$this->options[$client->name][$item->nid] = (array_key_exists('value', $title) && $title['value']) ? $title['value'] : $item->title;
           	$this->options[$item->nid] = (array_key_exists('value', $title) && $title['value']) ? $title['value'] : $item->title;
            
            if ( ! isset( $selected_value)) {
                $selected_value = $item->nid;
            }
        }
    }

    function select_options()
    {
        return $this->options;
    }

    function default_value()
    {
        return $this->selected_value;
    }

    function select( $nid)
    {
        foreach( $this->options as $option) {
            if ( is_array( $option) && array_key_exists( $nid, $option)) 
                return $option[$nid];
        }

        return NULL;
    }
}


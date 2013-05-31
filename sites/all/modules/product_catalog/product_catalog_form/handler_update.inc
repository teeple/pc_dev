<?php

function node_update_handler_to_touch_product($newNode,$oldNode){
    //TODO: find real values for the node, and determine wether the real data has been changed or not.
    //touch_product($newNode);
    $productNode = find_parent_product($newNode);
    if($productNode != NULL){
        _touch_product($productNode->nid);
    }
}

function _touch_product($productNid){
    $productNode = node_load($productNid);
    $productNode->changed = REQUEST_TIME;
    node_save($productNode);
}

function product_catalog_form_entity_update($entity, $type){
    switch($type){
        case 'node':
            switch($entity->type){
                case 'tariffplan_idd_carrier':
                    _tariffplan_idd_update_handler($entity);
                    break;
            }
            break;
    }
}

function _tariffplan_idd_update_handler($entity){
   global $user;
   //1. delete old basicrate nodes
   $view = views_get_view('list_basicrate');
   $view->set_display('panel_pane_4');
   $view->set_arguments(array('0' => $entity->field_ref_tariffplan['und'][0]['nid'],'1' => $entity->field_ref_carrier_mobile['und'][0]['nid']));
   $view->execute();
   $delNids = array();
        
   foreach($view->result as $item){
    $delNids[] = $item->nid;
   }
   node_delete_multiple($delNids);
}

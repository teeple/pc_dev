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

//entity update hook
function product_catalog_form_entity_update($entity, $type){
    switch($type){
        case 'node':
            switch($entity->type){
                case 'tariffplan_idd_carrier':
                  _tariffplan_idd_update_handler($entity);
                  break;
                case 'domestic_ratinggroup':
                  _domestic_ratinggroup_update_handler($entity);
                  break;
                case 'idd_ratinggroup':
                  _idd_ratinggroup_update_handler($entity);
                  break;
            }
            break;
    }
}

function _idd_ratinggroup_update_handler($entity){
  $original_ratinggroup = $entity->original->field_rating_group['und'][0]['value'];
  $numberingplan_nid = $entity->field_ref_numberingplan_idd['und'][0]['nid'];
  $new_ratinggroup = $entity->field_rating_group['und'][0]['value'];
  
  if($original_ratinggroup != $new_ratinggroup){
    _delete_basicrate_idd_by_ratinggroup($numberingplan_nid,$original_ratinggroup,$entity->nid);
  }
  
}

function _domestic_ratinggroup_update_handler($entity){
  $original_ratinggroup = $entity->original->field_rating_group['und'][0]['value'];
  $numberingplan_nid = $entity->field_ref_numberingplan_domestic['und'][0]['nid'];
  $new_ratinggroup = $entity->field_rating_group['und'][0]['value'];
  
  if($original_ratinggroup != $new_ratinggroup){
    _delete_basicrate_domestic_by_ratinggroup($numberingplan_nid,$original_ratinggroup,$entity->nid);
  }
}

function _delete_basicrate_idd_by_ratinggroup($numberingplan_nid,$rating_group,$basicrate_nid){
  $rating_group_view_result 
    = views_get_view_result('list_numberingplan_idd_ratinggroup', 'panel_pane_5', $numberingplan_nid,$rating_group,$basicrate_nid);
  
  if(empty($rating_group_view_result)){//if not exist delete related basicrate_domestic
    $del_nids = array();  
    $basicrate_view_result = views_get_view_result('list_basicrate_idd', 'panel_pane_1', $numberingplan_nid,$rating_group,$basicrate_nid);
    foreach($basicrate_view_result as $item){
      $del_nids[] = $item->nid;
    }
    if(!empty($del_nids)){
      node_delete_multiple($del_nids);
    }
  }
}

function _delete_basicrate_domestic_by_ratinggroup($numberingplan_nid,$rating_group,$basicrate_nid){
  $rating_group_view_result 
    = views_get_view_result('list_numberingplan_domestic_ratinggroup', 'panel_pane_4', $numberingplan_nid,$rating_group,$basicrate_nid);
  
  if(empty($rating_group_view_result)){//if not exist delete related basicrate_domestic
    $del_nids = array();  
    $basicrate_view_result = views_get_view_result('list_basicrate_domestic', 'panel_pane_1', $numberingplan_nid,$rating_group,$basicrate_nid);
    foreach($basicrate_view_result as $item){
      $del_nids[] = $item->nid;
    }
    if(!empty($del_nids)){
      node_delete_multiple($del_nids);
    }
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

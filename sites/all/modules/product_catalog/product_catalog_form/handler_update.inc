<?php

function node_update_handler_to_touch_product($newNode,$oldNode){
    
};

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
   
   //2. search used rating group
   $tariffplanNode = node_load($entity->field_ref_tariffplan['und'][0]['nid']);
   $numberingplanNid = $tariffplanNode->field_ref_numberingplan_idd['und'][0]['nid'];
   
   $query = db_select('field_data_field_rating_group', 'rg');
   $query->condition('rg.bundle', 'idd_ratinggroup','=');
   $query->join('field_data_field_ref_numberingplan_idd','idd','rg.entity_id = idd.entity_id');
   $query->condition('idd.field_ref_numberingplan_idd_nid',$numberingplanNid,'=');
   $query->join('field_data_field_ref_carrier_mobile','carrier','rg.entity_id = carrier.entity_id');
   $query->condition('carrier.field_ref_carrier_mobile_nid',$entity->field_ref_carrier_mobile['und'][0]['nid'],'=');
   $query->fields('rg',array('field_rating_group_value'));
   $query->distinct();
   $query->orderBy('rg.field_rating_group_value', 'ASC');
   
   $result = $query->execute();
   $ratingGroups = array();
   while($record = $result->fetchAssoc()) { 
      $ratingGroups[] = current($record);
       
   } 
   /*
   foreach($ratingGroups as $item){
       error_log($item);
   }
   */
   //3. find timetable factors for the carrier
   $timetableNode = node_load($entity->field_ref_timetable_idd['und'][0]['nid']);
   $timetableFactors = array();
   foreach($timetableNode->field_ref_timetablefactors['und'] as $timetableFactor){
       $timetableFactors[] = $timetableFactor['nid'];
   }   
   
   //4. create new basicrate nodes
   if (isset($entity->field_ref_timetable_idd['und'][0]['nid'])) {
       foreach ($ratingGroups as $ratingGroup) {
           foreach ($timetableFactors as $timetableFactor) {
               $node = new StdClass();
               $node->uid = $user->uid;
               $node->language = 'und';
               $node->type = 'basicrate_idd';
               $node->field_ref_tariffplan['und'][0]['nid'] = $entity->field_ref_tariffplan['und'][0]['nid'];
               $node->field_ref_timetablefactors['und'][0]['nid'] = $timetableFactor;
               $node->field_rating_group['und'][0]['value'] = $ratingGroup;
               $node->field_rating_group['und'][0]['safe_value'] = $ratingGroup;
               $node->field_ref_tariffplan_idd_carrier['und'][0]['nid'] = $entity->nid;
               node_save($node);
           }
       }
   }   
}

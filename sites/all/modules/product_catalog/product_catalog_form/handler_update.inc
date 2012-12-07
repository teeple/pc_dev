<?php

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
   error_log('update handler..');
   error_log($entity->nid);
   //1. find rating_group for selected carrir in numberingplan
   
   //2. delete old basicrate nodes
   //3. create new basicrate nodes
}

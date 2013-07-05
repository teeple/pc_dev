<?php
/**
 * @file
 * f_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function f_rules_default_rules_configuration() {
  $items = array();
  $items['rules__attribute_'] = entity_import('rules_config', '{ "rules__attribute_" : {
      "LABEL" : "\\uc0c1\\ud488 \\uc0dd\\uc131 \\ud6c4 \\uae30\\ubcf8 attribute\\uc0dd\\uc131",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "simpleproductoffering" : "simpleproductoffering" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "_create_default_items_in_product($node);\\r\\n" } }
      ]
    }
  }');
  $items['rules_add_js_settings_after_node_save'] = entity_import('rules_config', '{ "rules_add_js_settings_after_node_save" : {
      "LABEL" : "Add_JS_Settings_After_Node_Save",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "NOT node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "actionpricecugdiscountfactors" : "actionpricecugdiscountfactors",
                "area_code" : "area_code",
                "basicrate" : "basicrate",
                "basicrate_domestic" : "basicrate_domestic",
                "basicrate_idd" : "basicrate_idd",
                "basicrate_roaming" : "basicrate_roaming",
                "domestic_ratinggroup" : "domestic_ratinggroup",
                "export_history" : "export_history",
                "idd_ratinggroup" : "idd_ratinggroup",
                "numberingplan_domestic" : "numberingplan_domestic",
                "numberingplan_idd" : "numberingplan_idd",
                "ocs_account_state" : "ocs_account_state",
                "ocs_actions" : "ocs_actions",
                "ocs_event_subscription" : "ocs_event_subscription",
                "ocs_events" : "ocs_events",
                "ocs_message_group" : "ocs_message_group",
                "ocs_messages" : "ocs_messages",
                "ocs_param" : "ocs_param",
                "ocs_state_machine" : "ocs_state_machine",
                "ocs_svc_perm" : "ocs_svc_perm",
                "ocs_transition_actions" : "ocs_transition_actions",
                "packetdynamicl4" : "packetdynamicl4",
                "rate" : "rate",
                "roaming_carrier" : "roaming_carrier",
                "roaming_country" : "roaming_country",
                "roaming_plan" : "roaming_plan",
                "roaming_ratinggroup" : "roaming_ratinggroup",
                "tariffplan" : "tariffplan",
                "tariffplan_idd_carrier" : "tariffplan_idd_carrier",
                "timetable" : "timetable",
                "timetablefactors" : "timetablefactors",
                "timetablefactorsslot" : "timetablefactorsslot"
              }
            }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "add_js_settings_after_node_save($node);" } }
      ]
    }
  }');
  $items['rules_add_js_settings_after_node_update'] = entity_import('rules_config', '{ "rules_add_js_settings_after_node_update" : {
      "LABEL" : "Add_JS_Settings_After_Node_Update",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "NOT node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "area_code" : "area_code",
                "basicrate_domestic" : "basicrate_domestic",
                "basicrate_idd" : "basicrate_idd",
                "basicrate_roaming" : "basicrate_roaming",
                "domestic_ratinggroup" : "domestic_ratinggroup",
                "export_history" : "export_history",
                "idd_ratinggroup" : "idd_ratinggroup",
                "numberingplan_domestic" : "numberingplan_domestic",
                "numberingplan_idd" : "numberingplan_idd",
                "ocs_account_state" : "ocs_account_state",
                "ocs_actions" : "ocs_actions",
                "ocs_event_subscription" : "ocs_event_subscription",
                "ocs_events" : "ocs_events",
                "ocs_message_group" : "ocs_message_group",
                "ocs_messages" : "ocs_messages",
                "ocs_param" : "ocs_param",
                "ocs_state_machine" : "ocs_state_machine",
                "ocs_svc_perm" : "ocs_svc_perm",
                "ocs_transition_actions" : "ocs_transition_actions",
                "packetdynamicl4" : "packetdynamicl4",
                "prdcounterlist" : "prdcounterlist",
                "rate" : "rate",
                "roaming_carrier" : "roaming_carrier",
                "roaming_country" : "roaming_country",
                "roaming_plan" : "roaming_plan",
                "roaming_ratinggroup" : "roaming_ratinggroup",
                "tariffplan_idd_carrier" : "tariffplan_idd_carrier",
                "timetable" : "timetable",
                "timetablefactors" : "timetablefactors",
                "timetablefactorsslot" : "timetablefactorsslot",
                "treenodecounter" : "treenodecounter",
                "treenodecounterforvoucher" : "treenodecounterforvoucher"
              }
            }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "add_js_settings_after_node_update($node);" } }
      ]
    }
  }');
  $items['rules_add_link_in_views_summary'] = entity_import('rules_config', '{ "rules_add_link_in_views_summary" : {
      "LABEL" : "Add link in views summary",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "php", "rules", "rb_views" ],
      "ON" : [
        "rb_views_event_view_execute",
        "rb_views_event_view_render",
        "rb_views_event_view_complete"
      ],
      "DO" : [ { "php_eval" : { "code" : "dsm($view);\\r\\n" } } ]
    }
  }');
  $items['rules_basic_counter_counter_main_'] = entity_import('rules_config', '{ "rules_basic_counter_counter_main_" : {
      "LABEL" : "Basic Counter \\ucd94\\uac00 \\uc2dc \\ud574\\ub2f9 counter\\ub97c main \\uc0c1\\ud488\\uc5d0 \\uc790\\ub3d9 \\ucd94\\uac00",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "counter" : "counter" } } } },
        { "php_eval" : { "code" : "\\r\\n$counterTypeTerm = taxonomy_term_load($node-\\u003Efield_counter_type[\\u0027und\\u0027][0][\\u0027tid\\u0027]);\\r\\n\\r\\nif($counterTypeTerm-\\u003Ename == \\u0027Basic\\u0027) {\\r\\n  return TRUE;\\r\\n} else {\\r\\n  return FALSE;\\r\\n}\\r\\n" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "$svcDomainTerm = taxonomy_term_load($node-\\u003Efield_service_domain[\\u0027und\\u0027][0][\\u0027tid\\u0027]);\\r\\n_attach_basic_counter($node, $svcDomainTerm-\\u003Ename);\\r\\n" } }
      ]
    }
  }');
  $items['rules_before_saving_treenodecounter'] = entity_import('rules_config', '{ "rules_before_saving_treenodecounter" : {
      "LABEL" : "Unlimited Value Set in treeNodeCounter ",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "treenodecounter" : "treenodecounter" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "set_unlimited_in_treenodecounter($node);\\r\\n" } }
      ]
    }
  }');
  $items['rules_carrier_area_code_add'] = entity_import('rules_config', '{ "rules_carrier_area_code_add" : {
      "LABEL" : "carrier_area_code_add",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$carrier_nid = $temp[4];\\r\\n$carrier = node_load($carrier_nid);\\r\\n\\r\\nforeach($list_item as $item){\\r\\n  $searchItems = $carrier-\\u003Efield_ref_prefix;\\r\\n  $createFlag= TRUE;\\r\\n  if(!empty($searchItems)){\\r\\n     foreach($searchItems[\\u0027und\\u0027] as $search){\\r\\n       $prefixNode= node_load($search[\\u0027nid\\u0027]);\\r\\n       if(isset($prefixNode-\\u003Efield_ref_area_code)){\\r\\n         if($prefixNode-\\u003Efield_ref_area_code[\\u0027und\\u0027][0][\\u0027nid\\u0027] == $item-\\u003Enid){\\r\\n           $createFlag = FALSE;\\r\\n           break;\\r\\n         }\\r\\n      }\\r\\n    }\\r\\n  }\\r\\n\\r\\n  if($createFlag == TRUE){\\r\\n    $prefix = new StdClass();\\r\\n    $prefix-\\u003Etype = \\u0027prefix\\u0027;\\r\\n    $prefix-\\u003Euid = $user-\\u003Euid;\\r\\n    $prefix-\\u003Etitle = \\u0027prefix\\u0027;\\r\\n    $prefix-\\u003Efield_ref_area_code[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $item-\\u003Enid;\\r\\n    node_save($prefix);\\r\\n    $carrier-\\u003Efield_ref_prefix[\\u0027und\\u0027][][\\u0027nid\\u0027] = $prefix-\\u003Enid;\\r\\n  }\\r\\n}\\r\\n\\r\\nnode_save($carrier);\\r\\n\\r\\ndrupal_goto($current_path);" } }
      ]
    }
  }');
  $items['rules_carrier_area_code_delete'] = entity_import('rules_config', '{ "rules_carrier_area_code_delete" : {
      "LABEL" : "carrier_area_code_delete",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$carrier_nid = $temp[4];\\r\\n$carrier = node_load($carrier_nid);\\r\\n\\r\\nforeach($list_item as $item){\\r\\n  foreach($carrier-\\u003Efield_ref_prefix[\\u0027und\\u0027] as $prefix){\\r\\n     $prefixNode = node_load($prefix[\\u0027nid\\u0027]);\\r\\n     if(isset($prefixNode -\\u003Efield_ref_area_code)){\\r\\n       if($prefixNode -\\u003Efield_ref_area_code[\\u0027und\\u0027][0][\\u0027nid\\u0027] == $item-\\u003Enid){\\r\\n          $params = array();\\r\\n          $params[\\u0027parent_nid\\u0027] =  $carrier_nid;\\r\\n          $params[\\u0027target_field\\u0027] =  \\u0027field_ref_prefix\\u0027;\\r\\n          $params[\\u0027child_nid\\u0027] =   $prefix[\\u0027nid\\u0027];\\r\\n          $params[\\u0027redirect\\u0027] = FALSE;\\r\\n          _unlink_from_parent($params);\\r\\n          break;\\r\\n       }\\r\\n     }\\r\\n  }\\r\\n}\\r\\n\\r\\ndrupal_goto($current_path);" } }
      ]
    }
  }');
  $items['rules_check_duplicate'] = entity_import('rules_config', '{ "rules_check_duplicate" : {
      "LABEL" : "check duplicate (area_ratinggroup)",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php", "feeds" ],
      "ON" : [ "feeds_import_area_ratinggroup_importer" ],
      "IF" : [
        { "php_eval" : { "code" : "\\/\\/dsm(\\u0027from - [node:field-area-from]\\u0027);\\r\\n\\/\\/dsm(\\u0027to - [node:field-area-to]\\u0027);\\r\\n\\r\\n$query = \\u0022SELECT count(*) num\\r\\nFROM \\r\\n{node} node\\r\\nLEFT JOIN {field_data_field_area_from} field_data_field_area_from ON node.nid = field_data_field_area_from.entity_id AND (field_data_field_area_from.entity_type = \\u0027node\\u0027 AND field_data_field_area_from.deleted = \\u00270\\u0027)\\r\\nLEFT JOIN {node} node_field_data_field_area_from ON field_data_field_area_from.field_area_from_nid = node_field_data_field_area_from.nid\\r\\nLEFT JOIN {field_data_field_area_to} field_data_field_area_to ON node.nid = field_data_field_area_to.entity_id AND (field_data_field_area_to.entity_type = \\u0027node\\u0027 AND field_data_field_area_to.deleted = \\u00270\\u0027)\\r\\nLEFT JOIN {node} node_field_data_field_area_to ON field_data_field_area_to.field_area_to_nid = node_field_data_field_area_to.nid\\r\\nWHERE (( (node.status = \\u00271\\u0027) AND (node.type IN  (\\u0027area_ratinggroup\\u0027)) AND (node_field_data_field_area_from.title = :from) AND (node_field_data_field_area_to.title = :to)))\\u0022 ;\\r\\n\\r\\n$db_result = db_query($query,array(\\u0027:from\\u0027 =\\u003E\\u0027[node:field-area-from]\\u0027,\\u0027:to\\u0027 =\\u003E\\u0027[node:field-area-to]\\u0027))-\\u003EfetchObject();\\r\\n\\r\\nif($db_result-\\u003Enum \\u003E 0) return TRUE;\\r\\nelse return FALSE;" } }
      ],
      "DO" : [
        { "feeds_skip_item" : { "entity" : [ "node" ] } },
        { "drupal_message" : { "message" : "AreaFrom: [node:field-area-from] and AreaTo: [node:field-area-to] already registered." } }
      ]
    }
  }');
  $items['rules_check_lifecycle_scheme'] = entity_import('rules_config', '{ "rules_check_lifecycle_scheme" : {
      "LABEL" : "check_lifecycle_scheme",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "TAGS" : [ "lifecycle" ],
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "lifecyclescheme" : "lifecyclescheme" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\nocs_admin_check_lifecycle_scheme( $node, $node_unchanged);\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_check_lifecycle_scheme_after_deleting_content_'] = entity_import('rules_config', '{ "rules_check_lifecycle_scheme_after_deleting_content_" : {
      "LABEL" : "check_lifecycle_scheme (after deleting content)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "lifecycle" ],
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "lifecyclescheme" : "lifecyclescheme" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\nocs_lifecycle_deleted( $node);\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_check_lifecycle_scheme_after_new_content_'] = entity_import('rules_config', '{ "rules_check_lifecycle_scheme_after_new_content_" : {
      "LABEL" : "check_lifecycle_scheme (after new content)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "lifecycle" ],
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "lifecyclescheme" : "lifecyclescheme" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\nocs_lifecycle_add_svcperm( $node);\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_check_update_time'] = entity_import('rules_config', '{ "rules_check_update_time" : {
      "LABEL" : "check update time",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "simpleproductoffering" : "simpleproductoffering" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "module_load_include( \\u0027inc\\u0027, \\u0027ocs_admin\\u0027, \\u0027ocs_check\\u0027);\\r\\nocs_check_before_save( $node, $node_unchanged);" } }
      ]
    }
  }');
  $items['rules_common_code_update_for_vbo'] = entity_import('rules_config', '{ "rules_common_code_update_for_vbo" : {
      "LABEL" : "Common Code Update for VBO",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_voca" : { "label" : "list_voca", "type" : "list\\u003Clist\\u003E" } },
      "ACTION SET" : [ { "php_eval" : { "code" : "pc_code_update_in_vbo($list_voca);\\r\\n" } } ]
    }
  }');
  $items['rules_counter_all_default_usage_type_'] = entity_import('rules_config', '{ "rules_counter_all_default_usage_type_" : {
      "LABEL" : "Counter \\uc800\\uc7a5\\uc2dc All \\uc120\\ud0dd\\uc2dc default usage type\\uc744 \\uc544\\ubb34\\uac83\\ub3c4 \\uc120\\ud0dd\\ud558\\uc9c0 \\uc54a\\ub294 \\uac78\\ub85c",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "counter" : "counter" } } } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "if($node-\\u003Efield_select_all_or_not[\\u0027und\\u0027][0][\\u0027value\\u0027] == 1) {\\r\\n   $node-\\u003Efield_default_usage_type = array();\\r\\n}\\r\\n" } }
      ]
    }
  }');
  $items['rules_counter_treenodecounter_'] = entity_import('rules_config', '{ "rules_counter_treenodecounter_" : {
      "LABEL" : "Counter \\uc218\\uc815 \\uc2dc \\uc0ad\\uc81c\\ub41c treenodecounter\\ub97c \\uc0ad\\uc81c",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "prdcounterlist" : "prdcounterlist" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "$oldList = array_values($node_unchanged-\\u003Efield_counter_list[\\u0027und\\u0027]);\\r\\n$newList = array_values($node-\\u003Efield_counter_list[\\u0027und\\u0027]);\\r\\n\\r\\n$oldCounterNids = array();\\r\\n$newCounterNids = array();\\r\\nforeach($oldList as $record) {\\r\\n   $oldCounterNids[] = current($record);\\r\\n}\\r\\nforeach($newList as $record) {\\r\\n   $newCounterNids[] = current($record);\\r\\n}\\r\\n$changedCounters = array_diff($oldCounterNids, $newCounterNids);\\r\\n\\r\\n$args = array();\\r\\n$args[0] = $node-\\u003Efield_ref_product[\\u0027und\\u0027][0][\\u0027nid\\u0027];\\r\\n$args[1] = join(\\u0027+\\u0027, $changedCounters);\\r\\n$changedTreeNodeCounterNids = _get_nids_from_views(\\u0027list_treenodecounter\\u0027, \\u0027panel_pane_2\\u0027, $args);\\r\\n\\r\\nif(!empty($changedTreeNodeCounterNids)) {\\r\\n       node_delete_multiple($changedTreeNodeCounterNids);\\r\\n}\\r\\nadd_js_settings_after_node_update($node);" } }
      ]
    }
  }');
  $items['rules_create_counter_for_voucher_card_type'] = entity_import('rules_config', '{ "rules_create_counter_for_voucher_card_type" : {
      "LABEL" : "Create counter for voucher card type",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "vouchercardtype" : "vouchercardtype" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "product_catalog_rules_create_default_counters([node:nid]);" } }
      ]
    }
  }');
  $items['rules_cug_tariff_plan_cug_discount_factor_'] = entity_import('rules_config', '{ "rules_cug_tariff_plan_cug_discount_factor_" : {
      "LABEL" : "CUG\\uc6a9 Tariff Plan \\uc0dd\\uc131\\uc2dc \\uc790\\ub3d9\\uc73c\\ub85c CUG Discount Factor \\uc0dd\\uc131 ",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-10",
      "ACTIVE" : false,
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "php_eval" : { "code" : "$product = node_load($node-\\u003Efield_ref_product[\\u0027und\\u0027][0][\\u0027nid\\u0027]);\\r\\n$prdTypeTerm = taxonomy_term_load($product-\\u003Efield_product_type[\\u0027und\\u0027][0][\\u0027tid\\u0027]);\\r\\n\\r\\nif($prdTypeTerm-\\u003Ename == \\u0027CUG\\u0027) {\\r\\n  return TRUE;\\r\\n}\\r\\n" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "_create_default_cugdiscountfactors_in_tariffplan($node);\\r\\n" } }
      ]
    }
  }');
  $items['rules_deletetempmapnode'] = entity_import('rules_config', '{ "rules_deletetempmapnode" : {
      "LABEL" : "DeleteTempMapNode",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "mapbasicratedomestic" : "mapbasicratedomestic",
                "mapbasicratedomesticincoming" : "mapbasicratedomesticincoming",
                "mapbasicrateidd" : "mapbasicrateidd",
                "mapbasicrateroaming" : "mapbasicrateroaming"
              }
            }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\nnode_delete($node-\\u003Enid);\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_deploy_selected_items'] = entity_import('rules_config', '{ "rules_deploy_selected_items" : {
      "LABEL" : "Deploy Selected Items",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "term_list" : { "label" : "Taxonomy Terms", "type" : "list\\u003Ctaxonomy_term\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "dsm($term_list, \\u0027term_list\\u0027);\\r\\n" } }
      ]
    }
  }');
  $items['rules_deploy_selected_products'] = entity_import('rules_config', '{ "rules_deploy_selected_products" : {
      "LABEL" : "Deploy to Test Bed (PRODUCT)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial'] = entity_import('rules_config', '{ "rules_deploy_to_commercial" : {
      "LABEL" : "Deploy to Commercial",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "dsm($export_item_list, \\u0027export_item_list\\u0027);\\r\\n$item = current($export_item_list);\\r\\n$content_type = $item-\\u003Etype;\\r\\n$export_type = _get_export_type_by_content_type($content_type);\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_archive_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_archive_" : {
      "LABEL" : "Deploy to Commercial (ARCHIVE)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027ARCHIVE\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_audit_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_audit_" : {
      "LABEL" : "Deploy to Commercial (AUDIT)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027AUDIT\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_exclusiveness_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_exclusiveness_" : {
      "LABEL" : "Deploy to Commercial (EXCLUSIVENESS)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027EXCLUSIVENESS\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_product_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_product_" : {
      "LABEL" : "Deploy to Commercial (PRODUCT)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_product_change_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_product_change_" : {
      "LABEL" : "Deploy to Commercial (PRODUCT_CHANGE)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT_CHANGE_SCHEME\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_commercial_product_group_'] = entity_import('rules_config', '{ "rules_deploy_to_commercial_product_group_" : {
      "LABEL" : "Deploy to Commercial (PRODUCT_GROUP)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT_GROUP\\u0027;\\r\\n$target = \\u0027commercial\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed" : {
      "LABEL" : "Deploy to Test Bed",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$item = current($export_item_list);\\r\\n$content_type = $item-\\u003Etype;\\r\\n$export_type = _get_export_type_by_content_type($content_type);\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed_archive_'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed_archive_" : {
      "LABEL" : "Deploy to Test Bed (ARCHIVE)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027ARCHIVE\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed_audit_'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed_audit_" : {
      "LABEL" : "Deploy to Test Bed (AUDIT)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027AUDIT\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed_exclusivenss_'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed_exclusivenss_" : {
      "LABEL" : "Deploy to Test Bed (EXCLUSIVENSS)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027EXCLUSIVENESS\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed_product_change_'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed_product_change_" : {
      "LABEL" : "Deploy to Test Bed (PRODUCT_CHANGE)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT_CHANGE_SCHEME\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deploy_to_test_bed_product_group_'] = entity_import('rules_config', '{ "rules_deploy_to_test_bed_product_group_" : {
      "LABEL" : "Deploy to Test Bed (PRODUCT_GROUP)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "export_item_list" : { "label" : "Export Item List", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$export_type = \\u0027PRODUCT_GROUP\\u0027;\\r\\n$target = \\u0027testbed\\u0027;\\r\\necho export_deploy($export_type,$export_item_list, $target);" } }
      ]
    }
  }');
  $items['rules_deposit_scheme_total_record_'] = entity_import('rules_config', '{ "rules_deposit_scheme_total_record_" : {
      "LABEL" : "Deposit Scheme\\uc0dd\\uc131\\uc2dc \\uc790\\ub3d9\\uc73c\\ub85c TOTAL record \\uc0dd\\uc131 ",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "depositscheme" : "depositscheme" } }
          }
        },
        { "NOT text_matches" : { "text" : [ "node:title" ], "match" : "depositscheme_tmp" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$depositSchemeFactor = new StdClass();\\r\\n$depositSchemeFactor-\\u003Euid = $user-\\u003Euid;\\r\\n$depositSchemeFactor-\\u003Etype = \\u0027depositschemefactors\\u0027;\\r\\n$depositSchemeFactor-\\u003Elanguage = \\u0027und\\u0027;\\r\\n$depositSchemeFactor-\\u003Etitle = \\u0027TOTAL\\u0027;\\r\\n$depositSchemeFactor-\\u003Efield_ref_depositscheme[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $node-\\u003Enid;\\r\\n$depositSchemeFactor-\\u003Efield_is_default_factor[\\u0027und\\u0027][0][\\u0027value\\u0027] = 1;\\r\\nnode_save($depositSchemeFactor);\\r\\n" } }
      ]
    }
  }');
  $items['rules_dummy_action_for_vbo'] = entity_import('rules_config', '{ "rules_dummy_action_for_vbo" : {
      "LABEL" : "Dummy Action For VBO",
      "PLUGIN" : "action set",
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : []
    }
  }');
  $items['rules_dummy_action_for_vbo_term'] = entity_import('rules_config', '{ "rules_dummy_action_for_vbo_term" : {
      "LABEL" : "Dummy Action For VBO_TERM",
      "PLUGIN" : "action set",
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Ctaxonomy_term\\u003E" } },
      "ACTION SET" : []
    }
  }');
  $items['rules_for_list_characteristic_sub_temp'] = entity_import('rules_config', '{ "rules_for_list_characteristic_sub_temp" : {
      "LABEL" : "for_list_characteristic_sub",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php", "rb_views" ],
      "ON" : [ "rb_views_event_view_execute" ],
      "IF" : [
        { "OR" : [
            { "AND" : [
                { "text_matches" : { "text" : [ "view:human-name" ], "match" : "list_characteristic_sub" } },
                { "NOT data_is_empty" : { "data" : [ "view:args:1" ] } }
              ]
            },
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-user:name" ], "value" : "1" } }
              ]
            }
          ]
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "$returnArgs = array();\\r\\n\\r\\n$temp_result = views_get_view_result( \\u0027query_sub_characteristic_2\\u0027, \\u0027default\\u0027, $view-\\u003Eargs[1] );\\r\\n\\r\\nforeach($temp_result as $usedChar){\\r\\n   $returnArgs[] = $usedChar-\\u003Enode_field_data_field_r_productspecchar_nid;\\r\\n}\\r\\n\\r\\nif(count($returnArgs) \\u003E 0){\\r\\n  $view-\\u003Eargs[1] = join($returnArgs,\\u0027+\\u0027);   \\r\\n}" } }
      ]
    }
  }');
  $items['rules_hook_before_rule_viewed'] = entity_import('rules_config', '{ "rules_hook_before_rule_viewed" : {
      "LABEL" : "hook_before_rule_viewed",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "php", "rb_views" ],
      "ON" : [ "rb_views_event_view_execute" ],
      "DO" : [
        { "drupal_message" : { "message" : "--- HOOK_BEFORE_RULE_VIEWED ---" } },
        { "php_eval" : { "code" : "dsm($view);" } }
      ]
    }
  }');
  $items['rules_import_basicrate_domestic'] = entity_import('rules_config', '{ "rules_import_basicrate_domestic" : {
      "LABEL" : "Import_Basicrate_Domestic",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules", "feeds" ],
      "ON" : [ "feeds_import_basicrate_domestic_importer" ],
      "DO" : [
        { "php_eval" : { "code" : "$node-\\u003Efield_parent_node[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $_SESSION[\\u0027parent_node\\u0027];" } }
      ]
    }
  }');
  $items['rules_import_basicrate_idd'] = entity_import('rules_config', '{ "rules_import_basicrate_idd" : {
      "LABEL" : "Import_Basicrate_IDD",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules", "feeds" ],
      "ON" : [ "feeds_import_basicrate_idd_importer" ],
      "DO" : [
        { "php_eval" : { "code" : "$node-\\u003Efield_parent_node[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $_SESSION[\\u0027parent_node\\u0027];" } }
      ]
    }
  }');
  $items['rules_log_content_changes'] = entity_import('rules_config', '{ "rules_log_content_changes" : {
      "LABEL" : "Log content changes",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "node_update" ],
      "DO" : [
        { "php_eval" : { "code" : "module_load_include( \\u0027inc\\u0027, \\u0027ocs_admin\\u0027, \\u0027ocs_common\\u0027);\\r\\nocs_log_changes( $node_unchanged, $node);" } }
      ]
    }
  }');
  $items['rules_log_field_collection_item_changes'] = entity_import('rules_config', '{ "rules_log_field_collection_item_changes" : {
      "LABEL" : "Log field_collection item changes",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules", "field_collection" ],
      "ON" : [ "field_collection_item_update" ],
      "DO" : [
        { "php_eval" : { "code" : "module_load_include( \\u0027inc\\u0027, \\u0027ocs_admin\\u0027, \\u0027ocs_common\\u0027);\\r\\nocs_log_changes( $field_collection_item_unchanged, $field_collection_item);" } }
      ]
    }
  }');
  $items['rules_numberingplan_domestic_to_product'] = entity_import('rules_config', '{ "rules_numberingplan_domestic_to_product" : {
      "LABEL" : "Numberingplan_Domestic_To_Product",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "dsm(\\u0027rule excuted\\u0027);\\r\\n\\/*\\r\\nglobal $user;\\r\\n$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$usage_nid= $temp[6];\\r\\n\\r\\n$usage = node_load($usage_nid);\\r\\n$numberingplan = current($list_item);\\r\\n$usage-\\u003Efield_ref_numberingplan_domestic[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $numberingplan-\\u003Enid;\\r\\nnode_save($usage);\\r\\n\\r\\ndrupal_goto($current_path);\\r\\n*\\/\\r\\ndsm(\\u0027haha\\u0027);" } }
      ]
    }
  }');
  $items['rules_numberingplan_idd_to_product'] = entity_import('rules_config', '{ "rules_numberingplan_idd_to_product" : {
      "LABEL" : "Numberingplan_IDD_To_Product",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$usage_nid= $temp[6];\\r\\n\\r\\n$usage = node_load($usage_nid);\\r\\n$numberingplan = current($list_item);\\r\\n$usage-\\u003Efield_ref_numberingplan_idd[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $numberingplan-\\u003Enid;\\r\\nnode_save($usage);\\r\\n\\r\\ndrupal_goto($current_path);" } }
      ]
    }
  }');
  $items['rules_page_redirect_for_account'] = entity_import('rules_config', '{ "rules_page_redirect_for_account" : {
      "LABEL" : "Page Redirect for Account",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_insert", "user_update" ],
      "DO" : [ { "redirect" : { "url" : "account\\/list" } } ]
    }
  }');
  $items['rules_prdnonusagerollover_counter_change'] = entity_import('rules_config', '{ "rules_prdnonusagerollover_counter_change" : {
      "LABEL" : "PrdNonUsageRollover\\uc5d0\\uc11c counter \\uac12 \\uc218\\uc815\\uc2dc PrdNonUsageRolloverFactors\\uac12 \\ubcc0\\uacbd ",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "prdnonusagerollover" : "prdnonusagerollover" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$oldList = array_values($node_unchanged-\\u003Efield_counter_list[\\u0027und\\u0027]);\\r\\n$newList = array_values($node-\\u003Efield_counter_list[\\u0027und\\u0027]);\\r\\n\\r\\n$oldCounterNids = array();\\r\\n$newCounterNids = array();\\r\\nforeach($oldList as $record) {\\r\\n   $oldCounterNids[] = current($record);\\r\\n}\\r\\nforeach($newList as $record) {\\r\\n   $newCounterNids[] = current($record);\\r\\n}\\r\\n$changedCountersForDelete = array_diff($oldCounterNids, $newCounterNids);\\r\\n$changedCountersForAdd = array_diff($newCounterNids, $oldCounterNids);\\r\\n\\r\\n$args = array();\\r\\n$args[0] = $node-\\u003Enid;\\r\\n$args[1] = join(\\u0027+\\u0027, $changedCountersForDelete);\\r\\n$rolloverFactorsForDelete = _get_nids_from_views(\\u0027list_prdnonusagerolloverfactors\\u0027, \\u0027panel_pane_2\\u0027, $args);\\r\\n\\r\\nif(!empty($rolloverFactorsForDelete)) {\\r\\n       node_delete_multiple($rolloverFactorsForDelete);\\r\\n}\\r\\n\\r\\nforeach($changedCountersForAdd as $counterNid) {\\r\\n      $rolloverFactors = new StdClass();\\r\\n      $rolloverFactors-\\u003Euid = $user-\\u003Euid;\\r\\n      $rolloverFactors-\\u003Elanguage = \\u0027und\\u0027;\\r\\n      $rolloverFactors-\\u003Etype = \\u0027prdnonusagerolloverfactors\\u0027;\\r\\n      $rolloverFactors-\\u003Efield_ref_nonusagerollover[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $node-\\u003Enid;\\r\\n      $rolloverFactors-\\u003Efield_ref_counter[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $counterNid;\\r\\n      node_save($rolloverFactors);\\r\\n}\\r\\n" } }
      ]
    }
  }');
  $items['rules_prdnonusagerollover_prdnonusagerolloverfactors_'] = entity_import('rules_config', '{ "rules_prdnonusagerollover_prdnonusagerolloverfactors_" : {
      "LABEL" : "PrdNonUsageRollover\\uc0dd\\uc131\\uc2dc \\uc2dc PrdNonUsageRolloverFactors\\uac12 \\ubcc0\\uacbd",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "prdnonusagerollover" : "prdnonusagerollover" } }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$newList = array_values($node-\\u003Efield_counter_list[\\u0027und\\u0027]);\\r\\n$newCounterNids = array();\\r\\nforeach($newList as $record) {\\r\\n   $newCounterNids[] = current($record);\\r\\n}\\r\\n\\r\\nforeach($newCounterNids as $counterNid) {\\r\\n      $rolloverFactors = new StdClass();\\r\\n      $rolloverFactors-\\u003Euid = $user-\\u003Euid;\\r\\n      $rolloverFactors-\\u003Elanguage = \\u0027und\\u0027;\\r\\n      $rolloverFactors-\\u003Etype = \\u0027prdnonusagerolloverfactors\\u0027;\\r\\n      $rolloverFactors-\\u003Efield_ref_nonusagerollover[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $node-\\u003Enid;\\r\\n      $rolloverFactors-\\u003Efield_ref_counter[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $counterNid;\\r\\n      node_save($rolloverFactors);\\r\\n}\\r\\n" } }
      ]
    }
  }');
  $items['rules_product_change_delete_counters_'] = entity_import('rules_config', '{ "rules_product_change_delete_counters_" : {
      "LABEL" : "Product Change (Delete - Counters)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdchange_selected_counter" : {
          "label" : "ProductChange Selected Counters",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$counterNids = array_keys($prdchange_selected_counter);\\r\\nnode_delete_multiple($counterNids);" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productchange\\/edit\\/\\u0027 . $path[3] . \\u0027\\/2#quickset-relation_manager=5\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_product_change_delete_sub_items_'] = entity_import('rules_config', '{ "rules_product_change_delete_sub_items_" : {
      "LABEL" : "Product Change (Delete - Sub Items)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdchange_selected_sub" : {
          "label" : "ProductChange Selected Sub Products",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$productNids = array_keys($prdchange_selected_sub);\\r\\nnode_delete_multiple($productNids);\\r\\n" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productchange\\/edit\\/\\u0027 . $path[3] . \\u0027\\/1#quickset-relation_manager=5\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_product_change_select_counters_'] = entity_import('rules_config', '{ "rules_product_change_select_counters_" : {
      "LABEL" : "Product Change (Select - Counters)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdchange_selected_counter" : {
          "label" : "ProductChange Selected Counters",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$counterNids = array_keys($prdchange_selected_counter);\\r\\n$path= explode(\\u0027\\/\\u0027, current_path());\\r\\n$productChangeNid = $path[3];\\r\\n\\r\\nforeach($counterNids as $counterNid) {\\r\\n    $node = new stdClass();\\r\\n    $node-\\u003Etype = \\u0027productchangecounterselected\\u0027;\\r\\n    $node-\\u003Estatus = 1;\\r\\n    $node-\\u003Euid = $user-\\u003Euid;\\r\\n    $node-\\u003Etitle = \\u0027productchangecounterselected\\u0027;\\r\\n    $node-\\u003Efield_ref_counter[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $counterNid;\\r\\n    $node-\\u003Efield_ref_product_change[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $productChangeNid;\\r\\n    $node-\\u003Elanguage = \\u0027und\\u0027;\\r\\n    node_save($node); \\r\\n}" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productchange\\/edit\\/\\u0027 . $path[3] . \\u0027\\/2#quickset-relation_manager=5\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_product_change_select_not_main_products_'] = entity_import('rules_config', '{ "rules_product_change_select_not_main_products_" : {
      "LABEL" : "Product Change (Select - Not Main Products)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdchange_selected_sub" : {
          "label" : "ProductGroup Selected Sub Products",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$productNids = array_keys($prdchange_selected_sub);\\r\\n$path= explode(\\u0027\\/\\u0027, current_path());\\r\\n$productChangeNid = $path[3];\\r\\n\\r\\nforeach($productNids as $productNid) {\\r\\n    $node = new stdClass();\\r\\n    $node-\\u003Etype = \\u0027productchangesubselected\\u0027;\\r\\n    $node-\\u003Estatus = 1;\\r\\n    $node-\\u003Euid = $user-\\u003Euid;\\r\\n    $node-\\u003Etitle = \\u0027productchangesubselected\\u0027;\\r\\n    $node-\\u003Efield_ref_product[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $productNid;\\r\\n    $node-\\u003Efield_ref_product_change[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $productChangeNid;\\r\\n    $node-\\u003Elanguage = \\u0027und\\u0027;\\r\\n    node_save($node); \\r\\n}" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productchange\\/edit\\/\\u0027 . $path[3] . \\u0027\\/1#quickset-relation_manager=5\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_product_group_delete_main_items_'] = entity_import('rules_config', '{ "rules_product_group_delete_main_items_" : {
      "LABEL" : "Product Group (Delete - Main Items)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdgroup_selected_main" : {
          "label" : "ProductGroup Selected Main Products",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "$productNids = array_keys($prdgroup_selected_main);\\r\\nnode_delete_multiple($productNids);\\r\\n" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productgroup\\/edit\\/\\u0027 . $path[3] . \\u0027\\/1#quickset-relation_manager=4\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_product_number_special_allowed'] = entity_import('rules_config', '{ "rules_product_number_special_allowed" : {
      "LABEL" : "Product_Number_Special_Allowed",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$product_nid = $temp[4];\\r\\n\\r\\n$product = node_load($product_nid );\\r\\n\\r\\nforeach($list_item as $item){\\r\\n  $searchItems = $product -\\u003Efield_ref_number_sp_allowed;\\r\\n  $createFlag= TRUE;\\r\\n  if(!empty($searchItems)){\\r\\n     foreach($searchItems[\\u0027und\\u0027] as $search){\\r\\n       if($search[\\u0027nid\\u0027] == $item-\\u003Enid){\\r\\n         $createFlag = FALSE;\\r\\n         break;\\r\\n       }\\r\\n      }\\r\\n    }\\r\\n  if($createFlag == TRUE){\\r\\n    $product -\\u003Efield_ref_number_sp_allowed[\\u0027und\\u0027][][\\u0027nid\\u0027] = $item-\\u003Enid;\\r\\n  }\\r\\n}\\r\\n\\r\\nnode_save($product);\\r\\n\\r\\ndrupal_goto($current_path);" } }
      ]
    }
  }');
  $items['rules_product_number_special_forbidden'] = entity_import('rules_config', '{ "rules_product_number_special_forbidden" : {
      "LABEL" : "Product_Number_Special_Forbidden",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n$current_path = current_path();\\r\\n$temp = explode(\\u0027\\/\\u0027,$current_path);\\r\\n$product_nid = $temp[4];\\r\\n\\r\\n$product = node_load($product_nid );\\r\\n\\r\\nforeach($list_item as $item){\\r\\n  $searchItems = $product -\\u003Efield_ref_number_sp_forbidden;\\r\\n  $createFlag= TRUE;\\r\\n  if(!empty($searchItems)){\\r\\n     foreach($searchItems[\\u0027und\\u0027] as $search){\\r\\n       if($search[\\u0027nid\\u0027] == $item-\\u003Enid){\\r\\n         $createFlag = FALSE;\\r\\n         break;\\r\\n       }\\r\\n      }\\r\\n    }\\r\\n  if($createFlag == TRUE){\\r\\n    $product -\\u003Efield_ref_number_sp_forbidden[\\u0027und\\u0027][][\\u0027nid\\u0027] = $item-\\u003Enid;\\r\\n  }\\r\\n}\\r\\n\\r\\nnode_save($product);\\r\\n\\r\\ndrupal_goto($current_path);" } }
      ]
    }
  }');
  $items['rules_redirect_after_node_delete'] = entity_import('rules_config', '{ "rules_redirect_after_node_delete" : {
      "LABEL" : "Redirect After Node Delete",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "-10",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_delete" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "carrier_mobile" : "carrier_mobile",
                "depositscheme" : "depositscheme",
                "number_special" : "number_special",
                "numberingplan_domestic" : "numberingplan_domestic",
                "numberingplan_idd" : "numberingplan_idd",
                "packetdynamicchargingrule" : "packetdynamicchargingrule",
                "packetdynamicl4" : "packetdynamicl4",
                "packetpredefinedchargingrule" : "packetpredefinedchargingrule",
                "roaming_carrier" : "roaming_carrier",
                "roaming_country" : "roaming_country",
                "roaming_plan" : "roaming_plan",
                "roaming_zone" : "roaming_zone",
                "thresholdscheme" : "thresholdscheme",
                "timetable" : "timetable"
              }
            }
          }
        }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : {
              "type" : "uri",
              "value" : "\\u003C?php\\r\\n$url = _get_redirect_url_in_delete($node);\\r\\necho $url[\\u0027path\\u0027] . \\u0027#\\u0027. $url[\\u0027fragment\\u0027];\\r\\n?\\u003E\\r\\n"
            },
            "PROVIDE" : { "variable_added" : { "redirect_url" : "redirect URL" } }
          }
        },
        { "redirect" : { "url" : "\\u003C?php \\r\\necho $redirect_url;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_relation_mandatory_optional_set'] = entity_import('rules_config', '{ "rules_relation_mandatory_optional_set" : {
      "LABEL" : "Relation_Mandatory_Optional_Set",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "list_product" : { "label" : "products", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : [
        { "php_eval" : { "code" : "dsm(\\u0027here\\u0027);\\r\\ndrupal_add_js(\\u0027jQuery(document).ready(function () { alert(\\u0022Hello!\\u0022); });\\u0027, array(\\u0027type\\u0027 =\\u003E \\u0027inline\\u0027, \\u0027scope\\u0027 =\\u003E \\u0027footer\\u0027, \\u0027weight\\u0027 =\\u003E 1));" } }
      ]
    }
  }');
  $items['rules_select_product_group_main_items'] = entity_import('rules_config', '{ "rules_select_product_group_main_items" : {
      "LABEL" : "Product Group (Select - Main Products)",
      "PLUGIN" : "action set",
      "REQUIRES" : [ "php", "rules" ],
      "USES VARIABLES" : { "prdgroup_selected_main" : {
          "label" : "ProductGroup Selected Main Products",
          "type" : "list\\u003Cnode\\u003E"
        }
      },
      "ACTION SET" : [
        { "php_eval" : { "code" : "global $user;\\r\\n\\r\\n$productNids = array_keys($prdgroup_selected_main);\\r\\n$path= explode(\\u0027\\/\\u0027, current_path());\\r\\n$productGroupNid = $path[3];\\r\\n\\r\\nforeach($productNids as $productNid) {\\r\\n    $node = new stdClass();\\r\\n    $node-\\u003Etype = \\u0027productgroupmainselected\\u0027;\\r\\n    $node-\\u003Estatus = 1;\\r\\n    $node-\\u003Euid = $user-\\u003Euid;\\r\\n    $node-\\u003Etitle = \\u0027productgroupmainselected\\u0027;\\r\\n    $node-\\u003Efield_ref_product[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $productNid;\\r\\n    $node-\\u003Efield_ref_product_group[\\u0027und\\u0027][0][\\u0027nid\\u0027] = $productGroupNid;\\r\\n    $node-\\u003Elanguage = \\u0027und\\u0027;\\r\\n    node_save($node); \\r\\n}\\r\\n" } },
        { "redirect" : { "url" : "\\u003C?php\\r\\n$path = explode(\\u0027\\/\\u0027, current_path());\\r\\n$redirectPath = \\u0027relation\\/productgroup\\/edit\\/\\u0027 . $path[3] . \\u0027\\/1#quickset-relation_manager=4\\u0027;\\r\\necho $redirectPath;\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_set_viceversa_in_product_relation_exclusiveness'] = entity_import('rules_config', '{ "rules_set_viceversa_in_product_relation_exclusiveness" : {
      "LABEL" : "Set ViceVersa in Product Relation Exclusiveness",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "simpleproductoffering" : "simpleproductoffering" } }
          }
        },
        { "php_eval" : { "code" : "$productTypeTerm = taxonomy_term_load($node-\\u003Efield_product_type[\\u0027und\\u0027][0][\\u0027tid\\u0027]);\\r\\nif($producTypeTerm-\\u003Ename != \\u0027Main\\u0027) {\\r\\n   return TRUE;\\r\\n} else {\\r\\n  return FALSE;\\r\\n}\\r\\n" } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "set_exclusiveness_check($node_unchanged, $node);\\r\\n\\r\\n" } }
      ]
    }
  }');
  $items['rules_show_views_detail_info'] = entity_import('rules_config', '{ "rules_show_views_detail_info" : {
      "LABEL" : "show views detail info",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "php", "rules", "rb_views" ],
      "ON" : [ "rb_views_event_view_execute" ],
      "DO" : [ { "php_eval" : { "code" : "dsm($view);" } } ]
    }
  }');
  $items['rules_temp_update_status_alarm'] = entity_import('rules_config', '{ "rules_temp_update_status_alarm" : {
      "LABEL" : "temp_update_status_alarm",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "actionpricechargefactors" : "actionpricechargefactors" } }
          }
        }
      ],
      "DO" : [
        { "drupal_message" : { "message" : "[node:title] ([node:nid]) is updated " } }
      ]
    }
  }');
  $items['rules_test'] = entity_import('rules_config', '{ "rules_test" : { "LABEL" : "test", "PLUGIN" : "rule", "DO" : [] } }');
  $items['rules_touch_product_after_node_create'] = entity_import('rules_config', '{ "rules_touch_product_after_node_create" : {
      "LABEL" : "Touch_Product_After_Node_Create",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "NOT node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "prdattributebenefit" : "prdattributebenefit",
                "prdattributeprefixrange" : "prdattributeprefixrange",
                "prdattributeprefixrangeallowed" : "prdattributeprefixrangeallowed",
                "prdattributeprefixrangenotallowe" : "prdattributeprefixrangenotallowe",
                "prdcounterlist" : "prdcounterlist",
                "prdnonusagerechargeblock" : "prdnonusagerechargeblock",
                "prdnonusagerecurringbonusscheme" : "prdnonusagerecurringbonusscheme",
                "prdnonusagerecurringchargescheme" : "prdnonusagerecurringchargescheme",
                "simpleproductoffering" : "simpleproductoffering"
              }
            }
          }
        }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\/\\/dsm(\\u0027Touch Rule Executed!!\\u0027);\\r\\n\\/\\/dsm($node,\\u0027touch node\\u0027);\\r\\nnode_save_handler_to_touch_product($node);" } }
      ]
    }
  }');
  $items['rules_touch_product_after_node_delete'] = entity_import('rules_config', '{ "rules_touch_product_after_node_delete" : {
      "LABEL" : "Touch_Product_After_Node_Delete",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "node_delete" ],
      "DO" : [
        { "php_eval" : { "code" : "node_delete_handler_to_touch_product($node);" } }
      ]
    }
  }');
  $items['rules_touch_product_after_node_update'] = entity_import('rules_config', '{ "rules_touch_product_after_node_update" : {
      "LABEL" : "Touch_Product_After_Node_Update",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "node_update" ],
      "DO" : [
        { "php_eval" : { "code" : "node_update_handler_to_touch_product($node,$node_unchanged);" } }
      ]
    }
  }');
  $items['rules_user_account_'] = entity_import('rules_config', '{ "rules_user_account_" : {
      "LABEL" : "User Account \\uc800\\uc7a5 \\uc2dc ",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "user_update" ],
      "IF" : [
        { "php_eval" : { "code" : "$admin_list = array(\\u0027admin\\u0027, \\u0027realjangsun\\u0027, \\u0027youngmin\\u0027);\\r\\nif(in_array($account-\\u003Ename, $admin_list)) {\\r\\n  return TRUE;\\r\\n}" } }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "3" : "3" } } } }
      ]
    }
  }');
  $items['rules_valid_end_date_changed_for_infinity'] = entity_import('rules_config', '{ "rules_valid_end_date_changed_for_infinity" : {
      "LABEL" : "Valid End Date Changed for INFINITY",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_presave" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "vouchercardtype" : "vouchercardtype" } }
          }
        }
      ],
      "DO" : []
    }
  }');
  $items['rules_vbo_actions_on_tree'] = entity_import('rules_config', '{ "rules_vbo_actions_on_tree" : {
      "LABEL" : "VBO Actions on Tree",
      "PLUGIN" : "action set",
      "USES VARIABLES" : { "list_item" : { "label" : "list_item", "type" : "list\\u003Cnode\\u003E" } },
      "ACTION SET" : []
    }
  }');
  return $items;
}

<?php
function _backup_and_migrate_manual_file_list() {
    backup_migrate_include('destinations');
    drupal_add_css(drupal_get_path('module', 'backup_migrate') . '/backup_migrate.css');

    $destination_id = 'manual';
    
    $rows = $sort = array();
    
    if ($destination = backup_migrate_get_destination($destination_id)) {
        // Refresh the file listing cache if requested.
        if (isset($_GET['refresh'])) {
            $destination -> file_cache_clear();
            drupal_goto($_GET['q']);
        }

        drupal_set_title(t('@title Files', array('@title' => $destination -> get_name())));
        $headers = array( array('data' => t('Filename'), 'field' => 'filename'), array('data' => t('Date'), 'field' => 'filetime'), array('data' => t('Age'), 'field' => 'filetime', 'sort' => 'desc'), array('data' => t('Size'), 'field' => 'filesize'), );

        $sort_order = tablesort_get_order($headers);
        $sort_key = $sort_order['sql'] ? $sort_order['sql'] : 'filetime';
        $sort_dir = tablesort_get_sort($headers) == 'desc' ? SORT_DESC : SORT_ASC;

        $files = $destination -> list_files();

        $i = 0;
        $ops = 0;
        foreach ((array)$files as $file) {
            $info = $file -> info();
            $operations = $destination -> get_file_links($file -> file_id());
            
            $description = '';
            // Add the description as a new row.
            if (!empty($info['description'])) {
                $description = ' <div title="' . check_plain($info['description']) . '" class="backup-migrate-description">' . $info['description'] . '</div>';
            }

            // Show only files that can be restored from.
            if ($file -> is_recognized_type()) {
                $sort[] = $info[$sort_key];
                $rows[] = array_merge(array(check_plain($info['filename']) . $description, format_date($info['filetime'], 'small'), format_interval(time() - $info['filetime'], 1), format_size($info['filesize']), ), $operations);
            }
            $ops = max($ops, count($operations));
        }

        // Add the operations if any
        if ($ops) {
            $headers[] = array('data' => t('Operations'), 'colspan' => $ops);
        }

        array_multisort($sort, $sort_dir, $rows);

        if ($rows) {
            $out = theme('table', array('header' => $headers, 'rows' => $rows));
        } else {
            $out = t('There are no backup files to display.');
        }
        if ($destination -> cache_files && $destination -> fetch_time) {
            drupal_add_css(drupal_get_path('module', 'backup_migrate') . '/backup_migrate.css');
            $out .= '<div class="backup-migrate-cache-time">' . t('This listing was fetched !time ago. !refresh', array('!time' => format_interval(time() - $destination -> fetch_time, 1), '!refresh' => l(t('fetch now'), $_GET['q'], array('query' => array('refresh' => 'true'))))) . '</div>';
        }
        return $out;
    }
    drupal_goto(BACKUP_MIGRATE_MENU_PATH . "/destination");
}

function _get_vocabulary_name($contentType, $productNode, $serviceType = NULL) {

    $reserved_voca_name = array();
    $reserved_voca_name['simpleproductoffering'] = array('Cross' => 'tpl_default_tree_cross_main', 'IPTV' => 'tpl_default_tree_iptv', 'Mobile' => 'tpl_default_tree_mobile', 'Broadband' => 'tpl_default_tree_broadband', 'VoIP' => 'tpl_default_tree_voip', 'Satellite' => 'tpl_default_tree_satellite', 'Dummy' => 'tpl_default_tree_dummy', );
    $reserved_voca_name['tariffplan'] = array('Voice' => 'tpl_tariffplan_voice', 'SMS' => 'tpl_tariffplan_sms', 'Data' => 'tpl_tariffplan_data', 'MMS' => 'tpl_tariffplan_mms', 'CRBT' => 'tpl_tariffplan_crbt', 'Loyalty Point' => 'tpl_tariffplan_loyalty_point_deduct', 'VOD' => 'tpl_tariffplan_vod', );

    //load taxonomy
    $serviceDomainTerm = taxonomy_term_load($productNode -> field_service_type_of_provider['und'][0]['tid']);
    $serviceDomain = $serviceDomainTerm -> name;

    $productTypeTerm = taxonomy_term_load($productNode -> field_product_type['und'][0]['tid']);
    $productType = $productTypeTerm -> name;

    $billingTypeTerm = taxonomy_term_load($productNode -> field_billing_type['und'][0]['tid']);
    $billingType = $billingTypeTerm -> name;

    switch($contentType) {
        case 'simpleproductoffering' :
            $voca_name = $reserved_voca_name[$contentType][$serviceDomain];
            break;
        case 'tariffplan' :
            $voca_name = $reserved_voca_name[$contentType][$serviceType];
            break;
    }
    return $voca_name;
}

function _condition_select_form($form, &$form_state) {

    $form['condition_type'] = array('#type' => 'select', '#title' => t('Condition Type'), '#options' => array('==SELECT==', 'common' => array('conditioncommoncounterfactors' => 'Counter'), 'what' => array('conditionwhaturlgroupfactors' => 'URLGroup', 'conditionwhatqos' => 'QoS', 'conditionwhatcustomfactors' => 'Custom'), 'when' => array('conditionwhendayfactors' => 'Day', 'conditionwhendurationfactors' => 'Duration', 'conditionwhentimeslotfactors' => 'Timeslot', 'conditionwhenweekfactors' => 'Week', 'conditionwhencustomfactors' => 'Custom'), 'where' => array('conditionwherecountryfactors' => 'Country', 'conditionwherenetworkfactors' => 'Network', 'conditionwherezonefactors' => 'Zone', 'conditionwherecustomfactors' => 'Custom'), 'Who' => array('conditionwhomemberfactors' => 'Member', 'conditionwhonumberfactors' => 'Number', 'conditionwhoprefixfactors' => 'Prefix', 'conditionwhocustomfactors' => 'Custom')), '#ajax' => array('callback' => 'ajax_condition_select_form_callback', 'wrapper' => 'condition_form_wrapper', ), '#description' => t('Select a type of condition for the rule.'), );

    return $form;
}

function ajax_condition_select_form_callback($form, $form_state) {

    $condition_type = $form_state['values']['condition_type'];
    $current_path = current_path();
    $rule_nid = $form_state['rule_nid'];

    $rule = node_load($rule_nid);

    if ($rule -> type == 'rule') {
        if (isset($form_state['parent_name'])) {
            $redirect_url = 'designer/rules/' . $rule_nid . '/conditions/add/' . $condition_type;
        } else {
            $redirect_url = 'common/rules/' . $rule_nid . '/conditions/add/' . $condition_type;
        }
    } else {
        $redirect_url = 'common/number_sp_rule/' . $rule_nid . '/conditions/add/' . $condition_type;
    }
    // $redirect_url = $condition_type;

    ctools_include('ajax');
    ctools_add_js('ajax-responder');
    $commands[] = ctools_ajax_command_redirect($redirect_url);
    print ajax_render($commands);
    exit ;
}

function _load_node_form($buildType, $nodeType = NULL, $nid = NULL, $params = NULL) {
    global $user;
    module_load_include('inc', 'node', 'node.pages');

    switch($buildType) {
        case 'create' :
            if ($nodeType == NULL) {
                //set error message
                drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
                return;
            }
            $node = new StdClass();
            $node -> uid = $user -> uid;
            $node -> type = $nodeType;
            $node -> language = 'und';

            //numbering plan idd duplex link
            if (isset($params['numberingplan_idd_nid'])) {
                $node -> field_ref_numberingplan_idd['und'][0]['nid'] = $params['numberingplan_idd_nid'];
            }
            //numbering plan domestic duplex link
            if (isset($params['numberingplan_domestic_nid'])) {
                $node -> field_ref_numberingplan_domestic['und'][0]['nid'] = $params['numberingplan_domestic_nid'];
            }

            node_object_prepare($node);
            break;
        case 'edit' :
            if ($nid == NULL) {
                //set error message
                drupal_set_message($message = 'Can not find nid for Node.', $type = 'error');
                return;
            }
            $node = node_load($nid);
            $nodeType = $node -> type;
            break;
        default :
            //set error message
            drupal_set_message($message = 'Can not find buildType.', $type = 'error');
            return;
            break;
    }

    $form_state = array();

    if (!empty($params)) {
        $paramKeys = array_keys($params);
        $paramValues = array_values($params);
        $numberOfParams = count($paramKeys);
        for ($i = 0; $i < $numberOfParams; $i++) {
            $form_state[$paramKeys[$i]] = $paramValues[$i];
        }
    }

    $form_state['build_info']['args'] = array($node);
    $formName = $nodeType . '_node_form';
    $form = drupal_build_form($formName, $form_state);

    $output = drupal_render($form);
    return $output;
}

function make_taxonomy_view_form($form, &$form_state, $productNid, $vocabularyName) {

    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabularyName);
    //tree 를 가져올 때, sorting 되서 가져 오는 듯..
    $tree = taxonomy_get_tree($vocabulary -> vid);
    $current_path = base_path() . current_path();

    //load product
    $product = node_load($productNid);

    $event_list = array();

    $addBasicRate = FALSE;

    switch($vocabularyName) {
        case 'service_of_nonusage' :
            $temp_path = explode('/nonusage', $current_path);
            $current_path = $temp_path[0] . '/nonusage';

            $viewName = 'query_nonusage_nid_by_product_nid';

            break;

        case 'service_of_usage' :
            $temp_path = explode('/usage', $current_path);
            $current_path = $temp_path[0] . '/usage';

            $viewName = 'query_usage_nid_by_product_nid';

            $addBasicRate = TRUE;
            break;
    }

    $view = views_get_view($viewName);
    $view -> set_arguments(array('0' => $productNid));
    $view -> execute();

    $temp_array_result = $view -> result;
    foreach ($temp_array_result as $item) {
        $array_temp = objectToArray($item);
        $nid = array_shift($array_temp);
        $tid = array_shift($array_temp);
        $event_list[$tid] = $nid;
    }

    $header = array( array('data' => 'Event'), array('data' => 'Rule'), );
    $rows = array();
    foreach ($tree as $item) {
        $countDepth = $item -> depth;
        $markup = '';
        for ($i = 0; $i < $countDepth; $i++) {
            $markup = $markup . '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
        }

        if (!empty($event_list[$item -> tid])) {
            if ($addBasicRate) {
                $ruleContext = '<a href="' . $current_path . '/basic/' . $event_list[$item -> tid] . '">Rate</a>&nbsp;&nbsp;&nbsp;<a href="' . $current_path . '/additional/' . $event_list[$item -> tid] . '">Rule</a>';
            } else {
                $ruleContext = '<a href="' . $current_path . '/' . $event_list[$item -> tid] . '">Rule</a>';
            }
        } else {
            $ruleContext = '';
        }
        $rows[] = array($markup . $item -> name, $ruleContext, );

    }

    $args = array('header' => $header, 'rows' => $rows, 'sticky' => 'sticky', 'empty' => 'it is empty..', 'attributes' => array(), 'colgroups' => array(), 'caption' => '', );

    $theme_table_result = theme_table($args);

    $form['terms'] = array('#type' => 'markup', '#markup' => $theme_table_result);
    //$form = taxonomy_overview_vocabularies($form);
    return $form;
}

function _get_condition_type_human_readible($type) {

    $condition_type_1 = substr($type, 0, -7);
    // remove suffix 'factors'
    $pattern = array('/conditionwhat/', '/conditionwhen/', '/conditionwho/', '/conditionwhere/');
    $replacement = '';
    return preg_replace($pattern, $replacement, $condition_type_1);
}

function _load_node_form_without_render($buildType, $nodeType = NULL, $nid = NULL, $params = NULL) {
    global $user;
    module_load_include('inc', 'node', 'node.pages');

    switch($buildType) {
        case 'create' :
            if ($nodeType == NULL) {
                //set error message
                drupal_set_message($message = 'Can not find nodeType.', $type = 'error');
                return;
            }
            $node = new StdClass();
            $node -> uid = $user -> uid;
            $node -> type = $nodeType;
            $node -> language = 'und';

            //numbering plan duplex link
            if (isset($params['numberingplan_idd_nid'])) {
                $node -> field_ref_numberingplan_idd['und'][0]['nid'] = $params['numberingplan_idd_nid'];
            }

            node_object_prepare($node);
            break;
        case 'edit' :
            if ($nid == NULL) {
                //set error message
                drupal_set_message($message = 'Can not find nid for Node.', $type = 'error');
                return;
            }
            $node = node_load($nid);
            break;
        default :
            //set error message
            drupal_set_message($message = 'Can not find buildType.', $type = 'error');
            return;
            break;
    }

    $form_state = array();

    if (!empty($params)) {
        $paramKeys = array_keys($params);
        $paramValues = array_values($params);
        $numberOfParams = count($paramKeys);
        for ($i = 0; $i < $numberOfParams; $i++) {
            $form_state[$paramKeys[$i]] = $paramValues[$i];
        }
    }

    $form_state['build_info']['args'] = array($node);
    $formName = $nodeType . '_node_form';
    $form = drupal_build_form($formName, $form_state);

    return $form;
}

function numberingplan_domestic_view_form($form, &$form_state) {
    $view = views_get_view('list_numberingplan_domestic_ratinggroup');
    $view -> execute_display('panel_pane_2', array('0' => $form_state['param']['plan_nid']));
    $output = $view -> render();

    $form['view'] = array('#type' => 'markup', '#markup' => $output, );
    return $form;
}

function depositscheme_view_form($form, &$form_state) {
    $output = '<div><h2>Deposit Scheme Factors</h2></div>';
    $view = views_get_view('list_depositschemefactors');
    $view -> execute_display('panel_pane_7', array('0' => $form_state['param']['depositscheme_nid']));
    $output .= $view -> render();

    $output .= '<hr>';
    $output .= '<div><h2>Deposit Scheme Adjustment</h2></div>';
    $view = views_get_view('list_depositschemeadjustment');
    $view -> execute_display('panel_pane_2', array('0' => $form_state['param']['depositscheme_nid']));
    $output .= $view -> render();

    $form['view'] = array('#type' => 'markup', '#markup' => $output, );

    return $form;
}

function thresholdscheme_view_form($form, &$form_state) {
    $view = views_get_view('list_thresholdschemefactors');
    $view -> execute_display('panel_pane_2', array('0' => $form_state['param']['thresholdscheme_nid']));
    $output .= $view -> render();

    $form['view'] = array('#type' => 'markup', '#markup' => $output, );

    return $form;
}

function numberingplan_idd_view_form($form, &$form_state) {
    $view = views_get_view('list_numberingplan_idd_ratinggroup');
    $view -> execute_display('panel_pane_2', array('0' => $form_state['param']['plan_nid']));
    $output = $view -> render();

    $form['view'] = array('#type' => 'markup', '#markup' => $output, );
    return $form;
}

function roamingplan_view_form($form, &$form_state) {
    $view = views_get_view('list_roaming_plan_ratinggroup');
    $view -> execute_display('panel_pane_2', array('0' => $form_state['param']['plan_nid']));
    $output = $view -> render();

    $form['view'] = array('#type' => 'markup', '#markup' => $output, );
    return $form;
}

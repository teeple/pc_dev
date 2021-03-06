<?php
/**
 * @file
 */

/**
 * Menu callback: runs cron and returns to status-report page.
 */
function ultimate_cron_run_cron() {
  // Run the cron and return
  ultimate_cron_cron_run(TRUE);
  drupal_goto('admin/reports/status');
}

/**
 * Settings form.
 */
function ultimate_cron_settings_form() {
  $form = array();
  $advanced_help_enabled = module_exists('advanced_help');
   // General settings -----------------------------------
  $form['general'] = array(
    '#title' => t('General'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );
  $form['general']['ultimate_cron_handle_prefix'] = array(
    '#title' => t("Handle prefix"),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_handle_prefix', ULTIMATE_CRON_HANDLE_PREFIX),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'handle_prefix',
                              'type' => 'icon')
                      ) : '') . t('Handle prefix. Use with care. Changing this from the default value ("' . ULTIMATE_CRON_HANDLE_PREFIX . '"), might break compatibility with 3rd party modules. Also, make sure that no jobs are running when changing this.'),
  );
  $form['general']['ultimate_cron_simultaneous_connections'] = array(
    '#title' => t("Simultaneous connections"),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_simultaneous_connections', ULTIMATE_CRON_SIMULTANEOUS_CONNECTIONS),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'simultaneous_connections',
                              'type' => 'icon')
                      ) : '') . t('Maximum number of simultaneous connections'),
  );
  $form['general']['ultimate_cron_rule'] = array(
    '#title' => t("Default rule"),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'rules',
                              'type' => 'icon')
                      ) : '') . t('Enter the default fallback rule'),
  );
  $form['general']['ultimate_cron_cleanup_log'] = array(
    '#title' => t("Clean up logs older than X seconds"),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_cleanup_log', ULTIMATE_CRON_CLEANUP_LOG),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'cleanup_log',
                              'type' => 'icon')
                      ) : '') . t('Enter maximum age, in seconds, for log entries'),
  );
  $form['general']['ultimate_cron_catch_up'] = array(
    '#title' => t('Default catch up'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_catch_up', ULTIMATE_CRON_CATCH_UP),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'catch_up',
                              'type' => 'icon')
                      ) : '') . t('Time in seconds to catch up, if a job could not be run within its time frame. (blank = ' . variable_get('ultimate_cron_catch_up', ULTIMATE_CRON_CATCH_UP) . ')'),
  );
  $form['general']['ultimate_cron_queue_polling_latency'] = array(
    '#title' => t("Queue polling latency"),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_queue_polling_latency', ULTIMATE_CRON_QUEUE_POLLING_LATENCY),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'polling_latency',
                              'type' => 'icon')
                      ) : '') . t('Queue polling latency in miliseconds. Leave blank to disable continuous processing of queues.'),
  );
  $form['general']['ultimate_cron_queue_lease_time'] = array(
    '#title' => t('Queue lease time'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ultimate_cron_queue_lease_time', ULTIMATE_CRON_QUEUE_LEASE_TIME),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'queue_lease_time',
                              'type' => 'icon')
                      ) : '') . t('Time in seconds to keep lock on claimed item'),
  );
  $methods = module_invoke_all('service_group');
  $options = ultimate_cron_get_service_groups();
  foreach ($options as $key => &$value) {
    $value = (empty($value['description']) ? $key : $value['description']) . ' (' . join(',', $value['hosts']) . ') : ' . $methods['methods'][$value['method']];
  }
  $form['general']['ultimate_cron_service_group'] = array(
    '#type' => 'select',
    '#title' => t('Service group'),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'service_group',
                              'type' => 'icon')
                      ) : '') . t('Service group to use for all jobs. See Background Process !url for managing service groups.', array('!url' => l(t('settings'), 'admin/config/system/background-process'))),
    '#options' => $options,
    '#default_value' => variable_get('ultimate_cron_service_group', ULTIMATE_CRON_SERVICE_GROUP),
  );
  $form['general']['ultimate_cron_poorman'] = array(
    '#title' => t("Poormans cron"),
    '#type' => 'checkbox',
    '#default_value' => variable_get('ultimate_cron_poorman', ULTIMATE_CRON_POORMAN),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'poorman',
                              'type' => 'icon')
                      ) : '') . t('Keep background process alive, checking for cron every minute.'),
  );

  $form = system_settings_form($form);
  return $form;
}

/**
 * Function settings form.
 */
function ultimate_cron_function_settings_form($form, &$form_state, $function) {
  $hooks = ultimate_cron_get_hooks();
  if (!isset($hooks[(string)$function])) {
    drupal_not_found();
    exit;
  }

  // Load settings
  $hook = $hooks[$function];
  $conf = ultimate_cron_get_settings($function);
  $conf += _ultimate_cron_default_settings();

  // Setup form
  drupal_set_title(check_plain($function));
  $form = array();
  $advanced_help_enabled = module_exists('advanced_help');

   // General settings -----------------------------------
  $form['function'] = array(
    '#type' => 'value',
    '#value' => $function,
  );
  $form['general'] = array(
    '#title' => t('General'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );
  $form['general']['enabled'] = array(
    '#title' => t('Enabled'),
    '#type' => 'checkbox',
    '#default_value' => $conf['enabled'],
    '#description' => t('Enable this cron job.'),
  );
  $form['general']['rules'] = array(
    '#title' => t('Rules'),
    '#type' => 'textfield',
    '#default_value' => implode(';', $conf['rules']),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'rules',
                              'type' => 'icon')
                      ) : '') . t('Semi-colon separated list of rules for this job. (blank = ' . implode(';', $hook['settings']['rules']) . ')'),
  );
  $form['general']['catch_up'] = array(
    '#title' => t('Catch up'),
    '#type' => 'textfield',
    '#default_value' => $conf['catch_up'],
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'catch_up',
                              'type' => 'icon')
                      ) : '') . t('Time in seconds to catch up, if a job could not be run within its time frame. (blank = ' . variable_get('ultimate_cron_catch_up', ULTIMATE_CRON_CATCH_UP) . ')'),
  );
  if (strpos($function, 'ultimate_cron_queue_') === 0) {
    $form['general']['queue_lease_time'] = array(
      '#title' => t('Queue lease time'),
      '#type' => 'textfield',
      '#default_value' => $conf['queue_lease_time'],
      '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                                'module' => 'ultimate_cron',
                                'topic' => 'queue_lease_time',
                                'type' => 'icon')
                        ) : '') . t('Time in seconds to keep lock on claimed item. (blank = ' . variable_get('ultimate_cron_queue_lease_time', ULTIMATE_CRON_QUEUE_LEASE_TIME) . ')'),
    );
  }

  $methods = module_invoke_all('service_group');
  $service_groups = $options = ultimate_cron_get_service_groups();
  foreach ($options as $key => &$value) {
    $value = (empty($value['description']) ? $key : $value['description']) . ' (' . join(',', $value['hosts']) . ') : ' . $methods['methods'][$value['method']];
  }
  $options += array(
    NULL => 'Ultimate Cron service group (' . join(',', $service_groups[variable_get('ultimate_cron_service_group', ULTIMATE_CRON_SERVICE_GROUP)]['hosts']) . ') : ' . $methods['methods'][$service_groups[variable_get('ultimate_cron_service_group', ULTIMATE_CRON_SERVICE_GROUP)]['method']]
  );
  $form['general']['service_group'] = array(
    '#type' => 'select',
    '#title' => t('Service group'),
    '#description' => ($advanced_help_enabled ? theme('advanced_help_topic', array(
                              'module' => 'ultimate_cron',
                              'topic' => 'service_group',
                              'type' => 'icon')
                      ) : '') . t('Service group to use for this job. See Background Process !url for managing service groups.', array('!url' => l(t('settings'), 'admin/config/system/background-process'))),
    '#options' => $options,
    '#default_value' => isset($conf['service_group']) ? $conf['service_group'] : NULL,
  );

  $form['buttons'] = array(
    '#weight' => 1000,
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  $form['#redirect'] = 'admin/config/system/cron';

  return $form;
}

/**
 * Validate handler for function settings.
 */
function ultimate_cron_function_settings_form_validate($form, &$form_state) {
  $conf =& $form_state['values']['general'];
  $conf['rules'] = trim($conf['rules']);
  $conf['rules'] = $conf['rules'] ? explode(';', $conf['rules']) : array();

  if ($conf['rules']) {
    foreach ($conf['rules'] as &$rule) {
      $rule = trim($rule);
      if (!ultimate_cron_validate_rule($rule)) {
        form_set_error('rules', t('Invalid rule.'));
      }
    }
  }
  else {
    unset($conf['rules']);
  }
}

/**
 * Submit handler for function settings.
 */
function ultimate_cron_function_settings_form_submit($form, &$form_state) {
  $conf =& $form_state['values']['general'];
  ultimate_cron_set_settings($form_state['values']['function'], $conf);
  unset($form_state['storage']);
}

/**
 * Page overviewing cron jobs.
 */
function ultimate_cron_view_page($status = NULL) {
  require_once 'CronRule.class.php';
  drupal_add_css(drupal_get_path('module', 'ultimate_cron') . '/css/ultimate_cron.admin.css');
  drupal_add_js(drupal_get_path('module', 'ultimate_cron') . '/js/ultimate_cron.js');

  if (module_exists('nodejs')) {
    drupal_add_js(array(
      'ultimate_cron' => array(
        'processes' => new stdClass(),
        'skew' => 0,
        'handle_prefix' => variable_get('ultimate_cron_handle_prefix', ULTIMATE_CRON_HANDLE_PREFIX),
      ),
    ), 'setting');
    nodejs_send_content_channel_token('ultimate_cron');
    nodejs_send_content_channel_token('background_process');
    nodejs_send_content_channel_token('progress');
    drupal_add_js(drupal_get_path('module', 'ultimate_cron') . '/js/nodejs.ultimate_cron.js');
  }

  module_load_install('ultimate_cron');
  $requirements = ultimate_cron_requirements('runtime');
  if ($requirements['ultimate_cron']['severity'] != REQUIREMENT_OK) {
    drupal_set_message($requirements['ultimate_cron']['value'], 'error');
    drupal_set_message($requirements['ultimate_cron']['description'], 'error');
  }

  // Get hooks and their data
  $data = _ultimate_cron_preload_cron_data();
  $hooks = ultimate_cron_get_hooks();

  $modules = array();
  foreach ($hooks as $function => $hook) {
    $hook['settings'] = $data[$function]['settings'] + $hook['settings'];
    $hook['background_process'] = $data[$function]['background_process'];
    $hook['log'] = ultimate_cron_get_log($function);
    $modules[$hook['module']][$function] = $hook;
  }

  $headers = array('', t('Module'), t('Function'), t('Rules'), t('Start'), t('Duration'), t('Status'), array('colspan' => 3, 'data' => ''), l(t('Run all'), 'admin/reports/status/run-cron', array('query' => drupal_get_destination())));
  $output = '';

  $rows = array();

  $handle_prefix = variable_get('ultimate_cron_handle_prefix', ULTIMATE_CRON_HANDLE_PREFIX);

  $overview = array();
  $overview['running'] = 0;
  $overview['success'] = 0;
  $overview['info'] = 0;
  $overview['warning'] = 0;
  $overview['error'] = 0;


  // Used for JS encodeURIComponent emulation
  $revert = array('%21'=>'!', '%2A'=>'*', '%27'=>"'", '%28'=>'(', '%29'=>')');

  foreach ($modules as $module => $hooks) {
    foreach ($hooks as $function => $hook) {
      // Setup settings
      $conf = $hook['settings'];
      $rules = $hook['settings']['rules'];
      $cron = new CronRule();
      $parsed_rules = array();
      foreach ($rules as $rule) {
        $cron->rule = $rule;
        $cron->offset = $hook['delta'];
        $parsed_rules[] = $cron->parseRule();
      }

      // Setup process
      $process = $hook['background_process'];
      $service_host = empty($process->service_host) ? t('N/A') : $process->service_host;

      // Setup log
      $log = $hook['log'];
      if (!$log) {
        $log = array(
          'severity' => -1,
          'status' => NULL,
          'start' => NULL,
          'end' => NULL,
        );
      }
      $severity_type = $log['severity'] < 0 ? 'success' : ($log['severity'] >= WATCHDOG_NOTICE ? 'info' : ($log['severity'] >= WATCHDOG_WARNING ? 'warning' : 'error'));
      $css_status = !empty($process) ? 'running' : $severity_type;
      $short_msg = $log['severity'];
      $msg = !empty($log['msg']) ? $log['msg'] : t('No errors');

      $duration = '';
      if ($process) {
        $overview['running']++;
        $log['previous_start'] = $log['start'];
        $log['previous_end'] = $log['end'];
        $log['start'] = $process->start;
        if ($process->status == BACKGROUND_PROCESS_STATUS_RUNNING) {
          $log['end'] = microtime(TRUE);
        }
        else {
          $log['end'] = NULL;
        }
        $progress = progress_get_progress($handle_prefix . $function);
        if ($progress && $progress->progress > 0) {
          $duration .= sprintf(" (%d%%)", $progress->progress * 100);
        }
      }

      $overview[$severity_type]++;
      $link_configure = '';
      if (!empty($hook['configure'])) {
        $link_configure = _ultimate_cron_l('Settings', $hook['configure']);
      }

      $link_unlock = '';
      if ($process) {
        $link_unlock = _ultimate_cron_l('Unlock', 'background-process/unlock/' . $process->handle);
      }

      $link_settings = _ultimate_cron_l('Schedule', 'admin/config/system/cron/settings/' . $function);
      $link_execute = _ultimate_cron_l('Run', 'admin/ultimate-cron/service/start/' . $function);
      $link_log = _ultimate_cron_l('Log', 'admin/reports/cron/' . $function);

      $enable = !empty($conf) && empty($conf['enabled']);
      $link_toggle = _ultimate_cron_l($enable ? 'Enable' : 'Disable', 'admin/ultimate-cron/service/' . ($enable ? 'enable' : 'disable') . '/' . $function);

      $data = array(
        array('class' => $enable ? 'ultimate-cron-admin-enable' : 'ultimate-cron-admin-disable'),
        array('class' => 'ultimate-cron-admin-module'),
        array('class' => 'ultimate-cron-admin-function'),
        array('class' => 'ultimate-cron-admin-rules'),
        array('class' => 'ultimate-cron-admin-start'),
        array('class' => 'ultimate-cron-admin-end'),
        array('class' => 'ultimate-cron-admin-status ultimate-cron-admin-status-' . $css_status),
        array('class' => 'ultimate-cron-admin-settings'),
        array('class' => 'ultimate-cron-admin-configure'),
        array('class' => 'ultimate-cron-admin-log'),
        array('class' => $process ? 'ultimate-cron-admin-unlock' : 'ultimate-cron-admin-execute'),
      );
      $data[0]['data'] = $link_toggle;
      $data[0]['title'] = $enable ? t('Enable') : t('Disable');
      $data[1]['data'] = ultimate_cron_module_name($module);
      $data[2]['data'] = $hook['description'];
      $data[2]['title'] = $function;
      $data[3]['data'] = join("<br/>", $rules);
      $data[3]['title'] = join("\n", $parsed_rules);
      $data[4]['data'] = $log['start'] ? format_date((int)$log['start'], 'custom', 'Y-m-d H:i:s') : t('Never');
      $data[5]['data'] = $log['end'] ? gmdate('H:i:s', (int)($log['end'] - $log['start'])) . $duration : ($process ? t('Starting') : t('N/A'));
      $finish = !empty($log['previous_end']) ? $log['previous_end'] : $log['end'];
      $data[5]['title'] = t('Previous run finished @ !timestamp', array(
        '!timestamp' => $finish ? format_date((int)$finish, 'custom', 'Y-m-d H:i:s') : t('N/A')
      ));
      if (!empty($log['previous_start'])) {
        $data[4]['title'] = t('Previous run started @ !timestamp', array(
          '!timestamp' => format_date((int)$log['previous_start'], 'custom', 'Y-m-d H:i:s'),
        ));
        $data[5]['title'] .= ' - ' . t('Run time: !duration', array(
          '!duration' => gmdate('H:i:s', (int)($log['previous_end'] - $log['previous_start'])) . $duration,
        ));
      }
      if ($process) {
        $data[6]['data'] = '<span>' . t('Running') . '</span>';
        $data[6]['title'] = t('Running on @host', array('@host' => $service_host));
      }
      else {
        $data[6]['data'] = '<span>' . $short_msg . '</span>';
        $data[6]['title'] = strip_tags(html_entity_decode($msg, ENT_QUOTES));
      }
      $data[7]['data'] = $link_settings;
      $data[7]['title'] = t('Schedule');
      $data[8]['data'] = $link_configure;
      $data[8]['title'] = $link_configure ? t('Settings') : '';
      $data[9]['data'] = $link_log;
      $data[9]['title'] = t('Log');
      $data[10]['data'] = ($process ? $link_unlock : $link_execute);
      $data[10]['title'] = ($process ? t('Unlock') : t('Run'));

      $rows[(int)$enable][] = array(
        'class' => array('row-' . str_replace('%', '_', strtr(rawurlencode($function), $revert))),
        'data' => $data,
        'style' => ($status && $status != 'all' && ($css_status != $status) ? 'display: none' : ''),
      );
    }
  }

  if (!empty($rows[0])) {
    $output .= theme('table', array(
      'header' => $headers,
      'rows' => $rows[0],
      'attributes' => array('id' => array('ultimate-cron-view'))
    ));
    $output .= '<div class="clear-block"></div>';
  }
  if (!empty($rows[1])) {
    $headers = array('', t('Module'), t('Function'), t('Rules'), t('Start'), t('Duration'), t('Status'), array('colspan' => 4, 'data' => ''));
    $output .= theme('table', array(
      'header' => $headers,
      'rows' => $rows[1],
      'attributes' => array('id' => array('ultimate-cron-view'))
    ));
    $output .= '<div class="clear-block"></div>';
  }

  if ($overview['running']) {
    drupal_set_message(format_plural($overview['running'],
                        '@jobs job is currently running',
                        '@jobs jobs are currently running',
                        array('@jobs' => $overview['running'])
                      ));
  }
  if ($overview['warning']) {
    drupal_set_message(format_plural($overview['warning'],
                        '@jobs job had warnings during its last run',
                        '@jobs jobs had warnings during their last run',
                        array('@jobs' => $overview['warning'])
                      ), 'warning');
  }
  if ($overview['error']) {
    drupal_set_message(format_plural($overview['error'],
                        '@jobs job had errors during its last run',
                        '@jobs jobs had errors during their last run',
                        array('@jobs' => $overview['error'])
                      ), 'error');
  }

  return $output;
}

/**
 * Function log page.
 */
function ultimate_cron_function_log_page($function) {
  $hooks = ultimate_cron_get_hooks();
  if (!isset($hooks[(string)$function])) {
    drupal_not_found();
    exit;
  }

  drupal_add_css(drupal_get_path('module', 'ultimate_cron') . '/css/ultimate_cron.admin.css');

  $header = array(
    array('data' => t('Start'), 'field' => 'start_stamp', 'sort' => 'DESC'),
    array('data' => t('End'),   'field' => 'end_stamp'),
    t('Duration'),
    t('Service host'),
    t('Status'),
    t('Message'),
  );

  drupal_set_title(check_plain($function));

  $query = db_select('ultimate_cron_log', 'l');
  $query = $query->condition('l.name', $function)
    ->extend('PagerDefault')
    ->limit(10)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->fields('l', array('lid', 'name', 'start_stamp', 'end_stamp', 'service_host', 'exec_status', 'msg', 'severity'))
    ->orderBy('l.start_stamp', 'DESC');
  $logs = $query->execute()->fetchAll();

  $handle_prefix = variable_get('ultimate_cron_handle_prefix', ULTIMATE_CRON_HANDLE_PREFIX);

  $output = '';
  $rows = array();
  if (empty($_GET['page']) && $process = background_process_get_process($handle_prefix . $function)) {
    $data = array(
      array('class' => array('ultimate-cron-admin-start')),
      array('class' => array('ultimate-cron-admin-end')),
      array('class' => array('ultimate-cron-admin-duration')),
      array('class' => array('ultimate-cron-admin-service-host')),
      array('class' => array('ultimate-cron-admin-status ultimate-cron-admin-status-running')),
      array('class' => array('ultimate-cron-admin-message')),
    );
    $duration = time() - $process->start_stamp;
    $duration = gmdate('H:i:s', (int)$duration);
    $progress = progress_get_progress($handle_prefix . $function);
    if ($progress && $progress->progress > 0) {
      $duration .= sprintf(" (%d%%)", $progress->progress * 100);
    }
    $data[0]['data'] = format_date((int)$process->start_stamp, 'custom', 'Y-m-d H:i:s');
    $data[1]['data'] = t('N/A');
    $data[2]['data'] = $duration;
    $data[3]['data'] = $process->service_host ? $process->service_host : t('N/A');
    $data[4]['data'] = '<span>' . t('running') . '</span>';
    $data[5]['data'] = '';
    $rows[] = $data;
  }

  foreach ($logs as $log) {
    $log->function = $log->name;
    $log->status = $log->exec_status;
    $log->start = $log->start_stamp;
    $log->end = $log->end_stamp;
    $severity_type = $log->severity < 0 ? 'success' : ($log->severity >= WATCHDOG_NOTICE ? 'info' : ($log->severity >= WATCHDOG_WARNING ? 'warning' : 'error'));
    $css_status = $severity_type;
    $data = array(
      array('class' => array('ultimate-cron-admin-start')),
      array('class' => array('ultimate-cron-admin-end')),
      array('class' => array('ultimate-cron-admin-duration')),
      array('class' => array('ultimate-cron-admin-service-host')),
      array('class' => array('ultimate-cron-admin-status ultimate-cron-admin-status-' . $css_status)),
      array('class' => array('ultimate-cron-admin-message')),
    );
    $data[0]['data'] = format_date((int)$log->start, 'custom', 'Y-m-d H:i:s');
    $data[1]['data'] = format_date((int)$log->end, 'custom', 'Y-m-d H:i:s');
    $data[2]['data'] = gmdate('H:i:s', (int)($log->end - $log->start));
    $data[3]['data'] = $log->service_host ? $log->service_host : t('N/A');
    $data[4]['data'] = '<span>' . $log->status . '</span>';
    $data[5]['data'] = $log->msg;
    $rows[] = $data;
  }

  $output .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ultimate-cron-view')
  ));
  $output .= theme('pager');

  return $output;
}

/**
 * Run a single function.
 *
 * @param $function
 * @return string
 *   Output to page
 */
function ultimate_cron_service_start($function) {
  $hooks = ultimate_cron_get_hooks();
  if (!isset($hooks[(string)$function])) {
    drupal_not_found();
    exit;
  }

  if ($modules = _ultimate_cron_incompatible_modules()) {
    drupal_set_message(t('%function could not start (incompatible module installed)', array('%function' => $function)), 'error');
    drupal_set_message(t('%modules is installed on the system, but is incompatible with Ultimate Cron.<br/>Please disable the conflicting modules.<br/>You might want to !url settings first.', array('%modules' => join(', ', $modules), '!url' => l(t('import'), 'admin/settings/cron/import'))), 'error');
    drupal_goto();
  }

  // When run manually don't double check the rules
  $hooks[$function]['skip_catch_up'] = TRUE;

  ultimate_cron_load_hook_data($hooks[$function]);
  $handle = ultimate_cron_run_hook($function, $hooks[$function]);

  if ($handle === FALSE) {
    drupal_set_message(t('%function could not start (already running?)', array('%function' => $function)), 'error');
  }
  elseif ($handle === NULL) {
    drupal_set_message(t('%function could not start (service unavailable)', array('%function' => $function)), 'error');
  }
  else {
    drupal_set_message(t('%function started', array('%function' => $function)));
  }

  drupal_goto();
}

/**
 * Enable/disable cron job
 * @param type $function
 * @param type $enabled
 */
function ultimate_cron_service_enable($function, $enabled) {
  $conf = ultimate_cron_get_settings($function);
  $conf['enabled'] = $enabled;
  ultimate_cron_set_settings($function, $conf);
  drupal_goto();
}

/**
 * Send a message for all running processes.
 */
function ultimate_cron_service_process_status() {
  $handle_prefix = variable_get('ultimate_cron_handle_prefix', ULTIMATE_CRON_HANDLE_PREFIX);
  $processes = array();
  $query = db_select('background_process', 'b')
    ->fields('b')
    ->condition('handle', $handle_prefix . '%', 'LIKE');
  foreach ($query->execute()->fetchAllAssoc('handle', PDO::FETCH_OBJ) as $process) {
    $process = BackgroundProcess::load($process);
    $name = preg_replace('/^' . $handle_prefix . '/', '', $process->handle);
    $processes[$name] = $process;
    $process->sendMessage('ultimateCronStatus');
  }
  return drupal_json_output(array('processes' => $processes));
}

/**
 * Import form.
 */
function ultimate_cron_import_form() {
  $form = array();
  $options = array();

  if ($options) {
    $form['import']['module'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('Module'),
      '#description' => t('Module to import settings from'),
    );
    $form['import']['submit'] = array(
      '#type' => 'submit',
      '#submit' => array('ultimate_cron_import_form_submit'),
      '#value' => t('Import'),
    );
  }
  return $form;
}

/**
 * Submit handler for import.
 */
function ultimate_cron_import_form_submit($form, &$form_state) {
}

/**
 * Helper function for links on cron list
 * @param $text
 *   Text for link
 * @param $path
 *   Path to link to
 * @return type
 */
function _ultimate_cron_l($text, $path) {
  return l(
    '<span>' . t($text) . '</span>',
    $path,
    array(
      'query' => drupal_get_destination(),
      'html' => TRUE,
    )
  );
}

<?php

function test_ajax_sample_cache_clear($id){
    ctools_include('object-cache');
    ctools_object_cache_clear('test', $id);
}

function test_ajax_sample_cache_get($id) {
    ctools_include('object-cache');
    return ctools_object_cache_get('test', $id);
}


function test_1($form, &$form_state) {

    $form_state['title'] = t('Test 1');
    $form['name1'] = array(
            '#type' => 'textfield',
            '#title' => t('Blah 1'),
            '#default_value' => $form_state['object']->name1,
            '#required' => TRUE,
            );
    $form['wrap']['test'] = array(
            '#type' => 'select',
            '#title' => t('Numbers'),
            '#options' => array(
                '1' => 'one',
                '2' => 'two',
                ),
            '#default_value' => $form_state['object']->select,
            '#ajax' => array(
                'callback' => 'test_1_callback',
                'wrapper' => 'test_1test_1',
                ),
            '#prefix' => '<div id="test_1test_1">',
            '#suffix' => '</div>',
            );

    return $form;
}

function test_1_callback($form, $form_state) {
    return $form['wrap'];
}

function test_1_submit(&$form, &$form_state) {
    $form_state['object']->name1 = $form_state['values']['name1'];
}

function test_2($form, &$form_state) {
    $form_state['title'] = t('Test 2');

    $form['name2'] = array(
            '#type' => 'textfield',
            '#title' => t('Blah 2'),
            '#default_value' => $form_state['object']->name2,
            '#required' => TRUE,
            );

    return $form;
}

function test_2_submit(&$form, &$form_state) {
    $form_state['object']->name2 = $form_state['values']['name2'];
}

function test_3($form, &$form_state) {
    $form_state['title'] = t('Test 3');

    $form['name3'] = array(
            '#type' => 'textfield',
            '#title' => t('Blah 3'),
            '#default_value' => $form_state['object']->name3,
            '#required' => TRUE,
            );

    return $form;
}

function test_3_submit(&$form, &$form_state) {
    $form_state['object']->name3 = $form_state['values']['name3'];
}

function test_ajax_sample_wizard_next(&$form_state) {
      test_ajax_sample_cache_set($form_state['object_id'], $form_state['object']);
}

function test_ajax_sample_wizard_finish(&$form_state) {
      $form_state['complete'] = TRUE;
}

function test_ajax_sample_wizard_cancel(&$form_state) {
      $form_state['cancel'] = TRUE;
}

function test_ajax_sample_test($js = NULL, $step = NULL) {

    if ($js) {
        ctools_include('modal');
        ctools_include('ajax');
        ctools_modal_add_js();
    }
    else {
        drupal_access_denied();
        drupal_exit();
    }

    $form_info = array(
            'id' => 'animals',
            'path' => "test/" . ($js ? 'ajax' : 'nojs') . "/form/%step",
            'show trail' => TRUE,
            'show back' => TRUE,
            'show cancel' => TRUE,
            'show return' => FALSE,
            'next callback' =>  'test_ajax_sample_wizard_next',
            'finish callback' => 'test_ajax_sample_wizard_finish',
            'cancel callback' => 'test_ajax_sample_wizard_cancel',
            // this controls order, as well as form labels
            'order' => array(
                'test_1' => t('Test 1'),
                'test_2' => t('Test 2'),
                'test_3' => t('Test 3'),
                ),
            // here we map a step to a form id.
            'forms' => array(
                // e.g. this for the step at wombat/create
                'test_1' => array(
                    'form id' => 'test_1'
                    ),
                'test_2' => array(
                    'form id' => 'test_2'
                    ),
                'test_3' => array(
                    'form id' => 'test_3'
                    ),
                ),
            );

    $object_id = 1;

    if (empty($step)) {
        // We reset the form when $step is NULL because that means they have
        // for whatever reason started over.
        test_ajax_sample_cache_clear($object_id);
        $step = 'test_1';
    }

    // This automatically gets defaults if there wasn't anything saved.
    $object = test_ajax_sample_cache_get($object_id);

    $form_state = array(
            'ajax' => $js,
            'object_id' => $object_id,
            'object' => &$object,
            );
    // Send this all off to our form. This is like drupal_get_form only wizardy.
    ctools_include('wizard');
    $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
    $output = drupal_render($form);

    // If $output is FALSE, there was no actual form.
    if ($js) {
        // If javascript is active, we have to use a render array.
        $commands = array();
        if ($output === FALSE || !empty($form_state['complete'])) {
            // Dismiss the modal.
            $commands[] = ajax_command_html('#ctools-sample', finish($form_state['object']));
            $commands[] = ctools_modal_command_dismiss();
        }
        else if (!empty($form_state['cancel'])) {
            // If cancelling, return to the activity.
            $commands[] = ctools_modal_command_dismiss();
        }
        else {
            $commands = ctools_modal_form_render($form_state, $output);
            dsm($commands, 'before');
        }

        $commands[0] = array(
            'command' => 'modal_display',
            'title' => 'Select condition',
            'output' => $output
        );

        dsm($commands);

        /*
        print ajax_render($commands);
        exit();
        */
    }

    return $commands;
}


<?php

/**
 * Advanced theme settings.
 */
function elegantica_form_system_theme_settings_alter(&$form, $form_state) {
    $css_color = array(
        'beige_blue' => 'Beige blue',
        'default' => 'Default',
        'fade_red' => 'Fade red',
        'green' => 'Green',
        'pink' => 'Pink',
        'navy_blue' => 'Navy blue',
        'red' => 'Red',
        'purple' => 'Purple',
        'strong_blue' => 'Strong blue',
    );

    $form['elegantica'] = array(
        '#type' => 'fieldset',
        '#title' => t('Elegantica settings')
    );

    $form['elegantica']['elegantica_color'] = array(
        '#type' => 'select',
        '#options' => $css_color,
        '#title' => t('Theme color style'),
        '#default_value' => theme_get_setting('elegantica_color', 'elegantica'),
        '#description' => t('Change theme color style'),
    );

    return $form;
}

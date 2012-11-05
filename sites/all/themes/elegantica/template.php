<?php

function elegantica_page_alter($page) {

    $viewport = array(
        '#type' => 'html_tag',
        '#tag' => 'meta',
        '#attributes' => array(
            'name' => 'viewport',
            'content' => 'width=device-width, initial-scale=1, maximum-scale=1'
        ),
    );


    $google_web_font = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#attributes' => array(
            'rel' => 'stylesheet',
            'id' => 'googleFont-css',
            'href' => 'http://fonts.googleapis.com/css?family=PT%20Sans',
            'type' => 'text/css',
            'media' => 'all',
        ),
    );
    drupal_add_html_head($google_web_font, 'google_web_font');
    drupal_add_html_head($viewport, 'viewport');
}

function elegantica_breadcrumb($variables) {
    $breadcrumb = $variables['breadcrumb'];

    if (!drupal_is_front_page()) {
        $breadcrumb[] = drupal_get_title();
    }
    if (!empty($breadcrumb)) {
        // Provide a navigational heading to give context for breadcrumb links to
        // screen-reader users. Make the heading invisible with .element-invisible.
        $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

        $output .= '<div class="breadcrumb"><p><strong><span class="default_br">' . t('You are here') . ': </span></strong>' . implode(' » ', $breadcrumb) . '</p></div>';
        return $output;
    }
}

function elegantica_preprocess_html(&$variables) {

    $path = path_to_theme();

    drupal_add_css($path . '/style.css');
    drupal_add_css($path . '/css/options.css');

    $color_setting_style = theme_get_setting('elegantica_color', 'elegantica');
    if (file_exists($path . '/bar/css/' . $color_setting_style . '.css')) {
        drupal_add_css($path . '/bar/css/' . $color_setting_style . '.css');
    }
    /** color change */
    if (!empty($_GET['color']) || !empty($_SESSION['css_color'])) {
        $color = isset($_GET['color']) ? $_GET['color'] : $_SESSION['css_color'];
        $_SESSION['css_color'] = $color;
        if (file_exists($path . '/bar/css/' . $color . '.css')) {
            drupal_add_css($path . '/bar/css/' . $color . '.css');
        }
    }
}
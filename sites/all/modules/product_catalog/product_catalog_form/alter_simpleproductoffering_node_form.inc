<?php
function _alter_simpleproductoffering_node_form(&$form, &$form_state) {
	$formDefaultValues = array();

    // product type에서 DEVICE는 선택할 수 없도록 없앤다.
    //
    unset($form['field_product_type']['und']['#options'][528]);

    // in case EDIT
    //
    $valid_for_1;
    $valid_for_2;

    $valueUseNidList = array();
    $valueUseCharTitleList = array();
    $valueUseCustomValueList = array();

    // 일단 characteristic은 없애본다. 향후에 좀 더 심플하게 생각해보자.
    // 
    // in case Create
    /*
    if(isset($form['nid']['#value'])) {

        $prodSpecification = node_load($form['#node']->field_r_productspecification['und'][0]['nid']);
        $valid_for_1 = substr($prodSpecification->field_valid_for['und'][0]['value'], 0, 10);
        $valid_for_2 = substr($prodSpecification->field_valid_for['und'][0]['value2'], 0, 10);

        $argValueUseNidList = $form['field_r_prodspeccharvalueuse']['und']['#default_value'];

        $view = views_get_view('query_value_nid_from_valueuse');
        $view->args[0] = join("+", $argValueUseNidList);
        $view->execute();
        $viewResult = $view->result;

        foreach($viewResult as $result){
            $customValue = '';
            if(!empty($result->field_field_custom_value)){
                $customValue = $result->field_field_custom_value[0]['raw']['value'];
            }

            $valueUseNidList[$result->node_field_data_field_r_prodspeccharvalue_nid] = $result->node_field_data_field_r_prodspeccharvalue_nid;
            $valueUseCharTitleList[$result->node_field_data_field_r_prodspeccharvalue_nid] = $result->_field_data['nid']['entity']->title;
            $valueUseCustomValueList[$result->_field_data['nid']['entity']->title] = $customValue;

        }
    }
    */

    /*
    $view = views_get_view('query_characteristic');
    $view->execute();
    $viewResult = $view->result;

    $fieldSets = array();
    $preElement ='';

    $form['characteristic'] = array('#type' => 'value');
    $charItems = array();

    foreach($viewResult as $item) {

        // (characteristic_1) node_title,
        // (char_relationship_type)field_field_char_relationship_type[0]['rendered']['#title'],
        // (charactersitc_2) node_field_data_field_r_productspecchar_title ,
        // (value_type) field_field_value_type,
        // (value) node_field_data_field_r_prodspeccharvalue_title,
        // (value relation) field_field_char_relationship_type_1[0]['rendered'][#title]

        // relation type을 가지고 있을 때,
        //
        if(isset($item->field_field_char_relationship_type[0])) {
            // in case 'AGGREGATION'
            //
            if($item->field_field_char_relationship_type[0]['rendered']['#title'] == 'AGGREGATION') {
                if(isset($fieldSets[$item->node_title])){
                    $form[$fieldSets[$item->node_title][0]][$item->node_title] = array(
                    '#type' => 'fieldset',
                    '#title' => $item->node_title,
                    );
                }else{
                    $form[$item->node_title] = array(
                    '#type' => 'fieldset',
                    '#title' => $item->node_title,
                    );
                }

                $fieldSets[$item->node_field_data_field_r_productspecchar_title][] = array(
                'title' => $item->node_title,
                'seq' => $item->field_field_char_spec_seq[0]['raw']['value']
                );
                // not in case 'AGGREGATION'
            } else {
            }

            // relation type이 없을 때,
            //
        } else {
            $elementType = '';
            // 각item 의 form element type결정
            //
            if(!isset($item->node_field_data_field_r_prodspeccharvalue_title)) {
                $elementType = 'textarea';
            } else {
                if(isset($item->field_field_char_relationship_type_1[0]))  {
                    if($item->field_field_char_relationship_type_1[0]['rendered']['#title']== 'EXCLUSIVITY')  {
                        $elementType = 'select';
                    }
                } else {
                    $elementType = 'checkboxes';
                }
            }

            // fieldset에 item이 존재할 때
            //
            if(isset($fieldSets[$item->node_title])){
                if($preElement == $item->node_title){
                    $form[$fieldSets[$item->node_title][0]['title']][$item->node_title]['#options'][$item->node_field_data_field_r_prodspeccharvalue_nid]
                    = $item->node_field_data_field_r_prodspeccharvalue_title;

                    if(array_key_exists($item->node_field_data_field_r_prodspeccharvalue_nid,$valueUseNidList)){
                        if($valueUseCharTitleList[$item->node_field_data_field_r_prodspeccharvalue_nid] == $item->node_title){

                            $form[$fieldSets[$item->node_title][0]['title']][$item->node_title]['#default_value'][] = $item->node_field_data_field_r_prodspeccharvalue_nid;
                        }
                    }
                } else {
                    $form[$fieldSets[$item->node_title][0]['title']][$item->node_title] = array(
                    '#type' => $elementType,
                    '#title' => $item->node_title,
                    '#weight' => $fieldSets[$item->node_title][0]['seq']
                    );

                    if($elementType != 'textarea') {
                        $form[$fieldSets[$item->node_title][0]['title']][$item->node_title]['#options'][$item->node_field_data_field_r_prodspeccharvalue_nid]
                        = $item->node_field_data_field_r_prodspeccharvalue_title;

                        if(array_key_exists($item->node_field_data_field_r_prodspeccharvalue_nid,$valueUseNidList)){
                            if($valueUseCharTitleList[$item->node_field_data_field_r_prodspeccharvalue_nid] == $item->node_title){
                                $form[$fieldSets[$item->node_title][0]['title']][$item->node_title]['#default_value'][] = $item->node_field_data_field_r_prodspeccharvalue_nid;
                            }
                        }
                    }else{
                        if(array_key_exists($item->node_title,$valueUseCustomValueList)){
                            $form[$fieldSets[$item->node_title][0]['title']][$item->node_title]['#default_value'] = $valueUseCustomValueList[$item->node_title];
                        }
                    }

                    $charItems[]  = array(
                    'title' => $item->node_title,
                    'type'  => $elementType,
                    'nid'   => $item->nid,
                    );
                }

            } else{
                if($preElement == $item->node_title){
                    $form[$item->node_title]['#options'][$item->node_field_data_field_r_prodspeccharvalue_nid]
                    = $item->node_field_data_field_r_prodspeccharvalue_title;

                    if(array_key_exists($item->node_field_data_field_r_prodspeccharvalue_nid,$valueUseNidList)){
                        if($valueUseCharTitleList[$item->node_field_data_field_r_prodspeccharvalue_nid] == $item->node_title){
                            $form[$item->node_title]['#default_value'][] = $item->node_field_data_field_r_prodspeccharvalue_nid;
                        }
                    }
                } else {
                    $form[$item->node_title] = array(
                    '#type' => $elementType,
                    '#title' => $item->node_title
                    );

                    if($elementType != 'textarea') {
                        $form[$item->node_title]['#options'][$item->node_field_data_field_r_prodspeccharvalue_nid]
                        = $item->node_field_data_field_r_prodspeccharvalue_title;

                        if(array_key_exists($item->node_field_data_field_r_prodspeccharvalue_nid,$valueUseNidList)){
                            if($valueUseCharTitleList[$item->node_field_data_field_r_prodspeccharvalue_nid] == $item->node_title){
                                $form[$item->node_title]['#default_value'][] = $item->node_field_data_field_r_prodspeccharvalue_nid;
                            }
                        }
                    }else{
                        if(array_key_exists($item->node_title,$valueUseCustomValueList)){
                            $form[$item->node_title]['#default_value'] = $valueUseCustomValueList[$item->node_title];
                        }
                    }
                }
            }

            $preElement = $item->node_title;

        }

    }
    */

    /*
    {
        $form['valid_for'] = array(
        '#type' => 'fieldset',
        '#title' => 'Valid For',
        '#collapsible' => TRUE,
        );

        $form['valid_for']['field_valid_for'] = array(
        '#weight' => '3',
        '#type' => 'date_popup',
        '#title' => 'From',
        '#date_format' => 'Y-m-d',
        '#date_year_range' => '-5:+5', //allow 5 years past and future
        );

        $form['valid_for']['field_valid_for_2'] = array(
        '#weight' => '4',
        '#type' => 'date_popup',
        '#title' => 'To',
        '#date_format' => 'Y-m-d',
        '#date_year_range' => '-5:+5', //allow 5 years past and future
        );

        $form['valid_for']['field_valid_for']['#default_value'] = (isset($valid_for_1))?$valid_for_1:'';
        $form['valid_for']['field_valid_for_2']['#default_value'] = (isset($valid_for_2))?$valid_for_2:'';
    }
    */

    // $form['characteristic']['#value'] = $charItems;
    // dsm($form, 'from');
    
  	$form['actions']['submit']['#submit'][] = '_offering_submit_handler';
    $form['actions']['submit']['#submit'][] = 'product_catalog_form_form_redirect_handler';
}

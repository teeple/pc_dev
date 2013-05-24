<?php

require_once( 'ocs_common.inc');

// manages Parameters that belongs to each Event
// 
class OcsParam 
{ 
    private $nid;
    private $params;
    private $options;
    private $selected;
    private $list;      // parameter name list

    private $oplist = array(
        OCS_PARAM_TYPE_STRING => array(
            '=', 'starts', 
            ),
        OCS_PARAM_TYPE_INTEGER => array(
            '=', '>', '>=', '<', '<=', 'between',
            ),
        OCS_PARAM_TYPE_ENUM => array(
            '=', 'in list',
            ),
        OCS_PARAM_TYPE_ACCOUNT_KEY => array(
            '=', '>', '>=', '<', '<=', 'between',
            ),
        OCS_PARAM_TYPE_DATE => array(
            '=', '>', '>=', '<', '<=', 'between',
            ),
        OCS_PARAM_TYPE_TIME => array(
            'between',
            ),
        OCS_PARAM_TYPE_PRODUCT_KEY => array(
            '=', 
            ),
    );

    private $date_format = array(
        'yyyy-MM-dd',
        'MM/dd/yy',
    );

    private $time_format = array(
        'HH:mm:ss',
    );

    function load( $nid)
    {
        $this->nid = $nid;

        $paramlist = array();
        $options = array();

        $node = node_load( $nid);

        foreach( $node->field_ocs_param_ref['und'] as $param) {
            $para = node_load( $param['target_id']);
    //				dpm( $para, 'parameter');

            // store select options
            $key = $nid . ':' . $param['target_id'];

            // store key
            $this->list[] = $key;

            $value = $para->title;
            $options[ $node->title][ $key] = $value;
            // store parameter info
            $paramlist[$para->nid] = $para->field_ocs_param_type['und'][0]['value'];
            $paramlist[$key] = $value;
            $paramlist[$key.':title'] = $para->title;
            if ( ! isset( $this->selected)) {
                $this->selected = $nid . ':' . $param['target_id'];
            }

            // add additional condition if the parameter is 'account key' type
            if ( $para->field_ocs_param_type['und'][0]['value'] == OCS_PARAM_TYPE_ACCOUNT_KEY) {
                $paramlist[$key.':account'] = $options[ $node->title][ $key.':account'] = t( 'counter of the @val party', array( '@val' => $value));
                $paramlist[$para->nid.':account'] = OCS_PARAM_TYPE_ACCOUNT_KEY;
                // reset the type of original parameter as string
                $paramlist[$para->nid] = OCS_PARAM_TYPE_STRING;		
            }
            else if ( $para->field_ocs_param_type['und'][0]['value'] == OCS_PARAM_TYPE_ENUM) {
                // add enum value list
                $paramlist[$key.':enum'] = json_decode( $para->field_ocs_param_value['und'][0]['value'], TRUE);
            }
        }

        $this->params = $paramlist;
        $this->options = $options;
    }

    function operators( $selected)
    {
    //	dpm( $paramlist, 'param');
    //	dpm( $selected, 'selected');

        $type = $this->type( $selected);

        return $this->oplist[$type];
    }

    function type( $selected)
    {
        $list = explode( ':', $selected);       // event:param:account or action:param:account

        if ( substr( $selected, -7) == 'account') {
            return OCS_PARAM_TYPE_ACCOUNT_KEY;
        }
        else if ( substr( $selected, -4) == 'enum') {
            return OCS_PARAM_TYPE_ENUM;
        }
        else if ( isset( $this->params[$list[1]])) {
            return $this->params[$list[1]];
        }

        return OCS_PARAM_TYPE_STRING;
    }

    // return title of the parameter
    function get_title( $param)
	{
		$title = isset( $this->params[$param.':title']) ? $this->params[$param.':title'] : 'Unknown';
		return $title;
	}
	
    // return Drupal Form
    function get_form( $param, $operator = NULL)
    {
        $type = $this->type( $param);
        $title = $this->get_title( $param);

        if ($type == OCS_PARAM_TYPE_ENUM) {
            $options = $this->get_options( $type, $param);
            //dpm( $options, 'enum');
            $form = array(
                '#type' => ($operator == 'in list') ? 'checkboxes' : 'radios',
                '#title' => $title,
                '#options' => $options,
            );
        }
        else if ( $type == OCS_PARAM_TYPE_MESSAGE) {
            $options = $this->get_options( $type, $param);
            $form = array(
                '#type' => 'select',
                '#title' => $title,
                '#options' => $options,
            	'#attributes' => array( 'style' => 'width:400px;'),
            );
        }
        else if ( $type == OCS_PARAM_TYPE_DATE) {
            $form[0] = array(
                '#type' => 'textfield',
                '#title' => $title,
                '#size' => 30,
            );
            $form[1] = array(
                '#type' => 'select',
                '#title' => 'Date format',
                '#options' => $date_format,
            );
        }
		else if ( $type == OCS_PARAM_TYPE_ACCOUNT_STATUS ||
			$type == OCS_PARAM_TYPE_COUNTER ||
			$type == OCS_PARAM_TYPE_PIVOT_DATE ||
			$type == OCS_PARAM_TYPE_DAYS_TO_ADD) {

			// get all the account status
            $options = $this->get_options( $type, $param);
            $form = array(
                '#type' => 'select',
                '#title' => $title,
                '#options' => $options,
            );
		}
        else {
            $form = array(
                '#type' => 'textfield',
                '#title' => $title,
                '#size' => 30,
            );
        }

        return $form;
    }

	function get_options( $type, $param) 
	{
		$options = array();

        if ($type == OCS_PARAM_TYPE_ENUM) {
            $options = array_flip( $this->params[$param.':enum']);
        }
        else if ( $type == OCS_PARAM_TYPE_COUNTER) {
            $options = ocs_admin_get_counter_id_list();
        }
        else if ( $type == OCS_PARAM_TYPE_MESSAGE) {
            $options['Message'] = ocs_admin_get_message_list();
            $options['Group'] = ocs_admin_get_message_group_list();
        }
		else if ( $type == OCS_PARAM_TYPE_ACCOUNT_STATUS) {
			// get all the account status
			$opt = ocs_admin_get_account_state_list();
			foreach( $opt as $k => $v) {
				$options[$v] = 'Expire Date of ' . $v;
			}
		}
		else if ( $type == OCS_PARAM_TYPE_PIVOT_DATE) {
			$opt = ocs_admin_get_account_state_list();
			$opt2 = array();
			foreach( $opt as $k => $v) {
				$options[$v] = 'Expire Date of ' . $v;
				$options['MAX(NOW,'.$v.')'] = 'Later date between Now and Expire Date of ' . $v;
			}

			return array_merge( array( 'Now' => 'Now'), $options);
		}
		else if ( $type == OCS_PARAM_TYPE_DAYS_TO_ADD) {
			$opt = ocs_admin_get_account_state_list();
			foreach( $opt as $k => $v) {
				$options[$v] = 'Duration of ' . $v;
			}

			return array_merge( $options, array( 'Voucher.ACTIVE' => 'Active Days of the Voucher', 'Voucher.GRACE' => 'Grace Days of the Voucher',
					'Period.SERVICE_SAVING' => 'Period of SERVICE_SAVING',
				   	'MAX(RemainedDays.ACTIVE,Voucher.ACTIVE)' => 'Max( Remained Days of ACTIVE, Active Days of the Voucher)' ));

		}

		return $options;
	}

    function get_value( $param, $value)
    {
        $type = $this->type( $param);
        if ( $type == OCS_PARAM_TYPE_ENUM) {
            $enum_list = array_flip( $this->params[$param.':enum']);

            $selected = array();
            if ( is_array( $value)) {
                foreach( $value as $key => $item) {
                    if ( ! empty($item) ) {  // it's selected
                        $selected[$enum_list[$key]] = $key;
                    }
                }
            }
            else {
                if ( ! isset( $enum_list[$value])) return NULL;
                $selected = array( $enum_list[$value] => $value);
            }

            // return json encoded string
            return array( json_encode( $selected), '('.implode( ', ', array_values( $selected)). ')');
        }

        return array( $value, $value);
    }

    function get_param( $value)
    {
        return isset( $this->params[$value]) ? $this->params[$value] : NULL;
    }

    function selected()
    {
        return $this->selected;
    }

    function options()
    {
        return $this->options;
    }

    function keylist()
    {
        return $this->list;
    }
}

// string fomat : Array( [0]=>13033:12191=0212355,[1]=>13033:12184=0, 13033:12186=12336)
function ocs_lifecycle_decode_action_param_values( $param_list, $toArray=FALSE)
{
	$output = array();
	foreach( $param_list as $p) {
		list($k,$v) = explode( '=', $p);
		list($action_nid,$param_nid) = explode( ':', $k);
		
		$param = node_load( $param_nid);

		$type =  $param->field_ocs_param_type['und'][0]['value'];
		if ( $type == OCS_PARAM_TYPE_ENUM) {
			$options = array_flip( json_decode( $param->field_ocs_param_value['und'][0]['value'], TRUE));
			$v = $options[$v];
        }
		else {
			$params = new OcsParam; 
            $options = $params->get_options( $type, '');	// bhtak TODO: check 2nd parameter. it should be some valid value
			if ( ! empty( $options) && isset( $options[$v])) {
				$v = $options[$v];
			}
		}
            
		$output[] = $param->title . ' = ' . $v;
	}
	
	if ( $toArray) return $output;
	return implode( ', ', $output);
}



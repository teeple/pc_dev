<?php
/*
aaaaabbbbb
*/
/** 
 * Searches haystack for needle and returns an array of the key path if it is found in the (multidimensional) array, FALSE otherwise. 
 * 
 * mixed array_searchRecursive ( mixed needle, array haystack [, bool strict[, array path]] ) 
 */ 
function array_searchRecursive_get_key_path( $needle, $haystack, $strict=false, $path=array() ) 
{ 
    if( !is_array($haystack) ) { 
        return false; 
    } 

    foreach( $haystack as $key => $val ) { 
        if( is_array($val) && $subPath = array_searchRecursive_get_key_path($needle, $val, $strict, $path) ) { 
            $path = array_merge($path, array($key), $subPath); 
            return $path; 
        } elseif( (!$strict && $val == $needle) || ($strict && $val === $needle) ) { 
            $path[] = $key; 
            return $path; 
        } 
    } 
    return false; 
}

function array_flatten($array) {
    if (!is_array($array)) {
        return FALSE;
    }
    $result = array();
    foreach ($array as $key => $value) {
        if (is_array($value)) {
            $result = array_merge($result, array_flatten($value));
        }
        else {
            $result[$key] = $value;
        }
    }
    return $result;
}

function objectToArray($d) {
    if (is_object($d)) {
        // Gets the properties of the given object
        // with get_object_vars function
        $d = get_object_vars($d);
    }

    if (is_array($d)) {
        /*
         * Return array converted to object
         * Using __FUNCTION__ (Magic constant)
         * for recursive call
         */
        return array_map(__FUNCTION__, $d);
    }
    else {
        // Return array
        return $d;
    }
}

function _indent_json_string($json) {

	$result      = '';
	$pos         = 0;
	$strLen      = strlen($json);
	//$indentStr   = '  ';
	$indentStr   = '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	//$newLine     = "\n";
	$newLine     = "<br/>";
	$prevChar    = '';
	$outOfQuotes = true;

	for ($i=0; $i<=$strLen; $i++) {

		// Grab the next character in the string.
		$char = substr($json, $i, 1);

		// Are we inside a quoted string?
		if ($char == '"' && $prevChar != '\\') {
			$outOfQuotes = !$outOfQuotes;

			// If this character is the end of an element,
			// output a new line and indent the next line.
		} else if(($char == '}' || $char == ']') && $outOfQuotes) {
			$result .= $newLine;
			$pos --;
			for ($j=0; $j<$pos; $j++) {
				$result .= $indentStr;
			}
		}

		// Add the character to the result string.
		$result .= $char;

		// If the last character was the beginning of an element,
		// output a new line and indent the next line.
		if (($char == ',' || $char == '{' || $char == '[') && $outOfQuotes) {
			$result .= $newLine;
			if ($char == '{' || $char == '[') {
				$pos ++;
			}

			for ($j = 0; $j < $pos; $j++) {
				$result .= $indentStr;
			}
		}

		$prevChar = $char;
	}

	return $result;
}

function _fill_blank_string_for_timeslot($str){
	$value = intval($str);
	if($value/10 < 1){
		$str = '0'.$str;	
	}	
	return $str;
}

function generate_jstree() {

	require_once('Smarty.class.php');
	$smarty = new Smarty();
	$smarty->setTemplateDir('/var/www/pc_dev/sites/default/files/Smarty/templates/');
	$smarty->setCompileDir('/var/www/pc_dev/sites/default/files/Smarty/templates_c/');
	$smarty->setConfigDir('/var/www/pc_dev/sites/default/files/Smarty/configs/');
	$smarty->setConfigDir('/var/www/pc_dev/sites/default/files/Smarty/cache/');
	$smarty->assign('name', 'Ned');
	$smarty->fetch('index.tpl');
}

function build_navigation_bar()
{
	$path = current_path();
	//dpm( $path, 'current path');
	
	$menu = array(
			'dash' => array( 'href' => '/', 'icon' => 'dash', 
					'prefix' => 'node', 'title' => 'Home'),
			'product' => array( 'href' => '/product_designer/mobile', 'icon' => 'gal', 
					'prefix' => 'product_designer', 'title' => 'Product Designer',
                    'sub' => array( array( '/product_designer/mobile', 'Mobile'), 
                        array( '/product_designer/iptv', 'IPTV'),
                        array( '/product_designer/broadband', 'Broadband'),
                        array( '/product_designer/voip', 'VOIP'),
                        array( '/product_designer/satelite', 'Satelite'),
                        array( '/product_designer/cross', 'Bundle'))),
			'relation' => array( 'href' => '/relation/product/hierarchy/Mobile', 'icon' => 'widgets', 
					'prefix' => 'relation', 'title' => 'Relation Manager'),
			'lifecycle' => array( 'href' => '/lifecycles/product', 'icon' => 'anlt', 
					'prefix' => 'lifecycles', 'title' => 'Lifecycle'),
			'common' => array( 'href' => '/common/numberingplan/domestic/list', 'icon' => 'typ', 
					'prefix' => 'common', 'title' => 'Common Data',
					'sub' => array( 
						array( '/common/numberingplan/domestic/list', 'Numbering Plan'),
                        array( '/common/counter/list', 'Counters'),
					    array( '/common/vouchercardtype', 'ETC'),
                        )),
			'ocs' => array( 'href' => '/config/ocs', 'icon' => 'tb', 
					'prefix' => 'config/ocs', 'title' => 'OCS'),
			);

	$output = '';
	
	foreach( $menu as $item) {
		$image = '/sites/default/files/images/nav/' . $item['icon'];
		//dpm( $item['prefix']);
		if ( strpos( $path, $item['prefix'], 0) === 0)
			$image .= '-active.png';
		else
			$image .= '.png';

        $sub_menu = '';
        if ( array_key_exists( 'sub', $item)) {
            foreach( $item['sub'] as $title) {
                $sub_menu .= t( '<li><a href="@href">@title</a></li>', 
                    array( '@href' => $title[0], '@title' => $title[1]));
            }
            $sub_menu = '<ul class="sub-nav">' . $sub_menu . '</ul>';
        }

		$output .= t('<li class="nav-item"><a href="@href"><img src="@image" alt="" /><p>@title</p></a>!sub</li>',
				array( '@href' => $item['href'], '@image' => $image, '@title' => $item['title'],
                    '!sub' => $sub_menu));	
	}
	
	print '<div class="top-bar"><ul id="nav">' . $output . '</ul></div>';
}

function _get_nids_from_views($view_name, $display, $args) {
	$retArray = array();
	
	$view = views_get_view($view_name);
	$view->set_display($display);
	$view->set_arguments($args);
	$view->execute();
	
	foreach($view->result as $record) {
		$retArray[] = $record->nid;
	}
	return $retArray;
}

function _get_records_from_views($view_name, $display, $args) {
	
	$view = views_get_view($view_name);
	$view->set_display($display);
	$view->set_arguments($args);
	$view->execute();
	
	return $view->result;
}

function _get_records_from_views_by_label($view_name, $display, $args, $req_labels){
	$retArray = array();
	
	$view = views_get_view($view_name);
	$view->set_display($display);
	$view->set_arguments($args);
	$view->execute();
	
	foreach($view->result as $record) {
		$tmpRecord = array();
		foreach($req_labels as $key => $value) {
			$tmpRecord[$key] = view_get_field_value_by_label($view, $value, $record);
		}
		$retArray[] = $tmpRecord;
	}
	return $retArray;
}

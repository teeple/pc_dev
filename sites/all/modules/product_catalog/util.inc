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
	
	$image = 'sites/default/files/images/nav/dash-active.png';

	print '
<div class="top-bar">
  <ul id="nav">
         <li class="nav-item">
           <a href="#"><img src="' . $image . '" alt="" /><p>Home</p></a>
         </li>
  </ul>
</div>';
}
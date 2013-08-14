<?php
$roles = user_roles();
$permissions = user_role_permissions($roles);
$adminPermissions = $permissions[3];

dsm($adminPermissions, 'adminPermissions');

$revoke_permissions = array();
foreach($adminPermissions as $key => $value) {
	  if( (strpos($key, 'admin') !== false)
			  || (strpos($key, 'terms in') !== false)
				  || (strpos($key, 'access toolbar') !== false) ) {
		       $revoke_permissions[$key] = $value;
	}
}
$revokeRids = array(1,2,4,5,6,7,8,9,10);

foreach($revokeRids as $rid) {
	  user_role_revoke_permissions($rid, array_keys($revoke_permissions));
}

$roles = user_roles();

?>

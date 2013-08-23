<?php
$roles = user_roles();
$permissions = user_role_permissions($roles);
$adminPermissions = $permissions[3];
$excludePermissionList = array( 'admin', 'terms in', 'access toolbar', 'Access developer information', 'execute php code', 'switch users', 'access site in maintenance mode');

$revoke_permissions = array();
foreach($adminPermissions as $key => $value) {
	foreach($excludePermissionList as $perm) {
	   if( strpos($key, $perm) !== false) {
		    $revoke_permissions[$key] = $value;
		}
	}
}
$revokeRids = array(1,2,4,5,6,7,8,9,10);
foreach($revokeRids as $rid) {
	user_role_revoke_permissions($rid, array_keys($revoke_permissions));
}
?>

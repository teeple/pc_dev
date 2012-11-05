(function($) {

   Drupal.behaviors.sjangTestBehavior = {
		attach : function(context, settings) {
			console.log(context);
			console.log(settings);
			$.jstree._themes = "sites/all/libraries/jstree/themes/";
			$(".tree_test").jstree({
				"json_data" : {
					"data" : settings.tree_test_data,
					"progressive_render" : true
				},
				"plugins" : [ "themes", "json_data" ],
			});
		}
	};
})(jQuery);

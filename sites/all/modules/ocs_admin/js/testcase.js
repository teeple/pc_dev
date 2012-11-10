(function($){
  Drupal.behaviors.ocs_admin = {
	attach: function(context, settings) {
		console.log('testcase.js loaded');
		$('#run-test-button').bind('click',$.fn.runTestHandler);
	}
  };

  $.fn.runTestHandler = function(event) {
  	console.log('run test case');
	var ts = $('.node_nid');
	console.log( ts);
  };
	
 })(jQuery);

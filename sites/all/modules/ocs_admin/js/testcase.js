(function($){
  Drupal.behaviors.ocs_admin = {
	attach: function(context, settings) {
		console.log('testcase.js loaded');
		$('#run-test-ocs-button').bind('click',$.fn.runTestOcsHandler);
	}
  };

  $.fn.runTestOcsHandler = function(event) {
  	console.log('run test case');
	var ts = $('.testcase_status').each( function(index){
        $(this).text( 'Requesting');

        // get URL
        var testOcsUrl = '/ajax/test/ocs/' + $(this).attr('node');
        $('#run-test-ocs-result > ul').append( '<li>' + testOcsUrl + '</li>');

        $.ajax({
            url: testOcsUrl,
            type: "get",
            success: function(data) {
                var output = data;
                $('#run-test-ocs-result > ul').append( '<li>' + output + '</li>');
            }
        });
    });
  };
	
 })(jQuery);

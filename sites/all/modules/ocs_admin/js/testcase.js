(function($) {
	Drupal.behaviors.ocs_admin = {
		attach : function(context, settings) {
			console.log('testcase.js loaded');
			$('#run-test-ocs-button').bind('click', $.fn.runTestOcsHandler); // test button
			$('#add-action-button').bind('click', $.fn.addActionHandler);
		}
	};

	$.fn.runTestOcsHandler = function(event) {
		console.log('run test case');
		/*
		$('#run-test-ocs-result').append( 
		'<table>' +
		'<thead><tr><th>Response</th><th>Time</th></tr></thead>' +
		'<tbody></tbody>' +
		'</table>'
		);
		 */
		var ts = $('.testcase_status').each(
				function(index) {
					$(this).text('Requesting');

					// first, get the number of test cases
					var nid = $(this).attr('node');
					var testOcsUrl = '/ajax/test/ocs/count/' + nid;
					$.ajax({
						url : testOcsUrl,
						type : "get",
						success : function(data) {
							var output = data;
							//                $('#run-test-ocs-result > ul').append( '<li>' + output + '</li>');
							$.fn.runOcsTestCase(nid, data);
						},
						error : function() {
							$('#run-test-ocs-result > ul').append(
									'<li> Fail: ' + testOcsUrl + '</li>');
						}
					});

				});
	};

	$.fn.runOcsTestCase = function(nid, testData) {
		var testcase = $.parseJSON(testData);
		console.log('test: ', testcase);
		for ( var i = 0; i < testcase.length; i++) {
			var testOcsUrl = '/ajax/test/ocs/' + nid + '/' + testcase[i].nid;
			//            $('#run-test-ocs-result > ul').append( '<li>' + testOcsUrl + '</li>');

			$('.testcase_status[node=' + nid + ']').append(
					'<li node="' + nid + ':' + testcase[i].nid + '"> REQ '
							+ testOcsUrl + '</li>');
			$.ajax({
				url : testOcsUrl,
				type : "get",
				success : function(data) {
					var r = $.parseJSON(data);
					/*
					$('#run-test-ocs-result > ul').append( data);
					 */
					console.log(r);

					$('li[node="' + r.nid + ':' + r.tc_nid + '"]').append(
							'<ul><li> ' + r.nid + ' : ' + r.response.request
									+ '</li>' + '<li> RSP  : '
									+ r.response.code
									+ r.response.status_message + '</li>'
									+ '<li>' + r.response.data + '</li></ul>');

				}
			});
		}
	};
	
	$.fn.addActionHandler = function() {
		var num = $('input[name="num_action"]').val();
		console.log('add action', num);
		$('div.action-' + num).removeClass('hide');
		$('input[name="num_action"]').val( parseInt(num)+1);
	};

})(jQuery);

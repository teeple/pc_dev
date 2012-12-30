(function($) {
	Drupal.behaviors.ocs_admin = {
		attach : function(context, settings) {
			//console.log('testcase.js loaded');
			$('#run-test-ocs-button').bind('click', $.fn.runTestOcsHandler); // test button
			$('#add-action-button').bind('click', $.fn.addActionHandler);
			$('.run-one-test-case-button').bind('click', $.fn.runOneTestOcsHandler);
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
		var idx = 0;
		var ts = $('.testcase_status[order=' + idx + ']').each(
			function(index) {
				$.fn.runOneTestCase( this, idx +1);
			});
	};

	$.fn.runOneTestOcsHandler = function(event) {
		console.log('run one test case');
		/*
		$('#run-test-ocs-result').append( 
		'<table>' +
		'<thead><tr><th>Response</th><th>Time</th></tr></thead>' +
		'<tbody></tbody>' +
		'</table>'
		);
		*/
		var $target = $(event.target);
		$.fn.runOneTestCase( $target, 0);
	};

	$.fn.runOneTestCase = function( target, next) {
		console.log( 'target', target);
		var nid = $(target).attr('node');
		console.log('test: ', nid);
		$('.testcase_status[node=' + nid + ']').text('Requesting');
		$('.testcase_check_result[node=' + nid + ']').text( 'RESULT:');

		var pathname = window.location.pathname.split('/');
		var testsuite = pathname[pathname.length-1];
		console.log('path:', pathname, testsuite);

		// first, get the number of test cases
		var testOcsUrl = '/ajax/test/ocs/' + testsuite + '/' + nid;
		$.ajax({
			url : testOcsUrl,
			type : "get",
			success : function(data) {
				var output = $.parseJSON(data);
				console.log( 'response', output);
			    //$('#run-test-ocs-result').append( '<div>' + JSON.stringify( output, undefined, 2)  + '</div>');
				var rsp = output[0].response;
				var result = $.parseJSON( rsp.data);
			    $('#run-test-ocs-result').append( '<br>').append( prettyPrint( rsp.request)).
					append( prettyPrint( result, { expanded : false, maxDepth: 5}));
				var desc = ( typeof( result.result_desc) == 'undefined') ? '' : result.result_desc;
				$('.testcase_status[node=' + nid + ']').append( '<li> Code: ' + rsp.code + '</li>').
					append( '<li> Code: ' + result.result_code + '</li>').
					append( '<li> Reason: ' + result.result_reason + '(' + desc +')</li>') ;
			//	$.fn.runOcsTestCase(nid, data);

				// check result
				var check_target = $('.testcase_check[node=' + nid + ']');
				var check_result = eval( $(check_target).text());
				console.log( 'check', $(check_target).text(), check_result);
				$('.testcase_check_result[node=' + nid + ']').text( 'RESULT:' +(check_result ? "SUCCESS" : "FAIL") );

				if ( next > 0) {
					// run next test case
					var $target = $('.testcase_status[order=' + next + ']');
					if ( $target.length > 0) {
						$.fn.runOneTestCase( $target, next+1);
					}
				}
			},
			error : function() {
				$('#run-test-ocs-result > ul').append(
						'<li> Fail: ' + testOcsUrl + '</li>');
			}
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

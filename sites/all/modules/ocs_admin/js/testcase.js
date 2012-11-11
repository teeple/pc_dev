(function($){
  Drupal.behaviors.ocs_admin = {
	attach: function(context, settings) {
		console.log('testcase.js loaded');
		$('#run-test-ocs-button').bind('click',$.fn.runTestOcsHandler);
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
	var ts = $('.testcase_status').each( function(index){
        $(this).text( 'Requesting');

        // first, get the number of test cases
        var nid = $(this).attr('node');
        var testOcsUrl = '/ajax/test/ocs/count/' + nid;
        $.ajax({
            url: testOcsUrl,
            type: "get",
            success: function(data) {
                var output = data;
                $('#run-test-ocs-result > ul').append( '<li>' + output + '</li>');
                $.fn.runOcsTestCase(nid, data);
            },
            error: function() {
                $('#run-test-ocs-result > ul').append( '<li> Fail: ' + testOcsUrl + '</li>');
            }
        });

        
    });
  };

    $.fn.runOcsTestCase = function(nid,testData) {
        var testcase = $.parseJSON(testData);
        console.log( 'test: ', testcase);
        for( var i=0; i< testcase.length; i++) {
            var testOcsUrl = '/ajax/test/ocs/' + nid + '/' + testcase[i].nid;
            $('#run-test-ocs-result > ul').append( '<li>' + testOcsUrl + '</li>');

            $('.testcase_status[node=' + nid + ']').append( '<li node="' + nid + ':' + testcase[i].nid + '"> REQ ' + testOcsUrl + '</li>');
            $.ajax({
                url: testOcsUrl,
                type: "get",
                success: function(data) {
                    var result = $.parseJSON(data);
                    $('#run-test-ocs-result > ul').append( data);
                    console.log( result);

                    $('li[node="' + result.nid + ':' + result.tc_nid + '"]').append( 
                        '<ul><li> ' + result.nid  + ' : ' + result.effective_url + '</li>'  +
                        '<li> RSP  : ' + result.response + ', TIME : ' + result.total_time + '</li></ul>'  );

                }
            });
        }
    }
	
 })(jQuery);

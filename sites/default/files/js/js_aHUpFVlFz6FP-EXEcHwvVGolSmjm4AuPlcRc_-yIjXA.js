(function($) {
	Drupal.behaviors.ocs_admin = {
		attach : function(context, settings) {
			//console.log('testcase.js loaded');
			$('#run-test-ocs-button').bind('click', function(event) {
				$('.run-one-test-case-button').removeClass('fire').addClass( 'fire');
				$('.run-one-test-case-button[order=0]').trigger( 'click');
			});
			$('#add-action-button').bind('click', $.fn.addActionHandler);
			$('.run-one-test-case-button').bind('click', $.fn.runOneTestOcsHandler);
			$('.run-all-test-case-button').bind('click', function(event) {
				var target = $(event.target);
				var nid = $(target).attr('node');
				$('.run-one-test-case-button[node=' + nid +']').removeClass('fire').addClass('fire');
				$('.run-one-test-case-button[node=' + nid +'][tc=0]').trigger('click');
			});
			$('#clear-test-result-button').bind('click', function(event) {
				$('#run-test-ocs-result').text('');
			});

			$('.more_data').bind('click', function(event) {
				var target=$(event.target), 
					content=$(target).parent().children('.content'),
					print=$(target).attr('href'),
					json = $.parseJSON( $(content).text());
				if ( $(content).hasClass('export_result')) {
					json.data = $.parseJSON( json.data);
				}
				$(print).append( prettyPrint( json, {expanded:false}));
			});

			/*
			$('.export_result').each(function(i){
				var json = $.parseJSON($(this).text());
				json.data = $.parseJSON( json.data);
				console.log(json);
				//$(this).append( prettyPrint( json, {expanded:false}));
			});
			var str= $('.export_result').text();
			if ( str != 'undefined') {
				var json = $.parseJSON(str);
				console.log( json);
				$('.export_data').text( prettyPrint( json, {expanded:false}));
			}
			*/
		}
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
		$.fn.runOneTestCase( $target);
	};

	$.fn.runOneTestCase = function( target) {
		console.log( 'target', target);
		$(target).removeClass('fire');

		var nid = $(target).attr('node');
		var order = $(target).attr('order');
		var tc = $(target).attr('tc');
		var title = order + '. ' + $(target).attr('title');
		console.log('test: ', nid);
		/*
		$('.testcase_status[node=' + nid + ']').text('Requesting');
		$('.testcase_check_result[node=' + nid + ']').text( 'RESULT:');
		*/

		var pathname = window.location.pathname.split('/');
		var testsuite = pathname[pathname.length-1];
		console.log('path:', pathname, testsuite);

		// first, get the number of test cases
		var testOcsUrl = '/ajax/test/ocs/{0}/{1}/{2}'.format( testsuite, nid, tc);

		$.ajax({
			url : testOcsUrl,
			type : "get",
			success : function(data) {
				var output = $.parseJSON(data);
				console.log( 'response', output);
			    //$('#run-test-ocs-result').append( '<div>' + JSON.stringify( output, undefined, 2)  + '</div>');
				var config = { expanded : false, maxDepth: 5};

				var d = new Date();
				var tc_idx = output.tc;
				var result = $.parseJSON( output.response.data);
				var test_data = $.parseJSON( output.test_data);
				var test_result = $.parseJSON( output.test_result);
				var counter = [];

				$('#run-test-ocs-result').
					append( '<br>{0}:{1}:{2}<hr style="background-color:darkblue;"><h3>{3}</h3>'.
						format( d.getHours(), d.getMinutes(), d.getSeconds(), title)).
					append( '<h4 id="test_result_{1}_{0}"> TC-{0}    Request {2}</h4>'.format( tc_idx, nid, testOcsUrl)).
					append( '<p> {0}</p>'.format( output.response.request.replace(/\n/g, '<br>')));

				$('.testcase_status[node=' + nid + ']').
					append( '<h4> <a href="#test_result_{1}_{0}">TC-{0}</a> Code: {2}</h4>'.format( tc_idx, nid, output.response.code));

				if ( result != null) {
					var cdr = [];
					if ( typeof( result.cdr) != 'undefined') {
						for( var j in result.cdr) {
							if ( $.isArray( result.cdr[j])) {
								var tmp = [];
								for( var k in result.cdr[j]) {
									tmp[k] = result.cdr[j][k].split(',');
									/*
									var decoded_cdr = $.fn.decodeCDR( cdr[j]);
									counter = decoded_cdr.counters;
									*/
								}
								cdr[j] = tmp;
							}
							else {
								cdr[j] = result.cdr[j];
							}
						}
						result.cdr = cdr;
						console.log( 'cdr', cdr[0][0]);
						var decoded_cdr = $.fn.decodeCDR( cdr[0][0]);
						counter = decoded_cdr.charging_counters; 
						//console.log( 'voice cdr', voice_cdr);
					}

					$('#run-test-ocs-result').
						append( '<br><h4>Result</h4>').
						append( prettyPrint( result, config));

					$('.testcase_status[node=' + nid + ']').
						append( '<p> Result: {0} reason:{1} {2} </p>'.format( 
							(typeof( result.result_code) == 'undefined') ? '??' : result.result_code,
							(typeof( result.result_reason) == 'undefined') ? '??' : result.result_reason,
							(typeof( result.result_desc) == 'undefined') ? '' : '(' + result.result_desc + ')'));
			//	$.fn.runOcsTestCase(nid, data);

					// evalulate condition
					// check result
					var condition = $('.testcase_check[node=' + nid + ']').text();
					var token = condition.match(/[\w\d\.\[\]\']+/g);
					var eval_result = {};
					for( var i in token) {
						try {
							eval_result[token[i]] = eval( token[i]);
						}
						catch( e) {
							eval_result[token[i]] = e;
							eval_result['result'] = 'FAIL';
							break;
						}
					}
					if ( typeof(eval_result['result']) == 'undefined') 
						eval_result['result'] = eval(condition) ? "SUCCESS" : "FAIL";

					console.log( 'check', condition, eval_result);
					console.log( 'counter', counter);
					$('.testcase_check_result[node=' + nid + ']').
						append( '<h4> TC-{0} <a href="#test_result_{1}_{0}">{2}</a></h4>'.
							format( tc_idx, nid, eval_result['result'] ));

					$('#run-test-ocs-result').
						append( '<br><h4> Test Data </h4>').
						append( prettyPrint( eval_result, config));
				}
				else {
					$('#run-test-ocs-result').append( '<br><h4>Result </h4> : {0}<br>'.format( output.response.error));
				}

				// run next test case
				var nextRun = $('.run-one-test-case-button[order={0}][tc={1}]'.format( order, parseInt(tc_idx)+1));
				if ( nextRun.length > 0) {
					if ( $(nextRun).hasClass('fire')) $(nextRun).trigger('click');
				}
				else {
					nextRun = $('.run-one-test-case-button[order={0}][tc=0]'.format( parseInt(order)+1));
					if ( $(nextRun).hasClass('fire')) $(nextRun).trigger('click');
				}
			},
			error : function(data) {
				console.log( 'failed response', data);
				$('#run-test-ocs-result').append( '<br><div id="test_result_' + nid +'"></div>').
					append( '<h3>' + title + '</h3>').
					append( '<h4>Request {0}</h4>'.format( testOcsUrl)).
					append( '<br><h4>Result : Failed</h4>');
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

	String.prototype.format = function() {
	  var args = arguments;
	    return this.replace(/{(\d+)}/g, function(match, number) { 
			return typeof args[number] != 'undefined'
			  ? args[number]
				: match
								    ;
									  });
	};

	$.fn.decodeCDR = function( fields) {

		// decode used counter
		var cdr = {
			header: fields.slice(0,12),
			scription: fields.slice(12,25),
			charging: fields.slice(25,28),
			service:fields.slice(28),
		}, counter= {}

		console.log( 'cdr', cdr);

		for( var j=0; j< cdr.charging.length; j++){
			if ( cdr.charging[j].length > 0) {
				var used_counter = cdr.charging[j].split('/');
				for( var i=0; i< used_counter.length; i++){
					var usage = used_counter[i].split(':');
					counter[usage[0]] = { usage: parseInt( usage[2]) - parseInt( usage[1])};
				}
			}
		}

		cdr.subscription_key = fields[2];
		cdr.charging_counters = counter;

		console.log( 'decoded cdr', cdr);
		return cdr;
	}

})(jQuery);


;
/*
Copyright (c) 2009 James Padolsey.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   1. Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY James Padolsey ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL James Padolsey OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of James Padolsey.

 AUTHOR James Padolsey (http://james.padolsey.com)
 VERSION 1.03.0
 UPDATED 29-10-2011
 CONTRIBUTORS
	David Waller
    Benjamin Drucker

*/

var prettyPrint = (function(){
	
	/* These "util" functions are not part of the core
	   functionality but are  all necessary - mostly DOM helpers */
	
	var util = {
		
		el: function(type, attrs) {
			
			/* Create new element */
			var el = document.createElement(type), attr;
			
			/*Copy to single object */
			attrs = util.merge({}, attrs);
			
			/* Add attributes to el */
			if (attrs && attrs.style) {
				var styles = attrs.style;
				util.applyCSS( el, attrs.style );
				delete attrs.style;
			}
			for (attr in attrs) {
				if (attrs.hasOwnProperty(attr)) {
					el[attr] = attrs[attr];
				}
			}
			
			return el;
		
		},
		
		applyCSS: function(el, styles) {
			/* Applies CSS to a single element */
			for (var prop in styles) {
				if (styles.hasOwnProperty(prop)) {
					try{
						/* Yes, IE6 SUCKS! */
						el.style[prop] = styles[prop];
					}catch(e){}
				}
			}
		},
		
		txt: function(t) {
			/* Create text node */
			return document.createTextNode(t);
		},
		
		row: function(cells, type, cellType) {
			
			/* Creates new <tr> */
			cellType = cellType || 'td';
			
			/* colSpan is calculated by length of null items in array */
			var colSpan = util.count(cells, null) + 1,
				tr = util.el('tr'), td,
				attrs = {
					style: util.getStyles(cellType, type),
					colSpan: colSpan,
					onmouseover: function() {
						var tds = this.parentNode.childNodes;
						util.forEach(tds, function(cell){
							if (cell.nodeName.toLowerCase() !== 'td') { return; }
							util.applyCSS(cell, util.getStyles('td_hover', type));
						});
					},
					onmouseout: function() {
						var tds = this.parentNode.childNodes;
						util.forEach(tds, function(cell){
							if (cell.nodeName.toLowerCase() !== 'td') { return; }
							util.applyCSS(cell, util.getStyles('td', type));
						});
					}
				};
				
			util.forEach(cells, function(cell){
				
				if (cell === null) { return; }
				/* Default cell type is <td> */
				td = util.el(cellType, attrs);
				
				if (cell.nodeType) {
					/* IsDomElement */
					td.appendChild(cell);
				} else {
					/* IsString */
					td.innerHTML = util.shorten(cell.toString());
				}
				
				tr.appendChild(td);
			});
			
			return tr;
		},
		
		hRow: function(cells, type){
			/* Return new <th> */
			return util.row(cells, type, 'th');
		},
		
		table: function(headings, type){
			
			headings = headings || [];
			
			/* Creates new table: */
			var attrs = {
					thead: {
						style:util.getStyles('thead',type)
					},
					tbody: {
						style:util.getStyles('tbody',type)
					},
					table: {
						style:util.getStyles('table',type)
					}
				},
				tbl = util.el('table', attrs.table),
				thead = util.el('thead', attrs.thead),
				tbody = util.el('tbody', attrs.tbody);
				
			if (headings.length) {
				tbl.appendChild(thead);
				thead.appendChild( util.hRow(headings, type) );
			}
			tbl.appendChild(tbody);
			
			return {
				/* Facade for dealing with table/tbody
				   Actual table node is this.node: */
				node: tbl,
				tbody: tbody,
				thead: thead,
				appendChild: function(node) {
					this.tbody.appendChild(node);
				},
				addRow: function(cells, _type, cellType){
					this.appendChild(util.row.call(util, cells, (_type || type), cellType));
					return this;
				}
			};
		},
		
		shorten: function(str) {
			var max = 40;
			str = str.replace(/^\s\s*|\s\s*$|\n/g,'');
			return str.length > max ? (str.substring(0, max-1) + '...') : str;
		},
		
		htmlentities: function(str) {
			return str.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
		},
		
		merge: function(target, source) {
			
			/* Merges two (or more) objects,
			   giving the last one precedence */
			
			if ( typeof target !== 'object' ) {
				target = {};
			}
			
			for (var property in source) {
				
				if ( source.hasOwnProperty(property) ) {
					
					var sourceProperty = source[ property ];
					
					if ( typeof sourceProperty === 'object' ) {
						target[ property ] = util.merge( target[ property ], sourceProperty );
						continue;
					}
					
					target[ property ] = sourceProperty;
					
				}
				
			}
			
			for (var a = 2, l = arguments.length; a < l; a++) {
				util.merge(target, arguments[a]);
			}
			
			return target;
		},
		
		count: function(arr, item) {
			var count = 0;
			for (var i = 0, l = arr.length; i< l; i++) {
				if (arr[i] === item) {
					count++;
				}
			}
			return count;
		},
		
		thead: function(tbl) {
			return tbl.getElementsByTagName('thead')[0];
		},
		
		forEach: function(arr, max, fn) {
			
			if (!fn) {
				fn = max;
			}

			/* Helper: iteration */
			var len = arr.length,
				index = -1;
			
			while (++index < len) {
				if(fn( arr[index], index, arr ) === false) {
					break;
				}
			}
			
			return true;
		},
		
		type: function(v){
			try {
				/* Returns type, e.g. "string", "number", "array" etc.
				   Note, this is only used for precise typing. */
				if (v === null) { return 'null'; }
				if (v === undefined) { return 'undefined'; }
				var oType = Object.prototype.toString.call(v).match(/\s(.+?)\]/)[1].toLowerCase();
				if (v.nodeType) {
					if (v.nodeType === 1) {
						return 'domelement';
					}
					return 'domnode';
				}
				if (/^(string|number|array|regexp|function|date|boolean)$/.test(oType)) {
					return oType;
				}
				if (typeof v === 'object') {
					return v.jquery && typeof v.jquery === 'string' ? 'jquery' : 'object';
				}
				if (v === window || v === document) {
					return 'object';
				}
				return 'default';
			} catch(e) {
				return 'default';
			}
		},
		
		within: function(ref) {
			/* Check existence of a val within an object
			   RETURNS KEY */
			return {
				is: function(o) {
					for (var i in ref) {
						if (ref[i] === o) {
							return i;
						}
					}
					return '';
				}
			};
		},
		
		common: {
			circRef: function(obj, key, settings) {
				return util.expander(
					'[POINTS BACK TO <strong>' + (key) + '</strong>]',
					'Click to show this item anyway',
					function() {
						this.parentNode.appendChild( prettyPrintThis(obj,{maxDepth:1}) );
					}
				);
			},
			depthReached: function(obj, settings) {
				return util.expander(
					'[DEPTH REACHED]',
					'Click to show this item anyway',
					function() {
						try {
							this.parentNode.appendChild( prettyPrintThis(obj,{maxDepth:1}) );
						} catch(e) {
							this.parentNode.appendChild(
								util.table(['ERROR OCCURED DURING OBJECT RETRIEVAL'],'error').addRow([e.message]).node   
							);
						}
					}
				);
			}
		},
		
		getStyles: function(el, type) {
			type = prettyPrintThis.settings.styles[type] || {};
			return util.merge(
				{}, prettyPrintThis.settings.styles['default'][el], type[el]
			);
		},
		
		expander: function(text, title, clickFn) {
			return util.el('a', {
				innerHTML:  util.shorten(text) + ' <b style="visibility:hidden;">[+]</b>',
				title: title,
				onmouseover: function() {
					this.getElementsByTagName('b')[0].style.visibility = 'visible';
				},
				onmouseout: function() {
					this.getElementsByTagName('b')[0].style.visibility = 'hidden';
				},
				onclick: function() {
					this.style.display = 'none';
					clickFn.call(this);
					return false;
				},
				style: {
					cursor: 'pointer'
				}
			});
		},
		
		stringify: function(obj) {
			
			/* Bit of an ugly duckling!
			   - This fn returns an ATTEMPT at converting an object/array/anyType
				 into a string, kinda like a JSON-deParser
			   - This is used for when |settings.expanded === false| */
			
			var type = util.type(obj),
				str, first = true;
			if ( type === 'array' ) {
				str = '[';
				util.forEach(obj, function(item,i){
					str += (i===0?'':', ') + util.stringify(item);
				});
				return str + ']';
			}
			if (typeof obj === 'object') {
				str = '{';
				for (var i in obj){
					if (obj.hasOwnProperty(i)) {
						str += (first?'':', ') + i + ':' + util.stringify(obj[i]);
						first = false;
					}
				}
				return str + '}';
			}
			if (type === 'regexp') {
				return '/' + obj.source + '/';
			}
			if (type === 'string') {
				return '"' + obj.replace(/"/g,'\\"') + '"';
			}
			return (typeof(obj) == "undefined") ? "undefined" : obj.toString();
		},
		
		headerGradient: (function(){
			
			var canvas = document.createElement('canvas');
			if (!canvas.getContext) { return ''; }
			var cx = canvas.getContext('2d');
			canvas.height = 30;
			canvas.width = 1;
			
			var linearGrad = cx.createLinearGradient(0,0,0,30);
			linearGrad.addColorStop(0,'rgba(0,0,0,0)');
			linearGrad.addColorStop(1,'rgba(0,0,0,0.25)');
			
			cx.fillStyle = linearGrad;
			cx.fillRect(0,0,1,30);
			
			var dataURL = canvas.toDataURL && canvas.toDataURL();
			return 'url(' + (dataURL || '') + ')';
		
		})()
		
	};
	
	// Main..
	var prettyPrintThis = function(obj, options) {
		
		 /*
		 *	  obj :: Object to be printed					
		 *  options :: Options (merged with config)
		 */
		
		options = options || {};
		
		var settings = util.merge( {}, prettyPrintThis.config, options ),
			container = util.el('div'),
			config = prettyPrintThis.config,
			currentDepth = 0,
			stack = {},
			hasRunOnce = false;
		
		/* Expose per-call settings.
		   Note: "config" is overwritten (where necessary) by options/"settings"
		   So, if you need to access/change *DEFAULT* settings then go via ".config" */
		prettyPrintThis.settings = settings;
		
		var typeDealer = {
			string : function(item){
				//return util.txt('"' + util.shorten(item.replace(/"/g,'\\"')) + '"');
				return util.txt('"' + item.replace(/"/g,'\\"') + '"');
				/*
				var str = item.replace(/"/g,'\\"');
				var output = '';
				for( var i=0; i< str.length; i+= 40) {
					output += str.substr( i, 40) + '\\n';
				}
				return util.txt('"' + output + '"');
				*/
			},
			number : function(item) {
				return util.txt(item);
			},
			regexp : function(item) {
				
				var miniTable = util.table(['RegExp',null], 'regexp');
				var flags = util.table();
				var span = util.expander(
					'/' + item.source + '/',
					'Click to show more',
					function() {
						this.parentNode.appendChild(miniTable.node);
					}
				);
				
				flags
					.addRow(['g', item.global])
					.addRow(['i', item.ignoreCase])
					.addRow(['m', item.multiline]);
				
				miniTable
					.addRow(['source', '/' + item.source + '/'])
					.addRow(['flags', flags.node])
					.addRow(['lastIndex', item.lastIndex]);
					
				return settings.expanded ? miniTable.node : span;
			},
			domelement : function(element, depth) {
				
				var miniTable = util.table(['DOMElement',null], 'domelement'),
					props = ['id', 'className', 'innerHTML', 'src', 'href'], elname = element.nodeName || '';
				
				miniTable.addRow(['tag', '&lt;' + elname.toLowerCase() + '&gt;']);
					
				util.forEach(props, function(prop){
					if ( element[prop] ) {
						miniTable.addRow([ prop, util.htmlentities(element[prop]) ]);
					}
				});
				
				return settings.expanded ? miniTable.node : util.expander(
					'DOMElement (' + elname.toLowerCase() + ')',
					'Click to show more',
					function() {
						this.parentNode.appendChild(miniTable.node);
					}
				);
			},
			domnode : function(node){
				
				/* Deals with all DOMNodes that aren't elements (nodeType !== 1) */
				var miniTable = util.table(['DOMNode',null], 'domelement'),
					data =  util.htmlentities( (node.data || 'UNDEFINED').replace(/\n/g,'\\n') );
				miniTable
					.addRow(['nodeType', node.nodeType + ' (' + node.nodeName + ')'])
					.addRow(['data', data]);
				
				return settings.expanded ? miniTable.node : util.expander(
					'DOMNode',
					'Click to show more',
					function() {
						this.parentNode.appendChild(miniTable.node);
					}
				);
			},
			jquery : function(obj, depth, key) {
				return typeDealer['array'](obj, depth, key, true);
			},
			object : function(obj, depth, key) {
				
				/* Checking depth + circular refs */
				/* Note, check for circular refs before depth; just makes more sense */
				var stackKey = util.within(stack).is(obj);
				if ( stackKey ) {
					return util.common.circRef(obj, stackKey, settings);
				}
				stack[key||'TOP'] = obj;
				if (depth === settings.maxDepth) {
					return util.common.depthReached(obj, settings);
				}
				
				var table = util.table(['Object', null],'object'),
					isEmpty = true;
				
				for (var i in obj) {
					if (!obj.hasOwnProperty || obj.hasOwnProperty(i)) {
						var item = obj[i],
							type = util.type(item);
						isEmpty = false;
						try {
							table.addRow([i, typeDealer[ type ](item, depth+1, i)], type);
						} catch(e) {
							/* Security errors are thrown on certain Window/DOM properties */
							if (window.console && window.console.log) {
								console.log(e.message);
							}
						}
					}
				}
				
				if (isEmpty) {
					table.addRow(['<small>[empty]</small>']);
				} else {
					table.thead.appendChild(
						util.hRow(['key','value'], 'colHeader')
					);
				}
				
				var ret = (settings.expanded || hasRunOnce) ? table.node : util.expander(
					util.stringify(obj),
					'Click to show more',
					function() {
						this.parentNode.appendChild(table.node);
					}
				);
				
				hasRunOnce = true;
				
				return ret;
				
			},
			array : function(arr, depth, key, jquery) {
				
				/* Checking depth + circular refs */
				/* Note, check for circular refs before depth; just makes more sense */
				var stackKey = util.within(stack).is(arr);
				if ( stackKey ) {
					return util.common.circRef(arr, stackKey);
				}
				stack[key||'TOP'] = arr;
				if (depth === settings.maxDepth) {
					return util.common.depthReached(arr);
				}
				
				/* Accepts a table and modifies it */
				var me = jquery ? 'jQuery' : 'Array', table = util.table([me + '(' + arr.length + ')', null], jquery ? 'jquery' : me.toLowerCase()),
					isEmpty = true,
                    count = 0;
				
				if (jquery){
					table.addRow(['selector',arr.selector]);
				}

				util.forEach(arr, function(item,i){
                    if (settings.maxArray >= 0 && ++count > settings.maxArray) {
                        table.addRow([
                            i + '..' + (arr.length-1),
                            typeDealer[ util.type(item) ]('...', depth+1, i)
                        ]);
                        return false;
                    }
					isEmpty = false;
					table.addRow([i, typeDealer[ util.type(item) ](item, depth+1, i)]);
				});

				if (!jquery){
					if (isEmpty) {
						table.addRow(['<small>[empty]</small>']);
					} else {
						table.thead.appendChild( util.hRow(['index','value'], 'colHeader') );
					}
				}
				
				return settings.expanded ? table.node : util.expander(
					util.stringify(arr),
					'Click to show more',
					function() {
						this.parentNode.appendChild(table.node);
					}
				);
				
			},
			'function' : function(fn, depth, key) {
				
				/* Checking JUST circular refs */
				var stackKey = util.within(stack).is(fn);
				if ( stackKey ) { return util.common.circRef(fn, stackKey); }
				stack[key||'TOP'] = fn;
				
				var miniTable = util.table(['Function',null], 'function'),
					argsTable = util.table(['Arguments']),
					args = fn.toString().match(/\((.+?)\)/),
					body = fn.toString().match(/\(.*?\)\s+?\{?([\S\s]+)/)[1].replace(/\}?$/,'');
					
				miniTable
					.addRow(['arguments', args ? args[1].replace(/[^\w_,\s]/g,'') : '<small>[none/native]</small>'])
					.addRow(['body', body]);
					
				return settings.expanded ? miniTable.node : util.expander(
					'function(){...}',
					'Click to see more about this function.',
					function(){
						this.parentNode.appendChild(miniTable.node);
					}
				);
			},
			'date' : function(date) {
				
				var miniTable = util.table(['Date',null], 'date'),
					sDate = date.toString().split(/\s/);
				
				/* TODO: Make this work well in IE! */
				miniTable
					.addRow(['Time', sDate[4]])
					.addRow(['Date', sDate.slice(0,4).join('-')]);
					
				return settings.expanded ? miniTable.node : util.expander(
					'Date (timestamp): ' + (+date),
					'Click to see a little more info about this date',
					function() {
						this.parentNode.appendChild(miniTable.node);
					}
				);
				
			},
			'boolean' : function(bool) {
				return util.txt( bool.toString().toUpperCase() );
			},
			'undefined' : function() {
				return util.txt('UNDEFINED');
			},
			'null' : function() {
				return util.txt('NULL');
			},
			'default' : function() {
				/* When a type cannot be found */
				return util.txt('prettyPrint: TypeNotFound Error');
			}
		};
		
		container.appendChild( typeDealer[ (settings.forceObject) ? 'object' : util.type(obj) ](obj, currentDepth) );
		
		return container;
		
	};
	
	/* Configuration */
	
	/* All items can be overwridden by passing an
	   "options" object when calling prettyPrint */
	prettyPrintThis.config = {
		
		/* Try setting this to false to save space */
		expanded: true,
		
		forceObject: false,
		maxDepth: 3,
		maxArray: -1,  // default is unlimited
		styles: {
			array: {
				th: {
					backgroundColor: '#6DBD2A',
					color: 'white'
				}
			},
			'function': {
				th: {
					backgroundColor: '#D82525'
				}
			},
			regexp: {
				th: {
					backgroundColor: '#E2F3FB',
					color: '#000'
				}
			},
			object: {
				th: {
					backgroundColor: '#1F96CF'
				}
			},
			jquery : {
				th: {
					backgroundColor: '#FBF315'
				}
			},
			error: {
				th: {
					backgroundColor: 'red',
					color: 'yellow'
				}
			},
			domelement: {
				th: {
					backgroundColor: '#F3801E'
				}
			},
			date: {
				th: {
					backgroundColor: '#A725D8'
				}
			},
			colHeader: {
				th: {
					backgroundColor: '#EEE',
					color: '#000',
					textTransform: 'uppercase'
				}
			},
			'default': {
				table: {
					borderCollapse: 'collapse',
					width: '100%'
				},
				td: {
					padding: '5px',
					fontSize: '12px',
					backgroundColor: '#FFF',
					color: '#222',
					border: '1px solid #000',
					verticalAlign: 'top',
					fontFamily: '"Consolas","Lucida Console",Courier,mono',
					whiteSpace: 'nowrap',
				},
				td_hover: {
					/* Styles defined here will apply to all tr:hover > td,
						- Be aware that "inheritable" properties (e.g. fontWeight) WILL BE INHERITED */
				},
				th: {
					padding: '5px',
					fontSize: '12px',
					backgroundColor: '#222',
					color: '#EEE',
					textAlign: 'left',
					border: '1px solid #000',
					verticalAlign: 'top',
					fontFamily: '"Consolas","Lucida Console",Courier,mono',
					backgroundImage: util.headerGradient,
					backgroundRepeat: 'repeat-x'
				}
			}
		}
	};
	
	return prettyPrintThis;
	
})();
;
(function($){
  Drupal.behaviors.product_catalog = {
    attach: function(context, settings) {
        $('#nav li').hover(
          function() {
              $('ul',this).slideDown(100);
          },
          function() {
              $('ul',this).slideUp(100);
          }
        ); /* for dropdown sub-nav */
    }
  };

})(jQuery);
;
(function ($) {   
    Drupal.behaviors.testModule = {
        doitnow: function(){
            alert("A new \"tear\" content has just been added!");
        },

        attach: function (context, settings) {
            try{
                if(settings.testModule.tear_just_added){
                    this.doitnow();
                }
            } catch(ex){}
        }
    };
})(jQuery);
;

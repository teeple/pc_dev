(function($) {
	Drupal.behaviors.ProductCatalogTreeBehavior = {
		attach : function(context, settings) {
			$('#dummy-link').hide();
			$.jstree._themes = settings.themes_dir;
			//console.log(context);
			//console.log(settings);

			//bind ajax success callback. changes tree node's title		
				
			$(document).ajaxSuccess(function(event,request, settings) {	
				//console.log(settings.url);
				if(settings.url === '/system/ajax'){
					//console.log(event);
					//console.log(request);
					//console.log(settings);
					var triggeringElement = settings.extraData._triggering_element_name;
					//console.log(triggeringElement);
					if(triggeringElement.match('submit-field_ref_timetable_idd') != null){
						//refresh if tariffplan_idd_carrier has changed its timetable.
						var nodeId = $('.product_catalog_tree').jstree('get_selected').attr('id');
						var node = $('#'+nodeId);
						$.fn.reloadTreeContentDiv(node, 0);						
					}else if(triggeringElement === 'op' && 
							settings.extraData._triggering_element_value === 'Save'){
						var op = $("#tree_node_op").val();
						
						var responseText = request.responseText; 
						var responseJson = $.parseJSON(responseText);
						//console.log(responseJson);
						var product_catalog_ajax_result = responseJson[0].settings.product_catalog_ajax_result;
					
						//console.log(product_catalog_ajax_result);
						//console.log(responseJson);
						if(typeof product_catalog_ajax_result != 'undefined'){
							if(op === 'edit'){		
								// counter list를 보여주고자 할 때에는 변경된 부분을 보이기 위해 전체 tree를 refresh한다.
								var needToReloadAll = false;		
								if(product_catalog_ajax_result.need_to_reload_all instanceof Array){
									for(var i=0;i<product_catalog_ajax_result.need_to_reload_all.length;i++){
										if(needToReloadAll == true) break;
										needToReloadAll = product_catalog_ajax_result.need_to_reload_all[i];
									}
								}else{
									needToReloadAll = product_catalog_ajax_result.need_to_reload_all;
								}
								
								var needToRefreshNode = false;
								if(product_catalog_ajax_result.need_to_refresh_node instanceof Array){
									for(var i=0;i<product_catalog_ajax_result.need_to_refresh_node.length;i++){
										if(needToRefreshNode == true) break;
										needToRefreshNode = product_catalog_ajax_result.need_to_refresh_node[i];
									}
								}else{
									needToRefreshNode = product_catalog_ajax_result.need_to_refresh_node;
								}
								
								if(needToReloadAll){
									var treeData = $.parseJSON(product_catalog_ajax_result.data[0]);
					
									$.jstree._focused()._get_settings().json_data.data = treeData;
									$.jstree._focused().refresh(-1);
				
									$.fn.unmasking();
				
									$(".product_catalog_tree").jstree('open_all');
								}
								else if(needToRefreshNode){
									var nodeId = null;
									if(product_catalog_ajax_result.reload_node_id instanceof Array){
										for(var i=0;i<product_catalog_ajax_result.reload_node_id.length;i++){
											if(nodeId != null) break;
											nodeId = product_catalog_ajax_result.reload_node_id[i];
										}
									}else{
										nodeId = product_catalog_ajax_result.reload_node_id;
									}
									var node = $('#' + nodeId);
									$.fn.reloadTreeContentDiv(node);
								}
								else{
									if( product_catalog_ajax_result.data.nid instanceof Array) {
										$(".product_catalog_tree").jstree("set_text", $('#' + product_catalog_ajax_result.data.nid[0]), product_catalog_ajax_result.data.title[0]);
									}else{
										$(".product_catalog_tree").jstree("set_text", $('#' + product_catalog_ajax_result.data.nid), product_catalog_ajax_result.data.title);
									}
								}
							}else if(op === 'add'){
								$.fn.addNestedMultipleChildren(product_catalog_ajax_result);
								$("#form_content > form").replaceWith('<br/>');								
							}
						}						
					}
				} else if (settings.url == '/product_catalog_ajax/set_rollover') {
					
					// var selectTreeTid = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.select_tree_id;
					var parentId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.parentId;
					var childId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.childId;
					var title = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.title;
					var contentType = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.contentType;
					var weight = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.weight;
					
					if( $('#'+childId).length >0 ) {
						$(".product_catalog_tree").jstree("set_text", $('#' + childId), title);
						$('#'+childId).trigger('click');
					} else {
						$.fn.addTreeItemCallback(parentId, childId, title,contentType, weight);
						$('#'+childId).trigger('click');	
					}
					
				} else if (settings.url == '/product_catalog_ajax/set_cardtype') {
					var parentId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.parentId;
					var childId = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.childId;
					var title = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.title;
					var contentType = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.contentType;
					var weight = $.parseJSON(request.responseText)[0].settings.product_catalog_ajax_result.data.weight;
					
					// In case Edit
					if( $('#'+childId).length >0 ) {
						if( title instanceof Array) {
							title = title[0];
						}
						$(".product_catalog_tree").jstree("set_text", $('#' + childId), title);
						// $('#'+childId).trigger('click');
					// In case Create
					} else {
						$.fn.addTreeItemCallback(parentId, childId, title, contentType, weight);
						$('#'+childId).trigger('click');	
					}
				} else {
				}
			});
			
			//initialize tree
			var treeType = settings.product_catalog_tree_type;
			var types = $.fn.getTreeTypeSetting(treeType);
			
			if(settings.product_catalog_tree_data){
				$(".product_catalog_tree").jstree({
					"core" : {},
					"json_data" : {
						"data" : settings.product_catalog_tree_data,
						"progressive_render" : true,
					},
					"plugins" : [ "types", "themes", "json_data",
							"ui", "contextmenu", "crrm", "dnd" ,"search"],
					"ui" : {
						"select_multiple_modifier" : false,
						"initially_select" : [ settings.product_catalog_tree_data[0].attr.root_nid ],
						"select_limit" : 1
					},
					"crrm" : {
					        "move" : {
					            "check_move" : function (m) {
					            		if(m.o.attr('rel') == 'tree_node_counter_main_basic_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_postpaid'
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_prepaid_removable' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_basic_postpaid_removable'
					            			|| m.o.attr('rel') == 'tree_node_counter_main_optional_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_optional_postpaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_rollover_prepaid' 
					            			|| m.o.attr('rel') == 'tree_node_counter_main_rollover_postpaid' 
					            			|| m.o.attr('rel') == 'actionpriceallowanceonetime'
					            			|| m.o.attr('rel') == 'actionpricechargerecurring'
					            			) {
					            			
						            			if(m.op.attr('rel') == m.np.attr('rel') ) {
						            				return true;
															} else {
						            					return false;
						            			}
						            			
					            		} else {
					            			return false;
					            		}
					            }
					        }
					},
					"types" : types,
					"contextmenu" : {
						"select_node": true,
						"items" : function(obj) {
							var menus = $.fn.getTreeContextMenuSetting(treeType,obj);
							return menus;
						},
					},
				});
			}
		
			//bind load event for loading data from the server.
			$(".product_catalog_tree").bind("loaded.jstree",function(e, data) {
					$.fn.masking('Loading...');
	
					var rootNid = settings.product_catalog_tree_data[0].attr.root_nid;
					var ajaxUrl = '/product_catalog_ajax/nojs/loadTree/' + rootNid;
	
					$.ajax({
						url : ajaxUrl,
						dataType : 'json',
						success : function(data) {
							//console.log('haha');
							$.jstree._focused()._get_settings().json_data.data = data;
							$.jstree._focused().refresh(-1);
 
							$.fn.unmasking();
							
							//console.log(data);
							
							// 임시로 모두 오픈
							$(".product_catalog_tree").jstree('open_all');
							
//							alert(window.location.href);
//							
//							var params = {};
//							
//							if (location.search) {
//							    var parts = location.search.substring(1).split('&');
//							
//							    for (var i = 0; i < parts.length; i++) {
//							        var nv = parts[i].split('=');
//							        if (!nv[0]) continue;
//							        params[nv[0]] = nv[1] || true;
//							    }
//							}
//							
//							// Now you can get the parameters you want like so:
//							var abc = params.tree_item_id;
//							console.log(abc);
//							
//							if(abc) {
//								var foundItem = $('#'+abc);
//								console.log(foundItem);
//								if(foundItem) {
//									$(".product_catalog_tree").jstree('close_all');
//									$(".product_catalog_tree").jstree("select_node", "#"+abc);					
//								}
//							}
						},
						error: function(jqXHR, textStatus, errorThrown){
							//console.log('ajax error');
							//console.log(jqXHR, textStatus, errorThrown);
						}
					});
			});
			
			//bind click event for loading form
			$(".product_catalog_tree").bind("click.jstree", function (e, data) {
				var node = $(e.target).closest("li");
	            $("#tree_node_op").val('edit');
	            $.fn.loadForm(node,null);
	        });
			
			//bind move event
			$(".product_catalog_tree").bind(
				"move_node.jstree",
				function(e, data) {
					/*
					 * data.rslt contains: .o - the node being moved
					 * .r - the reference node in the move .ot - the
					 * origin tree instance .rt - the reference tree
					 * instance .p - the position to move to (may be
					 * a string - "last", "first", etc) .cp - the
					 * calculated position to move to (always a
					 * number) .np - the new parent .oc - the
					 * original node (if there was a copy) .cy -
					 * boolen indicating if the move was a copy .cr -
					 * same as np, but if a root node is created
					 * this is -1 .op - the former parent .or - the
					 * node that was previously in the position of
					 * the moved node
					 */
					var children = Array();
	
					var childNid = data.rslt.o[0].attributes[0].value;
					var weightStep = 100;
	
					var nextSiblingWeight = (data.rslt.o[0].nextSibling == null) ? -1 : data.rslt.o[0].nextSibling.attributes[3].value;
					var prevSiblingWeight = (data.rslt.o[0].previousSibling == null) ? -1 : data.rslt.o[0].previousSibling.attributes[3].value;
	
					var parentNid = data.rslt.np[0].attributes[0].value;
					var oldParentNid = data.rslt.op[0].attributes[0].value;
	
					var parent = {
						'changed' : (parentNid == oldParentNid) ? false : true,
						'nid' : parentNid,
					};
	
					children[0] = {
						'nid' : childNid,
					};
	
					if (prevSiblingWeight == -1 && nextSiblingWeight == -1) {
						children[0].weight = 0;
					} else if (prevSiblingWeight == -1) {
						children[0].weight = parseInt(nextSiblingWeight) + weightStep;
					} else if (nextSiblingWeight == -1) {
						children[0].weight = parseInt(prevSiblingWeight) - weightStep;
					} else {
						var pivot = parseInt((parseInt(nextSiblingWeight) + parseInt(prevSiblingWeight)) / 2);
						if (pivot == 0) {// 전체..
							children[0].weight = parseInt(nextSiblingWeight) + weightStep;
							var prevNode = data.rslt.o[0].previousSibling;
							var index = 1;
							while (prevNode != null) {
								children[index] = {
									'nid' : prevNode.attributes[0].value,
									'weight' : children[index - 1].weight + weightStep
								};
								prevNode = prevNode.previousSibling;
								index++;
							}
						} else {
							children[0].weight = pivot;
						}
					}
	
					for ( var i = 0; i < children.length; i++) {
						var node = $("#" + children[i].child_nid);
					}
	
					// send to server
					editLink = '/product_catalog_ajax/nojs/move_node';
	
					$.fn.masking('Progress');
					$.ajax({
						url : editLink,
						type : 'POST',
						dataType : 'json',
						data : {
							"nodes" : children,
							"parent" : parent
						},
						success : function(data) {
							for ( var i = 0; i < children.length; i++) {
								node = $('#' + children[i].nid);
								node.attr('weight',children[i].weight);
							}
							$.fn.unmasking();
						},
						error : function() {
							$.jstree._focused().rollback(data.rlbk);
							$.fn.unmasking();
						}
					});

			});

			/*
			$(".product_catalog_tree").bind("rename.jstree", function(e, data) { // $.jstree.rollback(data.rlbk);
				// console.log('rename');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("remove.jstree", function(e, data) {
				console.log('remove');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("create.jstree", function(e, data) { // $('#dialog').text('Do
				// you
				// want
				// to
				// delete');
				// $('#dialog').dialog('open'); console.log('create');
				console.log(e);
				console.log(data);
			});
			$(".product_catalog_tree").bind("move_node.jstree",
				function(e, data) {
					console.log('move_node');
					console.log(e);
					console.log(data);
			});
			*/
			// Drupal.detachBehaviors(productCatalogTreeBehavior);
			
			//operations
			$('#tree_op_expand').bind('click',{},$.fn.treeOpExpand);
			$('#tree_op_close').bind('click',{},$.fn.treeOpClose);
			$('#tree_op_search_button').bind('click',{},$.fn.treeOpSearch);
			$('#tree_op_search_clear').bind('click',{},$.fn.treeOpSearchClear);
			delete Drupal.behaviors.ProductCatalogTreeBehavior;
		}
	};
})(jQuery);

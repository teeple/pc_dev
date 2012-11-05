(function($) {
	Drupal.behaviors.ProductCatalogTreeBehavior = {
		attach : function(context, settings) {
			$('#dummy-link').hide();
			$.jstree._themes = settings.themes_dir;
			//console.log(context);
			//console.log(settings);

			//bind ajax success callback. changes tree node's title			
			$(document).ajaxSuccess(function(event,request, settings) {
				//console.log(event,request, settings);
				if(settings.url === '/system/ajax'){
					if(settings.extraData._triggering_element_name === 'op' && 
							settings.extraData._triggering_element_value === 'Save'){
						var op = $("#tree_node_op").val();
						
						var responseText = request.responseText; 
						var responseJson = $.parseJSON(responseText);
						var product_catalog_ajax_result = responseJson[0].settings.product_catalog_ajax_result;
					
						//console.log(product_catalog_ajax_result);
						//console.log(responseJson);
						if(typeof product_catalog_ajax_result != 'undefined'){
							if(op === 'edit'){				
								$(".product_catalog_tree").jstree("set_text", $('#' + product_catalog_ajax_result.data.nid), product_catalog_ajax_result.data.title);
							}else if(op === 'add'){
								$.fn.addNestedMultipleChildren(product_catalog_ajax_result);
								$("#form_content > form").replaceWith('<br/>');								
							}
						}						
					}
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
							"ui", "contextmenu", "crrm", "dnd" ],
					"ui" : {
						"select_multiple_modifier" : false,
						"initially_select" : [ settings.product_catalog_tree_data[0].attr.root_nid ]
					},
					"types" : types,
					"contextmenu" : {
						"items" : function(obj) {
							var menus = $.fn.getTreeContextMenuSetting(treeType,obj);
							return menus;
						},
					},
				});
			}
		
			//bind load event for loading data from the server.
			$(".product_catalog_tree").bind("loaded.jstree",function(e, data) {
					$(".product_catalog_tree").mask('Loading...');
	
					var rootNid = settings.product_catalog_tree_data[0].attr.root_nid;
					var ajaxUrl = '/product_catalog_ajax/nojs/loadTree/' + rootNid;
	
					$.ajax({
						url : ajaxUrl,
						dataType : 'json',
						success : function(data) {
							//console.log('haha');
							//console.log(data);
							$.jstree._focused()._get_settings().json_data.data = data;
							$.jstree._focused().refresh(-1);

							$(".product_catalog_tree").unmask();

							// 임시로 모두 오픈
							$(".product_catalog_tree").jstree('open_all');
						},
						error: function(jqXHR, textStatus, errorThrown){
							//console.log('ajax error');
							//console.log(jqXHR, textStatus, errorThrown);
						}
					});
					// $.jstree.rollback(data.rlbk);
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
	
					$(".product_catalog_tree").mask();
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
							$(".product_catalog_tree").unmask();
						},
						error : function() {
							$.jstree._focused().rollback(data.rlbk);
							$(".product_catalog_tree").unmask();
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
			delete Drupal.behaviors.ProductCatalogTreeBehavior;
		}
	};
})(jQuery);

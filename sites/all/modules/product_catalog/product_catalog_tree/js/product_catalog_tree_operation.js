(function($) {
	$.fn.loadSelectForm = function(node){
		var nodeId = node.attr('id');
		var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
		var loadLink = '/product_catalog_ajax/load_select_form/' + nodeId + '/' + 'right_click' + '/' + rootId + '/' + node.attr('rel');
		$(".product_catalog_tree").mask("Loading...");
		//console.log(loadLink);
		$.ajax({
			url : loadLink,
			success : function(data) {
				var output = $.parseJSON(data);
				//console.log(output);
				var settings = output[0].settings;
				var context = output[1];
				$('#tree_content_div').replaceWith(context);
				//console.log(output);
				if( typeof settings.views != 'undefined') {
					$.extend(Drupal.settings.views.ajaxViews,settings.views.ajaxViews);
				}
				
				$.fn.behaviorAttach(settings);
				
				$('#tree_content_div').append('<div style="clear:both;"><input id="vbo-select-button" type="button" value="Select"/></div>');
				$('#vbo-select-button').bind('click',{rootId:rootId, node: node},$.fn.selectItemHandler);

				$(".product_catalog_tree").unmask();
			}
		});
	};
	
	// select_load_form -> selectItemHandler
	//
	$.fn.selectItemHandler = function(event){
		
		var parent = event.data.node; 
        var rootId = event.data.rootId;
		//jQuery('input[name=views_bulk_operations]:checked')		
		var inputItems = $('input[name^=views_bulk_operations]:checked');
		
		if(inputItems.length == 0) {
			// �ν� Drupal message ���濡�蹂�꼍??
			alert('No Item Selected!');
			
		}else{
			$(".product_catalog_tree").mask("Adding...");

			var selectedItemNid = new Array();
			for(var i=0;i<inputItems.length;i++) {
				selectedItemNid[i] = inputItems[i].value;
			}
			
		    var max_weight = parent.children('ul').children('li').first().attr('weight');
		    if(max_weight == 'undefined') max_weight = 0;
		    var min_weight = parent.children('ul').children('li').last().attr('weight');
		    if(min_weight == 'undefined') min_weight = 0;
		    
			var selectItemUrl = '/product_catalog_ajax/select_item';
			$(".product_catalog_tree").mask("Adding...");
			$.ajax({
				url : selectItemUrl,
				type: "post",
		        data: {'product_nid': rootId, 'parent_nid': parent.attr('id'), 'child_nid': selectedItemNid, 'rel_type': parent.attr('rel'),'max_weight':max_weight, 'min_weight':min_weight,'parent_title':parent.children('a').text()},
				success : function(data) {
					var output = $.parseJSON(data);
					
					var product_catalog_ajax_result = output[0].settings.product_catalog_ajax_result;
					
					// 留�� 湲곗〈���щ���� children��吏��二쇱�����寃쎌���� 
					if(product_catalog_ajax_result.data.replace_or_append == 'replace') {
						var parentObj = $('.product_catalog_tree').jstree('get_json', parent)[0];
						var children = $.fn.getChildrenNotSelf(parentObj);
						for(var i=0;i<children.length;i++){
							$('.product_catalog_tree').jstree('delete_node', $('#'+children[i]));
						}
					}
					
					$.fn.addUnNestedMultipleChildren(product_catalog_ajax_result);
					
					var message = '<div style="display:block;"><div class="messages status"><h2 class="element-invisible">Status message</h2>'
						+ product_catalog_ajax_result.data.parent_title + ' has been changed.</div></div>';
					
					$.fn.clearTreeContentDiv(message);
					$(".product_catalog_tree").unmask();
				}
			});
			
		}		
	};
	
	$.fn.clearTreeContentDiv = function(message){
		$('#tree_content_div').replaceWith('<div id="tree_content_div" style="overflow:scroll;height:700px;"></div>');
		if(message != 'undefined') $('#tree_content_div').prepend(message);
	};
	
	$.fn.deleteFromView = function(parent_id,id,content_type){
		var deleteUrl = '/product_catalog_ajax/delete_from_view/' + id;
		var parentNode = $('#'+parent_id);
		$(".product_catalog_tree").mask("Deleting...");
		$.ajax({
			url : deleteUrl,
			success : function(data) {
				switch(content_type){
				case 'basicrate_domestic':
					$.fn.loadForm(parentNode,null);
					break;
				case 'basicrate_idd':
					$.fn.loadForm(parentNode,null);
					break;
				}
				$(".product_catalog_tree").unmask();
				//$.fn.loadForm(parent_id,content_type);
			}
		});	
	};
	
	$.fn.loadForm = function(node,collapsedIndex,defaultTabIndex){
		
		var id = node.attr("id");
        var content_type = node.attr("node_type");
        var rel_type = node.attr("rel");
        
		var needToLoadEdit = true; 
        var needToLoadDetail = true;
        var needToBindCustomSubmitButtons = false;
        
        switch(content_type){
            case 'treenodecounter':
            case 'treenodedepositscheme':
            case 'treenodethresholdscheme':
            case 'treeNodeBasicRateIDD':
            case 'treenodevouchercardforproduct':
            case 'prdattributepackaged':
            case "treenodeproductforvoucher":
            case 'treenodeunittransferscheme':
            case 'actionpricechargeonetime':
            case 'actionpriceallowanceonetime':
            case 'actionpricechargerecurring':
            case 'actionpriceallowancerecurring':
            	needToLoadEdit = false;
                break;
            case 'usage':
            case 'conditioncommonor':
            case 'conditioncommonand':
            case 'defaulttreenode':
            case 'conditionwhatincomingcall':
            	needToLoadEdit = false;
            	needToLoadDetail = false;
            	break;
            case 'conditionwhencustomerbirthday':
            	needToLoadEdit = false;
            	needToLoadDetail = false;
            	break;
            case 'conditionwhencompanybirthday':
            	needToLoadEdit = false;
            	needToLoadDetail = false;
            	break;
            case 'conditionwhenfirstmonth':
            	needToLoadEdit = false;
            	needToLoadDetail = false;
            	break;
            case 'treenodewithnodereference':
            	switch(rel_type){
            	case 'treenode_timetable':
            		needToLoadDetail = false;
            		break;
                case 'treenode_simpleproductoffering':
                    needToLoadEdit = false;
                    break;
            	default:
            		needToLoadEdit = false;
            		break;
            	}
            	break;
            case 'number_special':
            	needToLoadDetail = false;
            	break;
            case 'term':
            	switch(rel_type){
            	case 'voice_tariffplan_domestic':
            	case 'voice_tariffplan_international':   
            	case 'sms_tariffplan_domestic':
            	case 'sms_tariffplan_international': 
            	case 'mobile_counter':
            		needToLoadEdit = false;
            		needToBindCustomSubmitButtons = true;
            		break;
            	}
            	
            	case 'allowed':
            		needToLoadEdit = false;
            		break;
            	break; 
            	           
            case 'treenodecounterforvoucherprd':
            	needToLoadEdit = false;
        		needToBindCustomSubmitButtons = true;
        		break;
            default :
            	needToLoadDetail = false;
            	break;
        }
        
        // �대� content type��edit form�������
        if(needToLoadEdit){
            var editLink = '/product_catalog_ajax/nojs/edit/' + content_type + '/' + id;
            $(".product_catalog_tree").mask("Loading...");
    		$.ajax({
    			url : editLink,
    			success : function(data) {
    				var output = $.parseJSON(data);
    				var settings = output[0].settings;
    				var context = output[1];
    				$('#tree_content_div').replaceWith(context);
    				$.fn.behaviorAttach(settings);
    				$(".product_catalog_tree").unmask();
    			}
    		});
        }
        
        if(needToLoadDetail){
        	var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
        	var detailLink = '/product_catalog_ajax/load_select_form/' + id + '/' + 'click' + '/' + rootId + '/' + rel_type;
        	
        	if(defaultTabIndex > 0) {
        		detailLink = detailLink + '/' + defaultTabIndex;
        	}
    		
        	$(".product_catalog_tree").mask("Loading...");
    		$.ajax({
    			url : detailLink,
    			success : function(data) {
    				var output = $.parseJSON(data);
    				var settings = output[0].settings;
    				var context = output[1];
    				$('#tree_content_div').replaceWith(context);
    				$.fn.behaviorAttach(settings);
    				
    				//for basicrate
    				if(needToBindCustomSubmitButtons){
    					var tariffplanNid = $('#tariffplanNid').attr('value');
    					var refTreeTid = $('#refTreeTid').attr('value');
    					
    					$('#select_numberingplan_domestic').bind('click',
    							{'type':'select_numberingplan_domestic'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_timetable_domestic').bind('click',
    							{'type':'select_timetable_domestic'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_numberingplan_idd').bind('click',
    							{'type':'select_numberingplan_idd'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    					$('#select_timetable_idd').bind('click',
    							{'type':'select_timetable_idd'
    							,'node':node
    							,'tariffplanNid':tariffplanNid
    							,'refTreeTid':refTreeTid}
    					   ,$.fn.customSubmitButtonHandler);
    				}    		
    				
    				//selected region
    				if(collapsedIndex != null){
    					$.fn.setFocuseSelectedRegion(collapsedIndex);
    				}
    				
    				$(".product_catalog_tree").unmask();
    			} 
    		});
        }
	};
	
	$.fn.setFocuseSelectedRegion = function(collapsedIndex){
		var regions = $('#tree_content_div').find('.ctools-toggle');
		
		for(var i=0;i<regions.length;i++){	
			if($.inArray(i, collapsedIndex) > -1){				
				$('#tree_content_div').find('.ctools-toggle:eq('+i+')').addClass('ctools-toggle-collapsed');
				$('#tree_content_div').find('.ctools-collapsible-content:eq('+i+')').attr('style','display:none');
			}else{
				$('#tree_content_div').find('.ctools-toggle:eq('+i+')').removeClass('ctools-toggle-collapsed');
				$('#tree_content_div').find('.ctools-collapsible-content:eq('+i+')').attr('style','display:block');
			}				
		}		
	};
	
	$.fn.customSubmitButtonHandler = function(event){		
		var isSelect = false;
		var data = event.data;		
		
		switch(data.type){
		case 'select_numberingplan_domestic':			
		case 'select_numberingplan_idd':			
		case 'select_timetable_domestic':
		case 'select_timetable_idd':
			isSelect = true;
			break;
		}
		
		if(isSelect){
			var findStr = '\'.' + data.type + '_rows > div > input[name^=views_bulk_operations]:checked\'';			
			var inputItems = $(findStr);
			
			if(inputItems.length == 0){
				// �ν� Drupal message ���濡�蹂�꼍??
				alert('No Item Selected!');
			}else{
				var selectedItemNid = new Array();
				for(var i=0;i<inputItems.length;i++){
					selectedItemNid[i] = inputItems[i].value;
				}
				
				var customSubmitUrl = '/product_catalog_ajax/custom_submit';				
				$.ajax({
					url : customSubmitUrl,
					type: "post",
			        data: {'type': data.type, 'tariffplanNid': data.tariffplanNid, 'refTreeTid': data.refTreeTid, 'selected_nid': selectedItemNid},
					success : function(result) {
						$.fn.reloadTreeContentDiv(data.node);											
					}
				});
				
			}
		}
		
	};
	
	$.fn.reloadTreeContentDiv = function(node, tabIndex){
		//for setFocusRegion
		var regions = $('#tree_content_div').find('.ctools-toggle');
		var collapsedIndex = new Array();
		for(var i=0;i<regions.length;i++){	
			if($('#tree_content_div').find('.ctools-toggle:eq('+i+')').hasClass('ctools-toggle-collapsed')){
				collapsedIndex.push(i);
			}
		}
		$.fn.loadForm(node,collapsedIndex, tabIndex);	
	};
	
	/*
	$.fn.reloadTreeContentDivFromDrupal = function(nodeId, tabIndex){
		var node = $('#' + nodeId);
		console.log('here');
		console.log(tabIndex);
		$.fn.reloadTreeContentDiv(node);
	};
	*/
	
	$.fn.reloadTreeContentDivFromDrupal = function(nodeId, tabIndex){
		var node = $('#' + nodeId);
		
		$.fn.reloadTreeContentDiv(node, tabIndex);
	};
	
	$.fn.addNestedMultipleChildren = function(product_catalog_ajax_result){		
		var parentNode;
		var returnData;
		var tree = $.jstree._reference(".product_catalog_tree");
		//console.log(product_catalog_ajax_result);
		parentNode = $('#'+product_catalog_ajax_result.parent_nid);
		returnData = tree._parse_json(product_catalog_ajax_result.data);
		
        var attachChild = returnData.children("li");
        if(!parentNode.children("ul").length) { parentNode.append("<ul />"); }
        parentNode.children("ul").prepend(attachChild);
        tree.clean_node(parentNode);
        $(".product_catalog_tree").jstree("open_node", attachChild , function (){} , false);        
		
	};
	
	$.fn.addUnNestedMultipleChildren = function(product_catalog_ajax_result){		
		var parentNode;		
		parentNode = $('#'+product_catalog_ajax_result.data.parent_nid);		
		
		for(var i=0;i<product_catalog_ajax_result.data.children.length;i++){
			$(".product_catalog_tree").jstree("create", parentNode,product_catalog_ajax_result.data.append_to
				,{"data" : product_catalog_ajax_result.data.children[i].data
				,"attr" : {"id" : product_catalog_ajax_result.data.children[i].attr.id
						  ,"node_type" : product_catalog_ajax_result.data.children[i].attr.node_type
						  ,"rel" : product_catalog_ajax_result.data.children[i].attr.rel
						  ,"weight" : product_catalog_ajax_result.data.children[i].attr.weight}}, function() {}, true);	
				
		}		
	};
	
	$.fn.behaviorAttach = function(settings){	
		//console.log('mutiselect_behavior set');
		Drupal.behaviors.quicktabs.attach(document,settings);
		Drupal.behaviors.ViewsAjaxView.attach();		
		Drupal.behaviors.multiselect.attach(document);		
		Drupal.behaviors.AJAX.attach(document, settings);
		Drupal.settings.datePopup = settings.datePopup;
		Drupal.behaviors.date_popup.attach(document);
		Drupal.behaviors.tableDrag.attach(document, settings);
		Drupal.behaviors.tableHeader.attach(document, settings);	
		Drupal.behaviors.states.attach(document,settings);	
		Drupal.behaviors.vbo.attach(document);
		Drupal.behaviors.ZZCToolsModal.attach(document);
		Drupal.behaviors.editablefields_submit.attach(document);
		Drupal.behaviors.CToolsAutoSubmit.attach(document);
    //Drupal.behaviors.bef_live_filter.attach(document);
		
    Drupal.behaviors.CToolsCollapsible.attach(document);
    //Drupal.behaviors.qt_accordion.attach($('#tree_content_div'),settings);
    //Drupal.behaviors.qt_ui_tabs.attach(document,settings);
        
    $.fn.drawFlotLinkInit();
    
    
        
	};
	
	/*
	$.fn.getParentIdWithRelType = function(node,relType){
		var parentId = node.attr('parent_nid');
		var parentNode = $('#'+parentId);
		var parentRelType = parentNode.attr('rel');
		
		if(relType == parentRelType) {
			return parentId;
		} 
		else {
			return $.fn.getParentIdWithRelType(parentNode,relType);
		}
	};
	*/
	
	$.fn.addNode = function(parentNode, param) {
		$("#tree_node_op").val('add');
		//console.log(childContentType);
		var parentNodeId = parentNode.attr('id');
		var max_weight = parentNode.children('ul').children('li').first().attr('weight');
		if(max_weight == undefined) max_weight = 0;
		var rootId = $('.product_catalog_tree > ul:first > li:first').attr('id');
        var addLink = '/product_catalog_ajax/nojs/add/';
        
        var ajaxParam = {'root_id': rootId, 'parent_id': parentNodeId, 'child_content_type': param.childContentType
	        	, 'max_weight': max_weight, 'usage_type' : param.usageType, 'nonusage_type' : param.nonUsageType};
        
        /*
        switch(parentNode.attr('rel')){
	        case 'voice_tariffplan_domestic':
	        case 'voice_tariffplan_international':
	        case 'voice_tariffplan_specialnumbers':
	        case 'treeNodeCustomCharge':
	        case 'treeNodeCustomDiscount':
	        case 'treeNodeCustomAllowance':
	        	var tariffPlanId = $.fn.getParentIdWithRelType(parentNode,'tariffplan');
	        	
	        	ajaxParam.tariffplan_id = tariffPlanId;
	        	break;
        }
        */
        
        $(".product_catalog_tree").mask("Adding...");
		$.ajax({
			url : addLink,
			type: "post",
	        data: ajaxParam,
			success : function(data) {
				var output = $.parseJSON(data);			
				if(output != null){
					if(output instanceof Array == false){
						$.fn.addTreeItemCallback(output.parent_id, output.child_id,output.title, output.node_type, output.weight);
					}else{
						var settings = output[0].settings;
						var context = output[1];
						$('#tree_content_div').replaceWith(context);
						$.fn.behaviorAttach(settings);
					}
				}
				$(".product_catalog_tree").unmask();
			}
		});
	};
	
	$.fn.getChildrenNotSelf = function(node) {
		
		var children = new Array();
		
		var parent = $('.product_catalog_tree').jstree('get_json', parent)[0];
		
		if (node.children != null) {
			for ( var index = 0; index < node.children.length; index++) {
				$.merge(children, $.fn.getChildren(node.children[index]));
			}
		} else if ((node.metadata != null)
				&& (node.metadata.jstree_children != null)) {
			for ( var index = 0; index < node.metadata.jstree_children.length; index++) {
				$.merge(children,$.fn.getChildren(node.metadata.jstree_children[index]));
			}
		}

		if (children.length > 0) {
			return children;
		} else {
			return children;
		}
	};
	
	$.fn.getChildren = function(node) {
		var children = new Array();

		children.push(node.attr.id);

		if (node.children != null) {
			for ( var index = 0; index < node.children.length; index++) {
				$.merge(children, $.fn.getChildren(node.children[index]));
			}
		} else if ((node.metadata != null)
				&& (node.metadata.jstree_children != null)) {
			for ( var index = 0; index < node.metadata.jstree_children.length; index++) {
				$.merge(children,$.fn.getChildren(node.metadata.jstree_children[index]));
			}
		}

		if (children.length > 0) {
			return children;
		} else {
			return;
		}
	};

	$.fn.deleteNode = function(node) {
		$(".product_catalog_tree").mask("Deleting...");
		var jsonData = $(".product_catalog_tree").jstree("get_json", node);
		var children = $.fn.getChildren(jsonData[0]);
		//console.log(jsonData[0]);
		var delLink = '/product_catalog_ajax/nojs/delete_from_tree';

		$.ajax({
			url : delLink,
			type : 'POST',
			dataType : 'json',
			data : {
				"nodes" : children
			},
			success : function(data) {
				var rel_type = node.attr("rel");				
				$.jstree._focused().delete_node(node);
				$.fn.clearTreeContentDiv();
				$(".product_catalog_tree").unmask();
				
				if(rel_type === 'simpleproductoffering'){
					$(location).attr('href',"/product_designer");
				}else if(rel_type === 'number_special'){
					$(location).attr('href',"/common/vouchercardtype#quickset-qtabs_common_data=6");
				}else if(rel_type === 'vouchercardtype'){
					$(location).attr('href',"/common/vouchercardtype");
				}						
			}
		});
        //history.go(0);
	};	
	
	$.fn.addTreeItemCallback = function(parentId, childId, title,contentType, weight) {
		$(".product_catalog_tree").mask("Adding...");
		$(".product_catalog_tree").jstree("create", $('#' + parentId),"inside", {"data" : title,"attr" : {"id" : childId,"node_type" : contentType,"rel" : contentType,"weight" : weight}}, function() {}, true);
		$(".product_catalog_tree").unmask();
	};
	
})(jQuery);
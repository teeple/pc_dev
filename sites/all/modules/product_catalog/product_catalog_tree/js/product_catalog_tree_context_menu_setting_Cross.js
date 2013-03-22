(function($) {
	$.fn.getTreeContextMenuSetting = function(treeType, obj) {
		var menus = {
			"rename" : false,
			"remove" : false,
			"create" : false,
			"ccp" : false,
			"custom_create" : {
				"label" : "Add",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_copy" : {
				"label" : "Copy",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_paste" : {
				"label" : "Paste",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
			"custom_delete" : {
				"label" : "Delete",
				"action" : null,
				"submenu" : null,
				"_disabled" : true,
			},
		};

		switch (treeType) {
			case "product_tree":
				var relType = obj.attr("rel");
				console.log('relType');
				console.log(relType);
				switch (relType) {
					case "treenodevouchercardforproduct":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"TransferBonus" : {
								"label" : "TransferBonus",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionbonustransfer'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'actionbonustransfer':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "prdattributeprefixrangeallowed":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "prdnonusagerollover":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "treenodespecialnumberscheme":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;

					case "prdattributeprefixrangenotallowe":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "packaged_mandatory":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_packaged_mandatory" : {
							"packaged_mandatory" : {
								"label" : "Select Product",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "attribute_featurecode":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_packaged_hidden" : {
							"attribute_featurecode" : {
								"label" : "Select FeatureCode",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case 'prdattributefeaturecode':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "packaged_product":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_packaged_product" : {
							"packaged_product" : {
								"label" : "Select Product",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;	
					case "packaged_optional":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_packaged_optional" : {
							"packaged_optional" : {
								"label" : "Select Product",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "packaged_hidden":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_packaged_hidden" : {
							"packaged_hidden" : {
								"label" : "Select Product",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case 'prdattributepackaged':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "available_product":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"available_product" : {
								"label" : "Select Product",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "simpleproductoffering":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case "tree_node_counter_main_basic_prepaid":
					case "tree_node_counter_main_basic_postpaid":
						/*
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						*/				
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treenode_counter_main_basic" : {
								"label" : "Condition Set",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					case 'tree_node_counter_main_rollover_prepaid':
					case 'tree_node_counter_main_rollover_postpaid':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treenode_counter_main_basic" : {
								"label" : "Condition Set",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					case "tree_node_counter_main_optional_prepaid":
					case "tree_node_counter_main_optional_postpaid":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treenode_counter_main_optional" : {
								"label" : "Condition Set",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					case "tree_node_counter_accumulated_basic_prepaid":
					case "tree_node_counter_accumulated_basic_postpaid":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"tree_node_counter_accumulated_basic" : {
								"label" : "Condition Set",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
						
					case "counter_main":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_counter_main" : {
							"counter_main" : {
								"label" : "Select Counter",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "nonusage_deposit":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_nonusage_deposit" : {
							"nonusage_deposit" : {
								"label" : "Select Deposit Scheme",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};						
						break;
						
					case 'nonusage_otheronetimecharge':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_nonusage_otheronetimecharge" : {
							"nonusage_otheronetimecharge" : {	
								"label" : "Select Other Onetime Charge",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case 'treenodeotheronetimecharge':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					break;
					
					case 'nonusage_bonus_transfer':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_bonus_transfer" : {
							"nonusage_bonus_transfer" : {	
								"label" : "Select Voucher Card Type",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case 'treenodedepositscheme':
					case 'treenodethresholdscheme':
					case 'treenodeunittransferscheme':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case "nonusage_threshold":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_threshold" : {
							"nonusage_threshold" : {
								"label" : "Select Threshold Scheme",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;

					case "counter_accumulated":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_counter_accumulated " : {
							"counter_accumulated " : {	
								"label" : "Select Counter",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case "nonusage_unittransfer_scheme":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unittransfer_scheme" : {
							"nonusage_unittransfer_scheme" : {	
								"label" : "Select Unit Transfer",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case "attribute_subscriber_lifecycle_scheme":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_attribute_subscriber_lifecycle_scheme" : {
							"attribute_subscriber_lifecycle_scheme" : {
								"label" : "Select Lifecycle Scheme",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case 'treenodelifecyclescheme':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case 'nonusage_rollover':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//'mobile_nonusgae_rollover' : {
							'nonusgae_rollover' : {
								"label" : "RollOver",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'prdnonusagerollover'
									});
								}
							},
						};
						break;
					case "treeNodeCustomCharge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeCustomCharge" : {
								"label" : "Charge Factors",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargefactors'
									});
								}
							},
						};
						break;
					case "treeNodeCustomDiscount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeCustomDiscount" : {
								"label" : "Discount Factors",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricediscountfactors'
									});
								}
							},
						};
						break;
					case "treeNodeCustomBlock":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeCustomBlock" : {
								"label" : "Block Service Factors",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionblockfactors'
									});
								}
							},
						};
						break;
					case 'actionblockfactors':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionblockfactors" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "treeNodeCustomAllowance":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeCustomAllowance" : {
								"label" : "Allowance Factors",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowancefactors'
									});
								}
							},
						};
						break;
					case 'nonusage_fee_onetime':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_fee_onetime" : {
							"nonusage_fee_onetime" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargeonetime'
									});
								}
							},
						};
						break;
					case 'nonusage_fee_recurring':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_fee_recurring" : {
							"nonusage_fee_recurring" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargerecurring'
									});
								}
							},
						};
						break;

					case "nonusage_subscription_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_subscription_bonus" : {
							"nonusage_subscription_bonus" : {	
								"label" : "Bonus Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowanceonetime'
									});
								}
							},
						};
						break;

						
					case "nonusage_subscription_discount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unsubscription_discount" : {
							"nonusage_subscription_discount" : {	
								"label" : "Discount",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricediscount'
									});
								}
							},
						};
						break;

					case "nonusage_unsubscription_discount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unsubscription_discount" : {
							"nonusage_unsubscription_discount" : {	
								"label" : "Discount",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricediscount'
									});
								}
							},
						};
						break;
						
					case "nonusage_recurring_discount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_recurring_discount" : {
							"nonusage_recurring_discount" : {	
								"label" : "Discount",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricediscount'
									});
								}
							},
						};
						break;

					case "nonusage_unittransfer_discount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unittransfer_discount" : {
							"nonusage_unittransfer_discount" : {	
								"label" : "Discount",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricediscount'
									});
								}
							},
						};
						break;
						
					case "nonusage_activation_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_activation_bonus" : {
							"nonusage_activation_bonus" : {
								"label" : "Bonus Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowanceonetime'
									});
								}
							},
						};
						break;

					case "nonusage_recharge_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_recharge_bonus" : {
							"nonusage_recharge_bonus" : {	
								"label" : "Bonus Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowanceonetime'
									});
								}
							},
						};
						break;
						
					case "nonusage_usageend_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_usageend_bonus" : {
							"nonusage_usageend_bonus" : {	
								"label" : "Bonus Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowanceonetime'
									});
								}
							},
						};
						break;

					case "nonusage_subscription_charge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_subscription_charge" : {
							"nonusage_subscription_charge" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargeonetime'
									});
								}
							},
						};
						break;

					case "nonusage_unsubscription_charge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unsubscription_charge" : {
							"nonusage_unsubscription_charge" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargeonetime'
									});
								}
							},
						};
						break;

					case "nonusage_unsubscription_penalty":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unsubscription_penalty" : {
							"nonusage_unsubscription_penalty" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargeonetime'
									});
								}
							},
						};
						break;

					case "nonusage_unittransfer_charge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							//"mobile_nonusage_unittransfer_charge" : {
							"nonusage_unittransfer_charge" : {	
								"label" : "Charge Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpricechargeonetime'
									});
								}
							},
						};
						break;

					case "nonusage_recurring_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_nonusage_recurring_bonus" : {
							"nonusage_recurring_bonus" : {	
								"label" : "Bonus Item",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'actionpriceallowanceonetime'
									});
								}
							},
						};
						break;

					case "actionpricechargeonetime":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargeonetime" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;

					case 'tree_node_counter_accumulated_optional_prepaid':
					case 'tree_node_counter_accumulated_optional_postpaid':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargeonetime" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
						
					case 'tree_node_counter_accumulated_rollover_prepaid':
					case 'tree_node_counter_accumulated_rollover_postpaid':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargeonetime" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					
					case "actionpriceallowanceonetime":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpriceallowanceonetime" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					case "actionpricechargerecurring":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargerecurring" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;

					case "actionpriceallowancerecurring":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpriceallowancerecurring" : {
								"label" : "Discount",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;

					case "actionpricediscount":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricediscount" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						break;
					case "actionpriceallowance":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpriceallowance" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "actionpricechargefactors":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargefactors" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "actionpricediscountfactors":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricediscountfactors" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "actionpriceallowancefactors":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpriceallowancefactors" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'treenodepacketpredefined':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treenodepacketpredefined" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					  break;
					case 'treenodepacketdynamic':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treenodepacketdynamic" : {
								"label" : "ConditionSet",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonand'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
					  break;
					case 'conditionwhatincomingcall':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhensubscriptionday':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhenactivationday':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhenfirstmonth':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhencompanybirthday':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhencustomerbirthday':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhenstatechangedate':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'conditionwhenbilldate':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case "conditioncommonand":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who" : {
								"label" : "Who",
								"submenu" : {
									"subscriber MDN" : {
										"label" : "Subscriber MDN",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhosubscribermdn'
											});
										}
									},
									"Subscrbier Status" : {
										"label" : "Subscrbier Status",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhosubscriberstatus'
											});
										}
									},
									"prefix" : {
										"label" : "Called Number",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhoprefixfactors'
											});
										}
									},
									"carrier" : {
										"label" : "Carrier (Called)",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhocalledcarrier'
											});
										}
									},
									
									"customer level" : {
										"label" : "customer level",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhocustomerlevel'
											});
										}
									},
								}
							},
							"where" : {
								"label" : "Where",
								"submenu" : {
									"caller zone" : {
										"label" : "Caller Zone",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwherecallerzone'
											});
										}
									},
									"callee zone" : {
										"label" : "Callee Zone",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwherecalleezone'
											});
										}
									},
									"samezone" : {
										"label" : "Caller/Callee in SameZone",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhereissamezone'
											});
										}
									},
									"client IP" : {
										"label" : "Client IP",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhereclientip'
											});
										}
									},
									"client MAC Address" : {
										"label" : "Client MAC Address",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwheremacaddress'
											});
										}
									},
									"client Device Type" : {
										"label" : "Client Device Type",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwheredevicetype'
											});
										}
									},
								}
							},
							"what" : {
								"label" : "What",
								"submenu" : {
									"usage_type" : {
										"label" : "UsageType",
										action : function(node) {
											$.fn.addNode(node, {
													'childContentType' : 'conditionwhatusagetypefactors'
											});
										},
									},
									"nonusage_type" : {
										"label" : "NonUsageType",
											action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatnonusagetypefactors',
											});
										},
									},
									"voucher_card_type" : {
										"label" : "Card Types",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhatcardtype'
											});
										}
									},
									"Incoming Call" : {
										"label" : "Incoming Call",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhatincomingcall'
											});
										}
									},
									"calltype" : {
										"label" : "Call Type",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhatcalltype'
											});
										}
									},
									"Counter" : {
										"label" : "Counter",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhatcounter'
											});
										}
									},
									"Service Domain" : {
										"label" : "Service Domain",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhatservicedomain'
											});
										}
									},
								}
							},
							"when" : {
								"label" : "When",
								"submenu" : {
									"day" : {
										"label" : "Day",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhendayfactors'
											});
										}
									},
									"dom" : {
										"label" : "Day of Month",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhendayofmonth'
											});
										}
									},
									/*
									"statechangedate" : {
										"label" : "State Change Date",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenstatechangedate'
											});
										}
									},
									*/
									"billdate" : {
										"label" : "Bill Date",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenbilldate'
											});
										}
									},
									"subscription_day" : {
										"label" : "Subscription Date",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhensubscriptionday'
											});
										}
									},
									"activation_day" : {
										"label" : "Activation Date",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenactivationday'
											});
										}
									},
									"active_days" : {
										"label" : "Active Days",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenactivedays'
											});
										}
									},
									"customerbirthday" : {
										"label" : "Customer Birthday",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhencustomerbirthday'
											});
										}
									},
									"companybirthday" : {
										"label" : "Company Birthday",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhencompanybirthday'
											});
										}
									},
									"duration" : {	
										"label" : "Duration",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhendurationfactors'
											});
										}
									},
									"holiday" : {
										"label" : "Holiday",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenholidayfactors'
											});
										}
									},
									"timeslot" : {
										"label" : "Timeslot",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhentimeslotfactors'
											});
										}
									},
									"week" : {
										"label" : "Week",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenweekfactors'
											});
										}
									},
									"firstmonth" : {
										"label" : "First Month",
										action : function(node) {
											$.fn.addNode(node, {
												'childContentType' : 'conditionwhenfirstmonth'
											});
										}
									},
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_subscription":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"voucher_card_type" : {
												"label" : "Card Types",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcardtype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_unsubscription":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_activation":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_1" : {
										"label" : "Who",
										"submenu" : {
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"voucher_card_type" : {
												"label" : "Card Types",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcardtype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_recharge":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"voucher_card_type" : {
												"label" : "Card Types",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcardtype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_usageend":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
												"subscriber MDN" : {
													"label" : "Subscriber MDN",
													action : function(node) {
														$.fn.addNode(node, {
															'childContentType' : 'conditionwhosubscribermdn'
														});
													}
												},
												"Subscrbier Status" : {
													"label" : "Subscrbier Status",
													action : function(node) {
														$.fn.addNode(node, {
															'childContentType' : 'conditionwhosubscriberstatus'
														});
													}
												},
												
											"prefix" : {
												"label" : "Called Number",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhoprefixfactors'
													});
												}
											},
											"carrier" : {
												"label" : "Carrier (Called)",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocalledcarrier'
													});
												}
											},
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"where_" : {
										"label" : "Where",
										"submenu" : {
											"caller zone" : {
												"label" : "Caller Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecallerzone'
													});
												}
											},
											"callee zone" : {
												"label" : "Callee Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecalleezone'
													});
												}
											},
											"samezone" : {
												"label" : "Caller/Callee in SameZone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhereissamezone'
													});
												}
											},
											"client IP" : {
												"label" : "Client IP",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhereclientip'
													});
												}
											},
											"client MAC Address" : {
												"label" : "Client MAC Address",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwheremacaddress'
													});
												}
											},
											"client Device Type" : {
												"label" : "Client Device Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwheredevicetype'
													});
												}
											},										
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"Incoming Call" : {
												"label" : "Incoming Call",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatincomingcall'
													});
												}
											},
											"calltype" : {
												"label" : "Call Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcalltype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;

						case "conditioncommonand_nonusage_recurring":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
										
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						
						case "conditioncommonand_usage_voice":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
											"prefix" : {
												"label" : "Called Number",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhoprefixfactors'
													});
												}
											},
											"carrier" : {
												"label" : "Carrier (Called)",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocalledcarrier'
													});
												}
											},
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"where_" : {
										"label" : "Where",
										"submenu" : {
											"caller zone" : {
												"label" : "Caller Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecallerzone'
													});
												}
											},
											"callee zone" : {
												"label" : "Callee Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecalleezone'
													});
												}
											},
											"samezone" : {
												"label" : "Caller/Callee in SameZone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhereissamezone'
													});
												}
											},
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"Incoming Call" : {
												"label" : "Incoming Call",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatincomingcall'
													});
												}
											},
											"calltype" : {
												"label" : "Call Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcalltype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;

						case "conditioncommonand_usage_sms":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
											"prefix" : {
												"label" : "Called Number",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhoprefixfactors'
													});
												}
											},
											"carrier" : {
												"label" : "Carrier (Called)",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocalledcarrier'
													});
												}
											},
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"where_" : {
										"label" : "Where",
										"submenu" : {
											"caller zone" : {
												"label" : "Caller Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecallerzone'
													});
												}
											},
											"callee zone" : {
												"label" : "Callee Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecalleezone'
													});
												}
											},
											"samezone" : {
												"label" : "Caller/Callee in SameZone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhereissamezone'
													});
												}
											},
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"Incoming Call" : {
												"label" : "Incoming Call",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatincomingcall'
													});
												}
											},
											"calltype" : {
												"label" : "Call Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcalltype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_usage_data":
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"where_" : {
										"label" : "Where",
										"submenu" : {
											"caller zone" : {
												"label" : "Caller Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecallerzone'
													});
												}
											},
											"client IP" : {
												"label" : "Client IP",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhereclientip'
													});
												}
											},
											"client MAC Address" : {
												"label" : "Client MAC Address",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwheremacaddress'
													});
												}
											},
											"client Device Type" : {
												"label" : "Client Device Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwheredevicetype'
													});
												}
											},										
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"calltype" : {
												"label" : "Call Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcalltype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
					
						case "conditioncommonand_usage_mms":
						case "conditioncommonand_usage_vod":
						case "conditioncommonand_usage_crbt":
						case "conditioncommonand_usage_loyalty_point_deduct":
							menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : {
											"subscriber MDN" : {
												"label" : "Subscriber MDN",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscribermdn'
													});
												}
											},
											"Subscrbier Status" : {
												"label" : "Subscrbier Status",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhosubscriberstatus'
													});
												}
											},
											"customer level" : {
												"label" : "Customer level",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhocustomerlevel'
													});
												}
											},
										}
									},
									"where_" : {
										"label" : "Where",
										"submenu" : {
											"caller zone" : {
												"label" : "Caller Zone",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwherecallerzone'
													});
												}
											},
										}
									},
									"what" : {
										"label" : "What",
										"submenu" : {
											"calltype" : {
												"label" : "Call Type",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcalltype'
													});
												}
											},
											"Counter" : {
												"label" : "Counter",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatcounter'
													});
												}
											},
											"Service Domain" : {
												"label" : "Service Domain",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhatservicedomain'
													});
												}
											},
										}
									},
									"when" : {
										"label" : "When",
										"submenu" : {
											"day" : {
												"label" : "Day",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayfactors'
													});
												}
											},
											"dom" : {
												"label" : "Day of Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendayofmonth'
													});
												}
											},
											/*
											"statechangedate" : {
												"label" : "State Change Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenstatechangedate'
													});
												}
											},
											*/
											"billdate" : {
												"label" : "Bill Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenbilldate'
													});
												}
											},
											"subscription_day" : {
												"label" : "Subscription Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhensubscriptionday'
													});
												}
											},
											"activation_day" : {
												"label" : "Activation Date",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivationday'
													});
												}
											},
											"active_days" : {
												"label" : "Active Days",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenactivedays'
													});
												}
											},
											"customerbirthday" : {
												"label" : "Customer Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencustomerbirthday'
													});
												}
											},
											"companybirthday" : {
												"label" : "Company Birthday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhencompanybirthday'
													});
												}
											},
											"duration" : {
												"label" : "Duration",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhendurationfactors'
													});
												}
											},
											"holiday" : {
												"label" : "Holiday",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenholidayfactors'
													});
												}
											},
											"timeslot" : {
												"label" : "Timeslot",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhentimeslotfactors'
													});
												}
											},
											"week" : {
												"label" : "Week",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenweekfactors'
													});
												}
											},
											"firstmonth" : {
												"label" : "First Month",
												action : function(node) {
													$.fn.addNode(node, {
														'childContentType' : 'conditionwhenfirstmonth'
													});
												}
											},
										}
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
						
						
					case "conditionwhatqos":
					case "conditionwhaturlgroupfactors":
					case "conditionwhatcounter":
					case "conditionwhatcustomfactors":
					case "conditionwhatusagetypefactors":
					case "conditionwhatnonusagetypefactors":
					case "conditionwhatservicedomain":
					case "conditionwhendayfactors":
					case "conditionwhendurationfactors":
					case "conditionwhenholidayfactors":
					case "conditionwhendayofmonth":
					case "conditionwhenactivedays":
					case "conditionwhentimeslotfactors":
					case "conditionwhenweekfactors":
					case "conditionwhenstatechangedate":
					case "conditionwhenbilldate":
					case "conditionwherecountryfactors":
					case "conditionwherenetworkfactors":
					case "conditionwherecallerzone":
					case "conditionwherecalleezone":					
					case "conditionwherecustomfactors":
					case "conditionwhereclientip":
					case "conditionwheremacaddress":
					case "conditionwheredevicetype":
					case "conditionwhomemberfactors":
					case "conditionwhonumberfactors":
					case "conditionwhosubscribermdn":
					case "conditionwhosubscriberstatus":
					case "conditionwhoprefixfactors":
					case "conditionwhocustom":
					case "conditionwhocustomerlevel":
					case 'conditionwhatcardtype':
					case 'conditionwhereissamezone':
					case 'conditionwherezonefactors':
					case 'conditionwhocalledcarrier':
						menus.custom_delete._disabled = false;	
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case "usage_voice":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"usage_voice" : {	
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "mobile_usage_voice":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_voice" : {	
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
					case "voip_usage_voice":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"voip_usage_voice" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "usage_sms":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"usage_sms" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "mobile_usage_sms":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_sms" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
					case "voip_usage_sms":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_sms" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};					
						break;
						
					case "mobile_usage_data":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_data" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
					case "mobile_usage_data":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_data" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "mobile_usage_mms":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_mms" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
						
					case "mobile_usage_mms":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_mms" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}	
							},
						};
						break;
						
					case "mobile_usage_crbt":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_crbt" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "mobile_usage_crbt":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_crbt" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
						
					case "mobile_usage_vod":
					case "iptv_usage_vod":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"usage_vod" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
					case "mobile_usage_vod":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_vod" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
						
					case "iptv_usage_vod":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"iptv_usage_vod" : {
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
					
					case "mobile_usage_loyaltypoint":
					case "iptv_usage_loyaltypoint":
					case "voip_usage_loyaltypoint":
					case "broadband_usage_loyaltypoint":
					case "satellite_usage_loyaltypoint":
					case "dummy_usage_loyaltypoint":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							// "mobile_usage_loyaltypoint" : {
							"usage_loyaltypoint" : {	
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
						
					case "mobile_usage_loyaltypoint":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_usage_loyaltypoint" : {	
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
					case "voip_usage_loyaltypoint":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"voip_usage_loyaltypoint" : {	
								"label" : "Tariff Plan",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'tariffplan'
									});
								}
							},
						};
						break;
						
					case "attribute_required_device":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"attribute_required_device" : {
								"label" : "Select Required Device",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;	
					case "attribute_number_saving":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"attribute_number_saving" : {
								"label" : "Number Saving",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'prdattributenumbersaving' 
									});
								}
							},
						};
						break;	
					case "attribute_available_channel":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"attribute_available_channel" : {
								"label" : "Select Available Channel",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;	
					case "attribute_allowed_device":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"attribute_allowed_device" : {
								"label" : "Select Allowed Device",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;	
					case "prdattributerequireddevice":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "prdattributenumbersaving":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "prdattributeavailablechannel":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;					
					case "prdattributeallowedmodel":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						
					case "data_tariffplan_predefined":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"data_tariffplan_predefined" : {
								"label" : "Select Rule",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case "mobile_data_tariffplan_predefined":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_data_tariffplan_predefined" : {
								"label" : "Select Rule",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case "data_tariffplan_dynamic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"data_tariffplan_dynamic" : {
								"label" : "Select Rule",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case "mobile_data_tariffplan_dynamic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"mobile_data_tariffplan_dynamic" : {
								"label" : "Select Rule",
								action : function(node) {
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
						
					case 'data_tariffplan_basicrate':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"data_tariffplan_basicrate" : {
								"label" : "BasicRate",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'basicrate_data' 
									});
								}
							},
						};
						break;
				  case 'basicrate_data':
				  	menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "tariffplan":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_copy._disabled = false;
						menus.custom_copy.action = function(node) {
							$.fn.copyNode(node);
						};
						break;
					case "treeNodeNumberingPlanDomestic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeNumberingPlanDomestic" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treeNodeNumberingPlanIDD":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeNumberingPlanIDD" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treeNodeAllowedNumberSpecial":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeAllowedNumberSpecial" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treeNodeForbiddenNumberSpecial":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeForbiddenNumberSpecial" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treeNodeBasicRateDomestic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeBasicRateDomestic" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treeNodeBasicRateIDD":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"treeNodeBasicRateIDD" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "carrier_domestic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"carrier_domestic" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "carrier_idd":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"carrier_idd" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "basicrate_idd_ratinggroup":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"basicrate_idd_ratinggroup" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "basicrate_domestic_ratinggroup":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"basicrate_domestic_ratinggroup" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "voice_tariffplan_specialnumber":
					case "sms_tariffplan_specialnumber":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"tariffplan_specialnumber" : {
								"label" : "Select",
								action : function(node) {
									//$.fn.addNode(node,"tariffplan");
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					default:
						menus.custom_create = null;
						menus.custom_copy = null;
						menus.custom_paste = null;
						menus.custom_delete = null;
						break;
				}  
				break;
			
			case "numberspecial_tree":
				var relType = obj.attr("rel");
				switch (relType) {
					case "number_special":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "Rates":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"Rates" : {
								"label" : "Rate",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'numberspecialrate'
									});
								}
							},
						};
						break;

					case 'numberspecialrate':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "actionpricechargefactors":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"actionpricechargefactors" : {
								"label" : "Rating Group",
								action : function(node) {
									$.fn.addNode(node, {
										'childContentType' : 'conditioncommonratinggroup'
									});
								}
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "conditioncommonratinggroup":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
				}
				break;
			case "unittransfer_tree":
				var relType = obj.attr("rel");
				switch (relType) {
					case "unittransfer":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						break;
				}
				break;

			// vouchercardtype tree
			case "vouchercardtype_tree":
				var relType = obj.attr("rel");

				switch (relType) {
					case "vouchercardtype":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};

					case "voucher_domain_specific":
					case "voucher_domain_specific_mobile":
					case "voucher_domain_specific_iptv":
					case "voucher_domain_specific_broadband":
					case "voucher_domain_specific_voip":
					case "voucher_domain_specific_satellite":
					case "voucher_domain_specific_dummy":
						break;
					case "voucher_product_specific":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"voucher_product_specific" : {
								"label" : "Select Product",
								action : function(node) {
									console.log('here');
									$.fn.loadSelectForm(node);
								}
							},
						};
						break;
					case "treenodeproductforvoucher":
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
				}

				break;
			// vouchercardtype tree

			default:
				menus.custom_create = null;
				menus.custom_copy = null;
				menus.custom_paste = null;
				menus.custom_delete = null;
		};// switch
		return menus;
	};
})(jQuery);

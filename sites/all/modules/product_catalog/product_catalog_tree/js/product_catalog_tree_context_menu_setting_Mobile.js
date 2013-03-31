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
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("TransferBonus","actionbonustransfer");
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "packaged_mandatory":
					case "packaged_product":
					case "packaged_optional":
					case "packaged_hidden":
					case "cross_available_product":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Product");
						break;
					case "attribute_featurecode":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select FeatureCode");
						break;
					case "tree_node_counter_main_basic_prepaid":
					case "tree_node_counter_main_basic_postpaid":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set","conditioncommonand");
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case 'tree_node_counter_main_rollover_prepaid':
					case 'tree_node_counter_main_rollover_postpaid':
					case "tree_node_counter_main_optional_prepaid":
					case "tree_node_counter_main_optional_postpaid":
					case "tree_node_counter_accumulated_basic_prepaid":
					case "tree_node_counter_accumulated_basic_postpaid":
					case 'actionblockfactors':
					case "actionpricechargeonetime":
					case 'tree_node_counter_accumulated_optional_prepaid':
					case 'tree_node_counter_accumulated_optional_postpaid':
					case 'tree_node_counter_accumulated_rollover_prepaid':
					case 'tree_node_counter_accumulated_rollover_postpaid':
					case "actionpriceallowanceonetime":
					case "actionpricechargerecurring":
					case "actionpriceallowancerecurring":
					case "actionpricediscount":
					case "actionpriceallowance":
					case "actionpricechargefactors":
					case "actionpricediscountfactors":
					case "actionpricecugdiscountfactors":
					case "actionpriceallowancefactors":
					case 'treenodepacketpredefined':
					case 'treenodepacketdynamic':
					case 'treenodepacketdefaultqos':
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set","conditioncommonand");
						break;
					case "counter_main":
					case "counter_shared":
					case "counter_accumulated":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Counter");
						break;
					case "nonusage_deposit":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Deposit Scheme");
						break;
					case 'nonusage_otheronetimecharge':
					case 'nonusage_otheronetimecharge_discount_on_main':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Other Onetime Charge");
						break;
					case 'nonusage_bonus_transfer':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Voucher Card Type");
						break;
					case "nonusage_threshold":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Threshold Scheme");
						break;
					case "nonusage_unittransfer_scheme":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Unit Transfer Scheme");
						break;
					case "attribute_subscriber_lifecycle_scheme":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Select Lifecycle Scheme");
						break;
					case 'nonusage_rollover':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("RollOver","prdnonusagerollover");
						break;
					case "treeNodeCustomCharge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Factors","actionpricechargefactors");
						break;
					case "treeNodeCustomDiscount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount Factors","actionpricediscountfactors");
						break;
					case "treeNodeCugDiscount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount Factors","actionpricecugdiscountfactors");
						break;
					case "treeNodeCustomBlock":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Block Service Factors","actionblockfactors");
						break;
					case "treeNodeCustomAllowance":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Allowance Factors","actionpriceallowancefactors");
						break;
					case 'nonusage_fee_onetime':
					case "nonusage_subscription_charge":
					case "nonusage_unsubscription_charge":
					case "nonusage_unsubscription_penalty":
					case "nonusage_unittransfer_charge":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item","actionpricechargeonetime");
						break;
					case 'nonusage_fee_recurring':
					case 'nonusage_recurring_charge':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item","actionpricechargerecurring");
						break;
					case "nonusage_subscription_bonus":
					case "nonusage_activation_bonus":
					case "nonusage_recharge_bonus":
					case "nonusage_usageend_bonus":
					case "nonusage_recurring_bonus":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Bonus Item","actionpriceallowanceonetime");
						break;
					case "nonusage_subscription_discount":
					case "nonusage_unsubscription_discount":
					case "nonusage_recurring_discount":
					case "nonusage_recurring_discount_on_main":		
					case "nonusage_unittransfer_discount":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount","actionpricediscount");
						break;
					case "conditioncommonand":
						var who = $.fn.getConditionWhoType1();
						var where = $.fn.getConditionWhereType1();
						var what = $.fn.getConditionWhatType1();
						var when = $.fn.getConditionWhenType1();
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = {
							"who" : {
								"label" : "Who",
								"submenu" : who
							},
							"where" : {
								"label" : "Where",
								"submenu" : where
							},
							"what" : {
								"label" : "What",
								"submenu" : what
							},
							"when" : {
								"label" : "When",
								"submenu" : when
							},
						};
						menus.custom_delete._disabled = false;
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_subscription":
						case "conditioncommonand_nonusage_activation":
						case "conditioncommonand_nonusage_recharge":
							var who = $.fn.getConditionWhoType2();
							var what = $.fn.getConditionWhatType2();
							var when = $.fn.getConditionWhenType1();
							menus.custom_create._disabled = false;
							menus.custom_create.submenu = {
								"who_" : {
									"label" : "Who",
									"submenu" : who
								},
								"what" : {
									"label" : "What",
									"submenu" : what
								},
								"when" : {
									"label" : "When",
									"submenu" : when
								},
							};
							menus.custom_delete._disabled = false;
							menus.custom_delete.action = function(node) {
								$.fn.deleteNode(node);
							};
						break;
						case "conditioncommonand_nonusage_unsubscription":
						case "conditioncommonand_nonusage_recurring":
							var who = $.fn.getConditionWhoType2();
							var what = $.fn.getConditionWhatType3();
							var when = $.fn.getConditionWhenType1();
							menus.custom_create._disabled = false;
							menus.custom_create.submenu = {
								"who_" : {
									"label" : "Who",
									"submenu" : who
								},
								"what" : {
									"label" : "What",
									"submenu" : what
								},
								"when" : {
									"label" : "When",
									"submenu" : when
								}
									
							};
							menus.custom_delete._disabled = false;
							menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
						case "conditioncommonand_nonusage_usageend":
							var who = $.fn.getConditionWhoType1();
							var where = $.fn.getConditionWhereType1();
							var what = $.fn.getConditionWhatType4();
							var when = $.fn.getConditionWhenType1();
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : who
									},
									"where_" : {
										"label" : "Where",
										"submenu" : where
									},
									"what" : {
										"label" : "What",
										"submenu" : what
									},
									"when" : {
										"label" : "When",
										"submenu" : when
									}
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
						};
						break;
					case "conditioncommonand_usage_voice":
					case "conditioncommonand_usage_sms":
						var who = $.fn.getConditionWhoType1();
						var where = $.fn.getConditionWhereType2();
						var what = $.fn.getConditionWhatType5();
						var when = $.fn.getConditionWhenType1();
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : who
									},
									"where_" : {
										"label" : "Where",
										"submenu" : where
									},
									"what" : {
										"label" : "What",
										"submenu" : what
									},
									"when" : {
										"label" : "When",
										"submenu" : when
									},
								};
								menus.custom_delete._disabled = false;
								menus.custom_delete.action = function(node) {
									$.fn.deleteNode(node);
							};
						break;
						case "conditioncommonand_usage_data":
							var who = $.fn.getConditionWhoType2();
							var where = $.fn.getConditionWhereType3();
							var what = $.fn.getConditionWhatType3();
							var when = $.fn.getConditionWhenType1();
								menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : who
									},
									"where_" : {
										"label" : "Where",
										"submenu" : where
									},
									"what" : {
										"label" : "What",
										"submenu" : what
									},
									"when" : {
										"label" : "When",
										"submenu" : when
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
						var who = $.fn.getConditionWhoType2();
							var where = $.fn.getConditionWhereType4();
							var what = $.fn.getConditionWhatType3();
							var when = $.fn.getConditionWhenType1();
							menus.custom_create._disabled = false;
								menus.custom_create.submenu = {
									"who_" : {
										"label" : "Who",
										"submenu" : who
									},
									"where_" : {
										"label" : "Where",
										"submenu" : where
									},
									"what" : {
										"label" : "What",
										"submenu" : what
									},
									"when" : {
										"label" : "When",
										"submenu" : when
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
					case "conditionwhendayfactors":
					case "conditionwhendurationfactors":
					case "conditionwhenholidayfactors":
					case "conditionwhendayofmonth":
					case "conditionwhenstatechangedate":
					case "conditionwhenbillingdate":
					case "conditionwhenactivedays":
					case "conditionwhentimeslotfactors":
					case "conditionwhenweekfactors":
					case "conditionwherecountryfactors":
					case "conditionwherenetworkfactors":
					case "conditionwherecallerzone":
					case "conditionwherecalleezone":					
					case "conditionwherecustomfactors":
					case "conditionwhereclientip":
					case "conditionwheremacaddress":
					case "conditionwheredevicetype":
					case "conditionwhereserviceid":
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
					case 'actionbonustransfer':
					case "prdattributeprefixrangeallowed":
					case "prdnonusagerollover":
					case "treenodespecialnumberscheme":
					case "prdattributeprefixrangenotallowe":
					case 'prdattributefeaturecode':
					case 'prdattributepackaged':
					case "simpleproductoffering":
					case 'treenodeotheronetimecharge':
					case 'treenodedepositscheme':
					case 'treenodethresholdscheme':
					case 'treenodeunittransferscheme':
					case 'treenodelifecyclescheme':
					case 'conditionwhatincomingcall':
					case 'conditionwhatmainproduct':
					case 'conditionwhensubscriptionday':
					case 'conditionwhenactivationday':
					case 'conditionwhenfirstmonth':
					case 'conditionwhencompanybirthday':
					case 'conditionwhencustomerbirthday':
					case 'conditionwhenstatechangedate':
					case 'conditionwhenbillingdate':
					case "prdattributerequireddevice":
					case "prdattributenumbersaving":
					case "prdattributeavailablechannel":
					case "prdattributeallowedmodel":
					case 'basicrate_data':
					case 'conditionwhoroamingcarrier':
       	  case 'conditionwhereroamingcountry':
          case 'conditionwhereroamingzone':
          case 'conditionwhatroamingtype':
						menus.custom_delete._disabled = false;	
						menus.custom_delete.action = function(node) {
							$.fn.deleteNode(node);
						};
						break;
					case "usage_voice":
					case "cross_mobile_usage_voice":
					case "cross_voip_usage_voice":
					case "usage_sms":
					case "cross_mobile_usage_sms":
					case "cross_voip_usage_sms":
					case "usage_data":
					case "cross_mobile_usage_data":
					case "usage_mms":
					case "cross_mobile_usage_mms":
					case "usage_crbt":
					case "cross_mobile_usage_crbt":
					case "usage_vod":
					case "cross_mobile_usage_vod":
					case "cross_iptv_usage_vod":
					case "usage_loyaltypoint":
					case "cross_mobile_usage_loyaltypoint":
					case "cross_voip_usage_loyaltypoint":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Tariff Plan","tariffplan");
						menus.custom_paste._disabled = false;
						menus.custom_paste.action = function(node) {
							$.fn.pasteNode(node);
						};
						break;
					case "attribute_required_device":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Required Device");
						break;	
					case "attribute_number_saving":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Number Saving","prdattributenumbersaving");
						break;	
					case "attribute_available_channel":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Available Channel");
						break;	
					case "voice_tariffplan_specialnumber":
					case "sms_tariffplan_specialnumber":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select SpecialNumberScheme");
						break;
					case "attribute_allowed_device":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Allowed Device");
						break;	
					case "data_tariffplan_predefined":
					case "cross_mobile_data_tariffplan_predefined":
					case "data_tariffplan_dynamic":
					case "cross_mobile_data_tariffplan_dynamic":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Rule");
						break;
					case "data_tariffplan_qos":
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("Default QoS","treenodepacketdefaultqos");
						break;
					case 'data_tariffplan_basicrate':
						menus.custom_create._disabled = false;
						menus.custom_create.submenu = $.fn.getSubMenuAddNode("BasicRate","basicrate_data");
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
					default:
						menus.custom_create = null;
						menus.custom_copy = null;
						menus.custom_paste = null;
						menus.custom_delete = null;
						break;
				}  
				break;
			default:
				menus.custom_create = null;
				menus.custom_copy = null;
				menus.custom_paste = null;
				menus.custom_delete = null;
		};// switch
		console.log(menus);
		return menus;
	};
})(jQuery);

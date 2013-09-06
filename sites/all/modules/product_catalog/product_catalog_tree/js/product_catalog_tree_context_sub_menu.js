(function($) {
	$.fn.getFixedMenu = function(menus, relType) {
		switch(relType) {
			case "treenodevouchercardforproduct":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("TransferBonus", "actionbonustransfer");
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "packaged_mandatory":
			case "packaged_product":
			case "packaged_optional":
			case "packaged_hidden":
			case "available_product":
			case "member_product":
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
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
				/*
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				*/
				break;
			case "tree_node_counter_main_basic_prepaid_removable":
			case "tree_node_counter_main_basic_postpaid_removable":
			case 'tree_node_counter_main_rollover_prepaid':
			case 'tree_node_counter_main_rollover_postpaid':
			case "tree_node_counter_main_optional_prepaid":
			case "tree_node_counter_main_optional_postpaid":
			case 'actionblockfactors':
			case 'tree_node_counter_accumulated_optional_prepaid':
			case 'tree_node_counter_accumulated_optional_postpaid':
			case 'tree_node_counter_accumulated_rollover_prepaid':
			case 'tree_node_counter_accumulated_rollover_postpaid':
			case "actionpriceallowancerecurring":
			case "actionpriceallowance":
			case "actionpricechargefactors":
			case "actionpricediscountfactors":
			case "actionpriceallowancefactors":
			case 'treenodepacketpredefined':
			case 'treenodepacketdynamic':
			case 'treenodepacketdefaultqos':
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
				break;
				/*
			case "treeNodeCugDiscount":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Action Price Discount", "actionpricecugdiscountfactors");
				break;
				*/
			case "actionpricecugdiscountfactors":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
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
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("RollOver", "prdnonusagerollover");
				break;
			case "treeNodeCustomCharge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Factors", "actionpricechargefactors");
				break;
			case "treeNodeCustomDiscount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount Factors", "actionpricediscountfactors");
				break;
			case "treeNodeCustomBlock":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Block Service Factors", "actionblockfactors");
				break;
			case "treeNodeCustomAllowance":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Allowance Factors", "actionpriceallowancefactors");
				break;
			case 'nonusage_fee_onetime':
			
			case "nonusage_unsubscription_charge":
			case "nonusage_unsubscription_penalty":
			case "nonusage_unittransfer_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargeonetime");
				break;
			case "nonusage_subscription_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargeonetime");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case 'nonusage_fee_recurring_custom':
			//case 'nonusage_recurring_charge':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Charge Item", "actionpricechargerecurring");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_subscription_bonus":
			case "nonusage_activation_bonus":
			case "nonusage_recharge_bonus":
			case "nonusage_usageend_bonus":
			case "nonusage_recurring_bonus":
			case "nonusage_group_bonus_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Bonus Item", "actionpriceallowanceonetime");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_unittransfer_discount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				break;
			case "nonusage_unsubscription_discount":
			case "nonusage_recurring_discount_on_main":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "nonusage_subscription_discount":
			case "nonusage_recurring_discount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Discount", "actionpricediscount");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
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
			// case "conditionwhencallingzonetime":
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
			case "conditionwehreapn":
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
			//case "simpleproductoffering":
			case 'treenodeotheronetimecharge':
			case 'treenodedepositscheme':
			case 'treenodethresholdscheme':
			case 'treenodeunittransferscheme':
			case 'treenodelifecyclescheme':
			case 'conditionwhatincomingcall':
			case 'conditionwhatisvideo':
			case 'conditionwhatisgroupcall':
			case 'conditionwhatmainproduct':
			case 'conditionwhatmainproductforpeer':
			case 'conditionwhensubscriptionday':
			case 'conditionwhentodaysubscriptionda':
			case 'conditionwhenactivationday':
			// case 'conditionwhencompanybirthday':
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
			case 'conditionwhererattype':
			case 'conditionwheresgsn':
			case 'conditionwheresgsnip':
			case 'conditionwhereapn':
			case 'conditionwhatservicedomain':
			case 'conditionwhatcontentprice':
			case 'conditionwhatcalltype':
			case 'conditionwhatbilltype':
			case 'conditionwhatfeaturecode':
			case 'conditionwhatisredirected':
			// case 'conditionwhenvaliddate':
			case 'treenodeotheronetimechargediscou':
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "usage_voice":
			case "mobile_usage_voice":
			case "cross_mobile_usage_voice":
			case "cross_voip_usage_voice":
			case "voip_usage_voice":
			case "usage_sms":
			case "mobile_usage_sms":
			case "cross_mobile_usage_sms":
			case "voip_usage_sms":
			case "cross_voip_usage_sms":
			case "usage_data":
			case "mobile_usage_data":
			case "cross_mobile_usage_data":
			case "usage_mms":
			case "mobile_usage_mms":
			case "cross_mobile_usage_mms":
			case "usage_crbt":
			case "mobile_usage_crbt":
			case "cross_mobile_usage_crbt":
			case "usage_vod":
			case "mobile_usage_vod":
			case "cross_mobile_usage_vod":
			case "iptv_usage_vod":
			case "cross_iptv_usage_vod":
			case "usage_loyaltypoint":
			case "mobile_usage_loyaltypoint":
			case "iptv_usage_loyaltypoint":
			case "voip_usage_loyaltypoint":
			case "broadband_usage_loyaltypoint":
			case "satellite_usage_loyaltypoint":
			case "dummy_usage_loyaltypoint":
			case "cross_mobile_usage_loyaltypoint":
			case "cross_voip_usage_loyaltypoint":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Tariff Plan", "tariffplan");
				menus.custom_paste._disabled = false;
				menus.custom_paste.action = function(node) {
					$.fn.pasteNode(node);
				};
				break;
			case "attribute_required_device":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuLoadSelectForm("Select Required Device");
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
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("Default QoS", "treenodepacketdefaultqos");
				break;
			case 'data_tariffplan_basicrate':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = $.fn.getSubMenuAddNode("BasicRate", "basicrate_data");
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
			case "actionpricechargeonetime":
			case "actionpricediscount":
			case "actionpriceallowanceonetime":
			case "actionpricechargerecurring":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				menus.custom_create._disabled = false;
     		menus.custom_create.submenu = $.fn.getSubMenuAddNode("Condition Set", "conditioncommonand");
 				menus.custom_copy._disabled = false;
				menus.custom_copy.action = function(node) {
					$.fn.copyNode(node);
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
			default:
				menus.custom_create = null;
				menus.custom_copy = null;
				menus.custom_paste = null;
				menus.custom_delete = null;
				break;
		}
		return menus;
	};

	$.fn.getSubMenuAddNode = function(label, childContentType) {
		var obj = {
			"addNodeObject" : {
				"label" : label,
				"action" : function(node) {
					$.fn.addNode(node, {
						'childContentType' : childContentType
					});
				}
			}
		};
		return obj;
	};

	$.fn.getSubMenuAddNodeWithoutWrapper = function(label, childContentType) {
		var obj = {
			"label" : label,
			"action" : function(node) {
				$.fn.addNode(node, {
					'childContentType' : childContentType
				});
			}
		};
		return obj;
	};

	$.fn.getSubMenuLoadSelectForm = function(label) {
		var obj = {
			"loadSelectFormObject" : {
				"label" : label,
				"action" : function(node) {
					$.fn.loadSelectForm(node);
				}
			}
		};
		return obj;
	};

	$.fn.getConditionWhoType1 = function() {
		var obj = {
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN", "conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Called Number" : $.fn.getSubMenuAddNodeWithoutWrapper("Called Number", "conditionwhoprefixfactors"),
			"Carrier (Called)" : $.fn.getSubMenuAddNodeWithoutWrapper("Carrier (Called)", "conditionwhocalledcarrier"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
			"Roaming Carrier" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Carrier", "conditionwhoroamingcarrier"),
		};
		return obj;
	};

	$.fn.getConditionWhoType2 = function() {
		var obj = {
			"Subscriber MDN" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber MDN", "conditionwhosubscribermdn"),
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
		};
		return obj;
	};

	$.fn.getConditionWhoType3 = function() {
		var obj = {
			"Subscriber Status" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscriber Status", "conditionwhosubscriberstatus"),
			"Customer Level" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Level", "conditionwhocustomerlevel"),
		};
		return obj;
	};

	$.fn.getConditionWhereType1 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone", "conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone", "conditionwhereissamezone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID", "conditionwhereserviceid"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone", "conditionwhereroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country", "conditionwhereroamingcountry"),
			"RAT Type" : $.fn.getSubMenuAddNodeWithoutWrapper("RAT Type", "conditionwhererattype"),
			"SGSN" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN", "conditionwheresgsn"),
			"SGSN IP" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN IP", "conditionwheresgsnip"),
			"APN" : $.fn.getSubMenuAddNodeWithoutWrapper("APN", "conditionwhereapn"),			
		};
		return obj;
	};

	$.fn.getConditionWhereType2 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Callee Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee Zone", "conditionwherecalleezone"),
			"Caller/Callee in SameZone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller/Callee in SameZone", "conditionwhereissamezone"),
			"Roaming Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Zone", "conditionwhereroamingzone"),
			"Roaming Country" : $.fn.getSubMenuAddNodeWithoutWrapper("Roaming Country", "conditionwhereroamingcountry"),
		}
		return obj;
	};

	$.fn.getConditionWhereType3 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone"),
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
			"Service ID" : $.fn.getSubMenuAddNodeWithoutWrapper("Service ID", "conditionwhereserviceid"),
			"RAT Type" : $.fn.getSubMenuAddNodeWithoutWrapper("RAT Type", "conditionwhererattype"),
			"SGSN" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN", "conditionwheresgsn"),
			"SGSN IP" : $.fn.getSubMenuAddNodeWithoutWrapper("SGSN IP", "conditionwheresgsnip"),
			"APN" : $.fn.getSubMenuAddNodeWithoutWrapper("APN", "conditionwhereapn"),			
		};
		return obj;
	};

	$.fn.getConditionWhereType4 = function() {
		var obj = {
			"Caller Zone" : $.fn.getSubMenuAddNodeWithoutWrapper("Caller Zone", "conditionwherecallerzone")
		};
		return obj;
	};

	$.fn.getConditionWhereType5 = function() {
		var obj = {
			"Client IP" : $.fn.getSubMenuAddNodeWithoutWrapper("Client IP", "conditionwhereclientip"),
			"Client MAC Address" : $.fn.getSubMenuAddNodeWithoutWrapper("Client MAC Address", "conditionwheremacaddress"),
			"Client Device Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Client Device Type", "conditionwheredevicetype"),
		};
		return obj;
	};

	$.fn.getConditionWhatType1 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),			
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType2 = function() {
		var obj = {
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType3 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer"),
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};

	$.fn.getConditionWhatType4 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),			
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),			
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType5 = function() {
		var obj = {
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType6 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};

	$.fn.getConditionWhatType7 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType8 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),	
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType9 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType10 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType11 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType12 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),			
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Rating Group" : $.fn.getSubMenuAddNodeWithoutWrapper("Rating Group", "conditionwhatratinggroup"),
		};
		return obj;
	};
	
	$.fn.getConditionWhatType13 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType14 = function() {
		var obj = {
			"Service Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Service Domain", "conditionwhatservicedomain"),
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"RoamingType" : $.fn.getSubMenuAddNodeWithoutWrapper("RoamingType", "conditionwhatroamingtype"),
			"Incoming Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Incoming Call", "conditionwhatincomingcall"),
			"Is Group Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Group Call", "conditionwhatisgroupcall"),						
			"Is Video Call" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Video Call", "conditionwhatisvideo"),			
			"Is CLIR" : $.fn.getSubMenuAddNodeWithoutWrapper("Is CLIR", "conditionwhatisclir"),
			"Is Redirected" : $.fn.getSubMenuAddNodeWithoutWrapper("Is Redirected", "conditionwhatisredirected"),			
			"Group Member Count" : $.fn.getSubMenuAddNodeWithoutWrapper("Group Member Count", "conditionwhatgroupmembercount"),					
			"Usage Domain" : $.fn.getSubMenuAddNodeWithoutWrapper("Usage Domain", "conditionwhatusagedomain"),			
			"Call Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Call Type", "conditionwhatcalltype"),
			"Main Product Bill Type" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product Bill Type", "conditionwhatbilltype"),		
			"Feature Code" : $.fn.getSubMenuAddNodeWithoutWrapper("Feature Code", "conditionwhatfeaturecode"),						
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType15 = function() {
		var obj = {
			"UsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("UsageType", "conditionwhatusagetypefactors"),
			"NonUsageType" : $.fn.getSubMenuAddNodeWithoutWrapper("NonUsageType", "conditionwhatnonusagetypefactors"),
			"Card Types" : $.fn.getSubMenuAddNodeWithoutWrapper("Card Types", "conditionwhatcardtype"),
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
			"Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Main Product", "conditionwhatmainproduct"),
			"Callee Main Product" : $.fn.getSubMenuAddNodeWithoutWrapper("Callee's Main Product", "conditionwhatmainproductforpeer")
		};
		return obj;
	};
	
	$.fn.getConditionWhatType16 = function() {
		var obj = {
			"Counter" : $.fn.getSubMenuAddNodeWithoutWrapper("Counter", "conditionwhatcounter"),
			"Content Price" : $.fn.getSubMenuAddNodeWithoutWrapper("Content Price", "conditionwhatcontentprice"),
		};
		return obj;
	};

	$.fn.getConditionWhenType1 = function() {
		var obj = {
			"Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Day", "conditionwhendayfactors"),
			"Day of Month" : $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month", "conditionwhendayofmonth"),
			"Bill Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date", "conditionwhenbillingdate"),
			"Subscription Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date", "conditionwhensubscriptionday"),
			"Today Is Subscription Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Today is SubscriptionDay", "conditionwhentodaysubscriptionda"),
			"Activation Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date", "conditionwhenactivationday"),
			"Active Days" : $.fn.getSubMenuAddNodeWithoutWrapper("Active Days", "conditionwhenactivedays"),
			"Customer Birthday" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday", "conditionwhencustomerbirthday"),
			// "Company Anniversary" : $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary", "conditionwhencompanybirthday"),
			"Duration" : $.fn.getSubMenuAddNodeWithoutWrapper("Duration", "conditionwhendurationfactors"),
			"Holiday" : $.fn.getSubMenuAddNodeWithoutWrapper("Holiday", "conditionwhenholidayfactors"),
			"Timeslot" : $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot", "conditionwhentimeslotfactors"),
			"Week" : $.fn.getSubMenuAddNodeWithoutWrapper("Week", "conditionwhenweekfactors"),
			// "Calling Zone Time" : $.fn.getSubMenuAddNodeWithoutWrapper("Calling Zone Time", "conditionwhencallingzonetime"),
			// "Valid Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Valid Date", "conditionwhenvaliddate")
		};
		return obj;
	};

	$.fn.getConditionWhenType2 = function() {
		var obj = {
			"Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Day", "conditionwhendayfactors"),
			"Day of Month" : $.fn.getSubMenuAddNodeWithoutWrapper("Day of Month", "conditionwhendayofmonth"),
			"Bill Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Bill Date", "conditionwhenbillingdate"),
			"Subscription Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Subscription Date", "conditionwhensubscriptionday"),
			"Today Is Subscription Day" : $.fn.getSubMenuAddNodeWithoutWrapper("Today is SubscriptionDay", "conditionwhentodaysubscriptionda"),
			"Activation Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Activation Date", "conditionwhenactivationday"),
			"Active Days" : $.fn.getSubMenuAddNodeWithoutWrapper("Active Days", "conditionwhenactivedays"),
			"Customer Birthday" : $.fn.getSubMenuAddNodeWithoutWrapper("Customer Birthday", "conditionwhencustomerbirthday"),
			// "Company Anniversary" : $.fn.getSubMenuAddNodeWithoutWrapper("Company Anniversary", "conditionwhencompanybirthday"),
			"Duration" : $.fn.getSubMenuAddNodeWithoutWrapper("Duration", "conditionwhendurationfactors"),
			"Holiday" : $.fn.getSubMenuAddNodeWithoutWrapper("Holiday", "conditionwhenholidayfactors"),
			"Timeslot" : $.fn.getSubMenuAddNodeWithoutWrapper("Timeslot", "conditionwhentimeslotfactors"),
			"Week" : $.fn.getSubMenuAddNodeWithoutWrapper("Week", "conditionwhenweekfactors"),
			// "Valid Date" : $.fn.getSubMenuAddNodeWithoutWrapper("Valid Date", "conditionwhenvaliddate")
		};
		return obj;
	};
})(jQuery);

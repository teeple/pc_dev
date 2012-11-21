(function($) {
	$.fn.getTreeContextMenuSetting  = function(treeType,obj){
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
			switch (relType) {
			case "treenodevouchercardforproduct":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
 					"TransferBonus" : {
 						"label" : "TransferBonus",
 						action : function(node) {
 							$.fn.addNode(node,{'childContentType': 'actionbonustransfer'});
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
            case "prdattributeprefixrangenotallowe":
                menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
                break;
            case "mobile_packaged_mandatory":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"mobile_packaged_mandatory" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "mobile_packaged_optional":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"mobile_packaged_optional" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "mobile_packaged_hidden":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"mobile_packaged_hidden" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "cross_available_product":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"cross_available_product" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "iptv_packaged_mandatory":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"iptv_packaged_mandatory" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "iptv_packaged_optional":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"iptv_packaged_optional" : {
 						"label" : "Select Product",
 						action : function(node) {
 							$.fn.loadSelectForm(node);
 						}
 					},
 				};
            	break;
            case "iptv_packaged_hidden":
            	menus.custom_delete._disabled = false;
            	menus.custom_delete.action = function(node) {
            		$.fn.deleteNode(node);
            	};
            	menus.custom_create._disabled = false;
 				menus.custom_create.submenu = {
 					"iptv_packaged_hidden" : {
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
            case "tree_node_counter_main_basic":
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"treenode_counter_main_basic" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
						}
					},
				};
                break;
            case "tree_node_counter_main_optional":
                menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"treenode_counter_main_optional" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
						}
					},
				};		
                break;
            case "tree_node_counter_accumulated_basic":
                menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"tree_node_counter_accumulated_basic" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
						}
					},
				};		
                break;
            case "mobile_counter_main":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_counter_main" : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case "iptv_counter_main":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"iptv_counter_main" : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case "cross_counter_main":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"cross_counter_main" : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case "mobile_nonusage_deposit":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_deposit" : {
						"label" : "Select Deposit Scheme",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case "iptv_nonusage_deposit":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"iptv_nonusage_deposit" : {
						"label" : "Select Deposit Scheme",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case 'mobile_nonusage_bonus_transfer':
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
						"mobile_nonusage_bonus_transfer" : {
							"label" : "Select Voucher Card Type",
							action : function(node) {
								$.fn.loadSelectForm(node);
							}
						},
					};
            	break;            	
            case 'treenodedepositscheme':
            	 menus.custom_delete._disabled = false;
                 menus.custom_delete.action = function(node) {
                     $.fn.deleteNode(node);
                 };
            	break;
            case 'treenodethresholdscheme':
           	 menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
           	break;
           	
            case "mobile_nonusage_threshold":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_threshold" : {
						"label" : "Select Threshold Scheme",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            case "iptv_nonusage_threshold":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"iptv_nonusage_threshold" : {
						"label" : "Select Threshold Scheme",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
				break;
            	
            case "mobile_counter_accumulated":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_counter_accumulated " : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
                break;
            case "iptv_counter_accumulated":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"iptv_counter_accumulated " : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
                break;
            case "cross_counter_accumulated":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"cross_counter_accumulated " : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node);
						}
					},
				};
                break;
            case "mobile_nonusage_unittransfer_scheme":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_unittransfer_scheme" : {
						"label" : "Select Unit Transfer",
						action : function(node) {
							$.fn.loadSelectForm(node);
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
							$.fn.addNode(node,{'childContentType': 'actionpricechargefactors'});
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
							$.fn.addNode(node,{'childContentType': 'actionpricediscountfactors'});							
						}
					},
				};
				break;
			case "treeNodeCustomAllowance":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"treeNodeCustomAllowance" : {
						"label" : "Allowance Factors",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpriceallowancefactors'});	
						}
					},
				};
				break;			
			case 'mobile_nonusage_fee_onetime':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_fee_onetime" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargeonetime'});	
						}
					},
				};
				break;
			case 'iptv_nonusage_fee_onetime':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"iptv_nonusage_fee_onetime" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargeonetime'});	
						}
					},
				};
				break;
			case 'cross_nonusage_fee_onetime':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"cross_nonusage_fee_onetime" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargeonetime'});	
						}
					},
				};
				break;
			case 'mobile_nonusage_fee_recurring':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_fee_recurring" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargerecurring'});
						}
					},
				};
				break;	
			case 'iptv_nonusage_fee_recurring':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_fee_recurring" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargerecurring'});
						}
					},
				};
				break;	
			case 'cross_nonusage_fee_recurring':
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"cross_nonusage_fee_recurring" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargerecurring'});
						}
					},
				};
				break;
			
			case "mobile_nonusage_subscription_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_subscription_bonus" : {
						"label" : "Bonus Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpriceallowanceonetime'});
						}
					},
				};
				break;
			
			case "mobile_nonusage_subscription_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_subscription_charge" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricechargeonetime'});
						}
					},
				};
				break;
			
			case "mobile_nonusage_recurring_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_recurring_bonus" : {
						"label" : "Bonus Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpriceallowancerecurring'});
						}
					},
				};
				break;
				
			case "iptv_nonusage_subscription_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_nonusage_subscription_bonus" : {
						"label" : "Bonus Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpriceallowance'});
						}
					},
				};
				break;
			case "cross_nonusage_subscription_bonus":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"cross_nonusage_subscription_bonus" : {
						"label" : "Bonus Item",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpriceallowance'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
						}
					},
				};	
				break;
			case "actionpricechargerecurring":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricechargerecurring" : {
						"label" : "Discount",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'actionpricediscount'});
						}
					},
				};	
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "actionpricediscount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricediscount" : {
						"label" : "ConditionSet",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonand'});
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
			case "conditioncommonand":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"what" : {
						"label" : "WHAT",
						"submenu" : {
			                "service_type" : {
			                    "label" : "ServiceType",
			                    "submenu" : {
			                        "VOICE": {
			                            "label" : "VOICE",
			                            action : function(node) {
			                                $.fn.addNode(node,{'childContentType': 'conditionwhatservicetypefactors','serviceType':'VOICE'});
			                            }
			                        },
			                        "SMS": {
			                            "label" : "SMS",
			                            action : function(node) {
			                                $.fn.addNode(node,{'childContentType': 'conditionwhatservicetypefactors','serviceType':'SMS'});
			                            }
			                        },
			                        "DATA": {
			                            "label" : "DATA",
			                            action : function(node) {
			                                $.fn.addNode(node,{'childContentType': 'conditionwhatservicetypefactors','serviceType':'DATA'});
			                            }
			                        },
			                    },
			                },
                   
              				"incomingcall" : {
								"label" : "Incoming Call",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhatincomingcall'});
								}
							},
							         
							"qos" : {
								"label" : "QoS",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhatqos'});
								}
							},
							"urlgroup" : {
								"label" : "URL Group",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhaturlgroupfactors'});
								}
							},
							"calltype" : {
								"label" : "Call Type",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhatcalltype'});
								}
							},
							"Counter" : {
								"label" : "Counter",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhatcounter'});
								}
							},
							"what custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhatcustomfactors'});
								}
							},
						}
					},
					"when" : {
						"label" : "WHEN",
						"submenu" : {
							"day" : {
								"label" : "Day",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhendayfactors'});
								}
							},
							"subscription_day" : {
								"label" : "Subscription Day",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhensubscriptionday'});
								}
							},
							"customerbirthday" : {
								"label" : "Customer Birthday",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhencustomerbirthday'});
								}
							},
							"companybirthday" : {
								"label" : "Company Birthday",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhencompanybirthday'});
								}
							},
							"duration" : {
								"label" : "Duration",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhendurationfactors'});									
								}
							},
							"holiday" : {
								"label" : "Holiday",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhenholidayfactors'});
								}
							},
							"timeslot" : {
								"label" : "Timeslot",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhentimeslotfactors'});
								}
							},
							"week" : {
								"label" : "Week",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhenweekfactors'});
								}
							},
							"firstmonth" : {
								"label" : "First Month",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhenfirstmonth'});
								}
							},
						}
					},
					"where" : {
						"label" : "WHERE",
						"submenu" : {
							"country" : {
								"label" : "Country",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwherecountryfactors'});
								}
							},
							"network" : {
								"label" : "Network",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwherenetworkfactors'});
								}
							},
							"zone" : {
								"label" : "Zone",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwherezonefactors'});
								}
							},
							"where custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwherecustomfactors'});
								}
							},
						}
					},
					"who" : {
						"label" : "WHO",
						"submenu" : {
							"member" : {
								"label" : "Member",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhomemberfactors'});
								}
							},
							"number" : {
								"label" : "Number",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhonumberfactors'});
								}
							},
							"prefix" : {
								"label" : "Prefix",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhoprefixfactors'});
								}
							},
							"who custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,{'childContentType': 'conditionwhocustomfactors'});
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
			case "conditionwhatcustomfactors":
            case "conditionwhatservicetypefactors":
			case "conditionwhendayfactors":
			case "conditionwhendurationfactors":
			case "conditionwhenholidayfactors":
			case "conditionwhentimeslotfactors":
			case "conditionwhenweekfactors":
			case "conditionwherecountryfactors":
			case "conditionwherenetworkfactors":
			case "conditionwherezonefactors":
			case "conditionwherecustomfactors":
			case "conditionwhomemberfactors":
			case "conditionwhonumberfactors":
			case "conditionwhoprefixfactors":
			case "conditionwhocustom":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};								
				break;
			case "mobile_usage_voice":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_usage_voice" : {
						"label" : "Tariff Plan",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'tariffplan'});
						}
					},
				};
				break;
			case "mobile_usage_sms": 
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"mobile_usage_sms" : {
						"label" : "Tariff Plan",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'tariffplan'});
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
							$.fn.addNode(node,{'childContentType': 'tariffplan'});
						}
					},
				};
				break;
            case "tariffplan":				
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
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
			case "allowed":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"allowed" : {
						"label" : "Number Special Factors",
						action : function(node) {
							$.fn.addNode(node,{'childContentType': 'numberspecialfactors'});
						}
					},
				};
				break;
			case 'numberspecialfactors':
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
							$.fn.addNode(node,{'childContentType': 'numberspecialrate'});
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
							$.fn.addNode(node,{'childContentType': 'conditioncommonratinggroup'});
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
			
			break; // vouchercardtype tree
			
		default:
			menus.custom_create = null;
			menus.custom_copy = null;
			menus.custom_paste = null;
			menus.custom_delete = null;
		}; // switch
		return menus;
	};
})(jQuery);

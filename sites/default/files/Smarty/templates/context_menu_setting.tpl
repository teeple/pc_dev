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
            case "dtn_mobile_attribute_prefix_range":
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
                    "prefix_range_allowed": {
                        "label" : "Allowed",
                        action : function(node) {
							$.fn.addNode(node,"prdattributeprefixrangeallowed");
                        }
                    },
                }
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
            case "simpleproductoffering":
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
                break;
            case "treenode_counter_main_basic":
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"treenode_counter_main_basic" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				}
                break;
            case "treenode_counter_main_optional":
                menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"treenode_counter_main_optional" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};		
                break;
            case "treenode_counter_accumulated_optional":
                menus.custom_delete._disabled = false;
                menus.custom_delete.action = function(node) {
                    $.fn.deleteNode(node);
                };
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
					"treenode_counter_accumulated_optional" : {
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};		
                break;
            case "dtn_mobile_counter_main":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"dtn_mobile_counter_main" : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node,"seltype_treenode_counter_main_optional");
						}
					},
				};
				break;
            case "dtn_mobile_counter_accumulated":
                menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"dtn_mobile_counter_accumulated " : {
						"label" : "Select Counter",
						action : function(node) {
							$.fn.loadSelectForm(node,"seltype_treenode_counter_accumulated_optional");
						}
					},
				};
                break;
            case "dtn_mobile_unittransfer":
            	menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"dtn_mobile_unittransfer " : {
						"label" : "Select Unit Transfer",
						action : function(node) {
							$.fn.loadSelectForm(node,"unit_transfer_select");
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
							$.fn.addNode(node,"actionpricechargefactors");
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
							$.fn.addNode(node,"actionpricediscountfactors");
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
							$.fn.addNode(node,"actionpriceallowancefactors");
						}
					},
				};
				break;
			case "nonusage_charge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"nonusage_charge" : {
						"label" : "Charge Item",
						action : function(node) {
							$.fn.addNode(node,"actionpricecharge");
						}
					},
				};
				break;
			case "nonusage_discount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"nonusage_discount" : {
						"label" : "Discount Item",
						action : function(node) {
							$.fn.addNode(node,"actionpricediscount");
						}
					},
				};
				break;
			case "nonusage_allowance":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"nonusage_allowance" : {
						"label" : "Allowance Item",
						action : function(node) {
							$.fn.addNode(node,"actionpriceallowance");
						}
					},
				};
				break;
			case "actionpricecharge":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricecharge" : {
						"label" : "OR",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};	
				break;
			case "actionpricediscount":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricediscount" : {
						"label" : "OR",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};	
				break;
			case "actionpriceallowance":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpriceallowance" : {
						"label" : "OR",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};	
				break;
			case "actionpricechargefactors":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricechargefactors" : {
						"label" : "OR",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
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
						"label" : "OR",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
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
						"label" : "Condition Set",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonor");
						}
					},
				};								
				menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};
				break;
			case "conditioncommonor":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"conditioncommonor" : {
						"label" : "Conditions",
						action : function(node) {
							$.fn.addConditionOperator(node,"conditioncommonand");
						}
					},
				};
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
                                            $.fn.addConditionServiceType(node, "conditionwhatservicetypefactors", "VOICE");
                                        }
                                    },
                                    "SMS": {
                                        "label" : "SMS",
                                        action : function(node) {
                                            $.fn.addConditionServiceType(node, "conditionwhatservicetypefactors", "SMS");
                                        }
                                    },
                                    "DATA": {
                                        "label" : "DATA",
                                        action : function(node) {
                                            $.fn.addConditionServiceType(node, "conditionwhatservicetypefactors", "DATA");
                                        }
                                    },
                                },
                            },
							"qos" : {
								"label" : "QoS",
								action : function(node) {
									$.fn.addNode(node,"conditionwhatqos");
								}
							},
							"urlgroup" : {
								"label" : "URL Group",
								action : function(node) {
									$.fn.addNode(node,"conditionwhaturlgroupfactors");
								}
							},
							"what custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,"conditionwhatcustomfactors");
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
									$.fn.addNode(node,"conditionwhendayfactors");
								}
							},
							"duration" : {
								"label" : "Duration",
								action : function(node) {
									$.fn.addNode(node,"conditionwhendurationfactors");
								}
							},
							"holiday" : {
								"label" : "Holiday",
								action : function(node) {
									$.fn.addNode(node,"conditionwhenholidayfactors");
								}
							},
							"timeslot" : {
								"label" : "Timeslot",
								action : function(node) {
									$.fn.addNode(node,"conditionwhentimeslotfactors");
								}
							},
							"week" : {
								"label" : "Week",
								action : function(node) {
									$.fn.addNode(node,"conditionwhenweekfactors");
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
									$.fn.addNode(node,"conditionwherecountryfactors");
								}
							},
							"network" : {
								"label" : "Network",
								action : function(node) {
									$.fn.addNode(node,"conditionwherenetworkfactors");
								}
							},
							"zone" : {
								"label" : "Zone",
								action : function(node) {
									$.fn.addNode(node,"conditionwherezonefactors");
								}
							},
							"where custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,"conditionwherecustomfactors");
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
									$.fn.addNode(node,"conditionwhomemberfactors");
								}
							},
							"number" : {
								"label" : "Number",
								action : function(node) {
									$.fn.addNode(node,"conditionwhonumberfactors");
								}
							},
							"prefix" : {
								"label" : "Prefix",
								action : function(node) {
									$.fn.addNode(node,"conditionwhoprefixfactors");
								}
							},
							"who custom" : {
								"label" : "Custom",
								action : function(node) {
									$.fn.addNode(node,"conditionwhocustomfactors");
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
			case "dtn_mobile_voice":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"dtn_mobile_voice" : {
						"label" : "Tariff Plan",
						action : function(node) {
							$.fn.addNode(node,"tariffplan");
						}
					},
				};
				break;
			case "dtn_mobile_sms":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"dtn_mobile_sms" : {
						"label" : "Tariff Plan",
						action : function(node) {
							$.fn.addNode(node,"tariffplan");
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
							$.fn.loadSelectForm(node,"numbering_plan_domestic");
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
							$.fn.loadSelectForm(node,"numbering_plan_idd");
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
							$.fn.loadSelectForm(node,"treeNodeAllowedNumberSpecial");
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
							$.fn.loadSelectForm(node,"treeNodeForbiddenNumberSpecial");
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
							$.fn.loadSelectForm(node,"treeNodeBasicRateDomestic");
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
							$.fn.loadSelectForm(node,"treeNodeBasicRateIDD");
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
							$.fn.loadSelectForm(node,"carrier_domestic");
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
							$.fn.loadSelectForm(node,"carrier_idd");
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
							$.fn.loadSelectForm(node,"basicrate_idd_ratinggroup");
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
							$.fn.loadSelectForm(node,"basicrate_domestic_ratinggroup");
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
		case "vouchercardtype_tree":
            console.log("vouchercardtype_tree");
            var relType = obj.attr("rel");
            switch(relType) {
            case "treenode_simpleproductoffering":
            	menus.custom_delete._disabled = false;
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};								
            	break;
            case "vouchercardtype":
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
                    "vouchercardtype" : {
                       "label" : "Select Products",
                        action: function(node) {
                            $.fn.loadSelectForm(node, "product");
                       }
                    }
                };
                break;
            case "counter":
                menus.custom_create._disabled = false;
                menus.custom_create.submenu = {
                    "counter" : {
                        "label" : "Recharged Amount",
                        action: function(node) {
                            $.fn.addNode(node, "treeNodeBonus");
                        }
                    }
                };
                break;
            case "treeNodeBonus":
				menus.custom_delete.action = function(node) {
					$.fn.deleteNode(node);
				};								
                menus.custom_delete._disabled = false;
                break;
            };
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
			case "treeNodeNumberSpecialFactors":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"treeNodeNumberSpecialFactors" : {
						"label" : "Number Special Factors",
						action : function(node) {
							$.fn.addNode(node,"numberspecialfactors");
						}
					},
				};
				break;
			case "treeNodeNumberSpecialRates":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"treeNodeNumberSpecialRates" : {
						"label" : "Charge Factors",
						action : function(node) {
							$.fn.addNode(node,"actionpricechargefactors");
						}
					},
				};
				break;
			case "actionpricechargefactors":
				menus.custom_create._disabled = false;
				menus.custom_create.submenu = {
					"actionpricechargefactors" : {
						"label" : "Rating Group",
						action : function(node) {
							$.fn.addNode(node,"conditioncommonratinggroup");
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
		default:
			menus.custom_create = null;
			menus.custom_copy = null;
			menus.custom_paste = null;
			menus.custom_delete = null;
		};
		return menus;
	};
})(jQuery);

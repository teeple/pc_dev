(function($) {
	$.fn.getTreeTypeSetting = function(treeType) {
	var types = {};
	switch (treeType) {
	case 'product_tree':
		types = {
			"types" : {
            	"simpleproductoffering": {
            		"valid_children" : ["mobile_attribute", "mobile_attribute_packaed", "mobile_counter", "mobile_nonusage", "mobile_usage"],
            		"icon" : {
                		// "image" : "/sites/default/files/applications.png"
                		"image" : "/sites/default/files/icons/service_domain_mobile.png"
                	},
				},
				
				// Attribute
				"mobile_attribute": {
					"valid_children" : ['mobile_attribute_featurecode', 'mobile_attribute_allowed_prefix', 'mobile_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				'mobile_attribute_featurecode': {
					"valid_children" : "none"
				}, 
				'mobile_attribute_allowed_prefix': {
					"valid_children" : "none"
				}, 
				'mobile_attribute_benefits': {
					"valid_children" : "none"
				},
				
				// Packaged
				"mobile_attribute_packaged" : {
					"valid_children" : ['mobile_packaged_mandatory', 'mobile_packaged_optional', 'mobile_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"mobile_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"mobile_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"mobile_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"prdattributepackaged" : {
					"valid_children" : "none"
				},
				
				// Counter
				"mobile_counter" : {
					"valid_children" : ['mobile_counter_main','mobile_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},

				},
				"mobile_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional"],
									"icon" : {
											"image" : "/sites/default/files/icons/inbox-document.png"
										},
                    		
                },
         "mobile_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "tree_node_counter_main_basic" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "tree_node_counter_main_optional" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "tree_node_counter_accumulated_optional" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "conditioncommonand" : {
                /*
                    "icon" : {
						"image" : "/sites/default/files/inbox-document.png"
                    }
                    */
                },
                
                // NonUsage
                
                "mobile_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                
                "mobile_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "mobile_nonusage_fee_onetime" : {
                	"valid_children" : ["treenodedepositscheme"],
                },
                "mobile_nonusage_subscription_bonus" : {
                	"valid_children" : ["treenodedepositscheme"],
            		"icon" : {
                		// "image" : "/sites/default/files/icons4use/present.png"
                		"image" : "/sites/default/files/icons/point.png"
                	},
                },
                "mobile_nonusage_deposit" : {
                	"valid_children" : ["treenodedepositscheme"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/user.png"
                	},
                },
                "treenodedepositscheme" : {
                	"icon" : {
                		"image" : "/sites/default/files/file.png"
                	}
                },
                "mobile_nonusage_threshold" : {
                	"valid_children" : ["treenodethresholdscheme"],
                },
                "treenodethresholdscheme" : {
                	"icon" : {
                		"image" : "/sites/default/files/file.png"
                	}
                },
                
                // Usage
				"mobile_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						// "image" : "/sites/default/files/applications.png"
								"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
                "mobile_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/voice.png"
                	}
                	
                },
                "mobile_usage_sms" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/SMS.png"
                	}
                	
                },
                "mobile_usage_data" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/data.png"
                	}
                	
                },
				"actionpricecharge" : {
					"valid_children" : [ "actionpricechargefactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpricediscount" : {
					"valid_children" : [ "actionpricediscountfactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpriceallowance" : {
					"valid_children" : [ "actionpriceallowancefactors" ],
					"icon" : {
						"image" : "/sites/default/files/inbox-document.png"
					}
				},
				"actionpricecharge":{
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricediscount":{
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpriceallowance":{
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricechargefactors" : {
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					},
				},
				"actionpricediscountfactors" : {
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"actionpriceallowancefactors" : {
					"valid_children" : [ "conditioncommonand" ],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatqos" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhaturlgroupfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhatcustomfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhendayfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhendurationfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenholidayfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhentimeslotfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhenweekfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecountryfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherenetworkfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherezonefactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwherecustomfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhomemberfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhonumberfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhoprefixfactors" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				"conditionwhocustom" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				
				"tariffplan" :{
                    "valid_children" : ["treeNodeBasicRateIDD", "treeNodePlanCustom"],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodenumberingplandomestic" :{
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodenumberingplanidd" :{
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "treenodecounter" :{
                    "valid_children" : ["all"],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "prdattributeprefixrangeallowed" :{
                    "valid_children" : ["all"],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                },
                "prdattributeprefixrangenotallowe" : {
                    "valid_children" : [],
                    "icon" : {
						"image" : "/sites/default/files/file.png"
                    }
                }
			}
		};
		break;
		
	case 'vouchercardtype_tree':
		types = {
			"types" : {
            	"vouchercardtype": {
            		"valid_children" : ["voucher_domain_specific", "voucher_product_specific"],
            		"icon" : {
                		"image" : "/sites/default/files/applications.png"
                	},
				},
				"voucher_domain_specific": {
					"valid_children" : ["voucher_domain_specific_mobile", "voucher_domain_specific_iptv", "voucher_domain_specific_broadband", "voucher_domain_specific_voip","voucher_domain_specific_satellite","voucher_domain_specific_dummy"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"voucher_product_specific": {
					"valid_children" : ["treenodeproductforvoucher"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"voucher_loyalty_point": {
					"valid_children" : ["none"],
					"icon" : {
						"image" : "/sites/default/files/folder.png"
					},
				},
				"treenodeproductforvoucher" : {
					"valid_children" : ["none"],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				}
			}
		};
		break;
	} // switch
	
	return types;
};
})(jQuery);

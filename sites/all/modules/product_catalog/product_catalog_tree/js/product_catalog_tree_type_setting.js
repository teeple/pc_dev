(function($) {
	$.fn.getTreeTypeSetting = function(treeType) {
	var types = {};
	switch (treeType) {
	case 'product_tree':
		types = {
			"types" : {
            	"simpleproductoffering": {
            		"valid_children" : ["mobile_attribute", "mobile_attribute_packaed", "mobile_counter", "mobile_nonusage", "mobile_usage"
            							,"iptv_attribute", "iptv_attribute_packaed", "iptv_counter", "iptv_nonusage", "iptv_usage"
            							,"broadband_attribute", "broadband_attribute_packaed", "broadband_counter", "broadband_nonusage", "broadband_usage"
            							,"voip_attribute", "voip_attribute_packaed", "voip_counter", "voip_nonusage", "voip_usage"
            							,"satellite_attribute", "satellite_attribute_packaed", "satellite_counter", "satellite_nonusage", "satellite_usage"
            							,"dummy_attribute", "dummy_attribute_packaed", "dummy_counter", "dummy_nonusage", "dummy_usage"
            							,"cross_attribute", "cross_attribute_packaed", "cross_counter", "cross_nonusage", "cross_usage"
            							],
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
				"iptv_attribute": {
					"valid_children" : ['iptv_attribute_featurecode', 'iptv_attribute_allowed_prefix', 'iptv_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				"voip_attribute": {
					"valid_children" : ['voip_attribute_featurecode', 'voip_attribute_allowed_prefix', 'voip_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				"broadband_attribute": {
					"valid_children" : ['broadband_attribute_featurecode', 'broadband_attribute_allowed_prefix', 'broadband_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				"satellite_attribute": {
					"valid_children" : ['satellite_attribute_featurecode', 'satellite_attribute_allowed_prefix', 'satellite_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				"dummy_attribute": {
					"valid_children" : ['dummy_attribute_featurecode', 'dummy_attribute_allowed_prefix', 'dummy_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/gear.png"
                	},
				},
				
				'mobile_attribute_featurecode': {
					"valid_children" : "none"
				},
				'voip_attribute_featurecode': {
					"valid_children" : "none"
				},
				'iptv_attribute_featurecode': {
					"valid_children" : "none"
				},
				'broadband_attribute_featurecode': {
					"valid_children" : "none"
				},
				'satellite_attribute_featurecode': {
					"valid_children" : "none"
				},
				'dummy_attribute_featurecode': {
					"valid_children" : "none"
				},
				'cross_attribute_benefits': {
					"valid_children" : "none"
				},
				
				'mobile_attribute_allowed_prefix': {
					"valid_children" : "none"
				},
				'voip_attribute_allowed_prefix': {
					"valid_children" : "none"
				},
				 
				'mobile_attribute_benefits': {
					"valid_children" : "none"
				},
				'iptv_attribute_benefits': {
					"valid_children" : "none"
				},
				'voip_attribute_benefits': {
					"valid_children" : "none"
				},
				'broadband_attribute_benefits': {
					"valid_children" : "none"
				},
				'satellite_attribute_benefits': {
					"valid_children" : "none"
				},
				'dummy_attribute_benefits': {
					"valid_children" : "none"
				},
				'cross_attribute_benefits': {
					"valid_children" : "none"
				},
				
				// Packaged
				"mobile_attribute_packaged" : {
					"valid_children" : ['mobile_packaged_mandatory', 'mobile_packaged_optional', 'mobile_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"iptv_attribute_packaged" : {
					"valid_children" : ['iptv_packaged_mandatory', 'iptv_packaged_optional', 'iptv_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"voip_attribute_packaged" : {
					"valid_children" : ['voip_packaged_mandatory', 'voip_packaged_optional', 'voip_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"broadband_attribute_packaged" : {
					"valid_children" : ['broadband_packaged_mandatory', 'broadband_packaged_optional', 'broadband_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"satellite_attribute_packaged" : {
					"valid_children" : ['satellite_packaged_mandatory', 'satellite_packaged_optional', 'satellite_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"dummy_attribute_packaged" : {
					"valid_children" : ['dummy_packaged_mandatory', 'dummy_packaged_optional', 'dummy_packaged_hidden'],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/puzzle.png"
                	},
				},
				"cross_attribute_packaged" : {
					"valid_children" : ['cross_packaged_mandatory', 'cross_packaged_optional', 'cross_packaged_hidden'],
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
				"iptv_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"voip_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"broadband_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"satellite_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"dummy_packaged_mandatory" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/tick-octagon.png"
                	},

				},
				"cross_packaged_mandatory" : {
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
				"iptv_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"voip_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"broadband_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"mobile_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
                	},
				},
				"mobile_packaged_optional" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
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
				"iptv_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"voip_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"broadband_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"satellite_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"dummy_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				"cross_packaged_hidden" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons4use/lock.png"
                	},
				},
				
				
				"mobile_packaged_product" : {
					"valid_children" : ["prdattributepackaged"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/octagon-plus.png"
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
				"iptv_counter" : {
					"valid_children" : ['iptv_counter_main', 'iptv_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},

				},
				"voip_counter" : {
					"valid_children" : ['voip_counter_main','voip_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},

				},
				"broadband_counter" : {
					"valid_children" : ['broadband_counter_main','broadband_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},

				},
				"satellite_counter" : {
					"valid_children" : ['satellite_counter_main','satellite_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},
				},
				"dummy_counter" : {
					"valid_children" : ['dummy_counter_main','dummy_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},
				},
				"cross_counter" : {
					"valid_children" : ['cross_counter_main','cross_counter_accumulated'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/battery.png"
                	},
				},

				"mobile_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "iptv_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "voip_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "broadband_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "satellite_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "dummy_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
                },
                "cross_counter_main" : {
                    "valid_children" : ["tree_node_counter_main_basic","tree_node_counter_main_optional","tree_node_counter_main_rollover"],
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
                "iptv_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "voip_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "broadband_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "satellite_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "dummy_counter_accumulated": {
                	"valid_children" : ['tree_node_counter_accumulated_optional'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
                	
                },
                "cross_counter_accumulated": {
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
                "iptv_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                "voip_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                "broadband_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                "satellite_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                "dummy_nonusage" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/wheel.png"
                	        }
                },
                "cross_nonusage" : {
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
                "iptv_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "voip_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "broadband_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "satellite_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "dummy_nonusage_fee_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                "crosss_nonusage_fee_recurring" : {
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
                	"icon" : {
                		"image" : "/sites/default/files/icons/threshold.png"
                	}
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
						
								"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"iptv_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"voip_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"broadband_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"satellite_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"dummy_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				"cross_usage" : {
					"valid_children" : [ "actionpricecharge",
							"actionpricediscount", "actionpriceallowance" ],
					"icon" : {
						"image" : "/sites/default/files/icons/system-monitor.png"
					}
				},
				
				"mobile_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/voice.png"
                	}
                },
                "voip_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/voice.png"
                	}
                },
                "cross_mobile_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/voice.png"
                	}
                },
                "cross_voip_usage_voice" : {
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
                "voip_usage_sms" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/SMS.png"
                	}
                	
                },
                "cross_mobile_usage_sms" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/SMS.png"
                	}
                	
                },
                "cross_voip_usage_sms" : {
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
                "voip_usage_data" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/data.png"
                	}
                },
                "cross_mobile_usage_data" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/data.png"
                	}
                },
                "cross_voip_usage_data" : {
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

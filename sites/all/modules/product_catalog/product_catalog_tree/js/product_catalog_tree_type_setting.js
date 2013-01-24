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
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				"iptv_attribute": {
					"valid_children" : ['iptv_attribute_featurecode', 'iptv_attribute_allowed_prefix', 'iptv_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				"voip_attribute": {
					"valid_children" : ['voip_attribute_featurecode', 'voip_attribute_allowed_prefix', 'voip_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				"broadband_attribute": {
					"valid_children" : ['broadband_attribute_featurecode', 'broadband_attribute_allowed_prefix', 'broadband_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				"satellite_attribute": {
					"valid_children" : ['satellite_attribute_featurecode', 'satellite_attribute_allowed_prefix', 'satellite_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				"dummy_attribute": {
					"valid_children" : ['dummy_attribute_featurecode', 'dummy_attribute_allowed_prefix', 'dummy_attribute_benefits'],
            		"icon" : {
                		"image" : "/sites/default/files/icons/attribute.png"
                	},
				},
				
				'mobile_attribute_featurecode': {
					"valid_children" : "none"
					,
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'voip_attribute_featurecode': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'iptv_attribute_featurecode': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'broadband_attribute_featurecode': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'satellite_attribute_featurecode': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'dummy_attribute_featurecode': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'cross_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'mobile_attribute_allowed_prefix': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'voip_attribute_allowed_prefix': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				 
				'mobile_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'iptv_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'voip_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'broadband_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'satellite_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'dummy_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'cross_attribute_benefits': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				
				'attribute_allowed_device': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'attribute_required_device': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'mobile_attribute_subscriber_lifecycle_scheme': {
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/attribute_detail.png"
					      	},
				},
				'treenodelifecyclescheme': {
					"valid_children" : "none",
					  		"icon" : {
					      		"image" : "/sites/default/files/icons/scheme.png"
					      	},
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
				
				"mobile_nonusage_unittransfer_scheme" : {
					"icon" : {
							"image" : "/sites/default/files/icons/scheme.png"
						},
				},
				
				"mobile_nonusage_voucher" : {
					"icon" : {
							"image" : "/sites/default/files/icons/voucher.png"
						},
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
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
                    					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
        },
				"voip_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"iptv_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"broadband_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"dummy_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"satellite_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				"cross_counter_main" : {
					"valid_children" : ["tree_node_counter_main_basic_prepaid", "tree_node_counter_main_basic_postpaid",
															"tree_node_counter_main_optional_prepaid", "tree_node_counter_main_optional_postpaid",
				            					"tree_node_counter_main_rollover_prepaid", "tree_node_counter_main_rollover_postpaid"],
					"icon" : {
						"image" : "/sites/default/files/icons/inbox-document.png"
					},
				},
				
				"mobile_counter_accumulated": {
						"valid_children" : ['tree_node_counter_accumulated_optional_prepaid',"tree_node_counter_accumulated_optional_postpaid",
								'tree_node_counter_accumulated_rollover_prepaid', 'tree_node_counter_accumulated_rollover_prepaid'],
                	"icon" : {
                			"image" : "/sites/default/files/icons/inbox-document.png"
                		},
				},
				
				"tree_node_counter_main_basic_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/icons/Basic_Prepaid.png"
                    }
        },
        "tree_node_counter_main_basic_postpaid" : {
        	"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
        		"image" : "/sites/default/files/icons/Basic_Postpaid.png"
                    }
        },
        
        "tree_node_counter_main_optional_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/icons/Optional_Prepaid.png"
                    }
                },
				"tree_node_counter_main_optional_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
        		    "icon" : {
						"image" : "/sites/default/files/icons/Optional_Postpaid.png"
            }
        },
        "tree_node_counter_main_rollover_prepaid" : {
        	"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
        		"image" : "/sites/default/files/icons/Rollover_Prepaid.png"
                    }
                },
        "tree_node_counter_main_rollover_postpaid" : {
        	"valid_children" : [ "conditioncommonand" ],
        		    "icon" : {
        		"image" : "/sites/default/files/icons/Rollover_Postpaid.png"
            }
        },
        
        "tree_node_counter_accumulated_optional_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
						"image" : "/sites/default/files/icons/Optional_Prepaid.png"
                    }
				},
        "tree_node_counter_accumulated_optional_postpaid" : {
        	"valid_children" : [ "conditioncommonand" ],
                    "icon" : {
        		"image" : "/sites/default/files/icons/Optional_Postpaid.png"
                    }
                },
                
				"tree_node_counter_accumulated_rollover_prepaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Prepaid.png"
				            }
				},
				"tree_node_counter_accumulated_rollover_postpaid" : {
					"valid_children" : [ "conditioncommonand" ],
				            "icon" : {
						"image" : "/sites/default/files/icons/Rollover_Postpaid.png"
				            }
				        },
        
        
        "conditioncommonand_nonusage_subscription" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        
        "conditioncommonand_nonusage_recurring" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_usageend" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_recharge" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_unsubscription" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_nonusage_activation" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },

				"conditioncommonand_usage_sms" : {
				            "icon" : {
						"image" : "/sites/default/files/icons/conditioncommonand.png"
				            }
				        },

        "conditioncommonand_usage_voice" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_data" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_mms" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_crbt" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_loyalty_point_deduct" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
                },
        "conditioncommonand_usage_vod" : {
                    "icon" : {
        		"image" : "/sites/default/files/icons/conditioncommonand.png"
                    }
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
                
                "treeNodeCustomCharge" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
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
                
                "mobile_nonusage_recurring" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/ui-menu.png"
                	        }
                },
                "mobile_nonusage_subscription_charge" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/ui-menu.png"
                	        }
                },
								"mobile_nonusage_subscription" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_unsubscription" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_recharge" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_usageend" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_activation" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_unittransfer" : {
									"valid_children" : ["treenodedepositscheme"],
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								"mobile_nonusage_otheronetimecharge" : {
									"icon" : {
									"image" : "/sites/default/files/icons/ui-menu.png"
									        }
								},
								
                "mobile_nonusage_subscription_charge" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                
                "mobile_nonusage_subscription_discount" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/discount.png"
                	        }
                },
                
								"mobile_nonusage_unsubscription_charge" : {
									"icon" : {
									"image" : "/sites/default/files/icons/money.png"
									        }
								},
                
                "mobile_nonusage_unsubscription_discount" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/discount.png"
                	        }
                },
                
                "mobile_nonusage_recurring_discount" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/discount.png"
                	        }
                },
                
                "treeNodeCustomDiscount" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/discount.png"
                	        }
                },
                
                "data_tariffplan_rates" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/basic_rate.png"
                	        }
                },
                
                "data_tariffplan_basicrate" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/basic_rate.png"
                	        }
                },
                
                "treeNodeBasicRateIDD" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/basic_rate.png"
                	        }
                },
                                
                "treeNodeCustomBlock" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/custom_block.png"
                	        }
                },
                
                "treeNodePlanCustom" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/custom_rate.png"
                	        }
                },
                
                "treenodeotheronetimecharge" : {
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                
                "mobile_nonusage_unsubscription_penalty" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                	"image" : "/sites/default/files/icons/money.png"
                	        }
                },
                
                "mobile_nonusage_fee_onetime" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/money.png"
                		        }
                },
                
                "mobile_nonusage_subscription_bonus" : {
                	"valid_children" : ["treenodedepositscheme"],
            		"icon" : {
                		"image" : "/sites/default/files/icons/point.png"
                	},
                },
                
                "mobile_nonusage_activation_bonus" : {
                	"valid_children" : ["treenodedepositscheme"],
                "icon" : {
                		"image" : "/sites/default/files/icons/point.png"
                	},
                },
                
                "mobile_nonusage_recharge_bonus" : {
                	"valid_children" : ["treenodedepositscheme"],
                "icon" : {
                		"image" : "/sites/default/files/icons/point.png"
                	},
                },

								"mobile_nonusage_usageend_bonus" : {
									"valid_children" : ["treenodedepositscheme"],
								"icon" : {
										"image" : "/sites/default/files/icons/point.png"
									},
								},
                
                "mobile_nonusage_recurring_bonus" : {
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

				"mobile_usage_mms" : {
        	"valid_children" : ["treenodedepositscheme"],
        	"icon" : {
        		"image" : "/sites/default/files/icons/MMS.png"
        	}
        },
				"mobile_usage_crbt" : {
					"valid_children" : ["treenodedepositscheme"],
					"icon" : {
						"image" : "/sites/default/files/icons/CRBT.png"
					}
				},
				"mobile_usage_loyaltypoint" : {
					"valid_children" : ["treenodedepositscheme"],
					"icon" : {
						"image" : "/sites/default/files/icons/Loyalty_Point.png"
					}
				},
				"mobile_usage_vod" : {
					"valid_children" : ["treenodedepositscheme"],
					"icon" : {
						"image" : "/sites/default/files/icons/VOD.png"
					}
				},
				
				"mobile_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/Voice.png"
                	}
                },
                "voip_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/Voice.png"
                	}
                },
                "cross_mobile_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/Voice.png"
                	}
                },
                "cross_voip_usage_voice" : {
                	"valid_children" : ["treenodedepositscheme"],
                	"icon" : {
                		"image" : "/sites/default/files/icons/Voice.png"
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
                		"image" : "/sites/default/files/icons/Data02.png"
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
						"image" : "/sites/default/files/inui-menu-document.png"
					}
				},
				"actionpricediscount" : {
					"valid_children" : [ "actionpricediscountfactors" ],
					"icon" : {
						"image" : "/sites/default/files/inui-menu-document.png"
					}
				},
				"actionpriceallowance" : {
					"valid_children" : [ "actionpriceallowancefactors" ],
					"icon" : {
						"image" : "/sites/default/files/inui-menu-document.png"
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
				"conditionwhocustomerlevel" : {
					"valid_children" : [],
					"icon" : {
						"image" : "/sites/default/files/file.png"
					}
				},
				
				"tariffplan" :{
                    "valid_children" : ["treeNodeBasicRateIDD", "treeNodePlanCustom"],
                    "icon" : {
						"image" : "/sites/default/files/icons/plan.png"
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

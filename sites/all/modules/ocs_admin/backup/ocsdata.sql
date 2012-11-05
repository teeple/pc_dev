-- phpMyAdmin SQL Dump
-- version 3.4.10.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 26, 2012 at 03:48 PM
-- Server version: 5.1.41
-- PHP Version: 5.3.2-1ubuntu4.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `ocsdata`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`root`@`%` PROCEDURE `prc_fill_group_hierarchy`(level INT, fill INT)
BEGIN
        DECLARE _level INT;
        DECLARE _fill INT;
        INSERT
        INTO    ocs_group (group_id, parent_group_id)
        VALUES  (1, 0);
        SET _fill = 0;
        WHILE _fill < fill DO
                INSERT
                INTO    ocs_group (parent_group_id)
                VALUES  (1);
                SET _fill = _fill + 1;
        END WHILE;
        SET _fill = 1;
        SET _level = 0;
        WHILE _level < level DO
                INSERT
                INTO    ocs_group (parent_group_id)
                SELECT  hn.group_id
                FROM    ocs_group ho, ocs_group hn
                WHERE   ho.parent_group_id = 1
                        AND hn.id > _fill;
                SET _level = _level + 1;
                SET _fill = _fill + POWER(fill, _level);
        END WHILE;
END$$

CREATE DEFINER=`root`@`%` PROCEDURE `prc_fill_hierarchy`(level INT, fill INT)
BEGIN
        DECLARE _level INT;
        DECLARE _fill INT;
        INSERT
        INTO    t_hierarchy (id, parent)
        VALUES  (1, 0);
        SET _fill = 0;
        WHILE _fill < fill DO
                INSERT
                INTO    t_hierarchy (parent)
                VALUES  (1);
                SET _fill = _fill + 1;
        END WHILE;
        SET _fill = 1;
        SET _level = 0;
        WHILE _level < level DO
                INSERT
                INTO    t_hierarchy (parent)
                SELECT  hn.id
                FROM    t_hierarchy ho, t_hierarchy hn
                WHERE   ho.parent = 1
                        AND hn.id > _fill;
                SET _level = _level + 1;
                SET _fill = _fill + POWER(fill, _level);
        END WHILE;
END$$

--
-- Functions
--
CREATE DEFINER=`root`@`%` FUNCTION `hierarchy_group_connect_by_parent`(value INT) RETURNS int(11)
    READS SQL DATA
BEGIN
        DECLARE _id INT;
        DECLARE _parent INT;
        DECLARE _next INT;
        DECLARE CONTINUE HANDLER FOR NOT FOUND SET @id = NULL;

        SET _parent = @id;
        SET _id = -1;

        IF @id IS NULL THEN
                RETURN NULL;
        END IF;

        LOOP
                SELECT  MIN(id)
                INTO    @id
                FROM    ocs_group
                WHERE   parent_group_id = _parent
                        AND id > _id;
                IF @id IS NOT NULL OR _parent = @start_with THEN
                        SET @level = @level + 1;
                        RETURN @id;
                END IF;
                SET @level := @level - 1;
                SELECT  group_id, parent_group_id
                INTO    _id, _parent
                FROM    ocs_group
                WHERE   id = _parent;
        END LOOP;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `abmf_account`
--

CREATE TABLE IF NOT EXISTS `abmf_account` (
  `subscription_key` varchar(20) COLLATE latin1_general_ci NOT NULL,
  `BALANCE` int(11) DEFAULT NULL,
  `BALANCE2` int(11) DEFAULT NULL,
  `TIME_STAMP` bigint(20) DEFAULT NULL,
  `ACCOUNT_DEPOSIT` int(11) DEFAULT NULL,
  `DEPOSIT_TIME` bigint(20) DEFAULT NULL,
  `DEPOSIT_COUNT` int(11) DEFAULT NULL,
  `RESERVED0` varchar(8) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`subscription_key`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `abmf_account`
--

INSERT INTO `abmf_account` (`subscription_key`, `BALANCE`, `BALANCE2`, `TIME_STAMP`, `ACCOUNT_DEPOSIT`, `DEPOSIT_TIME`, `DEPOSIT_COUNT`, `RESERVED0`) VALUES
('91100055', NULL, NULL, NULL, 0, 1334884532998, 0, NULL),
('91100022', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('91100011', NULL, NULL, NULL, 0, 1337923493961, 0, NULL),
('91100066', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('91100033', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('91100303', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('91100001', NULL, NULL, NULL, 0, 1337933731247, 0, NULL),
('91100044', NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('91100000', NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `abmf_counter`
--

CREATE TABLE IF NOT EXISTS `abmf_counter` (
  `subscription_key` varchar(24) COLLATE latin1_general_ci NOT NULL COMMENT '... ID (MDN, MSISDN)  ',
  `counter_id` int(11) NOT NULL COMMENT 'COUNTER ID (ex:freeDosu,freeVodPacket)',
  `counter_value` int(11) NOT NULL DEFAULT '0' COMMENT 'COUNTER .',
  `counter_value2` int(11) NOT NULL DEFAULT '0' COMMENT '... COUNTER .',
  `counter_max_value` int(11) NOT NULL DEFAULT '0' COMMENT 'COUNTER .. .',
  `counter_expire` bigint(20) NOT NULL DEFAULT '0' COMMENT 'COUNTER .....',
  `counter_deposit` int(11) NOT NULL DEFAULT '0' COMMENT '... COUNTER VALUE',
  `RESERVED0` varchar(8) COLLATE latin1_general_ci DEFAULT NULL,
  UNIQUE KEY `IDX_OCS_COUNTER_01` (`subscription_key`,`counter_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `abmf_counter`
--

INSERT INTO `abmf_counter` (`subscription_key`, `counter_id`, `counter_value`, `counter_value2`, `counter_max_value`, `counter_expire`, `counter_deposit`, `RESERVED0`) VALUES
('91100001', 0, 5000000, 5000000, 0, 0, 0, NULL),
('91100001', 1, 4922240, 5000000, 0, 0, 0, NULL),
('91100011', 0, 5000000, 0, 0, 0, 0, NULL),
('91100011', 1, 4967600, 0, 0, 0, 0, ''),
('91100011', 2, 3000, 0, 0, 0, 0, NULL),
('91100011', 3, 100, 0, 0, 0, 0, NULL),
('91100033', 1, 100, 0, 0, 0, 0, '0'),
('91100033', 9, 100, 0, 0, 0, 0, '0'),
('91100055', 3, 0, 3, 0, 0, 0, NULL),
('91100077', 1, 50000000, 49935200, 0, 1366387200000, 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `ACCOUNT_TBL`
--

CREATE TABLE IF NOT EXISTS `ACCOUNT_TBL` (
  `SUBS_ID` varchar(20) COLLATE latin1_general_ci NOT NULL,
  `BALANCE` int(11) DEFAULT NULL,
  `BALANCE2` int(11) DEFAULT NULL,
  `TIME_STAMP` bigint(20) DEFAULT NULL,
  `ACCOUNT_DEPOSIT` int(11) DEFAULT NULL,
  `DEPOSIT_TIME` bigint(20) DEFAULT NULL,
  `DEPOSIT_COUNT` int(11) DEFAULT NULL,
  `RESERVED0` varchar(8) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`SUBS_ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Stand-in structure for view `activation_bonus_amount`
--
CREATE TABLE IF NOT EXISTS `activation_bonus_amount` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`targetRule_fid` int(11)
,`targetRule_op` int(11)
,`targetRule` varchar(32)
,`targetRuleLower` varchar(32)
,`targetRuleUpper` varchar(32)
,`targetRule_ref` varchar(32)
,`db_action_fid` int(11)
,`db_action_op` int(11)
,`db_action` varchar(128)
,`db_actionLower` varchar(128)
,`db_actionUpper` varchar(128)
,`db_action_ref` varchar(32)
,`counter_id_fid` int(11)
,`counter_id_op` int(11)
,`counter_id` varchar(32)
,`counter_idLower` varchar(32)
,`counter_idUpper` varchar(32)
,`counter_id_ref` varchar(32)
,`bonus_amount_fid` int(11)
,`bonus_amount_op` int(11)
,`bonus_amount` int(11)
,`bonus_amountLower` int(11)
,`bonus_amountUpper` int(11)
,`bonus_amount_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `activation_bonus_condition`
--
CREATE TABLE IF NOT EXISTS `activation_bonus_condition` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`fullday_fid` int(11)
,`fullday_op` int(11)
,`fullday` varchar(10)
,`fulldayLower` varchar(10)
,`fulldayUpper` varchar(10)
,`fullday_ref` varchar(32)
,`product_fid` int(11)
,`product_op` int(11)
,`product` varchar(4)
,`productLower` varchar(4)
,`productUpper` varchar(4)
,`product_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `aios_charging_account`
--
CREATE TABLE IF NOT EXISTS `aios_charging_account` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`call_type_fid` int(11)
,`call_type_op` int(11)
,`call_type` varchar(32)
,`call_typeLower` varchar(32)
,`call_typeUpper` varchar(32)
,`call_type_ref` varchar(32)
,`service_fid` int(11)
,`service_op` int(11)
,`service` varchar(32)
,`serviceLower` varchar(32)
,`serviceUpper` varchar(32)
,`service_ref` varchar(32)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
,`priority_fid` int(11)
,`priority_op` int(11)
,`priority` int(11)
,`priorityLower` int(11)
,`priorityUpper` int(11)
,`priority_ref` varchar(32)
,`counter_name_fid` int(11)
,`counter_name_op` int(11)
,`counter_name` varchar(32)
,`counter_nameLower` varchar(32)
,`counter_nameUpper` varchar(32)
,`counter_name_ref` varchar(32)
,`counter_type_fid` int(11)
,`counter_type_op` int(11)
,`counter_type` varchar(6)
,`counter_typeLower` varchar(6)
,`counter_typeUpper` varchar(6)
,`counter_type_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `aios_price_decision`
--
CREATE TABLE IF NOT EXISTS `aios_price_decision` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`call_type_fid` int(11)
,`call_type_op` int(11)
,`call_type` varchar(32)
,`call_typeLower` varchar(32)
,`call_typeUpper` varchar(32)
,`call_type_ref` varchar(32)
,`service_fid` int(11)
,`service_op` int(11)
,`service` varchar(32)
,`serviceLower` varchar(32)
,`serviceUpper` varchar(32)
,`service_ref` varchar(32)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `aios_tariff_decision`
--
CREATE TABLE IF NOT EXISTS `aios_tariff_decision` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`call_type_fid` int(11)
,`call_type_op` int(11)
,`call_type` varchar(32)
,`call_typeLower` varchar(32)
,`call_typeUpper` varchar(32)
,`call_type_ref` varchar(32)
,`service_fid` int(11)
,`service_op` int(11)
,`service` varchar(32)
,`serviceLower` varchar(32)
,`serviceUpper` varchar(32)
,`service_ref` varchar(32)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `call_type`
--
CREATE TABLE IF NOT EXISTS `call_type` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`calling_fid` int(11)
,`calling_op` int(11)
,`calling` varchar(32)
,`callingLower` varchar(32)
,`callingUpper` varchar(32)
,`calling_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Table structure for table `countername_tbl`
--

CREATE TABLE IF NOT EXISTS `countername_tbl` (
  `counter_id` int(11) NOT NULL DEFAULT '0',
  `counter_type` int(11) DEFAULT NULL,
  `counter_name` varchar(64) DEFAULT NULL,
  `counter_scale` int(11) DEFAULT '1',
  `counter_desc` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`counter_id`),
  UNIQUE KEY `countername_tbl_name` (`counter_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `countername_tbl`
--

INSERT INTO `countername_tbl` (`counter_id`, `counter_type`, `counter_name`, `counter_scale`, `counter_desc`) VALUES
(0, 0, 'Remains', 100, 'Remains'),
(1, 0, 'LastRemains', 100, 'LastRemains'),
(2, 0, 'FreeVoice', 10, 'FreeVoice'),
(3, 0, 'FreeSms', 1, 'FreeSms'),
(4, 0, 'FreePacket', 1, 'FreePacket'),
(11, 0, 'TotalUsedMoney', 100, 'TotalUsedMoney'),
(12, 0, 'UsedFreeCallTime', 10, 'UsedFreeCallTime'),
(13, 0, 'UsedFreeSms', 1, 'UsedFreeSms'),
(14, 0, 'UsedFreePacket', 1, 'UsedFreePacket'),
(15, 0, 'AttemptOfCall', 1, 'AttemptOfCall'),
(100, 0, 'UsedVolumeWithQoS', 1, 'UsedVolumeWithQoS'),
(101, 0, 'UsedTimeWithQoS', 10, 'UsedTimeWithQoS'),
(200, 0, 'GENERAL_REMAINS', 100, 'GENERAL_REMAINS'),
(201, 0, 'FREE_VOICE', 10, 'FREE_VOICE'),
(202, 0, 'FREE_SMS', 1, 'FREE_SMS'),
(203, 0, 'FREE_PACKET', 1, 'FREE_PACKET'),
(204, 0, 'Family_Free_Voice', 10, 'Family_Free_Voice'),
(205, 0, 'Family_Free_SMS', 1, 'Family_Free_Sms'),
(206, 0, 'Sponsor_Balance', 100, 'Sponsor_Balance'),
(207, 0, 'SNS_REMAINS', 100, 'SNS_REMAINS'),
(300, 0, 'POST_PAID', 100, 'POST_PAID');

-- --------------------------------------------------------

--
-- Table structure for table `COUNTER_TBL`
--

CREATE TABLE IF NOT EXISTS `COUNTER_TBL` (
  `SUBS_ID` varchar(20) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `COUNTER_ID` int(11) NOT NULL DEFAULT '0',
  `COUNTER_VALUE` int(11) DEFAULT NULL,
  `COUNTER_VALUE2` int(11) DEFAULT NULL,
  `COUNTER_MAX_VALUE` int(11) DEFAULT NULL,
  `COUNTER_EXPIRE` bigint(20) DEFAULT NULL,
  `COUNTER_DEPOSIT` int(11) DEFAULT NULL,
  `RESERVED0` varchar(8) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`SUBS_ID`,`COUNTER_ID`),
  UNIQUE KEY `IDX_COUNTER_TBL_02` (`SUBS_ID`,`COUNTER_ID`),
  KEY `IDX_COUNTER_TBL_01` (`SUBS_ID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `dailyCounterPrice`
--

CREATE TABLE IF NOT EXISTS `dailyCounterPrice` (
  `service_id` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promotionCounterType` int(11) NOT NULL DEFAULT '0',
  `counterID` varchar(255) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `counterType` int(11) DEFAULT NULL,
  `initialValue` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `setCounterTo` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterExpiryDate` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterScale` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterThreshold` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterChange` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`,`promotionCounterType`,`counterID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `daily_promotion`
--

CREATE TABLE IF NOT EXISTS `daily_promotion` (
  `service_id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promoEndDate` varchar(18) COLLATE latin1_general_ci DEFAULT '2099-12-31',
  `promotionType` varchar(16) COLLATE latin1_general_ci DEFAULT 'general',
  `setup` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `targetSubsRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoCountingRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoGrantRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoUseRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `discountType` varchar(16) COLLATE latin1_general_ci DEFAULT NULL,
  `countWhenUse` tinyint(1) DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `category` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `if_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `if_not_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `setPriceTo` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `priceDiscountRate` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Stand-in structure for view `discount_rules`
--
CREATE TABLE IF NOT EXISTS `discount_rules` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`service_fid` int(11)
,`service_op` int(11)
,`service` varchar(32)
,`serviceLower` varchar(32)
,`serviceUpper` varchar(32)
,`service_ref` varchar(32)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
,`data_load_type_fid` int(11)
,`data_load_type_op` int(11)
,`data_load_type` int(11)
,`data_load_typeLower` int(11)
,`data_load_typeUpper` int(11)
,`data_load_type_ref` varchar(32)
,`discount_rate_fid` int(11)
,`discount_rate_op` int(11)
,`discount_rate` int(11)
,`discount_rateLower` int(11)
,`discount_rateUpper` int(11)
,`discount_rate_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Table structure for table `enum_factor_meta`
--

CREATE TABLE IF NOT EXISTS `enum_factor_meta` (
  `enum_name` varchar(64) COLLATE latin1_general_ci NOT NULL,
  PRIMARY KEY (`enum_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `enum_factor_value`
--

CREATE TABLE IF NOT EXISTS `enum_factor_value` (
  `enum_name` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `enum_code` int(11) NOT NULL DEFAULT '0',
  `enum_string` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`enum_name`,`enum_code`),
  UNIQUE KEY `enum_factor_value_string_key` (`enum_name`,`enum_string`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Stand-in structure for view `event_actions`
--
CREATE TABLE IF NOT EXISTS `event_actions` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
,`event_name_fid` int(11)
,`event_name_op` int(11)
,`event_name` varchar(32)
,`event_nameLower` varchar(32)
,`event_nameUpper` varchar(32)
,`event_name_ref` varchar(32)
,`promotion_service_id_fid` int(11)
,`promotion_service_id_op` int(11)
,`promotion_service_id` varchar(30)
,`promotion_service_idLower` varchar(30)
,`promotion_service_idUpper` varchar(30)
,`promotion_service_id_ref` varchar(32)
,`priority_fid` int(11)
,`priority_op` int(11)
,`priority` int(11)
,`priorityLower` int(11)
,`priorityUpper` int(11)
,`priority_ref` varchar(32)
,`promotion_category_fid` int(11)
,`promotion_category_op` int(11)
,`promotion_category` varchar(30)
,`promotion_categoryLower` varchar(30)
,`promotion_categoryUpper` varchar(30)
,`promotion_category_ref` varchar(32)
,`promotion_parameter_fid` int(11)
,`promotion_parameter_op` int(11)
,`promotion_parameter` varchar(256)
,`promotion_parameterLower` varchar(256)
,`promotion_parameterUpper` varchar(256)
,`promotion_parameter_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Table structure for table `FactorList`
--

CREATE TABLE IF NOT EXISTS `FactorList` (
  `fieldName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `fieldAlias` varchar(64) COLLATE latin1_general_ci DEFAULT NULL,
  `fieldType` int(11) NOT NULL,
  `fieldLength` int(11) DEFAULT NULL,
  `domain_type` varchar(64) COLLATE latin1_general_ci DEFAULT NULL,
  `domain_expr` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  `description` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`fieldName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `FactorList`
--

INSERT INTO `FactorList` (`fieldName`, `fieldAlias`, `fieldType`, `fieldLength`, `domain_type`, `domain_expr`, `description`) VALUES
('service', NULL, 1, 32, NULL, NULL, NULL),
('service_id', NULL, 1, 32, NULL, NULL, NULL),
('data_load_type', NULL, 0, 0, NULL, NULL, NULL),
('discount_rate', NULL, 0, 0, NULL, NULL, NULL),
('event_name', NULL, 1, 32, NULL, NULL, NULL),
('promotion_service_id', NULL, 1, 30, NULL, NULL, NULL),
('priority', NULL, 0, 0, NULL, NULL, NULL),
('promotion_category', NULL, 1, 30, NULL, NULL, NULL),
('promotion_parameter', NULL, 1, 256, NULL, NULL, NULL),
('call_type', NULL, 1, 32, NULL, NULL, NULL),
('counter_name', NULL, 1, 32, NULL, NULL, NULL),
('counter_type', NULL, 1, 6, NULL, NULL, NULL),
('fullday', NULL, 1, 10, NULL, NULL, NULL),
('product', NULL, 1, 4, NULL, NULL, NULL),
('targetRule', NULL, 1, 32, NULL, NULL, NULL),
('counter_id', NULL, 1, 32, NULL, NULL, NULL),
('bonus_amount', NULL, 0, 0, NULL, NULL, NULL),
('week', NULL, 1, 4, NULL, NULL, NULL),
('time', NULL, 1, 4, NULL, NULL, NULL),
('calling', NULL, 1, 32, NULL, NULL, NULL),
('TotalUsedMoney', NULL, 0, 0, NULL, NULL, NULL),
('db_action', NULL, 1, 128, NULL, NULL, NULL),
('is_vpn', NULL, 1, 6, NULL, NULL, NULL),
('vpn_discount_rate', NULL, 0, 0, NULL, NULL, NULL),
('vpn_group_id', NULL, 0, 0, NULL, NULL, NULL),
('vpn_grou_id', NULL, 1, 10, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factorpool_generator`
--

CREATE TABLE IF NOT EXISTS `factorpool_generator` (
  `id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `factor_name` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `expression` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`,`factor_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_bonus_amount`
--

CREATE TABLE IF NOT EXISTS `factor_bonus_amount` (
  `bonus_amount_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `bonus_amount_op` int(11) DEFAULT NULL,
  `bonus_amount` int(11) DEFAULT NULL,
  `bonus_amountLower` int(11) DEFAULT NULL,
  `bonus_amountUpper` int(11) DEFAULT NULL,
  `bonus_amount_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`bonus_amount_fid`),
  KEY `factor_bonus_amount_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=144 ;

--
-- Dumping data for table `factor_bonus_amount`
--

INSERT INTO `factor_bonus_amount` (`bonus_amount_fid`, `ruleSetName`, `ruleName`, `rule_id`, `bonus_amount_op`, `bonus_amount`, `bonus_amountLower`, `bonus_amountUpper`, `bonus_amount_ref`) VALUES
(143, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1376, 0, 600, 600, 600, NULL),
(142, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1375, 0, 50, 50, 50, NULL),
(141, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1374, 0, 300, 300, 300, NULL),
(140, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1373, 0, 100, 100, 100, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_bonus_amount_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_bonus_amount_notlist` (
  `bonus_amount_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`bonus_amount_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_calling`
--

CREATE TABLE IF NOT EXISTS `factor_calling` (
  `calling_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `calling_op` int(11) DEFAULT NULL,
  `calling` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `callingLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `callingUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `calling_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`calling_fid`),
  KEY `factor_calling_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=681 ;

--
-- Dumping data for table `factor_calling`
--

INSERT INTO `factor_calling` (`calling_fid`, `ruleSetName`, `ruleName`, `rule_id`, `calling_op`, `calling`, `callingLower`, `callingUpper`, `calling_ref`) VALUES
(680, 'call_type', 'IPTV', 1368, 3, 'FF', 'FF', 'FF', NULL),
(679, 'call_type', 'PSTN', 1367, 3, '09', '09', '09', NULL),
(678, 'call_type', 'PSTN', 1367, 3, '08', '08', '08', NULL),
(677, 'call_type', 'PSTN', 1367, 3, '07', '07', '07', NULL),
(676, 'call_type', 'PSTN', 1367, 3, '06', '06', '06', NULL),
(675, 'call_type', 'PSTN', 1367, 3, '05', '05', '05', NULL),
(674, 'call_type', 'PSTN', 1367, 3, '04', '04', '04', NULL),
(673, 'call_type', 'PSTN', 1367, 3, '03', '03', '03', NULL),
(672, 'call_type', 'PSTN', 1367, 3, '02', '02', '02', NULL),
(671, 'call_type', 'MOBILE', 1366, 3, '91', '91', '91', NULL),
(670, 'call_type', 'MOBILE', 1366, 3, '88', '88', '88', NULL),
(669, 'call_type', 'MOBILE', 1366, 3, '019', '019', '019', NULL),
(668, 'call_type', 'MOBILE', 1366, 3, '018', '018', '018', NULL),
(665, 'call_type', 'MOBILE', 1366, 3, '011', '011', '011', NULL),
(667, 'call_type', 'MOBILE', 1366, 3, '017', '017', '017', NULL),
(666, 'call_type', 'MOBILE', 1366, 3, '016', '016', '016', NULL),
(664, 'call_type', 'MOBILE', 1366, 3, '010', '010', '010', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_calling_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_calling_notlist` (
  `calling_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`calling_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_call_type`
--

CREATE TABLE IF NOT EXISTS `factor_call_type` (
  `call_type_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `call_type_op` int(11) DEFAULT NULL,
  `call_type` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `call_typeLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `call_typeUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `call_type_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`call_type_fid`),
  KEY `factor_call_type_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=79 ;

--
-- Dumping data for table `factor_call_type`
--

INSERT INTO `factor_call_type` (`call_type_fid`, `ruleSetName`, `ruleName`, `rule_id`, `call_type_op`, `call_type`, `call_typeLower`, `call_typeUpper`, `call_type_ref`) VALUES
(77, 'aios_price_decision', 'AIOS_SMS', 1380, 0, 'MOBILE', 'MOBILE', 'MOBILE', NULL),
(78, 'aios_price_decision', 'AIOS_EVENT', 1381, 0, 'IPTV', 'IPTV', 'IPTV', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_call_type_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_call_type_notlist` (
  `call_type_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`call_type_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_id`
--

CREATE TABLE IF NOT EXISTS `factor_counter_id` (
  `counter_id_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `counter_id_op` int(11) DEFAULT NULL,
  `counter_id` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_idLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_idUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_id_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`counter_id_fid`),
  KEY `factor_counter_id_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=144 ;

--
-- Dumping data for table `factor_counter_id`
--

INSERT INTO `factor_counter_id` (`counter_id_fid`, `ruleSetName`, `ruleName`, `rule_id`, `counter_id_op`, `counter_id`, `counter_idLower`, `counter_idUpper`, `counter_id_ref`) VALUES
(140, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1373, 0, '3', '3', '3', NULL),
(141, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1374, 0, '2', '2', '2', NULL),
(142, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1375, 0, '3', '3', '3', NULL),
(143, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1376, 0, '2', '2', '2', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_id_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_counter_id_notlist` (
  `counter_id_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`counter_id_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_name`
--

CREATE TABLE IF NOT EXISTS `factor_counter_name` (
  `counter_name_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `counter_name_op` int(11) DEFAULT NULL,
  `counter_name` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_nameLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_nameUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_name_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`counter_name_fid`),
  KEY `factor_counter_name_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=266 ;

--
-- Dumping data for table `factor_counter_name`
--

INSERT INTO `factor_counter_name` (`counter_name_fid`, `ruleSetName`, `ruleName`, `rule_id`, `counter_name_op`, `counter_name`, `counter_nameLower`, `counter_nameUpper`, `counter_name_ref`) VALUES
(265, 'aios_charging_account', 'Remains', 1357, 0, 'Remains', 'Remains', 'Remains', NULL),
(264, 'aios_charging_account', 'LastRemains', 1356, 0, 'LastRemains', 'LastRemains', 'LastRemains', NULL),
(263, 'aios_charging_account', 'LastRemains', 1355, 0, 'LastRemains', 'LastRemains', 'LastRemains', NULL),
(262, 'aios_charging_account', 'Remains', 1354, 0, 'Remains', 'Remains', 'Remains', NULL),
(261, 'aios_charging_account', 'FreePacket', 1353, 0, 'FreePacket', 'FreePacket', 'FreePacket', NULL),
(259, 'aios_charging_account', 'FreeVoice', 1351, 0, 'FreeVoice', 'FreeVoice', 'FreeVoice', NULL),
(260, 'aios_charging_account', 'FreeSms', 1352, 0, 'FreeSms', 'FreeSms', 'FreeSms', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_name_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_counter_name_notlist` (
  `counter_name_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`counter_name_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_type`
--

CREATE TABLE IF NOT EXISTS `factor_counter_type` (
  `counter_type_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `counter_type_op` int(11) DEFAULT NULL,
  `counter_type` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_typeLower` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_typeUpper` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `counter_type_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`counter_type_fid`),
  KEY `factor_counter_type_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=266 ;

--
-- Dumping data for table `factor_counter_type`
--

INSERT INTO `factor_counter_type` (`counter_type_fid`, `ruleSetName`, `ruleName`, `rule_id`, `counter_type_op`, `counter_type`, `counter_typeLower`, `counter_typeUpper`, `counter_type_ref`) VALUES
(265, 'aios_charging_account', 'Remains', 1357, 0, 'MONEY', 'MONEY', 'MONEY', NULL),
(264, 'aios_charging_account', 'LastRemains', 1356, 0, 'MONEY', 'MONEY', 'MONEY', NULL),
(263, 'aios_charging_account', 'LastRemains', 1355, 0, 'MONEY', 'MONEY', 'MONEY', NULL),
(262, 'aios_charging_account', 'Remains', 1354, 0, 'MONEY', 'MONEY', 'MONEY', NULL),
(261, 'aios_charging_account', 'FreePacket', 1353, 0, 'BYTE', 'BYTE', 'BYTE', NULL),
(260, 'aios_charging_account', 'FreeSms', 1352, 0, 'UNIT', 'UNIT', 'UNIT', NULL),
(259, 'aios_charging_account', 'FreeVoice', 1351, 0, 'TIME', 'TIME', 'TIME', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_counter_type_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_counter_type_notlist` (
  `counter_type_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(6) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`counter_type_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_data_load_type`
--

CREATE TABLE IF NOT EXISTS `factor_data_load_type` (
  `data_load_type_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `data_load_type_op` int(11) DEFAULT NULL,
  `data_load_type` int(11) DEFAULT NULL,
  `data_load_typeLower` int(11) DEFAULT NULL,
  `data_load_typeUpper` int(11) DEFAULT NULL,
  `data_load_type_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`data_load_type_fid`),
  KEY `factor_data_load_type_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=121 ;

--
-- Dumping data for table `factor_data_load_type`
--

INSERT INTO `factor_data_load_type` (`data_load_type_fid`, `ruleSetName`, `ruleName`, `rule_id`, `data_load_type_op`, `data_load_type`, `data_load_typeLower`, `data_load_typeUpper`, `data_load_type_ref`) VALUES
(120, 'discount_rules', 'DataLoadFare_50', 1362, 0, 2, 2, 2, NULL),
(118, 'discount_rules', 'DataLoadFare_100', 1360, 0, 0, 0, 0, NULL),
(119, 'discount_rules', 'DataLoadFare_200', 1361, 0, 1, 1, 1, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_data_load_type_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_data_load_type_notlist` (
  `data_load_type_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`data_load_type_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_db_action`
--

CREATE TABLE IF NOT EXISTS `factor_db_action` (
  `db_action_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `db_action_op` int(11) DEFAULT NULL,
  `db_action` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `db_actionLower` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `db_actionUpper` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `db_action_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`db_action_fid`),
  KEY `factor_db_action_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=25 ;

-- --------------------------------------------------------

--
-- Table structure for table `factor_db_action_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_db_action_notlist` (
  `db_action_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(128) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`db_action_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_discount_rate`
--

CREATE TABLE IF NOT EXISTS `factor_discount_rate` (
  `discount_rate_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `discount_rate_op` int(11) DEFAULT NULL,
  `discount_rate` int(11) DEFAULT NULL,
  `discount_rateLower` int(11) DEFAULT NULL,
  `discount_rateUpper` int(11) DEFAULT NULL,
  `discount_rate_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`discount_rate_fid`),
  KEY `factor_discount_rate_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=292 ;

--
-- Dumping data for table `factor_discount_rate`
--

INSERT INTO `factor_discount_rate` (`discount_rate_fid`, `ruleSetName`, `ruleName`, `rule_id`, `discount_rate_op`, `discount_rate`, `discount_rateLower`, `discount_rateUpper`, `discount_rate_ref`) VALUES
(290, 'vpn_discount_rate', 'VPN_1085_working', 1382, 0, 50, 50, 50, NULL),
(291, 'vpn_discount_rate', 'VPN_1085_night', 1383, 0, 30, 30, 30, NULL),
(289, 'discount_rules', 'DataLoadFare_50', 1362, 0, 50, 50, 50, NULL),
(288, 'discount_rules', 'DataLoadFare_200', 1361, 0, -100, -100, -100, NULL),
(287, 'discount_rules', 'DataLoadFare_100', 1360, 0, 0, 0, 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_discount_rate_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_discount_rate_notlist` (
  `discount_rate_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`discount_rate_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_event_name`
--

CREATE TABLE IF NOT EXISTS `factor_event_name` (
  `event_name_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `event_name_op` int(11) DEFAULT NULL,
  `event_name` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `event_nameLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `event_nameUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `event_name_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`event_name_fid`),
  KEY `factor_event_name_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=49 ;

--
-- Dumping data for table `factor_event_name`
--

INSERT INTO `factor_event_name` (`event_name_fid`, `ruleSetName`, `ruleName`, `rule_id`, `event_name_op`, `event_name`, `event_nameLower`, `event_nameUpper`, `event_name_ref`) VALUES
(48, 'event_actions', '7', 1369, 0, 'OCS_FIRST_CALL', 'OCS_FIRST_CALL', 'OCS_FIRST_CALL', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_event_name_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_event_name_notlist` (
  `event_name_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`event_name_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_fullday`
--

CREATE TABLE IF NOT EXISTS `factor_fullday` (
  `fullday_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `fullday_op` int(11) DEFAULT NULL,
  `fullday` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `fulldayLower` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `fulldayUpper` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `fullday_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`fullday_fid`),
  KEY `factor_fullday_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=76 ;

--
-- Dumping data for table `factor_fullday`
--

INSERT INTO `factor_fullday` (`fullday_fid`, `ruleSetName`, `ruleName`, `rule_id`, `fullday_op`, `fullday`, `fulldayLower`, `fulldayUpper`, `fullday_ref`) VALUES
(75, 'activation_bonus_condition', 'May_Promotion_for_Y_Product', 1359, 1, '20120501', '20120501', '20120531', NULL),
(74, 'activation_bonus_condition', 'May_Promotion_for_N_Product', 1358, 1, '20120501', '20120501', '20120531', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_fullday_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_fullday_notlist` (
  `fullday_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(10) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`fullday_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_is_vpn`
--

CREATE TABLE IF NOT EXISTS `factor_is_vpn` (
  `is_vpn_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `is_vpn_op` int(11) DEFAULT NULL,
  `is_vpn` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `is_vpnLower` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `is_vpnUpper` varchar(6) COLLATE latin1_general_ci DEFAULT NULL,
  `is_vpn_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`is_vpn_fid`),
  KEY `factor_is_vpn_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=33 ;

--
-- Dumping data for table `factor_is_vpn`
--

INSERT INTO `factor_is_vpn` (`is_vpn_fid`, `ruleSetName`, `ruleName`, `rule_id`, `is_vpn_op`, `is_vpn`, `is_vpnLower`, `is_vpnUpper`, `is_vpn_ref`) VALUES
(32, 'pps_actions', '1', 1378, 0, 'true', 'true', 'true', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_is_vpn_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_is_vpn_notlist` (
  `is_vpn_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(6) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`is_vpn_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_priority`
--

CREATE TABLE IF NOT EXISTS `factor_priority` (
  `priority_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `priority_op` int(11) DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `priorityLower` int(11) DEFAULT NULL,
  `priorityUpper` int(11) DEFAULT NULL,
  `priority_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`priority_fid`),
  KEY `factor_priority_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=428 ;

--
-- Dumping data for table `factor_priority`
--

INSERT INTO `factor_priority` (`priority_fid`, `ruleSetName`, `ruleName`, `rule_id`, `priority_op`, `priority`, `priorityLower`, `priorityUpper`, `priority_ref`) VALUES
(426, 'pps_actions', '1', 1378, 0, 10, 10, 10, NULL),
(427, 'pps_actions', '1', 1379, 0, 11, 11, 11, NULL),
(417, 'aios_charging_account', 'FreeVoice', 1351, 0, 1, 1, 1, NULL),
(418, 'aios_charging_account', 'FreeSms', 1352, 0, 1, 1, 1, NULL),
(419, 'aios_charging_account', 'FreePacket', 1353, 0, 1, 1, 1, NULL),
(420, 'aios_charging_account', 'Remains', 1354, 0, 90, 90, 90, NULL),
(421, 'aios_charging_account', 'LastRemains', 1355, 0, 91, 91, 91, NULL),
(422, 'aios_charging_account', 'LastRemains', 1356, 0, 91, 91, 91, NULL),
(423, 'aios_charging_account', 'Remains', 1357, 0, 92, 92, 92, NULL),
(424, 'event_actions', '7', 1369, 0, 10, 10, 10, NULL),
(425, 'pps_actions', '1', 1377, 0, 10, 10, 10, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_priority_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_priority_notlist` (
  `priority_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`priority_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_product`
--

CREATE TABLE IF NOT EXISTS `factor_product` (
  `product_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `product_op` int(11) DEFAULT NULL,
  `product` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `productLower` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `productUpper` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `product_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`product_fid`),
  KEY `factor_product_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=69 ;

--
-- Dumping data for table `factor_product`
--

INSERT INTO `factor_product` (`product_fid`, `ruleSetName`, `ruleName`, `rule_id`, `product_op`, `product`, `productLower`, `productUpper`, `product_ref`) VALUES
(67, 'activation_bonus_condition', 'May_Promotion_for_N_Product', 1358, 0, 'N', 'N', 'N', NULL),
(68, 'activation_bonus_condition', 'May_Promotion_for_Y_Product', 1359, 0, 'Y', 'Y', 'Y', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_product_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_product_notlist` (
  `product_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(4) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`product_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_category`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_category` (
  `promotion_category_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `promotion_category_op` int(11) DEFAULT NULL,
  `promotion_category` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_categoryLower` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_categoryUpper` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_category_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`promotion_category_fid`),
  KEY `factor_promotion_category_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_category_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_category_notlist` (
  `promotion_category_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(30) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`promotion_category_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_parameter`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_parameter` (
  `promotion_parameter_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `promotion_parameter_op` int(11) DEFAULT NULL,
  `promotion_parameter` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_parameterLower` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_parameterUpper` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_parameter_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`promotion_parameter_fid`),
  KEY `factor_promotion_parameter_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=163 ;

--
-- Dumping data for table `factor_promotion_parameter`
--

INSERT INTO `factor_promotion_parameter` (`promotion_parameter_fid`, `ruleSetName`, `ruleName`, `rule_id`, `promotion_parameter_op`, `promotion_parameter`, `promotion_parameterLower`, `promotion_parameterUpper`, `promotion_parameter_ref`) VALUES
(161, 'pps_actions', '1', 1378, 0, 't_discount_condition=vpn_discount_condition&t_discount_rate=vpn_discount_rate', 't_discount_condition=vpn_discount_condition&t_discount_rate=vpn_discount_rate', 't_discount_condition=vpn_discount_condition&t_discount_rate=vpn_discount_rate', NULL),
(162, 'pps_actions', '1', 1379, 0, 't_charging_account=aios_charging_account', 't_charging_account=aios_charging_account', 't_charging_account=aios_charging_account', NULL),
(159, 'event_actions', '7', 1369, 0, 't_bonus_condition=activation_bonus_condition&t_bonus_amount=activation_bonus_amount', 't_bonus_condition=activation_bonus_condition&t_bonus_amount=activation_bonus_amount', 't_bonus_condition=activation_bonus_condition&t_bonus_amount=activation_bonus_amount', NULL),
(160, 'pps_actions', '1', 1377, 0, 't_discount_rule=lunch_discount', 't_discount_rule=lunch_discount', 't_discount_rule=lunch_discount', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_parameter_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_parameter_notlist` (
  `promotion_parameter_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(256) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`promotion_parameter_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_service_id`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_service_id` (
  `promotion_service_id_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `promotion_service_id_op` int(11) DEFAULT NULL,
  `promotion_service_id` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_service_idLower` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_service_idUpper` varchar(30) COLLATE latin1_general_ci DEFAULT NULL,
  `promotion_service_id_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`promotion_service_id_fid`),
  KEY `factor_promotion_service_id_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=163 ;

--
-- Dumping data for table `factor_promotion_service_id`
--

INSERT INTO `factor_promotion_service_id` (`promotion_service_id_fid`, `ruleSetName`, `ruleName`, `rule_id`, `promotion_service_id_op`, `promotion_service_id`, `promotion_service_idLower`, `promotion_service_idUpper`, `promotion_service_id_ref`) VALUES
(160, 'pps_actions', '1', 1377, 0, 'simple_discount', 'simple_discount', 'simple_discount', NULL),
(161, 'pps_actions', '1', 1378, 0, 'simple_discount', 'simple_discount', 'simple_discount', NULL),
(162, 'pps_actions', '1', 1379, 0, 'simple_accounting', 'simple_accounting', 'simple_accounting', NULL),
(159, 'event_actions', '7', 1369, 0, 'giving_bonus', 'giving_bonus', 'giving_bonus', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_promotion_service_id_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_promotion_service_id_notlist` (
  `promotion_service_id_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(30) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`promotion_service_id_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_service`
--

CREATE TABLE IF NOT EXISTS `factor_service` (
  `service_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `service_op` int(11) DEFAULT NULL,
  `service` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `serviceLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `serviceUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `service_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_fid`),
  KEY `factor_service_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=584 ;

--
-- Dumping data for table `factor_service`
--

INSERT INTO `factor_service` (`service_fid`, `ruleSetName`, `ruleName`, `rule_id`, `service_op`, `service`, `serviceLower`, `serviceUpper`, `service_ref`) VALUES
(583, 'aios_price_decision', 'AIOS_EVENT', 1381, 0, 'OCS', 'OCS', 'OCS', NULL),
(582, 'aios_price_decision', 'AIOS_SMS', 1380, 0, 'OCS', 'OCS', 'OCS', NULL),
(581, 'aios_tariff_decision', 'AIOS_PACKET', 1365, 0, 'OCS', 'OCS', 'OCS', NULL),
(576, 'discount_rules', 'DataLoadFare_100', 1360, 0, 'OCS', 'OCS', 'OCS', NULL),
(577, 'discount_rules', 'DataLoadFare_200', 1361, 0, 'OCS', 'OCS', 'OCS', NULL),
(578, 'discount_rules', 'DataLoadFare_50', 1362, 0, 'OCS', 'OCS', 'OCS', NULL),
(579, 'aios_tariff_decision', 'AIOS_VOICE', 1363, 0, 'OCS', 'OCS', 'OCS', NULL),
(580, 'aios_tariff_decision', 'AIOS_VOICE', 1364, 0, 'MOBILE', 'MOBILE', 'MOBILE', NULL),
(575, 'aios_charging_account', 'Remains', 1357, 0, 'MOBILE', 'MOBILE', 'MOBILE', NULL),
(574, 'aios_charging_account', 'LastRemains', 1356, 0, 'MOBILE', 'MOBILE', 'MOBILE', NULL),
(569, 'aios_charging_account', 'FreeVoice', 1351, 0, 'OCS', 'OCS', 'OCS', NULL),
(570, 'aios_charging_account', 'FreeSms', 1352, 0, 'OCS', 'OCS', 'OCS', NULL),
(571, 'aios_charging_account', 'FreePacket', 1353, 0, 'OCS', 'OCS', 'OCS', NULL),
(572, 'aios_charging_account', 'Remains', 1354, 0, 'OCS', 'OCS', 'OCS', NULL),
(573, 'aios_charging_account', 'LastRemains', 1355, 0, 'OCS', 'OCS', 'OCS', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_service_id`
--

CREATE TABLE IF NOT EXISTS `factor_service_id` (
  `service_id_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `service_id_op` int(11) DEFAULT NULL,
  `service_id` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `service_idLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `service_idUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `service_id_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id_fid`),
  KEY `factor_service_id_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=602 ;

--
-- Dumping data for table `factor_service_id`
--

INSERT INTO `factor_service_id` (`service_id_fid`, `ruleSetName`, `ruleName`, `rule_id`, `service_id_op`, `service_id`, `service_idLower`, `service_idUpper`, `service_id_ref`) VALUES
(601, 'aios_price_decision', 'AIOS_EVENT', 1381, 0, 'IPTV_EVENT', 'IPTV_EVENT', 'IPTV_EVENT', NULL),
(597, 'pps_actions', '1', 1377, 0, 'PC_VOICE', 'PC_VOICE', 'PC_VOICE', NULL),
(598, 'pps_actions', '1', 1377, 0, 'PC_SMS', 'PC_SMS', 'PC_SMS', NULL),
(599, 'pps_actions', '1', 1378, 0, 'PC_VOICE', 'PC_VOICE', 'PC_VOICE', NULL),
(600, 'aios_price_decision', 'AIOS_SMS', 1380, 0, 'PC_SMS', 'PC_SMS', 'PC_SMS', NULL),
(594, 'aios_tariff_decision', 'AIOS_VOICE', 1364, 0, 'PC_VOICE', 'PC_VOICE', 'PC_VOICE', NULL),
(595, 'aios_tariff_decision', 'AIOS_PACKET', 1365, 0, 'PC_PACKET', 'PC_PACKET', 'PC_PACKET', NULL),
(596, 'event_actions', '7', 1369, 0, 'PC_EVENT', 'PC_EVENT', 'PC_EVENT', NULL),
(593, 'aios_tariff_decision', 'AIOS_VOICE', 1363, 0, 'PC_VOICE', 'PC_VOICE', 'PC_VOICE', NULL),
(592, 'discount_rules', 'DataLoadFare_50', 1362, 0, 'PC_PACKET', 'PC_PACKET', 'PC_PACKET', NULL),
(587, 'aios_charging_account', 'FreeVoice', 1351, 0, 'PC_VOICE', 'PC_VOICE', 'PC_VOICE', NULL),
(588, 'aios_charging_account', 'FreeSms', 1352, 0, 'PC_SMS', 'PC_SMS', 'PC_SMS', NULL),
(589, 'aios_charging_account', 'FreePacket', 1353, 0, 'PC_PACKET', 'PC_PACKET', 'PC_PACKET', NULL),
(590, 'discount_rules', 'DataLoadFare_100', 1360, 0, 'PC_PACKET', 'PC_PACKET', 'PC_PACKET', NULL),
(591, 'discount_rules', 'DataLoadFare_200', 1361, 0, 'PC_PACKET', 'PC_PACKET', 'PC_PACKET', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_service_id_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_service_id_notlist` (
  `service_id_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`service_id_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_service_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_service_notlist` (
  `service_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`service_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_targetRule`
--

CREATE TABLE IF NOT EXISTS `factor_targetRule` (
  `targetRule_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `targetRule_op` int(11) DEFAULT NULL,
  `targetRule` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `targetRuleLower` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `targetRuleUpper` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `targetRule_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`targetRule_fid`),
  KEY `factor_targetRule_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=220 ;

--
-- Dumping data for table `factor_targetRule`
--

INSERT INTO `factor_targetRule` (`targetRule_fid`, `ruleSetName`, `ruleName`, `rule_id`, `targetRule_op`, `targetRule`, `targetRuleLower`, `targetRuleUpper`, `targetRule_ref`) VALUES
(214, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1373, 0, 'May_Promotion_for_N_Product', 'May_Promotion_for_N_Product', 'May_Promotion_for_N_Product', NULL),
(215, 'activation_bonus_amount', 'May_Promotion_for_N_Product', 1374, 0, 'May_Promotion_for_N_Product', 'May_Promotion_for_N_Product', 'May_Promotion_for_N_Product', NULL),
(216, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1375, 0, 'May_Promotion_for_Y_Product', 'May_Promotion_for_Y_Product', 'May_Promotion_for_Y_Product', NULL),
(217, 'activation_bonus_amount', 'May_Promotion_for_Y_Product', 1376, 0, 'May_Promotion_for_Y_Product', 'May_Promotion_for_Y_Product', 'May_Promotion_for_Y_Product', NULL),
(218, 'vpn_discount_rate', 'VPN_1085_working', 1382, 0, 'VPN_1085_working', 'VPN_1085_working', 'VPN_1085_working', NULL),
(219, 'vpn_discount_rate', 'VPN_1085_night', 1383, 0, 'VPN_1085_night', 'VPN_1085_night', 'VPN_1085_night', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_targetRule_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_targetRule_notlist` (
  `targetRule_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`targetRule_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_time`
--

CREATE TABLE IF NOT EXISTS `factor_time` (
  `time_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `time_op` int(11) DEFAULT NULL,
  `time` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `timeLower` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `timeUpper` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `time_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`time_fid`),
  KEY `factor_time_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=178 ;

--
-- Dumping data for table `factor_time`
--

INSERT INTO `factor_time` (`time_fid`, `ruleSetName`, `ruleName`, `rule_id`, `time_op`, `time`, `timeLower`, `timeUpper`, `time_ref`) VALUES
(177, 'vpn_discount_condition', 'VPN_1085_night', 1372, 1, '1800', '1800', '2400', NULL),
(176, 'vpn_discount_condition', 'VPN_1085_working', 1371, 1, '0000', '0000', '1800', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_time_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_time_notlist` (
  `time_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(4) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`time_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_TotalUsedMoney`
--

CREATE TABLE IF NOT EXISTS `factor_TotalUsedMoney` (
  `TotalUsedMoney_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `TotalUsedMoney_op` int(11) DEFAULT NULL,
  `TotalUsedMoney` int(11) DEFAULT NULL,
  `TotalUsedMoneyLower` int(11) DEFAULT NULL,
  `TotalUsedMoneyUpper` int(11) DEFAULT NULL,
  `TotalUsedMoney_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`TotalUsedMoney_fid`),
  KEY `factor_TotalUsedMoney_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=15 ;

-- --------------------------------------------------------

--
-- Table structure for table `factor_TotalUsedMoney_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_TotalUsedMoney_notlist` (
  `TotalUsedMoney_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`TotalUsedMoney_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_discount_rate`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_discount_rate` (
  `vpn_discount_rate_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `vpn_discount_rate_op` int(11) DEFAULT NULL,
  `vpn_discount_rate` int(11) DEFAULT NULL,
  `vpn_discount_rateLower` int(11) DEFAULT NULL,
  `vpn_discount_rateUpper` int(11) DEFAULT NULL,
  `vpn_discount_rate_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`vpn_discount_rate_fid`),
  KEY `factor_vpn_discount_rate_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_discount_rate_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_discount_rate_notlist` (
  `vpn_discount_rate_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`vpn_discount_rate_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_group_id`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_group_id` (
  `vpn_group_id_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `vpn_group_id_op` int(11) DEFAULT NULL,
  `vpn_group_id` int(11) DEFAULT NULL,
  `vpn_group_idLower` int(11) DEFAULT NULL,
  `vpn_group_idUpper` int(11) DEFAULT NULL,
  `vpn_group_id_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`vpn_group_id_fid`),
  KEY `factor_vpn_group_id_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=143 ;

--
-- Dumping data for table `factor_vpn_group_id`
--

INSERT INTO `factor_vpn_group_id` (`vpn_group_id_fid`, `ruleSetName`, `ruleName`, `rule_id`, `vpn_group_id_op`, `vpn_group_id`, `vpn_group_idLower`, `vpn_group_idUpper`, `vpn_group_id_ref`) VALUES
(141, 'vpn_discount_condition', 'VPN_1085_working', 1371, 0, 1085, 1085, 1085, NULL),
(142, 'vpn_discount_condition', 'VPN_1085_night', 1372, 0, 1085, 1085, 1085, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_group_id_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_group_id_notlist` (
  `vpn_group_id_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`vpn_group_id_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_grou_id`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_grou_id` (
  `vpn_grou_id_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `vpn_grou_id_op` int(11) DEFAULT NULL,
  `vpn_grou_id` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `vpn_grou_idLower` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `vpn_grou_idUpper` varchar(10) COLLATE latin1_general_ci DEFAULT NULL,
  `vpn_grou_id_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`vpn_grou_id_fid`),
  KEY `factor_vpn_grou_id_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `factor_vpn_grou_id_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_vpn_grou_id_notlist` (
  `vpn_grou_id_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(10) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`vpn_grou_id_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `factor_week`
--

CREATE TABLE IF NOT EXISTS `factor_week` (
  `week_fid` int(11) NOT NULL AUTO_INCREMENT,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `week_op` int(11) DEFAULT NULL,
  `week` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `weekLower` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `weekUpper` varchar(4) COLLATE latin1_general_ci DEFAULT NULL,
  `week_ref` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`week_fid`),
  KEY `factor_week_facotr_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=531 ;

--
-- Dumping data for table `factor_week`
--

INSERT INTO `factor_week` (`week_fid`, `ruleSetName`, `ruleName`, `rule_id`, `week_op`, `week`, `weekLower`, `weekUpper`, `week_ref`) VALUES
(530, 'vpn_discount_condition', 'VPN_1085_night', 1372, 0, 'fri', 'fri', 'fri', NULL),
(529, 'vpn_discount_condition', 'VPN_1085_night', 1372, 0, 'thu', 'thu', 'thu', NULL),
(528, 'vpn_discount_condition', 'VPN_1085_working', 1371, 0, 'fri', 'fri', 'fri', NULL),
(527, 'vpn_discount_condition', 'VPN_1085_working', 1371, 0, 'thu', 'thu', 'thu', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `factor_week_notlist`
--

CREATE TABLE IF NOT EXISTS `factor_week_notlist` (
  `week_fid` int(11) NOT NULL,
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL,
  `value` varchar(4) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`week_fid`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Stand-in structure for view `holiday`
--
CREATE TABLE IF NOT EXISTS `holiday` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`week_fid` int(11)
,`week_op` int(11)
,`week` varchar(4)
,`weekLower` varchar(4)
,`weekUpper` varchar(4)
,`week_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `lunch_discount`
--
CREATE TABLE IF NOT EXISTS `lunch_discount` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`time_fid` int(11)
,`time_op` int(11)
,`time` varchar(4)
,`timeLower` varchar(4)
,`timeUpper` varchar(4)
,`time_ref` varchar(32)
,`discount_rate_fid` int(11)
,`discount_rate_op` int(11)
,`discount_rate` int(11)
,`discount_rateLower` int(11)
,`discount_rateUpper` int(11)
,`discount_rate_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Table structure for table `ocs_account`
--

CREATE TABLE IF NOT EXISTS `ocs_account` (
  `account_key` varchar(24) NOT NULL,
  `customer_id` varchar(11) NOT NULL,
  `subscription_key` varchar(24) NOT NULL,
  `status` int(11) NOT NULL COMMENT 'active or deactive\nUnitel?? ??? 2?? ????? ??? ?? ?? ????? ????? ?Î¾???? ????? ??? ????? ?? ????\nCS?? USSD, Feature Code?? ?????? ?? ????',
  `product_id` int(11) NOT NULL,
  PRIMARY KEY (`account_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_account`
--

INSERT INTO `ocs_account` (`account_key`, `customer_id`, `subscription_key`, `status`, `product_id`) VALUES
('91100000', '9000027765', '91100000', 1, 5),
('91100001', '8000067086', '91100001', 0, 1),
('91100011', '9000022260', '91100011', 0, 1),
('91100022', '9000010574', '91100022', 0, 5),
('91100033', '8000067086', '91100033', 0, 5),
('91100044', '9000022260', '91100044', 0, 3),
('91100055', '8000067086', '91100055', 1, 3),
('91100066', '9000026424', '91100066', 0, 5);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_account_key`
--

CREATE TABLE IF NOT EXISTS `ocs_account_key` (
  `account_key` varchar(30) NOT NULL,
  `account_key_type` varchar(10) NOT NULL,
  `status` varchar(10) NOT NULL,
  `sales_flag` varchar(1) DEFAULT '0',
  PRIMARY KEY (`account_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_account_key`
--

INSERT INTO `ocs_account_key` (`account_key`, `account_key_type`, `status`, `sales_flag`) VALUES
('91100000', 'MTYPE_GOLD', '02', '1'),
('91100001', 'VTYPE_MOBI', '05', '0'),
('91100002', 'VTYPE_MOBI', '05', '0'),
('91100003', 'VTYPE_MOBI', '05', '0'),
('91100004', 'VTYPE_MOBI', '05', '0'),
('91100005', 'VTYPE_MOBI', '05', '0'),
('91100006', 'VTYPE_MOBI', '05', '0'),
('91100007', 'VTYPE_MOBI', '05', '0'),
('91100008', 'VTYPE_MOBI', '05', '0'),
('91100009', 'VTYPE_MOBI', '05', '0'),
('91100010', 'VTYPE_MOBI', '01', '0'),
('91100011', 'MTYPE_BRON', '03', '1'),
('91100012', 'VTYPE_MOBI', '01', '0'),
('91100013', 'VTYPE_MOBI', '01', '0'),
('91100014', 'VTYPE_MOBI', '01', '0'),
('91100015', 'VTYPE_MOBI', '01', '0'),
('91100016', 'VTYPE_MOBI', '01', '0'),
('91100017', 'VTYPE_MOBI', '01', '0'),
('91100018', 'VTYPE_MOBI', '01', '0'),
('91100019', 'VTYPE_MOBI', '01', '0'),
('91100021', 'VTYPE_MOBI', '01', '0'),
('91100022', 'MTYPE_BRON', '03', '1'),
('91100023', 'VTYPE_MOBI', '01', '0'),
('91100024', 'VTYPE_MOBI', '01', '0'),
('91100025', 'VTYPE_MOBI', '01', '0'),
('91100026', 'VTYPE_MOBI', '01', '0'),
('91100027', 'VTYPE_MOBI', '01', '0'),
('91100028', 'VTYPE_MOBI', '01', '0'),
('91100029', 'VTYPE_MOBI', '01', '0'),
('91100030', 'VTYPE_MOBI', '01', '0'),
('91100031', 'VTYPE_MOBI', '01', '0'),
('91100032', 'VTYPE_MOBI', '01', '0'),
('91100033', 'MTYPE_BRON', '03', '1'),
('91100034', 'VTYPE_MOBI', '01', '0'),
('91100035', 'VTYPE_MOBI', '01', '0'),
('91100036', 'VTYPE_MOBI', '01', '0'),
('91100037', 'VTYPE_MOBI', '01', '0'),
('91100038', 'VTYPE_MOBI', '01', '0'),
('91100039', 'VTYPE_MOBI', '01', '0'),
('91100040', 'VTYPE_MOBI', '01', '0'),
('91100041', 'VTYPE_MOBI', '01', '0'),
('91100042', 'VTYPE_MOBI', '01', '0'),
('91100043', 'VTYPE_MOBI', '01', '0'),
('91100044', 'MTYPE_BRON', '03', '1'),
('91100045', 'VTYPE_MOBI', '01', '0'),
('91100046', 'VTYPE_MOBI', '01', '0'),
('91100047', 'VTYPE_MOBI', '01', '0'),
('91100048', 'VTYPE_MOBI', '01', '0'),
('91100049', 'VTYPE_MOBI', '01', '0'),
('91100050', 'VTYPE_MOBI', '01', '0'),
('91100051', 'VTYPE_MOBI', '01', '0'),
('91100052', 'VTYPE_MOBI', '01', '0'),
('91100053', 'VTYPE_MOBI', '01', '0'),
('91100054', 'VTYPE_MOBI', '01', '0'),
('91100055', 'MTYPE_BRON', '03', '1'),
('91100056', 'VTYPE_MOBI', '01', '0'),
('91100057', 'VTYPE_MOBI', '01', '0'),
('91100058', 'VTYPE_MOBI', '01', '0'),
('91100059', 'VTYPE_MOBI', '01', '0'),
('91100060', 'VTYPE_MOBI', '01', '0'),
('91100061', 'VTYPE_MOBI', '01', '0'),
('91100062', 'VTYPE_MOBI', '01', '0'),
('91100063', 'VTYPE_MOBI', '01', '0'),
('91100064', 'VTYPE_MOBI', '01', '0'),
('91100065', 'VTYPE_MOBI', '01', '0'),
('91100066', 'MTYPE_BRON', '03', '1'),
('91100067', 'VTYPE_MOBI', '01', '0'),
('91100068', 'VTYPE_MOBI', '01', '0'),
('91100069', 'VTYPE_MOBI', '01', '0'),
('91100070', 'VTYPE_MOBI', '01', '0'),
('91100071', 'VTYPE_MOBI', '01', '0'),
('91100072', 'VTYPE_MOBI', '01', '0'),
('91100073', 'VTYPE_MOBI', '01', '0'),
('91100074', 'VTYPE_MOBI', '01', '0'),
('91100075', 'VTYPE_MOBI', '01', '0'),
('91100076', 'VTYPE_MOBI', '01', '0'),
('91100077', 'MTYPE_BRON', '03', '1'),
('91100078', 'VTYPE_MOBI', '01', '0'),
('91100079', 'VTYPE_MOBI', '01', '0'),
('91100080', 'VTYPE_MOBI', '01', '0'),
('91100081', 'VTYPE_MOBI', '01', '0'),
('91100082', 'VTYPE_MOBI', '01', '0'),
('91100083', 'VTYPE_MOBI', '01', '0'),
('91100084', 'VTYPE_MOBI', '01', '0'),
('91100085', 'VTYPE_MOBI', '01', '0'),
('91100086', 'VTYPE_MOBI', '01', '0'),
('91100087', 'VTYPE_MOBI', '01', '0'),
('91100088', 'MTYPE_BRON', '03', '0'),
('91100090', 'VTYPE_MOBI', '01', '0'),
('91100092', 'VTYPE_MOBI', '01', '0'),
('91100094', 'VTYPE_MOBI', '01', '0'),
('91100095', 'VTYPE_MOBI', '01', '0'),
('91100096', 'VTYPE_MOBI', '01', '0'),
('91100097', 'VTYPE_MOBI', '01', '0'),
('91100098', 'VTYPE_MOBI', '01', '0'),
('91100099', 'MTYPE_BRON', '03', '0'),
('91100100', 'VTYPE_MOBI', '01', '0'),
('91100101', 'MTYPE_BRON', '04', '0'),
('91100102', 'VTYPE_MOBI', '01', '0'),
('91100103', 'VTYPE_MOBI', '01', '0'),
('91100104', 'VTYPE_MOBI', '01', '0'),
('91100105', 'VTYPE_MOBI', '01', '0'),
('91100106', 'VTYPE_MOBI', '01', '0'),
('91100107', 'VTYPE_MOBI', '01', '0'),
('91100108', 'VTYPE_MOBI', '01', '0'),
('91100109', 'VTYPE_MOBI', '01', '0'),
('91100110', 'VTYPE_MOBI', '01', '0'),
('91100111', 'MTYPE_SILV', '05', '0'),
('91100112', 'VTYPE_MOBI', '01', '0'),
('91100113', 'VTYPE_MOBI', '01', '0'),
('91100114', 'VTYPE_MOBI', '01', '0'),
('91100115', 'VTYPE_MOBI', '01', '0'),
('91100116', 'VTYPE_MOBI', '01', '0'),
('91100117', 'VTYPE_MOBI', '01', '0'),
('91100118', 'VTYPE_MOBI', '01', '0'),
('91100119', 'VTYPE_MOBI', '01', '0'),
('91100120', 'VTYPE_MOBI', '01', '0'),
('91100121', 'VTYPE_MOBI', '01', '0'),
('91100122', 'VTYPE_MOBI', '01', '0'),
('91100123', 'VTYPE_MOBI', '01', '0'),
('91100124', 'VTYPE_MOBI', '01', '0'),
('91100125', 'VTYPE_MOBI', '01', '0'),
('91100127', 'VTYPE_MOBI', '01', '0'),
('91100128', 'VTYPE_MOBI', '01', '0'),
('91100129', 'VTYPE_MOBI', '01', '0'),
('91100130', 'VTYPE_MOBI', '01', '0'),
('91100131', 'VTYPE_MOBI', '01', '0'),
('91100132', 'VTYPE_MOBI', '01', '0'),
('91100133', 'VTYPE_MOBI', '01', '0'),
('91100134', 'VTYPE_MOBI', '01', '0'),
('91100135', 'VTYPE_MOBI', '01', '0'),
('91100136', 'VTYPE_MOBI', '01', '0'),
('91100137', 'VTYPE_MOBI', '01', '0'),
('91100138', 'VTYPE_MOBI', '01', '0'),
('91100140', 'VTYPE_MOBI', '01', '0'),
('91100141', 'VTYPE_MOBI', '01', '0'),
('91100142', 'VTYPE_MOBI', '01', '0'),
('91100143', 'VTYPE_MOBI', '01', '0'),
('91100144', 'VTYPE_MOBI', '01', '0'),
('91100145', 'VTYPE_MOBI', '01', '0'),
('91100146', 'VTYPE_MOBI', '01', '0'),
('91100147', 'VTYPE_MOBI', '01', '0'),
('91100148', 'VTYPE_MOBI', '01', '0'),
('91100149', 'VTYPE_MOBI', '01', '0'),
('91100150', 'VTYPE_MOBI', '01', '0'),
('91100151', 'VTYPE_MOBI', '01', '0'),
('91100152', 'VTYPE_MOBI', '01', '0'),
('91100153', 'VTYPE_MOBI', '01', '0'),
('91100154', 'VTYPE_MOBI', '01', '0'),
('91100155', 'VTYPE_MOBI', '01', '0'),
('91100156', 'VTYPE_MOBI', '01', '0'),
('91100157', 'VTYPE_MOBI', '01', '0'),
('91100158', 'VTYPE_MOBI', '01', '0'),
('91100159', 'VTYPE_MOBI', '01', '0'),
('91100161', 'VTYPE_MOBI', '01', '0'),
('91100163', 'VTYPE_MOBI', '01', '0'),
('91100165', 'VTYPE_MOBI', '01', '0'),
('91100167', 'VTYPE_MOBI', '01', '0'),
('91100169', 'VTYPE_MOBI', '01', '0'),
('91100171', 'VTYPE_MOBI', '01', '0'),
('91100173', 'VTYPE_MOBI', '01', '0'),
('91100175', 'VTYPE_MOBI', '01', '0'),
('91100177', 'VTYPE_MOBI', '01', '0'),
('91100179', 'VTYPE_MOBI', '01', '0'),
('91100181', 'VTYPE_MOBI', '01', '0'),
('91100185', 'VTYPE_MOBI', '01', '0'),
('91100187', 'VTYPE_MOBI', '01', '0'),
('91100189', 'VTYPE_MOBI', '01', '0'),
('91100191', 'VTYPE_MOBI', '01', '0'),
('91100193', 'VTYPE_MOBI', '01', '0'),
('91100195', 'VTYPE_MOBI', '01', '0'),
('91100197', 'VTYPE_MOBI', '01', '0'),
('91100199', 'VTYPE_MOBI', '01', '0'),
('91100201', 'VTYPE_MOBI', '01', '0'),
('91100202', 'MTYPE_BRON', '04', '0'),
('91100204', 'VTYPE_MOBI', '01', '0'),
('91100206', 'VTYPE_MOBI', '01', '0'),
('91100208', 'VTYPE_MOBI', '01', '0'),
('91100210', 'VTYPE_MOBI', '01', '0'),
('91100212', 'VTYPE_MOBI', '01', '0'),
('91100214', 'VTYPE_MOBI', '01', '0'),
('91100216', 'VTYPE_MOBI', '01', '0'),
('91100218', 'VTYPE_MOBI', '01', '0'),
('91100220', 'VTYPE_MOBI', '01', '0'),
('91100221', 'VTYPE_MOBI', '01', '0'),
('91100222', 'MTYPE_SILV', '05', '0'),
('91100224', 'VTYPE_MOBI', '01', '0'),
('91100226', 'VTYPE_MOBI', '01', '0'),
('91100228', 'VTYPE_MOBI', '01', '0'),
('91100230', 'VTYPE_MOBI', '01', '0'),
('91100232', 'VTYPE_MOBI', '01', '0'),
('91100234', 'VTYPE_MOBI', '01', '0'),
('91100236', 'VTYPE_MOBI', '01', '0'),
('91100238', 'VTYPE_MOBI', '01', '0'),
('91100240', 'VTYPE_MOBI', '01', '0'),
('91100242', 'VTYPE_MOBI', '01', '0'),
('91100244', 'VTYPE_MOBI', '01', '0'),
('91100246', 'VTYPE_MOBI', '01', '0'),
('91100248', 'VTYPE_MOBI', '01', '0'),
('91100250', 'VTYPE_MOBI', '01', '0'),
('91100252', 'VTYPE_MOBI', '01', '0'),
('91100254', 'VTYPE_MOBI', '01', '0'),
('91100256', 'VTYPE_MOBI', '01', '0'),
('91100258', 'VTYPE_MOBI', '01', '0'),
('91100260', 'VTYPE_MOBI', '01', '0'),
('91100262', 'VTYPE_MOBI', '01', '0'),
('91100264', 'VTYPE_MOBI', '01', '0'),
('91100266', 'VTYPE_MOBI', '01', '0'),
('91100267', 'VTYPE_MOBI', '01', '0'),
('91100269', 'VTYPE_MOBI', '01', '0'),
('91100271', 'VTYPE_MOBI', '01', '0'),
('91100273', 'VTYPE_MOBI', '01', '0'),
('91100275', 'VTYPE_MOBI', '01', '0'),
('91100277', 'VTYPE_MOBI', '01', '0'),
('91100279', 'VTYPE_MOBI', '01', '0'),
('91100281', 'VTYPE_MOBI', '01', '0'),
('91100283', 'VTYPE_MOBI', '01', '0'),
('91100285', 'VTYPE_MOBI', '01', '0'),
('91100287', 'VTYPE_MOBI', '01', '0'),
('91100289', 'VTYPE_MOBI', '01', '0'),
('91100291', 'VTYPE_MOBI', '01', '0'),
('91100295', 'VTYPE_MOBI', '01', '0'),
('91100299', 'VTYPE_MOBI', '01', '0'),
('91100300', 'VTYPE_MOBI', '01', '0'),
('91100302', 'VTYPE_MOBI', '01', '0'),
('91100303', 'MTYPE_BRON', '04', '0'),
('91100305', 'VTYPE_MOBI', '01', '0'),
('91100307', 'VTYPE_MOBI', '01', '0'),
('91100309', 'VTYPE_MOBI', '01', '0'),
('91100311', 'VTYPE_MOBI', '01', '0'),
('91100313', 'VTYPE_MOBI', '01', '0'),
('91100315', 'VTYPE_MOBI', '01', '0'),
('91100317', 'VTYPE_MOBI', '01', '0'),
('91100319', 'VTYPE_MOBI', '01', '0'),
('91100321', 'VTYPE_MOBI', '01', '0'),
('91100322', 'VTYPE_MOBI', '01', '0'),
('91100323', 'VTYPE_MOBI', '01', '0'),
('91100324', 'VTYPE_MOBI', '01', '0'),
('91100325', 'VTYPE_MOBI', '01', '0'),
('91100326', 'VTYPE_MOBI', '01', '0'),
('91100327', 'VTYPE_MOBI', '01', '0'),
('91100328', 'VTYPE_MOBI', '01', '0'),
('91100329', 'VTYPE_MOBI', '01', '0'),
('91100330', 'VTYPE_MOBI', '01', '0'),
('91100331', 'VTYPE_MOBI', '01', '0'),
('91100332', 'VTYPE_MOBI', '01', '0'),
('91100333', 'MTYPE_SILV', '05', '0'),
('91100334', 'VTYPE_MOBI', '01', '0'),
('91100335', 'VTYPE_MOBI', '01', '0'),
('91100336', 'VTYPE_MOBI', '01', '0'),
('91100337', 'VTYPE_MOBI', '01', '0'),
('91100338', 'VTYPE_MOBI', '01', '0'),
('91100339', 'VTYPE_MOBI', '01', '0'),
('91100340', 'VTYPE_MOBI', '01', '0'),
('91100341', 'VTYPE_MOBI', '01', '0'),
('91100342', 'VTYPE_MOBI', '01', '0'),
('91100343', 'VTYPE_MOBI', '01', '0'),
('91100344', 'VTYPE_MOBI', '01', '0'),
('91100345', 'VTYPE_MOBI', '01', '0'),
('91100346', 'VTYPE_MOBI', '01', '0'),
('91100347', 'VTYPE_MOBI', '01', '0'),
('91100348', 'VTYPE_MOBI', '01', '0'),
('91100349', 'VTYPE_MOBI', '01', '0'),
('91100351', 'VTYPE_MOBI', '01', '0'),
('91100352', 'VTYPE_MOBI', '01', '0'),
('91100353', 'VTYPE_MOBI', '01', '0'),
('91100355', 'VTYPE_MOBI', '01', '0'),
('91100356', 'VTYPE_MOBI', '01', '0'),
('91100357', 'VTYPE_MOBI', '01', '0'),
('91100358', 'VTYPE_MOBI', '01', '0'),
('91100359', 'VTYPE_MOBI', '01', '0'),
('91100360', 'VTYPE_MOBI', '01', '0'),
('91100362', 'VTYPE_MOBI', '01', '0'),
('91100363', 'VTYPE_MOBI', '01', '0'),
('91100364', 'VTYPE_MOBI', '01', '0'),
('91100365', 'VTYPE_MOBI', '01', '0'),
('91100366', 'VTYPE_MOBI', '01', '0'),
('91100368', 'VTYPE_MOBI', '01', '0'),
('91100369', 'VTYPE_MOBI', '01', '0'),
('91100370', 'VTYPE_MOBI', '01', '0'),
('91100371', 'VTYPE_MOBI', '01', '0'),
('91100372', 'VTYPE_MOBI', '01', '0'),
('91100373', 'VTYPE_MOBI', '01', '0'),
('91100374', 'VTYPE_MOBI', '01', '0'),
('91100375', 'VTYPE_MOBI', '01', '0'),
('91100376', 'VTYPE_MOBI', '01', '0'),
('91100377', 'VTYPE_MOBI', '01', '0'),
('91100378', 'VTYPE_MOBI', '01', '0'),
('91100379', 'VTYPE_MOBI', '01', '0'),
('91100380', 'VTYPE_MOBI', '01', '0'),
('91100381', 'VTYPE_MOBI', '01', '0'),
('91100382', 'VTYPE_MOBI', '01', '0'),
('91100383', 'VTYPE_MOBI', '01', '0'),
('91100384', 'VTYPE_MOBI', '01', '0'),
('91100385', 'VTYPE_MOBI', '01', '0'),
('91100386', 'VTYPE_MOBI', '01', '0'),
('91100387', 'VTYPE_MOBI', '01', '0'),
('91100388', 'VTYPE_MOBI', '01', '0'),
('91100389', 'VTYPE_MOBI', '01', '0'),
('91100390', 'VTYPE_MOBI', '01', '0'),
('91100391', 'VTYPE_MOBI', '01', '0'),
('91100392', 'VTYPE_MOBI', '01', '0'),
('91100393', 'VTYPE_MOBI', '01', '0'),
('91100394', 'VTYPE_MOBI', '01', '0'),
('91100395', 'VTYPE_MOBI', '01', '0'),
('91100396', 'VTYPE_MOBI', '01', '0'),
('91100397', 'VTYPE_MOBI', '01', '0'),
('91100398', 'VTYPE_MOBI', '01', '0'),
('91100399', 'VTYPE_MOBI', '01', '0'),
('91100400', 'VTYPE_MOBI', '01', '0'),
('91100401', 'VTYPE_MOBI', '01', '0'),
('91100402', 'VTYPE_MOBI', '01', '0'),
('91100403', 'VTYPE_MOBI', '01', '0'),
('91100404', 'MTYPE_BRON', '04', '0'),
('91100405', 'VTYPE_MOBI', '01', '0'),
('91100406', 'VTYPE_MOBI', '01', '0'),
('91100407', 'VTYPE_MOBI', '01', '0'),
('91100408', 'VTYPE_MOBI', '01', '0'),
('91100409', 'VTYPE_MOBI', '01', '0'),
('91100410', 'VTYPE_MOBI', '01', '0'),
('91100411', 'VTYPE_MOBI', '01', '0'),
('91100412', 'VTYPE_MOBI', '01', '0'),
('91100413', 'VTYPE_MOBI', '01', '0'),
('91100414', 'VTYPE_MOBI', '01', '0'),
('91100415', 'VTYPE_MOBI', '01', '0'),
('91100416', 'VTYPE_MOBI', '01', '0'),
('91100417', 'VTYPE_MOBI', '01', '0'),
('91100418', 'VTYPE_MOBI', '01', '0'),
('91100419', 'VTYPE_MOBI', '01', '0'),
('91100420', 'VTYPE_MOBI', '01', '0'),
('91100421', 'VTYPE_MOBI', '01', '0'),
('91100422', 'VTYPE_MOBI', '01', '0'),
('91100423', 'VTYPE_MOBI', '01', '0'),
('91100424', 'VTYPE_MOBI', '01', '0'),
('91100425', 'VTYPE_MOBI', '01', '0'),
('91100426', 'VTYPE_MOBI', '01', '0'),
('91100427', 'VTYPE_MOBI', '01', '0'),
('91100428', 'VTYPE_MOBI', '01', '0'),
('91100429', 'VTYPE_MOBI', '01', '0'),
('91100430', 'VTYPE_MOBI', '01', '0'),
('91100431', 'VTYPE_MOBI', '01', '0'),
('91100432', 'VTYPE_MOBI', '01', '0'),
('91100433', 'VTYPE_MOBI', '01', '0'),
('91100435', 'VTYPE_MOBI', '01', '0'),
('91100436', 'VTYPE_MOBI', '01', '0'),
('91100437', 'VTYPE_MOBI', '01', '0'),
('91100438', 'VTYPE_MOBI', '01', '0'),
('91100439', 'VTYPE_MOBI', '01', '0'),
('91100440', 'VTYPE_MOBI', '01', '0'),
('91100441', 'VTYPE_MOBI', '01', '0'),
('91100534', 'VTYPE_MOBI', '01', '0'),
('91100553', 'VTYPE_MOBI', '01', '0'),
('91100555', 'MTYPE_SILV', '05', '0'),
('91100657', 'VTYPE_MOBI', '01', '0'),
('91100737', 'VTYPE_MOBI', '01', '0'),
('91100738', 'VTYPE_MOBI', '01', '0'),
('91100751', 'VTYPE_MOBI', '01', '0'),
('91100780', 'VTYPE_MOBI', '01', '0'),
('91101000', 'VTYPE_MOBI', '01', '0'),
('91101034', 'VTYPE_MOBI', '01', '0'),
('91101045', 'VTYPE_MOBI', '01', '0'),
('91101121', 'VTYPE_MOBI', '01', '0'),
('91101193', 'VTYPE_MOBI', '01', '0'),
('91101345', 'VTYPE_MOBI', '01', '0'),
('91101349', 'VTYPE_MOBI', '01', '0'),
('91101388', 'VTYPE_MOBI', '01', '0'),
('91101389', 'VTYPE_MOBI', '01', '0'),
('91101390', 'VTYPE_MOBI', '01', '0'),
('91101391', 'VTYPE_MOBI', '01', '0'),
('91101392', 'VTYPE_MOBI', '01', '0'),
('91101393', 'VTYPE_MOBI', '01', '0'),
('91101394', 'VTYPE_MOBI', '01', '0'),
('91101395', 'VTYPE_MOBI', '01', '0'),
('91101396', 'VTYPE_MOBI', '01', '0'),
('91101397', 'VTYPE_MOBI', '01', '0'),
('91101398', 'VTYPE_MOBI', '01', '0'),
('91101399', 'VTYPE_MOBI', '01', '0'),
('91101400', 'VTYPE_MOBI', '01', '0'),
('91101401', 'VTYPE_MOBI', '01', '0'),
('91101402', 'VTYPE_MOBI', '01', '0'),
('91101403', 'VTYPE_MOBI', '01', '0'),
('91101404', 'VTYPE_MOBI', '01', '0'),
('91101405', 'VTYPE_MOBI', '01', '0'),
('91101406', 'VTYPE_MOBI', '01', '0'),
('91101407', 'VTYPE_MOBI', '01', '0'),
('91101408', 'VTYPE_MOBI', '01', '0'),
('91101409', 'VTYPE_MOBI', '01', '0'),
('91101410', 'VTYPE_MOBI', '01', '0'),
('91101411', 'VTYPE_MOBI', '01', '0'),
('91101412', 'VTYPE_MOBI', '01', '0'),
('91101413', 'VTYPE_MOBI', '01', '0'),
('91101414', 'MTYPE_BRON', '04', '0'),
('91101415', 'VTYPE_MOBI', '01', '0'),
('91101416', 'VTYPE_MOBI', '01', '0'),
('91101417', 'VTYPE_MOBI', '01', '0'),
('91101418', 'VTYPE_MOBI', '01', '0'),
('91101420', 'VTYPE_MOBI', '01', '0'),
('91101421', 'VTYPE_MOBI', '01', '0'),
('91101422', 'VTYPE_MOBI', '01', '0'),
('91101423', 'VTYPE_MOBI', '01', '0'),
('91101424', 'VTYPE_MOBI', '01', '0'),
('91101425', 'VTYPE_MOBI', '01', '0'),
('91101426', 'VTYPE_MOBI', '01', '0'),
('91101427', 'VTYPE_MOBI', '01', '0'),
('91101428', 'VTYPE_MOBI', '01', '0'),
('91101429', 'VTYPE_MOBI', '01', '0'),
('91101430', 'VTYPE_MOBI', '01', '0'),
('91101431', 'VTYPE_MOBI', '01', '0'),
('91101432', 'VTYPE_MOBI', '01', '0'),
('91101433', 'VTYPE_MOBI', '01', '0'),
('91101434', 'VTYPE_MOBI', '01', '0'),
('91101435', 'VTYPE_MOBI', '01', '0'),
('91101436', 'VTYPE_MOBI', '01', '0'),
('91101437', 'VTYPE_MOBI', '01', '0'),
('91101438', 'VTYPE_MOBI', '01', '0'),
('91101439', 'VTYPE_MOBI', '01', '0'),
('91101440', 'VTYPE_MOBI', '01', '0'),
('91101441', 'VTYPE_MOBI', '01', '0'),
('91101442', 'VTYPE_MOBI', '01', '0'),
('91101443', 'VTYPE_MOBI', '01', '0'),
('91101444', 'MTYPE_SILV', '05', '0'),
('91101445', 'VTYPE_MOBI', '01', '0'),
('91101446', 'VTYPE_MOBI', '01', '0'),
('91101447', 'VTYPE_MOBI', '01', '0'),
('91101449', 'VTYPE_MOBI', '01', '0'),
('91101450', 'VTYPE_MOBI', '01', '0'),
('91101451', 'VTYPE_MOBI', '01', '0'),
('91101452', 'VTYPE_MOBI', '01', '0'),
('91101454', 'VTYPE_MOBI', '01', '0'),
('91101455', 'VTYPE_MOBI', '01', '0'),
('91101456', 'VTYPE_MOBI', '01', '0'),
('91101457', 'VTYPE_MOBI', '01', '0'),
('91101458', 'VTYPE_MOBI', '01', '0'),
('91101459', 'VTYPE_MOBI', '01', '0'),
('91101460', 'VTYPE_MOBI', '01', '0'),
('91101461', 'VTYPE_MOBI', '01', '0'),
('91101462', 'VTYPE_MOBI', '01', '0'),
('91101463', 'VTYPE_MOBI', '01', '0'),
('91101464', 'VTYPE_MOBI', '01', '0'),
('91101465', 'VTYPE_MOBI', '01', '0'),
('91101466', 'VTYPE_MOBI', '01', '0'),
('91101467', 'VTYPE_MOBI', '01', '0'),
('91101468', 'VTYPE_MOBI', '01', '0'),
('91101469', 'VTYPE_MOBI', '01', '0'),
('91101470', 'VTYPE_MOBI', '01', '0'),
('91101471', 'VTYPE_MOBI', '01', '0'),
('91101472', 'VTYPE_MOBI', '01', '0'),
('91101473', 'VTYPE_MOBI', '01', '0'),
('91101474', 'VTYPE_MOBI', '01', '0'),
('91101475', 'VTYPE_MOBI', '01', '0'),
('91101477', 'VTYPE_MOBI', '01', '0'),
('91101478', 'VTYPE_MOBI', '01', '0'),
('91101479', 'VTYPE_MOBI', '01', '0'),
('91101480', 'VTYPE_MOBI', '01', '0'),
('91101481', 'VTYPE_MOBI', '01', '0'),
('91101482', 'VTYPE_MOBI', '01', '0'),
('91101483', 'VTYPE_MOBI', '01', '0'),
('91101484', 'VTYPE_MOBI', '01', '0'),
('91101485', 'VTYPE_MOBI', '01', '0'),
('91101486', 'VTYPE_MOBI', '01', '0'),
('91101488', 'VTYPE_MOBI', '01', '0'),
('91101489', 'VTYPE_MOBI', '01', '0'),
('91101490', 'VTYPE_MOBI', '01', '0'),
('91101491', 'VTYPE_MOBI', '01', '0'),
('91101492', 'VTYPE_MOBI', '01', '0'),
('91101493', 'VTYPE_MOBI', '01', '0'),
('91101494', 'VTYPE_MOBI', '01', '0'),
('91101495', 'VTYPE_MOBI', '01', '0'),
('91101496', 'VTYPE_MOBI', '01', '0'),
('91101497', 'VTYPE_MOBI', '01', '0'),
('91101498', 'VTYPE_MOBI', '01', '0'),
('91101499', 'VTYPE_MOBI', '01', '0'),
('91101500', 'VTYPE_MOBI', '01', '0'),
('91101501', 'VTYPE_MOBI', '01', '0'),
('91101502', 'VTYPE_MOBI', '01', '0'),
('91101503', 'VTYPE_MOBI', '01', '0'),
('91101504', 'VTYPE_MOBI', '01', '0'),
('91101505', 'VTYPE_MOBI', '01', '0'),
('91101506', 'VTYPE_MOBI', '01', '0'),
('91101507', 'VTYPE_MOBI', '01', '0'),
('91101508', 'VTYPE_MOBI', '01', '0'),
('91101509', 'VTYPE_MOBI', '01', '0'),
('91101510', 'VTYPE_MOBI', '01', '0'),
('91101511', 'VTYPE_MOBI', '01', '0'),
('91101512', 'VTYPE_MOBI', '01', '0'),
('91101513', 'VTYPE_MOBI', '01', '0'),
('91101514', 'VTYPE_MOBI', '01', '0'),
('91101515', 'MTYPE_BRON', '04', '0'),
('91101516', 'VTYPE_MOBI', '01', '0'),
('91101517', 'VTYPE_MOBI', '01', '0'),
('91101518', 'VTYPE_MOBI', '01', '0'),
('91101520', 'VTYPE_MOBI', '01', '0'),
('91101521', 'VTYPE_MOBI', '01', '0'),
('91101522', 'VTYPE_MOBI', '01', '0'),
('91101523', 'VTYPE_MOBI', '01', '0'),
('91101525', 'VTYPE_MOBI', '01', '0'),
('91101526', 'VTYPE_MOBI', '01', '0'),
('91101527', 'VTYPE_MOBI', '01', '0'),
('91101528', 'VTYPE_MOBI', '01', '0'),
('91101529', 'VTYPE_MOBI', '01', '0'),
('91101530', 'VTYPE_MOBI', '01', '0'),
('91101531', 'VTYPE_MOBI', '01', '0'),
('91101532', 'VTYPE_MOBI', '01', '0'),
('91101533', 'VTYPE_MOBI', '01', '0'),
('91101534', 'VTYPE_MOBI', '01', '0'),
('91101535', 'VTYPE_MOBI', '01', '0'),
('91101536', 'VTYPE_MOBI', '01', '0'),
('91101537', 'VTYPE_MOBI', '01', '0'),
('91101538', 'VTYPE_MOBI', '01', '0'),
('91101539', 'VTYPE_MOBI', '01', '0'),
('91101540', 'VTYPE_MOBI', '01', '0'),
('91101541', 'VTYPE_MOBI', '01', '0'),
('91101542', 'VTYPE_MOBI', '01', '0'),
('91101544', 'VTYPE_MOBI', '01', '0'),
('91101546', 'VTYPE_MOBI', '01', '0'),
('91101547', 'VTYPE_MOBI', '01', '0'),
('91101548', 'VTYPE_MOBI', '01', '0'),
('91101549', 'VTYPE_MOBI', '01', '0'),
('91101551', 'VTYPE_MOBI', '01', '0'),
('91101552', 'VTYPE_MOBI', '01', '0'),
('91101553', 'VTYPE_MOBI', '01', '0'),
('91101554', 'VTYPE_MOBI', '01', '0'),
('91101555', 'MTYPE_SILV', '05', '0'),
('91101556', 'VTYPE_MOBI', '01', '0'),
('91101557', 'VTYPE_MOBI', '01', '0'),
('91101558', 'VTYPE_MOBI', '01', '0'),
('91101559', 'VTYPE_MOBI', '01', '0'),
('91101560', 'VTYPE_MOBI', '01', '0'),
('91101562', 'VTYPE_MOBI', '01', '0'),
('91101566', 'VTYPE_MOBI', '01', '0'),
('91101568', 'VTYPE_MOBI', '01', '0'),
('91101570', 'VTYPE_MOBI', '01', '0'),
('91101572', 'VTYPE_MOBI', '01', '0'),
('91101574', 'VTYPE_MOBI', '01', '0'),
('91101576', 'VTYPE_MOBI', '01', '0'),
('91101578', 'VTYPE_MOBI', '01', '0'),
('91101580', 'VTYPE_MOBI', '01', '0'),
('91101582', 'VTYPE_MOBI', '01', '0'),
('91101584', 'VTYPE_MOBI', '01', '0'),
('91101586', 'VTYPE_MOBI', '01', '0'),
('91101588', 'VTYPE_MOBI', '01', '0'),
('91101590', 'VTYPE_MOBI', '01', '0'),
('91101592', 'VTYPE_MOBI', '01', '0'),
('91101594', 'VTYPE_MOBI', '01', '0'),
('91101596', 'VTYPE_MOBI', '01', '0'),
('91101598', 'VTYPE_MOBI', '01', '0'),
('91101600', 'VTYPE_MOBI', '01', '0'),
('91101601', 'VTYPE_MOBI', '01', '0'),
('91101603', 'VTYPE_MOBI', '01', '0'),
('91101605', 'VTYPE_MOBI', '01', '0'),
('91101607', 'VTYPE_MOBI', '01', '0'),
('91101609', 'VTYPE_MOBI', '01', '0'),
('91101611', 'VTYPE_MOBI', '01', '0'),
('91101612', 'VTYPE_MOBI', '01', '0'),
('91101614', 'VTYPE_MOBI', '01', '0'),
('91101616', 'MTYPE_BRON', '04', '0'),
('91101617', 'VTYPE_MOBI', '01', '0'),
('91101619', 'VTYPE_MOBI', '01', '0'),
('91101621', 'VTYPE_MOBI', '01', '0'),
('91101625', 'VTYPE_MOBI', '01', '0'),
('91101627', 'VTYPE_MOBI', '01', '0'),
('91101629', 'VTYPE_MOBI', '01', '0'),
('91101631', 'VTYPE_MOBI', '01', '0'),
('91101633', 'VTYPE_MOBI', '01', '0'),
('91101635', 'VTYPE_MOBI', '01', '0'),
('91101637', 'VTYPE_MOBI', '01', '0'),
('91101639', 'VTYPE_MOBI', '01', '0'),
('91101641', 'VTYPE_MOBI', '01', '0'),
('91101643', 'VTYPE_MOBI', '01', '0'),
('91101645', 'VTYPE_MOBI', '01', '0'),
('91101647', 'VTYPE_MOBI', '01', '0'),
('91101649', 'VTYPE_MOBI', '01', '0'),
('91101651', 'VTYPE_MOBI', '01', '0'),
('91101655', 'VTYPE_MOBI', '01', '0'),
('91101657', 'VTYPE_MOBI', '01', '0'),
('91101659', 'VTYPE_MOBI', '01', '0'),
('91101661', 'VTYPE_MOBI', '01', '0'),
('91101662', 'VTYPE_MOBI', '01', '0'),
('91101664', 'VTYPE_MOBI', '01', '0'),
('91101666', 'MTYPE_SILV', '05', '0'),
('91101667', 'VTYPE_MOBI', '01', '0'),
('91101669', 'VTYPE_MOBI', '01', '0'),
('91101671', 'VTYPE_MOBI', '01', '0'),
('91101673', 'VTYPE_MOBI', '01', '0'),
('91101675', 'VTYPE_MOBI', '01', '0'),
('91101677', 'VTYPE_MOBI', '01', '0'),
('91101679', 'VTYPE_MOBI', '01', '0'),
('91101681', 'VTYPE_MOBI', '01', '0'),
('91101683', 'VTYPE_MOBI', '01', '0'),
('91101685', 'VTYPE_MOBI', '01', '0'),
('91101689', 'VTYPE_MOBI', '01', '0'),
('91101691', 'VTYPE_MOBI', '01', '0'),
('91101693', 'VTYPE_MOBI', '01', '0'),
('91101695', 'VTYPE_MOBI', '01', '0'),
('91101697', 'VTYPE_MOBI', '01', '0'),
('91101699', 'VTYPE_MOBI', '01', '0'),
('91101700', 'VTYPE_MOBI', '01', '0'),
('91101702', 'VTYPE_MOBI', '01', '0'),
('91101704', 'VTYPE_MOBI', '01', '0'),
('91101706', 'VTYPE_MOBI', '01', '0'),
('91101708', 'VTYPE_MOBI', '01', '0'),
('91101710', 'VTYPE_MOBI', '01', '0'),
('91101711', 'VTYPE_MOBI', '01', '0'),
('91101713', 'VTYPE_MOBI', '01', '0'),
('91101715', 'VTYPE_MOBI', '01', '0'),
('91101717', 'MTYPE_BRON', '04', '0'),
('91101718', 'VTYPE_MOBI', '01', '0'),
('91101720', 'VTYPE_MOBI', '01', '0'),
('91101722', 'VTYPE_MOBI', '01', '0'),
('91101724', 'VTYPE_MOBI', '01', '0'),
('91101726', 'VTYPE_MOBI', '01', '0'),
('91101728', 'VTYPE_MOBI', '01', '0'),
('91101730', 'VTYPE_MOBI', '01', '0'),
('91101732', 'VTYPE_MOBI', '01', '0'),
('91101734', 'VTYPE_MOBI', '01', '0'),
('91101738', 'VTYPE_MOBI', '01', '0'),
('91101740', 'VTYPE_MOBI', '01', '0'),
('91101742', 'VTYPE_MOBI', '01', '0'),
('91101744', 'VTYPE_MOBI', '01', '0'),
('91101746', 'VTYPE_MOBI', '01', '0'),
('91101748', 'VTYPE_MOBI', '01', '0'),
('91101750', 'VTYPE_MOBI', '01', '0'),
('91101754', 'VTYPE_MOBI', '01', '0'),
('91101756', 'VTYPE_MOBI', '01', '0'),
('91101758', 'VTYPE_MOBI', '01', '0'),
('91101760', 'VTYPE_MOBI', '01', '0'),
('91101762', 'VTYPE_MOBI', '01', '0'),
('91101764', 'VTYPE_MOBI', '01', '0'),
('91101766', 'VTYPE_MOBI', '01', '0'),
('91101768', 'VTYPE_MOBI', '01', '0'),
('91101770', 'VTYPE_MOBI', '01', '0'),
('91101772', 'VTYPE_MOBI', '01', '0'),
('91101774', 'VTYPE_MOBI', '01', '0'),
('91101775', 'VTYPE_MOBI', '01', '0'),
('91101776', 'VTYPE_MOBI', '01', '0'),
('91101777', 'MTYPE_SILV', '05', '0'),
('91101779', 'VTYPE_MOBI', '01', '0'),
('91101781', 'VTYPE_MOBI', '01', '0'),
('91101783', 'VTYPE_MOBI', '01', '0'),
('91101785', 'VTYPE_MOBI', '01', '0'),
('91101789', 'VTYPE_MOBI', '01', '0'),
('91101791', 'VTYPE_MOBI', '01', '0'),
('91101793', 'VTYPE_MOBI', '01', '0'),
('91101795', 'VTYPE_MOBI', '01', '0'),
('91101797', 'VTYPE_MOBI', '01', '0'),
('91101799', 'VTYPE_MOBI', '01', '0'),
('91101800', 'VTYPE_MOBI', '01', '0'),
('91101806', 'VTYPE_MOBI', '01', '0'),
('91101808', 'VTYPE_MOBI', '01', '0'),
('91101810', 'VTYPE_MOBI', '01', '0'),
('91101811', 'VTYPE_MOBI', '01', '0'),
('91101813', 'VTYPE_MOBI', '01', '0'),
('91101815', 'VTYPE_MOBI', '01', '0'),
('91101817', 'VTYPE_MOBI', '01', '0'),
('91101818', 'MTYPE_BRON', '04', '0'),
('91101820', 'VTYPE_MOBI', '01', '0'),
('91101822', 'VTYPE_MOBI', '01', '0'),
('91101824', 'VTYPE_MOBI', '01', '0'),
('91101826', 'VTYPE_MOBI', '01', '0'),
('91101828', 'VTYPE_MOBI', '01', '0'),
('91101830', 'VTYPE_MOBI', '01', '0'),
('91101832', 'VTYPE_MOBI', '01', '0'),
('91101835', 'VTYPE_MOBI', '01', '0'),
('91101836', 'VTYPE_MOBI', '01', '0'),
('91101837', 'VTYPE_MOBI', '01', '0'),
('91101838', 'VTYPE_MOBI', '01', '0'),
('91101839', 'VTYPE_MOBI', '01', '0'),
('91101840', 'VTYPE_MOBI', '01', '0'),
('91101841', 'VTYPE_MOBI', '01', '0'),
('91101842', 'VTYPE_MOBI', '01', '0'),
('91101843', 'VTYPE_MOBI', '01', '0'),
('91101844', 'VTYPE_MOBI', '01', '0'),
('91101845', 'VTYPE_MOBI', '01', '0'),
('91101847', 'VTYPE_MOBI', '01', '0'),
('91101848', 'VTYPE_MOBI', '01', '0'),
('91101849', 'VTYPE_MOBI', '01', '0'),
('91101850', 'VTYPE_MOBI', '01', '0'),
('91101851', 'VTYPE_MOBI', '01', '0'),
('91101852', 'VTYPE_MOBI', '01', '0'),
('91101854', 'VTYPE_MOBI', '01', '0'),
('91101855', 'VTYPE_MOBI', '01', '0'),
('91101856', 'VTYPE_MOBI', '01', '0'),
('91101857', 'VTYPE_MOBI', '01', '0'),
('91101858', 'VTYPE_MOBI', '01', '0'),
('91101859', 'VTYPE_MOBI', '01', '0'),
('91101860', 'VTYPE_MOBI', '01', '0'),
('91101861', 'VTYPE_MOBI', '01', '0'),
('91101862', 'VTYPE_MOBI', '01', '0'),
('91101863', 'VTYPE_MOBI', '01', '0'),
('91101864', 'VTYPE_MOBI', '01', '0'),
('91101865', 'VTYPE_MOBI', '01', '0'),
('91101866', 'VTYPE_MOBI', '01', '0'),
('91101868', 'VTYPE_MOBI', '01', '0'),
('91101869', 'VTYPE_MOBI', '01', '0'),
('91101870', 'VTYPE_MOBI', '01', '0'),
('91101872', 'VTYPE_MOBI', '01', '0'),
('91101873', 'VTYPE_MOBI', '01', '0'),
('91101875', 'VTYPE_MOBI', '01', '0'),
('91101877', 'VTYPE_MOBI', '01', '0'),
('91101878', 'VTYPE_MOBI', '01', '0'),
('91101879', 'VTYPE_MOBI', '01', '0'),
('91101880', 'VTYPE_MOBI', '01', '0'),
('91101881', 'VTYPE_MOBI', '01', '0'),
('91101882', 'VTYPE_MOBI', '01', '0'),
('91101883', 'VTYPE_MOBI', '01', '0'),
('91101884', 'VTYPE_MOBI', '01', '0'),
('91101885', 'VTYPE_MOBI', '01', '0'),
('91101886', 'VTYPE_MOBI', '01', '0'),
('91101887', 'VTYPE_MOBI', '01', '0'),
('91101888', 'MTYPE_SILV', '05', '0'),
('91101889', 'VTYPE_MOBI', '01', '0'),
('91101890', 'VTYPE_MOBI', '01', '0'),
('91101891', 'VTYPE_MOBI', '01', '0'),
('91101892', 'VTYPE_MOBI', '01', '0'),
('91101893', 'VTYPE_MOBI', '01', '0'),
('91101894', 'VTYPE_MOBI', '01', '0'),
('91101895', 'VTYPE_MOBI', '01', '0'),
('91101896', 'VTYPE_MOBI', '01', '0'),
('91101897', 'VTYPE_MOBI', '01', '0'),
('91101898', 'VTYPE_MOBI', '01', '0'),
('91101899', 'VTYPE_MOBI', '01', '0'),
('91101900', 'VTYPE_MOBI', '01', '0'),
('91101901', 'VTYPE_MOBI', '01', '0'),
('91101902', 'VTYPE_MOBI', '01', '0'),
('91101903', 'VTYPE_MOBI', '01', '0'),
('91101904', 'VTYPE_MOBI', '01', '0'),
('91101905', 'VTYPE_MOBI', '01', '0'),
('91101906', 'VTYPE_MOBI', '01', '0'),
('91101907', 'VTYPE_MOBI', '01', '0'),
('91101908', 'VTYPE_MOBI', '01', '0'),
('91101909', 'VTYPE_MOBI', '01', '0'),
('91101910', 'VTYPE_MOBI', '01', '0'),
('91101911', 'VTYPE_MOBI', '01', '0'),
('91101912', 'VTYPE_MOBI', '01', '0'),
('91101913', 'VTYPE_MOBI', '01', '0'),
('91101914', 'VTYPE_MOBI', '01', '0'),
('91101915', 'VTYPE_MOBI', '01', '0'),
('91101916', 'VTYPE_MOBI', '01', '0'),
('91101917', 'VTYPE_MOBI', '01', '0'),
('91101918', 'VTYPE_MOBI', '01', '0'),
('91101919', 'MTYPE_BRON', '04', '0'),
('91101920', 'VTYPE_MOBI', '01', '0'),
('91101922', 'VTYPE_MOBI', '01', '0'),
('91101924', 'VTYPE_MOBI', '01', '0'),
('91101925', 'VTYPE_MOBI', '01', '0'),
('91101926', 'VTYPE_MOBI', '01', '0'),
('91101927', 'VTYPE_MOBI', '01', '0'),
('91101928', 'VTYPE_MOBI', '01', '0'),
('91101929', 'VTYPE_MOBI', '01', '0'),
('91101930', 'VTYPE_MOBI', '01', '0'),
('91101931', 'VTYPE_MOBI', '01', '0'),
('91101932', 'VTYPE_MOBI', '01', '0'),
('91101933', 'VTYPE_MOBI', '01', '0'),
('91101934', 'VTYPE_MOBI', '01', '0'),
('91101935', 'VTYPE_MOBI', '01', '0'),
('91101936', 'VTYPE_MOBI', '01', '0'),
('91101937', 'VTYPE_MOBI', '01', '0'),
('91101938', 'VTYPE_MOBI', '01', '0'),
('91101939', 'VTYPE_MOBI', '01', '0'),
('91101940', 'VTYPE_MOBI', '01', '0'),
('91101943', 'VTYPE_MOBI', '01', '0'),
('91101944', 'VTYPE_MOBI', '01', '0'),
('91101945', 'VTYPE_MOBI', '01', '0'),
('91101946', 'VTYPE_MOBI', '01', '0'),
('91101947', 'VTYPE_MOBI', '01', '0'),
('91101948', 'VTYPE_MOBI', '01', '0'),
('91101949', 'VTYPE_MOBI', '01', '0'),
('91101950', 'VTYPE_MOBI', '01', '0'),
('91101951', 'VTYPE_MOBI', '01', '0'),
('91101952', 'VTYPE_MOBI', '01', '0'),
('91101953', 'VTYPE_MOBI', '01', '0'),
('91101954', 'VTYPE_MOBI', '01', '0'),
('91101955', 'VTYPE_MOBI', '01', '0'),
('91101956', 'VTYPE_MOBI', '01', '0'),
('91101958', 'VTYPE_MOBI', '01', '0'),
('91101959', 'VTYPE_MOBI', '01', '0'),
('91101960', 'VTYPE_MOBI', '01', '0'),
('91101961', 'VTYPE_MOBI', '01', '0'),
('91101962', 'VTYPE_MOBI', '01', '0'),
('91101963', 'VTYPE_MOBI', '01', '0'),
('91101964', 'VTYPE_MOBI', '01', '0'),
('91101965', 'VTYPE_MOBI', '01', '0'),
('91101966', 'VTYPE_MOBI', '01', '0'),
('91101967', 'VTYPE_MOBI', '01', '0'),
('91101968', 'VTYPE_MOBI', '01', '0'),
('91101969', 'VTYPE_MOBI', '01', '0'),
('91101970', 'VTYPE_MOBI', '01', '0'),
('91101971', 'VTYPE_MOBI', '01', '0'),
('91101973', 'VTYPE_MOBI', '01', '0'),
('91101974', 'VTYPE_MOBI', '01', '0'),
('91101976', 'VTYPE_MOBI', '01', '0'),
('91101977', 'VTYPE_MOBI', '01', '0'),
('91101978', 'VTYPE_MOBI', '01', '0'),
('91101979', 'VTYPE_MOBI', '01', '0'),
('91101980', 'VTYPE_MOBI', '01', '0'),
('91101982', 'VTYPE_MOBI', '01', '0'),
('91101984', 'VTYPE_MOBI', '01', '0'),
('91101986', 'VTYPE_MOBI', '01', '0'),
('91101988', 'VTYPE_MOBI', '01', '0'),
('91101990', 'VTYPE_MOBI', '01', '0'),
('91101991', 'VTYPE_MOBI', '01', '0'),
('91101993', 'VTYPE_MOBI', '01', '0'),
('91101995', 'VTYPE_MOBI', '01', '0'),
('91101997', 'VTYPE_MOBI', '01', '0'),
('91101999', 'MTYPE_SILV', '05', '0'),
('91102000', 'MTYPE_SILV', '05', '0'),
('91102001', 'VTYPE_MOBI', '01', '0'),
('91102002', 'VTYPE_MOBI', '01', '0'),
('91102003', 'VTYPE_MOBI', '01', '0'),
('91102005', 'VTYPE_MOBI', '01', '0'),
('91102007', 'VTYPE_MOBI', '01', '0'),
('91102009', 'VTYPE_MOBI', '01', '0'),
('91102011', 'VTYPE_MOBI', '01', '0'),
('91102013', 'VTYPE_MOBI', '01', '0'),
('91102015', 'VTYPE_MOBI', '01', '0'),
('91102017', 'VTYPE_MOBI', '01', '0'),
('91102019', 'VTYPE_MOBI', '01', '0'),
('91102021', 'VTYPE_MOBI', '01', '0'),
('91102022', 'VTYPE_MOBI', '01', '0'),
('91102024', 'VTYPE_MOBI', '01', '0'),
('91102026', 'VTYPE_MOBI', '01', '0'),
('91102028', 'VTYPE_MOBI', '01', '0'),
('91102030', 'VTYPE_MOBI', '01', '0'),
('91102032', 'VTYPE_MOBI', '01', '0'),
('91102034', 'VTYPE_MOBI', '01', '0'),
('91102036', 'VTYPE_MOBI', '01', '0'),
('91102038', 'VTYPE_MOBI', '01', '0'),
('91102040', 'VTYPE_MOBI', '01', '0'),
('91102042', 'VTYPE_MOBI', '01', '0'),
('91102044', 'VTYPE_MOBI', '01', '0'),
('91102046', 'VTYPE_MOBI', '01', '0'),
('91102048', 'VTYPE_MOBI', '01', '0'),
('91102050', 'VTYPE_MOBI', '01', '0'),
('91102052', 'VTYPE_MOBI', '01', '0'),
('91102054', 'VTYPE_MOBI', '01', '0'),
('91102056', 'VTYPE_MOBI', '01', '0'),
('91102058', 'VTYPE_MOBI', '01', '0'),
('91102060', 'VTYPE_MOBI', '01', '0'),
('91102062', 'VTYPE_MOBI', '01', '0'),
('91102064', 'VTYPE_MOBI', '01', '0'),
('91102066', 'VTYPE_MOBI', '01', '0'),
('91102068', 'VTYPE_MOBI', '01', '0'),
('91102070', 'VTYPE_MOBI', '01', '0'),
('91102072', 'VTYPE_MOBI', '01', '0'),
('91102074', 'VTYPE_MOBI', '01', '0'),
('91102076', 'VTYPE_MOBI', '01', '0'),
('91102077', 'VTYPE_MOBI', '01', '0'),
('91102078', 'VTYPE_MOBI', '01', '0'),
('91102080', 'VTYPE_MOBI', '01', '0'),
('91102082', 'VTYPE_MOBI', '01', '0'),
('91102084', 'VTYPE_MOBI', '01', '0'),
('91102086', 'VTYPE_MOBI', '01', '0'),
('91102088', 'VTYPE_MOBI', '01', '0'),
('91102090', 'VTYPE_MOBI', '01', '0'),
('91102092', 'VTYPE_MOBI', '01', '0'),
('91102094', 'VTYPE_MOBI', '01', '0'),
('91102096', 'VTYPE_MOBI', '01', '0'),
('91102098', 'VTYPE_MOBI', '01', '0'),
('91102100', 'VTYPE_MOBI', '01', '0'),
('91102101', 'VTYPE_MOBI', '01', '0'),
('91102103', 'VTYPE_MOBI', '01', '0'),
('91102105', 'VTYPE_MOBI', '01', '0'),
('91102107', 'VTYPE_MOBI', '01', '0'),
('91102109', 'VTYPE_MOBI', '01', '0'),
('91102111', 'MTYPE_SILV', '05', '0'),
('91102112', 'VTYPE_MOBI', '01', '0'),
('91102113', 'VTYPE_MOBI', '01', '0'),
('91102115', 'VTYPE_MOBI', '01', '0'),
('91102117', 'VTYPE_MOBI', '01', '0'),
('91102119', 'VTYPE_MOBI', '01', '0'),
('91102121', 'MTYPE_BRON', '04', '0'),
('91102122', 'VTYPE_MOBI', '01', '0'),
('91102123', 'VTYPE_MOBI', '01', '0'),
('91102125', 'VTYPE_MOBI', '01', '0'),
('91102127', 'VTYPE_MOBI', '01', '0'),
('91102129', 'VTYPE_MOBI', '01', '0'),
('91102131', 'VTYPE_MOBI', '01', '0'),
('91102133', 'VTYPE_MOBI', '01', '0'),
('91102135', 'VTYPE_MOBI', '01', '0'),
('91102137', 'VTYPE_MOBI', '01', '0'),
('91102139', 'VTYPE_MOBI', '01', '0'),
('91102141', 'VTYPE_MOBI', '01', '0'),
('91102143', 'VTYPE_MOBI', '01', '0'),
('91102145', 'VTYPE_MOBI', '01', '0'),
('91102147', 'VTYPE_MOBI', '01', '0'),
('91102149', 'VTYPE_MOBI', '01', '0'),
('91102151', 'VTYPE_MOBI', '01', '0'),
('91102153', 'VTYPE_MOBI', '01', '0'),
('91102155', 'VTYPE_MOBI', '01', '0'),
('91102157', 'VTYPE_MOBI', '01', '0'),
('91102159', 'VTYPE_MOBI', '01', '0'),
('91102161', 'VTYPE_MOBI', '01', '0'),
('91102163', 'VTYPE_MOBI', '01', '0'),
('91102165', 'VTYPE_MOBI', '01', '0'),
('91102167', 'VTYPE_MOBI', '01', '0'),
('91102169', 'VTYPE_MOBI', '01', '0'),
('91102171', 'VTYPE_MOBI', '01', '0'),
('91102173', 'VTYPE_MOBI', '01', '0'),
('91102175', 'VTYPE_MOBI', '01', '0'),
('91102177', 'VTYPE_MOBI', '01', '0'),
('91102179', 'VTYPE_MOBI', '01', '0'),
('91102181', 'VTYPE_MOBI', '01', '0'),
('91102183', 'VTYPE_MOBI', '01', '0'),
('91102185', 'VTYPE_MOBI', '01', '0'),
('91102187', 'VTYPE_MOBI', '01', '0'),
('91102189', 'VTYPE_MOBI', '01', '0'),
('91102191', 'VTYPE_MOBI', '01', '0'),
('91102193', 'VTYPE_MOBI', '01', '0'),
('91102197', 'VTYPE_MOBI', '01', '0'),
('91102199', 'VTYPE_MOBI', '01', '0'),
('91102200', 'MTYPE_BRON', '03', '0'),
('91102204', 'VTYPE_MOBI', '01', '0'),
('91102206', 'VTYPE_MOBI', '01', '0'),
('91102208', 'VTYPE_MOBI', '01', '0'),
('91102211', 'MTYPE_BRON', '03', '0'),
('91102212', 'VTYPE_MOBI', '01', '0'),
('91102214', 'VTYPE_MOBI', '01', '0'),
('91102216', 'VTYPE_MOBI', '01', '0'),
('91102218', 'VTYPE_MOBI', '01', '0'),
('91102220', 'VTYPE_MOBI', '05', '0'),
('91102221', 'VTYPE_MOBI', '05', '0'),
('91102222', 'MTYPE_GOLD', '02', '0'),
('91102223', 'VTYPE_MOBI', '05', '0'),
('91102224', 'VTYPE_MOBI', '05', '0'),
('91102225', 'VTYPE_MOBI', '05', '0'),
('91102226', 'VTYPE_MOBI', '05', '0'),
('91102227', 'VTYPE_MOBI', '05', '0'),
('91102228', 'VTYPE_MOBI', '05', '0'),
('91102229', 'VTYPE_MOBI', '05', '0'),
('91102230', 'VTYPE_MOBI', '01', '0'),
('91102232', 'VTYPE_MOBI', '01', '0'),
('91102233', 'MTYPE_BRON', '03', '0'),
('91102234', 'VTYPE_MOBI', '01', '0'),
('91102236', 'VTYPE_MOBI', '01', '0'),
('91102238', 'VTYPE_MOBI', '01', '0'),
('91102240', 'VTYPE_MOBI', '01', '0'),
('91102242', 'VTYPE_MOBI', '01', '0'),
('91102243', 'VTYPE_MOBI', '01', '0'),
('91102244', 'MTYPE_BRON', '03', '0'),
('91102246', 'VTYPE_MOBI', '01', '0'),
('91102248', 'VTYPE_MOBI', '01', '0'),
('91102250', 'VTYPE_MOBI', '01', '0'),
('91102251', 'VTYPE_MOBI', '01', '0'),
('91102252', 'VTYPE_MOBI', '01', '0'),
('91102253', 'VTYPE_MOBI', '01', '0'),
('91102254', 'VTYPE_MOBI', '01', '0'),
('91102255', 'MTYPE_BRON', '03', '0'),
('91102256', 'VTYPE_MOBI', '01', '0'),
('91102257', 'VTYPE_MOBI', '01', '0'),
('91102258', 'VTYPE_MOBI', '01', '0'),
('91102259', 'VTYPE_MOBI', '01', '0'),
('91102260', 'VTYPE_MOBI', '01', '0'),
('91102261', 'VTYPE_MOBI', '01', '0'),
('91102262', 'VTYPE_MOBI', '01', '0'),
('91102263', 'VTYPE_MOBI', '01', '0'),
('91102264', 'VTYPE_MOBI', '01', '0'),
('91102265', 'VTYPE_MOBI', '01', '0'),
('91102266', 'MTYPE_BRON', '03', '0'),
('91102267', 'VTYPE_MOBI', '01', '0'),
('91102268', 'VTYPE_MOBI', '01', '0'),
('91102269', 'VTYPE_MOBI', '01', '0'),
('91102270', 'VTYPE_MOBI', '01', '0'),
('91102271', 'VTYPE_MOBI', '01', '0'),
('91102272', 'VTYPE_MOBI', '01', '0'),
('91102273', 'VTYPE_MOBI', '01', '0'),
('91102274', 'VTYPE_MOBI', '01', '0'),
('91102275', 'VTYPE_MOBI', '01', '0'),
('91102276', 'VTYPE_MOBI', '01', '0'),
('91102277', 'MTYPE_BRON', '03', '0'),
('91102278', 'VTYPE_MOBI', '01', '0'),
('91102279', 'VTYPE_MOBI', '01', '0'),
('91102280', 'VTYPE_MOBI', '01', '0'),
('91102281', 'VTYPE_MOBI', '01', '0'),
('91102282', 'VTYPE_MOBI', '01', '0'),
('91102283', 'VTYPE_MOBI', '01', '0'),
('91102284', 'VTYPE_MOBI', '01', '0'),
('91102285', 'VTYPE_MOBI', '01', '0'),
('91102286', 'VTYPE_MOBI', '01', '0'),
('91102287', 'VTYPE_MOBI', '01', '0'),
('91102288', 'MTYPE_BRON', '03', '0'),
('91102289', 'VTYPE_MOBI', '01', '0'),
('91102290', 'VTYPE_MOBI', '01', '0'),
('91102291', 'VTYPE_MOBI', '01', '0'),
('91102292', 'VTYPE_MOBI', '01', '0'),
('91102293', 'VTYPE_MOBI', '01', '0'),
('91102294', 'VTYPE_MOBI', '01', '0'),
('91102295', 'VTYPE_MOBI', '01', '0'),
('91102296', 'VTYPE_MOBI', '01', '0'),
('91102297', 'VTYPE_MOBI', '01', '0'),
('91102298', 'VTYPE_MOBI', '01', '0'),
('91102299', 'MTYPE_BRON', '03', '0'),
('91102300', 'VTYPE_MOBI', '01', '0'),
('91102301', 'VTYPE_MOBI', '01', '0'),
('91102302', 'VTYPE_MOBI', '01', '0'),
('91102303', 'VTYPE_MOBI', '01', '0'),
('91102304', 'VTYPE_MOBI', '01', '0'),
('91102305', 'VTYPE_MOBI', '01', '0'),
('91102306', 'VTYPE_MOBI', '01', '0'),
('91102307', 'VTYPE_MOBI', '01', '0'),
('91102308', 'VTYPE_MOBI', '01', '0'),
('91102310', 'VTYPE_MOBI', '01', '0'),
('91102311', 'VTYPE_MOBI', '01', '0'),
('91102312', 'VTYPE_MOBI', '01', '0'),
('91102313', 'VTYPE_MOBI', '01', '0'),
('91102314', 'VTYPE_MOBI', '01', '0'),
('91102315', 'VTYPE_MOBI', '01', '0'),
('91102316', 'VTYPE_MOBI', '01', '0'),
('91102318', 'VTYPE_MOBI', '01', '0'),
('91102319', 'VTYPE_MOBI', '01', '0'),
('91102320', 'VTYPE_MOBI', '01', '0'),
('91102321', 'VTYPE_MOBI', '01', '0'),
('91102322', 'VTYPE_MOBI', '01', '0'),
('91102323', 'MTYPE_BRON', '04', '0'),
('91102324', 'VTYPE_MOBI', '01', '0'),
('91102325', 'VTYPE_MOBI', '01', '0'),
('91102326', 'VTYPE_MOBI', '01', '0'),
('91102327', 'VTYPE_MOBI', '01', '0'),
('91102328', 'VTYPE_MOBI', '01', '0'),
('91102329', 'VTYPE_MOBI', '01', '0'),
('91102330', 'VTYPE_MOBI', '01', '0'),
('91102331', 'VTYPE_MOBI', '01', '0'),
('91102332', 'VTYPE_MOBI', '01', '0'),
('91102333', 'MTYPE_SILV', '05', '0'),
('91102334', 'VTYPE_MOBI', '01', '0'),
('91102335', 'VTYPE_MOBI', '01', '0'),
('91102336', 'VTYPE_MOBI', '01', '0'),
('91102337', 'VTYPE_MOBI', '01', '0'),
('91102338', 'VTYPE_MOBI', '01', '0'),
('91102339', 'VTYPE_MOBI', '01', '0'),
('91102340', 'VTYPE_MOBI', '01', '0'),
('91102341', 'VTYPE_MOBI', '01', '0'),
('91102342', 'VTYPE_MOBI', '01', '0'),
('91102343', 'VTYPE_MOBI', '01', '0'),
('91102344', 'VTYPE_MOBI', '01', '0'),
('91102345', 'VTYPE_MOBI', '01', '0'),
('91102346', 'VTYPE_MOBI', '01', '0'),
('91102347', 'VTYPE_MOBI', '01', '0'),
('91102348', 'VTYPE_MOBI', '01', '0'),
('91102349', 'VTYPE_MOBI', '01', '0'),
('91102350', 'VTYPE_MOBI', '01', '0'),
('91102351', 'VTYPE_MOBI', '01', '0'),
('91102352', 'VTYPE_MOBI', '01', '0'),
('91102353', 'VTYPE_MOBI', '01', '0'),
('91102354', 'VTYPE_MOBI', '01', '0'),
('91102355', 'VTYPE_MOBI', '01', '0'),
('91102356', 'VTYPE_MOBI', '01', '0'),
('91102357', 'VTYPE_MOBI', '01', '0'),
('91102358', 'VTYPE_MOBI', '01', '0'),
('91102359', 'VTYPE_MOBI', '01', '0'),
('91102360', 'VTYPE_MOBI', '01', '0'),
('91102361', 'VTYPE_MOBI', '01', '0'),
('91102362', 'VTYPE_MOBI', '01', '0'),
('91102364', 'VTYPE_MOBI', '01', '0'),
('91102365', 'VTYPE_MOBI', '01', '0'),
('91102366', 'VTYPE_MOBI', '01', '0'),
('91102367', 'VTYPE_MOBI', '01', '0'),
('91102368', 'VTYPE_MOBI', '01', '0'),
('91102370', 'VTYPE_MOBI', '01', '0'),
('91102371', 'VTYPE_MOBI', '01', '0'),
('91102372', 'VTYPE_MOBI', '01', '0'),
('91102373', 'VTYPE_MOBI', '01', '0'),
('91102374', 'VTYPE_MOBI', '01', '0'),
('91102375', 'VTYPE_MOBI', '01', '0'),
('91102376', 'VTYPE_MOBI', '01', '0'),
('91102377', 'VTYPE_MOBI', '01', '0'),
('91102378', 'VTYPE_MOBI', '01', '0'),
('91102379', 'VTYPE_MOBI', '01', '0'),
('91102380', 'VTYPE_MOBI', '01', '0'),
('91102381', 'VTYPE_MOBI', '01', '0'),
('91102382', 'VTYPE_MOBI', '01', '0'),
('91102383', 'VTYPE_MOBI', '01', '0'),
('91102384', 'VTYPE_MOBI', '01', '0'),
('91102385', 'VTYPE_MOBI', '01', '0'),
('91102386', 'VTYPE_MOBI', '01', '0'),
('91102387', 'VTYPE_MOBI', '01', '0'),
('91102389', 'VTYPE_MOBI', '01', '0'),
('91102391', 'VTYPE_MOBI', '01', '0'),
('91102393', 'VTYPE_MOBI', '01', '0'),
('91102395', 'VTYPE_MOBI', '01', '0'),
('91102397', 'VTYPE_MOBI', '01', '0'),
('91102399', 'VTYPE_MOBI', '01', '0'),
('91102400', 'VTYPE_MOBI', '01', '0'),
('91102402', 'VTYPE_MOBI', '01', '0'),
('91102404', 'VTYPE_MOBI', '01', '0'),
('91102406', 'VTYPE_MOBI', '01', '0'),
('91102408', 'VTYPE_MOBI', '01', '0'),
('91102410', 'VTYPE_MOBI', '01', '0'),
('91102412', 'VTYPE_MOBI', '01', '0'),
('91102414', 'VTYPE_MOBI', '01', '0'),
('91102416', 'VTYPE_MOBI', '01', '0'),
('91102418', 'VTYPE_MOBI', '01', '0'),
('91102420', 'VTYPE_MOBI', '01', '0'),
('91102421', 'VTYPE_MOBI', '01', '0'),
('91102422', 'VTYPE_MOBI', '01', '0'),
('91102423', 'VTYPE_MOBI', '01', '0'),
('91102425', 'VTYPE_MOBI', '01', '0'),
('91102429', 'VTYPE_MOBI', '01', '0'),
('91102431', 'VTYPE_MOBI', '01', '0'),
('91102433', 'VTYPE_MOBI', '01', '0'),
('91102435', 'VTYPE_MOBI', '01', '0'),
('91102437', 'VTYPE_MOBI', '01', '0'),
('91102439', 'VTYPE_MOBI', '01', '0'),
('91102441', 'VTYPE_MOBI', '01', '0'),
('91102442', 'VTYPE_MOBI', '01', '0'),
('91102444', 'MTYPE_SILV', '05', '0'),
('91102445', 'VTYPE_MOBI', '01', '0'),
('91102447', 'VTYPE_MOBI', '01', '0'),
('91102449', 'VTYPE_MOBI', '01', '0'),
('91102451', 'VTYPE_MOBI', '01', '0'),
('91102453', 'VTYPE_MOBI', '01', '0'),
('91102455', 'VTYPE_MOBI', '01', '0'),
('91102457', 'VTYPE_MOBI', '01', '0'),
('91102459', 'VTYPE_MOBI', '01', '0'),
('91102460', 'VTYPE_MOBI', '01', '0'),
('91102461', 'VTYPE_MOBI', '01', '0'),
('91102463', 'VTYPE_MOBI', '01', '0'),
('91102465', 'VTYPE_MOBI', '01', '0'),
('91102467', 'VTYPE_MOBI', '01', '0'),
('91102469', 'VTYPE_MOBI', '01', '0'),
('91102471', 'VTYPE_MOBI', '01', '0'),
('91102473', 'VTYPE_MOBI', '01', '0'),
('91102475', 'VTYPE_MOBI', '01', '0'),
('91102477', 'VTYPE_MOBI', '01', '0'),
('91102479', 'VTYPE_MOBI', '01', '0'),
('91102481', 'VTYPE_MOBI', '01', '0'),
('91102485', 'VTYPE_MOBI', '01', '0'),
('91102487', 'VTYPE_MOBI', '01', '0'),
('91102489', 'VTYPE_MOBI', '01', '0'),
('91102491', 'VTYPE_MOBI', '01', '0'),
('91102493', 'VTYPE_MOBI', '01', '0'),
('91102495', 'VTYPE_MOBI', '01', '0'),
('91102497', 'VTYPE_MOBI', '01', '0'),
('91102499', 'VTYPE_MOBI', '01', '0'),
('91102500', 'VTYPE_MOBI', '01', '0'),
('91102502', 'VTYPE_MOBI', '01', '0'),
('91102506', 'VTYPE_MOBI', '01', '0'),
('91102508', 'VTYPE_MOBI', '01', '0'),
('91102510', 'VTYPE_MOBI', '01', '0'),
('91102512', 'VTYPE_MOBI', '01', '0'),
('91102516', 'VTYPE_MOBI', '01', '0'),
('91102518', 'VTYPE_MOBI', '01', '0'),
('91102520', 'VTYPE_MOBI', '01', '0'),
('91102523', 'VTYPE_MOBI', '01', '0'),
('91102525', 'MTYPE_BRON', '04', '0'),
('91102526', 'VTYPE_MOBI', '01', '0'),
('91102528', 'VTYPE_MOBI', '01', '0'),
('91102532', 'VTYPE_MOBI', '01', '0'),
('91102534', 'VTYPE_MOBI', '01', '0'),
('91102536', 'VTYPE_MOBI', '01', '0'),
('91102538', 'VTYPE_MOBI', '01', '0'),
('91102540', 'VTYPE_MOBI', '01', '0'),
('91102546', 'VTYPE_MOBI', '01', '0'),
('91102548', 'VTYPE_MOBI', '01', '0'),
('91102550', 'VTYPE_MOBI', '01', '0'),
('91102552', 'VTYPE_MOBI', '01', '0'),
('91102553', 'VTYPE_MOBI', '01', '0'),
('91102555', 'MTYPE_SILV', '05', '0'),
('91102556', 'VTYPE_MOBI', '01', '0'),
('91102558', 'VTYPE_MOBI', '01', '0'),
('91102560', 'VTYPE_MOBI', '01', '0'),
('91102562', 'VTYPE_MOBI', '01', '0'),
('91102564', 'VTYPE_MOBI', '01', '0'),
('91102566', 'VTYPE_MOBI', '01', '0'),
('91102568', 'VTYPE_MOBI', '01', '0'),
('91102570', 'VTYPE_MOBI', '01', '0'),
('91102572', 'VTYPE_MOBI', '01', '0'),
('91102576', 'VTYPE_MOBI', '01', '0'),
('91102578', 'VTYPE_MOBI', '01', '0'),
('91102580', 'VTYPE_MOBI', '01', '0'),
('91102581', 'VTYPE_MOBI', '01', '0'),
('91102583', 'VTYPE_MOBI', '01', '0'),
('91102585', 'VTYPE_MOBI', '01', '0'),
('91102587', 'VTYPE_MOBI', '01', '0'),
('91102589', 'VTYPE_MOBI', '01', '0'),
('91102591', 'VTYPE_MOBI', '01', '0'),
('91102593', 'VTYPE_MOBI', '01', '0'),
('91102595', 'VTYPE_MOBI', '01', '0'),
('91102599', 'VTYPE_MOBI', '01', '0'),
('91102600', 'VTYPE_MOBI', '01', '0'),
('91102602', 'VTYPE_MOBI', '01', '0'),
('91102604', 'VTYPE_MOBI', '01', '0'),
('91102606', 'VTYPE_MOBI', '01', '0'),
('91102610', 'VTYPE_MOBI', '01', '0'),
('91102612', 'VTYPE_MOBI', '01', '0'),
('91102614', 'VTYPE_MOBI', '01', '0'),
('91102616', 'VTYPE_MOBI', '01', '0'),
('91102617', 'VTYPE_MOBI', '01', '0'),
('91102619', 'VTYPE_MOBI', '01', '0'),
('91102621', 'VTYPE_MOBI', '01', '0'),
('91102622', 'VTYPE_MOBI', '01', '0'),
('91102624', 'VTYPE_MOBI', '01', '0'),
('91102626', 'MTYPE_BRON', '04', '0'),
('91102627', 'VTYPE_MOBI', '01', '0'),
('91102629', 'VTYPE_MOBI', '01', '0'),
('91102631', 'VTYPE_MOBI', '01', '0'),
('91102633', 'VTYPE_MOBI', '01', '0'),
('91102635', 'VTYPE_MOBI', '01', '0'),
('91102637', 'VTYPE_MOBI', '01', '0'),
('91102639', 'VTYPE_MOBI', '01', '0'),
('91102641', 'VTYPE_MOBI', '01', '0'),
('91102643', 'VTYPE_MOBI', '01', '0'),
('91102647', 'VTYPE_MOBI', '01', '0'),
('91102651', 'VTYPE_MOBI', '01', '0'),
('91102653', 'VTYPE_MOBI', '01', '0'),
('91102655', 'VTYPE_MOBI', '01', '0'),
('91102657', 'VTYPE_MOBI', '01', '0'),
('91102659', 'VTYPE_MOBI', '01', '0'),
('91102661', 'VTYPE_MOBI', '01', '0'),
('91102662', 'VTYPE_MOBI', '01', '0'),
('91102664', 'VTYPE_MOBI', '01', '0'),
('91102665', 'VTYPE_MOBI', '01', '0'),
('91102666', 'MTYPE_SILV', '05', '0'),
('91102667', 'VTYPE_MOBI', '01', '0'),
('91102668', 'VTYPE_MOBI', '01', '0'),
('91102669', 'VTYPE_MOBI', '01', '0'),
('91102670', 'VTYPE_MOBI', '01', '0'),
('91102671', 'VTYPE_MOBI', '01', '0'),
('91102672', 'VTYPE_MOBI', '01', '0'),
('91102673', 'VTYPE_MOBI', '01', '0'),
('91102674', 'VTYPE_MOBI', '01', '0'),
('91102675', 'VTYPE_MOBI', '01', '0'),
('91102676', 'VTYPE_MOBI', '01', '0'),
('91102677', 'VTYPE_MOBI', '01', '0'),
('91102678', 'VTYPE_MOBI', '01', '0'),
('91102679', 'VTYPE_MOBI', '01', '0'),
('91102680', 'VTYPE_MOBI', '01', '0'),
('91102681', 'VTYPE_MOBI', '01', '0'),
('91102682', 'VTYPE_MOBI', '01', '0'),
('91102684', 'VTYPE_MOBI', '01', '0'),
('91102686', 'VTYPE_MOBI', '01', '0'),
('91102687', 'VTYPE_MOBI', '01', '0'),
('91102688', 'VTYPE_MOBI', '01', '0'),
('91102689', 'VTYPE_MOBI', '01', '0'),
('91102691', 'VTYPE_MOBI', '01', '0'),
('91102692', 'VTYPE_MOBI', '01', '0'),
('91102693', 'VTYPE_MOBI', '01', '0'),
('91102696', 'VTYPE_MOBI', '01', '0'),
('91102697', 'VTYPE_MOBI', '01', '0'),
('91102698', 'VTYPE_MOBI', '01', '0'),
('91102699', 'VTYPE_MOBI', '01', '0'),
('91102700', 'VTYPE_MOBI', '01', '0'),
('91102701', 'VTYPE_MOBI', '01', '0'),
('91102702', 'VTYPE_MOBI', '01', '0'),
('91102703', 'VTYPE_MOBI', '01', '0'),
('91102704', 'VTYPE_MOBI', '01', '0'),
('91102705', 'VTYPE_MOBI', '01', '0'),
('91102706', 'VTYPE_MOBI', '01', '0'),
('91102707', 'VTYPE_MOBI', '01', '0'),
('91102708', 'VTYPE_MOBI', '01', '0'),
('91102709', 'VTYPE_MOBI', '01', '0'),
('91102711', 'VTYPE_MOBI', '01', '0'),
('91102713', 'VTYPE_MOBI', '01', '0'),
('91102714', 'VTYPE_MOBI', '01', '0'),
('91102715', 'VTYPE_MOBI', '01', '0'),
('91102716', 'VTYPE_MOBI', '01', '0'),
('91102717', 'VTYPE_MOBI', '01', '0'),
('91102718', 'VTYPE_MOBI', '01', '0'),
('91102719', 'VTYPE_MOBI', '01', '0'),
('91102720', 'VTYPE_MOBI', '01', '0'),
('91102722', 'VTYPE_MOBI', '01', '0'),
('91102723', 'VTYPE_MOBI', '01', '0'),
('91102724', 'VTYPE_MOBI', '01', '0'),
('91102725', 'VTYPE_MOBI', '01', '0'),
('91102726', 'VTYPE_MOBI', '01', '0'),
('91102727', 'MTYPE_BRON', '04', '0'),
('91102728', 'VTYPE_MOBI', '01', '0'),
('91102729', 'VTYPE_MOBI', '01', '0'),
('91102730', 'VTYPE_MOBI', '01', '0'),
('91102731', 'VTYPE_MOBI', '01', '0'),
('91102732', 'VTYPE_MOBI', '01', '0'),
('91102733', 'VTYPE_MOBI', '01', '0'),
('91102737', 'VTYPE_MOBI', '01', '0'),
('91102738', 'VTYPE_MOBI', '01', '0'),
('91102740', 'VTYPE_MOBI', '01', '0'),
('91102742', 'VTYPE_MOBI', '01', '0'),
('91102743', 'VTYPE_MOBI', '01', '0'),
('91102744', 'VTYPE_MOBI', '01', '0'),
('91102745', 'VTYPE_MOBI', '01', '0'),
('91102747', 'VTYPE_MOBI', '01', '0'),
('91102748', 'VTYPE_MOBI', '01', '0'),
('91102750', 'VTYPE_MOBI', '01', '0'),
('91102751', 'VTYPE_MOBI', '01', '0'),
('91102752', 'VTYPE_MOBI', '01', '0'),
('91102754', 'VTYPE_MOBI', '01', '0'),
('91102755', 'VTYPE_MOBI', '01', '0'),
('91102757', 'VTYPE_MOBI', '01', '0'),
('91102758', 'VTYPE_MOBI', '01', '0'),
('91102760', 'VTYPE_MOBI', '01', '0'),
('91102761', 'VTYPE_MOBI', '01', '0'),
('91102762', 'VTYPE_MOBI', '01', '0'),
('91102763', 'VTYPE_MOBI', '01', '0'),
('91102765', 'VTYPE_MOBI', '01', '0'),
('91102766', 'VTYPE_MOBI', '01', '0'),
('91102767', 'VTYPE_MOBI', '01', '0'),
('91102768', 'VTYPE_MOBI', '01', '0'),
('91102769', 'VTYPE_MOBI', '01', '0'),
('91102770', 'VTYPE_MOBI', '01', '0'),
('91102771', 'VTYPE_MOBI', '01', '0'),
('91102772', 'VTYPE_MOBI', '01', '0'),
('91102773', 'VTYPE_MOBI', '01', '0'),
('91102774', 'VTYPE_MOBI', '01', '0'),
('91102775', 'VTYPE_MOBI', '01', '0'),
('91102776', 'VTYPE_MOBI', '01', '0'),
('91102777', 'MTYPE_SILV', '05', '0'),
('91102778', 'VTYPE_MOBI', '01', '0'),
('91102779', 'VTYPE_MOBI', '01', '0'),
('91102780', 'VTYPE_MOBI', '01', '0'),
('91102782', 'VTYPE_MOBI', '01', '0'),
('91102784', 'VTYPE_MOBI', '01', '0'),
('91102786', 'VTYPE_MOBI', '01', '0'),
('91102787', 'VTYPE_MOBI', '01', '0'),
('91102789', 'VTYPE_MOBI', '01', '0'),
('91102792', 'VTYPE_MOBI', '01', '0'),
('91102793', 'VTYPE_MOBI', '01', '0'),
('91102794', 'VTYPE_MOBI', '01', '0'),
('91102795', 'VTYPE_MOBI', '01', '0'),
('91102797', 'VTYPE_MOBI', '01', '0'),
('91102798', 'VTYPE_MOBI', '01', '0'),
('91102799', 'VTYPE_MOBI', '01', '0'),
('91102800', 'VTYPE_MOBI', '01', '0'),
('91102801', 'VTYPE_MOBI', '01', '0'),
('91102802', 'VTYPE_MOBI', '01', '0'),
('91102803', 'VTYPE_MOBI', '01', '0'),
('91102804', 'VTYPE_MOBI', '01', '0'),
('91102805', 'VTYPE_MOBI', '01', '0'),
('91102806', 'VTYPE_MOBI', '01', '0'),
('91102807', 'VTYPE_MOBI', '01', '0'),
('91102808', 'VTYPE_MOBI', '01', '0'),
('91102809', 'VTYPE_MOBI', '01', '0'),
('91102810', 'VTYPE_MOBI', '01', '0'),
('91102811', 'VTYPE_MOBI', '01', '0'),
('91102812', 'VTYPE_MOBI', '01', '0'),
('91102813', 'VTYPE_MOBI', '01', '0'),
('91102815', 'VTYPE_MOBI', '01', '0'),
('91102816', 'VTYPE_MOBI', '01', '0'),
('91102817', 'VTYPE_MOBI', '01', '0'),
('91102818', 'VTYPE_MOBI', '01', '0'),
('91102820', 'VTYPE_MOBI', '01', '0'),
('91102821', 'VTYPE_MOBI', '01', '0'),
('91102822', 'VTYPE_MOBI', '01', '0'),
('91102823', 'VTYPE_MOBI', '01', '0'),
('91102824', 'VTYPE_MOBI', '01', '0'),
('91102825', 'VTYPE_MOBI', '01', '0'),
('91102826', 'VTYPE_MOBI', '01', '0'),
('91102827', 'VTYPE_MOBI', '01', '0'),
('91102828', 'MTYPE_BRON', '04', '0'),
('91102829', 'VTYPE_MOBI', '01', '0'),
('91102830', 'VTYPE_MOBI', '01', '0');
INSERT INTO `ocs_account_key` (`account_key`, `account_key_type`, `status`, `sales_flag`) VALUES
('91102831', 'VTYPE_MOBI', '01', '0'),
('91102832', 'VTYPE_MOBI', '01', '0'),
('91102833', 'VTYPE_MOBI', '01', '0'),
('91102834', 'VTYPE_MOBI', '01', '0'),
('91102835', 'VTYPE_MOBI', '01', '0'),
('91102839', 'VTYPE_MOBI', '01', '0'),
('91102845', 'VTYPE_MOBI', '01', '0'),
('91102847', 'VTYPE_MOBI', '01', '0'),
('91102849', 'VTYPE_MOBI', '01', '0'),
('91102851', 'VTYPE_MOBI', '01', '0'),
('91102855', 'VTYPE_MOBI', '01', '0'),
('91102857', 'VTYPE_MOBI', '01', '0'),
('91102861', 'VTYPE_MOBI', '01', '0'),
('91102864', 'VTYPE_MOBI', '01', '0'),
('91102865', 'VTYPE_MOBI', '01', '0'),
('91102867', 'VTYPE_MOBI', '01', '0'),
('91102869', 'VTYPE_MOBI', '01', '0'),
('91102871', 'VTYPE_MOBI', '01', '0'),
('91102875', 'VTYPE_MOBI', '01', '0'),
('91102877', 'VTYPE_MOBI', '01', '0'),
('91102879', 'VTYPE_MOBI', '01', '0'),
('91102881', 'VTYPE_MOBI', '01', '0'),
('91102882', 'VTYPE_MOBI', '01', '0'),
('91102884', 'VTYPE_MOBI', '01', '0'),
('91102886', 'VTYPE_MOBI', '01', '0'),
('91102888', 'MTYPE_SILV', '05', '0'),
('91102889', 'VTYPE_MOBI', '01', '0'),
('91102891', 'VTYPE_MOBI', '01', '0'),
('91102893', 'VTYPE_MOBI', '01', '0'),
('91102895', 'VTYPE_MOBI', '01', '0'),
('91102897', 'VTYPE_MOBI', '01', '0'),
('91102899', 'VTYPE_MOBI', '01', '0'),
('91102900', 'VTYPE_MOBI', '01', '0'),
('91102902', 'VTYPE_MOBI', '01', '0'),
('91102904', 'VTYPE_MOBI', '01', '0'),
('91102908', 'VTYPE_MOBI', '01', '0'),
('91102910', 'VTYPE_MOBI', '01', '0'),
('91102912', 'VTYPE_MOBI', '01', '0'),
('91102914', 'VTYPE_MOBI', '01', '0'),
('91102916', 'VTYPE_MOBI', '01', '0'),
('91102918', 'VTYPE_MOBI', '01', '0'),
('91102920', 'VTYPE_MOBI', '01', '0'),
('91102922', 'VTYPE_MOBI', '01', '0'),
('91102923', 'VTYPE_MOBI', '01', '0'),
('91102925', 'VTYPE_MOBI', '01', '0'),
('91102927', 'VTYPE_MOBI', '01', '0'),
('91102929', 'MTYPE_BRON', '04', '0'),
('91102930', 'VTYPE_MOBI', '01', '0'),
('91102934', 'VTYPE_MOBI', '01', '0'),
('91102938', 'VTYPE_MOBI', '01', '0'),
('91102940', 'VTYPE_MOBI', '01', '0'),
('91102942', 'VTYPE_MOBI', '01', '0'),
('91102944', 'VTYPE_MOBI', '01', '0'),
('91102948', 'VTYPE_MOBI', '01', '0'),
('91102950', 'VTYPE_MOBI', '01', '0'),
('91102954', 'VTYPE_MOBI', '01', '0'),
('91102956', 'VTYPE_MOBI', '01', '0'),
('91102958', 'VTYPE_MOBI', '01', '0'),
('91102962', 'VTYPE_MOBI', '01', '0'),
('91102966', 'VTYPE_MOBI', '01', '0'),
('91102968', 'VTYPE_MOBI', '01', '0'),
('91102970', 'VTYPE_MOBI', '01', '0'),
('91102972', 'VTYPE_MOBI', '01', '0'),
('91102974', 'VTYPE_MOBI', '01', '0'),
('91102975', 'VTYPE_MOBI', '01', '0'),
('91102976', 'VTYPE_MOBI', '01', '0'),
('91102978', 'VTYPE_MOBI', '01', '0'),
('91102980', 'VTYPE_MOBI', '01', '0'),
('91102982', 'VTYPE_MOBI', '01', '0'),
('91102984', 'VTYPE_MOBI', '01', '0'),
('91102986', 'VTYPE_MOBI', '01', '0'),
('91102988', 'VTYPE_MOBI', '01', '0'),
('91102990', 'VTYPE_MOBI', '01', '0'),
('91102992', 'VTYPE_MOBI', '01', '0'),
('91102993', 'VTYPE_MOBI', '01', '0'),
('91102995', 'VTYPE_MOBI', '01', '0'),
('91102997', 'VTYPE_MOBI', '01', '0'),
('91102999', 'MTYPE_SILV', '05', '0'),
('91103000', 'MTYPE_SILV', '05', '0'),
('91103001', 'VTYPE_MOBI', '01', '0'),
('91103002', 'VTYPE_MOBI', '01', '0'),
('91103003', 'VTYPE_MOBI', '01', '0'),
('91103005', 'VTYPE_MOBI', '01', '0'),
('91103007', 'VTYPE_MOBI', '01', '0'),
('91103009', 'VTYPE_MOBI', '01', '0'),
('91103011', 'VTYPE_MOBI', '01', '0'),
('91103013', 'VTYPE_MOBI', '01', '0'),
('91103014', 'VTYPE_MOBI', '01', '0'),
('91103015', 'VTYPE_MOBI', '01', '0'),
('91103019', 'VTYPE_MOBI', '01', '0'),
('91103021', 'VTYPE_MOBI', '01', '0'),
('91103023', 'VTYPE_MOBI', '01', '0'),
('91103025', 'VTYPE_MOBI', '01', '0'),
('91103027', 'VTYPE_MOBI', '01', '0'),
('91103029', 'VTYPE_MOBI', '01', '0'),
('91103030', 'MTYPE_BRON', '04', '0'),
('91103032', 'VTYPE_MOBI', '01', '0'),
('91103033', 'VTYPE_MOBI', '01', '0'),
('91103035', 'VTYPE_MOBI', '01', '0'),
('91103037', 'VTYPE_MOBI', '01', '0'),
('91103039', 'VTYPE_MOBI', '01', '0'),
('91103041', 'VTYPE_MOBI', '01', '0'),
('91103043', 'VTYPE_MOBI', '01', '0'),
('91103045', 'VTYPE_MOBI', '01', '0'),
('91103047', 'VTYPE_MOBI', '01', '0'),
('91103049', 'VTYPE_MOBI', '01', '0'),
('91103053', 'VTYPE_MOBI', '01', '0'),
('91103055', 'VTYPE_MOBI', '01', '0'),
('91103059', 'VTYPE_MOBI', '01', '0'),
('91103061', 'VTYPE_MOBI', '01', '0'),
('91103063', 'VTYPE_MOBI', '01', '0'),
('91103065', 'VTYPE_MOBI', '01', '0'),
('91103067', 'VTYPE_MOBI', '01', '0'),
('91103069', 'VTYPE_MOBI', '01', '0'),
('91103071', 'VTYPE_MOBI', '01', '0'),
('91103073', 'VTYPE_MOBI', '01', '0'),
('91103075', 'VTYPE_MOBI', '01', '0'),
('91103077', 'VTYPE_MOBI', '01', '0'),
('91103079', 'VTYPE_MOBI', '01', '0'),
('91103081', 'VTYPE_MOBI', '01', '0'),
('91103083', 'VTYPE_MOBI', '01', '0'),
('91103084', 'VTYPE_MOBI', '01', '0'),
('91103085', 'VTYPE_MOBI', '01', '0'),
('91103086', 'VTYPE_MOBI', '01', '0'),
('91103087', 'VTYPE_MOBI', '01', '0'),
('91103088', 'VTYPE_MOBI', '01', '0'),
('91103089', 'VTYPE_MOBI', '01', '0'),
('91103090', 'VTYPE_MOBI', '01', '0'),
('91103091', 'VTYPE_MOBI', '01', '0'),
('91103092', 'VTYPE_MOBI', '01', '0'),
('91103093', 'VTYPE_MOBI', '01', '0'),
('91103094', 'VTYPE_MOBI', '01', '0'),
('91103095', 'VTYPE_MOBI', '01', '0'),
('91103096', 'VTYPE_MOBI', '01', '0'),
('91103097', 'VTYPE_MOBI', '01', '0'),
('91103098', 'VTYPE_MOBI', '01', '0'),
('91103099', 'VTYPE_MOBI', '01', '0'),
('91103100', 'VTYPE_MOBI', '01', '0'),
('91103101', 'VTYPE_MOBI', '01', '0'),
('91103102', 'VTYPE_MOBI', '01', '0'),
('91103103', 'VTYPE_MOBI', '01', '0'),
('91103104', 'VTYPE_MOBI', '01', '0'),
('91103105', 'VTYPE_MOBI', '01', '0'),
('91103106', 'VTYPE_MOBI', '01', '0'),
('91103107', 'VTYPE_MOBI', '01', '0'),
('91103108', 'VTYPE_MOBI', '01', '0'),
('91103109', 'VTYPE_MOBI', '01', '0'),
('91103110', 'VTYPE_MOBI', '01', '0'),
('91103112', 'VTYPE_MOBI', '01', '0'),
('91103113', 'VTYPE_MOBI', '01', '0'),
('91103114', 'VTYPE_MOBI', '01', '0'),
('91103115', 'VTYPE_MOBI', '01', '0'),
('91103116', 'VTYPE_MOBI', '01', '0'),
('91103117', 'VTYPE_MOBI', '01', '0'),
('91103118', 'VTYPE_MOBI', '01', '0'),
('91103119', 'VTYPE_MOBI', '01', '0'),
('91103120', 'VTYPE_MOBI', '01', '0'),
('91103121', 'VTYPE_MOBI', '01', '0'),
('91103122', 'VTYPE_MOBI', '01', '0'),
('91103123', 'VTYPE_MOBI', '01', '0'),
('91103124', 'VTYPE_MOBI', '01', '0'),
('91103125', 'VTYPE_MOBI', '01', '0'),
('91103126', 'VTYPE_MOBI', '01', '0'),
('91103127', 'VTYPE_MOBI', '01', '0'),
('91103128', 'VTYPE_MOBI', '01', '0'),
('91103129', 'VTYPE_MOBI', '01', '0'),
('91103130', 'VTYPE_MOBI', '01', '0'),
('91103131', 'MTYPE_BRON', '04', '0'),
('91103132', 'VTYPE_MOBI', '01', '0'),
('91103133', 'VTYPE_MOBI', '01', '0'),
('91103134', 'VTYPE_MOBI', '01', '0'),
('91103135', 'VTYPE_MOBI', '01', '0'),
('91103136', 'VTYPE_MOBI', '01', '0'),
('91103137', 'VTYPE_MOBI', '01', '0'),
('91103138', 'VTYPE_MOBI', '01', '0'),
('91103139', 'VTYPE_MOBI', '01', '0'),
('91103140', 'VTYPE_MOBI', '01', '0'),
('91103141', 'VTYPE_MOBI', '01', '0'),
('91103142', 'VTYPE_MOBI', '01', '0'),
('91103143', 'VTYPE_MOBI', '01', '0'),
('91103144', 'VTYPE_MOBI', '01', '0'),
('91103145', 'VTYPE_MOBI', '01', '0'),
('91103146', 'VTYPE_MOBI', '01', '0'),
('91103147', 'VTYPE_MOBI', '01', '0'),
('91103148', 'VTYPE_MOBI', '01', '0'),
('91103149', 'VTYPE_MOBI', '01', '0'),
('91103150', 'VTYPE_MOBI', '01', '0'),
('91103151', 'VTYPE_MOBI', '01', '0'),
('91103152', 'VTYPE_MOBI', '01', '0'),
('91103153', 'VTYPE_MOBI', '01', '0'),
('91103154', 'VTYPE_MOBI', '01', '0'),
('91103155', 'VTYPE_MOBI', '01', '0'),
('91103156', 'VTYPE_MOBI', '01', '0'),
('91103157', 'VTYPE_MOBI', '01', '0'),
('91103158', 'VTYPE_MOBI', '01', '0'),
('91103159', 'VTYPE_MOBI', '01', '0'),
('91103161', 'VTYPE_MOBI', '01', '0'),
('91103162', 'VTYPE_MOBI', '01', '0'),
('91103163', 'VTYPE_MOBI', '01', '0'),
('91103164', 'VTYPE_MOBI', '01', '0'),
('91103165', 'VTYPE_MOBI', '01', '0'),
('91103166', 'VTYPE_MOBI', '01', '0'),
('91103168', 'VTYPE_MOBI', '01', '0'),
('91103169', 'VTYPE_MOBI', '01', '0'),
('91103170', 'VTYPE_MOBI', '01', '0'),
('91103171', 'VTYPE_MOBI', '01', '0'),
('91103172', 'VTYPE_MOBI', '01', '0'),
('91103173', 'VTYPE_MOBI', '01', '0'),
('91103174', 'VTYPE_MOBI', '01', '0'),
('91103175', 'VTYPE_MOBI', '01', '0'),
('91103176', 'VTYPE_MOBI', '01', '0'),
('91103177', 'VTYPE_MOBI', '01', '0'),
('91103178', 'VTYPE_MOBI', '01', '0'),
('91103179', 'VTYPE_MOBI', '01', '0'),
('91103180', 'VTYPE_MOBI', '01', '0'),
('91103181', 'VTYPE_MOBI', '01', '0'),
('91103182', 'VTYPE_MOBI', '01', '0'),
('91103183', 'VTYPE_MOBI', '01', '0'),
('91103184', 'VTYPE_MOBI', '01', '0'),
('91103185', 'VTYPE_MOBI', '01', '0'),
('91103186', 'VTYPE_MOBI', '01', '0'),
('91103187', 'VTYPE_MOBI', '01', '0'),
('91103188', 'VTYPE_MOBI', '01', '0'),
('91103189', 'VTYPE_MOBI', '01', '0'),
('91103190', 'VTYPE_MOBI', '01', '0'),
('91103191', 'VTYPE_MOBI', '01', '0'),
('91103192', 'VTYPE_MOBI', '01', '0'),
('91103193', 'VTYPE_MOBI', '01', '0'),
('91103194', 'VTYPE_MOBI', '01', '0'),
('91103195', 'VTYPE_MOBI', '01', '0'),
('91103196', 'VTYPE_MOBI', '01', '0'),
('91103197', 'VTYPE_MOBI', '01', '0'),
('91103198', 'VTYPE_MOBI', '01', '0'),
('91103199', 'VTYPE_MOBI', '01', '0'),
('91103200', 'VTYPE_MOBI', '01', '0'),
('91103201', 'VTYPE_MOBI', '01', '0'),
('91103202', 'VTYPE_MOBI', '01', '0'),
('91103203', 'VTYPE_MOBI', '01', '0'),
('91103204', 'VTYPE_MOBI', '01', '0'),
('91103205', 'VTYPE_MOBI', '01', '0'),
('91103206', 'VTYPE_MOBI', '01', '0'),
('91103208', 'VTYPE_MOBI', '01', '0'),
('91103209', 'VTYPE_MOBI', '01', '0'),
('91103210', 'VTYPE_MOBI', '01', '0'),
('91103211', 'VTYPE_MOBI', '01', '0'),
('91103212', 'VTYPE_MOBI', '01', '0'),
('91103213', 'VTYPE_MOBI', '01', '0'),
('91103214', 'VTYPE_MOBI', '01', '0'),
('91103215', 'VTYPE_MOBI', '01', '0'),
('91103216', 'VTYPE_MOBI', '01', '0'),
('91103217', 'VTYPE_MOBI', '01', '0'),
('91103218', 'VTYPE_MOBI', '01', '0'),
('91103219', 'VTYPE_MOBI', '01', '0'),
('91103220', 'VTYPE_MOBI', '01', '0'),
('91103221', 'VTYPE_MOBI', '01', '0'),
('91103222', 'MTYPE_SILV', '05', '0'),
('91103223', 'VTYPE_MOBI', '01', '0'),
('91103224', 'VTYPE_MOBI', '01', '0'),
('91103225', 'VTYPE_MOBI', '01', '0'),
('91103226', 'VTYPE_MOBI', '01', '0'),
('91103227', 'VTYPE_MOBI', '01', '0'),
('91103228', 'VTYPE_MOBI', '01', '0'),
('91103229', 'VTYPE_MOBI', '01', '0'),
('91103230', 'VTYPE_MOBI', '01', '0'),
('91103231', 'VTYPE_MOBI', '01', '0'),
('91103232', 'MTYPE_BRON', '04', '0'),
('91103233', 'VTYPE_MOBI', '01', '0'),
('91103234', 'VTYPE_MOBI', '01', '0'),
('91103235', 'VTYPE_MOBI', '01', '0'),
('91103236', 'VTYPE_MOBI', '01', '0'),
('91103237', 'VTYPE_MOBI', '01', '0'),
('91103238', 'VTYPE_MOBI', '01', '0'),
('91103239', 'VTYPE_MOBI', '01', '0'),
('91103240', 'VTYPE_MOBI', '01', '0'),
('91103241', 'VTYPE_MOBI', '01', '0'),
('91103242', 'VTYPE_MOBI', '01', '0'),
('91103243', 'VTYPE_MOBI', '01', '0'),
('91103244', 'VTYPE_MOBI', '01', '0'),
('91103245', 'VTYPE_MOBI', '01', '0'),
('91103246', 'VTYPE_MOBI', '01', '0'),
('91103248', 'VTYPE_MOBI', '01', '0'),
('91103249', 'VTYPE_MOBI', '01', '0'),
('91103250', 'VTYPE_MOBI', '01', '0'),
('91103251', 'VTYPE_MOBI', '01', '0'),
('91103252', 'VTYPE_MOBI', '01', '0'),
('91103253', 'VTYPE_MOBI', '01', '0'),
('91103254', 'VTYPE_MOBI', '01', '0'),
('91103258', 'VTYPE_MOBI', '01', '0'),
('91103260', 'VTYPE_MOBI', '01', '0'),
('91103262', 'VTYPE_MOBI', '01', '0'),
('91103264', 'VTYPE_MOBI', '01', '0'),
('91103266', 'VTYPE_MOBI', '01', '0'),
('91103268', 'VTYPE_MOBI', '01', '0'),
('91103270', 'VTYPE_MOBI', '01', '0'),
('91103272', 'VTYPE_MOBI', '01', '0'),
('91103276', 'VTYPE_MOBI', '01', '0'),
('91103278', 'VTYPE_MOBI', '01', '0'),
('91103280', 'VTYPE_MOBI', '01', '0'),
('91103282', 'VTYPE_MOBI', '01', '0'),
('91103284', 'VTYPE_MOBI', '01', '0'),
('91103286', 'VTYPE_MOBI', '01', '0'),
('91103288', 'VTYPE_MOBI', '01', '0'),
('91103290', 'VTYPE_MOBI', '01', '0'),
('91103292', 'VTYPE_MOBI', '01', '0'),
('91103294', 'VTYPE_MOBI', '01', '0'),
('91103296', 'VTYPE_MOBI', '01', '0'),
('91103300', 'MTYPE_BRON', '03', '0'),
('91103301', 'VTYPE_MOBI', '01', '0'),
('91103303', 'VTYPE_MOBI', '01', '0'),
('91103304', 'VTYPE_MOBI', '01', '0'),
('91103306', 'VTYPE_MOBI', '01', '0'),
('91103308', 'VTYPE_MOBI', '01', '0'),
('91103310', 'VTYPE_MOBI', '01', '0'),
('91103311', 'MTYPE_BRON', '03', '0'),
('91103313', 'VTYPE_MOBI', '01', '0'),
('91103314', 'VTYPE_MOBI', '01', '0'),
('91103316', 'VTYPE_MOBI', '01', '0'),
('91103318', 'VTYPE_MOBI', '01', '0'),
('91103320', 'VTYPE_MOBI', '01', '0'),
('91103322', 'MTYPE_BRON', '03', '0'),
('91103323', 'VTYPE_MOBI', '01', '0'),
('91103324', 'VTYPE_MOBI', '01', '0'),
('91103326', 'VTYPE_MOBI', '01', '0'),
('91103328', 'VTYPE_MOBI', '01', '0'),
('91103330', 'VTYPE_MOBI', '05', '0'),
('91103331', 'VTYPE_MOBI', '05', '0'),
('91103332', 'VTYPE_MOBI', '05', '0'),
('91103333', 'MTYPE_GOLD', '02', '0'),
('91103334', 'VTYPE_MOBI', '05', '0'),
('91103335', 'VTYPE_MOBI', '05', '0'),
('91103336', 'VTYPE_MOBI', '05', '0'),
('91103337', 'VTYPE_MOBI', '05', '0'),
('91103338', 'VTYPE_MOBI', '05', '0'),
('91103339', 'VTYPE_MOBI', '05', '0'),
('91103340', 'VTYPE_MOBI', '01', '0'),
('91103343', 'VTYPE_MOBI', '01', '0'),
('91103344', 'MTYPE_BRON', '03', '0'),
('91103346', 'VTYPE_MOBI', '01', '0'),
('91103348', 'VTYPE_MOBI', '01', '0'),
('91103350', 'VTYPE_MOBI', '01', '0'),
('91103352', 'VTYPE_MOBI', '01', '0'),
('91103353', 'VTYPE_MOBI', '01', '0'),
('91103355', 'MTYPE_BRON', '03', '0'),
('91103356', 'VTYPE_MOBI', '01', '0'),
('91103358', 'VTYPE_MOBI', '01', '0'),
('91103360', 'VTYPE_MOBI', '01', '0'),
('91103362', 'VTYPE_MOBI', '01', '0'),
('91103363', 'VTYPE_MOBI', '01', '0'),
('91103365', 'VTYPE_MOBI', '01', '0'),
('91103366', 'MTYPE_BRON', '03', '0'),
('91103368', 'VTYPE_MOBI', '01', '0'),
('91103370', 'VTYPE_MOBI', '01', '0'),
('91103372', 'VTYPE_MOBI', '01', '0'),
('91103373', 'VTYPE_MOBI', '01', '0'),
('91103375', 'VTYPE_MOBI', '01', '0'),
('91103377', 'MTYPE_BRON', '03', '0'),
('91103378', 'VTYPE_MOBI', '01', '0'),
('91103380', 'VTYPE_MOBI', '01', '0'),
('91103382', 'VTYPE_MOBI', '01', '0'),
('91103383', 'VTYPE_MOBI', '01', '0'),
('91103385', 'VTYPE_MOBI', '01', '0'),
('91103387', 'VTYPE_MOBI', '01', '0'),
('91103388', 'MTYPE_BRON', '03', '0'),
('91103390', 'VTYPE_MOBI', '01', '0'),
('91103392', 'VTYPE_MOBI', '01', '0'),
('91103393', 'VTYPE_MOBI', '01', '0'),
('91103395', 'VTYPE_MOBI', '01', '0'),
('91103397', 'VTYPE_MOBI', '01', '0'),
('91103399', 'MTYPE_BRON', '03', '0'),
('91103400', 'VTYPE_MOBI', '01', '0'),
('91103401', 'VTYPE_MOBI', '01', '0'),
('91103403', 'VTYPE_MOBI', '01', '0'),
('91103405', 'VTYPE_MOBI', '01', '0'),
('91103407', 'VTYPE_MOBI', '01', '0'),
('91103411', 'VTYPE_MOBI', '01', '0'),
('91103413', 'VTYPE_MOBI', '01', '0'),
('91103415', 'VTYPE_MOBI', '01', '0'),
('91103417', 'VTYPE_MOBI', '01', '0'),
('91103419', 'VTYPE_MOBI', '01', '0'),
('91103421', 'VTYPE_MOBI', '01', '0'),
('91103423', 'VTYPE_MOBI', '01', '0'),
('91103425', 'VTYPE_MOBI', '01', '0'),
('91103427', 'VTYPE_MOBI', '01', '0'),
('91103429', 'VTYPE_MOBI', '01', '0'),
('91103431', 'VTYPE_MOBI', '01', '0'),
('91103433', 'VTYPE_MOBI', '01', '0'),
('91103434', 'MTYPE_BRON', '04', '0'),
('91103435', 'VTYPE_MOBI', '01', '0'),
('91103437', 'VTYPE_MOBI', '01', '0'),
('91103439', 'VTYPE_MOBI', '01', '0'),
('91103441', 'VTYPE_MOBI', '01', '0'),
('91103443', 'VTYPE_MOBI', '01', '0'),
('91103444', 'MTYPE_SILV', '05', '0'),
('91103445', 'VTYPE_MOBI', '01', '0'),
('91103447', 'VTYPE_MOBI', '01', '0'),
('91103449', 'VTYPE_MOBI', '01', '0'),
('91103451', 'VTYPE_MOBI', '01', '0'),
('91103453', 'VTYPE_MOBI', '01', '0'),
('91103455', 'VTYPE_MOBI', '01', '0'),
('91103456', 'VTYPE_MOBI', '01', '0'),
('91103458', 'VTYPE_MOBI', '01', '0'),
('91103460', 'VTYPE_MOBI', '01', '0'),
('91103462', 'VTYPE_MOBI', '01', '0'),
('91103464', 'VTYPE_MOBI', '01', '0'),
('91103466', 'VTYPE_MOBI', '01', '0'),
('91103468', 'VTYPE_MOBI', '01', '0'),
('91103470', 'VTYPE_MOBI', '01', '0'),
('91103472', 'VTYPE_MOBI', '01', '0'),
('91103474', 'VTYPE_MOBI', '01', '0'),
('91103476', 'VTYPE_MOBI', '01', '0'),
('91103478', 'VTYPE_MOBI', '01', '0'),
('91103480', 'VTYPE_MOBI', '01', '0'),
('91103482', 'VTYPE_MOBI', '01', '0'),
('91103490', 'VTYPE_MOBI', '01', '0'),
('91103494', 'VTYPE_MOBI', '01', '0'),
('91103498', 'VTYPE_MOBI', '01', '0'),
('91103499', 'VTYPE_MOBI', '01', '0'),
('91103500', 'VTYPE_MOBI', '01', '0'),
('91103501', 'VTYPE_MOBI', '01', '0'),
('91103502', 'VTYPE_MOBI', '01', '0'),
('91103503', 'VTYPE_MOBI', '01', '0'),
('91103504', 'VTYPE_MOBI', '01', '0'),
('91103505', 'VTYPE_MOBI', '01', '0'),
('91103506', 'VTYPE_MOBI', '01', '0'),
('91103508', 'VTYPE_MOBI', '01', '0'),
('91103509', 'VTYPE_MOBI', '01', '0'),
('91103510', 'VTYPE_MOBI', '01', '0'),
('91103511', 'VTYPE_MOBI', '01', '0'),
('91103512', 'VTYPE_MOBI', '01', '0'),
('91103514', 'VTYPE_MOBI', '01', '0'),
('91103515', 'VTYPE_MOBI', '01', '0'),
('91103520', 'VTYPE_MOBI', '01', '0'),
('91103522', 'VTYPE_MOBI', '01', '0'),
('91103523', 'VTYPE_MOBI', '01', '0'),
('91103525', 'VTYPE_MOBI', '01', '0'),
('91103528', 'VTYPE_MOBI', '01', '0'),
('91103529', 'VTYPE_MOBI', '01', '0'),
('91103530', 'VTYPE_MOBI', '01', '0'),
('91103531', 'VTYPE_MOBI', '01', '0'),
('91103532', 'VTYPE_MOBI', '01', '0'),
('91103533', 'VTYPE_MOBI', '01', '0'),
('91103534', 'VTYPE_MOBI', '01', '0'),
('91103535', 'MTYPE_BRON', '04', '0'),
('91103536', 'VTYPE_MOBI', '01', '0'),
('91103537', 'VTYPE_MOBI', '01', '0'),
('91103539', 'VTYPE_MOBI', '01', '0'),
('91103540', 'VTYPE_MOBI', '01', '0'),
('91103543', 'VTYPE_MOBI', '01', '0'),
('91103544', 'VTYPE_MOBI', '01', '0'),
('91103545', 'VTYPE_MOBI', '01', '0'),
('91103546', 'VTYPE_MOBI', '01', '0'),
('91103547', 'VTYPE_MOBI', '01', '0'),
('91103548', 'VTYPE_MOBI', '01', '0'),
('91103549', 'VTYPE_MOBI', '01', '0'),
('91103550', 'VTYPE_MOBI', '01', '0'),
('91103551', 'VTYPE_MOBI', '01', '0'),
('91103552', 'VTYPE_MOBI', '01', '0'),
('91103553', 'VTYPE_MOBI', '01', '0'),
('91103554', 'VTYPE_MOBI', '01', '0'),
('91103555', 'MTYPE_SILV', '05', '0'),
('91103556', 'VTYPE_MOBI', '01', '0'),
('91103557', 'VTYPE_MOBI', '01', '0'),
('91103558', 'VTYPE_MOBI', '01', '0'),
('91103559', 'VTYPE_MOBI', '01', '0'),
('91103560', 'VTYPE_MOBI', '01', '0'),
('91103562', 'VTYPE_MOBI', '01', '0'),
('91103563', 'VTYPE_MOBI', '01', '0'),
('91103565', 'VTYPE_MOBI', '01', '0'),
('91103566', 'VTYPE_MOBI', '01', '0'),
('91103567', 'VTYPE_MOBI', '01', '0'),
('91103568', 'VTYPE_MOBI', '01', '0'),
('91103570', 'VTYPE_MOBI', '01', '0'),
('91103571', 'VTYPE_MOBI', '01', '0'),
('91103572', 'VTYPE_MOBI', '01', '0'),
('91103574', 'VTYPE_MOBI', '01', '0'),
('91103575', 'VTYPE_MOBI', '01', '0'),
('91103576', 'VTYPE_MOBI', '01', '0'),
('91103577', 'VTYPE_MOBI', '01', '0'),
('91103578', 'VTYPE_MOBI', '01', '0'),
('91103579', 'VTYPE_MOBI', '01', '0'),
('91103580', 'VTYPE_MOBI', '01', '0'),
('91103583', 'VTYPE_MOBI', '01', '0'),
('91103585', 'VTYPE_MOBI', '01', '0'),
('91103586', 'VTYPE_MOBI', '01', '0'),
('91103587', 'VTYPE_MOBI', '01', '0'),
('91103588', 'VTYPE_MOBI', '01', '0'),
('91103590', 'VTYPE_MOBI', '01', '0'),
('91103593', 'VTYPE_MOBI', '01', '0'),
('91103595', 'VTYPE_MOBI', '01', '0'),
('91103597', 'VTYPE_MOBI', '01', '0'),
('91103598', 'VTYPE_MOBI', '01', '0'),
('91103599', 'VTYPE_MOBI', '01', '0'),
('91103600', 'VTYPE_MOBI', '01', '0'),
('91103601', 'VTYPE_MOBI', '01', '0'),
('91103602', 'VTYPE_MOBI', '01', '0'),
('91103603', 'VTYPE_MOBI', '01', '0'),
('91103604', 'VTYPE_MOBI', '01', '0'),
('91103605', 'VTYPE_MOBI', '01', '0'),
('91103606', 'VTYPE_MOBI', '01', '0'),
('91103607', 'VTYPE_MOBI', '01', '0'),
('91103608', 'VTYPE_MOBI', '01', '0'),
('91103609', 'VTYPE_MOBI', '01', '0'),
('91103610', 'VTYPE_MOBI', '01', '0'),
('91103611', 'VTYPE_MOBI', '01', '0'),
('91103612', 'VTYPE_MOBI', '01', '0'),
('91103613', 'VTYPE_MOBI', '01', '0'),
('91103614', 'VTYPE_MOBI', '01', '0'),
('91103616', 'VTYPE_MOBI', '01', '0'),
('91103618', 'VTYPE_MOBI', '01', '0'),
('91103620', 'VTYPE_MOBI', '01', '0'),
('91103622', 'VTYPE_MOBI', '01', '0'),
('91103624', 'VTYPE_MOBI', '01', '0'),
('91103625', 'VTYPE_MOBI', '01', '0'),
('91103626', 'VTYPE_MOBI', '01', '0'),
('91103630', 'VTYPE_MOBI', '01', '0'),
('91103631', 'VTYPE_MOBI', '01', '0'),
('91103632', 'VTYPE_MOBI', '01', '0'),
('91103633', 'VTYPE_MOBI', '01', '0'),
('91103634', 'VTYPE_MOBI', '01', '0'),
('91103635', 'VTYPE_MOBI', '01', '0'),
('91103636', 'MTYPE_BRON', '04', '0'),
('91103637', 'VTYPE_MOBI', '01', '0'),
('91103638', 'VTYPE_MOBI', '01', '0'),
('91103639', 'VTYPE_MOBI', '01', '0'),
('91103640', 'VTYPE_MOBI', '01', '0'),
('91103642', 'VTYPE_MOBI', '01', '0'),
('91103644', 'VTYPE_MOBI', '01', '0'),
('91103645', 'VTYPE_MOBI', '01', '0'),
('91103646', 'VTYPE_MOBI', '01', '0'),
('91103647', 'VTYPE_MOBI', '01', '0'),
('91103648', 'VTYPE_MOBI', '01', '0'),
('91103650', 'VTYPE_MOBI', '01', '0'),
('91103654', 'VTYPE_MOBI', '01', '0'),
('91103655', 'VTYPE_MOBI', '01', '0'),
('91103656', 'VTYPE_MOBI', '01', '0'),
('91103658', 'VTYPE_MOBI', '01', '0'),
('91103660', 'VTYPE_MOBI', '01', '0'),
('91103661', 'VTYPE_MOBI', '01', '0'),
('91103662', 'VTYPE_MOBI', '01', '0'),
('91103663', 'VTYPE_MOBI', '01', '0'),
('91103666', 'MTYPE_SILV', '05', '0'),
('91103667', 'VTYPE_MOBI', '01', '0'),
('91103669', 'VTYPE_MOBI', '01', '0'),
('91103673', 'VTYPE_MOBI', '01', '0'),
('91103675', 'VTYPE_MOBI', '01', '0'),
('91103677', 'VTYPE_MOBI', '01', '0'),
('91103679', 'VTYPE_MOBI', '01', '0'),
('91103681', 'VTYPE_MOBI', '01', '0'),
('91103683', 'VTYPE_MOBI', '01', '0'),
('91103689', 'VTYPE_MOBI', '01', '0'),
('91103693', 'VTYPE_MOBI', '01', '0'),
('91103695', 'VTYPE_MOBI', '01', '0'),
('91103697', 'VTYPE_MOBI', '01', '0'),
('91103699', 'VTYPE_MOBI', '01', '0'),
('91103700', 'VTYPE_MOBI', '01', '0'),
('91103702', 'VTYPE_MOBI', '01', '0'),
('91103704', 'VTYPE_MOBI', '01', '0'),
('91103708', 'VTYPE_MOBI', '01', '0'),
('91103710', 'VTYPE_MOBI', '01', '0'),
('91103712', 'VTYPE_MOBI', '01', '0'),
('91103718', 'VTYPE_MOBI', '01', '0'),
('91103722', 'VTYPE_MOBI', '01', '0'),
('91103726', 'VTYPE_MOBI', '01', '0'),
('91103727', 'VTYPE_MOBI', '01', '0'),
('91103728', 'VTYPE_MOBI', '01', '0'),
('91103730', 'VTYPE_MOBI', '01', '0'),
('91103732', 'VTYPE_MOBI', '01', '0'),
('91103733', 'VTYPE_MOBI', '01', '0'),
('91103735', 'VTYPE_MOBI', '01', '0'),
('91103737', 'MTYPE_BRON', '04', '0'),
('91103738', 'VTYPE_MOBI', '01', '0'),
('91103740', 'VTYPE_MOBI', '01', '0'),
('91103742', 'VTYPE_MOBI', '01', '0'),
('91103744', 'VTYPE_MOBI', '01', '0'),
('91103748', 'VTYPE_MOBI', '01', '0'),
('91103758', 'VTYPE_MOBI', '01', '0'),
('91103764', 'VTYPE_MOBI', '01', '0'),
('91103766', 'VTYPE_MOBI', '01', '0'),
('91103770', 'VTYPE_MOBI', '01', '0'),
('91103772', 'VTYPE_MOBI', '01', '0'),
('91103773', 'VTYPE_MOBI', '01', '0'),
('91103775', 'VTYPE_MOBI', '01', '0'),
('91103777', 'MTYPE_SILV', '05', '0'),
('91103778', 'VTYPE_MOBI', '01', '0'),
('91103780', 'VTYPE_MOBI', '01', '0'),
('91103782', 'VTYPE_MOBI', '01', '0'),
('91103784', 'VTYPE_MOBI', '01', '0'),
('91103788', 'VTYPE_MOBI', '01', '0'),
('91103790', 'VTYPE_MOBI', '01', '0'),
('91103798', 'VTYPE_MOBI', '01', '0'),
('91103800', 'VTYPE_MOBI', '01', '0'),
('91103801', 'VTYPE_MOBI', '01', '0'),
('91103803', 'VTYPE_MOBI', '01', '0'),
('91103805', 'VTYPE_MOBI', '01', '0'),
('91103807', 'VTYPE_MOBI', '01', '0'),
('91103809', 'VTYPE_MOBI', '01', '0'),
('91103811', 'VTYPE_MOBI', '01', '0'),
('91103821', 'VTYPE_MOBI', '01', '0'),
('91103824', 'VTYPE_MOBI', '01', '0'),
('91103825', 'VTYPE_MOBI', '01', '0'),
('91103831', 'VTYPE_MOBI', '01', '0'),
('91103833', 'VTYPE_MOBI', '01', '0'),
('91103834', 'VTYPE_MOBI', '01', '0'),
('91103836', 'VTYPE_MOBI', '01', '0'),
('91103838', 'MTYPE_BRON', '04', '0'),
('91103839', 'VTYPE_MOBI', '01', '0'),
('91103841', 'VTYPE_MOBI', '01', '0'),
('91103843', 'VTYPE_MOBI', '01', '0'),
('91103845', 'VTYPE_MOBI', '01', '0'),
('91103849', 'VTYPE_MOBI', '01', '0'),
('91103855', 'VTYPE_MOBI', '01', '0'),
('91103869', 'VTYPE_MOBI', '01', '0'),
('91103871', 'VTYPE_MOBI', '01', '0'),
('91103877', 'VTYPE_MOBI', '01', '0'),
('91103879', 'VTYPE_MOBI', '01', '0'),
('91103881', 'VTYPE_MOBI', '01', '0'),
('91103883', 'VTYPE_MOBI', '01', '0'),
('91103884', 'VTYPE_MOBI', '01', '0'),
('91103886', 'VTYPE_MOBI', '01', '0'),
('91103888', 'MTYPE_SILV', '05', '0'),
('91103889', 'VTYPE_MOBI', '01', '0'),
('91103891', 'VTYPE_MOBI', '01', '0'),
('91103893', 'VTYPE_MOBI', '01', '0'),
('91103897', 'VTYPE_MOBI', '01', '0'),
('91103899', 'VTYPE_MOBI', '01', '0'),
('91103900', 'VTYPE_MOBI', '01', '0'),
('91103906', 'VTYPE_MOBI', '01', '0'),
('91103907', 'VTYPE_MOBI', '01', '0'),
('91103908', 'VTYPE_MOBI', '01', '0'),
('91103910', 'VTYPE_MOBI', '01', '0'),
('91103912', 'VTYPE_MOBI', '01', '0'),
('91103914', 'VTYPE_MOBI', '01', '0'),
('91103915', 'VTYPE_MOBI', '01', '0'),
('91103916', 'VTYPE_MOBI', '01', '0'),
('91103917', 'VTYPE_MOBI', '01', '0'),
('91103918', 'VTYPE_MOBI', '01', '0'),
('91103919', 'VTYPE_MOBI', '01', '0'),
('91103921', 'VTYPE_MOBI', '01', '0'),
('91103922', 'VTYPE_MOBI', '01', '0'),
('91103926', 'VTYPE_MOBI', '01', '0'),
('91103927', 'VTYPE_MOBI', '01', '0'),
('91103928', 'VTYPE_MOBI', '01', '0'),
('91103929', 'VTYPE_MOBI', '01', '0'),
('91103930', 'VTYPE_MOBI', '01', '0'),
('91103931', 'VTYPE_MOBI', '01', '0'),
('91103932', 'VTYPE_MOBI', '01', '0'),
('91103933', 'VTYPE_MOBI', '01', '0'),
('91103934', 'VTYPE_MOBI', '01', '0'),
('91103935', 'VTYPE_MOBI', '01', '0'),
('91103936', 'VTYPE_MOBI', '01', '0'),
('91103937', 'VTYPE_MOBI', '01', '0'),
('91103938', 'VTYPE_MOBI', '01', '0'),
('91103939', 'MTYPE_BRON', '04', '0'),
('91103940', 'VTYPE_MOBI', '01', '0'),
('91103941', 'VTYPE_MOBI', '01', '0'),
('91103942', 'VTYPE_MOBI', '01', '0'),
('91103943', 'VTYPE_MOBI', '01', '0'),
('91103944', 'VTYPE_MOBI', '01', '0'),
('91103948', 'VTYPE_MOBI', '01', '0'),
('91103949', 'VTYPE_MOBI', '01', '0'),
('91103950', 'VTYPE_MOBI', '01', '0'),
('91103951', 'VTYPE_MOBI', '01', '0'),
('91103952', 'VTYPE_MOBI', '01', '0'),
('91103955', 'VTYPE_MOBI', '01', '0'),
('91103956', 'VTYPE_MOBI', '01', '0'),
('91103957', 'VTYPE_MOBI', '01', '0'),
('91103958', 'VTYPE_MOBI', '01', '0'),
('91103959', 'VTYPE_MOBI', '01', '0'),
('91103960', 'VTYPE_MOBI', '01', '0'),
('91103963', 'VTYPE_MOBI', '01', '0'),
('91103964', 'VTYPE_MOBI', '01', '0'),
('91103966', 'VTYPE_MOBI', '01', '0'),
('91103968', 'VTYPE_MOBI', '01', '0'),
('91103969', 'VTYPE_MOBI', '01', '0'),
('91103970', 'VTYPE_MOBI', '01', '0'),
('91103971', 'VTYPE_MOBI', '01', '0'),
('91103974', 'VTYPE_MOBI', '01', '0'),
('91103977', 'VTYPE_MOBI', '01', '0'),
('91103978', 'VTYPE_MOBI', '01', '0'),
('91103979', 'VTYPE_MOBI', '01', '0'),
('91103980', 'VTYPE_MOBI', '01', '0'),
('91103981', 'VTYPE_MOBI', '01', '0'),
('91103983', 'VTYPE_MOBI', '01', '0'),
('91103985', 'VTYPE_MOBI', '01', '0'),
('91103987', 'VTYPE_MOBI', '01', '0'),
('91103988', 'VTYPE_MOBI', '01', '0'),
('91103989', 'VTYPE_MOBI', '01', '0'),
('91103991', 'VTYPE_MOBI', '01', '0'),
('91103992', 'VTYPE_MOBI', '01', '0'),
('91103993', 'VTYPE_MOBI', '01', '0'),
('91103994', 'VTYPE_MOBI', '01', '0'),
('91103995', 'VTYPE_MOBI', '01', '0'),
('91103997', 'VTYPE_MOBI', '01', '0'),
('91103998', 'VTYPE_MOBI', '01', '0'),
('91103999', 'MTYPE_SILV', '05', '0'),
('91104000', 'MTYPE_SILV', '05', '0'),
('91104001', 'VTYPE_MOBI', '01', '0'),
('91104002', 'VTYPE_MOBI', '01', '0'),
('91104003', 'VTYPE_MOBI', '01', '0'),
('91104004', 'VTYPE_MOBI', '01', '0'),
('91104005', 'VTYPE_MOBI', '01', '0'),
('91104006', 'VTYPE_MOBI', '01', '0'),
('91104007', 'VTYPE_MOBI', '01', '0'),
('91104008', 'VTYPE_MOBI', '01', '0'),
('91104009', 'VTYPE_MOBI', '01', '0'),
('91104010', 'VTYPE_MOBI', '01', '0'),
('91104011', 'VTYPE_MOBI', '01', '0'),
('91104012', 'VTYPE_MOBI', '01', '0'),
('91104013', 'VTYPE_MOBI', '01', '0'),
('91104014', 'VTYPE_MOBI', '01', '0'),
('91104015', 'VTYPE_MOBI', '01', '0'),
('91104016', 'VTYPE_MOBI', '01', '0'),
('91104017', 'VTYPE_MOBI', '01', '0'),
('91104018', 'VTYPE_MOBI', '01', '0'),
('91104019', 'VTYPE_MOBI', '01', '0'),
('91104020', 'VTYPE_MOBI', '01', '0'),
('91104021', 'VTYPE_MOBI', '01', '0'),
('91104022', 'VTYPE_MOBI', '01', '0'),
('91104023', 'VTYPE_MOBI', '01', '0'),
('91104024', 'VTYPE_MOBI', '01', '0'),
('91104025', 'VTYPE_MOBI', '01', '0'),
('91104026', 'VTYPE_MOBI', '01', '0'),
('91104027', 'VTYPE_MOBI', '01', '0'),
('91104028', 'VTYPE_MOBI', '01', '0'),
('91104029', 'VTYPE_MOBI', '01', '0'),
('91104030', 'VTYPE_MOBI', '01', '0'),
('91104033', 'VTYPE_MOBI', '01', '0'),
('91104035', 'VTYPE_MOBI', '01', '0'),
('91104037', 'VTYPE_MOBI', '01', '0'),
('91104040', 'MTYPE_BRON', '04', '0'),
('91104041', 'VTYPE_MOBI', '01', '0'),
('91104042', 'VTYPE_MOBI', '01', '0'),
('91104043', 'VTYPE_MOBI', '01', '0'),
('91104044', 'VTYPE_MOBI', '01', '0'),
('91104045', 'VTYPE_MOBI', '01', '0'),
('91104046', 'VTYPE_MOBI', '01', '0'),
('91104047', 'VTYPE_MOBI', '01', '0'),
('91104048', 'VTYPE_MOBI', '01', '0'),
('91104049', 'VTYPE_MOBI', '01', '0'),
('91104050', 'VTYPE_MOBI', '01', '0'),
('91104051', 'VTYPE_MOBI', '01', '0'),
('91104052', 'VTYPE_MOBI', '01', '0'),
('91104053', 'VTYPE_MOBI', '01', '0'),
('91104054', 'VTYPE_MOBI', '01', '0'),
('91104056', 'VTYPE_MOBI', '01', '0'),
('91104057', 'VTYPE_MOBI', '01', '0'),
('91104058', 'VTYPE_MOBI', '01', '0'),
('91104059', 'VTYPE_MOBI', '01', '0'),
('91104060', 'VTYPE_MOBI', '01', '0'),
('91104061', 'VTYPE_MOBI', '01', '0'),
('91104062', 'VTYPE_MOBI', '01', '0'),
('91104063', 'VTYPE_MOBI', '01', '0'),
('91104064', 'VTYPE_MOBI', '01', '0'),
('91104065', 'VTYPE_MOBI', '01', '0'),
('91104066', 'VTYPE_MOBI', '01', '0'),
('91104067', 'VTYPE_MOBI', '01', '0'),
('91104068', 'VTYPE_MOBI', '01', '0'),
('91104069', 'VTYPE_MOBI', '01', '0'),
('91104070', 'VTYPE_MOBI', '01', '0'),
('91104072', 'VTYPE_MOBI', '01', '0'),
('91104073', 'VTYPE_MOBI', '01', '0'),
('91104074', 'VTYPE_MOBI', '01', '0'),
('91104075', 'VTYPE_MOBI', '01', '0'),
('91104076', 'VTYPE_MOBI', '01', '0'),
('91104077', 'VTYPE_MOBI', '01', '0'),
('91104078', 'VTYPE_MOBI', '01', '0'),
('91104079', 'VTYPE_MOBI', '01', '0'),
('91104080', 'VTYPE_MOBI', '01', '0'),
('91104081', 'VTYPE_MOBI', '01', '0'),
('91104082', 'VTYPE_MOBI', '01', '0'),
('91104083', 'VTYPE_MOBI', '01', '0'),
('91104084', 'VTYPE_MOBI', '01', '0'),
('91104086', 'VTYPE_MOBI', '01', '0'),
('91104088', 'VTYPE_MOBI', '01', '0'),
('91104090', 'VTYPE_MOBI', '01', '0'),
('91104092', 'VTYPE_MOBI', '01', '0'),
('91104094', 'VTYPE_MOBI', '01', '0'),
('91104097', 'VTYPE_MOBI', '01', '0'),
('91104098', 'VTYPE_MOBI', '01', '0'),
('91104100', 'VTYPE_MOBI', '01', '0'),
('91104101', 'VTYPE_MOBI', '01', '0'),
('91104103', 'VTYPE_MOBI', '01', '0'),
('91104104', 'VTYPE_MOBI', '01', '0'),
('91104105', 'VTYPE_MOBI', '01', '0'),
('91104107', 'VTYPE_MOBI', '01', '0'),
('91104109', 'VTYPE_MOBI', '01', '0'),
('91104110', 'VTYPE_MOBI', '01', '0'),
('91104111', 'MTYPE_SILV', '05', '0'),
('91104112', 'VTYPE_MOBI', '01', '0'),
('91104114', 'VTYPE_MOBI', '01', '0'),
('91104115', 'VTYPE_MOBI', '01', '0'),
('91104117', 'VTYPE_MOBI', '01', '0'),
('91104121', 'VTYPE_MOBI', '01', '0'),
('91104123', 'VTYPE_MOBI', '01', '0'),
('91104125', 'VTYPE_MOBI', '01', '0'),
('91104129', 'VTYPE_MOBI', '01', '0'),
('91104131', 'VTYPE_MOBI', '01', '0'),
('91104133', 'VTYPE_MOBI', '01', '0'),
('91104135', 'VTYPE_MOBI', '01', '0'),
('91104137', 'VTYPE_MOBI', '01', '0'),
('91104139', 'VTYPE_MOBI', '01', '0'),
('91104141', 'MTYPE_BRON', '04', '0'),
('91104142', 'VTYPE_MOBI', '01', '0'),
('91104144', 'VTYPE_MOBI', '01', '0'),
('91104145', 'VTYPE_MOBI', '01', '0'),
('91104147', 'VTYPE_MOBI', '01', '0'),
('91104149', 'VTYPE_MOBI', '01', '0'),
('91104151', 'VTYPE_MOBI', '01', '0'),
('91104153', 'VTYPE_MOBI', '01', '0'),
('91104155', 'VTYPE_MOBI', '01', '0'),
('91104159', 'VTYPE_MOBI', '01', '0'),
('91104161', 'VTYPE_MOBI', '01', '0'),
('91104165', 'VTYPE_MOBI', '01', '0'),
('91104167', 'VTYPE_MOBI', '01', '0'),
('91104169', 'VTYPE_MOBI', '01', '0'),
('91104171', 'VTYPE_MOBI', '01', '0'),
('91104175', 'VTYPE_MOBI', '01', '0'),
('91104176', 'VTYPE_MOBI', '01', '0'),
('91104177', 'VTYPE_MOBI', '01', '0'),
('91104179', 'VTYPE_MOBI', '01', '0'),
('91104181', 'VTYPE_MOBI', '01', '0'),
('91104183', 'VTYPE_MOBI', '01', '0'),
('91104185', 'VTYPE_MOBI', '01', '0'),
('91104187', 'VTYPE_MOBI', '01', '0'),
('91104189', 'VTYPE_MOBI', '01', '0'),
('91104191', 'VTYPE_MOBI', '01', '0'),
('91104193', 'VTYPE_MOBI', '01', '0'),
('91104195', 'VTYPE_MOBI', '01', '0'),
('91104197', 'VTYPE_MOBI', '01', '0'),
('91104199', 'VTYPE_MOBI', '01', '0'),
('91104200', 'VTYPE_MOBI', '01', '0'),
('91104202', 'VTYPE_MOBI', '01', '0'),
('91104204', 'VTYPE_MOBI', '01', '0'),
('91104208', 'VTYPE_MOBI', '01', '0'),
('91104210', 'VTYPE_MOBI', '01', '0'),
('91104211', 'VTYPE_MOBI', '01', '0'),
('91104212', 'VTYPE_MOBI', '01', '0'),
('91104216', 'VTYPE_MOBI', '01', '0'),
('91104220', 'VTYPE_MOBI', '01', '0'),
('91104222', 'MTYPE_SILV', '05', '0'),
('91104224', 'VTYPE_MOBI', '01', '0'),
('91104226', 'VTYPE_MOBI', '01', '0'),
('91104228', 'VTYPE_MOBI', '01', '0'),
('91104230', 'VTYPE_MOBI', '01', '0'),
('91104232', 'VTYPE_MOBI', '01', '0'),
('91104234', 'VTYPE_MOBI', '01', '0'),
('91104238', 'VTYPE_MOBI', '01', '0'),
('91104240', 'VTYPE_MOBI', '01', '0'),
('91104242', 'MTYPE_BRON', '04', '0'),
('91104243', 'VTYPE_MOBI', '01', '0'),
('91104244', 'VTYPE_MOBI', '01', '0'),
('91104246', 'VTYPE_MOBI', '01', '0'),
('91104248', 'VTYPE_MOBI', '01', '0'),
('91104250', 'VTYPE_MOBI', '01', '0'),
('91104251', 'VTYPE_MOBI', '01', '0'),
('91104252', 'VTYPE_MOBI', '01', '0'),
('91104253', 'VTYPE_MOBI', '01', '0'),
('91104254', 'VTYPE_MOBI', '01', '0'),
('91104255', 'VTYPE_MOBI', '01', '0'),
('91104256', 'VTYPE_MOBI', '01', '0'),
('91104261', 'VTYPE_MOBI', '01', '0'),
('91104262', 'VTYPE_MOBI', '01', '0'),
('91104264', 'VTYPE_MOBI', '01', '0'),
('91104266', 'VTYPE_MOBI', '01', '0'),
('91104267', 'VTYPE_MOBI', '01', '0'),
('91104268', 'VTYPE_MOBI', '01', '0'),
('91104269', 'VTYPE_MOBI', '01', '0'),
('91104271', 'VTYPE_MOBI', '01', '0'),
('91104274', 'VTYPE_MOBI', '01', '0'),
('91104277', 'VTYPE_MOBI', '01', '0'),
('91104278', 'VTYPE_MOBI', '01', '0'),
('91104280', 'VTYPE_MOBI', '01', '0'),
('91104281', 'VTYPE_MOBI', '01', '0'),
('91104282', 'VTYPE_MOBI', '01', '0'),
('91104283', 'VTYPE_MOBI', '01', '0'),
('91104284', 'VTYPE_MOBI', '01', '0'),
('91104285', 'VTYPE_MOBI', '01', '0'),
('91104286', 'VTYPE_MOBI', '01', '0'),
('91104287', 'VTYPE_MOBI', '01', '0'),
('91104288', 'VTYPE_MOBI', '01', '0'),
('91104289', 'VTYPE_MOBI', '01', '0'),
('91104291', 'VTYPE_MOBI', '01', '0'),
('91104292', 'VTYPE_MOBI', '01', '0'),
('91104297', 'VTYPE_MOBI', '01', '0'),
('91104298', 'VTYPE_MOBI', '01', '0'),
('91104299', 'VTYPE_MOBI', '01', '0'),
('91104300', 'VTYPE_MOBI', '01', '0'),
('91104301', 'VTYPE_MOBI', '01', '0'),
('91104302', 'VTYPE_MOBI', '01', '0'),
('91104304', 'VTYPE_MOBI', '01', '0'),
('91104305', 'VTYPE_MOBI', '01', '0'),
('91104307', 'VTYPE_MOBI', '01', '0'),
('91104308', 'VTYPE_MOBI', '01', '0'),
('91104309', 'VTYPE_MOBI', '01', '0'),
('91104310', 'VTYPE_MOBI', '01', '0'),
('91104311', 'VTYPE_MOBI', '01', '0'),
('91104313', 'VTYPE_MOBI', '01', '0'),
('91104314', 'VTYPE_MOBI', '01', '0'),
('91104315', 'VTYPE_MOBI', '01', '0'),
('91104320', 'VTYPE_MOBI', '01', '0'),
('91104321', 'VTYPE_MOBI', '01', '0'),
('91104322', 'VTYPE_MOBI', '01', '0'),
('91104323', 'VTYPE_MOBI', '01', '0'),
('91104324', 'VTYPE_MOBI', '01', '0'),
('91104325', 'VTYPE_MOBI', '01', '0'),
('91104326', 'VTYPE_MOBI', '01', '0'),
('91104327', 'VTYPE_MOBI', '01', '0'),
('91104330', 'VTYPE_MOBI', '01', '0'),
('91104331', 'VTYPE_MOBI', '01', '0'),
('91104332', 'VTYPE_MOBI', '01', '0'),
('91104334', 'VTYPE_MOBI', '01', '0'),
('91104335', 'VTYPE_MOBI', '01', '0'),
('91104336', 'VTYPE_MOBI', '01', '0'),
('91104337', 'VTYPE_MOBI', '01', '0'),
('91104338', 'VTYPE_MOBI', '01', '0'),
('91104339', 'VTYPE_MOBI', '01', '0'),
('91104340', 'VTYPE_MOBI', '01', '0'),
('91104341', 'VTYPE_MOBI', '01', '0'),
('91104342', 'VTYPE_MOBI', '01', '0'),
('91104343', 'MTYPE_BRON', '04', '0'),
('91104344', 'VTYPE_MOBI', '01', '0'),
('91104345', 'VTYPE_MOBI', '01', '0'),
('91104346', 'VTYPE_MOBI', '01', '0'),
('91104348', 'VTYPE_MOBI', '01', '0'),
('91104349', 'VTYPE_MOBI', '01', '0'),
('91104350', 'VTYPE_MOBI', '01', '0'),
('91104353', 'VTYPE_MOBI', '01', '0'),
('91104354', 'VTYPE_MOBI', '01', '0'),
('91104355', 'VTYPE_MOBI', '01', '0'),
('91104356', 'VTYPE_MOBI', '01', '0'),
('91104357', 'VTYPE_MOBI', '01', '0'),
('91104358', 'VTYPE_MOBI', '01', '0'),
('91104361', 'VTYPE_MOBI', '01', '0'),
('91104363', 'VTYPE_MOBI', '01', '0'),
('91104364', 'VTYPE_MOBI', '01', '0'),
('91104366', 'VTYPE_MOBI', '01', '0'),
('91104368', 'VTYPE_MOBI', '01', '0'),
('91104369', 'VTYPE_MOBI', '01', '0'),
('91104371', 'VTYPE_MOBI', '01', '0'),
('91104373', 'VTYPE_MOBI', '01', '0'),
('91104374', 'VTYPE_MOBI', '01', '0'),
('91104375', 'VTYPE_MOBI', '01', '0'),
('91104376', 'VTYPE_MOBI', '01', '0'),
('91104377', 'VTYPE_MOBI', '01', '0'),
('91104378', 'VTYPE_MOBI', '01', '0'),
('91104379', 'VTYPE_MOBI', '01', '0'),
('91104380', 'VTYPE_MOBI', '01', '0'),
('91104381', 'VTYPE_MOBI', '01', '0'),
('91104382', 'VTYPE_MOBI', '01', '0'),
('91104383', 'VTYPE_MOBI', '01', '0'),
('91104384', 'VTYPE_MOBI', '01', '0'),
('91104387', 'VTYPE_MOBI', '01', '0'),
('91104388', 'VTYPE_MOBI', '01', '0'),
('91104389', 'VTYPE_MOBI', '01', '0'),
('91104391', 'VTYPE_MOBI', '01', '0'),
('91104392', 'VTYPE_MOBI', '01', '0'),
('91104393', 'VTYPE_MOBI', '01', '0'),
('91104394', 'VTYPE_MOBI', '01', '0'),
('91104395', 'VTYPE_MOBI', '01', '0'),
('91104398', 'VTYPE_MOBI', '01', '0'),
('91104399', 'VTYPE_MOBI', '01', '0'),
('91104400', 'MTYPE_BRON', '03', '0'),
('91104401', 'VTYPE_MOBI', '01', '0'),
('91104402', 'VTYPE_MOBI', '01', '0'),
('91104403', 'VTYPE_MOBI', '01', '0'),
('91104404', 'VTYPE_MOBI', '01', '0'),
('91104405', 'VTYPE_MOBI', '01', '0'),
('91104406', 'VTYPE_MOBI', '01', '0'),
('91104407', 'VTYPE_MOBI', '01', '0'),
('91104408', 'VTYPE_MOBI', '01', '0'),
('91104409', 'VTYPE_MOBI', '01', '0'),
('91104410', 'VTYPE_MOBI', '01', '0'),
('91104411', 'MTYPE_BRON', '03', '0'),
('91104413', 'VTYPE_MOBI', '01', '0'),
('91104415', 'VTYPE_MOBI', '01', '0'),
('91104416', 'VTYPE_MOBI', '01', '0'),
('91104417', 'VTYPE_MOBI', '01', '0'),
('91104418', 'VTYPE_MOBI', '01', '0'),
('91104419', 'VTYPE_MOBI', '01', '0'),
('91104420', 'VTYPE_MOBI', '01', '0'),
('91104421', 'VTYPE_MOBI', '01', '0'),
('91104422', 'MTYPE_BRON', '03', '0'),
('91104423', 'VTYPE_MOBI', '01', '0'),
('91104424', 'VTYPE_MOBI', '01', '0'),
('91104425', 'VTYPE_MOBI', '01', '0'),
('91104427', 'VTYPE_MOBI', '01', '0'),
('91104429', 'VTYPE_MOBI', '01', '0'),
('91104431', 'VTYPE_MOBI', '01', '0'),
('91104433', 'MTYPE_BRON', '03', '0'),
('91104434', 'VTYPE_MOBI', '01', '0'),
('91104435', 'VTYPE_MOBI', '01', '0'),
('91104437', 'VTYPE_MOBI', '01', '0'),
('91104438', 'VTYPE_MOBI', '01', '0'),
('91104440', 'VTYPE_MOBI', '05', '0'),
('91104441', 'VTYPE_MOBI', '05', '0'),
('91104442', 'VTYPE_MOBI', '05', '0'),
('91104443', 'VTYPE_MOBI', '05', '0'),
('91104444', 'MTYPE_GOLD', '02', '0'),
('91104445', 'VTYPE_MOBI', '05', '0'),
('91104446', 'VTYPE_MOBI', '05', '0'),
('91104447', 'VTYPE_MOBI', '05', '0'),
('91104448', 'VTYPE_MOBI', '05', '0'),
('91104449', 'VTYPE_MOBI', '05', '0'),
('91104451', 'VTYPE_MOBI', '01', '0'),
('91104453', 'VTYPE_MOBI', '01', '0'),
('91104454', 'VTYPE_MOBI', '01', '0'),
('91104455', 'MTYPE_BRON', '03', '0'),
('91104461', 'VTYPE_MOBI', '01', '0'),
('91104463', 'VTYPE_MOBI', '01', '0'),
('91104464', 'VTYPE_MOBI', '01', '0'),
('91104466', 'MTYPE_BRON', '03', '0'),
('91104467', 'VTYPE_MOBI', '01', '0'),
('91104469', 'VTYPE_MOBI', '01', '0'),
('91104471', 'VTYPE_MOBI', '01', '0'),
('91104473', 'VTYPE_MOBI', '01', '0'),
('91104474', 'VTYPE_MOBI', '01', '0'),
('91104476', 'VTYPE_MOBI', '01', '0'),
('91104477', 'MTYPE_BRON', '03', '0'),
('91104479', 'VTYPE_MOBI', '01', '0'),
('91104481', 'VTYPE_MOBI', '01', '0'),
('91104483', 'VTYPE_MOBI', '01', '0'),
('91104484', 'VTYPE_MOBI', '01', '0'),
('91104486', 'VTYPE_MOBI', '01', '0'),
('91104488', 'MTYPE_BRON', '03', '0'),
('91104489', 'VTYPE_MOBI', '01', '0'),
('91104491', 'VTYPE_MOBI', '01', '0'),
('91104493', 'VTYPE_MOBI', '01', '0'),
('91104494', 'VTYPE_MOBI', '01', '0'),
('91104496', 'VTYPE_MOBI', '01', '0'),
('91104498', 'VTYPE_MOBI', '01', '0'),
('91104499', 'MTYPE_BRON', '03', '0'),
('91104500', 'VTYPE_MOBI', '01', '0'),
('91104501', 'VTYPE_MOBI', '01', '0'),
('91104502', 'VTYPE_MOBI', '01', '0'),
('91104504', 'VTYPE_MOBI', '01', '0'),
('91104506', 'VTYPE_MOBI', '01', '0'),
('91104510', 'VTYPE_MOBI', '01', '0'),
('91104512', 'VTYPE_MOBI', '01', '0'),
('91104518', 'VTYPE_MOBI', '01', '0'),
('91104520', 'VTYPE_MOBI', '01', '0'),
('91104522', 'VTYPE_MOBI', '01', '0'),
('91104524', 'VTYPE_MOBI', '01', '0'),
('91104526', 'VTYPE_MOBI', '01', '0'),
('91104528', 'VTYPE_MOBI', '01', '0'),
('91104532', 'VTYPE_MOBI', '01', '0'),
('91104534', 'VTYPE_MOBI', '01', '0'),
('91104538', 'VTYPE_MOBI', '01', '0'),
('91104540', 'VTYPE_MOBI', '01', '0'),
('91104542', 'VTYPE_MOBI', '01', '0'),
('91104544', 'VTYPE_MOBI', '01', '0'),
('91104545', 'MTYPE_BRON', '04', '0'),
('91104546', 'VTYPE_MOBI', '01', '0'),
('91104552', 'VTYPE_MOBI', '01', '0'),
('91104554', 'VTYPE_MOBI', '01', '0'),
('91104555', 'MTYPE_SILV', '05', '0'),
('91104556', 'VTYPE_MOBI', '01', '0'),
('91104558', 'VTYPE_MOBI', '01', '0'),
('91104560', 'VTYPE_MOBI', '01', '0'),
('91104564', 'VTYPE_MOBI', '01', '0'),
('91104566', 'VTYPE_MOBI', '01', '0'),
('91104567', 'VTYPE_MOBI', '01', '0'),
('91104569', 'VTYPE_MOBI', '01', '0'),
('91104573', 'VTYPE_MOBI', '01', '0'),
('91104575', 'VTYPE_MOBI', '01', '0'),
('91104577', 'VTYPE_MOBI', '01', '0'),
('91104579', 'VTYPE_MOBI', '01', '0'),
('91104581', 'VTYPE_MOBI', '01', '0'),
('91104583', 'VTYPE_MOBI', '01', '0'),
('91104585', 'VTYPE_MOBI', '01', '0'),
('91104587', 'VTYPE_MOBI', '01', '0'),
('91104589', 'VTYPE_MOBI', '01', '0'),
('91104591', 'VTYPE_MOBI', '01', '0'),
('91104595', 'VTYPE_MOBI', '01', '0'),
('91104599', 'VTYPE_MOBI', '01', '0'),
('91104600', 'VTYPE_MOBI', '01', '0'),
('91104606', 'VTYPE_MOBI', '01', '0'),
('91104608', 'VTYPE_MOBI', '01', '0'),
('91104610', 'VTYPE_MOBI', '01', '0'),
('91104612', 'VTYPE_MOBI', '01', '0'),
('91104614', 'VTYPE_MOBI', '01', '0'),
('91104616', 'VTYPE_MOBI', '01', '0'),
('91104621', 'VTYPE_MOBI', '01', '0'),
('91104639', 'VTYPE_MOBI', '01', '0'),
('91104641', 'VTYPE_MOBI', '01', '0'),
('91104643', 'VTYPE_MOBI', '01', '0'),
('91104644', 'VTYPE_MOBI', '01', '0'),
('91104646', 'MTYPE_BRON', '04', '0'),
('91104647', 'VTYPE_MOBI', '01', '0'),
('91104649', 'VTYPE_MOBI', '01', '0'),
('91104651', 'VTYPE_MOBI', '01', '0'),
('91104653', 'VTYPE_MOBI', '01', '0'),
('91104655', 'VTYPE_MOBI', '01', '0'),
('91104657', 'VTYPE_MOBI', '01', '0'),
('91104661', 'VTYPE_MOBI', '01', '0'),
('91104664', 'VTYPE_MOBI', '01', '0'),
('91104666', 'MTYPE_SILV', '05', '0'),
('91104667', 'VTYPE_MOBI', '01', '0'),
('91104671', 'VTYPE_MOBI', '01', '0'),
('91104677', 'VTYPE_MOBI', '01', '0'),
('91104678', 'VTYPE_MOBI', '01', '0'),
('91104679', 'VTYPE_MOBI', '01', '0'),
('91104681', 'VTYPE_MOBI', '01', '0'),
('91104685', 'VTYPE_MOBI', '01', '0'),
('91104691', 'VTYPE_MOBI', '01', '0'),
('91104692', 'VTYPE_MOBI', '01', '0'),
('91104694', 'VTYPE_MOBI', '01', '0'),
('91104696', 'VTYPE_MOBI', '01', '0'),
('91104698', 'VTYPE_MOBI', '01', '0'),
('91104699', 'VTYPE_MOBI', '01', '0'),
('91104700', 'VTYPE_MOBI', '01', '0'),
('91104703', 'VTYPE_MOBI', '01', '0'),
('91104707', 'VTYPE_MOBI', '01', '0'),
('91104708', 'VTYPE_MOBI', '01', '0'),
('91104710', 'VTYPE_MOBI', '01', '0'),
('91104714', 'VTYPE_MOBI', '01', '0'),
('91104717', 'VTYPE_MOBI', '01', '0'),
('91104721', 'VTYPE_MOBI', '01', '0'),
('91104722', 'VTYPE_MOBI', '01', '0'),
('91104727', 'VTYPE_MOBI', '01', '0'),
('91104730', 'VTYPE_MOBI', '01', '0'),
('91104731', 'VTYPE_MOBI', '01', '0'),
('91104732', 'VTYPE_MOBI', '01', '0'),
('91104733', 'VTYPE_MOBI', '01', '0'),
('91104735', 'VTYPE_MOBI', '01', '0'),
('91104736', 'VTYPE_MOBI', '01', '0'),
('91104737', 'VTYPE_MOBI', '01', '0'),
('91104739', 'VTYPE_MOBI', '01', '0'),
('91104740', 'VTYPE_MOBI', '01', '0'),
('91104741', 'VTYPE_MOBI', '01', '0'),
('91104742', 'VTYPE_MOBI', '01', '0'),
('91104744', 'VTYPE_MOBI', '01', '0'),
('91104745', 'VTYPE_MOBI', '01', '0'),
('91104746', 'VTYPE_MOBI', '01', '0'),
('91104747', 'MTYPE_BRON', '04', '0'),
('91104748', 'VTYPE_MOBI', '01', '0'),
('91104749', 'VTYPE_MOBI', '01', '0'),
('91104750', 'VTYPE_MOBI', '01', '0'),
('91104753', 'VTYPE_MOBI', '01', '0'),
('91104754', 'VTYPE_MOBI', '01', '0'),
('91104755', 'VTYPE_MOBI', '01', '0'),
('91104756', 'VTYPE_MOBI', '01', '0'),
('91104757', 'VTYPE_MOBI', '01', '0'),
('91104758', 'VTYPE_MOBI', '01', '0'),
('91104760', 'VTYPE_MOBI', '01', '0'),
('91104761', 'VTYPE_MOBI', '01', '0'),
('91104762', 'VTYPE_MOBI', '01', '0'),
('91104766', 'VTYPE_MOBI', '01', '0'),
('91104767', 'VTYPE_MOBI', '01', '0'),
('91104768', 'VTYPE_MOBI', '01', '0'),
('91104769', 'VTYPE_MOBI', '01', '0'),
('91104770', 'VTYPE_MOBI', '01', '0'),
('91104771', 'VTYPE_MOBI', '01', '0'),
('91104772', 'VTYPE_MOBI', '01', '0'),
('91104773', 'VTYPE_MOBI', '01', '0'),
('91104774', 'VTYPE_MOBI', '01', '0'),
('91104775', 'VTYPE_MOBI', '01', '0'),
('91104776', 'VTYPE_MOBI', '01', '0'),
('91104777', 'MTYPE_SILV', '05', '0'),
('91104778', 'VTYPE_MOBI', '01', '0'),
('91104779', 'VTYPE_MOBI', '01', '0'),
('91104780', 'VTYPE_MOBI', '01', '0'),
('91104782', 'VTYPE_MOBI', '01', '0'),
('91104785', 'VTYPE_MOBI', '01', '0'),
('91104787', 'VTYPE_MOBI', '01', '0'),
('91104788', 'VTYPE_MOBI', '01', '0'),
('91104789', 'VTYPE_MOBI', '01', '0'),
('91104790', 'VTYPE_MOBI', '01', '0'),
('91104795', 'VTYPE_MOBI', '01', '0'),
('91104796', 'VTYPE_MOBI', '01', '0'),
('91104797', 'VTYPE_MOBI', '01', '0'),
('91104798', 'VTYPE_MOBI', '01', '0'),
('91104799', 'VTYPE_MOBI', '01', '0'),
('91104800', 'VTYPE_MOBI', '01', '0'),
('91104802', 'VTYPE_MOBI', '01', '0'),
('91104803', 'VTYPE_MOBI', '01', '0'),
('91104804', 'VTYPE_MOBI', '01', '0'),
('91104806', 'VTYPE_MOBI', '01', '0'),
('91104807', 'VTYPE_MOBI', '01', '0'),
('91104808', 'VTYPE_MOBI', '01', '0'),
('91104809', 'VTYPE_MOBI', '01', '0'),
('91104810', 'VTYPE_MOBI', '01', '0'),
('91104811', 'VTYPE_MOBI', '01', '0'),
('91104812', 'VTYPE_MOBI', '01', '0'),
('91104813', 'VTYPE_MOBI', '01', '0'),
('91104814', 'VTYPE_MOBI', '01', '0'),
('91104816', 'VTYPE_MOBI', '01', '0'),
('91104818', 'VTYPE_MOBI', '01', '0'),
('91104819', 'VTYPE_MOBI', '01', '0'),
('91104820', 'VTYPE_MOBI', '01', '0'),
('91104824', 'VTYPE_MOBI', '01', '0'),
('91104826', 'VTYPE_MOBI', '01', '0'),
('91104828', 'VTYPE_MOBI', '01', '0'),
('91104830', 'VTYPE_MOBI', '01', '0'),
('91104831', 'VTYPE_MOBI', '01', '0'),
('91104834', 'VTYPE_MOBI', '01', '0'),
('91104835', 'VTYPE_MOBI', '01', '0'),
('91104838', 'VTYPE_MOBI', '01', '0'),
('91104840', 'VTYPE_MOBI', '01', '0'),
('91104841', 'VTYPE_MOBI', '01', '0'),
('91104842', 'VTYPE_MOBI', '01', '0'),
('91104843', 'VTYPE_MOBI', '01', '0'),
('91104844', 'VTYPE_MOBI', '01', '0'),
('91104845', 'VTYPE_MOBI', '01', '0'),
('91104846', 'VTYPE_MOBI', '01', '0'),
('91104847', 'VTYPE_MOBI', '01', '0'),
('91104848', 'MTYPE_BRON', '04', '0'),
('91104849', 'VTYPE_MOBI', '01', '0'),
('91104850', 'VTYPE_MOBI', '01', '0'),
('91104851', 'VTYPE_MOBI', '01', '0'),
('91104853', 'VTYPE_MOBI', '01', '0'),
('91104854', 'VTYPE_MOBI', '01', '0'),
('91104855', 'VTYPE_MOBI', '01', '0'),
('91104857', 'VTYPE_MOBI', '01', '0'),
('91104858', 'VTYPE_MOBI', '01', '0'),
('91104859', 'VTYPE_MOBI', '01', '0'),
('91104861', 'VTYPE_MOBI', '01', '0'),
('91104863', 'VTYPE_MOBI', '01', '0'),
('91104865', 'VTYPE_MOBI', '01', '0'),
('91104869', 'VTYPE_MOBI', '01', '0'),
('91104875', 'VTYPE_MOBI', '01', '0'),
('91104877', 'VTYPE_MOBI', '01', '0'),
('91104879', 'VTYPE_MOBI', '01', '0'),
('91104881', 'VTYPE_MOBI', '01', '0'),
('91104883', 'VTYPE_MOBI', '01', '0'),
('91104885', 'VTYPE_MOBI', '01', '0'),
('91104887', 'VTYPE_MOBI', '01', '0'),
('91104888', 'MTYPE_SILV', '05', '0'),
('91104890', 'VTYPE_MOBI', '01', '0'),
('91104896', 'VTYPE_MOBI', '01', '0'),
('91104898', 'VTYPE_MOBI', '01', '0'),
('91104900', 'VTYPE_MOBI', '01', '0'),
('91104901', 'VTYPE_MOBI', '01', '0'),
('91104902', 'VTYPE_MOBI', '01', '0'),
('91104903', 'VTYPE_MOBI', '01', '0'),
('91104905', 'VTYPE_MOBI', '01', '0'),
('91104909', 'VTYPE_MOBI', '01', '0'),
('91104915', 'VTYPE_MOBI', '01', '0'),
('91104919', 'VTYPE_MOBI', '01', '0'),
('91104923', 'VTYPE_MOBI', '01', '0'),
('91104929', 'VTYPE_MOBI', '01', '0'),
('91104931', 'VTYPE_MOBI', '01', '0'),
('91104935', 'VTYPE_MOBI', '01', '0'),
('91104937', 'VTYPE_MOBI', '01', '0'),
('91104939', 'VTYPE_MOBI', '01', '0'),
('91104941', 'VTYPE_MOBI', '01', '0'),
('91104946', 'VTYPE_MOBI', '01', '0'),
('91104948', 'VTYPE_MOBI', '01', '0'),
('91104949', 'MTYPE_BRON', '04', '0'),
('91104951', 'VTYPE_MOBI', '01', '0'),
('91104953', 'VTYPE_MOBI', '01', '0'),
('91104955', 'VTYPE_MOBI', '01', '0'),
('91104959', 'VTYPE_MOBI', '01', '0'),
('91104965', 'VTYPE_MOBI', '01', '0'),
('91104967', 'VTYPE_MOBI', '01', '0'),
('91104969', 'VTYPE_MOBI', '01', '0'),
('91104971', 'VTYPE_MOBI', '01', '0'),
('91104973', 'VTYPE_MOBI', '01', '0'),
('91104977', 'VTYPE_MOBI', '01', '0'),
('91104979', 'VTYPE_MOBI', '01', '0'),
('91104981', 'VTYPE_MOBI', '01', '0'),
('91104983', 'VTYPE_MOBI', '01', '0'),
('91104985', 'VTYPE_MOBI', '01', '0'),
('91104989', 'VTYPE_MOBI', '01', '0'),
('91104991', 'VTYPE_MOBI', '01', '0'),
('91104994', 'VTYPE_MOBI', '01', '0'),
('91104996', 'VTYPE_MOBI', '01', '0'),
('91104998', 'VTYPE_MOBI', '01', '0'),
('91104999', 'MTYPE_SILV', '05', '0'),
('91105000', 'MTYPE_SILV', '05', '0'),
('91105001', 'VTYPE_MOBI', '01', '0'),
('91105003', 'VTYPE_MOBI', '01', '0'),
('91105005', 'VTYPE_MOBI', '01', '0'),
('91105006', 'VTYPE_MOBI', '01', '0'),
('91105008', 'VTYPE_MOBI', '01', '0'),
('91105010', 'VTYPE_MOBI', '01', '0'),
('91105012', 'VTYPE_MOBI', '01', '0'),
('91105014', 'VTYPE_MOBI', '01', '0'),
('91105016', 'VTYPE_MOBI', '01', '0'),
('91105018', 'VTYPE_MOBI', '01', '0'),
('91105020', 'VTYPE_MOBI', '01', '0'),
('91105022', 'VTYPE_MOBI', '01', '0'),
('91105024', 'VTYPE_MOBI', '01', '0'),
('91105026', 'VTYPE_MOBI', '01', '0'),
('91105028', 'VTYPE_MOBI', '01', '0'),
('91105030', 'VTYPE_MOBI', '01', '0'),
('91105032', 'VTYPE_MOBI', '01', '0'),
('91105034', 'VTYPE_MOBI', '01', '0'),
('91105036', 'VTYPE_MOBI', '01', '0'),
('91105038', 'VTYPE_MOBI', '01', '0'),
('91105040', 'VTYPE_MOBI', '01', '0'),
('91105042', 'VTYPE_MOBI', '01', '0'),
('91105044', 'VTYPE_MOBI', '01', '0'),
('91105046', 'VTYPE_MOBI', '01', '0'),
('91105048', 'VTYPE_MOBI', '01', '0'),
('91105050', 'MTYPE_BRON', '04', '0'),
('91105051', 'VTYPE_MOBI', '01', '0'),
('91105055', 'VTYPE_MOBI', '01', '0'),
('91105056', 'VTYPE_MOBI', '01', '0'),
('91105058', 'VTYPE_MOBI', '01', '0'),
('91105060', 'VTYPE_MOBI', '01', '0'),
('91105062', 'VTYPE_MOBI', '01', '0'),
('91105064', 'VTYPE_MOBI', '01', '0'),
('91105066', 'VTYPE_MOBI', '01', '0'),
('91105068', 'VTYPE_MOBI', '01', '0'),
('91105070', 'VTYPE_MOBI', '01', '0'),
('91105072', 'VTYPE_MOBI', '01', '0'),
('91105074', 'VTYPE_MOBI', '01', '0'),
('91105076', 'VTYPE_MOBI', '01', '0'),
('91105078', 'VTYPE_MOBI', '01', '0'),
('91105080', 'VTYPE_MOBI', '01', '0'),
('91105082', 'VTYPE_MOBI', '01', '0'),
('91105084', 'VTYPE_MOBI', '01', '0'),
('91105086', 'VTYPE_MOBI', '01', '0'),
('91105088', 'VTYPE_MOBI', '01', '0'),
('91105090', 'VTYPE_MOBI', '01', '0'),
('91105092', 'VTYPE_MOBI', '01', '0'),
('91105094', 'VTYPE_MOBI', '01', '0'),
('91105098', 'VTYPE_MOBI', '01', '0'),
('91105100', 'VTYPE_MOBI', '01', '0'),
('91105101', 'VTYPE_MOBI', '01', '0'),
('91105103', 'VTYPE_MOBI', '01', '0'),
('91105105', 'VTYPE_MOBI', '01', '0'),
('91105107', 'VTYPE_MOBI', '01', '0'),
('91105109', 'VTYPE_MOBI', '01', '0'),
('91105111', 'MTYPE_SILV', '05', '0'),
('91105112', 'VTYPE_MOBI', '01', '0'),
('91105114', 'VTYPE_MOBI', '01', '0'),
('91105115', 'VTYPE_MOBI', '01', '0'),
('91105117', 'VTYPE_MOBI', '01', '0'),
('91105119', 'VTYPE_MOBI', '01', '0'),
('91105121', 'VTYPE_MOBI', '01', '0'),
('91105123', 'VTYPE_MOBI', '01', '0'),
('91105124', 'VTYPE_MOBI', '01', '0'),
('91105125', 'VTYPE_MOBI', '01', '0'),
('91105131', 'VTYPE_MOBI', '01', '0'),
('91105133', 'VTYPE_MOBI', '01', '0'),
('91105135', 'VTYPE_MOBI', '01', '0'),
('91105136', 'VTYPE_MOBI', '01', '0'),
('91105138', 'VTYPE_MOBI', '01', '0'),
('91105139', 'VTYPE_MOBI', '01', '0'),
('91105140', 'VTYPE_MOBI', '01', '0'),
('91105141', 'VTYPE_MOBI', '01', '0'),
('91105142', 'VTYPE_MOBI', '01', '0'),
('91105143', 'VTYPE_MOBI', '01', '0'),
('91105144', 'VTYPE_MOBI', '01', '0'),
('91105145', 'VTYPE_MOBI', '01', '0'),
('91105146', 'VTYPE_MOBI', '01', '0'),
('91105147', 'VTYPE_MOBI', '01', '0');
INSERT INTO `ocs_account_key` (`account_key`, `account_key_type`, `status`, `sales_flag`) VALUES
('91105148', 'VTYPE_MOBI', '01', '0'),
('91105150', 'VTYPE_MOBI', '01', '0'),
('91105151', 'MTYPE_BRON', '04', '0'),
('91105152', 'VTYPE_MOBI', '01', '0'),
('91105153', 'VTYPE_MOBI', '01', '0'),
('91105154', 'VTYPE_MOBI', '01', '0'),
('91105155', 'VTYPE_MOBI', '01', '0'),
('91105156', 'VTYPE_MOBI', '01', '0'),
('91105157', 'VTYPE_MOBI', '01', '0'),
('91105158', 'VTYPE_MOBI', '01', '0'),
('91105159', 'VTYPE_MOBI', '01', '0'),
('91105160', 'VTYPE_MOBI', '01', '0'),
('91105161', 'VTYPE_MOBI', '01', '0'),
('91105162', 'VTYPE_MOBI', '01', '0'),
('91105165', 'VTYPE_MOBI', '01', '0'),
('91105166', 'VTYPE_MOBI', '01', '0'),
('91105167', 'VTYPE_MOBI', '01', '0'),
('91105168', 'VTYPE_MOBI', '01', '0'),
('91105170', 'VTYPE_MOBI', '01', '0'),
('91105171', 'VTYPE_MOBI', '01', '0'),
('91105172', 'VTYPE_MOBI', '01', '0'),
('91105175', 'VTYPE_MOBI', '01', '0'),
('91105177', 'VTYPE_MOBI', '01', '0'),
('91105179', 'VTYPE_MOBI', '01', '0'),
('91105181', 'VTYPE_MOBI', '01', '0'),
('91105182', 'VTYPE_MOBI', '01', '0'),
('91105183', 'VTYPE_MOBI', '01', '0'),
('91105184', 'VTYPE_MOBI', '01', '0'),
('91105185', 'VTYPE_MOBI', '01', '0'),
('91105186', 'VTYPE_MOBI', '01', '0'),
('91105187', 'VTYPE_MOBI', '01', '0'),
('91105188', 'VTYPE_MOBI', '01', '0'),
('91105190', 'VTYPE_MOBI', '01', '0'),
('91105191', 'VTYPE_MOBI', '01', '0'),
('91105192', 'VTYPE_MOBI', '01', '0'),
('91105194', 'VTYPE_MOBI', '01', '0'),
('91105195', 'VTYPE_MOBI', '01', '0'),
('91105196', 'VTYPE_MOBI', '01', '0'),
('91105197', 'VTYPE_MOBI', '01', '0'),
('91105199', 'VTYPE_MOBI', '01', '0'),
('91105200', 'VTYPE_MOBI', '01', '0'),
('91105201', 'VTYPE_MOBI', '01', '0'),
('91105202', 'VTYPE_MOBI', '01', '0'),
('91105203', 'VTYPE_MOBI', '01', '0'),
('91105204', 'VTYPE_MOBI', '01', '0'),
('91105205', 'VTYPE_MOBI', '01', '0'),
('91105206', 'VTYPE_MOBI', '01', '0'),
('91105207', 'VTYPE_MOBI', '01', '0'),
('91105208', 'VTYPE_MOBI', '01', '0'),
('91105209', 'VTYPE_MOBI', '01', '0'),
('91105210', 'VTYPE_MOBI', '01', '0'),
('91105211', 'VTYPE_MOBI', '01', '0'),
('91105213', 'VTYPE_MOBI', '01', '0'),
('91105214', 'VTYPE_MOBI', '01', '0'),
('91105215', 'VTYPE_MOBI', '01', '0'),
('91105216', 'VTYPE_MOBI', '01', '0'),
('91105219', 'VTYPE_MOBI', '01', '0'),
('91105220', 'VTYPE_MOBI', '01', '0'),
('91105221', 'VTYPE_MOBI', '01', '0'),
('91105222', 'MTYPE_SILV', '05', '0'),
('91105223', 'VTYPE_MOBI', '01', '0'),
('91105224', 'VTYPE_MOBI', '01', '0'),
('91105225', 'VTYPE_MOBI', '01', '0'),
('91105226', 'VTYPE_MOBI', '01', '0'),
('91105227', 'VTYPE_MOBI', '01', '0'),
('91105228', 'VTYPE_MOBI', '01', '0'),
('91105229', 'VTYPE_MOBI', '01', '0'),
('91105230', 'VTYPE_MOBI', '01', '0'),
('91105231', 'VTYPE_MOBI', '01', '0'),
('91105232', 'VTYPE_MOBI', '01', '0'),
('91105233', 'VTYPE_MOBI', '01', '0'),
('91105234', 'VTYPE_MOBI', '01', '0'),
('91105236', 'VTYPE_MOBI', '01', '0'),
('91105237', 'VTYPE_MOBI', '01', '0'),
('91105238', 'VTYPE_MOBI', '01', '0'),
('91105239', 'VTYPE_MOBI', '01', '0'),
('91105240', 'VTYPE_MOBI', '01', '0'),
('91105241', 'VTYPE_MOBI', '01', '0'),
('91105242', 'VTYPE_MOBI', '01', '0'),
('91105244', 'VTYPE_MOBI', '01', '0'),
('91105245', 'VTYPE_MOBI', '01', '0'),
('91105247', 'VTYPE_MOBI', '01', '0'),
('91105248', 'VTYPE_MOBI', '01', '0'),
('91105249', 'VTYPE_MOBI', '01', '0'),
('91105250', 'VTYPE_MOBI', '01', '0'),
('91105251', 'VTYPE_MOBI', '01', '0'),
('91105252', 'MTYPE_BRON', '04', '0'),
('91105253', 'VTYPE_MOBI', '01', '0'),
('91105254', 'VTYPE_MOBI', '01', '0'),
('91105255', 'VTYPE_MOBI', '01', '0'),
('91105256', 'VTYPE_MOBI', '01', '0'),
('91105257', 'VTYPE_MOBI', '01', '0'),
('91105258', 'VTYPE_MOBI', '01', '0'),
('91105259', 'VTYPE_MOBI', '01', '0'),
('91105261', 'VTYPE_MOBI', '01', '0'),
('91105262', 'VTYPE_MOBI', '01', '0'),
('91105263', 'VTYPE_MOBI', '01', '0'),
('91105264', 'VTYPE_MOBI', '01', '0'),
('91105265', 'VTYPE_MOBI', '01', '0'),
('91105266', 'VTYPE_MOBI', '01', '0'),
('91105267', 'VTYPE_MOBI', '01', '0'),
('91105268', 'VTYPE_MOBI', '01', '0'),
('91105269', 'VTYPE_MOBI', '01', '0'),
('91105271', 'VTYPE_MOBI', '01', '0'),
('91105272', 'VTYPE_MOBI', '01', '0'),
('91105274', 'VTYPE_MOBI', '01', '0'),
('91105277', 'VTYPE_MOBI', '01', '0'),
('91105279', 'VTYPE_MOBI', '01', '0'),
('91105280', 'VTYPE_MOBI', '01', '0'),
('91105281', 'VTYPE_MOBI', '01', '0'),
('91105282', 'VTYPE_MOBI', '01', '0'),
('91105285', 'VTYPE_MOBI', '01', '0'),
('91105286', 'VTYPE_MOBI', '01', '0'),
('91105287', 'VTYPE_MOBI', '01', '0'),
('91105288', 'VTYPE_MOBI', '01', '0'),
('91105291', 'VTYPE_MOBI', '01', '0'),
('91105292', 'VTYPE_MOBI', '01', '0'),
('91105294', 'VTYPE_MOBI', '01', '0'),
('91105295', 'VTYPE_MOBI', '01', '0'),
('91105296', 'VTYPE_MOBI', '01', '0'),
('91105298', 'VTYPE_MOBI', '01', '0'),
('91105299', 'VTYPE_MOBI', '01', '0'),
('91105300', 'VTYPE_MOBI', '01', '0'),
('91105301', 'VTYPE_MOBI', '01', '0'),
('91105303', 'VTYPE_MOBI', '01', '0'),
('91105304', 'VTYPE_MOBI', '01', '0'),
('91105305', 'VTYPE_MOBI', '01', '0'),
('91105307', 'VTYPE_MOBI', '01', '0'),
('91105310', 'VTYPE_MOBI', '01', '0'),
('91105313', 'VTYPE_MOBI', '01', '0'),
('91105318', 'VTYPE_MOBI', '01', '0'),
('91105320', 'VTYPE_MOBI', '01', '0'),
('91105322', 'VTYPE_MOBI', '01', '0'),
('91105324', 'VTYPE_MOBI', '01', '0'),
('91105326', 'VTYPE_MOBI', '01', '0'),
('91105330', 'VTYPE_MOBI', '01', '0'),
('91105332', 'VTYPE_MOBI', '01', '0'),
('91105335', 'VTYPE_MOBI', '01', '0'),
('91105337', 'VTYPE_MOBI', '01', '0'),
('91105339', 'VTYPE_MOBI', '01', '0'),
('91105341', 'VTYPE_MOBI', '01', '0'),
('91105343', 'VTYPE_MOBI', '01', '0'),
('91105345', 'VTYPE_MOBI', '01', '0'),
('91105349', 'VTYPE_MOBI', '01', '0'),
('91105351', 'VTYPE_MOBI', '01', '0'),
('91105353', 'MTYPE_BRON', '04', '0'),
('91105354', 'VTYPE_MOBI', '01', '0'),
('91105355', 'VTYPE_MOBI', '01', '0'),
('91105359', 'VTYPE_MOBI', '01', '0'),
('91105363', 'VTYPE_MOBI', '01', '0'),
('91105365', 'VTYPE_MOBI', '01', '0'),
('91105367', 'VTYPE_MOBI', '01', '0'),
('91105371', 'VTYPE_MOBI', '01', '0'),
('91105373', 'VTYPE_MOBI', '01', '0'),
('91105379', 'VTYPE_MOBI', '01', '0'),
('91105381', 'VTYPE_MOBI', '01', '0'),
('91105383', 'VTYPE_MOBI', '01', '0'),
('91105385', 'VTYPE_MOBI', '01', '0'),
('91105389', 'VTYPE_MOBI', '01', '0'),
('91105391', 'VTYPE_MOBI', '01', '0'),
('91105393', 'VTYPE_MOBI', '01', '0'),
('91105395', 'VTYPE_MOBI', '01', '0'),
('91105399', 'VTYPE_MOBI', '01', '0'),
('91105400', 'VTYPE_MOBI', '01', '0'),
('91105402', 'VTYPE_MOBI', '01', '0'),
('91105404', 'VTYPE_MOBI', '01', '0'),
('91105406', 'VTYPE_MOBI', '01', '0'),
('91105408', 'VTYPE_MOBI', '01', '0'),
('91105410', 'VTYPE_MOBI', '01', '0'),
('91105412', 'VTYPE_MOBI', '01', '0'),
('91105414', 'VTYPE_MOBI', '01', '0'),
('91105416', 'VTYPE_MOBI', '01', '0'),
('91105418', 'VTYPE_MOBI', '01', '0'),
('91105420', 'VTYPE_MOBI', '01', '0'),
('91105424', 'VTYPE_MOBI', '01', '0'),
('91105430', 'VTYPE_MOBI', '01', '0'),
('91105431', 'VTYPE_MOBI', '01', '0'),
('91105432', 'VTYPE_MOBI', '01', '0'),
('91105433', 'VTYPE_MOBI', '01', '0'),
('91105435', 'VTYPE_MOBI', '01', '0'),
('91105441', 'VTYPE_MOBI', '01', '0'),
('91105443', 'VTYPE_MOBI', '01', '0'),
('91105444', 'MTYPE_SILV', '05', '0'),
('91105445', 'VTYPE_MOBI', '01', '0'),
('91105447', 'VTYPE_MOBI', '01', '0'),
('91105449', 'VTYPE_MOBI', '01', '0'),
('91105451', 'VTYPE_MOBI', '01', '0'),
('91105453', 'VTYPE_MOBI', '01', '0'),
('91105454', 'MTYPE_BRON', '04', '0'),
('91105455', 'VTYPE_MOBI', '01', '0'),
('91105457', 'VTYPE_MOBI', '01', '0'),
('91105459', 'VTYPE_MOBI', '01', '0'),
('91105461', 'VTYPE_MOBI', '01', '0'),
('91105463', 'VTYPE_MOBI', '01', '0'),
('91105465', 'VTYPE_MOBI', '01', '0'),
('91105467', 'VTYPE_MOBI', '01', '0'),
('91105475', 'VTYPE_MOBI', '01', '0'),
('91105477', 'VTYPE_MOBI', '01', '0'),
('91105479', 'VTYPE_MOBI', '01', '0'),
('91105481', 'VTYPE_MOBI', '01', '0'),
('91105483', 'VTYPE_MOBI', '01', '0'),
('91105485', 'VTYPE_MOBI', '01', '0'),
('91105486', 'VTYPE_MOBI', '01', '0'),
('91105487', 'VTYPE_MOBI', '01', '0'),
('91105489', 'VTYPE_MOBI', '01', '0'),
('91105491', 'VTYPE_MOBI', '01', '0'),
('91105493', 'VTYPE_MOBI', '01', '0'),
('91105495', 'VTYPE_MOBI', '01', '0'),
('91105500', 'MTYPE_BRON', '03', '0'),
('91105502', 'VTYPE_MOBI', '01', '0'),
('91105504', 'VTYPE_MOBI', '01', '0'),
('91105506', 'VTYPE_MOBI', '01', '0'),
('91105508', 'VTYPE_MOBI', '01', '0'),
('91105510', 'VTYPE_MOBI', '01', '0'),
('91105511', 'MTYPE_BRON', '03', '0'),
('91105513', 'VTYPE_MOBI', '01', '0'),
('91105515', 'VTYPE_MOBI', '01', '0'),
('91105516', 'VTYPE_MOBI', '01', '0'),
('91105517', 'VTYPE_MOBI', '01', '0'),
('91105518', 'VTYPE_MOBI', '01', '0'),
('91105520', 'VTYPE_MOBI', '01', '0'),
('91105522', 'MTYPE_BRON', '03', '0'),
('91105523', 'VTYPE_MOBI', '01', '0'),
('91105525', 'VTYPE_MOBI', '01', '0'),
('91105526', 'VTYPE_MOBI', '01', '0'),
('91105528', 'VTYPE_MOBI', '01', '0'),
('91105530', 'VTYPE_MOBI', '01', '0'),
('91105532', 'VTYPE_MOBI', '01', '0'),
('91105533', 'MTYPE_BRON', '03', '0'),
('91105535', 'VTYPE_MOBI', '01', '0'),
('91105536', 'VTYPE_MOBI', '01', '0'),
('91105540', 'VTYPE_MOBI', '01', '0'),
('91105544', 'MTYPE_BRON', '03', '0'),
('91105545', 'VTYPE_MOBI', '01', '0'),
('91105546', 'VTYPE_MOBI', '01', '0'),
('91105548', 'VTYPE_MOBI', '01', '0'),
('91105550', 'VTYPE_MOBI', '05', '0'),
('91105551', 'VTYPE_MOBI', '05', '0'),
('91105552', 'VTYPE_MOBI', '05', '0'),
('91105553', 'VTYPE_MOBI', '05', '0'),
('91105554', 'VTYPE_MOBI', '05', '0'),
('91105555', 'MTYPE_GOLD', '02', '0'),
('91105556', 'VTYPE_MOBI', '05', '0'),
('91105557', 'VTYPE_MOBI', '05', '0'),
('91105558', 'VTYPE_MOBI', '05', '0'),
('91105559', 'VTYPE_MOBI', '05', '0'),
('91105560', 'VTYPE_MOBI', '01', '0'),
('91105562', 'VTYPE_MOBI', '01', '0'),
('91105564', 'VTYPE_MOBI', '01', '0'),
('91105565', 'VTYPE_MOBI', '01', '0'),
('91105566', 'MTYPE_BRON', '03', '0'),
('91105568', 'VTYPE_MOBI', '01', '0'),
('91105572', 'VTYPE_MOBI', '01', '0'),
('91105574', 'VTYPE_MOBI', '01', '0'),
('91105575', 'VTYPE_MOBI', '01', '0'),
('91105577', 'MTYPE_BRON', '03', '0'),
('91105578', 'VTYPE_MOBI', '01', '0'),
('91105579', 'VTYPE_MOBI', '01', '0'),
('91105580', 'VTYPE_MOBI', '01', '0'),
('91105581', 'VTYPE_MOBI', '01', '0'),
('91105582', 'VTYPE_MOBI', '01', '0'),
('91105583', 'VTYPE_MOBI', '01', '0'),
('91105585', 'VTYPE_MOBI', '01', '0'),
('91105586', 'VTYPE_MOBI', '01', '0'),
('91105588', 'MTYPE_BRON', '03', '0'),
('91105589', 'VTYPE_MOBI', '01', '0'),
('91105590', 'VTYPE_MOBI', '01', '0'),
('91105591', 'VTYPE_MOBI', '01', '0'),
('91105592', 'VTYPE_MOBI', '01', '0'),
('91105593', 'VTYPE_MOBI', '01', '0'),
('91105594', 'VTYPE_MOBI', '01', '0'),
('91105595', 'VTYPE_MOBI', '01', '0'),
('91105596', 'VTYPE_MOBI', '01', '0'),
('91105597', 'VTYPE_MOBI', '01', '0'),
('91105598', 'VTYPE_MOBI', '01', '0'),
('91105599', 'MTYPE_BRON', '03', '0'),
('91105600', 'VTYPE_MOBI', '01', '0'),
('91105601', 'VTYPE_MOBI', '01', '0'),
('91105602', 'VTYPE_MOBI', '01', '0'),
('91105603', 'VTYPE_MOBI', '01', '0'),
('91105605', 'VTYPE_MOBI', '01', '0'),
('91105608', 'VTYPE_MOBI', '01', '0'),
('91105609', 'VTYPE_MOBI', '01', '0'),
('91105610', 'VTYPE_MOBI', '01', '0'),
('91105611', 'VTYPE_MOBI', '01', '0'),
('91105614', 'VTYPE_MOBI', '01', '0'),
('91105615', 'VTYPE_MOBI', '01', '0'),
('91105616', 'VTYPE_MOBI', '01', '0'),
('91105617', 'VTYPE_MOBI', '01', '0'),
('91105620', 'VTYPE_MOBI', '01', '0'),
('91105622', 'VTYPE_MOBI', '01', '0'),
('91105624', 'VTYPE_MOBI', '01', '0'),
('91105626', 'VTYPE_MOBI', '01', '0'),
('91105627', 'VTYPE_MOBI', '01', '0'),
('91105628', 'VTYPE_MOBI', '01', '0'),
('91105630', 'VTYPE_MOBI', '01', '0'),
('91105632', 'VTYPE_MOBI', '01', '0'),
('91105633', 'VTYPE_MOBI', '01', '0'),
('91105635', 'VTYPE_MOBI', '01', '0'),
('91105637', 'VTYPE_MOBI', '01', '0'),
('91105638', 'VTYPE_MOBI', '01', '0'),
('91105639', 'VTYPE_MOBI', '01', '0'),
('91105640', 'VTYPE_MOBI', '01', '0'),
('91105644', 'VTYPE_MOBI', '01', '0'),
('91105645', 'VTYPE_MOBI', '01', '0'),
('91105646', 'VTYPE_MOBI', '01', '0'),
('91105650', 'VTYPE_MOBI', '01', '0'),
('91105651', 'VTYPE_MOBI', '01', '0'),
('91105652', 'VTYPE_MOBI', '01', '0'),
('91105653', 'VTYPE_MOBI', '01', '0'),
('91105654', 'VTYPE_MOBI', '01', '0'),
('91105655', 'VTYPE_MOBI', '01', '0'),
('91105656', 'MTYPE_BRON', '04', '0'),
('91105657', 'VTYPE_MOBI', '01', '0'),
('91105658', 'VTYPE_MOBI', '01', '0'),
('91105659', 'VTYPE_MOBI', '01', '0'),
('91105660', 'VTYPE_MOBI', '01', '0'),
('91105661', 'VTYPE_MOBI', '01', '0'),
('91105662', 'VTYPE_MOBI', '01', '0'),
('91105663', 'VTYPE_MOBI', '01', '0'),
('91105664', 'VTYPE_MOBI', '01', '0'),
('91105665', 'VTYPE_MOBI', '01', '0'),
('91105666', 'MTYPE_SILV', '05', '0'),
('91105668', 'VTYPE_MOBI', '01', '0'),
('91105669', 'VTYPE_MOBI', '01', '0'),
('91105670', 'VTYPE_MOBI', '01', '0'),
('91105672', 'VTYPE_MOBI', '01', '0'),
('91105673', 'VTYPE_MOBI', '01', '0'),
('91105674', 'VTYPE_MOBI', '01', '0'),
('91105675', 'VTYPE_MOBI', '01', '0'),
('91105676', 'VTYPE_MOBI', '01', '0'),
('91105677', 'VTYPE_MOBI', '01', '0'),
('91105678', 'VTYPE_MOBI', '01', '0'),
('91105679', 'VTYPE_MOBI', '01', '0'),
('91105680', 'VTYPE_MOBI', '01', '0'),
('91105681', 'VTYPE_MOBI', '01', '0'),
('91105682', 'VTYPE_MOBI', '01', '0'),
('91105684', 'VTYPE_MOBI', '01', '0'),
('91105685', 'VTYPE_MOBI', '01', '0'),
('91105686', 'VTYPE_MOBI', '01', '0'),
('91105688', 'VTYPE_MOBI', '01', '0'),
('91105689', 'VTYPE_MOBI', '01', '0'),
('91105694', 'VTYPE_MOBI', '01', '0'),
('91105695', 'VTYPE_MOBI', '01', '0'),
('91105696', 'VTYPE_MOBI', '01', '0'),
('91105698', 'VTYPE_MOBI', '01', '0'),
('91105699', 'VTYPE_MOBI', '01', '0'),
('91105700', 'VTYPE_MOBI', '01', '0'),
('91105701', 'VTYPE_MOBI', '01', '0'),
('91105702', 'VTYPE_MOBI', '01', '0'),
('91105703', 'VTYPE_MOBI', '01', '0'),
('91105704', 'VTYPE_MOBI', '01', '0'),
('91105705', 'VTYPE_MOBI', '01', '0'),
('91105706', 'VTYPE_MOBI', '01', '0'),
('91105707', 'VTYPE_MOBI', '01', '0'),
('91105708', 'VTYPE_MOBI', '01', '0'),
('91105709', 'VTYPE_MOBI', '01', '0'),
('91105710', 'VTYPE_MOBI', '01', '0'),
('91105711', 'VTYPE_MOBI', '01', '0'),
('91105712', 'VTYPE_MOBI', '01', '0'),
('91105715', 'VTYPE_MOBI', '01', '0'),
('91105717', 'VTYPE_MOBI', '01', '0'),
('91105718', 'VTYPE_MOBI', '01', '0'),
('91105721', 'VTYPE_MOBI', '01', '0'),
('91105722', 'VTYPE_MOBI', '01', '0'),
('91105725', 'VTYPE_MOBI', '01', '0'),
('91105728', 'VTYPE_MOBI', '01', '0'),
('91105730', 'VTYPE_MOBI', '01', '0'),
('91105731', 'VTYPE_MOBI', '01', '0'),
('91105733', 'VTYPE_MOBI', '01', '0'),
('91105735', 'VTYPE_MOBI', '01', '0'),
('91105736', 'VTYPE_MOBI', '01', '0'),
('91105737', 'VTYPE_MOBI', '01', '0'),
('91105741', 'VTYPE_MOBI', '01', '0'),
('91105742', 'VTYPE_MOBI', '01', '0'),
('91105744', 'VTYPE_MOBI', '01', '0'),
('91105747', 'VTYPE_MOBI', '01', '0'),
('91105750', 'VTYPE_MOBI', '01', '0'),
('91105752', 'VTYPE_MOBI', '01', '0'),
('91105754', 'VTYPE_MOBI', '01', '0'),
('91105755', 'VTYPE_MOBI', '01', '0'),
('91105757', 'MTYPE_BRON', '04', '0'),
('91105760', 'VTYPE_MOBI', '01', '0'),
('91105765', 'VTYPE_MOBI', '01', '0'),
('91105766', 'VTYPE_MOBI', '01', '0'),
('91105768', 'VTYPE_MOBI', '01', '0'),
('91105770', 'VTYPE_MOBI', '01', '0'),
('91105772', 'VTYPE_MOBI', '01', '0'),
('91105774', 'VTYPE_MOBI', '01', '0'),
('91105775', 'VTYPE_MOBI', '01', '0'),
('91105777', 'MTYPE_SILV', '05', '0'),
('91105778', 'VTYPE_MOBI', '01', '0'),
('91105780', 'VTYPE_MOBI', '01', '0'),
('91105782', 'VTYPE_MOBI', '01', '0'),
('91105784', 'VTYPE_MOBI', '01', '0'),
('91105788', 'VTYPE_MOBI', '01', '0'),
('91105790', 'VTYPE_MOBI', '01', '0'),
('91105794', 'VTYPE_MOBI', '01', '0'),
('91105795', 'VTYPE_MOBI', '01', '0'),
('91105796', 'VTYPE_MOBI', '01', '0'),
('91105800', 'VTYPE_MOBI', '01', '0'),
('91105805', 'VTYPE_MOBI', '01', '0'),
('91105807', 'VTYPE_MOBI', '01', '0'),
('91105808', 'VTYPE_MOBI', '01', '0'),
('91105811', 'VTYPE_MOBI', '01', '0'),
('91105813', 'VTYPE_MOBI', '01', '0'),
('91105815', 'VTYPE_MOBI', '01', '0'),
('91105819', 'VTYPE_MOBI', '01', '0'),
('91105825', 'VTYPE_MOBI', '01', '0'),
('91105827', 'VTYPE_MOBI', '01', '0'),
('91105829', 'VTYPE_MOBI', '01', '0'),
('91105833', 'VTYPE_MOBI', '01', '0'),
('91105837', 'VTYPE_MOBI', '01', '0'),
('91105846', 'VTYPE_MOBI', '01', '0'),
('91105847', 'VTYPE_MOBI', '01', '0'),
('91105851', 'VTYPE_MOBI', '01', '0'),
('91105853', 'VTYPE_MOBI', '01', '0'),
('91105856', 'VTYPE_MOBI', '01', '0'),
('91105858', 'MTYPE_BRON', '04', '0'),
('91105859', 'VTYPE_MOBI', '01', '0'),
('91105861', 'VTYPE_MOBI', '01', '0'),
('91105865', 'VTYPE_MOBI', '01', '0'),
('91105869', 'VTYPE_MOBI', '01', '0'),
('91105871', 'VTYPE_MOBI', '01', '0'),
('91105873', 'VTYPE_MOBI', '01', '0'),
('91105876', 'VTYPE_MOBI', '01', '0'),
('91105877', 'VTYPE_MOBI', '01', '0'),
('91105879', 'VTYPE_MOBI', '01', '0'),
('91105881', 'VTYPE_MOBI', '01', '0'),
('91105883', 'VTYPE_MOBI', '01', '0'),
('91105885', 'VTYPE_MOBI', '01', '0'),
('91105886', 'VTYPE_MOBI', '01', '0'),
('91105888', 'MTYPE_SILV', '05', '0'),
('91105889', 'VTYPE_MOBI', '01', '0'),
('91105891', 'VTYPE_MOBI', '01', '0'),
('91105895', 'VTYPE_MOBI', '01', '0'),
('91105897', 'VTYPE_MOBI', '01', '0'),
('91105899', 'VTYPE_MOBI', '01', '0'),
('91105900', 'VTYPE_MOBI', '01', '0'),
('91105906', 'VTYPE_MOBI', '01', '0'),
('91105908', 'VTYPE_MOBI', '01', '0'),
('91105918', 'VTYPE_MOBI', '01', '0'),
('91105920', 'VTYPE_MOBI', '01', '0'),
('91105934', 'VTYPE_MOBI', '01', '0'),
('91105938', 'VTYPE_MOBI', '01', '0'),
('91105940', 'VTYPE_MOBI', '01', '0'),
('91105946', 'VTYPE_MOBI', '01', '0'),
('91105948', 'VTYPE_MOBI', '01', '0'),
('91105950', 'VTYPE_MOBI', '01', '0'),
('91105952', 'VTYPE_MOBI', '01', '0'),
('91105954', 'VTYPE_MOBI', '01', '0'),
('91105955', 'VTYPE_MOBI', '01', '0'),
('91105957', 'VTYPE_MOBI', '01', '0'),
('91105959', 'MTYPE_BRON', '04', '0'),
('91105960', 'VTYPE_MOBI', '01', '0'),
('91105966', 'VTYPE_MOBI', '01', '0'),
('91105968', 'VTYPE_MOBI', '01', '0'),
('91105970', 'VTYPE_MOBI', '01', '0'),
('91105974', 'VTYPE_MOBI', '01', '0'),
('91105978', 'VTYPE_MOBI', '01', '0'),
('91105980', 'VTYPE_MOBI', '01', '0'),
('91105982', 'VTYPE_MOBI', '01', '0'),
('91105984', 'VTYPE_MOBI', '01', '0'),
('91105987', 'VTYPE_MOBI', '01', '0'),
('91105988', 'VTYPE_MOBI', '01', '0'),
('91105990', 'VTYPE_MOBI', '01', '0'),
('91105994', 'VTYPE_MOBI', '01', '0'),
('91105995', 'VTYPE_MOBI', '01', '0'),
('91105997', 'VTYPE_MOBI', '01', '0'),
('91105999', 'MTYPE_SILV', '05', '0'),
('91106000', 'MTYPE_SILV', '05', '0'),
('91106001', 'VTYPE_MOBI', '01', '0'),
('91106002', 'VTYPE_MOBI', '01', '0'),
('91106004', 'VTYPE_MOBI', '01', '0'),
('91106006', 'VTYPE_MOBI', '01', '0'),
('91106007', 'VTYPE_MOBI', '01', '0'),
('91106009', 'VTYPE_MOBI', '01', '0'),
('91106011', 'VTYPE_MOBI', '01', '0'),
('91106013', 'VTYPE_MOBI', '01', '0'),
('91106015', 'VTYPE_MOBI', '01', '0'),
('91106017', 'VTYPE_MOBI', '01', '0'),
('91106019', 'VTYPE_MOBI', '01', '0'),
('91106021', 'VTYPE_MOBI', '01', '0'),
('91106022', 'VTYPE_MOBI', '01', '0'),
('91106023', 'VTYPE_MOBI', '01', '0'),
('91106024', 'VTYPE_MOBI', '01', '0'),
('91106025', 'VTYPE_MOBI', '01', '0'),
('91106026', 'VTYPE_MOBI', '01', '0'),
('91106027', 'VTYPE_MOBI', '01', '0'),
('91106028', 'VTYPE_MOBI', '01', '0'),
('91106029', 'VTYPE_MOBI', '01', '0'),
('91106030', 'VTYPE_MOBI', '01', '0'),
('91106031', 'VTYPE_MOBI', '01', '0'),
('91106032', 'VTYPE_MOBI', '01', '0'),
('91106034', 'VTYPE_MOBI', '01', '0'),
('91106035', 'VTYPE_MOBI', '01', '0'),
('91106036', 'VTYPE_MOBI', '01', '0'),
('91106039', 'VTYPE_MOBI', '01', '0'),
('91106040', 'VTYPE_MOBI', '01', '0'),
('91106041', 'VTYPE_MOBI', '01', '0'),
('91106042', 'VTYPE_MOBI', '01', '0'),
('91106044', 'VTYPE_MOBI', '01', '0'),
('91106045', 'VTYPE_MOBI', '01', '0'),
('91106047', 'VTYPE_MOBI', '01', '0'),
('91106048', 'VTYPE_MOBI', '01', '0'),
('91106049', 'VTYPE_MOBI', '01', '0'),
('91106050', 'VTYPE_MOBI', '01', '0'),
('91106051', 'VTYPE_MOBI', '01', '0'),
('91106052', 'VTYPE_MOBI', '01', '0'),
('91106053', 'VTYPE_MOBI', '01', '0'),
('91106054', 'VTYPE_MOBI', '01', '0'),
('91106055', 'VTYPE_MOBI', '01', '0'),
('91106056', 'VTYPE_MOBI', '01', '0'),
('91106057', 'VTYPE_MOBI', '01', '0'),
('91106058', 'VTYPE_MOBI', '01', '0'),
('91106059', 'VTYPE_MOBI', '01', '0'),
('91106060', 'MTYPE_BRON', '04', '0'),
('91106061', 'VTYPE_MOBI', '01', '0'),
('91106062', 'VTYPE_MOBI', '01', '0'),
('91106064', 'VTYPE_MOBI', '01', '0'),
('91106065', 'VTYPE_MOBI', '01', '0'),
('91106066', 'VTYPE_MOBI', '01', '0'),
('91106067', 'VTYPE_MOBI', '01', '0'),
('91106068', 'VTYPE_MOBI', '01', '0'),
('91106069', 'VTYPE_MOBI', '01', '0'),
('91106070', 'VTYPE_MOBI', '01', '0'),
('91106071', 'VTYPE_MOBI', '01', '0'),
('91106072', 'VTYPE_MOBI', '01', '0'),
('91106073', 'VTYPE_MOBI', '01', '0'),
('91106074', 'VTYPE_MOBI', '01', '0'),
('91106075', 'VTYPE_MOBI', '01', '0'),
('91106076', 'VTYPE_MOBI', '01', '0'),
('91106077', 'VTYPE_MOBI', '01', '0'),
('91106078', 'VTYPE_MOBI', '01', '0'),
('91106080', 'VTYPE_MOBI', '01', '0'),
('91106081', 'VTYPE_MOBI', '01', '0'),
('91106083', 'VTYPE_MOBI', '01', '0'),
('91106084', 'VTYPE_MOBI', '01', '0'),
('91106085', 'VTYPE_MOBI', '01', '0'),
('91106086', 'VTYPE_MOBI', '01', '0'),
('91106087', 'VTYPE_MOBI', '01', '0'),
('91106088', 'VTYPE_MOBI', '01', '0'),
('91106089', 'VTYPE_MOBI', '01', '0'),
('91106090', 'VTYPE_MOBI', '01', '0'),
('91106091', 'VTYPE_MOBI', '01', '0'),
('91106092', 'VTYPE_MOBI', '01', '0'),
('91106093', 'VTYPE_MOBI', '01', '0'),
('91106094', 'VTYPE_MOBI', '01', '0'),
('91106095', 'VTYPE_MOBI', '01', '0'),
('91106096', 'VTYPE_MOBI', '01', '0'),
('91106097', 'VTYPE_MOBI', '01', '0'),
('91106098', 'VTYPE_MOBI', '01', '0'),
('91106099', 'VTYPE_MOBI', '01', '0'),
('91106100', 'VTYPE_MOBI', '01', '0'),
('91106101', 'VTYPE_MOBI', '01', '0'),
('91106102', 'VTYPE_MOBI', '01', '0'),
('91106103', 'VTYPE_MOBI', '01', '0'),
('91106104', 'VTYPE_MOBI', '01', '0'),
('91106105', 'VTYPE_MOBI', '01', '0'),
('91106107', 'VTYPE_MOBI', '01', '0'),
('91106108', 'VTYPE_MOBI', '01', '0'),
('91106109', 'VTYPE_MOBI', '01', '0'),
('91106110', 'VTYPE_MOBI', '01', '0'),
('91106111', 'MTYPE_SILV', '05', '0'),
('91106112', 'VTYPE_MOBI', '01', '0'),
('91106113', 'VTYPE_MOBI', '01', '0'),
('91106114', 'VTYPE_MOBI', '01', '0'),
('91106115', 'VTYPE_MOBI', '01', '0'),
('91106116', 'VTYPE_MOBI', '01', '0'),
('91106117', 'VTYPE_MOBI', '01', '0'),
('91106118', 'VTYPE_MOBI', '01', '0'),
('91106119', 'VTYPE_MOBI', '01', '0'),
('91106120', 'VTYPE_MOBI', '01', '0'),
('91106122', 'VTYPE_MOBI', '01', '0'),
('91106123', 'VTYPE_MOBI', '01', '0'),
('91106125', 'VTYPE_MOBI', '01', '0'),
('91106126', 'VTYPE_MOBI', '01', '0'),
('91106128', 'VTYPE_MOBI', '01', '0'),
('91106130', 'VTYPE_MOBI', '01', '0'),
('91106131', 'VTYPE_MOBI', '01', '0'),
('91106132', 'VTYPE_MOBI', '01', '0'),
('91106133', 'VTYPE_MOBI', '01', '0'),
('91106134', 'VTYPE_MOBI', '01', '0'),
('91106137', 'VTYPE_MOBI', '01', '0'),
('91106138', 'VTYPE_MOBI', '01', '0'),
('91106139', 'VTYPE_MOBI', '01', '0'),
('91106141', 'VTYPE_MOBI', '01', '0'),
('91106142', 'VTYPE_MOBI', '01', '0'),
('91106143', 'VTYPE_MOBI', '01', '0'),
('91106145', 'VTYPE_MOBI', '01', '0'),
('91106148', 'VTYPE_MOBI', '01', '0'),
('91106150', 'VTYPE_MOBI', '01', '0'),
('91106151', 'VTYPE_MOBI', '01', '0'),
('91106152', 'VTYPE_MOBI', '01', '0'),
('91106153', 'VTYPE_MOBI', '01', '0'),
('91106156', 'VTYPE_MOBI', '01', '0'),
('91106157', 'VTYPE_MOBI', '01', '0'),
('91106158', 'VTYPE_MOBI', '01', '0'),
('91106160', 'VTYPE_MOBI', '01', '0'),
('91106161', 'MTYPE_BRON', '04', '0'),
('91106162', 'VTYPE_MOBI', '01', '0'),
('91106163', 'VTYPE_MOBI', '01', '0'),
('91106164', 'VTYPE_MOBI', '01', '0'),
('91106166', 'VTYPE_MOBI', '01', '0'),
('91106167', 'VTYPE_MOBI', '01', '0'),
('91106169', 'VTYPE_MOBI', '01', '0'),
('91106171', 'VTYPE_MOBI', '01', '0'),
('91106173', 'VTYPE_MOBI', '01', '0'),
('91106175', 'VTYPE_MOBI', '01', '0'),
('91106177', 'VTYPE_MOBI', '01', '0'),
('91106179', 'VTYPE_MOBI', '01', '0'),
('91106181', 'VTYPE_MOBI', '01', '0'),
('91106183', 'VTYPE_MOBI', '01', '0'),
('91106185', 'VTYPE_MOBI', '01', '0'),
('91106187', 'VTYPE_MOBI', '01', '0'),
('91106191', 'VTYPE_MOBI', '01', '0'),
('91106193', 'VTYPE_MOBI', '01', '0'),
('91106195', 'VTYPE_MOBI', '01', '0'),
('91106199', 'VTYPE_MOBI', '01', '0'),
('91106200', 'VTYPE_MOBI', '01', '0'),
('91106202', 'VTYPE_MOBI', '01', '0'),
('91106204', 'VTYPE_MOBI', '01', '0'),
('91106206', 'VTYPE_MOBI', '01', '0'),
('91106208', 'VTYPE_MOBI', '01', '0'),
('91106210', 'VTYPE_MOBI', '01', '0'),
('91106212', 'VTYPE_MOBI', '01', '0'),
('91106214', 'VTYPE_MOBI', '01', '0'),
('91106218', 'VTYPE_MOBI', '01', '0'),
('91106220', 'VTYPE_MOBI', '01', '0'),
('91106222', 'MTYPE_SILV', '05', '0'),
('91106223', 'VTYPE_MOBI', '01', '0'),
('91106225', 'VTYPE_MOBI', '01', '0'),
('91106226', 'VTYPE_MOBI', '01', '0'),
('91106228', 'VTYPE_MOBI', '01', '0'),
('91106232', 'VTYPE_MOBI', '01', '0'),
('91106234', 'VTYPE_MOBI', '01', '0'),
('91106236', 'VTYPE_MOBI', '01', '0'),
('91106238', 'VTYPE_MOBI', '01', '0'),
('91106240', 'VTYPE_MOBI', '01', '0'),
('91106242', 'VTYPE_MOBI', '01', '0'),
('91106244', 'VTYPE_MOBI', '01', '0'),
('91106246', 'VTYPE_MOBI', '01', '0'),
('91106248', 'VTYPE_MOBI', '01', '0'),
('91106250', 'VTYPE_MOBI', '01', '0'),
('91106252', 'VTYPE_MOBI', '01', '0'),
('91106258', 'VTYPE_MOBI', '01', '0'),
('91106260', 'VTYPE_MOBI', '01', '0'),
('91106262', 'MTYPE_BRON', '04', '0'),
('91106263', 'VTYPE_MOBI', '01', '0'),
('91106265', 'VTYPE_MOBI', '01', '0'),
('91106266', 'VTYPE_MOBI', '01', '0'),
('91106268', 'VTYPE_MOBI', '01', '0'),
('91106272', 'VTYPE_MOBI', '01', '0'),
('91106274', 'VTYPE_MOBI', '01', '0'),
('91106278', 'VTYPE_MOBI', '01', '0'),
('91106280', 'VTYPE_MOBI', '01', '0'),
('91106282', 'VTYPE_MOBI', '01', '0'),
('91106284', 'VTYPE_MOBI', '01', '0'),
('91106286', 'VTYPE_MOBI', '01', '0'),
('91106288', 'VTYPE_MOBI', '01', '0'),
('91106290', 'VTYPE_MOBI', '01', '0'),
('91106292', 'VTYPE_MOBI', '01', '0'),
('91106298', 'VTYPE_MOBI', '01', '0'),
('91106300', 'VTYPE_MOBI', '01', '0'),
('91106301', 'VTYPE_MOBI', '01', '0'),
('91106303', 'VTYPE_MOBI', '01', '0'),
('91106305', 'VTYPE_MOBI', '01', '0'),
('91106307', 'VTYPE_MOBI', '01', '0'),
('91106309', 'VTYPE_MOBI', '01', '0'),
('91106313', 'VTYPE_MOBI', '01', '0'),
('91106315', 'VTYPE_MOBI', '01', '0'),
('91106325', 'VTYPE_MOBI', '01', '0'),
('91106327', 'VTYPE_MOBI', '01', '0'),
('91106329', 'VTYPE_MOBI', '01', '0'),
('91106331', 'VTYPE_MOBI', '01', '0'),
('91106333', 'MTYPE_SILV', '05', '0'),
('91106334', 'VTYPE_MOBI', '01', '0'),
('91106336', 'VTYPE_MOBI', '01', '0'),
('91106337', 'VTYPE_MOBI', '01', '0'),
('91106339', 'VTYPE_MOBI', '01', '0'),
('91106345', 'VTYPE_MOBI', '01', '0'),
('91106349', 'VTYPE_MOBI', '01', '0'),
('91106351', 'VTYPE_MOBI', '01', '0'),
('91106352', 'VTYPE_MOBI', '01', '0'),
('91106353', 'VTYPE_MOBI', '01', '0'),
('91106355', 'VTYPE_MOBI', '01', '0'),
('91106359', 'VTYPE_MOBI', '01', '0'),
('91106361', 'VTYPE_MOBI', '01', '0'),
('91106363', 'MTYPE_BRON', '04', '0'),
('91106364', 'VTYPE_MOBI', '01', '0'),
('91106366', 'VTYPE_MOBI', '01', '0'),
('91106367', 'VTYPE_MOBI', '01', '0'),
('91106369', 'VTYPE_MOBI', '01', '0'),
('91106371', 'VTYPE_MOBI', '01', '0'),
('91106373', 'VTYPE_MOBI', '01', '0'),
('91106377', 'VTYPE_MOBI', '01', '0'),
('91106382', 'VTYPE_MOBI', '01', '0'),
('91106385', 'VTYPE_MOBI', '01', '0'),
('91106391', 'VTYPE_MOBI', '01', '0'),
('91106393', 'VTYPE_MOBI', '01', '0'),
('91106395', 'VTYPE_MOBI', '01', '0'),
('91106399', 'VTYPE_MOBI', '01', '0'),
('91106400', 'VTYPE_MOBI', '01', '0'),
('91106404', 'VTYPE_MOBI', '01', '0'),
('91106406', 'VTYPE_MOBI', '01', '0'),
('91106408', 'VTYPE_MOBI', '01', '0'),
('91106410', 'VTYPE_MOBI', '01', '0'),
('91106412', 'VTYPE_MOBI', '01', '0'),
('91106416', 'VTYPE_MOBI', '01', '0'),
('91106418', 'VTYPE_MOBI', '01', '0'),
('91106420', 'VTYPE_MOBI', '01', '0'),
('91106422', 'VTYPE_MOBI', '01', '0'),
('91106424', 'VTYPE_MOBI', '01', '0'),
('91106434', 'VTYPE_MOBI', '01', '0'),
('91106436', 'VTYPE_MOBI', '01', '0'),
('91106438', 'VTYPE_MOBI', '01', '0'),
('91106442', 'VTYPE_MOBI', '01', '0'),
('91106443', 'VTYPE_MOBI', '01', '0'),
('91106444', 'MTYPE_SILV', '05', '0'),
('91106445', 'VTYPE_MOBI', '01', '0'),
('91106446', 'VTYPE_MOBI', '01', '0'),
('91106447', 'VTYPE_MOBI', '01', '0'),
('91106448', 'VTYPE_MOBI', '01', '0'),
('91106449', 'VTYPE_MOBI', '01', '0'),
('91106450', 'VTYPE_MOBI', '01', '0'),
('91106451', 'VTYPE_MOBI', '01', '0'),
('91106453', 'VTYPE_MOBI', '01', '0'),
('91106454', 'VTYPE_MOBI', '01', '0'),
('91106455', 'VTYPE_MOBI', '01', '0'),
('91106456', 'VTYPE_MOBI', '01', '0'),
('91106457', 'VTYPE_MOBI', '01', '0'),
('91106458', 'VTYPE_MOBI', '01', '0'),
('91106459', 'VTYPE_MOBI', '01', '0'),
('91106460', 'VTYPE_MOBI', '01', '0'),
('91106461', 'VTYPE_MOBI', '01', '0'),
('91106462', 'VTYPE_MOBI', '01', '0'),
('91106463', 'VTYPE_MOBI', '01', '0'),
('91106464', 'MTYPE_BRON', '04', '0'),
('91106465', 'VTYPE_MOBI', '01', '0'),
('91106466', 'VTYPE_MOBI', '01', '0'),
('91106467', 'VTYPE_MOBI', '01', '0'),
('91106468', 'VTYPE_MOBI', '01', '0'),
('91106469', 'VTYPE_MOBI', '01', '0'),
('91106470', 'VTYPE_MOBI', '01', '0'),
('91106472', 'VTYPE_MOBI', '01', '0'),
('91106473', 'VTYPE_MOBI', '01', '0'),
('91106474', 'VTYPE_MOBI', '01', '0'),
('91106475', 'VTYPE_MOBI', '01', '0'),
('91106476', 'VTYPE_MOBI', '01', '0'),
('91106477', 'VTYPE_MOBI', '01', '0'),
('91106478', 'VTYPE_MOBI', '01', '0'),
('91106479', 'VTYPE_MOBI', '01', '0'),
('91106480', 'VTYPE_MOBI', '01', '0'),
('91106484', 'VTYPE_MOBI', '01', '0'),
('91106486', 'VTYPE_MOBI', '01', '0'),
('91106488', 'VTYPE_MOBI', '01', '0'),
('91106489', 'VTYPE_MOBI', '01', '0'),
('91106490', 'VTYPE_MOBI', '01', '0'),
('91106491', 'VTYPE_MOBI', '01', '0'),
('91106494', 'VTYPE_MOBI', '01', '0'),
('91106496', 'VTYPE_MOBI', '01', '0'),
('91106497', 'VTYPE_MOBI', '01', '0'),
('91106498', 'VTYPE_MOBI', '01', '0'),
('91106499', 'VTYPE_MOBI', '01', '0'),
('91106500', 'VTYPE_MOBI', '01', '0'),
('91106501', 'VTYPE_MOBI', '01', '0'),
('91106502', 'VTYPE_MOBI', '01', '0'),
('91106503', 'VTYPE_MOBI', '01', '0'),
('91106504', 'VTYPE_MOBI', '01', '0'),
('91106505', 'VTYPE_MOBI', '01', '0'),
('91106506', 'VTYPE_MOBI', '01', '0'),
('91106507', 'VTYPE_MOBI', '01', '0'),
('91106508', 'VTYPE_MOBI', '01', '0'),
('91106509', 'VTYPE_MOBI', '01', '0'),
('91106511', 'VTYPE_MOBI', '01', '0'),
('91106513', 'VTYPE_MOBI', '01', '0'),
('91106514', 'VTYPE_MOBI', '01', '0'),
('91106561', 'VTYPE_MOBI', '01', '0'),
('91106581', 'VTYPE_MOBI', '01', '0'),
('91106594', 'VTYPE_MOBI', '01', '0'),
('91106612', 'VTYPE_MOBI', '01', '0'),
('91106647', 'VTYPE_MOBI', '01', '0'),
('91106901', 'VTYPE_MOBI', '01', '0'),
('91106910', 'VTYPE_MOBI', '01', '0'),
('91107077', 'VTYPE_MOBI', '01', '0'),
('91107100', 'VTYPE_MOBI', '01', '0'),
('91107102', 'VTYPE_MOBI', '01', '0'),
('91107105', 'VTYPE_MOBI', '01', '0'),
('91107142', 'VTYPE_MOBI', '01', '0'),
('91107162', 'VTYPE_MOBI', '01', '0'),
('91107215', 'VTYPE_MOBI', '01', '0'),
('91107261', 'VTYPE_MOBI', '01', '0'),
('91107292', 'VTYPE_MOBI', '01', '0'),
('91107337', 'VTYPE_MOBI', '01', '0'),
('91107360', 'VTYPE_MOBI', '01', '0'),
('91107390', 'VTYPE_MOBI', '01', '0'),
('91107414', 'VTYPE_MOBI', '01', '0'),
('91107448', 'VTYPE_MOBI', '01', '0'),
('91107459', 'VTYPE_MOBI', '01', '0'),
('91107463', 'VTYPE_MOBI', '01', '0'),
('91107514', 'VTYPE_MOBI', '01', '0'),
('91107535', 'VTYPE_MOBI', '01', '0'),
('91107536', 'VTYPE_MOBI', '01', '0'),
('91107537', 'VTYPE_MOBI', '01', '0'),
('91107538', 'VTYPE_MOBI', '01', '0'),
('91107539', 'VTYPE_MOBI', '01', '0'),
('91107540', 'VTYPE_MOBI', '01', '0'),
('91107541', 'VTYPE_MOBI', '01', '0'),
('91107542', 'VTYPE_MOBI', '01', '0'),
('91107543', 'VTYPE_MOBI', '01', '0'),
('91107544', 'VTYPE_MOBI', '01', '0'),
('91107545', 'VTYPE_MOBI', '01', '0'),
('91107546', 'VTYPE_MOBI', '01', '0'),
('91107547', 'VTYPE_MOBI', '01', '0'),
('91107548', 'VTYPE_MOBI', '01', '0'),
('91107549', 'VTYPE_MOBI', '01', '0'),
('91107550', 'VTYPE_MOBI', '01', '0'),
('91107551', 'VTYPE_MOBI', '01', '0'),
('91107552', 'VTYPE_MOBI', '01', '0'),
('91107553', 'VTYPE_MOBI', '01', '0'),
('91107554', 'VTYPE_MOBI', '01', '0'),
('91107555', 'MTYPE_SILV', '05', '0'),
('91107556', 'VTYPE_MOBI', '01', '0'),
('91107557', 'VTYPE_MOBI', '01', '0'),
('91107559', 'VTYPE_MOBI', '01', '0'),
('91107560', 'VTYPE_MOBI', '01', '0'),
('91107561', 'VTYPE_MOBI', '01', '0'),
('91107562', 'VTYPE_MOBI', '01', '0'),
('91107563', 'VTYPE_MOBI', '01', '0'),
('91107564', 'VTYPE_MOBI', '01', '0'),
('91107565', 'VTYPE_MOBI', '01', '0'),
('91107567', 'VTYPE_MOBI', '01', '0'),
('91107568', 'VTYPE_MOBI', '01', '0'),
('91107569', 'VTYPE_MOBI', '01', '0'),
('91107570', 'VTYPE_MOBI', '01', '0'),
('91107571', 'VTYPE_MOBI', '01', '0'),
('91107572', 'VTYPE_MOBI', '01', '0'),
('91107573', 'VTYPE_MOBI', '01', '0'),
('91107574', 'VTYPE_MOBI', '01', '0'),
('91107575', 'MTYPE_BRON', '04', '0'),
('91107576', 'VTYPE_MOBI', '01', '0'),
('91107577', 'VTYPE_MOBI', '01', '0'),
('91107578', 'VTYPE_MOBI', '01', '0'),
('91107580', 'VTYPE_MOBI', '01', '0'),
('91107581', 'VTYPE_MOBI', '01', '0'),
('91107582', 'VTYPE_MOBI', '01', '0'),
('91107583', 'VTYPE_MOBI', '01', '0'),
('91107584', 'VTYPE_MOBI', '01', '0'),
('91107585', 'VTYPE_MOBI', '01', '0'),
('91107586', 'VTYPE_MOBI', '01', '0'),
('91107587', 'VTYPE_MOBI', '01', '0'),
('91107588', 'VTYPE_MOBI', '01', '0'),
('91107589', 'VTYPE_MOBI', '01', '0'),
('91107590', 'VTYPE_MOBI', '01', '0'),
('91107591', 'VTYPE_MOBI', '01', '0'),
('91107592', 'VTYPE_MOBI', '01', '0'),
('91107593', 'VTYPE_MOBI', '01', '0'),
('91107594', 'VTYPE_MOBI', '01', '0'),
('91107595', 'VTYPE_MOBI', '01', '0'),
('91107596', 'VTYPE_MOBI', '01', '0'),
('91107598', 'VTYPE_MOBI', '01', '0'),
('91107599', 'VTYPE_MOBI', '01', '0'),
('91107600', 'VTYPE_MOBI', '01', '0'),
('91107602', 'VTYPE_MOBI', '01', '0'),
('91107604', 'VTYPE_MOBI', '01', '0'),
('91107605', 'VTYPE_MOBI', '01', '0'),
('91107606', 'VTYPE_MOBI', '01', '0'),
('91107607', 'VTYPE_MOBI', '01', '0'),
('91107608', 'VTYPE_MOBI', '01', '0'),
('91107609', 'VTYPE_MOBI', '01', '0'),
('91107610', 'VTYPE_MOBI', '01', '0'),
('91107611', 'VTYPE_MOBI', '01', '0'),
('91107612', 'VTYPE_MOBI', '01', '0'),
('91107613', 'VTYPE_MOBI', '01', '0'),
('91107615', 'VTYPE_MOBI', '01', '0'),
('91107616', 'VTYPE_MOBI', '01', '0'),
('91107617', 'VTYPE_MOBI', '01', '0'),
('91107618', 'VTYPE_MOBI', '01', '0'),
('91107619', 'VTYPE_MOBI', '01', '0'),
('91107620', 'VTYPE_MOBI', '01', '0'),
('91107621', 'VTYPE_MOBI', '01', '0'),
('91107622', 'VTYPE_MOBI', '01', '0'),
('91107623', 'VTYPE_MOBI', '01', '0'),
('91107624', 'VTYPE_MOBI', '01', '0'),
('91107625', 'VTYPE_MOBI', '01', '0'),
('91107626', 'VTYPE_MOBI', '01', '0'),
('91107627', 'VTYPE_MOBI', '01', '0'),
('91107628', 'VTYPE_MOBI', '01', '0'),
('91107629', 'VTYPE_MOBI', '01', '0'),
('91107630', 'VTYPE_MOBI', '01', '0'),
('91107631', 'VTYPE_MOBI', '01', '0'),
('91107632', 'VTYPE_MOBI', '01', '0'),
('91107634', 'VTYPE_MOBI', '01', '0'),
('91107635', 'VTYPE_MOBI', '01', '0'),
('91107636', 'VTYPE_MOBI', '01', '0'),
('91107637', 'VTYPE_MOBI', '01', '0'),
('91107638', 'VTYPE_MOBI', '01', '0'),
('91107639', 'VTYPE_MOBI', '01', '0'),
('91107640', 'VTYPE_MOBI', '01', '0'),
('91107641', 'VTYPE_MOBI', '01', '0'),
('91107642', 'VTYPE_MOBI', '01', '0'),
('91107644', 'VTYPE_MOBI', '01', '0'),
('91107645', 'VTYPE_MOBI', '01', '0'),
('91107647', 'VTYPE_MOBI', '01', '0'),
('91107648', 'VTYPE_MOBI', '01', '0'),
('91107650', 'VTYPE_MOBI', '01', '0'),
('91107651', 'VTYPE_MOBI', '01', '0'),
('91107654', 'VTYPE_MOBI', '01', '0'),
('91107655', 'VTYPE_MOBI', '01', '0'),
('91107656', 'VTYPE_MOBI', '01', '0'),
('91107657', 'VTYPE_MOBI', '01', '0'),
('91107658', 'VTYPE_MOBI', '01', '0'),
('91107659', 'VTYPE_MOBI', '01', '0'),
('91107660', 'VTYPE_MOBI', '01', '0'),
('91107661', 'VTYPE_MOBI', '01', '0'),
('91107662', 'VTYPE_MOBI', '01', '0'),
('91107663', 'VTYPE_MOBI', '01', '0'),
('91107664', 'VTYPE_MOBI', '01', '0'),
('91107665', 'VTYPE_MOBI', '01', '0'),
('91107666', 'MTYPE_SILV', '05', '0'),
('91107667', 'VTYPE_MOBI', '01', '0'),
('91107668', 'VTYPE_MOBI', '01', '0'),
('91107669', 'VTYPE_MOBI', '01', '0'),
('91107670', 'VTYPE_MOBI', '01', '0'),
('91107672', 'VTYPE_MOBI', '01', '0'),
('91107673', 'VTYPE_MOBI', '01', '0'),
('91107674', 'VTYPE_MOBI', '01', '0'),
('91107675', 'VTYPE_MOBI', '01', '0'),
('91107676', 'MTYPE_BRON', '04', '0'),
('91107677', 'VTYPE_MOBI', '01', '0'),
('91107679', 'VTYPE_MOBI', '01', '0'),
('91107681', 'VTYPE_MOBI', '01', '0'),
('91107683', 'VTYPE_MOBI', '01', '0'),
('91107685', 'VTYPE_MOBI', '01', '0'),
('91107687', 'VTYPE_MOBI', '01', '0'),
('91107689', 'VTYPE_MOBI', '01', '0'),
('91107691', 'VTYPE_MOBI', '01', '0'),
('91107693', 'VTYPE_MOBI', '01', '0'),
('91107695', 'VTYPE_MOBI', '01', '0'),
('91107697', 'VTYPE_MOBI', '01', '0'),
('91107699', 'VTYPE_MOBI', '01', '0'),
('91107700', 'MTYPE_BRON', '03', '0'),
('91107702', 'VTYPE_MOBI', '01', '0'),
('91107704', 'VTYPE_MOBI', '01', '0'),
('91107706', 'VTYPE_MOBI', '01', '0'),
('91107707', 'VTYPE_MOBI', '01', '0'),
('91107709', 'VTYPE_MOBI', '01', '0'),
('91107711', 'MTYPE_BRON', '03', '0'),
('91107712', 'VTYPE_MOBI', '01', '0'),
('91107714', 'VTYPE_MOBI', '01', '0'),
('91107716', 'VTYPE_MOBI', '01', '0'),
('91107717', 'VTYPE_MOBI', '01', '0'),
('91107719', 'VTYPE_MOBI', '01', '0'),
('91107721', 'VTYPE_MOBI', '01', '0'),
('91107722', 'MTYPE_BRON', '03', '0'),
('91107724', 'VTYPE_MOBI', '01', '0'),
('91107726', 'VTYPE_MOBI', '01', '0'),
('91107727', 'VTYPE_MOBI', '01', '0'),
('91107728', 'VTYPE_MOBI', '01', '0'),
('91107729', 'VTYPE_MOBI', '01', '0'),
('91107731', 'VTYPE_MOBI', '01', '0'),
('91107733', 'MTYPE_BRON', '03', '0'),
('91107734', 'VTYPE_MOBI', '01', '0'),
('91107736', 'VTYPE_MOBI', '01', '0'),
('91107737', 'VTYPE_MOBI', '01', '0'),
('91107739', 'VTYPE_MOBI', '01', '0'),
('91107741', 'VTYPE_MOBI', '01', '0'),
('91107743', 'VTYPE_MOBI', '01', '0'),
('91107744', 'MTYPE_BRON', '03', '0'),
('91107747', 'VTYPE_MOBI', '01', '0'),
('91107749', 'VTYPE_MOBI', '01', '0'),
('91107751', 'VTYPE_MOBI', '01', '0'),
('91107755', 'MTYPE_BRON', '03', '0'),
('91107756', 'VTYPE_MOBI', '01', '0'),
('91107757', 'VTYPE_MOBI', '01', '0'),
('91107759', 'VTYPE_MOBI', '01', '0'),
('91107761', 'VTYPE_MOBI', '01', '0'),
('91107763', 'VTYPE_MOBI', '01', '0'),
('91107765', 'VTYPE_MOBI', '01', '0'),
('91107766', 'MTYPE_BRON', '03', '0'),
('91107767', 'VTYPE_MOBI', '01', '0'),
('91107769', 'VTYPE_MOBI', '01', '0'),
('91107770', 'VTYPE_MOBI', '05', '0'),
('91107771', 'VTYPE_MOBI', '05', '0'),
('91107772', 'VTYPE_MOBI', '05', '0'),
('91107773', 'VTYPE_MOBI', '05', '0'),
('91107774', 'VTYPE_MOBI', '05', '0'),
('91107775', 'VTYPE_MOBI', '05', '0'),
('91107776', 'VTYPE_MOBI', '05', '0'),
('91107777', 'MTYPE_GOLD', '02', '0'),
('91107778', 'VTYPE_MOBI', '05', '0'),
('91107779', 'VTYPE_MOBI', '05', '0'),
('91107781', 'VTYPE_MOBI', '01', '0'),
('91107783', 'VTYPE_MOBI', '01', '0'),
('91107785', 'VTYPE_MOBI', '01', '0'),
('91107787', 'VTYPE_MOBI', '01', '0'),
('91107788', 'MTYPE_BRON', '03', '0'),
('91107789', 'VTYPE_MOBI', '01', '0'),
('91107791', 'VTYPE_MOBI', '01', '0'),
('91107793', 'VTYPE_MOBI', '01', '0'),
('91107797', 'VTYPE_MOBI', '01', '0'),
('91107798', 'VTYPE_MOBI', '01', '0'),
('91107799', 'MTYPE_BRON', '03', '0'),
('91107800', 'VTYPE_MOBI', '01', '0'),
('91107802', 'VTYPE_MOBI', '01', '0'),
('91107804', 'VTYPE_MOBI', '01', '0'),
('91107808', 'VTYPE_MOBI', '01', '0'),
('91107810', 'VTYPE_MOBI', '01', '0'),
('91107812', 'VTYPE_MOBI', '01', '0'),
('91107814', 'VTYPE_MOBI', '01', '0'),
('91107818', 'VTYPE_MOBI', '01', '0'),
('91107820', 'VTYPE_MOBI', '01', '0'),
('91107824', 'VTYPE_MOBI', '01', '0'),
('91107826', 'VTYPE_MOBI', '01', '0'),
('91107828', 'VTYPE_MOBI', '01', '0'),
('91107830', 'VTYPE_MOBI', '01', '0'),
('91107832', 'VTYPE_MOBI', '01', '0'),
('91107834', 'VTYPE_MOBI', '01', '0'),
('91107836', 'VTYPE_MOBI', '01', '0'),
('91107838', 'VTYPE_MOBI', '01', '0'),
('91107840', 'VTYPE_MOBI', '01', '0'),
('91107842', 'VTYPE_MOBI', '01', '0'),
('91107844', 'VTYPE_MOBI', '01', '0'),
('91107846', 'VTYPE_MOBI', '01', '0'),
('91107848', 'VTYPE_MOBI', '01', '0'),
('91107850', 'VTYPE_MOBI', '01', '0'),
('91107854', 'VTYPE_MOBI', '01', '0'),
('91107856', 'VTYPE_MOBI', '01', '0'),
('91107858', 'VTYPE_MOBI', '01', '0'),
('91107860', 'VTYPE_MOBI', '01', '0'),
('91107862', 'VTYPE_MOBI', '01', '0'),
('91107864', 'VTYPE_MOBI', '01', '0'),
('91107866', 'VTYPE_MOBI', '01', '0'),
('91107870', 'VTYPE_MOBI', '01', '0'),
('91107872', 'VTYPE_MOBI', '01', '0'),
('91107874', 'VTYPE_MOBI', '01', '0'),
('91107876', 'VTYPE_MOBI', '01', '0'),
('91107877', 'VTYPE_MOBI', '01', '0'),
('91107878', 'MTYPE_BRON', '04', '0'),
('91107880', 'VTYPE_MOBI', '01', '0'),
('91107882', 'VTYPE_MOBI', '01', '0'),
('91107884', 'VTYPE_MOBI', '01', '0'),
('91107886', 'VTYPE_MOBI', '01', '0'),
('91107887', 'VTYPE_MOBI', '01', '0'),
('91107888', 'MTYPE_SILV', '05', '0'),
('91107890', 'VTYPE_MOBI', '01', '0'),
('91107891', 'VTYPE_MOBI', '01', '0'),
('91107893', 'VTYPE_MOBI', '01', '0'),
('91107895', 'VTYPE_MOBI', '01', '0'),
('91107897', 'VTYPE_MOBI', '01', '0'),
('91107899', 'VTYPE_MOBI', '01', '0'),
('91107900', 'VTYPE_MOBI', '01', '0'),
('91107904', 'VTYPE_MOBI', '01', '0'),
('91107906', 'VTYPE_MOBI', '01', '0'),
('91107908', 'VTYPE_MOBI', '01', '0'),
('91107910', 'VTYPE_MOBI', '01', '0'),
('91107912', 'VTYPE_MOBI', '01', '0'),
('91107915', 'VTYPE_MOBI', '01', '0'),
('91107916', 'VTYPE_MOBI', '01', '0'),
('91107918', 'VTYPE_MOBI', '01', '0'),
('91107920', 'VTYPE_MOBI', '01', '0'),
('91107922', 'VTYPE_MOBI', '01', '0'),
('91107924', 'VTYPE_MOBI', '01', '0'),
('91107930', 'VTYPE_MOBI', '01', '0'),
('91107934', 'VTYPE_MOBI', '01', '0'),
('91107936', 'VTYPE_MOBI', '01', '0'),
('91107938', 'VTYPE_MOBI', '01', '0'),
('91107944', 'VTYPE_MOBI', '01', '0'),
('91107946', 'VTYPE_MOBI', '01', '0'),
('91107947', 'VTYPE_MOBI', '01', '0'),
('91107948', 'VTYPE_MOBI', '01', '0'),
('91107949', 'VTYPE_MOBI', '01', '0'),
('91107950', 'VTYPE_MOBI', '01', '0'),
('91107951', 'VTYPE_MOBI', '01', '0'),
('91107952', 'VTYPE_MOBI', '01', '0'),
('91107953', 'VTYPE_MOBI', '01', '0'),
('91107954', 'VTYPE_MOBI', '01', '0'),
('91107955', 'VTYPE_MOBI', '01', '0'),
('91107957', 'VTYPE_MOBI', '01', '0'),
('91107958', 'VTYPE_MOBI', '01', '0'),
('91107960', 'VTYPE_MOBI', '01', '0'),
('91107961', 'VTYPE_MOBI', '01', '0'),
('91107962', 'VTYPE_MOBI', '01', '0'),
('91107963', 'VTYPE_MOBI', '01', '0'),
('91107964', 'VTYPE_MOBI', '01', '0'),
('91107965', 'VTYPE_MOBI', '01', '0'),
('91107966', 'VTYPE_MOBI', '01', '0'),
('91107967', 'VTYPE_MOBI', '01', '0'),
('91107968', 'VTYPE_MOBI', '01', '0'),
('91107969', 'VTYPE_MOBI', '01', '0'),
('91107970', 'VTYPE_MOBI', '01', '0'),
('91107971', 'VTYPE_MOBI', '01', '0'),
('91107972', 'VTYPE_MOBI', '01', '0'),
('91107973', 'VTYPE_MOBI', '01', '0'),
('91107974', 'VTYPE_MOBI', '01', '0'),
('91107975', 'VTYPE_MOBI', '01', '0'),
('91107976', 'VTYPE_MOBI', '01', '0'),
('91107977', 'VTYPE_MOBI', '01', '0'),
('91107978', 'VTYPE_MOBI', '01', '0'),
('91107979', 'MTYPE_BRON', '04', '0'),
('91107980', 'VTYPE_MOBI', '01', '0'),
('91107981', 'VTYPE_MOBI', '01', '0'),
('91107982', 'VTYPE_MOBI', '01', '0'),
('91107983', 'VTYPE_MOBI', '01', '0'),
('91107984', 'VTYPE_MOBI', '01', '0'),
('91107985', 'VTYPE_MOBI', '01', '0'),
('91107986', 'VTYPE_MOBI', '01', '0'),
('91107987', 'VTYPE_MOBI', '01', '0'),
('91107988', 'VTYPE_MOBI', '01', '0'),
('91107989', 'VTYPE_MOBI', '01', '0'),
('91107990', 'VTYPE_MOBI', '01', '0'),
('91107991', 'VTYPE_MOBI', '01', '0'),
('91107992', 'VTYPE_MOBI', '01', '0'),
('91107993', 'VTYPE_MOBI', '01', '0'),
('91107994', 'VTYPE_MOBI', '01', '0'),
('91107995', 'VTYPE_MOBI', '01', '0'),
('91107997', 'VTYPE_MOBI', '01', '0'),
('91107998', 'VTYPE_MOBI', '01', '0'),
('91107999', 'MTYPE_SILV', '05', '0'),
('91108000', 'MTYPE_SILV', '05', '0'),
('91108001', 'VTYPE_MOBI', '01', '0'),
('91108002', 'VTYPE_MOBI', '01', '0'),
('91108003', 'VTYPE_MOBI', '01', '0'),
('91108004', 'VTYPE_MOBI', '01', '0'),
('91108005', 'VTYPE_MOBI', '01', '0'),
('91108006', 'VTYPE_MOBI', '01', '0'),
('91108007', 'VTYPE_MOBI', '01', '0'),
('91108008', 'VTYPE_MOBI', '01', '0'),
('91108009', 'VTYPE_MOBI', '01', '0'),
('91108010', 'VTYPE_MOBI', '01', '0'),
('91108011', 'VTYPE_MOBI', '01', '0'),
('91108012', 'VTYPE_MOBI', '01', '0'),
('91108013', 'VTYPE_MOBI', '01', '0'),
('91108014', 'VTYPE_MOBI', '01', '0'),
('91108015', 'VTYPE_MOBI', '01', '0'),
('91108016', 'VTYPE_MOBI', '01', '0'),
('91108017', 'VTYPE_MOBI', '01', '0'),
('91108018', 'VTYPE_MOBI', '01', '0'),
('91108019', 'VTYPE_MOBI', '01', '0'),
('91108020', 'VTYPE_MOBI', '01', '0'),
('91108021', 'VTYPE_MOBI', '01', '0'),
('91108022', 'VTYPE_MOBI', '01', '0'),
('91108023', 'VTYPE_MOBI', '01', '0'),
('91108024', 'VTYPE_MOBI', '01', '0'),
('91108025', 'VTYPE_MOBI', '01', '0'),
('91108026', 'VTYPE_MOBI', '01', '0'),
('91108027', 'VTYPE_MOBI', '01', '0'),
('91108028', 'VTYPE_MOBI', '01', '0'),
('91108029', 'VTYPE_MOBI', '01', '0'),
('91108030', 'VTYPE_MOBI', '01', '0'),
('91108031', 'VTYPE_MOBI', '01', '0'),
('91108032', 'VTYPE_MOBI', '01', '0'),
('91108033', 'VTYPE_MOBI', '01', '0'),
('91108034', 'VTYPE_MOBI', '01', '0'),
('91108036', 'VTYPE_MOBI', '01', '0'),
('91108037', 'VTYPE_MOBI', '01', '0'),
('91108038', 'VTYPE_MOBI', '01', '0'),
('91108039', 'VTYPE_MOBI', '01', '0'),
('91108041', 'VTYPE_MOBI', '01', '0'),
('91108042', 'VTYPE_MOBI', '01', '0'),
('91108043', 'VTYPE_MOBI', '01', '0'),
('91108045', 'VTYPE_MOBI', '01', '0'),
('91108046', 'VTYPE_MOBI', '01', '0'),
('91108047', 'VTYPE_MOBI', '01', '0'),
('91108048', 'VTYPE_MOBI', '01', '0'),
('91108049', 'VTYPE_MOBI', '01', '0'),
('91108050', 'VTYPE_MOBI', '01', '0'),
('91108051', 'VTYPE_MOBI', '01', '0'),
('91108052', 'VTYPE_MOBI', '01', '0'),
('91108053', 'VTYPE_MOBI', '01', '0'),
('91108054', 'VTYPE_MOBI', '01', '0'),
('91108055', 'VTYPE_MOBI', '01', '0'),
('91108056', 'VTYPE_MOBI', '01', '0'),
('91108058', 'VTYPE_MOBI', '01', '0'),
('91108059', 'VTYPE_MOBI', '01', '0'),
('91108060', 'VTYPE_MOBI', '01', '0'),
('91108061', 'VTYPE_MOBI', '01', '0'),
('91108062', 'VTYPE_MOBI', '01', '0'),
('91108063', 'VTYPE_MOBI', '01', '0'),
('91108064', 'VTYPE_MOBI', '01', '0'),
('91108065', 'VTYPE_MOBI', '01', '0'),
('91108066', 'VTYPE_MOBI', '01', '0'),
('91108067', 'VTYPE_MOBI', '01', '0'),
('91108068', 'VTYPE_MOBI', '01', '0'),
('91108069', 'VTYPE_MOBI', '01', '0'),
('91108070', 'VTYPE_MOBI', '01', '0'),
('91108071', 'VTYPE_MOBI', '01', '0'),
('91108072', 'VTYPE_MOBI', '01', '0'),
('91108073', 'VTYPE_MOBI', '01', '0'),
('91108074', 'VTYPE_MOBI', '01', '0'),
('91108075', 'VTYPE_MOBI', '01', '0'),
('91108076', 'VTYPE_MOBI', '01', '0'),
('91108077', 'VTYPE_MOBI', '01', '0'),
('91108078', 'VTYPE_MOBI', '01', '0'),
('91108079', 'VTYPE_MOBI', '01', '0'),
('91108080', 'MTYPE_BRON', '04', '0'),
('91108081', 'VTYPE_MOBI', '01', '0'),
('91108082', 'VTYPE_MOBI', '01', '0'),
('91108083', 'VTYPE_MOBI', '01', '0'),
('91108084', 'VTYPE_MOBI', '01', '0'),
('91108085', 'VTYPE_MOBI', '01', '0'),
('91108086', 'VTYPE_MOBI', '01', '0'),
('91108087', 'VTYPE_MOBI', '01', '0'),
('91108088', 'VTYPE_MOBI', '01', '0'),
('91108089', 'VTYPE_MOBI', '01', '0'),
('91108090', 'VTYPE_MOBI', '01', '0'),
('91108092', 'VTYPE_MOBI', '01', '0'),
('91108093', 'VTYPE_MOBI', '01', '0'),
('91108094', 'VTYPE_MOBI', '01', '0'),
('91108095', 'VTYPE_MOBI', '01', '0'),
('91108096', 'VTYPE_MOBI', '01', '0'),
('91108097', 'VTYPE_MOBI', '01', '0'),
('91108099', 'VTYPE_MOBI', '01', '0'),
('91108100', 'VTYPE_MOBI', '01', '0'),
('91108104', 'VTYPE_MOBI', '01', '0'),
('91108108', 'VTYPE_MOBI', '01', '0'),
('91108110', 'VTYPE_MOBI', '01', '0'),
('91108111', 'MTYPE_SILV', '05', '0'),
('91108113', 'VTYPE_MOBI', '01', '0'),
('91108115', 'VTYPE_MOBI', '01', '0'),
('91108117', 'VTYPE_MOBI', '01', '0'),
('91108118', 'VTYPE_MOBI', '01', '0'),
('91108122', 'VTYPE_MOBI', '01', '0'),
('91108124', 'VTYPE_MOBI', '01', '0'),
('91108126', 'VTYPE_MOBI', '01', '0'),
('91108128', 'VTYPE_MOBI', '01', '0'),
('91108130', 'VTYPE_MOBI', '01', '0'),
('91108134', 'VTYPE_MOBI', '01', '0'),
('91108136', 'VTYPE_MOBI', '01', '0'),
('91108138', 'VTYPE_MOBI', '01', '0'),
('91108140', 'VTYPE_MOBI', '01', '0'),
('91108142', 'VTYPE_MOBI', '01', '0'),
('91108144', 'VTYPE_MOBI', '01', '0'),
('91108146', 'VTYPE_MOBI', '01', '0'),
('91108148', 'VTYPE_MOBI', '01', '0'),
('91108150', 'VTYPE_MOBI', '01', '0'),
('91108152', 'VTYPE_MOBI', '01', '0'),
('91108154', 'VTYPE_MOBI', '01', '0'),
('91108158', 'VTYPE_MOBI', '01', '0'),
('91108160', 'VTYPE_MOBI', '01', '0'),
('91108162', 'VTYPE_MOBI', '01', '0'),
('91108164', 'VTYPE_MOBI', '01', '0'),
('91108166', 'VTYPE_MOBI', '01', '0'),
('91108168', 'VTYPE_MOBI', '01', '0'),
('91108170', 'VTYPE_MOBI', '01', '0'),
('91108172', 'VTYPE_MOBI', '01', '0'),
('91108176', 'VTYPE_MOBI', '01', '0'),
('91108180', 'VTYPE_MOBI', '01', '0'),
('91108181', 'MTYPE_BRON', '04', '0'),
('91108183', 'VTYPE_MOBI', '01', '0'),
('91108187', 'VTYPE_MOBI', '01', '0'),
('91108188', 'VTYPE_MOBI', '01', '0'),
('91108190', 'VTYPE_MOBI', '01', '0'),
('91108192', 'VTYPE_MOBI', '01', '0'),
('91108194', 'VTYPE_MOBI', '01', '0'),
('91108196', 'VTYPE_MOBI', '01', '0'),
('91108198', 'VTYPE_MOBI', '01', '0'),
('91108200', 'VTYPE_MOBI', '01', '0'),
('91108201', 'VTYPE_MOBI', '01', '0'),
('91108203', 'VTYPE_MOBI', '01', '0'),
('91108205', 'VTYPE_MOBI', '01', '0'),
('91108209', 'VTYPE_MOBI', '01', '0'),
('91108211', 'VTYPE_MOBI', '01', '0'),
('91108213', 'VTYPE_MOBI', '01', '0'),
('91108215', 'VTYPE_MOBI', '01', '0'),
('91108217', 'VTYPE_MOBI', '01', '0'),
('91108219', 'VTYPE_MOBI', '01', '0'),
('91108221', 'VTYPE_MOBI', '01', '0'),
('91108222', 'MTYPE_SILV', '05', '0'),
('91108224', 'VTYPE_MOBI', '01', '0'),
('91108226', 'VTYPE_MOBI', '01', '0'),
('91108227', 'VTYPE_MOBI', '01', '0'),
('91108228', 'VTYPE_MOBI', '01', '0'),
('91108229', 'VTYPE_MOBI', '01', '0'),
('91108231', 'VTYPE_MOBI', '01', '0'),
('91108235', 'VTYPE_MOBI', '01', '0'),
('91108237', 'VTYPE_MOBI', '01', '0'),
('91108239', 'VTYPE_MOBI', '01', '0'),
('91108241', 'VTYPE_MOBI', '01', '0'),
('91108243', 'VTYPE_MOBI', '01', '0'),
('91108245', 'VTYPE_MOBI', '01', '0'),
('91108247', 'VTYPE_MOBI', '01', '0'),
('91108249', 'VTYPE_MOBI', '01', '0'),
('91108251', 'VTYPE_MOBI', '01', '0'),
('91108255', 'VTYPE_MOBI', '01', '0'),
('91108259', 'VTYPE_MOBI', '01', '0'),
('91108263', 'VTYPE_MOBI', '01', '0'),
('91108265', 'VTYPE_MOBI', '01', '0'),
('91108267', 'VTYPE_MOBI', '01', '0'),
('91108273', 'VTYPE_MOBI', '01', '0'),
('91108277', 'VTYPE_MOBI', '01', '0'),
('91108279', 'VTYPE_MOBI', '01', '0'),
('91108281', 'VTYPE_MOBI', '01', '0'),
('91108282', 'MTYPE_BRON', '04', '0'),
('91108286', 'VTYPE_MOBI', '01', '0'),
('91108288', 'VTYPE_MOBI', '01', '0'),
('91108289', 'VTYPE_MOBI', '01', '0'),
('91108291', 'VTYPE_MOBI', '01', '0'),
('91108293', 'VTYPE_MOBI', '01', '0'),
('91108295', 'VTYPE_MOBI', '01', '0'),
('91108299', 'VTYPE_MOBI', '01', '0'),
('91108300', 'VTYPE_MOBI', '01', '0'),
('91108304', 'VTYPE_MOBI', '01', '0'),
('91108306', 'VTYPE_MOBI', '01', '0'),
('91108308', 'VTYPE_MOBI', '01', '0'),
('91108310', 'VTYPE_MOBI', '01', '0'),
('91108312', 'VTYPE_MOBI', '01', '0'),
('91108314', 'VTYPE_MOBI', '01', '0'),
('91108316', 'VTYPE_MOBI', '01', '0'),
('91108320', 'VTYPE_MOBI', '01', '0'),
('91108324', 'VTYPE_MOBI', '01', '0'),
('91108326', 'VTYPE_MOBI', '01', '0'),
('91108328', 'VTYPE_MOBI', '01', '0'),
('91108330', 'VTYPE_MOBI', '01', '0'),
('91108332', 'VTYPE_MOBI', '01', '0'),
('91108333', 'MTYPE_SILV', '05', '0'),
('91108337', 'VTYPE_MOBI', '01', '0'),
('91108338', 'VTYPE_MOBI', '01', '0'),
('91108340', 'VTYPE_MOBI', '01', '0'),
('91108342', 'VTYPE_MOBI', '01', '0'),
('91108343', 'VTYPE_MOBI', '01', '0'),
('91108344', 'VTYPE_MOBI', '01', '0'),
('91108346', 'VTYPE_MOBI', '01', '0'),
('91108347', 'VTYPE_MOBI', '01', '0'),
('91108348', 'VTYPE_MOBI', '01', '0'),
('91108350', 'VTYPE_MOBI', '01', '0'),
('91108352', 'VTYPE_MOBI', '01', '0'),
('91108354', 'VTYPE_MOBI', '01', '0'),
('91108356', 'VTYPE_MOBI', '01', '0'),
('91108358', 'VTYPE_MOBI', '01', '0'),
('91108360', 'VTYPE_MOBI', '01', '0'),
('91108362', 'VTYPE_MOBI', '01', '0'),
('91108364', 'VTYPE_MOBI', '01', '0'),
('91108365', 'VTYPE_MOBI', '01', '0'),
('91108366', 'VTYPE_MOBI', '01', '0'),
('91108368', 'VTYPE_MOBI', '01', '0'),
('91108369', 'VTYPE_MOBI', '01', '0'),
('91108370', 'VTYPE_MOBI', '01', '0'),
('91108371', 'VTYPE_MOBI', '01', '0'),
('91108372', 'VTYPE_MOBI', '01', '0'),
('91108374', 'VTYPE_MOBI', '01', '0'),
('91108375', 'VTYPE_MOBI', '01', '0'),
('91108376', 'VTYPE_MOBI', '01', '0'),
('91108377', 'VTYPE_MOBI', '01', '0'),
('91108378', 'VTYPE_MOBI', '01', '0'),
('91108379', 'VTYPE_MOBI', '01', '0'),
('91108380', 'VTYPE_MOBI', '01', '0'),
('91108381', 'VTYPE_MOBI', '01', '0');
INSERT INTO `ocs_account_key` (`account_key`, `account_key_type`, `status`, `sales_flag`) VALUES
('91108382', 'VTYPE_MOBI', '01', '0'),
('91108383', 'MTYPE_BRON', '04', '0'),
('91108384', 'VTYPE_MOBI', '01', '0'),
('91108385', 'VTYPE_MOBI', '01', '0'),
('91108386', 'VTYPE_MOBI', '01', '0'),
('91108387', 'VTYPE_MOBI', '01', '0'),
('91108388', 'VTYPE_MOBI', '01', '0'),
('91108389', 'VTYPE_MOBI', '01', '0'),
('91108391', 'VTYPE_MOBI', '01', '0'),
('91108392', 'VTYPE_MOBI', '01', '0'),
('91108393', 'VTYPE_MOBI', '01', '0'),
('91108394', 'VTYPE_MOBI', '01', '0'),
('91108395', 'VTYPE_MOBI', '01', '0'),
('91108396', 'VTYPE_MOBI', '01', '0'),
('91108398', 'VTYPE_MOBI', '01', '0'),
('91108399', 'VTYPE_MOBI', '01', '0'),
('91108400', 'VTYPE_MOBI', '01', '0'),
('91108401', 'VTYPE_MOBI', '01', '0'),
('91108402', 'VTYPE_MOBI', '01', '0'),
('91108403', 'VTYPE_MOBI', '01', '0'),
('91108404', 'VTYPE_MOBI', '01', '0'),
('91108405', 'VTYPE_MOBI', '01', '0'),
('91108407', 'VTYPE_MOBI', '01', '0'),
('91108408', 'VTYPE_MOBI', '01', '0'),
('91108409', 'VTYPE_MOBI', '01', '0'),
('91108410', 'VTYPE_MOBI', '01', '0'),
('91108411', 'VTYPE_MOBI', '01', '0'),
('91108412', 'VTYPE_MOBI', '01', '0'),
('91108413', 'VTYPE_MOBI', '01', '0'),
('91108414', 'VTYPE_MOBI', '01', '0'),
('91108415', 'VTYPE_MOBI', '01', '0'),
('91108417', 'VTYPE_MOBI', '01', '0'),
('91108418', 'VTYPE_MOBI', '01', '0'),
('91108419', 'VTYPE_MOBI', '01', '0'),
('91108422', 'VTYPE_MOBI', '01', '0'),
('91108423', 'VTYPE_MOBI', '01', '0'),
('91108424', 'VTYPE_MOBI', '01', '0'),
('91108425', 'VTYPE_MOBI', '01', '0'),
('91108426', 'VTYPE_MOBI', '01', '0'),
('91108428', 'VTYPE_MOBI', '01', '0'),
('91108429', 'VTYPE_MOBI', '01', '0'),
('91108430', 'VTYPE_MOBI', '01', '0'),
('91108431', 'VTYPE_MOBI', '01', '0'),
('91108432', 'VTYPE_MOBI', '01', '0'),
('91108434', 'VTYPE_MOBI', '01', '0'),
('91108435', 'VTYPE_MOBI', '01', '0'),
('91108436', 'VTYPE_MOBI', '01', '0'),
('91108438', 'VTYPE_MOBI', '01', '0'),
('91108440', 'VTYPE_MOBI', '01', '0'),
('91108441', 'VTYPE_MOBI', '01', '0'),
('91108442', 'VTYPE_MOBI', '01', '0'),
('91108443', 'VTYPE_MOBI', '01', '0'),
('91108444', 'MTYPE_SILV', '05', '0'),
('91108445', 'VTYPE_MOBI', '01', '0'),
('91108446', 'VTYPE_MOBI', '01', '0'),
('91108447', 'VTYPE_MOBI', '01', '0'),
('91108448', 'VTYPE_MOBI', '01', '0'),
('91108449', 'VTYPE_MOBI', '01', '0'),
('91108450', 'VTYPE_MOBI', '01', '0'),
('91108451', 'VTYPE_MOBI', '01', '0'),
('91108453', 'VTYPE_MOBI', '01', '0'),
('91108454', 'VTYPE_MOBI', '01', '0'),
('91108455', 'VTYPE_MOBI', '01', '0'),
('91108456', 'VTYPE_MOBI', '01', '0'),
('91108457', 'VTYPE_MOBI', '01', '0'),
('91108458', 'VTYPE_MOBI', '01', '0'),
('91108460', 'VTYPE_MOBI', '01', '0'),
('91108462', 'VTYPE_MOBI', '01', '0'),
('91108464', 'VTYPE_MOBI', '01', '0'),
('91108466', 'VTYPE_MOBI', '01', '0'),
('91108467', 'VTYPE_MOBI', '01', '0'),
('91108468', 'VTYPE_MOBI', '01', '0'),
('91108469', 'VTYPE_MOBI', '01', '0'),
('91108470', 'VTYPE_MOBI', '01', '0'),
('91108471', 'VTYPE_MOBI', '01', '0'),
('91108472', 'VTYPE_MOBI', '01', '0'),
('91108474', 'VTYPE_MOBI', '01', '0'),
('91108475', 'VTYPE_MOBI', '01', '0'),
('91108476', 'VTYPE_MOBI', '01', '0'),
('91108477', 'VTYPE_MOBI', '01', '0'),
('91108480', 'VTYPE_MOBI', '01', '0'),
('91108481', 'VTYPE_MOBI', '01', '0'),
('91108482', 'VTYPE_MOBI', '01', '0'),
('91108483', 'VTYPE_MOBI', '01', '0'),
('91108484', 'MTYPE_BRON', '04', '0'),
('91108485', 'VTYPE_MOBI', '01', '0'),
('91108486', 'VTYPE_MOBI', '01', '0'),
('91108487', 'VTYPE_MOBI', '01', '0'),
('91108488', 'VTYPE_MOBI', '01', '0'),
('91108492', 'VTYPE_MOBI', '01', '0'),
('91108493', 'VTYPE_MOBI', '01', '0'),
('91108494', 'VTYPE_MOBI', '01', '0'),
('91108495', 'VTYPE_MOBI', '01', '0'),
('91108497', 'VTYPE_MOBI', '01', '0'),
('91108498', 'VTYPE_MOBI', '01', '0'),
('91108499', 'VTYPE_MOBI', '01', '0'),
('91108500', 'VTYPE_MOBI', '01', '0'),
('91108501', 'VTYPE_MOBI', '01', '0'),
('91108502', 'VTYPE_MOBI', '01', '0'),
('91108503', 'VTYPE_MOBI', '01', '0'),
('91108504', 'VTYPE_MOBI', '01', '0'),
('91108505', 'VTYPE_MOBI', '01', '0'),
('91108506', 'VTYPE_MOBI', '01', '0'),
('91108507', 'VTYPE_MOBI', '01', '0'),
('91108508', 'VTYPE_MOBI', '01', '0'),
('91108509', 'VTYPE_MOBI', '01', '0'),
('91108514', 'VTYPE_MOBI', '01', '0'),
('91108520', 'VTYPE_MOBI', '01', '0'),
('91108522', 'VTYPE_MOBI', '01', '0'),
('91108524', 'VTYPE_MOBI', '01', '0'),
('91108526', 'VTYPE_MOBI', '01', '0'),
('91108528', 'VTYPE_MOBI', '01', '0'),
('91108530', 'VTYPE_MOBI', '01', '0'),
('91108534', 'VTYPE_MOBI', '01', '0'),
('91108538', 'VTYPE_MOBI', '01', '0'),
('91108540', 'VTYPE_MOBI', '01', '0'),
('91108544', 'VTYPE_MOBI', '01', '0'),
('91108548', 'VTYPE_MOBI', '01', '0'),
('91108550', 'VTYPE_MOBI', '01', '0'),
('91108552', 'VTYPE_MOBI', '01', '0'),
('91108554', 'VTYPE_MOBI', '01', '0'),
('91108555', 'MTYPE_SILV', '05', '0'),
('91108557', 'VTYPE_MOBI', '01', '0'),
('91108558', 'VTYPE_MOBI', '01', '0'),
('91108560', 'VTYPE_MOBI', '01', '0'),
('91108562', 'VTYPE_MOBI', '01', '0'),
('91108566', 'VTYPE_MOBI', '01', '0'),
('91108568', 'VTYPE_MOBI', '01', '0'),
('91108570', 'VTYPE_MOBI', '01', '0'),
('91108572', 'VTYPE_MOBI', '01', '0'),
('91108574', 'VTYPE_MOBI', '01', '0'),
('91108578', 'VTYPE_MOBI', '01', '0'),
('91108580', 'VTYPE_MOBI', '01', '0'),
('91108582', 'VTYPE_MOBI', '01', '0'),
('91108584', 'VTYPE_MOBI', '01', '0'),
('91108585', 'MTYPE_BRON', '04', '0'),
('91108587', 'VTYPE_MOBI', '01', '0'),
('91108588', 'VTYPE_MOBI', '01', '0'),
('91108590', 'VTYPE_MOBI', '01', '0'),
('91108592', 'VTYPE_MOBI', '01', '0'),
('91108596', 'VTYPE_MOBI', '01', '0'),
('91108598', 'VTYPE_MOBI', '01', '0'),
('91108600', 'VTYPE_MOBI', '01', '0'),
('91108601', 'VTYPE_MOBI', '01', '0'),
('91108605', 'VTYPE_MOBI', '01', '0'),
('91108607', 'VTYPE_MOBI', '01', '0'),
('91108609', 'VTYPE_MOBI', '01', '0'),
('91108616', 'VTYPE_MOBI', '01', '0'),
('91108618', 'VTYPE_MOBI', '01', '0'),
('91108622', 'VTYPE_MOBI', '01', '0'),
('91108624', 'VTYPE_MOBI', '01', '0'),
('91108626', 'VTYPE_MOBI', '01', '0'),
('91108628', 'VTYPE_MOBI', '01', '0'),
('91108630', 'VTYPE_MOBI', '01', '0'),
('91108636', 'VTYPE_MOBI', '01', '0'),
('91108638', 'VTYPE_MOBI', '01', '0'),
('91108640', 'VTYPE_MOBI', '01', '0'),
('91108642', 'VTYPE_MOBI', '01', '0'),
('91108644', 'VTYPE_MOBI', '01', '0'),
('91108646', 'VTYPE_MOBI', '01', '0'),
('91108648', 'VTYPE_MOBI', '01', '0'),
('91108650', 'VTYPE_MOBI', '01', '0'),
('91108652', 'VTYPE_MOBI', '01', '0'),
('91108654', 'VTYPE_MOBI', '01', '0'),
('91108656', 'VTYPE_MOBI', '01', '0'),
('91108658', 'VTYPE_MOBI', '01', '0'),
('91108660', 'VTYPE_MOBI', '01', '0'),
('91108662', 'VTYPE_MOBI', '01', '0'),
('91108664', 'VTYPE_MOBI', '01', '0'),
('91108666', 'MTYPE_SILV', '05', '0'),
('91108667', 'VTYPE_MOBI', '01', '0'),
('91108668', 'VTYPE_MOBI', '01', '0'),
('91108672', 'VTYPE_MOBI', '01', '0'),
('91108674', 'VTYPE_MOBI', '01', '0'),
('91108676', 'VTYPE_MOBI', '01', '0'),
('91108678', 'VTYPE_MOBI', '01', '0'),
('91108680', 'VTYPE_MOBI', '01', '0'),
('91108682', 'VTYPE_MOBI', '01', '0'),
('91108684', 'VTYPE_MOBI', '01', '0'),
('91108686', 'MTYPE_BRON', '04', '0'),
('91108687', 'VTYPE_MOBI', '01', '0'),
('91108688', 'VTYPE_MOBI', '01', '0'),
('91108690', 'VTYPE_MOBI', '01', '0'),
('91108694', 'VTYPE_MOBI', '01', '0'),
('91108696', 'VTYPE_MOBI', '01', '0'),
('91108698', 'VTYPE_MOBI', '01', '0'),
('91108700', 'VTYPE_MOBI', '01', '0'),
('91108701', 'VTYPE_MOBI', '01', '0'),
('91108703', 'VTYPE_MOBI', '01', '0'),
('91108705', 'VTYPE_MOBI', '01', '0'),
('91108707', 'VTYPE_MOBI', '01', '0'),
('91108709', 'VTYPE_MOBI', '01', '0'),
('91108711', 'VTYPE_MOBI', '01', '0'),
('91108713', 'VTYPE_MOBI', '01', '0'),
('91108717', 'VTYPE_MOBI', '01', '0'),
('91108719', 'VTYPE_MOBI', '01', '0'),
('91108721', 'VTYPE_MOBI', '01', '0'),
('91108723', 'VTYPE_MOBI', '01', '0'),
('91108725', 'VTYPE_MOBI', '01', '0'),
('91108727', 'VTYPE_MOBI', '01', '0'),
('91108729', 'VTYPE_MOBI', '01', '0'),
('91108733', 'VTYPE_MOBI', '01', '0'),
('91108735', 'VTYPE_MOBI', '01', '0'),
('91108737', 'VTYPE_MOBI', '01', '0'),
('91108745', 'VTYPE_MOBI', '01', '0'),
('91108747', 'VTYPE_MOBI', '01', '0'),
('91108749', 'VTYPE_MOBI', '01', '0'),
('91108757', 'VTYPE_MOBI', '01', '0'),
('91108759', 'VTYPE_MOBI', '01', '0'),
('91108761', 'VTYPE_MOBI', '01', '0'),
('91108765', 'VTYPE_MOBI', '01', '0'),
('91108766', 'VTYPE_MOBI', '01', '0'),
('91108768', 'VTYPE_MOBI', '01', '0'),
('91108770', 'VTYPE_MOBI', '01', '0'),
('91108772', 'VTYPE_MOBI', '01', '0'),
('91108774', 'VTYPE_MOBI', '01', '0'),
('91108776', 'VTYPE_MOBI', '01', '0'),
('91108777', 'MTYPE_SILV', '05', '0'),
('91108778', 'VTYPE_MOBI', '01', '0'),
('91108780', 'VTYPE_MOBI', '01', '0'),
('91108782', 'VTYPE_MOBI', '01', '0'),
('91108783', 'VTYPE_MOBI', '01', '0'),
('91108784', 'VTYPE_MOBI', '01', '0'),
('91108785', 'VTYPE_MOBI', '01', '0'),
('91108786', 'VTYPE_MOBI', '01', '0'),
('91108787', 'MTYPE_BRON', '04', '0'),
('91108788', 'VTYPE_MOBI', '01', '0'),
('91108789', 'VTYPE_MOBI', '01', '0'),
('91108790', 'VTYPE_MOBI', '01', '0'),
('91108792', 'VTYPE_MOBI', '01', '0'),
('91108794', 'VTYPE_MOBI', '01', '0'),
('91108797', 'VTYPE_MOBI', '01', '0'),
('91108798', 'VTYPE_MOBI', '01', '0'),
('91108799', 'VTYPE_MOBI', '01', '0'),
('91108800', 'MTYPE_BRON', '03', '0'),
('91108801', 'VTYPE_MOBI', '01', '0'),
('91108802', 'VTYPE_MOBI', '01', '0'),
('91108803', 'VTYPE_MOBI', '01', '0'),
('91108804', 'VTYPE_MOBI', '01', '0'),
('91108805', 'VTYPE_MOBI', '01', '0'),
('91108806', 'VTYPE_MOBI', '01', '0'),
('91108807', 'VTYPE_MOBI', '01', '0'),
('91108808', 'VTYPE_MOBI', '01', '0'),
('91108809', 'VTYPE_MOBI', '01', '0'),
('91108810', 'VTYPE_MOBI', '01', '0'),
('91108811', 'MTYPE_BRON', '03', '0'),
('91108813', 'VTYPE_MOBI', '01', '0'),
('91108814', 'VTYPE_MOBI', '01', '0'),
('91108815', 'VTYPE_MOBI', '01', '0'),
('91108816', 'VTYPE_MOBI', '01', '0'),
('91108817', 'VTYPE_MOBI', '01', '0'),
('91108818', 'VTYPE_MOBI', '01', '0'),
('91108819', 'VTYPE_MOBI', '01', '0'),
('91108820', 'VTYPE_MOBI', '01', '0'),
('91108821', 'VTYPE_MOBI', '01', '0'),
('91108822', 'MTYPE_BRON', '03', '0'),
('91108824', 'VTYPE_MOBI', '01', '0'),
('91108825', 'VTYPE_MOBI', '01', '0'),
('91108826', 'VTYPE_MOBI', '01', '0'),
('91108827', 'VTYPE_MOBI', '01', '0'),
('91108828', 'VTYPE_MOBI', '01', '0'),
('91108829', 'VTYPE_MOBI', '01', '0'),
('91108830', 'VTYPE_MOBI', '01', '0'),
('91108831', 'VTYPE_MOBI', '01', '0'),
('91108832', 'VTYPE_MOBI', '01', '0'),
('91108833', 'MTYPE_BRON', '03', '0'),
('91108834', 'VTYPE_MOBI', '01', '0'),
('91108835', 'VTYPE_MOBI', '01', '0'),
('91108836', 'VTYPE_MOBI', '01', '0'),
('91108837', 'VTYPE_MOBI', '01', '0'),
('91108838', 'VTYPE_MOBI', '01', '0'),
('91108839', 'VTYPE_MOBI', '01', '0'),
('91108840', 'VTYPE_MOBI', '01', '0'),
('91108841', 'VTYPE_MOBI', '01', '0'),
('91108842', 'VTYPE_MOBI', '01', '0'),
('91108843', 'VTYPE_MOBI', '01', '0'),
('91108844', 'MTYPE_BRON', '03', '0'),
('91108845', 'VTYPE_MOBI', '01', '0'),
('91108846', 'VTYPE_MOBI', '01', '0'),
('91108847', 'VTYPE_MOBI', '01', '0'),
('91108848', 'VTYPE_MOBI', '01', '0'),
('91108849', 'VTYPE_MOBI', '01', '0'),
('91108850', 'VTYPE_MOBI', '01', '0'),
('91108851', 'VTYPE_MOBI', '01', '0'),
('91108853', 'VTYPE_MOBI', '01', '0'),
('91108854', 'VTYPE_MOBI', '01', '0'),
('91108855', 'MTYPE_BRON', '03', '0'),
('91108856', 'VTYPE_MOBI', '01', '0'),
('91108857', 'VTYPE_MOBI', '01', '0'),
('91108858', 'VTYPE_MOBI', '01', '0'),
('91108859', 'VTYPE_MOBI', '01', '0'),
('91108860', 'VTYPE_MOBI', '01', '0'),
('91108862', 'VTYPE_MOBI', '01', '0'),
('91108863', 'VTYPE_MOBI', '01', '0'),
('91108864', 'VTYPE_MOBI', '01', '0'),
('91108865', 'VTYPE_MOBI', '01', '0'),
('91108866', 'MTYPE_BRON', '03', '0'),
('91108867', 'VTYPE_MOBI', '01', '0'),
('91108868', 'VTYPE_MOBI', '01', '0'),
('91108869', 'VTYPE_MOBI', '01', '0'),
('91108870', 'VTYPE_MOBI', '01', '0'),
('91108871', 'VTYPE_MOBI', '01', '0'),
('91108872', 'VTYPE_MOBI', '01', '0'),
('91108873', 'VTYPE_MOBI', '01', '0'),
('91108874', 'VTYPE_MOBI', '01', '0'),
('91108875', 'VTYPE_MOBI', '01', '0'),
('91108876', 'VTYPE_MOBI', '01', '0'),
('91108877', 'MTYPE_BRON', '03', '0'),
('91108878', 'VTYPE_MOBI', '01', '0'),
('91108879', 'VTYPE_MOBI', '01', '0'),
('91108880', 'VTYPE_MOBI', '05', '0'),
('91108881', 'VTYPE_MOBI', '05', '0'),
('91108882', 'VTYPE_MOBI', '05', '0'),
('91108883', 'VTYPE_MOBI', '05', '0'),
('91108884', 'VTYPE_MOBI', '05', '0'),
('91108885', 'VTYPE_MOBI', '05', '0'),
('91108886', 'VTYPE_MOBI', '05', '0'),
('91108887', 'VTYPE_MOBI', '05', '0'),
('91108888', 'MTYPE_GOLD', '02', '0'),
('91108889', 'VTYPE_MOBI', '05', '0'),
('91108891', 'VTYPE_MOBI', '01', '0'),
('91108892', 'VTYPE_MOBI', '01', '0'),
('91108893', 'VTYPE_MOBI', '01', '0'),
('91108894', 'VTYPE_MOBI', '01', '0'),
('91108896', 'VTYPE_MOBI', '01', '0'),
('91108897', 'VTYPE_MOBI', '01', '0'),
('91108898', 'VTYPE_MOBI', '01', '0'),
('91108899', 'MTYPE_BRON', '03', '0'),
('91108900', 'VTYPE_MOBI', '01', '0'),
('91108901', 'VTYPE_MOBI', '01', '0'),
('91108902', 'VTYPE_MOBI', '01', '0'),
('91108903', 'VTYPE_MOBI', '01', '0'),
('91108905', 'VTYPE_MOBI', '01', '0'),
('91108906', 'VTYPE_MOBI', '01', '0'),
('91108907', 'VTYPE_MOBI', '01', '0'),
('91108908', 'VTYPE_MOBI', '01', '0'),
('91108909', 'VTYPE_MOBI', '01', '0'),
('91108911', 'VTYPE_MOBI', '01', '0'),
('91108912', 'VTYPE_MOBI', '01', '0'),
('91108913', 'VTYPE_MOBI', '01', '0'),
('91108914', 'VTYPE_MOBI', '01', '0'),
('91108916', 'VTYPE_MOBI', '01', '0'),
('91108917', 'VTYPE_MOBI', '01', '0'),
('91108918', 'VTYPE_MOBI', '01', '0'),
('91108919', 'VTYPE_MOBI', '01', '0'),
('91108920', 'VTYPE_MOBI', '01', '0'),
('91108921', 'VTYPE_MOBI', '01', '0'),
('91108922', 'VTYPE_MOBI', '01', '0'),
('91108923', 'VTYPE_MOBI', '01', '0'),
('91108924', 'VTYPE_MOBI', '01', '0'),
('91108925', 'VTYPE_MOBI', '01', '0'),
('91108926', 'VTYPE_MOBI', '01', '0'),
('91108927', 'VTYPE_MOBI', '01', '0'),
('91108928', 'VTYPE_MOBI', '01', '0'),
('91108929', 'VTYPE_MOBI', '01', '0'),
('91108930', 'VTYPE_MOBI', '01', '0'),
('91108933', 'VTYPE_MOBI', '01', '0'),
('91108935', 'VTYPE_MOBI', '01', '0'),
('91108936', 'VTYPE_MOBI', '01', '0'),
('91108937', 'VTYPE_MOBI', '01', '0'),
('91108939', 'VTYPE_MOBI', '01', '0'),
('91108941', 'VTYPE_MOBI', '01', '0'),
('91108942', 'VTYPE_MOBI', '01', '0'),
('91108943', 'VTYPE_MOBI', '01', '0'),
('91108944', 'VTYPE_MOBI', '01', '0'),
('91108948', 'VTYPE_MOBI', '01', '0'),
('91108950', 'VTYPE_MOBI', '01', '0'),
('91108952', 'VTYPE_MOBI', '01', '0'),
('91108954', 'VTYPE_MOBI', '01', '0'),
('91108958', 'VTYPE_MOBI', '01', '0'),
('91108960', 'VTYPE_MOBI', '01', '0'),
('91108962', 'VTYPE_MOBI', '01', '0'),
('91108964', 'VTYPE_MOBI', '01', '0'),
('91108966', 'VTYPE_MOBI', '01', '0'),
('91108968', 'VTYPE_MOBI', '01', '0'),
('91108970', 'VTYPE_MOBI', '01', '0'),
('91108974', 'VTYPE_MOBI', '01', '0'),
('91108976', 'VTYPE_MOBI', '01', '0'),
('91108978', 'VTYPE_MOBI', '01', '0'),
('91108980', 'VTYPE_MOBI', '01', '0'),
('91108984', 'VTYPE_MOBI', '01', '0'),
('91108986', 'VTYPE_MOBI', '01', '0'),
('91108988', 'VTYPE_MOBI', '01', '0'),
('91108989', 'MTYPE_BRON', '04', '0'),
('91108990', 'VTYPE_MOBI', '01', '0'),
('91108992', 'VTYPE_MOBI', '01', '0'),
('91108994', 'VTYPE_MOBI', '01', '0'),
('91108996', 'VTYPE_MOBI', '01', '0'),
('91108998', 'VTYPE_MOBI', '01', '0'),
('91108999', 'MTYPE_SILV', '05', '0'),
('91109000', 'MTYPE_SILV', '05', '0'),
('91109001', 'VTYPE_MOBI', '01', '0'),
('91109002', 'VTYPE_MOBI', '01', '0'),
('91109003', 'VTYPE_MOBI', '01', '0'),
('91109004', 'VTYPE_MOBI', '01', '0'),
('91109006', 'VTYPE_MOBI', '01', '0'),
('91109008', 'VTYPE_MOBI', '01', '0'),
('91109009', 'VTYPE_MOBI', '01', '0'),
('91109011', 'VTYPE_MOBI', '01', '0'),
('91109013', 'VTYPE_MOBI', '01', '0'),
('91109017', 'VTYPE_MOBI', '01', '0'),
('91109019', 'VTYPE_MOBI', '01', '0'),
('91109021', 'VTYPE_MOBI', '01', '0'),
('91109023', 'VTYPE_MOBI', '01', '0'),
('91109025', 'VTYPE_MOBI', '01', '0'),
('91109027', 'VTYPE_MOBI', '01', '0'),
('91109029', 'VTYPE_MOBI', '01', '0'),
('91109031', 'VTYPE_MOBI', '01', '0'),
('91109033', 'VTYPE_MOBI', '01', '0'),
('91109035', 'VTYPE_MOBI', '01', '0'),
('91109041', 'VTYPE_MOBI', '01', '0'),
('91109043', 'VTYPE_MOBI', '01', '0'),
('91109045', 'VTYPE_MOBI', '01', '0'),
('91109049', 'VTYPE_MOBI', '01', '0'),
('91109053', 'VTYPE_MOBI', '01', '0'),
('91109055', 'VTYPE_MOBI', '01', '0'),
('91109057', 'VTYPE_MOBI', '01', '0'),
('91109059', 'VTYPE_MOBI', '01', '0'),
('91109061', 'VTYPE_MOBI', '01', '0'),
('91109063', 'VTYPE_MOBI', '01', '0'),
('91109067', 'VTYPE_MOBI', '01', '0'),
('91109069', 'VTYPE_MOBI', '01', '0'),
('91109071', 'VTYPE_MOBI', '01', '0'),
('91109073', 'VTYPE_MOBI', '01', '0'),
('91109075', 'VTYPE_MOBI', '01', '0'),
('91109077', 'VTYPE_MOBI', '01', '0'),
('91109079', 'VTYPE_MOBI', '01', '0'),
('91109081', 'VTYPE_MOBI', '01', '0'),
('91109083', 'VTYPE_MOBI', '01', '0'),
('91109085', 'VTYPE_MOBI', '01', '0'),
('91109087', 'VTYPE_MOBI', '01', '0'),
('91109089', 'VTYPE_MOBI', '01', '0'),
('91109090', 'MTYPE_BRON', '04', '0'),
('91109092', 'VTYPE_MOBI', '01', '0'),
('91109094', 'VTYPE_MOBI', '01', '0'),
('91109096', 'VTYPE_MOBI', '01', '0'),
('91109098', 'VTYPE_MOBI', '01', '0'),
('91109099', 'VTYPE_MOBI', '01', '0'),
('91109100', 'VTYPE_MOBI', '01', '0'),
('91109102', 'VTYPE_MOBI', '01', '0'),
('91109106', 'VTYPE_MOBI', '01', '0'),
('91109108', 'VTYPE_MOBI', '01', '0'),
('91109110', 'VTYPE_MOBI', '01', '0'),
('91109111', 'MTYPE_SILV', '05', '0'),
('91109113', 'VTYPE_MOBI', '01', '0'),
('91109115', 'VTYPE_MOBI', '01', '0'),
('91109117', 'VTYPE_MOBI', '01', '0'),
('91109119', 'VTYPE_MOBI', '01', '0'),
('91109120', 'VTYPE_MOBI', '01', '0'),
('91109122', 'VTYPE_MOBI', '01', '0'),
('91109123', 'VTYPE_MOBI', '01', '0'),
('91109124', 'VTYPE_MOBI', '01', '0'),
('91109126', 'VTYPE_MOBI', '01', '0'),
('91109128', 'VTYPE_MOBI', '01', '0'),
('91109132', 'VTYPE_MOBI', '01', '0'),
('91109134', 'VTYPE_MOBI', '01', '0'),
('91109136', 'VTYPE_MOBI', '01', '0'),
('91109138', 'VTYPE_MOBI', '01', '0'),
('91109140', 'VTYPE_MOBI', '01', '0'),
('91109142', 'VTYPE_MOBI', '01', '0'),
('91109144', 'VTYPE_MOBI', '01', '0'),
('91109147', 'VTYPE_MOBI', '01', '0'),
('91109148', 'VTYPE_MOBI', '01', '0'),
('91109150', 'VTYPE_MOBI', '01', '0'),
('91109151', 'VTYPE_MOBI', '01', '0'),
('91109152', 'VTYPE_MOBI', '01', '0'),
('91109154', 'VTYPE_MOBI', '01', '0'),
('91109156', 'VTYPE_MOBI', '01', '0'),
('91109162', 'VTYPE_MOBI', '01', '0'),
('91109166', 'VTYPE_MOBI', '01', '0'),
('91109168', 'VTYPE_MOBI', '01', '0'),
('91109169', 'VTYPE_MOBI', '01', '0'),
('91109170', 'VTYPE_MOBI', '01', '0'),
('91109172', 'VTYPE_MOBI', '01', '0'),
('91109174', 'VTYPE_MOBI', '01', '0'),
('91109176', 'VTYPE_MOBI', '01', '0'),
('91109178', 'VTYPE_MOBI', '01', '0'),
('91109180', 'VTYPE_MOBI', '01', '0'),
('91109182', 'VTYPE_MOBI', '01', '0'),
('91109186', 'VTYPE_MOBI', '01', '0'),
('91109188', 'VTYPE_MOBI', '01', '0'),
('91109190', 'VTYPE_MOBI', '01', '0'),
('91109191', 'MTYPE_BRON', '04', '0'),
('91109193', 'VTYPE_MOBI', '01', '0'),
('91109194', 'VTYPE_MOBI', '01', '0'),
('91109195', 'VTYPE_MOBI', '01', '0'),
('91109196', 'VTYPE_MOBI', '01', '0'),
('91109197', 'VTYPE_MOBI', '01', '0'),
('91109198', 'VTYPE_MOBI', '01', '0'),
('91109199', 'VTYPE_MOBI', '01', '0'),
('91109200', 'VTYPE_MOBI', '01', '0'),
('91109201', 'VTYPE_MOBI', '01', '0'),
('91109202', 'VTYPE_MOBI', '01', '0'),
('91109203', 'VTYPE_MOBI', '01', '0'),
('91109204', 'VTYPE_MOBI', '01', '0'),
('91109205', 'VTYPE_MOBI', '01', '0'),
('91109206', 'VTYPE_MOBI', '01', '0'),
('91109208', 'VTYPE_MOBI', '01', '0'),
('91109209', 'VTYPE_MOBI', '01', '0'),
('91109210', 'VTYPE_MOBI', '01', '0'),
('91109213', 'VTYPE_MOBI', '01', '0'),
('91109214', 'VTYPE_MOBI', '01', '0'),
('91109215', 'VTYPE_MOBI', '01', '0'),
('91109216', 'VTYPE_MOBI', '01', '0'),
('91109217', 'VTYPE_MOBI', '01', '0'),
('91109218', 'VTYPE_MOBI', '01', '0'),
('91109219', 'VTYPE_MOBI', '01', '0'),
('91109220', 'VTYPE_MOBI', '01', '0'),
('91109221', 'VTYPE_MOBI', '01', '0'),
('91109222', 'MTYPE_SILV', '05', '0'),
('91109223', 'VTYPE_MOBI', '01', '0'),
('91109225', 'VTYPE_MOBI', '01', '0'),
('91109226', 'VTYPE_MOBI', '01', '0'),
('91109227', 'VTYPE_MOBI', '01', '0'),
('91109228', 'VTYPE_MOBI', '01', '0'),
('91109229', 'VTYPE_MOBI', '01', '0'),
('91109230', 'VTYPE_MOBI', '01', '0'),
('91109231', 'VTYPE_MOBI', '01', '0'),
('91109232', 'VTYPE_MOBI', '01', '0'),
('91109233', 'VTYPE_MOBI', '01', '0'),
('91109234', 'VTYPE_MOBI', '01', '0'),
('91109235', 'VTYPE_MOBI', '01', '0'),
('91109236', 'VTYPE_MOBI', '01', '0'),
('91109237', 'VTYPE_MOBI', '01', '0'),
('91109238', 'VTYPE_MOBI', '01', '0'),
('91109239', 'VTYPE_MOBI', '01', '0'),
('91109250', 'VTYPE_MOBI', '01', '0'),
('91109251', 'VTYPE_MOBI', '01', '0'),
('91109252', 'VTYPE_MOBI', '01', '0'),
('91109253', 'VTYPE_MOBI', '01', '0'),
('91109255', 'VTYPE_MOBI', '01', '0'),
('91109256', 'VTYPE_MOBI', '01', '0'),
('91109257', 'VTYPE_MOBI', '01', '0'),
('91109258', 'VTYPE_MOBI', '01', '0'),
('91109259', 'VTYPE_MOBI', '01', '0'),
('91109260', 'VTYPE_MOBI', '01', '0'),
('91109262', 'VTYPE_MOBI', '01', '0'),
('91109263', 'VTYPE_MOBI', '01', '0'),
('91109265', 'VTYPE_MOBI', '01', '0'),
('91109266', 'VTYPE_MOBI', '01', '0'),
('91109268', 'VTYPE_MOBI', '01', '0'),
('91109269', 'VTYPE_MOBI', '01', '0'),
('91109270', 'VTYPE_MOBI', '01', '0'),
('91109271', 'VTYPE_MOBI', '01', '0'),
('91109272', 'VTYPE_MOBI', '01', '0'),
('91109273', 'VTYPE_MOBI', '01', '0'),
('91109274', 'VTYPE_MOBI', '01', '0'),
('91109275', 'VTYPE_MOBI', '01', '0'),
('91109277', 'VTYPE_MOBI', '01', '0'),
('91109278', 'VTYPE_MOBI', '01', '0'),
('91109290', 'VTYPE_MOBI', '01', '0'),
('91109291', 'VTYPE_MOBI', '01', '0'),
('91109292', 'MTYPE_BRON', '04', '0'),
('91109294', 'VTYPE_MOBI', '01', '0'),
('91109295', 'VTYPE_MOBI', '01', '0'),
('91109296', 'VTYPE_MOBI', '01', '0'),
('91109297', 'VTYPE_MOBI', '01', '0'),
('91109298', 'VTYPE_MOBI', '01', '0'),
('91109299', 'VTYPE_MOBI', '01', '0'),
('91109300', 'VTYPE_MOBI', '01', '0'),
('91109301', 'VTYPE_MOBI', '01', '0'),
('91109303', 'VTYPE_MOBI', '01', '0'),
('91109305', 'VTYPE_MOBI', '01', '0'),
('91109306', 'VTYPE_MOBI', '01', '0'),
('91109307', 'VTYPE_MOBI', '01', '0'),
('91109308', 'VTYPE_MOBI', '01', '0'),
('91109310', 'VTYPE_MOBI', '01', '0'),
('91109311', 'VTYPE_MOBI', '01', '0'),
('91109312', 'VTYPE_MOBI', '01', '0'),
('91109313', 'VTYPE_MOBI', '01', '0'),
('91109314', 'VTYPE_MOBI', '01', '0'),
('91109315', 'VTYPE_MOBI', '01', '0'),
('91109316', 'VTYPE_MOBI', '01', '0'),
('91109317', 'VTYPE_MOBI', '01', '0'),
('91109318', 'VTYPE_MOBI', '01', '0'),
('91109319', 'VTYPE_MOBI', '01', '0'),
('91109321', 'VTYPE_MOBI', '01', '0'),
('91109322', 'VTYPE_MOBI', '01', '0'),
('91109323', 'VTYPE_MOBI', '01', '0'),
('91109325', 'VTYPE_MOBI', '01', '0'),
('91109326', 'VTYPE_MOBI', '01', '0'),
('91109327', 'VTYPE_MOBI', '01', '0'),
('91109328', 'VTYPE_MOBI', '01', '0'),
('91109329', 'VTYPE_MOBI', '01', '0'),
('91109331', 'VTYPE_MOBI', '01', '0'),
('91109332', 'VTYPE_MOBI', '01', '0'),
('91109333', 'MTYPE_SILV', '05', '0'),
('91109334', 'VTYPE_MOBI', '01', '0'),
('91109335', 'VTYPE_MOBI', '01', '0'),
('91109337', 'VTYPE_MOBI', '01', '0'),
('91109338', 'VTYPE_MOBI', '01', '0'),
('91109339', 'VTYPE_MOBI', '01', '0'),
('91109341', 'VTYPE_MOBI', '01', '0'),
('91109342', 'VTYPE_MOBI', '01', '0'),
('91109343', 'VTYPE_MOBI', '01', '0'),
('91109345', 'VTYPE_MOBI', '01', '0'),
('91109347', 'VTYPE_MOBI', '01', '0'),
('91109348', 'VTYPE_MOBI', '01', '0'),
('91109349', 'VTYPE_MOBI', '01', '0'),
('91109350', 'VTYPE_MOBI', '01', '0'),
('91109352', 'VTYPE_MOBI', '01', '0'),
('91109353', 'VTYPE_MOBI', '01', '0'),
('91109354', 'VTYPE_MOBI', '01', '0'),
('91109355', 'VTYPE_MOBI', '01', '0'),
('91109356', 'VTYPE_MOBI', '01', '0'),
('91109357', 'VTYPE_MOBI', '01', '0'),
('91109358', 'VTYPE_MOBI', '01', '0'),
('91109359', 'VTYPE_MOBI', '01', '0'),
('91109360', 'VTYPE_MOBI', '01', '0'),
('91109361', 'VTYPE_MOBI', '01', '0'),
('91109362', 'VTYPE_MOBI', '01', '0'),
('91109363', 'VTYPE_MOBI', '01', '0'),
('91109364', 'VTYPE_MOBI', '01', '0'),
('91109365', 'VTYPE_MOBI', '01', '0'),
('91109366', 'VTYPE_MOBI', '01', '0'),
('91109368', 'VTYPE_MOBI', '01', '0'),
('91109370', 'VTYPE_MOBI', '01', '0'),
('91109372', 'VTYPE_MOBI', '01', '0'),
('91109374', 'VTYPE_MOBI', '01', '0'),
('91109376', 'VTYPE_MOBI', '01', '0'),
('91109378', 'VTYPE_MOBI', '01', '0'),
('91109380', 'VTYPE_MOBI', '01', '0'),
('91109382', 'VTYPE_MOBI', '01', '0'),
('91109384', 'VTYPE_MOBI', '01', '0'),
('91109386', 'VTYPE_MOBI', '01', '0'),
('91109388', 'VTYPE_MOBI', '01', '0'),
('91109390', 'VTYPE_MOBI', '01', '0'),
('91109392', 'VTYPE_MOBI', '01', '0'),
('91109393', 'MTYPE_BRON', '04', '0'),
('91109395', 'VTYPE_MOBI', '01', '0'),
('91109397', 'VTYPE_MOBI', '01', '0'),
('91109399', 'VTYPE_MOBI', '01', '0'),
('91109400', 'VTYPE_MOBI', '01', '0'),
('91109401', 'VTYPE_MOBI', '01', '0'),
('91109403', 'VTYPE_MOBI', '01', '0'),
('91109407', 'VTYPE_MOBI', '01', '0'),
('91109409', 'VTYPE_MOBI', '01', '0'),
('91109411', 'VTYPE_MOBI', '01', '0'),
('91109415', 'VTYPE_MOBI', '01', '0'),
('91109417', 'VTYPE_MOBI', '01', '0'),
('91109419', 'VTYPE_MOBI', '01', '0'),
('91109423', 'VTYPE_MOBI', '01', '0'),
('91109427', 'VTYPE_MOBI', '01', '0'),
('91109429', 'VTYPE_MOBI', '01', '0'),
('91109431', 'VTYPE_MOBI', '01', '0'),
('91109433', 'VTYPE_MOBI', '01', '0'),
('91109437', 'VTYPE_MOBI', '01', '0'),
('91109441', 'VTYPE_MOBI', '01', '0'),
('91109444', 'MTYPE_SILV', '05', '0'),
('91109448', 'VTYPE_MOBI', '01', '0'),
('91109449', 'VTYPE_MOBI', '01', '0'),
('91109455', 'VTYPE_MOBI', '01', '0'),
('91109459', 'VTYPE_MOBI', '01', '0'),
('91109461', 'VTYPE_MOBI', '01', '0'),
('91109463', 'VTYPE_MOBI', '01', '0'),
('91109471', 'VTYPE_MOBI', '01', '0'),
('91109475', 'VTYPE_MOBI', '01', '0'),
('91109477', 'VTYPE_MOBI', '01', '0'),
('91109479', 'VTYPE_MOBI', '01', '0'),
('91109481', 'VTYPE_MOBI', '01', '0'),
('91109485', 'VTYPE_MOBI', '01', '0'),
('91109489', 'VTYPE_MOBI', '01', '0'),
('91109491', 'VTYPE_MOBI', '01', '0'),
('91109493', 'VTYPE_MOBI', '01', '0'),
('91109494', 'MTYPE_BRON', '04', '0'),
('91109496', 'VTYPE_MOBI', '01', '0'),
('91109498', 'VTYPE_MOBI', '01', '0'),
('91109499', 'VTYPE_MOBI', '01', '0'),
('91109500', 'VTYPE_MOBI', '01', '0'),
('91109502', 'VTYPE_MOBI', '01', '0'),
('91109503', 'VTYPE_MOBI', '01', '0'),
('91109506', 'VTYPE_MOBI', '01', '0'),
('91109508', 'VTYPE_MOBI', '01', '0'),
('91109510', 'VTYPE_MOBI', '01', '0'),
('91109512', 'VTYPE_MOBI', '01', '0'),
('91109513', 'VTYPE_MOBI', '01', '0'),
('91109518', 'VTYPE_MOBI', '01', '0'),
('91109520', 'VTYPE_MOBI', '01', '0'),
('91109522', 'VTYPE_MOBI', '01', '0'),
('91109526', 'VTYPE_MOBI', '01', '0'),
('91109528', 'VTYPE_MOBI', '01', '0'),
('91109530', 'VTYPE_MOBI', '01', '0'),
('91109534', 'VTYPE_MOBI', '01', '0'),
('91109536', 'VTYPE_MOBI', '01', '0'),
('91109538', 'VTYPE_MOBI', '01', '0'),
('91109540', 'VTYPE_MOBI', '01', '0'),
('91109544', 'VTYPE_MOBI', '01', '0'),
('91109548', 'VTYPE_MOBI', '01', '0'),
('91109550', 'VTYPE_MOBI', '01', '0'),
('91109552', 'VTYPE_MOBI', '01', '0'),
('91109554', 'VTYPE_MOBI', '01', '0'),
('91109555', 'MTYPE_SILV', '05', '0'),
('91109557', 'VTYPE_MOBI', '01', '0'),
('91109559', 'VTYPE_MOBI', '01', '0'),
('91109560', 'VTYPE_MOBI', '01', '0'),
('91109562', 'VTYPE_MOBI', '01', '0'),
('91109568', 'VTYPE_MOBI', '01', '0'),
('91109570', 'VTYPE_MOBI', '01', '0'),
('91109572', 'VTYPE_MOBI', '01', '0'),
('91109574', 'VTYPE_MOBI', '01', '0'),
('91109576', 'VTYPE_MOBI', '01', '0'),
('91109578', 'VTYPE_MOBI', '01', '0'),
('91109580', 'VTYPE_MOBI', '01', '0'),
('91109584', 'VTYPE_MOBI', '01', '0'),
('91109590', 'VTYPE_MOBI', '01', '0'),
('91109592', 'VTYPE_MOBI', '01', '0'),
('91109594', 'VTYPE_MOBI', '01', '0'),
('91109595', 'MTYPE_BRON', '04', '0'),
('91109597', 'VTYPE_MOBI', '01', '0'),
('91109599', 'VTYPE_MOBI', '01', '0'),
('91109600', 'VTYPE_MOBI', '01', '0'),
('91109601', 'VTYPE_MOBI', '01', '0'),
('91109603', 'VTYPE_MOBI', '01', '0'),
('91109605', 'VTYPE_MOBI', '01', '0'),
('91109607', 'VTYPE_MOBI', '01', '0'),
('91109609', 'VTYPE_MOBI', '01', '0'),
('91109611', 'VTYPE_MOBI', '01', '0'),
('91109613', 'VTYPE_MOBI', '01', '0'),
('91109616', 'VTYPE_MOBI', '01', '0'),
('91109618', 'VTYPE_MOBI', '01', '0'),
('91109619', 'VTYPE_MOBI', '01', '0'),
('91109621', 'VTYPE_MOBI', '01', '0'),
('91109622', 'VTYPE_MOBI', '01', '0'),
('91109623', 'VTYPE_MOBI', '01', '0'),
('91109626', 'VTYPE_MOBI', '01', '0'),
('91109627', 'VTYPE_MOBI', '01', '0'),
('91109629', 'VTYPE_MOBI', '01', '0'),
('91109630', 'VTYPE_MOBI', '01', '0'),
('91109631', 'VTYPE_MOBI', '01', '0'),
('91109632', 'VTYPE_MOBI', '01', '0'),
('91109635', 'VTYPE_MOBI', '01', '0'),
('91109636', 'VTYPE_MOBI', '01', '0'),
('91109638', 'VTYPE_MOBI', '01', '0'),
('91109640', 'VTYPE_MOBI', '01', '0'),
('91109642', 'VTYPE_MOBI', '01', '0'),
('91109643', 'VTYPE_MOBI', '01', '0'),
('91109644', 'VTYPE_MOBI', '01', '0'),
('91109645', 'VTYPE_MOBI', '01', '0'),
('91109646', 'VTYPE_MOBI', '01', '0'),
('91109647', 'VTYPE_MOBI', '01', '0'),
('91109648', 'VTYPE_MOBI', '01', '0'),
('91109649', 'VTYPE_MOBI', '01', '0'),
('91109654', 'VTYPE_MOBI', '01', '0'),
('91109655', 'VTYPE_MOBI', '01', '0'),
('91109656', 'VTYPE_MOBI', '01', '0'),
('91109658', 'VTYPE_MOBI', '01', '0'),
('91109659', 'VTYPE_MOBI', '01', '0'),
('91109660', 'VTYPE_MOBI', '01', '0'),
('91109661', 'VTYPE_MOBI', '01', '0'),
('91109662', 'VTYPE_MOBI', '01', '0'),
('91109663', 'VTYPE_MOBI', '01', '0'),
('91109664', 'VTYPE_MOBI', '01', '0'),
('91109665', 'VTYPE_MOBI', '01', '0'),
('91109666', 'MTYPE_SILV', '05', '0'),
('91109667', 'VTYPE_MOBI', '01', '0'),
('91109668', 'VTYPE_MOBI', '01', '0'),
('91109669', 'VTYPE_MOBI', '01', '0'),
('91109670', 'VTYPE_MOBI', '01', '0'),
('91109672', 'VTYPE_MOBI', '01', '0'),
('91109674', 'VTYPE_MOBI', '01', '0'),
('91109675', 'VTYPE_MOBI', '01', '0'),
('91109676', 'VTYPE_MOBI', '01', '0'),
('91109678', 'VTYPE_MOBI', '01', '0'),
('91109679', 'VTYPE_MOBI', '01', '0'),
('91109680', 'VTYPE_MOBI', '01', '0'),
('91109682', 'VTYPE_MOBI', '01', '0'),
('91109683', 'VTYPE_MOBI', '01', '0'),
('91109684', 'VTYPE_MOBI', '01', '0'),
('91109686', 'VTYPE_MOBI', '01', '0'),
('91109688', 'VTYPE_MOBI', '01', '0'),
('91109690', 'VTYPE_MOBI', '01', '0'),
('91109691', 'VTYPE_MOBI', '01', '0'),
('91109692', 'VTYPE_MOBI', '01', '0'),
('91109693', 'VTYPE_MOBI', '01', '0'),
('91109694', 'VTYPE_MOBI', '01', '0'),
('91109695', 'VTYPE_MOBI', '01', '0'),
('91109696', 'MTYPE_BRON', '04', '0'),
('91109697', 'VTYPE_MOBI', '01', '0'),
('91109698', 'VTYPE_MOBI', '01', '0'),
('91109699', 'VTYPE_MOBI', '01', '0'),
('91109700', 'VTYPE_MOBI', '01', '0'),
('91109701', 'VTYPE_MOBI', '01', '0'),
('91109703', 'VTYPE_MOBI', '01', '0'),
('91109704', 'VTYPE_MOBI', '01', '0'),
('91109705', 'VTYPE_MOBI', '01', '0'),
('91109707', 'VTYPE_MOBI', '01', '0'),
('91109708', 'VTYPE_MOBI', '01', '0'),
('91109709', 'VTYPE_MOBI', '01', '0'),
('91109710', 'VTYPE_MOBI', '01', '0'),
('91109712', 'VTYPE_MOBI', '01', '0'),
('91109714', 'VTYPE_MOBI', '01', '0'),
('91109715', 'VTYPE_MOBI', '01', '0'),
('91109716', 'VTYPE_MOBI', '01', '0'),
('91109717', 'VTYPE_MOBI', '01', '0'),
('91109719', 'VTYPE_MOBI', '01', '0'),
('91109722', 'VTYPE_MOBI', '01', '0'),
('91109723', 'VTYPE_MOBI', '01', '0'),
('91109724', 'VTYPE_MOBI', '01', '0'),
('91109725', 'VTYPE_MOBI', '01', '0'),
('91109727', 'VTYPE_MOBI', '01', '0'),
('91109728', 'VTYPE_MOBI', '01', '0'),
('91109730', 'VTYPE_MOBI', '01', '0'),
('91109731', 'VTYPE_MOBI', '01', '0'),
('91109733', 'VTYPE_MOBI', '01', '0'),
('91109734', 'VTYPE_MOBI', '01', '0'),
('91109735', 'VTYPE_MOBI', '01', '0'),
('91109737', 'VTYPE_MOBI', '01', '0'),
('91109739', 'VTYPE_MOBI', '01', '0'),
('91109740', 'VTYPE_MOBI', '01', '0'),
('91109742', 'VTYPE_MOBI', '01', '0'),
('91109743', 'VTYPE_MOBI', '01', '0'),
('91109745', 'VTYPE_MOBI', '01', '0'),
('91109747', 'VTYPE_MOBI', '01', '0'),
('91109749', 'VTYPE_MOBI', '01', '0'),
('91109755', 'VTYPE_MOBI', '01', '0'),
('91109757', 'VTYPE_MOBI', '01', '0'),
('91109758', 'VTYPE_MOBI', '01', '0'),
('91109759', 'VTYPE_MOBI', '01', '0'),
('91109760', 'VTYPE_MOBI', '01', '0'),
('91109763', 'VTYPE_MOBI', '01', '0'),
('91109766', 'VTYPE_MOBI', '01', '0'),
('91109767', 'VTYPE_MOBI', '01', '0'),
('91109769', 'VTYPE_MOBI', '01', '0'),
('91109770', 'VTYPE_MOBI', '01', '0'),
('91109771', 'VTYPE_MOBI', '01', '0'),
('91109772', 'VTYPE_MOBI', '01', '0'),
('91109774', 'VTYPE_MOBI', '01', '0'),
('91109776', 'VTYPE_MOBI', '01', '0'),
('91109777', 'MTYPE_SILV', '05', '0'),
('91109779', 'VTYPE_MOBI', '01', '0'),
('91109780', 'VTYPE_MOBI', '01', '0'),
('91109781', 'VTYPE_MOBI', '01', '0'),
('91109789', 'VTYPE_MOBI', '01', '0'),
('91109791', 'VTYPE_MOBI', '01', '0'),
('91109793', 'VTYPE_MOBI', '01', '0'),
('91109795', 'VTYPE_MOBI', '01', '0'),
('91109797', 'MTYPE_BRON', '04', '0'),
('91109798', 'VTYPE_MOBI', '01', '0'),
('91109800', 'VTYPE_MOBI', '01', '0'),
('91109801', 'VTYPE_MOBI', '01', '0'),
('91109803', 'VTYPE_MOBI', '01', '0'),
('91109805', 'VTYPE_MOBI', '01', '0'),
('91109807', 'VTYPE_MOBI', '01', '0'),
('91109809', 'VTYPE_MOBI', '01', '0'),
('91109811', 'VTYPE_MOBI', '01', '0'),
('91109813', 'VTYPE_MOBI', '01', '0'),
('91109817', 'VTYPE_MOBI', '01', '0'),
('91109819', 'VTYPE_MOBI', '01', '0'),
('91109821', 'VTYPE_MOBI', '01', '0'),
('91109823', 'VTYPE_MOBI', '01', '0'),
('91109829', 'VTYPE_MOBI', '01', '0'),
('91109831', 'VTYPE_MOBI', '01', '0'),
('91109833', 'VTYPE_MOBI', '01', '0'),
('91109843', 'VTYPE_MOBI', '01', '0'),
('91109851', 'VTYPE_MOBI', '01', '0'),
('91109853', 'VTYPE_MOBI', '01', '0'),
('91109855', 'VTYPE_MOBI', '01', '0'),
('91109861', 'VTYPE_MOBI', '01', '0'),
('91109865', 'VTYPE_MOBI', '01', '0'),
('91109867', 'VTYPE_MOBI', '01', '0'),
('91109869', 'VTYPE_MOBI', '01', '0'),
('91109875', 'VTYPE_MOBI', '01', '0'),
('91109877', 'VTYPE_MOBI', '01', '0'),
('91109879', 'VTYPE_MOBI', '01', '0'),
('91109881', 'VTYPE_MOBI', '01', '0'),
('91109883', 'VTYPE_MOBI', '01', '0'),
('91109885', 'VTYPE_MOBI', '01', '0'),
('91109887', 'VTYPE_MOBI', '01', '0'),
('91109888', 'MTYPE_SILV', '05', '0'),
('91109889', 'VTYPE_MOBI', '01', '0'),
('91109891', 'VTYPE_MOBI', '01', '0'),
('91109893', 'VTYPE_MOBI', '01', '0'),
('91109895', 'VTYPE_MOBI', '01', '0'),
('91109897', 'VTYPE_MOBI', '01', '0'),
('91109898', 'MTYPE_BRON', '04', '0'),
('91109899', 'VTYPE_MOBI', '01', '0'),
('91109900', 'MTYPE_BRON', '03', '0'),
('91109902', 'VTYPE_MOBI', '01', '0'),
('91109904', 'VTYPE_MOBI', '01', '0'),
('91109906', 'VTYPE_MOBI', '01', '0'),
('91109908', 'VTYPE_MOBI', '01', '0'),
('91109909', 'VTYPE_MOBI', '01', '0'),
('91109911', 'MTYPE_BRON', '03', '0'),
('91109912', 'VTYPE_MOBI', '01', '0'),
('91109914', 'VTYPE_MOBI', '01', '0'),
('91109916', 'VTYPE_MOBI', '01', '0'),
('91109918', 'VTYPE_MOBI', '01', '0'),
('91109919', 'VTYPE_MOBI', '01', '0'),
('91109922', 'MTYPE_BRON', '03', '0'),
('91109924', 'VTYPE_MOBI', '01', '0'),
('91109926', 'VTYPE_MOBI', '01', '0'),
('91109928', 'VTYPE_MOBI', '01', '0'),
('91109929', 'VTYPE_MOBI', '01', '0'),
('91109931', 'VTYPE_MOBI', '01', '0'),
('91109933', 'MTYPE_BRON', '03', '0'),
('91109934', 'VTYPE_MOBI', '01', '0'),
('91109936', 'VTYPE_MOBI', '01', '0'),
('91109938', 'VTYPE_MOBI', '01', '0'),
('91109939', 'VTYPE_MOBI', '01', '0'),
('91109941', 'VTYPE_MOBI', '01', '0'),
('91109943', 'VTYPE_MOBI', '01', '0'),
('91109944', 'MTYPE_BRON', '03', '0'),
('91109946', 'VTYPE_MOBI', '01', '0'),
('91109948', 'VTYPE_MOBI', '01', '0'),
('91109949', 'VTYPE_MOBI', '01', '0'),
('91109951', 'VTYPE_MOBI', '01', '0'),
('91109953', 'VTYPE_MOBI', '01', '0'),
('91109955', 'MTYPE_BRON', '03', '0'),
('91109956', 'VTYPE_MOBI', '01', '0'),
('91109958', 'VTYPE_MOBI', '01', '0'),
('91109959', 'VTYPE_MOBI', '01', '0'),
('91109961', 'VTYPE_MOBI', '01', '0'),
('91109963', 'VTYPE_MOBI', '01', '0'),
('91109965', 'VTYPE_MOBI', '01', '0'),
('91109966', 'MTYPE_BRON', '03', '0'),
('91109968', 'VTYPE_MOBI', '01', '0'),
('91109969', 'VTYPE_MOBI', '01', '0'),
('91109971', 'VTYPE_MOBI', '01', '0'),
('91109973', 'VTYPE_MOBI', '01', '0'),
('91109975', 'VTYPE_MOBI', '01', '0'),
('91109977', 'MTYPE_BRON', '03', '0'),
('91109978', 'VTYPE_MOBI', '01', '0'),
('91109979', 'VTYPE_MOBI', '01', '0'),
('91109981', 'VTYPE_MOBI', '01', '0'),
('91109985', 'VTYPE_MOBI', '01', '0'),
('91109987', 'VTYPE_MOBI', '01', '0'),
('91109988', 'MTYPE_BRON', '03', '0'),
('91109989', 'VTYPE_MOBI', '01', '0'),
('91109990', 'VTYPE_MOBI', '05', '0'),
('91109991', 'VTYPE_MOBI', '05', '0'),
('91109992', 'VTYPE_MOBI', '05', '0'),
('91109993', 'VTYPE_MOBI', '05', '0'),
('91109994', 'VTYPE_MOBI', '05', '0'),
('91109995', 'VTYPE_MOBI', '05', '0'),
('91109996', 'VTYPE_MOBI', '05', '0'),
('91109997', 'VTYPE_MOBI', '05', '0'),
('91109998', 'VTYPE_MOBI', '05', '0'),
('91109999', 'MTYPE_GOLD', '02', '0');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_account_key_type`
--

CREATE TABLE IF NOT EXISTS `ocs_account_key_type` (
  `account_key_type` varchar(30) NOT NULL,
  `account_key_name` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`account_key_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_account_key_type`
--

INSERT INTO `ocs_account_key_type` (`account_key_type`, `account_key_name`) VALUES
('MTYPE_BRON', 'Bronze(Mobile)'),
('MTYPE_GOLD', 'Gold(Mobile)'),
('MTYPE_SILV', 'Silver(Mobile)'),
('VTYPE_BORN', 'Normal(Mobile)');

-- --------------------------------------------------------

--
-- Stand-in structure for view `ocs_account_key_view`
--
CREATE TABLE IF NOT EXISTS `ocs_account_key_view` (
`account_key` varchar(30)
,`account_key_type` varchar(10)
,`account_key_name` varchar(50)
,`sales_flag` varchar(7)
);
-- --------------------------------------------------------

--
-- Table structure for table `ocs_call_history`
--

CREATE TABLE IF NOT EXISTS `ocs_call_history` (
  `subscription_key` varchar(24) NOT NULL,
  `calling` varchar(24) NOT NULL,
  `call_type` int(11) NOT NULL,
  `destination` varchar(32) NOT NULL,
  `start_time` datetime NOT NULL,
  `end_time` datetime NOT NULL,
  `account_usage` int(11) NOT NULL,
  `charging_type` int(11) NOT NULL,
  `deducted_unit` int(11) NOT NULL,
  PRIMARY KEY (`subscription_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `ocs_campaign`
--

CREATE TABLE IF NOT EXISTS `ocs_campaign` (
  `campaign_id` int(11) NOT NULL AUTO_INCREMENT,
  `campaign_name` varchar(64) DEFAULT 'Campaign',
  `description` varchar(256) NOT NULL,
  `status` tinyint(4) NOT NULL,
  `start_date` datetime NOT NULL,
  `end_date` datetime NOT NULL,
  PRIMARY KEY (`campaign_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=11 ;

--
-- Dumping data for table `ocs_campaign`
--

INSERT INTO `ocs_campaign` (`campaign_id`, `campaign_name`, `description`, `status`, `start_date`, `end_date`) VALUES
(7, 'First Call Promotion', 'Give bonus at the first call', 1, '2012-05-10 00:00:00', '2012-06-10 00:00:00'),
(9, 'Recharge Promotion', 'Give bonus on recharge', 1, '2012-05-24 00:00:00', '2013-05-24 00:00:00'),
(10, 'new campaign', 'this  month...', 1, '2012-05-25 00:00:00', '2013-05-25 00:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_campaign_actions`
--

CREATE TABLE IF NOT EXISTS `ocs_campaign_actions` (
  `rule_id` int(11) NOT NULL,
  `action_id` int(11) NOT NULL AUTO_INCREMENT,
  `action_name` varchar(128) CHARACTER SET utf8 DEFAULT NULL,
  `ocs_action_id` int(11) NOT NULL,
  PRIMARY KEY (`action_id`),
  KEY `rule_id` (`rule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=865 ;

--
-- Dumping data for table `ocs_campaign_actions`
--

INSERT INTO `ocs_campaign_actions` (`rule_id`, `action_id`, `action_name`, `ocs_action_id`) VALUES
(0, 828, 'send SMS notification orig=02114 dest=CALLING message=844 : You have %1 Last Remains', 877),
(56, 830, 'give_bonus counter_id=FreeVoice bonus_amount=10000', 876),
(56, 831, 'send_sms_notification orig=02114 dest=CALLING message=844 : You have %1, %2 remains.', 877),
(61, 832, 'give_bonus counter_id=FreeVoice bonus_amount=100', 876),
(61, 833, 'send_sms_notification orig=02114 dest=CALLING message=850 : You have free %1 %1 units.', 877),
(0, 834, 'send_sms_notification orig=02114 dest=CALLING message=844 : You have %1, %2 remains.', 877),
(0, 835, NULL, 0),
(0, 836, NULL, 0),
(0, 837, 'send_sms_notification orig=02114 dest=CALLING message=844 : You have %1, %2 remains.', 877),
(51, 839, 'give_bonus counter_id=Remains bonus_amount=111', 876),
(51, 840, 'send_sms_notification orig=02114 dest=CALLING message=844 : You have %1, %2 remains.', 877),
(11, 846, 'apply_discount discount_rate=10', 885),
(12, 847, 'apply_discount discount_rate=20', 885),
(13, 848, 'give_bonus counter_id=Remains bonus_amount=1000', 876),
(13, 849, 'send_sms_notification orig=02114 dest=CALLING message=844 : You have %1 Last Remains', 877),
(16, 850, 'give_bonus counter_id=FreeVoice bonus_amount=100', 876),
(16, 851, 'give_bonus counter_id=FreeSms bonus_amount=50', 876),
(16, 852, 'send_sms_notification orig=02114 dest=CALLING message=850 : Welcome to UNITEL. You have Remains %1 TG .', 877),
(18, 853, 'give_bonus counter_id=FreeSms bonus_amount=100', 876),
(18, 854, 'give_bonus counter_id=FreeVoice bonus_amount=300', 876),
(19, 855, 'give_bonus counter_id=FreeSms bonus_amount=50', 876),
(19, 856, 'give_bonus counter_id=FreeVoice bonus_amount=600', 876),
(21, 857, 'apply_discount discount_rate=50', 885),
(22, 858, 'apply_discount discount_rate=30', 885),
(0, 859, 'send SMS notification orig=1414 dest=CALLING message=844 : You have %1 Last Remains', 877),
(23, 860, 'give_bonus counter_id=FreeSms bonus_amount=100', 876),
(24, 861, 'give_bonus counter_id=FreeSms bonus_amount=200', 876),
(24, 862, 'give_bonus counter_id=FreeVoice bonus_amount=300', 876),
(24, 863, 'send_sms_notification orig=1414 dest=CALLING message=850 : Welcome to UNITEL. You have Remains %1 TG .', 877),
(22, 864, 'give_bonus counter_id=FreeVoice bonus_amount=100', 876);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_campaign_action_param`
--

CREATE TABLE IF NOT EXISTS `ocs_campaign_action_param` (
  `action_id` int(11) NOT NULL,
  `param_id` varchar(16) COLLATE latin1_general_ci NOT NULL,
  `param_name` varchar(32) CHARACTER SET utf8 NOT NULL,
  `value` varchar(32) CHARACTER SET utf8 NOT NULL,
  KEY `action_id` (`action_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `ocs_campaign_action_param`
--

INSERT INTO `ocs_campaign_action_param` (`action_id`, `param_id`, `param_name`, `value`) VALUES
(801, '58:833', 'counter', 'LastRemains'),
(803, '56:832', 'dest', '0'),
(803, '56:833', 'counter', 'Remains'),
(803, '56:839', 'amount', '1000'),
(804, '58:832', 'dest', '0'),
(804, '58:833', 'counter', 'Remains'),
(804, '58:839', 'amount', '2'),
(801, '58:839', 'amount', '1011'),
(801, '58:832', 'dest', '3'),
(830, '56:859', 'bonus_amount', '10000'),
(830, '56:867', 'counter_id', '2'),
(831, '56:866', 'dest', '0'),
(831, '56:868', 'orig', '02114'),
(819, '58:842', 'bonus_amount', '123'),
(832, '61:867', 'counter_id', '2'),
(831, '56:861', 'message', '844'),
(810, '58:832', 'dest', '1'),
(825, '58:851', 'orig', '0101231234'),
(0, '0:832', 'dest', '0'),
(0, '0:841', 'message', '844'),
(0, '0:851', 'orig', ''),
(820, '58:842', 'bonus_amount', '111'),
(820, '58:843', 'counter_id', '1'),
(819, '58:843', 'counter_id', '0'),
(825, '58:832', 'dest', '0'),
(825, '58:814', 'call_type', '0'),
(826, '0:843', 'counter_id', '0'),
(826, '0:842', 'bonus_amount', ''),
(827, '0:843', 'counter_id', '0'),
(827, '0:842', 'bonus_amount', ''),
(828, '828:861', 'message', '844'),
(828, '828:866', 'dest', '0'),
(828, '828:868', 'orig', '02114'),
(832, '61:859', 'bonus_amount', '100'),
(833, '61:868', 'orig', '02114'),
(833, '61:866', 'dest', '0'),
(833, '61:861', 'message', '850'),
(834, '0:868', 'orig', '02114'),
(834, '0:866', 'dest', '0'),
(834, '0:861', 'message', '844'),
(858, '22:883', 'discount_rate', '30'),
(857, '21:883', 'discount_rate', '50'),
(837, '0:868', 'orig', '02114'),
(837, '0:866', 'dest', '0'),
(837, '0:861', 'message', '844'),
(839, '51:867', 'counter_id', '0'),
(839, '51:859', 'bonus_amount', '111'),
(840, '51:868', 'orig', '02114'),
(840, '51:866', 'dest', '0'),
(840, '51:861', 'message', '844'),
(842, '2:859', 'bonus_amount', '111111'),
(842, '2:867', 'counter_id', '0'),
(844, '5:859', 'bonus_amount', '10009'),
(844, '5:867', 'counter_id', '0'),
(847, '12:883', 'discount_rate', '20'),
(846, '11:883', 'discount_rate', '10'),
(848, '13:867', 'counter_id', '0'),
(848, '13:859', 'bonus_amount', '1000'),
(849, '13:868', 'orig', '02114'),
(849, '13:866', 'dest', '0'),
(849, '13:861', 'message', '844'),
(850, '16:867', 'counter_id', '2'),
(850, '16:859', 'bonus_amount', '100'),
(851, '16:867', 'counter_id', '3'),
(851, '16:859', 'bonus_amount', '50'),
(852, '16:868', 'orig', '02114'),
(852, '16:866', 'dest', '0'),
(852, '16:861', 'message', '850'),
(853, '18:867', 'counter_id', '3'),
(853, '18:859', 'bonus_amount', '100'),
(854, '18:859', 'bonus_amount', '300'),
(854, '18:867', 'counter_id', '2'),
(855, '19:859', 'bonus_amount', '50'),
(855, '19:867', 'counter_id', '3'),
(856, '19:867', 'counter_id', '2'),
(856, '19:859', 'bonus_amount', '600'),
(859, ':868', 'orig', '1414'),
(859, ':866', 'dest', '0'),
(859, ':861', 'message', '844'),
(860, '23:867', 'counter_id', '3'),
(860, '23:859', 'bonus_amount', '100'),
(861, '24:867', 'counter_id', '3'),
(861, '24:859', 'bonus_amount', '200'),
(862, '24:867', 'counter_id', '2'),
(862, '24:859', 'bonus_amount', '300'),
(863, '24:868', 'orig', '1414'),
(863, '24:866', 'dest', '0'),
(863, '24:861', 'message', '850'),
(864, '22:867', 'counter_id', '2'),
(864, '22:859', 'bonus_amount', '100');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_campaign_conditions`
--

CREATE TABLE IF NOT EXISTS `ocs_campaign_conditions` (
  `cond_id` int(11) NOT NULL AUTO_INCREMENT,
  `rule_id` int(11) NOT NULL DEFAULT '0',
  `param_name` varchar(32) DEFAULT NULL,
  `operator` varchar(32) DEFAULT NULL,
  `value` varchar(128) DEFAULT NULL,
  `param_id` varchar(32) NOT NULL,
  `cond_name` varchar(128) NOT NULL,
  `cond_idx` int(11) NOT NULL DEFAULT '0',
  `value2` varchar(32) DEFAULT NULL,
  `counter_input` tinyint(1) NOT NULL DEFAULT '0',
  `cond_rule` varchar(128) NOT NULL,
  KEY `rule_id` (`rule_id`),
  KEY `cond_id` (`cond_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=94 ;

--
-- Dumping data for table `ocs_campaign_conditions`
--

INSERT INTO `ocs_campaign_conditions` (`cond_id`, `rule_id`, `param_name`, `operator`, `value`, `param_id`, `cond_name`, `cond_idx`, `value2`, `counter_input`, `cond_rule`) VALUES
(46, 47, 'counter of the calling party', '=', '5', '813:account', 'Remains counter of the calling party = 5 ', 0, NULL, 0, ''),
(46, 47, 'calling', 'string', '3', '813', 'calling string 3', 1, '', 0, ''),
(70, 56, 'fullday', '=', '20121021', '862', ' fullday = 20121021 ', 1336725641, '', 0, 'fullday = 20121021 '),
(74, 61, 'product', '=', 'Y', '854', ' product = Y ', 1337218829, '', 0, 'product = Y '),
(70, 56, 'counter of the calling party', 'between', '1', '858:account', 'Remains counter of the calling party between 1 and 2', 1337608694, '2', 0, 'Remains between 1 , 2'),
(70, 56, 'week', '=', '{"tue":"tue"}', '856', ' week = (tue) ', 1337651093, NULL, 0, 'week = (tue) '),
(76, 63, 'counter of the calling party', '>', 'TotalUsedMoney', '858:account', 'Remains counter of the calling party > TotalUsedMoney ', 1337665228, '', 1, 'Remains > TotalUsedMoney '),
(77, 56, 'counter of the calling party', '<', '3000', '858:account', 'Remains counter of the calling party < 3000 ', 1337665547, '', 0, 'Remains < 3000 '),
(47, 51, 'calling', '=', '1', '858', ' calling = 1 ', 1337680161, '', 0, 'calling = 1 '),
(47, 51, 'fullday', '=', '20121011', '862', ' fullday = 20121011 ', 1337680204, '', 0, 'fullday = 20121011 '),
(47, 51, 'counter of the calling party', '=', '123', '858:account', 'Remains counter of the calling party = 123 ', 1337680343, '', 0, 'Remains = 123 '),
(80, 11, 'time', 'between', '0600', '857', ' time between 0600 and 1800', 1337756660, '1800', 0, 'time between 0600 , 1800'),
(81, 12, 'week', '=', '{"sat":"sat"}', '856', ' week = (sat) ', 1337756904, NULL, 0, 'week = (sat) '),
(83, 13, 'counter of the calling party', '>', '1000', '858:account', 'TotalUsedMoney counter of the calling party > 1000 ', 1337767270, '', 0, 'TotalUsedMoney > 1000 '),
(83, 13, 'week', '=', '{"sun":"sun"}', '856', ' week = (sun) ', 1337767299, NULL, 0, 'week = (sun) '),
(84, 13, 'counter of the calling party', '>', '2000', '858:account', 'TotalUsedMoney counter of the calling party > 2000 ', 1337767313, '', 0, 'TotalUsedMoney > 2000 '),
(84, 13, 'week', '=', '{"sat":"sat"}', '856', ' week = (sat) ', 1337767334, NULL, 0, 'week = (sat) '),
(83, 13, 'product', '=', 'N', '854', ' product = N ', 1337767410, '', 0, 'product = N '),
(84, 13, 'product', '=', 'N', '854', ' product = N ', 1337767422, '', 0, 'product = N '),
(85, 16, 'product', '=', 'Y', '854', ' product = Y ', 1337767435, '', 0, 'product = Y '),
(85, 16, 'fullday', 'between', '20120401', '862', ' fullday between 20120401 and 20120430', 1337767449, '20120430', 0, 'fullday between 20120401 , 20120430'),
(86, 18, 'fullday', 'between', '20120501', '862', ' fullday between 20120501 and 20120531', 1337822765, '20120531', 0, 'fullday between 20120501 , 20120531'),
(86, 18, 'product', '=', 'N', '854', ' product = N ', 1337822789, '', 0, 'product = N '),
(87, 19, 'fullday', 'between', '20120501', '862', ' fullday between 20120501 and 20120531', 1337824285, '20120531', 0, 'fullday between 20120501 , 20120531'),
(87, 19, 'product', '=', 'Y', '854', ' product = Y ', 1337824307, '', 0, 'product = Y '),
(80, 11, 'week', '=', '{"tue":"tue"}', '856', ' week = (tue) ', 1337824711, NULL, 0, 'week = (tue) '),
(88, 11, 'week', '=', '{"sat":"sat"}', '856', ' week = (sat) ', 1337824757, NULL, 0, 'week = (sat) '),
(81, 12, 'time', 'between', '0600', '857', ' time between 0600 and 2200', 1337825469, '2200', 0, 'time between 0600 , 2200'),
(88, 11, 'time', 'between', '0600', '857', ' time between 0600 and 2200', 1337825501, '2200', 0, 'time between 0600 , 2200'),
(89, 21, 'week', '=', '{"fri":"fri"}', '856', ' week = (fri) ', 1337845393, NULL, 0, 'week = (fri) '),
(89, 21, 'time', 'between', '0000', '857', ' time between 0000 and 1800', 1337845409, '1800', 0, 'time between 0000 , 1800'),
(91, 22, 'week', '=', '{"fri":"fri"}', '856', ' week = (fri) ', 1337845519, NULL, 0, 'week = (fri) '),
(91, 22, 'time', 'between', '1800', '857', ' time between 1800 and 2400', 1337845530, '2400', 0, 'time between 1800 , 2400'),
(92, 23, 'product', '=', 'N', '854', ' product = N ', 1337922545, '', 0, 'product = N '),
(92, 23, 'counter of the calling party', '>', '10000', '858:account', 'TotalUsedMoney counter of the calling party > 10000 ', 1337922566, '', 0, 'TotalUsedMoney > 10000 '),
(93, 23, 'product', '=', 'N', '854', ' product = N ', 1337922602, '', 0, 'product = N '),
(93, 23, 'counter of the calling party', '>', '20000', '858:account', 'TotalUsedMoney counter of the calling party > 20000 ', 1337922617, '', 0, 'TotalUsedMoney > 20000 ');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_card`
--

CREATE TABLE IF NOT EXISTS `ocs_card` (
  `card_no` varchar(32) CHARACTER SET utf8 NOT NULL COMMENT 'Ä«µå¹øÈ£',
  `card_type` varchar(4) CHARACTER SET utf8 NOT NULL,
  `pin_no` varchar(32) CHARACTER SET utf8 DEFAULT NULL COMMENT 'PIN ¹øÈ£',
  `recharge_datetime` datetime DEFAULT NULL COMMENT 'ÃæÀüÀÏ½Ã',
  `account_key` varchar(24) CHARACTER SET utf8 DEFAULT NULL COMMENT 'Account Key',
  `status` varchar(2) CHARACTER SET utf8 DEFAULT '0' COMMENT 'Ä«µå»óÅÂ(IDLE, NOT USED, USED, ...)',
  PRIMARY KEY (`card_no`,`card_type`),
  UNIQUE KEY `IDX_OCS_CARD_01` (`pin_no`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ocs_card`
--

INSERT INTO `ocs_card` (`card_no`, `card_type`, `pin_no`, `recharge_datetime`, `account_key`, `status`) VALUES
('10148103981', 'AAAA', '228560229896', '2012-04-01 00:01:19', '88935466', '1'),
('10154561945', 'AAAA', '894050829496', '2012-04-01 00:01:27', '88707188', '0'),
('10698241945', 'AAAA', '892342329496', '2012-04-01 00:01:27', '91100038', '0');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_card_added_service`
--

CREATE TABLE IF NOT EXISTS `ocs_card_added_service` (
  `card_type` varchar(4) NOT NULL COMMENT 'Ä«µåÀ¯Çü',
  `start_date` date NOT NULL COMMENT 'Àû¿ëÀÏ½Ã',
  `end_date` date DEFAULT NULL COMMENT 'Á¾·áÀÏ½Ã',
  `promotion_no` varchar(16) DEFAULT NULL COMMENT 'pc¿¡¼­ Á¤ÀÇÇÑ promotion È£Ãâ',
  PRIMARY KEY (`card_type`,`start_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `ocs_card_product`
--

CREATE TABLE IF NOT EXISTS `ocs_card_product` (
  `card_type` varchar(4) NOT NULL COMMENT 'ì¹´ë“œ ìœ í˜•',
  `product_id` varchar(45) NOT NULL COMMENT 'ìƒí’ˆ ì½”ë“œ',
  `usable` tinyint(1) DEFAULT '0' COMMENT 'ì‚¬ìš©ê°€ëŠ¥ ì—¬ë¶€(0:not usd, 1:use)',
  PRIMARY KEY (`card_type`,`product_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_card_product`
--

INSERT INTO `ocs_card_product` (`card_type`, `product_id`, `usable`) VALUES
('AAAA', '1', 1),
('AAAA', '2', 1);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_card_type`
--

CREATE TABLE IF NOT EXISTS `ocs_card_type` (
  `card_type` varchar(4) CHARACTER SET utf8 NOT NULL COMMENT 'Ä«µå À¯Çü',
  `unit` decimal(10,0) DEFAULT '0' COMMENT 'ÃæÀü±Ý¾×',
  `active_period` int(11) DEFAULT '0' COMMENT 'Active ±â°£',
  `grace_period` int(11) DEFAULT '0' COMMENT 'Grace ±â°£',
  `description` varchar(128) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`card_type`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ocs_card_type`
--

INSERT INTO `ocs_card_type` (`card_type`, `unit`, `active_period`, `grace_period`, `description`) VALUES
('AAAA', '50000', 0, 60, '50000SU 0days SMS Dealer'),
('AAAB', '10000', 30, 60, '10000SU 0days SMS Dealer'),
('AAAC', '3000', 30, 60, 'Rural Promotion (New site)'),
('AAAD', '33000', 90, 60, '33000SU 90days WLL'),
('AAAE', '2500', 0, 60, '1000SU 60days Econo'),
('AAAF', '5000', 30, 60, '5000SU 60days, bonus D20'),
('AAAG', '1000', 0, 60, '1000SU 0days Econo'),
('AAAH', '2000', 0, 60, '2000SU 0 days ALL service'),
('AAAI', '5000', 0, 60, '5000SU 60days, coupon D20'),
('AAAJ', '0', 0, 60, 'SkyPhone scratch (Skycall, D20)'),
('PPPP', '10000', 30, 30, 'PPPP'),
('PSPS', '10', 10, 10, '');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_code_master`
--

CREATE TABLE IF NOT EXISTS `ocs_code_master` (
  `master_code` varchar(10) NOT NULL,
  `code_name` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`master_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_code_master`
--

INSERT INTO `ocs_code_master` (`master_code`, `code_name`) VALUES
('B304', 'Personal/Corporate'),
('P100', 'Product Status');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_code_sub`
--

CREATE TABLE IF NOT EXISTS `ocs_code_sub` (
  `master_code` varchar(10) NOT NULL,
  `sub_code` varchar(10) NOT NULL DEFAULT '',
  `code_name` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`master_code`,`sub_code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_code_sub`
--

INSERT INTO `ocs_code_sub` (`master_code`, `sub_code`, `code_name`) VALUES
('B304', '10', 'Individual'),
('B304', '20', 'Corp. provider'),
('B304', '30', 'Personal company'),
('P100', '1', 'Planned'),
('P100', '2', 'Designed'),
('P100', '3', 'Activated'),
('P100', '4', 'Disconnected');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_counter`
--

CREATE TABLE IF NOT EXISTS `ocs_counter` (
  `counter_id` int(11) NOT NULL COMMENT 'COUNTER ID (ex:freeDosu,freeVodPacket)',
  `subscription_key` varchar(24) COLLATE latin1_general_ci NOT NULL COMMENT '... ID (MDN, MSISDN)  ',
  `counter_value` int(11) NOT NULL DEFAULT '0' COMMENT 'COUNTER .',
  `counter_value2` int(11) NOT NULL DEFAULT '0' COMMENT '... COUNTER .',
  `counter_max_value` int(11) NOT NULL DEFAULT '0' COMMENT 'COUNTER .. .',
  `counter_expire` bigint(20) NOT NULL DEFAULT '0' COMMENT 'COUNTER .....',
  `counter_deposit` int(11) NOT NULL DEFAULT '0' COMMENT '... COUNTER VALUE',
  `RESERVED0` varchar(8) COLLATE latin1_general_ci DEFAULT NULL,
  UNIQUE KEY `IDX_OCS_COUNTER_01` (`subscription_key`,`counter_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `ocs_counter_name`
--

CREATE TABLE IF NOT EXISTS `ocs_counter_name` (
  `counter_id` int(11) NOT NULL,
  `counter_name` varchar(40) NOT NULL,
  `counter_desc` varchar(128) NOT NULL,
  `counter_type` int(11) NOT NULL COMMENT 'COUNTER ???? (bit?? ??? int?? ?????)\n- XXXXXX01 : ??? reset ???\n- XXXXXX10 : expire ???? ??? counter????.\n- XXXX00XXXX : WON\n- XXXX01XXXX : DOSU\n- XXXX02XXXX : ???\n- XXXX03XXXX : sec\n- XXXX04XXXX : byte\n- XXXX05XXXX : packet',
  `counter_scale` int(11) NOT NULL,
  PRIMARY KEY (`counter_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `ocs_customer`
--

CREATE TABLE IF NOT EXISTS `ocs_customer` (
  `customer_id` varchar(11) NOT NULL,
  `customer_name` varchar(128) NOT NULL,
  `customer_type` varchar(3) NOT NULL,
  `date_register` datetime NOT NULL,
  PRIMARY KEY (`customer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_customer`
--

INSERT INTO `ocs_customer` (`customer_id`, `customer_name`, `customer_type`, `date_register`) VALUES
('8000067086', 'Min su22', '10', '2009-12-02 00:00:00'),
('9000010574', 'Garry Park', '20', '2008-04-15 00:00:00'),
('9000018483', 'SH&nbspSJ', '10', '2008-07-15 00:00:00'),
('9000022260', 'L SM', '10', '2008-08-09 00:00:00'),
('9000022366', 'SeGwang inc.', '20', '2008-08-11 00:00:00'),
('9000022717', 'International Art inc.', '20', '2008-08-14 00:00:00'),
('9000023413', 'Buil Tnc inc.', '20', '2008-08-21 00:00:00'),
('9000026424', 'KJJ', '10', '2008-09-04 00:00:00'),
('9000027381', 'NK Bio Inc.', '20', '2008-09-16 00:00:00'),
('9000027765', 'HanBit Resarch', '20', '2008-09-19 00:00:00'),
('9000030735', 'H Bene Inc.', '20', '2008-10-14 00:00:00'),
('9000034898', 'Daesung Construction', '20', '2008-11-18 00:00:00'),
('9000034914', 'Addo International inc.', '20', '2008-11-18 00:00:00'),
('9000034925', 'JuAn Inc.', '20', '2008-11-18 00:00:00'),
('9000035084', 'Neo Printech', '20', '2008-11-19 00:00:00'),
('9000035164', 'Brian', '10', '2008-11-20 00:00:00'),
('9000036551', 'Hansol PaJoo Inc.', '30', '2008-11-28 00:00:00'),
('9000037017', 'Okid TNC inc.', '20', '2008-12-01 00:00:00'),
('9000037317', 'Best Process Inc.', '20', '2008-12-03 00:00:00'),
('9000037660', 'GuHwa Construction Design Co.', '20', '2008-12-06 00:00:00'),
('9000037768', 'Hyundai Safe Public Company', '20', '2008-12-08 00:00:00'),
('9000038685', 'SJ Oil Inc.', '20', '2008-12-17 00:00:00'),
('9000039384', 'PCI Insurrace Branch', '20', '2008-12-23 00:00:00'),
('9000039600', 'SJ Car Center', '20', '2008-12-26 00:00:00'),
('9000039737', 'CY Elementary School', '20', '2008-12-29 00:00:00'),
('9000039858', 'UChnag Construction', '20', '2008-12-29 00:00:00'),
('9000039920', 'SungIl Process Inc.', '20', '2008-12-30 00:00:00'),
('9000040492', 'SJ Construction', '20', '2009-01-05 00:00:00'),
('9000041457', 'Y One Korea', '20', '2009-01-15 00:00:00'),
('9000042673', 'Hanbit Electronics', '20', '2009-02-02 00:00:00'),
('9000043303', 'Kewel', '10', '2009-02-09 00:00:00'),
('9000043628', 'KyungIl Elementary School', '30', '2009-02-12 00:00:00'),
('9000044155', 'JinHakSa', '20', '2009-02-18 00:00:00'),
('9000044792', 'KJM', '10', '2009-02-25 00:00:00'),
('9000044795', 'Young', '10', '2009-02-25 00:00:00'),
('9000046070', 'Hanbit Medica Company', '20', '2009-03-10 00:00:00'),
('9000046921', 'INT Digital Inc.', '20', '2009-03-19 00:00:00'),
('9000047167', 'Samsung CS Academy', '20', '2009-03-23 00:00:00'),
('9000047389', 'M.Jeany', '10', '2009-03-25 00:00:00'),
('9000047508', 'InChoen Corp.', '20', '2009-03-26 00:00:00'),
('9000047978', 'BSW Inc.', '20', '2009-03-30 00:00:00'),
('9000050219', 'KHY', '10', '2009-04-27 00:00:00'),
('9000050630', 'Ink Discount Mart', '20', '2009-04-30 00:00:00'),
('9000050731', 'ShinHan Walpaper Co.', '20', '2009-04-30 00:00:00'),
('9000051790', 'Mosan Elementry School', '30', '2009-05-15 00:00:00'),
('9000052382', 'KeyMax Air and Shipping Inc.', '20', '2009-05-22 00:00:00'),
('9000052622', 'wwwww', '10', '2009-05-26 00:00:00'),
('9000053751', 'Techno Com(Seoul)', '20', '2009-06-03 00:00:00'),
('9000053833', 'Seo', '10', '2009-06-03 00:00:00'),
('9000053940', 'Instopia Corporation', '20', '2009-06-05 00:00:00'),
('9000054001', 'Coma Inc.', '20', '2009-06-05 00:00:00'),
('9000054028', 'Bank Force DaeGu Br', '30', '2009-06-05 00:00:00'),
('9000054201', 'U sys Information Tech Inc.', '20', '2009-06-09 00:00:00'),
('9000054385', 'S.G Elementary School', '30', '2009-06-11 00:00:00'),
('9000055082', 'BYB', '10', '2009-06-19 00:00:00'),
('9000055298', 'Korea Human Association', '20', '2009-06-23 00:00:00'),
('9000055805', 'HyoJa Construction Co,. Ltd', '20', '2009-06-26 00:00:00'),
('9000056253', 'STS', '10', '2009-06-30 00:00:00'),
('9000056649', 'SBY', '10', '2009-07-01 00:00:00'),
('9000057092', 'KYR', '10', '2009-07-06 00:00:00'),
('9000057224', 'WonJi(Seoul)', '20', '2009-07-07 00:00:00'),
('9000057962', 'HS Material Inc.', '20', '2009-07-17 00:00:00'),
('9000058148', 'UlSan Chritian Association', '30', '2009-07-20 00:00:00'),
('9000060168', 'Lotte Construction Corp.', '20', '2009-08-05 00:00:00'),
('9000060588', 'DANASA Hotspital', '20', '2009-08-12 00:00:00'),
('9000060915', 'YJ Industry Development', '20', '2009-08-17 00:00:00'),
('9000061223', 'YGH', '10', '2009-08-20 00:00:00'),
('9000061977', 'HGS', '30', '2009-08-27 00:00:00'),
('9000062457', 'EMI Institution', '30', '2009-08-31 00:00:00'),
('9000062722', 'KHW', '10', '2009-08-31 00:00:00'),
('9000062723', 'Hondra', '30', '2009-08-31 00:00:00'),
('9000063060', 'YMR', '10', '2009-09-01 00:00:00'),
('9000064645', 'Carnegi Human Side Construction', '20', '2009-09-29 00:00:00'),
('9000067534', 'JJu', '10', '2009-12-22 00:00:00'),
('9100069773', 'Bong kuk', '10', '2010-03-08 00:00:00'),
('9100508015', 'TNC Tech', '20', '2011-01-14 00:00:00'),
('9100508017', 'dreamer', '10', '2011-01-15 00:00:00'),
('9100508018', 'SKT(In)', '20', '2011-01-14 00:00:00'),
('9100508019', 'SKT(OUT)', '20', '2011-01-14 00:00:00'),
('9100508023', 'Suk', '10', '2011-03-08 00:00:00'),
('9100508027', 'test', '10', '2011-06-09 00:00:00'),
('9100508028', 'test', '10', '2011-06-09 00:00:00'),
('9100508029', 'test', '10', '2011-06-09 00:00:00'),
('9100508030', 'test', '10', '2011-06-09 00:00:00'),
('9100508039', 'j-Kim-2', '10', '2011-02-02 00:00:00'),
('9100508043', 'Nara', '10', '2011-02-02 00:00:00'),
('9100508070', 'j-kim1-Demo', '10', '2011-03-28 00:00:00'),
('9100508071', 'j-kim1', '10', '2011-03-29 00:00:00'),
('9100508072', 'j-kim2', '10', '2011-03-29 00:00:00'),
('9100508081', 'Dong June-Demo', '10', '2011-03-31 00:00:00'),
('9100508087', 'Dong June-2', '30', '2011-04-05 00:00:00'),
('9100508115', 'dreamer', '10', '2011-05-13 00:00:00'),
('9100508118', 'jae won jung', '10', '2011-05-15 00:00:00'),
('9100508131', 'j-Kim-4', '10', '2011-05-30 00:00:00'),
('9100509134', 'JKim', '10', '2011-07-05 00:00:00'),
('9100509139', 'j-Kim', '10', '2011-07-08 00:00:00'),
('9100509140', 'jkim-test', '10', '2011-07-08 00:00:00'),
('9100509143', 'jkim1', '10', '2011-07-12 00:00:00'),
('9100509170', 'Jay-Kim', '10', '2011-08-02 00:00:00');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_customer_info`
--

CREATE TABLE IF NOT EXISTS `ocs_customer_info` (
  `customer_id` varchar(11) NOT NULL,
  `additional_info` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`customer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Stand-in structure for view `ocs_customer_view`
--
CREATE TABLE IF NOT EXISTS `ocs_customer_view` (
`customer_id` varchar(11)
,`customer_name` varchar(128)
,`code_name` varchar(100)
,`sub_code` varchar(10)
,`date_register` datetime
);
-- --------------------------------------------------------

--
-- Table structure for table `ocs_group`
--

CREATE TABLE IF NOT EXISTS `ocs_group` (
  `group_id` int(11) NOT NULL AUTO_INCREMENT,
  `group_type` int(11) NOT NULL DEFAULT '0' COMMENT '0:VPN, 1:Family, 2:Couple, 3:Extra',
  `parent_group_id` int(11) NOT NULL,
  `member_count` int(11) NOT NULL DEFAULT '0' COMMENT '0:unlimited',
  `service_type` int(11) NOT NULL,
  `master_number` varchar(24) NOT NULL,
  `group_name` varchar(64) NOT NULL,
  `ancestor_group_id` int(11) NOT NULL,
  `limit_usage` decimal(10,0) DEFAULT '0' COMMENT 'group limit usage',
  PRIMARY KEY (`group_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1086 ;

--
-- Dumping data for table `ocs_group`
--

INSERT INTO `ocs_group` (`group_id`, `group_type`, `parent_group_id`, `member_count`, `service_type`, `master_number`, `group_name`, `ancestor_group_id`, `limit_usage`) VALUES
(1084, 0, 1084, 0, 0, '91100011', 'UANGEL', 1084, '1000000'),
(1085, 0, 1084, 0, 0, '91100011', 'UANGEL', 1084, '1000000');

-- --------------------------------------------------------

--
-- Stand-in structure for view `ocs_group_account_key`
--
CREATE TABLE IF NOT EXISTS `ocs_group_account_key` (
`customer_id` varchar(11)
,`customer_name` varchar(128)
,`account_key` varchar(24)
,`status` int(11)
,`group_id` int(11)
,`ancestor_group_id` int(11)
,`group_name` varchar(64)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `ocs_group_account_key_view`
--
CREATE TABLE IF NOT EXISTS `ocs_group_account_key_view` (
`customer_id` varchar(11)
,`customer_name` varchar(128)
,`account_key` varchar(24)
,`status` int(11)
,`group_id` int(11)
,`ancestor_group_id` int(11)
,`group_name` varchar(64)
);
-- --------------------------------------------------------

--
-- Table structure for table `ocs_group_member`
--

CREATE TABLE IF NOT EXISTS `ocs_group_member` (
  `group_id` int(11) NOT NULL,
  `group_type` int(11) NOT NULL DEFAULT '0',
  `account_key` varchar(24) NOT NULL,
  `call_flag` int(11) DEFAULT '1' COMMENT '0:off net, 1:on net',
  `ancestor_group_id` int(11) NOT NULL,
  `extension` varchar(16) DEFAULT NULL,
  `limit_usage` int(11) DEFAULT '0',
  `account_usage` int(11) DEFAULT '0',
  `next_reset_date` date DEFAULT NULL,
  `description` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`group_type`,`account_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_group_member`
--

INSERT INTO `ocs_group_member` (`group_id`, `group_type`, `account_key`, `call_flag`, `ancestor_group_id`, `extension`, `limit_usage`, `account_usage`, `next_reset_date`, `description`) VALUES
(1085, 0, '91100011', 1, 1084, '5555', 0, 3000, NULL, NULL),
(1085, 0, '91100066', 1, 1084, '6666', 0, 3000, NULL, NULL),
(1, 1, '8800', 1, 0, NULL, 0, 0, NULL, NULL),
(2, 1, '9900', 1, 0, NULL, 0, 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_product`
--

CREATE TABLE IF NOT EXISTS `ocs_product` (
  `product_name` varchar(20) NOT NULL COMMENT '»óÇ°¸í',
  `product_desc` varchar(100) DEFAULT NULL COMMENT '»óÇ°¼³¸í',
  `product_serial_no` varchar(10) DEFAULT NULL COMMENT '»óÇ° °íÀ¯ ¹øÈ£',
  `product_status` varchar(2) DEFAULT NULL COMMENT 'planned, designed, activated, disconnected',
  `product_period` datetime DEFAULT NULL,
  `product_tid` int(11) DEFAULT NULL,
  PRIMARY KEY (`product_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_product`
--

INSERT INTO `ocs_product` (`product_name`, `product_desc`, `product_serial_no`, `product_status`, `product_period`, `product_tid`) VALUES
('BC', 'postpaid', '5', '1', '0000-00-00 00:00:00', NULL),
('Cool', 'prepaid', '3', '1', '0000-00-00 00:00:00', NULL),
('D20', 'prepaid', '1', '1', '0000-00-00 00:00:00', NULL),
('Free VPN', 'prepaid', '4', '1', '0000-00-00 00:00:00', NULL),
('HYBRID', 'postpaid', '12', '1', '0000-00-00 00:00:00', NULL),
('NICE', 'postpaid', '8', '1', '0000-00-00 00:00:00', NULL),
('SkyCall', 'prepaid', '2', '1', '0000-00-00 00:00:00', NULL),
('SkyNet', 'prepaid', '11', '1', '0000-00-00 00:00:00', NULL),
('SkyPhone', 'prepaid', '7', '1', '0000-00-00 00:00:00', NULL),
('SKYTEL', 'postpaid', '10', '1', '0000-00-00 00:00:00', NULL),
('SMS Dealer', 'prepaid', '0', '1', '0000-00-00 00:00:00', NULL),
('VIP', 'postpaid', '6', '1', '0000-00-00 00:00:00', NULL),
('VIP 1000', 'postpaid', '9', '1', '0000-00-00 00:00:00', NULL),
('VIP1', 'postpaid', '13', '1', '0000-00-00 00:00:00', NULL),
('VIP2', 'postpaid', '14', '1', '0000-00-00 00:00:00', NULL),
('VIP3', 'postpaid', '15', '1', '0000-00-00 00:00:00', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_product_card`
--

CREATE TABLE IF NOT EXISTS `ocs_product_card` (
  `card_type` varchar(4) NOT NULL COMMENT 'Ä«µå À¯Çü',
  `product_id` varchar(45) NOT NULL COMMENT '»óÇ° ÄÚµå',
  `usable` tinyint(1) DEFAULT '0' COMMENT '»ç¿ë°¡´É ¿©ºÎ(0:not usd, 1:use)',
  PRIMARY KEY (`card_type`,`product_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_product_card`
--

INSERT INTO `ocs_product_card` (`card_type`, `product_id`, `usable`) VALUES
('AAAA', '0', 1),
('AAAA', '1', 0);

-- --------------------------------------------------------

--
-- Stand-in structure for view `ocs_product_view`
--
CREATE TABLE IF NOT EXISTS `ocs_product_view` (
`product_serial_no` varchar(10)
,`product_desc` varchar(100)
,`product_name` varchar(20)
,`product_status` varchar(2)
,`product_period` datetime
,`product_tid` int(11)
,`code_name` varchar(100)
);
-- --------------------------------------------------------

--
-- Table structure for table `ocs_recharge_info`
--

CREATE TABLE IF NOT EXISTS `ocs_recharge_info` (
  `subscription_key` varchar(24) NOT NULL,
  `last_recharge_type` int(11) NOT NULL,
  `last_recharge_money` int(11) NOT NULL,
  `last_recharge_time` datetime NOT NULL,
  `voucher_number` varchar(32) NOT NULL,
  `error_count` int(11) NOT NULL,
  PRIMARY KEY (`subscription_key`),
  KEY `IDX_OCS_RECHARGE_INFO_01` (`subscription_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `ocs_rules`
--

CREATE TABLE IF NOT EXISTS `ocs_rules` (
  `rule_id` int(11) NOT NULL AUTO_INCREMENT,
  `rule_key` varchar(32) CHARACTER SET utf8 NOT NULL,
  `rule_name` varchar(32) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`rule_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=25 ;

--
-- Dumping data for table `ocs_rules`
--

INSERT INTO `ocs_rules` (`rule_id`, `rule_key`, `rule_name`) VALUES
(10, 'group:1071', 'subgroup dis'),
(13, 'campaign:1:event:873', 'April N'),
(14, 'campaign:1:event:871', NULL),
(15, 'campaign:1:event:875', NULL),
(16, 'campaign:1:event:873', 'April_Y'),
(17, 'group:1078:event:884', 'VPN_DISCOUNT'),
(18, 'campaign:7:event:873', 'May Promotion for N Product'),
(19, 'campaign:7:event:873', 'May Promotion for Y Product'),
(20, 'campaign:9:event:871', 'April N'),
(21, 'group:1085:event:884', 'VPN_1085_working'),
(22, 'group:1085:event:884', 'VPN_1085_night'),
(23, 'campaign:10:event:873', 'Product N'),
(24, 'campaign:10:event:873', 'Product N 20000');

-- --------------------------------------------------------

--
-- Table structure for table `ocs_subscription`
--

CREATE TABLE IF NOT EXISTS `ocs_subscription` (
  `subscription_key` varchar(24) NOT NULL,
  `subscription_type` int(11) DEFAULT NULL COMMENT '- 0:postpaid, 1:prepaid, 2:hybrid',
  `charging_type` int(11) DEFAULT NULL COMMENT '- 0:deduction,1:accumulation',
  `status` int(11) DEFAULT NULL COMMENT 'normal, suspend, initial, terminate, ...',
  `create_date` bigint(8) DEFAULT NULL,
  `active_date` bigint(8) DEFAULT NULL,
  `active_expire_date` bigint(8) DEFAULT NULL,
  `grace_expire_date` bigint(8) DEFAULT NULL,
  `home_info` varchar(32) DEFAULT NULL,
  `preferred_language` int(11) DEFAULT NULL COMMENT '- 0:Mongolia, 1:English',
  `notification_flag_set` int(11) DEFAULT NULL COMMENT '- 0:NONE, 1:SMS_NOTI, 2:IVR_NOTI 3:USSD_NOTI',
  PRIMARY KEY (`subscription_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ocs_subscription`
--

INSERT INTO `ocs_subscription` (`subscription_key`, `subscription_type`, `charging_type`, `status`, `create_date`, `active_date`, `active_expire_date`, `grace_expire_date`, `home_info`, `preferred_language`, `notification_flag_set`) VALUES
('91100000', 0, 0, 0, NULL, NULL, NULL, NULL, '', 0, 0),
('91100001', 0, 0, 1, 0, 1337933534, 0, 0, '105', 0, 0),
('91100011', 0, 0, 1, 0, 1337923482, 0, 0, '', 0, 0),
('91100022', 0, 0, 0, 1337759965, 0, 0, 0, '105', 0, 0),
('91100033', 0, 0, 0, NULL, NULL, NULL, NULL, '', 1, 1),
('91100044', 0, 0, 0, NULL, NULL, NULL, NULL, '', 0, 0),
('91100055', 0, 0, 0, NULL, NULL, NULL, NULL, '', 0, 0),
('91100077', 0, 0, 0, NULL, NULL, NULL, NULL, '', 0, 0),
('91100097', 0, 0, 0, NULL, NULL, NULL, NULL, '105', 0, 0),
('91100099', 0, 0, 0, NULL, NULL, NULL, NULL, '105', 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `ocs_vas`
--

CREATE TABLE IF NOT EXISTS `ocs_vas` (
  `subscription_key` varchar(24) NOT NULL,
  `vas_id` varchar(45) NOT NULL,
  `registred_date` datetime NOT NULL,
  `status` int(11) NOT NULL,
  PRIMARY KEY (`subscription_key`),
  UNIQUE KEY `IDX_OCS_VAS_01` (`vas_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Stand-in structure for view `pps_actions`
--
CREATE TABLE IF NOT EXISTS `pps_actions` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`service_id_fid` int(11)
,`service_id_op` int(11)
,`service_id` varchar(32)
,`service_idLower` varchar(32)
,`service_idUpper` varchar(32)
,`service_id_ref` varchar(32)
,`event_name_fid` int(11)
,`event_name_op` int(11)
,`event_name` varchar(32)
,`event_nameLower` varchar(32)
,`event_nameUpper` varchar(32)
,`event_name_ref` varchar(32)
,`is_vpn_fid` int(11)
,`is_vpn_op` int(11)
,`is_vpn` varchar(6)
,`is_vpnLower` varchar(6)
,`is_vpnUpper` varchar(6)
,`is_vpn_ref` varchar(32)
,`promotion_service_id_fid` int(11)
,`promotion_service_id_op` int(11)
,`promotion_service_id` varchar(30)
,`promotion_service_idLower` varchar(30)
,`promotion_service_idUpper` varchar(30)
,`promotion_service_id_ref` varchar(32)
,`priority_fid` int(11)
,`priority_op` int(11)
,`priority` int(11)
,`priorityLower` int(11)
,`priorityUpper` int(11)
,`priority_ref` varchar(32)
,`promotion_category_fid` int(11)
,`promotion_category_op` int(11)
,`promotion_category` varchar(30)
,`promotion_categoryLower` varchar(30)
,`promotion_categoryUpper` varchar(30)
,`promotion_category_ref` varchar(32)
,`promotion_parameter_fid` int(11)
,`promotion_parameter_op` int(11)
,`promotion_parameter` varchar(256)
,`promotion_parameterLower` varchar(256)
,`promotion_parameterUpper` varchar(256)
,`promotion_parameter_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Table structure for table `price_data`
--

CREATE TABLE IF NOT EXISTS `price_data` (
  `price_name` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `version` int(11) NOT NULL DEFAULT '0',
  `price` double DEFAULT NULL,
  PRIMARY KEY (`price_name`,`version`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `price_data`
--

INSERT INTO `price_data` (`price_name`, `version`, `price`) VALUES
('AIOS_SMS', 0, 20),
('AIOS_EVENT', 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `price_promotion`
--

CREATE TABLE IF NOT EXISTS `price_promotion` (
  `service_id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promoEndDate` varchar(18) COLLATE latin1_general_ci DEFAULT '2099-12-31',
  `promotionType` varchar(16) COLLATE latin1_general_ci DEFAULT 'general',
  `setup` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `targetSubsRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoCountingRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoGrantRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoUseRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `discountType` varchar(16) COLLATE latin1_general_ci DEFAULT NULL,
  `countWhenUse` tinyint(1) DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `category` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `if_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `if_not_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `setPriceTo` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `priceDiscountRate` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `price_promotion`
--

INSERT INTO `price_promotion` (`service_id`, `promotion`, `promoStartDate`, `promoEndDate`, `promotionType`, `setup`, `targetSubsRule`, `promoCountingRule`, `promoGrantRule`, `promoUseRule`, `discountType`, `countWhenUse`, `priority`, `category`, `if_applied`, `if_not_applied`, `setPriceTo`, `priceDiscountRate`) VALUES
('simple_accounting', 'simple_price_charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/t_charging_account/sg && rule.counter_type != "TIME"', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, NULL),
('PC_SMS', 'SMS_Account_Charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/aios_charging_account/sg && rule.counter_type != "TIME"', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, NULL),
('IPTV_EVENT', 'IPTV_EVENT_Account_Charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/aios_charging_account/sg && rule.counter_type != "TIME"', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, NULL),
('simple_discount', 'SIMPLE_DISCOUNT', '1970-01-01', '2099-12-31', 'discounting', NULL, NULL, NULL, NULL, '/t_discount_rule/', NULL, NULL, 1, 'simple_discount', NULL, NULL, NULL, '100 - rule.discount_rate'),
('PC_PACKET', 'DATA_LOAD', '1970-01-01', '2099-12-31', 'discounting', NULL, NULL, NULL, NULL, '/discount_rules/', NULL, NULL, 1, 'data_load_discount', NULL, NULL, NULL, NULL),
('giving_bonus', 'GIVING_BONUS', '1970-01-01', '2099-12-31', 'general', NULL, '/t_bonus_condition/', NULL, '/t_bonus_amount/g', NULL, NULL, NULL, 10, 'giving_bonus', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `promotion`
--

CREATE TABLE IF NOT EXISTS `promotion` (
  `service_id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promoEndDate` varchar(18) COLLATE latin1_general_ci DEFAULT '2099-12-31',
  `promotionType` varchar(16) COLLATE latin1_general_ci DEFAULT 'general',
  `setup` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `targetSubsRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoCountingRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoGrantRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `promoUseRule` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `discountType` varchar(16) COLLATE latin1_general_ci DEFAULT NULL,
  `countWhenUse` tinyint(1) DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `category` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `if_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `if_not_applied` varchar(1024) COLLATE latin1_general_ci DEFAULT NULL,
  `e1` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e2` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e3` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e4` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e5` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e6` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `e7` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `validUnit` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `validTime` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `validUnitType` varchar(16) COLLATE latin1_general_ci DEFAULT NULL,
  `validTimeType` varchar(16) COLLATE latin1_general_ci DEFAULT NULL,
  `accountingType` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `promotion`
--

INSERT INTO `promotion` (`service_id`, `promotion`, `promoStartDate`, `promoEndDate`, `promotionType`, `setup`, `targetSubsRule`, `promoCountingRule`, `promoGrantRule`, `promoUseRule`, `discountType`, `countWhenUse`, `priority`, `category`, `if_applied`, `if_not_applied`, `e1`, `e2`, `e3`, `e4`, `e5`, `e6`, `e7`, `validUnit`, `validTime`, `validUnitType`, `validTimeType`, `accountingType`) VALUES
('simple_accounting', 'simple_time_charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/t_charging_account/sg', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, 'rule.counter_type == "MIN" ? 60 : e2', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'time_charge'),
('simple_accounting', 'simple_volume_charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/t_charging_account/sg && rule.counter_type != "TIME" && rule.counter_type != "UNIT"', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "BYTE" ? 1 : e6', NULL, NULL, NULL, NULL, NULL, 'volume_charge'),
('simple_accounting', 'simple_extra_charging', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/t_charging_account/sg && rule.counter_type == "MONEY"', NULL, NULL, 9, 'accounting', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'extra_charge'),
('PC_VOICE', 'Voice_Accounting', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/aios_charging_account/sg', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, 'rule.counter_type == "MIN" ? 60 : e2', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'time_charge'),
('PC_PACKET', 'Packet_Accounting', '1970-01-01', '2099-12-31', 'accounting', NULL, NULL, NULL, NULL, '/aios_charging_account/sg && rule.counter_type != "TIME" && rule.counter_type != "UNIT"', NULL, NULL, 10, 'accounting', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "BYTE" ? 1 : e6', NULL, NULL, NULL, NULL, NULL, 'volume_charge'),
('simple_discount', 'SIMPLE_DISCOUNT', '1970-01-01', '2099-12-31', 'discounting', NULL, '/t_discount_condition/', NULL, NULL, '/t_discount_rate/g', NULL, NULL, 1, 'simple_discount', NULL, NULL, NULL, NULL, '100 - rule.discount_rate', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'min', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `promotionCounterPrice`
--

CREATE TABLE IF NOT EXISTS `promotionCounterPrice` (
  `service_id` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promotionCounterType` int(11) NOT NULL DEFAULT '0',
  `counterID` varchar(255) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `counterType` int(11) DEFAULT NULL,
  `initialValue` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `setCounterTo` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterExpiryDate` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterScale` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterThreshold` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterChange` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`,`promotionCounterType`,`counterID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `promotionCounterPrice`
--

INSERT INTO `promotionCounterPrice` (`service_id`, `promotion`, `promoStartDate`, `promotionCounterType`, `counterID`, `counterType`, `initialValue`, `setCounterTo`, `counterExpiryDate`, `counterScale`, `counterThreshold`, `counterChange`) VALUES
('simple_accounting', 'simple_price_charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "MONEY" ? -price : -1'),
('PC_SMS', 'SMS_Account_Charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "MONEY" ? -price : -1'),
('IPTV_EVENT', 'IPTV_EVENT_Account_Charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "MONEY" ? -price : -1'),
('giving_bonus', 'GIVING_BONUS', '1970-01-01', 2, 'rule.counter_id', 1, NULL, NULL, NULL, NULL, NULL, 'rule.bonus_amount');

-- --------------------------------------------------------

--
-- Table structure for table `promotionCounterTariff`
--

CREATE TABLE IF NOT EXISTS `promotionCounterTariff` (
  `service_id` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promotion` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `promoStartDate` varchar(18) COLLATE latin1_general_ci NOT NULL DEFAULT '1970-01-01',
  `promotionCounterType` int(11) NOT NULL DEFAULT '0',
  `counterID` varchar(255) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `counterType` int(11) DEFAULT NULL,
  `initialValue` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `setCounterTo` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterExpiryDate` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterScale` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `counterThreshold` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `ccPerSession` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `ccPerConsumedServiceUnit` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `ccForFirstChargeableTimeUnit` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `ccPerSubsequentChargeableTimeUnit` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `ccPerChargeableVolumeUnit` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_id`,`promotion`,`promoStartDate`,`promotionCounterType`,`counterID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `promotionCounterTariff`
--

INSERT INTO `promotionCounterTariff` (`service_id`, `promotion`, `promoStartDate`, `promotionCounterType`, `counterID`, `counterType`, `initialValue`, `setCounterTo`, `counterExpiryDate`, `counterScale`, `counterThreshold`, `ccPerSession`, `ccPerConsumedServiceUnit`, `ccForFirstChargeableTimeUnit`, `ccPerSubsequentChargeableTimeUnit`, `ccPerChargeableVolumeUnit`) VALUES
('simple_accounting', 'simple_time_charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type=="MIN" ? -e2 : rule.counter_type == "TIME" ? -e2 : -price', NULL),
('simple_accounting', 'simple_volume_charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "BYTE" ? -e6 : -price'),
('simple_accounting', 'simple_extra_charging', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, '-normalPrice', NULL, NULL, NULL, NULL),
('PC_VOICE', 'Voice_Accounting', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type=="MIN" ? -e2 : rule.counter_type == "TIME" ? -e2 : -price', NULL),
('PC_PACKET', 'Packet_Accounting', '1970-01-01', 3, 'rule.counter_name', 16, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'rule.counter_type == "BYTE" ? -e6 : -price');

-- --------------------------------------------------------

--
-- Table structure for table `promotion_list_name`
--

CREATE TABLE IF NOT EXISTS `promotion_list_name` (
  `list_name` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`list_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `rating_factors`
--

CREATE TABLE IF NOT EXISTS `rating_factors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `product_code` varchar(32) NOT NULL,
  `product_name` varchar(32) NOT NULL,
  `packaged_code` varchar(32) NOT NULL,
  `packaged_name` varchar(32) DEFAULT NULL,
  `factor` varchar(32) NOT NULL,
  `function_name` varchar(32) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `RuleList`
--

CREATE TABLE IF NOT EXISTS `RuleList` (
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `ruleName` varchar(128) COLLATE latin1_general_ci NOT NULL,
  `rule_id` int(11) NOT NULL AUTO_INCREMENT,
  `rule_desc` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`rule_id`),
  UNIQUE KEY `RuleList_key` (`ruleSetName`,`ruleName`,`rule_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=1384 ;

--
-- Dumping data for table `RuleList`
--

INSERT INTO `RuleList` (`ruleSetName`, `ruleName`, `rule_id`, `rule_desc`) VALUES
('pps_actions', '1', 1377, NULL),
('pps_actions', '1', 1378, NULL),
('pps_actions', '1', 1379, '1 : service_id = PC_VOICE , event_name=OCS_VPN_CALL, promotion_service_id = simple_discount , priority = 10 , promotion_parameter = ''t_discount_rule=vpn_discount'''),
('aios_price_decision', 'AIOS_SMS', 1380, NULL),
('aios_price_decision', 'AIOS_EVENT', 1381, NULL),
('vpn_discount_rate', 'VPN_1085_working', 1382, NULL),
('vpn_discount_rate', 'VPN_1085_night', 1383, NULL),
('call_type', 'MOBILE', 1366, NULL),
('call_type', 'PSTN', 1367, NULL),
('call_type', 'IPTV', 1368, NULL),
('event_actions', '7', 1369, NULL),
('aios_charging_account', 'Remains', 1354, NULL),
('holiday', 'false', 1370, NULL),
('vpn_discount_condition', 'VPN_1085_working', 1371, NULL),
('vpn_discount_condition', 'VPN_1085_night', 1372, NULL),
('activation_bonus_amount', 'May_Promotion_for_N_Product', 1373, NULL),
('activation_bonus_amount', 'May_Promotion_for_N_Product', 1374, NULL),
('activation_bonus_amount', 'May_Promotion_for_Y_Product', 1375, NULL),
('activation_bonus_amount', 'May_Promotion_for_Y_Product', 1376, NULL),
('aios_charging_account', 'LastRemains', 1355, NULL),
('aios_charging_account', 'LastRemains', 1356, NULL),
('aios_charging_account', 'Remains', 1357, NULL),
('activation_bonus_condition', 'May_Promotion_for_N_Product', 1358, NULL),
('activation_bonus_condition', 'May_Promotion_for_Y_Product', 1359, NULL),
('discount_rules', 'DataLoadFare_100', 1360, NULL),
('discount_rules', 'DataLoadFare_200', 1361, NULL),
('discount_rules', 'DataLoadFare_50', 1362, NULL),
('aios_tariff_decision', 'AIOS_VOICE', 1363, NULL),
('aios_tariff_decision', 'AIOS_VOICE', 1364, NULL),
('aios_tariff_decision', 'AIOS_PACKET', 1365, NULL),
('aios_charging_account', 'FreePacket', 1353, NULL),
('aios_charging_account', 'FreeSms', 1352, NULL),
('aios_charging_account', 'FreeVoice', 1351, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `RuleSetFactorMeta`
--

CREATE TABLE IF NOT EXISTS `RuleSetFactorMeta` (
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `fieldName` varchar(64) COLLATE latin1_general_ci NOT NULL,
  `factOrder` int(11) DEFAULT '0',
  `sortMethod` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `isResult` tinyint(1) DEFAULT '0',
  `mandatory` tinyint(1) DEFAULT '0',
  `domain_type_in_ruleset` varchar(64) COLLATE latin1_general_ci DEFAULT NULL,
  `domain_expr_in_ruleset` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  `description` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`ruleSetName`,`fieldName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `RuleSetFactorMeta`
--

INSERT INTO `RuleSetFactorMeta` (`ruleSetName`, `fieldName`, `factOrder`, `sortMethod`, `isResult`, `mandatory`, `domain_type_in_ruleset`, `domain_expr_in_ruleset`, `description`) VALUES
('pps_actions', 'promotion_category', 6, 'no_sort', 1, 0, NULL, NULL, NULL),
('pps_actions', 'promotion_parameter', 7, 'no_sort', 1, 1, NULL, NULL, NULL),
('call_type', 'calling', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('pps_actions', 'event_name', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('pps_actions', 'is_vpn', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('pps_actions', 'promotion_service_id', 4, 'no_sort', 1, 1, NULL, NULL, NULL),
('pps_actions', 'priority', 5, 'no_sort', 1, 1, NULL, NULL, NULL),
('pps_actions', 'service_id', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('holiday', 'week', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('lunch_discount', 'time', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('lunch_discount', 'discount_rate', 2, 'no_sort', 1, 0, NULL, NULL, NULL),
('aios_price_decision', 'call_type', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_price_decision', 'service', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_price_decision', 'service_id', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('activation_bonus_amount', 'counter_id', 3, 'no_sort', 1, 0, NULL, NULL, NULL),
('activation_bonus_amount', 'bonus_amount', 4, 'no_sort', 1, 0, NULL, NULL, NULL),
('activation_bonus_amount', 'db_action', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('activation_bonus_amount', 'targetRule', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('activation_bonus_condition', 'fullday', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('activation_bonus_condition', 'product', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('vpn_discount_rate', 'db_action', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('vpn_discount_rate', 'discount_rate', 3, 'no_sort', 1, 0, NULL, NULL, NULL),
('vpn_discount_rate', 'targetRule', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('vpn_discount_condition', 'vpn_group_id', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('vpn_discount_condition', 'week', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('vpn_discount_condition', 'time', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_charging_account', 'call_type', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_charging_account', 'service', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_charging_account', 'service_id', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_charging_account', 'priority', 4, 'no_sort', 1, 0, NULL, NULL, NULL),
('aios_charging_account', 'counter_name', 5, 'no_sort', 1, 0, NULL, NULL, NULL),
('aios_charging_account', 'counter_type', 6, 'no_sort', 1, 0, 'rule', 'value = (MONEY, TIME, UNIT, BYTE, MIN)', NULL),
('aios_tariff_decision', 'call_type', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_tariff_decision', 'service', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('aios_tariff_decision', 'service_id', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('event_actions', 'promotion_parameter', 6, 'no_sort', 1, 1, NULL, NULL, NULL),
('event_actions', 'promotion_category', 5, 'no_sort', 1, 0, NULL, NULL, NULL),
('event_actions', 'priority', 4, 'no_sort', 1, 1, NULL, NULL, NULL),
('event_actions', 'promotion_service_id', 3, 'no_sort', 1, 1, NULL, NULL, NULL),
('event_actions', 'event_name', 2, 'no_sort', 0, 0, NULL, NULL, NULL),
('event_actions', 'service_id', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('discount_rules', 'discount_rate', 4, 'desc', 1, 0, NULL, NULL, NULL),
('discount_rules', 'data_load_type', 3, 'no_sort', 0, 0, NULL, NULL, NULL),
('discount_rules', 'service', 1, 'no_sort', 0, 0, NULL, NULL, NULL),
('discount_rules', 'service_id', 2, 'no_sort', 0, 0, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `RuleSetMeta`
--

CREATE TABLE IF NOT EXISTS `RuleSetMeta` (
  `ruleSetName` varchar(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `rulename_isResult` tinyint(1) DEFAULT '1',
  `super_ruleset` varchar(64) COLLATE latin1_general_ci DEFAULT NULL,
  `rulename_domain_type` varchar(64) COLLATE latin1_general_ci DEFAULT NULL,
  `rulename_domain_expr` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`ruleSetName`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `RuleSetMeta`
--

INSERT INTO `RuleSetMeta` (`ruleSetName`, `rulename_isResult`, `super_ruleset`, `rulename_domain_type`, `rulename_domain_expr`) VALUES
('call_type', 1, NULL, NULL, NULL),
('pps_actions', 1, NULL, NULL, NULL),
('lunch_discount', 1, NULL, NULL, NULL),
('holiday', 1, NULL, NULL, NULL),
('aios_price_decision', 1, NULL, NULL, NULL),
('activation_bonus_amount', 1, NULL, NULL, NULL),
('activation_bonus_condition', 1, NULL, NULL, NULL),
('vpn_discount_rate', 1, NULL, NULL, NULL),
('vpn_discount_condition', 1, NULL, NULL, NULL),
('aios_charging_account', 1, NULL, NULL, NULL),
('aios_tariff_decision', 1, NULL, NULL, NULL),
('event_actions', 1, NULL, NULL, NULL),
('discount_rules', 1, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `rule_match`
--

CREATE TABLE IF NOT EXISTS `rule_match` (
  `match_name` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `match_category` char(64) COLLATE latin1_general_ci DEFAULT NULL,
  `targetRule` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `rule` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `match_return` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`match_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `rule_match_flow`
--

CREATE TABLE IF NOT EXISTS `rule_match_flow` (
  `flow_id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `name` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `match_name` char(64) COLLATE latin1_general_ci DEFAULT NULL,
  `priority` int(11) DEFAULT NULL,
  `match_group` char(64) COLLATE latin1_general_ci DEFAULT NULL,
  `exclusive_type` char(10) COLLATE latin1_general_ci DEFAULT NULL,
  `setup` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `if_matched` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `if_not_matched` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `parameterized` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`flow_id`,`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `rule_match_flow_def`
--

CREATE TABLE IF NOT EXISTS `rule_match_flow_def` (
  `flow_id` char(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `setup` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  `flow_return` varchar(1023) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`flow_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `rule_update_history`
--

CREATE TABLE IF NOT EXISTS `rule_update_history` (
  `update_id` int(11) NOT NULL AUTO_INCREMENT,
  `update_op` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `update_date` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `updater_address` varchar(32) COLLATE latin1_general_ci DEFAULT NULL,
  `updater` varchar(128) COLLATE latin1_general_ci DEFAULT NULL,
  `update_argument` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  `update_comment` varchar(512) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`update_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=80 ;

--
-- Dumping data for table `rule_update_history`
--

INSERT INTO `rule_update_history` (`update_id`, `update_op`, `update_date`, `updater_address`, `updater`, `update_argument`, `update_comment`) VALUES
(1, 'update', '2012-05-02 17:59:48', 'upcef/127.0.0.1', 'rating_util', '[reload, counters]', NULL),
(2, 'update', '2012-05-02 18:00:15', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(3, 'read', '2012-05-02 18:00:49', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(4, 'read', '2012-05-14 12:00:35', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(5, 'update', '2012-05-16 09:50:56', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(6, 'read', '2012-05-16 13:39:09', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(7, 'update', '2012-05-17 11:06:51', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(8, 'update', '2012-05-17 11:11:16', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(9, 'read', '2012-05-17 11:11:39', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(10, 'update', '2012-05-17 15:02:13', 'Tachyon/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(11, 'update', '2012-05-17 15:02:50', 'Tachyon/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(12, 'read', '2012-05-17 15:03:45', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(13, 'update', '2012-05-17 16:13:30', 'Tachyon/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(14, 'read', '2012-05-17 16:14:07', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(15, 'read', '2012-05-17 16:16:36', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(16, 'update', '2012-05-17 16:20:29', 'Tachyon/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(17, 'read', '2012-05-17 16:21:03', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(18, 'update', '2012-05-17 16:37:24', 'Tachyon/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(19, 'read', '2012-05-17 16:37:44', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(20, 'read', '2012-05-21 10:31:48', 'Tachyon/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(21, 'read', '2012-05-21 10:53:08', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(22, 'update', '2012-05-21 19:51:01', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(23, 'update', '2012-05-21 20:13:17', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(24, 'read', '2012-05-21 20:13:34', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(25, 'update', '2012-05-22 16:09:39', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(26, 'update', '2012-05-22 16:10:36', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(27, 'read', '2012-05-22 16:11:04', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(28, 'read', '2012-05-22 16:11:30', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(29, 'update', '2012-05-22 16:45:28', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(30, 'read', '2012-05-22 16:45:46', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(31, 'update', '2012-05-22 16:58:31', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(32, 'update', '2012-05-22 17:10:54', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(33, 'read', '2012-05-22 17:11:24', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(34, 'update', '2012-05-23 11:03:18', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(35, 'read', '2012-05-23 11:03:52', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(36, 'update', '2012-05-23 15:51:28', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(37, 'read', '2012-05-23 15:52:26', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(38, 'update', '2012-05-23 16:10:37', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(39, 'read', '2012-05-23 16:12:30', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(40, 'update', '2012-05-23 17:03:56', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(41, 'read', '2012-05-23 17:04:39', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(42, 'update', '2012-05-23 17:08:06', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(43, 'read', '2012-05-23 17:08:33', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(44, 'update', '2012-05-23 17:36:11', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(45, 'read', '2012-05-23 17:36:44', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(46, 'update', '2012-05-23 17:38:30', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(47, 'read', '2012-05-23 17:38:54', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(48, 'update', '2012-05-23 17:41:28', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(49, 'update', '2012-05-23 17:42:58', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(50, 'read', '2012-05-23 17:43:26', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(51, 'update', '2012-05-23 17:52:14', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(52, 'read', '2012-05-23 17:52:47', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(53, 'update', '2012-05-24 10:07:19', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(54, 'read', '2012-05-24 10:07:47', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(55, 'update', '2012-05-24 10:13:00', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(56, 'read', '2012-05-24 10:19:32', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(57, 'update', '2012-05-24 10:21:37', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(58, 'read', '2012-05-24 10:22:03', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(59, 'update', '2012-05-24 10:25:17', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(60, 'read', '2012-05-24 10:25:41', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(61, 'update', '2012-05-24 10:37:30', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(62, 'read', '2012-05-24 10:38:16', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(63, 'update', '2012-05-24 10:54:02', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(64, 'read', '2012-05-24 10:54:11', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(65, 'update', '2012-05-24 11:19:25', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(66, 'update', '2012-05-24 11:28:59', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(67, 'update', '2012-05-24 11:29:30', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(68, 'update', '2012-05-24 11:29:58', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(69, 'read', '2012-05-24 11:30:04', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(70, 'update', '2012-05-24 16:50:04', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(71, 'read', '2012-05-24 16:50:17', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(72, 'update', '2012-05-24 16:51:51', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(73, 'read', '2012-05-24 16:52:04', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(74, 'update', '2012-05-24 19:09:55', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(75, 'update', '2012-05-25 09:27:36', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(76, 'read', '2012-05-25 09:27:54', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(77, 'read', '2012-05-25 13:52:16', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL),
(78, 'update', '2012-05-25 13:54:28', 'upcef/127.0.0.1', 'rating_util', '[reload, all]', NULL),
(79, 'read', '2012-05-25 13:55:19', 'upcef/127.0.0.1', 'DBRuleEngine', 'caching all', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `script_alias`
--

CREATE TABLE IF NOT EXISTS `script_alias` (
  `service_name` varchar(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `service_type` varchar(16) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `var_name` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `expression` varchar(255) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_name`,`service_type`,`var_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `script_alias`
--

INSERT INTO `script_alias` (`service_name`, `service_type`, `var_name`, `expression`) VALUES
('COMMON', 'TARIFF', 'called', 'rating.destinationID '),
('COMMON', 'TARIFF', 'calling', 'request.subscriptionID '),
('COMMON', 'TARIFF', 'service_id', 'rating.serviceIdentifier '),
('COMMON', 'TARIFF', 'service', 'rating.extension.getExtension(''Ext_Service'') '),
('COMMON', 'TARIFF', 'balance', 'rating.extension.getExtension(''Ext_Balance'') '),
('COMMON', 'TARIFF', 'service_option', 'rating.extension.getExtension(''Ext_ServiceOption'') '),
('COMMON', 'TARIFF', 'vas', 'rating.extension.getExtension(''Ext_VAS'') '),
('COMMON', 'TARIFF', 'product', 'rating.extension.getExtension(''Ext_UserTariff'') '),
('COMMON', 'TARIFF', 'bundle', 'rating.extension.getExtension(''Ext_Bundle'') '),
('COMMON', 'TARIFF', 'grade', 'rating.extension.getExtension(''Ext_Grade'') '),
('COMMON', 'TARIFF', 'is_family', 'rating.extension.getBoolean(''Ext_IsFamiy'') '),
('COMMON', 'TARIFF', 'is_vpn', 'rating.extension.getBoolean(''Ext_IsVpn'') '),
('COMMON', 'TARIFF', 'vpn_group_id', 'rating.extension.getInt(''Ext_VpnGroupId'') '),
('COMMON', 'TARIFF', 'is_favorite', 'rating.extension.getExtension(''Ext_IsFavorite'') '),
('COMMON', 'TARIFF', 'cc_rating_group', 'rating.extension.getExtension(''Ext_PacketRatingGroup'') '),
('COMMON', 'TARIFF', 'cc_service_id', 'rating.extension.getExtension(''Ext_PacketServiceId'') '),
('COMMON', 'TARIFF', 'event_name', 'rating.extension.getExtension(''Ext_EventName'') '),
('COMMON', 'TARIFF', 'apply_action_ruleset', 'rating.extension.getExtension(''Ext_ApplyActionRuleset'') ');

-- --------------------------------------------------------

--
-- Table structure for table `service_script`
--

CREATE TABLE IF NOT EXISTS `service_script` (
  `service_identifier` varchar(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `request_type` varchar(16) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `script_path` varchar(256) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`service_identifier`,`request_type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `service_script`
--

INSERT INTO `service_script` (`service_identifier`, `request_type`, `script_path`) VALUES
('PC_VOICE', 'TARIFF', '$(UASYS_HOME)/rating/js/AIOS_VOICE.js'),
('PC_SMS', 'PRICE', '$(UASYS_HOME)/rating/js/AIOS_SMS.js'),
('PC_PACKET', 'TARIFF', '$(UASYS_HOME)/rating/js/AIOS_PACKET.js'),
('IPTV_EVENT', 'PRICE', '$(UASYS_HOME)/rating/js/IPTV_EVENT.js'),
('PC_EVENT', 'PRICE', '$(UASYS_HOME)/rating/js/AIOS_EVENT.js');

-- --------------------------------------------------------

--
-- Table structure for table `sub_tariff_data`
--

CREATE TABLE IF NOT EXISTS `sub_tariff_data` (
  `sub_tariff_name` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `version` int(11) NOT NULL DEFAULT '0',
  `e1` double DEFAULT NULL,
  `e2` double DEFAULT NULL,
  `e3` double DEFAULT NULL,
  `e4` double DEFAULT NULL,
  `e5` double DEFAULT NULL,
  `e6` double DEFAULT NULL,
  `e7` double DEFAULT NULL,
  `validUnits` int(11) DEFAULT NULL,
  `nextTariffName` char(32) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`sub_tariff_name`,`version`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

--
-- Dumping data for table `sub_tariff_data`
--

INSERT INTO `sub_tariff_data` (`sub_tariff_name`, `version`, `e1`, `e2`, `e3`, `e4`, `e5`, `e6`, `e7`, `validUnits`, `nextTariffName`) VALUES
('AIOS_PACKET', 0, 0, 0, 100, 0, 0.25, 1024, 0, NULL, NULL),
('AIOS_VOICE', 0, 1.8, 1, 100, 0, 0, 0, 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `ValueList`
--

CREATE TABLE IF NOT EXISTS `ValueList` (
  `ref_name` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `value` varchar(64) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`ref_name`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `valueList_meta`
--

CREATE TABLE IF NOT EXISTS `valueList_meta` (
  `ref_name` varchar(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `ref_type` int(11) NOT NULL,
  PRIMARY KEY (`ref_name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `version_list`
--

CREATE TABLE IF NOT EXISTS `version_list` (
  `subject` char(32) COLLATE latin1_general_ci NOT NULL DEFAULT '',
  `version` int(11) NOT NULL DEFAULT '0',
  `start_date` char(18) COLLATE latin1_general_ci DEFAULT NULL,
  PRIMARY KEY (`subject`,`version`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- --------------------------------------------------------

--
-- Stand-in structure for view `vpn_discount_condition`
--
CREATE TABLE IF NOT EXISTS `vpn_discount_condition` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`vpn_group_id_fid` int(11)
,`vpn_group_id_op` int(11)
,`vpn_group_id` int(11)
,`vpn_group_idLower` int(11)
,`vpn_group_idUpper` int(11)
,`vpn_group_id_ref` varchar(32)
,`week_fid` int(11)
,`week_op` int(11)
,`week` varchar(4)
,`weekLower` varchar(4)
,`weekUpper` varchar(4)
,`week_ref` varchar(32)
,`time_fid` int(11)
,`time_op` int(11)
,`time` varchar(4)
,`timeLower` varchar(4)
,`timeUpper` varchar(4)
,`time_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Stand-in structure for view `vpn_discount_rate`
--
CREATE TABLE IF NOT EXISTS `vpn_discount_rate` (
`ruleSetName` varchar(64)
,`ruleName` varchar(128)
,`rule_id` int(11)
,`rule_desc` varchar(1023)
,`targetRule_fid` int(11)
,`targetRule_op` int(11)
,`targetRule` varchar(32)
,`targetRuleLower` varchar(32)
,`targetRuleUpper` varchar(32)
,`targetRule_ref` varchar(32)
,`db_action_fid` int(11)
,`db_action_op` int(11)
,`db_action` varchar(128)
,`db_actionLower` varchar(128)
,`db_actionUpper` varchar(128)
,`db_action_ref` varchar(32)
,`discount_rate_fid` int(11)
,`discount_rate_op` int(11)
,`discount_rate` int(11)
,`discount_rateLower` int(11)
,`discount_rateUpper` int(11)
,`discount_rate_ref` varchar(32)
);
-- --------------------------------------------------------

--
-- Structure for view `activation_bonus_amount`
--
DROP TABLE IF EXISTS `activation_bonus_amount`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `activation_bonus_amount` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_targetRule`.`targetRule_fid` AS `targetRule_fid`,`factor_targetRule`.`targetRule_op` AS `targetRule_op`,`factor_targetRule`.`targetRule` AS `targetRule`,`factor_targetRule`.`targetRuleLower` AS `targetRuleLower`,`factor_targetRule`.`targetRuleUpper` AS `targetRuleUpper`,`factor_targetRule`.`targetRule_ref` AS `targetRule_ref`,`factor_db_action`.`db_action_fid` AS `db_action_fid`,`factor_db_action`.`db_action_op` AS `db_action_op`,`factor_db_action`.`db_action` AS `db_action`,`factor_db_action`.`db_actionLower` AS `db_actionLower`,`factor_db_action`.`db_actionUpper` AS `db_actionUpper`,`factor_db_action`.`db_action_ref` AS `db_action_ref`,`factor_counter_id`.`counter_id_fid` AS `counter_id_fid`,`factor_counter_id`.`counter_id_op` AS `counter_id_op`,`factor_counter_id`.`counter_id` AS `counter_id`,`factor_counter_id`.`counter_idLower` AS `counter_idLower`,`factor_counter_id`.`counter_idUpper` AS `counter_idUpper`,`factor_counter_id`.`counter_id_ref` AS `counter_id_ref`,`factor_bonus_amount`.`bonus_amount_fid` AS `bonus_amount_fid`,`factor_bonus_amount`.`bonus_amount_op` AS `bonus_amount_op`,`factor_bonus_amount`.`bonus_amount` AS `bonus_amount`,`factor_bonus_amount`.`bonus_amountLower` AS `bonus_amountLower`,`factor_bonus_amount`.`bonus_amountUpper` AS `bonus_amountUpper`,`factor_bonus_amount`.`bonus_amount_ref` AS `bonus_amount_ref` from ((((`RuleList` left join `factor_targetRule` on(((`RuleList`.`ruleSetName` = `factor_targetRule`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_targetRule`.`ruleName`) and (`RuleList`.`rule_id` = `factor_targetRule`.`rule_id`)))) left join `factor_db_action` on(((`RuleList`.`ruleSetName` = `factor_db_action`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_db_action`.`ruleName`) and (`RuleList`.`rule_id` = `factor_db_action`.`rule_id`)))) left join `factor_counter_id` on(((`RuleList`.`ruleSetName` = `factor_counter_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_counter_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_counter_id`.`rule_id`)))) left join `factor_bonus_amount` on(((`RuleList`.`ruleSetName` = `factor_bonus_amount`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_bonus_amount`.`ruleName`) and (`RuleList`.`rule_id` = `factor_bonus_amount`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'activation_bonus_amount');

-- --------------------------------------------------------

--
-- Structure for view `activation_bonus_condition`
--
DROP TABLE IF EXISTS `activation_bonus_condition`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `activation_bonus_condition` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_fullday`.`fullday_fid` AS `fullday_fid`,`factor_fullday`.`fullday_op` AS `fullday_op`,`factor_fullday`.`fullday` AS `fullday`,`factor_fullday`.`fulldayLower` AS `fulldayLower`,`factor_fullday`.`fulldayUpper` AS `fulldayUpper`,`factor_fullday`.`fullday_ref` AS `fullday_ref`,`factor_product`.`product_fid` AS `product_fid`,`factor_product`.`product_op` AS `product_op`,`factor_product`.`product` AS `product`,`factor_product`.`productLower` AS `productLower`,`factor_product`.`productUpper` AS `productUpper`,`factor_product`.`product_ref` AS `product_ref` from ((`RuleList` left join `factor_fullday` on(((`RuleList`.`ruleSetName` = `factor_fullday`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_fullday`.`ruleName`) and (`RuleList`.`rule_id` = `factor_fullday`.`rule_id`)))) left join `factor_product` on(((`RuleList`.`ruleSetName` = `factor_product`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_product`.`ruleName`) and (`RuleList`.`rule_id` = `factor_product`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'activation_bonus_condition');

-- --------------------------------------------------------

--
-- Structure for view `aios_charging_account`
--
DROP TABLE IF EXISTS `aios_charging_account`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `aios_charging_account` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_call_type`.`call_type_fid` AS `call_type_fid`,`factor_call_type`.`call_type_op` AS `call_type_op`,`factor_call_type`.`call_type` AS `call_type`,`factor_call_type`.`call_typeLower` AS `call_typeLower`,`factor_call_type`.`call_typeUpper` AS `call_typeUpper`,`factor_call_type`.`call_type_ref` AS `call_type_ref`,`factor_service`.`service_fid` AS `service_fid`,`factor_service`.`service_op` AS `service_op`,`factor_service`.`service` AS `service`,`factor_service`.`serviceLower` AS `serviceLower`,`factor_service`.`serviceUpper` AS `serviceUpper`,`factor_service`.`service_ref` AS `service_ref`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref`,`factor_priority`.`priority_fid` AS `priority_fid`,`factor_priority`.`priority_op` AS `priority_op`,`factor_priority`.`priority` AS `priority`,`factor_priority`.`priorityLower` AS `priorityLower`,`factor_priority`.`priorityUpper` AS `priorityUpper`,`factor_priority`.`priority_ref` AS `priority_ref`,`factor_counter_name`.`counter_name_fid` AS `counter_name_fid`,`factor_counter_name`.`counter_name_op` AS `counter_name_op`,`factor_counter_name`.`counter_name` AS `counter_name`,`factor_counter_name`.`counter_nameLower` AS `counter_nameLower`,`factor_counter_name`.`counter_nameUpper` AS `counter_nameUpper`,`factor_counter_name`.`counter_name_ref` AS `counter_name_ref`,`factor_counter_type`.`counter_type_fid` AS `counter_type_fid`,`factor_counter_type`.`counter_type_op` AS `counter_type_op`,`factor_counter_type`.`counter_type` AS `counter_type`,`factor_counter_type`.`counter_typeLower` AS `counter_typeLower`,`factor_counter_type`.`counter_typeUpper` AS `counter_typeUpper`,`factor_counter_type`.`counter_type_ref` AS `counter_type_ref` from ((((((`RuleList` left join `factor_call_type` on(((`RuleList`.`ruleSetName` = `factor_call_type`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_call_type`.`ruleName`) and (`RuleList`.`rule_id` = `factor_call_type`.`rule_id`)))) left join `factor_service` on(((`RuleList`.`ruleSetName` = `factor_service`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service`.`rule_id`)))) left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) left join `factor_priority` on(((`RuleList`.`ruleSetName` = `factor_priority`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_priority`.`ruleName`) and (`RuleList`.`rule_id` = `factor_priority`.`rule_id`)))) left join `factor_counter_name` on(((`RuleList`.`ruleSetName` = `factor_counter_name`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_counter_name`.`ruleName`) and (`RuleList`.`rule_id` = `factor_counter_name`.`rule_id`)))) left join `factor_counter_type` on(((`RuleList`.`ruleSetName` = `factor_counter_type`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_counter_type`.`ruleName`) and (`RuleList`.`rule_id` = `factor_counter_type`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'aios_charging_account');

-- --------------------------------------------------------

--
-- Structure for view `aios_price_decision`
--
DROP TABLE IF EXISTS `aios_price_decision`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `aios_price_decision` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_call_type`.`call_type_fid` AS `call_type_fid`,`factor_call_type`.`call_type_op` AS `call_type_op`,`factor_call_type`.`call_type` AS `call_type`,`factor_call_type`.`call_typeLower` AS `call_typeLower`,`factor_call_type`.`call_typeUpper` AS `call_typeUpper`,`factor_call_type`.`call_type_ref` AS `call_type_ref`,`factor_service`.`service_fid` AS `service_fid`,`factor_service`.`service_op` AS `service_op`,`factor_service`.`service` AS `service`,`factor_service`.`serviceLower` AS `serviceLower`,`factor_service`.`serviceUpper` AS `serviceUpper`,`factor_service`.`service_ref` AS `service_ref`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref` from (((`RuleList` left join `factor_call_type` on(((`RuleList`.`ruleSetName` = `factor_call_type`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_call_type`.`ruleName`) and (`RuleList`.`rule_id` = `factor_call_type`.`rule_id`)))) left join `factor_service` on(((`RuleList`.`ruleSetName` = `factor_service`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service`.`rule_id`)))) left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'aios_price_decision');

-- --------------------------------------------------------

--
-- Structure for view `aios_tariff_decision`
--
DROP TABLE IF EXISTS `aios_tariff_decision`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `aios_tariff_decision` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_call_type`.`call_type_fid` AS `call_type_fid`,`factor_call_type`.`call_type_op` AS `call_type_op`,`factor_call_type`.`call_type` AS `call_type`,`factor_call_type`.`call_typeLower` AS `call_typeLower`,`factor_call_type`.`call_typeUpper` AS `call_typeUpper`,`factor_call_type`.`call_type_ref` AS `call_type_ref`,`factor_service`.`service_fid` AS `service_fid`,`factor_service`.`service_op` AS `service_op`,`factor_service`.`service` AS `service`,`factor_service`.`serviceLower` AS `serviceLower`,`factor_service`.`serviceUpper` AS `serviceUpper`,`factor_service`.`service_ref` AS `service_ref`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref` from (((`RuleList` left join `factor_call_type` on(((`RuleList`.`ruleSetName` = `factor_call_type`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_call_type`.`ruleName`) and (`RuleList`.`rule_id` = `factor_call_type`.`rule_id`)))) left join `factor_service` on(((`RuleList`.`ruleSetName` = `factor_service`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service`.`rule_id`)))) left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'aios_tariff_decision');

-- --------------------------------------------------------

--
-- Structure for view `call_type`
--
DROP TABLE IF EXISTS `call_type`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `call_type` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_calling`.`calling_fid` AS `calling_fid`,`factor_calling`.`calling_op` AS `calling_op`,`factor_calling`.`calling` AS `calling`,`factor_calling`.`callingLower` AS `callingLower`,`factor_calling`.`callingUpper` AS `callingUpper`,`factor_calling`.`calling_ref` AS `calling_ref` from (`RuleList` left join `factor_calling` on(((`RuleList`.`ruleSetName` = `factor_calling`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_calling`.`ruleName`) and (`RuleList`.`rule_id` = `factor_calling`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'call_type');

-- --------------------------------------------------------

--
-- Structure for view `discount_rules`
--
DROP TABLE IF EXISTS `discount_rules`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `discount_rules` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_service`.`service_fid` AS `service_fid`,`factor_service`.`service_op` AS `service_op`,`factor_service`.`service` AS `service`,`factor_service`.`serviceLower` AS `serviceLower`,`factor_service`.`serviceUpper` AS `serviceUpper`,`factor_service`.`service_ref` AS `service_ref`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref`,`factor_data_load_type`.`data_load_type_fid` AS `data_load_type_fid`,`factor_data_load_type`.`data_load_type_op` AS `data_load_type_op`,`factor_data_load_type`.`data_load_type` AS `data_load_type`,`factor_data_load_type`.`data_load_typeLower` AS `data_load_typeLower`,`factor_data_load_type`.`data_load_typeUpper` AS `data_load_typeUpper`,`factor_data_load_type`.`data_load_type_ref` AS `data_load_type_ref`,`factor_discount_rate`.`discount_rate_fid` AS `discount_rate_fid`,`factor_discount_rate`.`discount_rate_op` AS `discount_rate_op`,`factor_discount_rate`.`discount_rate` AS `discount_rate`,`factor_discount_rate`.`discount_rateLower` AS `discount_rateLower`,`factor_discount_rate`.`discount_rateUpper` AS `discount_rateUpper`,`factor_discount_rate`.`discount_rate_ref` AS `discount_rate_ref` from ((((`RuleList` left join `factor_service` on(((`RuleList`.`ruleSetName` = `factor_service`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service`.`rule_id`)))) left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) left join `factor_data_load_type` on(((`RuleList`.`ruleSetName` = `factor_data_load_type`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_data_load_type`.`ruleName`) and (`RuleList`.`rule_id` = `factor_data_load_type`.`rule_id`)))) left join `factor_discount_rate` on(((`RuleList`.`ruleSetName` = `factor_discount_rate`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_discount_rate`.`ruleName`) and (`RuleList`.`rule_id` = `factor_discount_rate`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'discount_rules');

-- --------------------------------------------------------

--
-- Structure for view `event_actions`
--
DROP TABLE IF EXISTS `event_actions`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `event_actions` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref`,`factor_event_name`.`event_name_fid` AS `event_name_fid`,`factor_event_name`.`event_name_op` AS `event_name_op`,`factor_event_name`.`event_name` AS `event_name`,`factor_event_name`.`event_nameLower` AS `event_nameLower`,`factor_event_name`.`event_nameUpper` AS `event_nameUpper`,`factor_event_name`.`event_name_ref` AS `event_name_ref`,`factor_promotion_service_id`.`promotion_service_id_fid` AS `promotion_service_id_fid`,`factor_promotion_service_id`.`promotion_service_id_op` AS `promotion_service_id_op`,`factor_promotion_service_id`.`promotion_service_id` AS `promotion_service_id`,`factor_promotion_service_id`.`promotion_service_idLower` AS `promotion_service_idLower`,`factor_promotion_service_id`.`promotion_service_idUpper` AS `promotion_service_idUpper`,`factor_promotion_service_id`.`promotion_service_id_ref` AS `promotion_service_id_ref`,`factor_priority`.`priority_fid` AS `priority_fid`,`factor_priority`.`priority_op` AS `priority_op`,`factor_priority`.`priority` AS `priority`,`factor_priority`.`priorityLower` AS `priorityLower`,`factor_priority`.`priorityUpper` AS `priorityUpper`,`factor_priority`.`priority_ref` AS `priority_ref`,`factor_promotion_category`.`promotion_category_fid` AS `promotion_category_fid`,`factor_promotion_category`.`promotion_category_op` AS `promotion_category_op`,`factor_promotion_category`.`promotion_category` AS `promotion_category`,`factor_promotion_category`.`promotion_categoryLower` AS `promotion_categoryLower`,`factor_promotion_category`.`promotion_categoryUpper` AS `promotion_categoryUpper`,`factor_promotion_category`.`promotion_category_ref` AS `promotion_category_ref`,`factor_promotion_parameter`.`promotion_parameter_fid` AS `promotion_parameter_fid`,`factor_promotion_parameter`.`promotion_parameter_op` AS `promotion_parameter_op`,`factor_promotion_parameter`.`promotion_parameter` AS `promotion_parameter`,`factor_promotion_parameter`.`promotion_parameterLower` AS `promotion_parameterLower`,`factor_promotion_parameter`.`promotion_parameterUpper` AS `promotion_parameterUpper`,`factor_promotion_parameter`.`promotion_parameter_ref` AS `promotion_parameter_ref` from ((((((`RuleList` left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) left join `factor_event_name` on(((`RuleList`.`ruleSetName` = `factor_event_name`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_event_name`.`ruleName`) and (`RuleList`.`rule_id` = `factor_event_name`.`rule_id`)))) left join `factor_promotion_service_id` on(((`RuleList`.`ruleSetName` = `factor_promotion_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_service_id`.`rule_id`)))) left join `factor_priority` on(((`RuleList`.`ruleSetName` = `factor_priority`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_priority`.`ruleName`) and (`RuleList`.`rule_id` = `factor_priority`.`rule_id`)))) left join `factor_promotion_category` on(((`RuleList`.`ruleSetName` = `factor_promotion_category`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_category`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_category`.`rule_id`)))) left join `factor_promotion_parameter` on(((`RuleList`.`ruleSetName` = `factor_promotion_parameter`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_parameter`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_parameter`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'event_actions');

-- --------------------------------------------------------

--
-- Structure for view `holiday`
--
DROP TABLE IF EXISTS `holiday`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `holiday` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_week`.`week_fid` AS `week_fid`,`factor_week`.`week_op` AS `week_op`,`factor_week`.`week` AS `week`,`factor_week`.`weekLower` AS `weekLower`,`factor_week`.`weekUpper` AS `weekUpper`,`factor_week`.`week_ref` AS `week_ref` from (`RuleList` left join `factor_week` on(((`RuleList`.`ruleSetName` = `factor_week`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_week`.`ruleName`) and (`RuleList`.`rule_id` = `factor_week`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'holiday');

-- --------------------------------------------------------

--
-- Structure for view `lunch_discount`
--
DROP TABLE IF EXISTS `lunch_discount`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `lunch_discount` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_time`.`time_fid` AS `time_fid`,`factor_time`.`time_op` AS `time_op`,`factor_time`.`time` AS `time`,`factor_time`.`timeLower` AS `timeLower`,`factor_time`.`timeUpper` AS `timeUpper`,`factor_time`.`time_ref` AS `time_ref`,`factor_discount_rate`.`discount_rate_fid` AS `discount_rate_fid`,`factor_discount_rate`.`discount_rate_op` AS `discount_rate_op`,`factor_discount_rate`.`discount_rate` AS `discount_rate`,`factor_discount_rate`.`discount_rateLower` AS `discount_rateLower`,`factor_discount_rate`.`discount_rateUpper` AS `discount_rateUpper`,`factor_discount_rate`.`discount_rate_ref` AS `discount_rate_ref` from ((`RuleList` left join `factor_time` on(((`RuleList`.`ruleSetName` = `factor_time`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_time`.`ruleName`) and (`RuleList`.`rule_id` = `factor_time`.`rule_id`)))) left join `factor_discount_rate` on(((`RuleList`.`ruleSetName` = `factor_discount_rate`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_discount_rate`.`ruleName`) and (`RuleList`.`rule_id` = `factor_discount_rate`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'lunch_discount');

-- --------------------------------------------------------

--
-- Structure for view `ocs_account_key_view`
--
DROP TABLE IF EXISTS `ocs_account_key_view`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `ocs_account_key_view` AS select `a`.`account_key` AS `account_key`,`a`.`account_key_type` AS `account_key_type`,`b`.`account_key_name` AS `account_key_name`,(case `a`.`sales_flag` when '0' then 'Not Use' when '1' then 'Used' end) AS `sales_flag` from (`ocs_account_key` `a` join `ocs_account_key_type` `b`) where (`a`.`account_key_type` = `b`.`account_key_type`);

-- --------------------------------------------------------

--
-- Structure for view `ocs_customer_view`
--
DROP TABLE IF EXISTS `ocs_customer_view`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.5.1` SQL SECURITY DEFINER VIEW `ocs_customer_view` AS select `a`.`customer_id` AS `customer_id`,`a`.`customer_name` AS `customer_name`,`b`.`code_name` AS `code_name`,`b`.`sub_code` AS `sub_code`,`a`.`date_register` AS `date_register` from (`ocs_customer` `a` join `ocs_code_sub` `b`) where (`a`.`customer_type` = `b`.`sub_code`);

-- --------------------------------------------------------

--
-- Structure for view `ocs_group_account_key`
--
DROP TABLE IF EXISTS `ocs_group_account_key`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.5.1` SQL SECURITY DEFINER VIEW `ocs_group_account_key` AS select `a`.`customer_id` AS `customer_id`,`a`.`customer_name` AS `customer_name`,`b`.`account_key` AS `account_key`,`b`.`status` AS `status`,`c`.`group_id` AS `group_id`,`c`.`ancestor_group_id` AS `ancestor_group_id`,`d`.`group_name` AS `group_name` from (((`ocs_customer` `a` join `ocs_account` `b`) join `ocs_group_member` `c`) join `ocs_group` `d`) where ((`a`.`customer_id` = `b`.`customer_id`) and (`b`.`account_key` = `c`.`account_key`) and (`c`.`group_id` = `d`.`group_id`));

-- --------------------------------------------------------

--
-- Structure for view `ocs_group_account_key_view`
--
DROP TABLE IF EXISTS `ocs_group_account_key_view`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.5.1` SQL SECURITY DEFINER VIEW `ocs_group_account_key_view` AS select `a`.`customer_id` AS `customer_id`,`a`.`customer_name` AS `customer_name`,`b`.`account_key` AS `account_key`,`b`.`status` AS `status`,`c`.`group_id` AS `group_id`,`c`.`ancestor_group_id` AS `ancestor_group_id`,`d`.`group_name` AS `group_name` from (((`ocs_customer` `a` join `ocs_account` `b`) join `ocs_group_member` `c`) join `ocs_group` `d`) where ((`a`.`customer_id` = `b`.`customer_id`) and (`b`.`account_key` = `c`.`account_key`) and (`c`.`group_id` = `d`.`group_id`));

-- --------------------------------------------------------

--
-- Structure for view `ocs_product_view`
--
DROP TABLE IF EXISTS `ocs_product_view`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `ocs_product_view` AS select `a`.`product_serial_no` AS `product_serial_no`,`a`.`product_desc` AS `product_desc`,`a`.`product_name` AS `product_name`,`a`.`product_status` AS `product_status`,`a`.`product_period` AS `product_period`,`a`.`product_tid` AS `product_tid`,`b`.`code_name` AS `code_name` from (`ocs_product` `a` join `ocs_code_sub` `b`) where ((`a`.`product_status` = `b`.`sub_code`) and (`b`.`master_code` = 'P100'));

-- --------------------------------------------------------

--
-- Structure for view `pps_actions`
--
DROP TABLE IF EXISTS `pps_actions`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `pps_actions` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_service_id`.`service_id_fid` AS `service_id_fid`,`factor_service_id`.`service_id_op` AS `service_id_op`,`factor_service_id`.`service_id` AS `service_id`,`factor_service_id`.`service_idLower` AS `service_idLower`,`factor_service_id`.`service_idUpper` AS `service_idUpper`,`factor_service_id`.`service_id_ref` AS `service_id_ref`,`factor_event_name`.`event_name_fid` AS `event_name_fid`,`factor_event_name`.`event_name_op` AS `event_name_op`,`factor_event_name`.`event_name` AS `event_name`,`factor_event_name`.`event_nameLower` AS `event_nameLower`,`factor_event_name`.`event_nameUpper` AS `event_nameUpper`,`factor_event_name`.`event_name_ref` AS `event_name_ref`,`factor_is_vpn`.`is_vpn_fid` AS `is_vpn_fid`,`factor_is_vpn`.`is_vpn_op` AS `is_vpn_op`,`factor_is_vpn`.`is_vpn` AS `is_vpn`,`factor_is_vpn`.`is_vpnLower` AS `is_vpnLower`,`factor_is_vpn`.`is_vpnUpper` AS `is_vpnUpper`,`factor_is_vpn`.`is_vpn_ref` AS `is_vpn_ref`,`factor_promotion_service_id`.`promotion_service_id_fid` AS `promotion_service_id_fid`,`factor_promotion_service_id`.`promotion_service_id_op` AS `promotion_service_id_op`,`factor_promotion_service_id`.`promotion_service_id` AS `promotion_service_id`,`factor_promotion_service_id`.`promotion_service_idLower` AS `promotion_service_idLower`,`factor_promotion_service_id`.`promotion_service_idUpper` AS `promotion_service_idUpper`,`factor_promotion_service_id`.`promotion_service_id_ref` AS `promotion_service_id_ref`,`factor_priority`.`priority_fid` AS `priority_fid`,`factor_priority`.`priority_op` AS `priority_op`,`factor_priority`.`priority` AS `priority`,`factor_priority`.`priorityLower` AS `priorityLower`,`factor_priority`.`priorityUpper` AS `priorityUpper`,`factor_priority`.`priority_ref` AS `priority_ref`,`factor_promotion_category`.`promotion_category_fid` AS `promotion_category_fid`,`factor_promotion_category`.`promotion_category_op` AS `promotion_category_op`,`factor_promotion_category`.`promotion_category` AS `promotion_category`,`factor_promotion_category`.`promotion_categoryLower` AS `promotion_categoryLower`,`factor_promotion_category`.`promotion_categoryUpper` AS `promotion_categoryUpper`,`factor_promotion_category`.`promotion_category_ref` AS `promotion_category_ref`,`factor_promotion_parameter`.`promotion_parameter_fid` AS `promotion_parameter_fid`,`factor_promotion_parameter`.`promotion_parameter_op` AS `promotion_parameter_op`,`factor_promotion_parameter`.`promotion_parameter` AS `promotion_parameter`,`factor_promotion_parameter`.`promotion_parameterLower` AS `promotion_parameterLower`,`factor_promotion_parameter`.`promotion_parameterUpper` AS `promotion_parameterUpper`,`factor_promotion_parameter`.`promotion_parameter_ref` AS `promotion_parameter_ref` from (((((((`RuleList` left join `factor_service_id` on(((`RuleList`.`ruleSetName` = `factor_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_service_id`.`rule_id`)))) left join `factor_event_name` on(((`RuleList`.`ruleSetName` = `factor_event_name`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_event_name`.`ruleName`) and (`RuleList`.`rule_id` = `factor_event_name`.`rule_id`)))) left join `factor_is_vpn` on(((`RuleList`.`ruleSetName` = `factor_is_vpn`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_is_vpn`.`ruleName`) and (`RuleList`.`rule_id` = `factor_is_vpn`.`rule_id`)))) left join `factor_promotion_service_id` on(((`RuleList`.`ruleSetName` = `factor_promotion_service_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_service_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_service_id`.`rule_id`)))) left join `factor_priority` on(((`RuleList`.`ruleSetName` = `factor_priority`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_priority`.`ruleName`) and (`RuleList`.`rule_id` = `factor_priority`.`rule_id`)))) left join `factor_promotion_category` on(((`RuleList`.`ruleSetName` = `factor_promotion_category`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_category`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_category`.`rule_id`)))) left join `factor_promotion_parameter` on(((`RuleList`.`ruleSetName` = `factor_promotion_parameter`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_promotion_parameter`.`ruleName`) and (`RuleList`.`rule_id` = `factor_promotion_parameter`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'pps_actions');

-- --------------------------------------------------------

--
-- Structure for view `vpn_discount_condition`
--
DROP TABLE IF EXISTS `vpn_discount_condition`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `vpn_discount_condition` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_vpn_group_id`.`vpn_group_id_fid` AS `vpn_group_id_fid`,`factor_vpn_group_id`.`vpn_group_id_op` AS `vpn_group_id_op`,`factor_vpn_group_id`.`vpn_group_id` AS `vpn_group_id`,`factor_vpn_group_id`.`vpn_group_idLower` AS `vpn_group_idLower`,`factor_vpn_group_id`.`vpn_group_idUpper` AS `vpn_group_idUpper`,`factor_vpn_group_id`.`vpn_group_id_ref` AS `vpn_group_id_ref`,`factor_week`.`week_fid` AS `week_fid`,`factor_week`.`week_op` AS `week_op`,`factor_week`.`week` AS `week`,`factor_week`.`weekLower` AS `weekLower`,`factor_week`.`weekUpper` AS `weekUpper`,`factor_week`.`week_ref` AS `week_ref`,`factor_time`.`time_fid` AS `time_fid`,`factor_time`.`time_op` AS `time_op`,`factor_time`.`time` AS `time`,`factor_time`.`timeLower` AS `timeLower`,`factor_time`.`timeUpper` AS `timeUpper`,`factor_time`.`time_ref` AS `time_ref` from (((`RuleList` left join `factor_vpn_group_id` on(((`RuleList`.`ruleSetName` = `factor_vpn_group_id`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_vpn_group_id`.`ruleName`) and (`RuleList`.`rule_id` = `factor_vpn_group_id`.`rule_id`)))) left join `factor_week` on(((`RuleList`.`ruleSetName` = `factor_week`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_week`.`ruleName`) and (`RuleList`.`rule_id` = `factor_week`.`rule_id`)))) left join `factor_time` on(((`RuleList`.`ruleSetName` = `factor_time`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_time`.`ruleName`) and (`RuleList`.`rule_id` = `factor_time`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'vpn_discount_condition');

-- --------------------------------------------------------

--
-- Structure for view `vpn_discount_rate`
--
DROP TABLE IF EXISTS `vpn_discount_rate`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`192.168.1.151` SQL SECURITY DEFINER VIEW `vpn_discount_rate` AS select `RuleList`.`ruleSetName` AS `ruleSetName`,`RuleList`.`ruleName` AS `ruleName`,`RuleList`.`rule_id` AS `rule_id`,`RuleList`.`rule_desc` AS `rule_desc`,`factor_targetRule`.`targetRule_fid` AS `targetRule_fid`,`factor_targetRule`.`targetRule_op` AS `targetRule_op`,`factor_targetRule`.`targetRule` AS `targetRule`,`factor_targetRule`.`targetRuleLower` AS `targetRuleLower`,`factor_targetRule`.`targetRuleUpper` AS `targetRuleUpper`,`factor_targetRule`.`targetRule_ref` AS `targetRule_ref`,`factor_db_action`.`db_action_fid` AS `db_action_fid`,`factor_db_action`.`db_action_op` AS `db_action_op`,`factor_db_action`.`db_action` AS `db_action`,`factor_db_action`.`db_actionLower` AS `db_actionLower`,`factor_db_action`.`db_actionUpper` AS `db_actionUpper`,`factor_db_action`.`db_action_ref` AS `db_action_ref`,`factor_discount_rate`.`discount_rate_fid` AS `discount_rate_fid`,`factor_discount_rate`.`discount_rate_op` AS `discount_rate_op`,`factor_discount_rate`.`discount_rate` AS `discount_rate`,`factor_discount_rate`.`discount_rateLower` AS `discount_rateLower`,`factor_discount_rate`.`discount_rateUpper` AS `discount_rateUpper`,`factor_discount_rate`.`discount_rate_ref` AS `discount_rate_ref` from (((`RuleList` left join `factor_targetRule` on(((`RuleList`.`ruleSetName` = `factor_targetRule`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_targetRule`.`ruleName`) and (`RuleList`.`rule_id` = `factor_targetRule`.`rule_id`)))) left join `factor_db_action` on(((`RuleList`.`ruleSetName` = `factor_db_action`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_db_action`.`ruleName`) and (`RuleList`.`rule_id` = `factor_db_action`.`rule_id`)))) left join `factor_discount_rate` on(((`RuleList`.`ruleSetName` = `factor_discount_rate`.`ruleSetName`) and (`RuleList`.`ruleName` = `factor_discount_rate`.`ruleName`) and (`RuleList`.`rule_id` = `factor_discount_rate`.`rule_id`)))) where (`RuleList`.`ruleSetName` = 'vpn_discount_rate');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

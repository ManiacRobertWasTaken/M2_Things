/*
Navicat MySQL Data Transfer

Source Server         : Canary_live
Source Server Version : 50650
Source Host           : localhost:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50650
File Encoding         : 65001

Date: 2020-12-16 05:38:41
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for bonusEvent_itemTable
-- ----------------------------
DROP TABLE IF EXISTS `bonusEvent_itemTable`;
CREATE TABLE `bonusEvent_itemTable` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `attrtype0` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue0` smallint(6) NOT NULL DEFAULT '0',
  `attrtype1` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue1` smallint(6) NOT NULL DEFAULT '0',
  `attrtype2` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue2` smallint(6) NOT NULL DEFAULT '0',
  `attrtype3` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue3` smallint(6) NOT NULL DEFAULT '0',
  `attrtype4` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue4` smallint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=630000005 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of bonusEvent_itemTable
-- ----------------------------
INSERT INTO `bonusEvent_itemTable` VALUES ('469', '1', '2000', '15', '15', '16', '15', '17', '15', '18', '15');

-- ----------------------------
-- Table structure for bonusEvent_rewardTable
-- ----------------------------
DROP TABLE IF EXISTS `bonusEvent_rewardTable`;
CREATE TABLE `bonusEvent_rewardTable` (
  `id` int(10) NOT NULL,
  `itemReward` int(10) DEFAULT NULL,
  `itemCount` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of bonusEvent_rewardTable
-- ----------------------------
INSERT INTO `bonusEvent_rewardTable` VALUES ('0', '30001', '10');
INSERT INTO `bonusEvent_rewardTable` VALUES ('1', '30005', '10');

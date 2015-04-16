DELIMITER $$

--
-- Table structure for table `patch_log`
--
DROP TABLE IF EXISTS `patch_log` $$

CREATE TABLE  `patch_log` 
(
  `PATCH_NAME` varchar(100) DEFAULT NULL,
  `TIME_PATCHED` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$



DELIMITER ;


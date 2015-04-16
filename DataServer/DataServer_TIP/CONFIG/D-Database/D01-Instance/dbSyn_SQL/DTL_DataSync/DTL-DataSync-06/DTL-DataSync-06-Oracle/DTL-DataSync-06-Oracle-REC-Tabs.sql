drop table RECIPIENT;

CREATE TABLE RECIPIENT
(
  PKEY          NUMBER(9) CONSTRAINT RECIP_01_NN NOT NULL,
  NAME          VARCHAR2(30 BYTE) CONSTRAINT NL_RECIP_02_NN NOT NULL,
  ADDRESS       VARCHAR2(1024 BYTE),
  DB_LINK_NAME  VARCHAR2(40 BYTE),
  STATUS        NUMBER                          DEFAULT 0,
  TIMEOUT       NUMBER                          DEFAULT 0,
  PROP_TYPE     VARCHAR2(50 BYTE)               NOT NULL
)
TABLESPACE EVENT_DATA
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          10M
            NEXT             10M
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOLOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

COMMENT ON TABLE RECIPIENT IS 'Table RECIPIENT (RECIP) contains the recipients and their addresses for Advanced Queueing.';

COMMENT ON COLUMN RECIPIENT.PKEY IS 'Primary Key Column - A unique identifier for each row';

COMMENT ON COLUMN RECIPIENT.NAME IS 'The name of the recipient.  The same type as SYS.AQ$AGENT.NAME.';

COMMENT ON COLUMN RECIPIENT.ADDRESS IS 'The address of the recipient.  The same type as SYS.AQ$AGENT.ADDRESS.';


CREATE UNIQUE INDEX RECIP_PK ON RECIPIENT
(PKEY)
NOLOGGING
TABLESPACE EVENT_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          10M
            NEXT             10M
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE UNIQUE INDEX RECIP_01_UK ON RECIPIENT
(NAME, ADDRESS)
NOLOGGING
TABLESPACE EVENT_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          10M
            NEXT             10M
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


ALTER TABLE RECIPIENT ADD (
  CONSTRAINT RECIP_PK
 PRIMARY KEY
 (PKEY)
    USING INDEX 
    TABLESPACE EVENT_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          10M
                NEXT             10M
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

ALTER TABLE RECIPIENT ADD (
  CONSTRAINT RECIP_01_UK
 UNIQUE (NAME, ADDRESS)
    USING INDEX 
    TABLESPACE EVENT_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          10M
                NEXT             10M
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));


GRANT DELETE, INSERT, UPDATE ON  RECIPIENT TO ITS_USER;

GRANT SELECT ON  RECIPIENT TO ITS_VIEW;

drop table recipient_all;

CREATE TABLE RECIPIENT_ALL
(
  PKEY          NUMBER(9)                       NOT NULL,
  NAME          VARCHAR2(30 BYTE)               NOT NULL,
  MEMBER        VARCHAR2(30 BYTE)               NOT NULL,
  DB_LINK_NAME  VARCHAR2(40 BYTE),
  STATUS        NUMBER(1)                       NOT NULL,
  TIMEOUT       NUMBER
)
TABLESPACE CONFIG_DATA
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE UNIQUE INDEX RECIPIENT_ALL_PK ON RECIPIENT_ALL
(PKEY)
LOGGING
TABLESPACE CONFIG_DATA
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE UNIQUE INDEX RECIPIENT_ALL_UNIQUE ON RECIPIENT_ALL
(NAME, MEMBER)
LOGGING
TABLESPACE CONFIG_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


ALTER TABLE RECIPIENT_ALL ADD (
  CONSTRAINT RECIPIENT_ALL_PK
 PRIMARY KEY
 (PKEY)
    USING INDEX 
    TABLESPACE CONFIG_DATA
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

ALTER TABLE RECIPIENT_ALL ADD (
  CONSTRAINT RECIPIENT_ALL_UNIQUE
 UNIQUE (NAME, MEMBER)
    USING INDEX 
    TABLESPACE CONFIG_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

drop table recipient_group;

CREATE TABLE RECIPIENT_GROUP
(
  PKEY          NUMBER(9)                       NOT NULL,
  NAME          VARCHAR2(30 BYTE)               NOT NULL,
  MEMBER        VARCHAR2(30 BYTE)               NOT NULL,
  DB_LINK_NAME  VARCHAR2(40 BYTE),
  STATUS        NUMBER(1)                       NOT NULL,
  TIMEOUT       NUMBER                          DEFAULT 0,
  PROP_TYPE     VARCHAR2(50 BYTE)               NOT NULL
)
TABLESPACE CONFIG_DATA
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;

COMMENT ON TABLE RECIPIENT_GROUP IS 'Table recipient_group contains the list of stations and their neighbouring stations.';

COMMENT ON COLUMN RECIPIENT_GROUP.PKEY IS 'Primary Key Column - A unique identifier for each row';

COMMENT ON COLUMN RECIPIENT_GROUP.NAME IS 'The station name';

COMMENT ON COLUMN RECIPIENT_GROUP.MEMBER IS 'The neighbouring station name for the given station';

COMMENT ON COLUMN RECIPIENT_GROUP.DB_LINK_NAME IS 'Obsolete, The datbase link name to be created at satation to enable propogation to neighbouring station';

COMMENT ON COLUMN RECIPIENT_GROUP.STATUS IS 'The status of the link and advanced queue 0-down 1-active';


CREATE UNIQUE INDEX RECIPIENT_GROUP_UNIQUE ON RECIPIENT_GROUP
(NAME, MEMBER)
LOGGING
TABLESPACE CONFIG_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE UNIQUE INDEX RECIPIENT_GROUP_PK ON RECIPIENT_GROUP
(PKEY)
LOGGING
TABLESPACE CONFIG_DATA
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


ALTER TABLE RECIPIENT_GROUP ADD (
  CONSTRAINT RECIPIENT_GROUP_PK
 PRIMARY KEY
 (PKEY)
    USING INDEX 
    TABLESPACE CONFIG_DATA
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

ALTER TABLE RECIPIENT_GROUP ADD (
  CONSTRAINT RECIPIENT_GROUP_UNIQUE
 UNIQUE (NAME, MEMBER)
    USING INDEX 
    TABLESPACE CONFIG_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

drop table recipient_info;

CREATE TABLE RECIPIENT_INFO
(
  PKEY          NUMBER                          NOT NULL,
  NAME          VARCHAR2(30 BYTE)               NOT NULL,
  HOSTNAME      VARCHAR2(128 BYTE)              NOT NULL,
  ADDRESS       VARCHAR2(128 BYTE)              NOT NULL,
  DB_LINK_NAME  VARCHAR2(40 BYTE)               DEFAULT NULL,
  STATUS        NUMBER(1)                       NOT NULL,
  DB_TYPE       VARCHAR2(50 BYTE)               NOT NULL
)
TABLESPACE CONFIG_DATA
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


CREATE UNIQUE INDEX RECIPIENT_INFO_PK ON RECIPIENT_INFO
(PKEY)
LOGGING
TABLESPACE CONFIG_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


CREATE UNIQUE INDEX RECIPIENT_INFO_U_NAME_HOSTNAME ON RECIPIENT_INFO
(NAME, HOSTNAME)
LOGGING
TABLESPACE CONFIG_INDX
PCTFREE    10
INITRANS   2
MAXTRANS   255
STORAGE    (
            INITIAL          200K
            NEXT             200K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
NOPARALLEL;


ALTER TABLE RECIPIENT_INFO ADD (
  CONSTRAINT RECIPIENT_INFO_PK
 PRIMARY KEY
 (PKEY)
    USING INDEX 
    TABLESPACE CONFIG_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));

ALTER TABLE RECIPIENT_INFO ADD (
  CONSTRAINT RECIPIENT_INFO_U_NAME_HOSTNAME
 UNIQUE (NAME, HOSTNAME)
    USING INDEX 
    TABLESPACE CONFIG_INDX
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          200K
                NEXT             200K
                MINEXTENTS       1
                MAXEXTENTS       2147483645
                PCTINCREASE      0
               ));
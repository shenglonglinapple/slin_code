1. ftp (binary mode) scripts HA-DBSyn-Main.bsh, HA-DBSyn-Ora.sh and ha-oracle.xml of HA into Central Database Server(both nodes):
The scripts path of Oracle Database: /u01/app/datasyn/bin
2. Login Central Database Servers and execute below OS commands:
   # su - root
   # cd /u01/app/datasyn/bin
   # chown oracle:oracle ./HA-*
   # chown oracle:oracle ./ha-oracle.xml
   # chmod 755 ./HA-*
   # chmod 755 ./ha-oracle.xml

3. Re-configure HA-Oracle of Oracle Database Servers.
3.1 Stop HA-Oracle
   # su - Oracle
   # /u01/app/datasyn/bin/HA-DBSyn-Main.bsh stop 
3.2 Re-configure HA-Oracle according to 2.2.4.2 of document 'C955-Solaris_10_MySQL_SSReplication_Setup.doc'.

4. ftp (binary mode) scripts *.bsh, *.sh and configuration files 'ha.cnf', 'ha-mysql.xml' of HA into Station Database Servers(both Nodes):
The scripts path of MySQL Databases: /u01/app/HA
5. Login Station Database Servers and execute below OS commands:
   # su - root
   # cd /u01/app/HA
   # chmod 755 ./*.bsh
   # chmod 755 ./*.sh
6. Re-configure HA-MySQL of MySQL Database Servers.
6.1 Stop HA-Mysql
  # su - mysql
  # /u01/app/HA/HA-MySQL.bsh stop
6.2 Re-configure HA-MySQL according to 2.2.4.1 of document 'C955-Solaris_10_MySQL_SSReplication_Setup.doc'.



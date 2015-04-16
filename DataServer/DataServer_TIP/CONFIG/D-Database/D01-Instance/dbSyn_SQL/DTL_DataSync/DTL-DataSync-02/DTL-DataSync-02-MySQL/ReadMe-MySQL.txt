/*=====================================================
Version: DTL-DataSync-02-MySQL
Note: This DB patch must be applied after DTL-DataSync-MySQL applied.
-----------

number of scripts: 6
scripts name:
1.DTL-DataSync-02-MySQL-Main.sql			-- Main script to call other script(s).
2.DTL-DataSync-02-MySQL-Recipient.sql		-- Create and alter recipient tables.
3.DTL-DataSync-02-MySQL-Recreate-AQ.sql		-- Recreate AQ table.
4.DTL-DataSync-02-MySQL-Trg-Updated.sql		-- Update triggers.
5.DTL-DataSync-02-MySQL-Enq-Updated.sql		-- Update enqueue procedures.
6.DTL-DataSync-02-MySQL-Deq-Updated.sql		-- Update dequeue procedures.


========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name]
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ
3. type below command and Enter:
source DTL-DataSync-02-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/





tee LOG-DTL-DataSync-07-02-02-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

drop trigger if exists adm_seq_air_trg;
drop trigger if exists adm_seq_adr_trg;

insert into patch_log values ('DTL-DataSync-07-02-02-MySQL', sysdate());

commit;

notee;
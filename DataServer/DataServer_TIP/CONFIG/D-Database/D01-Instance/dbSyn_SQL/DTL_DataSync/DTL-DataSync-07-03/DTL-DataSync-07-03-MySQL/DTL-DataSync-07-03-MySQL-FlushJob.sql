delimiter $$
drop event if exists job_flush_hosts$$
CREATE EVENT job_flush_hosts
ON SCHEDULE
EVERY 5 MINUTE
STARTS (NOW() + INTERVAL 1 MINUTE)
DO
Begin
FLUSH HOSTS;
End$$
delimiter ;
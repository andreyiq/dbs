CREATE DATABASE '~/projects/dbs/db.fdb' user 'SYSDBA' password 'masterkey';
commit;
CONNECT '~/projects/dbs/db.fdb' user 'SYSDBA' password 'masterkey';
CREATE TABLE tmp (field1 integer);
INSERT INTO tmp (field1) VALUES (1);
INSERT iNTO tmp (field1) VALUES (2);
COMMIT;
SELECT * FROM tmp;

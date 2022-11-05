CREATE TABLE test (    test1 VARCHAR ( 50 ) ,	test2 VARCHAR ( 50 ) );
CREATE TABLE activity ( id int primary key GENERATED ALWAYS AS IDENTITY,  name VARCHAR ( 50 ) ,	min_age smallint , max_age smallint , max_participant int  );
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('tennis',7,99,4);
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('tennis de table',7,99,4);
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('UNO',5,99,9);
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('BEER party',18,99,100);
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('poker',21,99,8);
INSERT INTO  activity(name,min_age,max_age,max_participant ) VALUES ('young gun',6,12,15);
CREATE table date_acty( id int primary key GENERATED ALWAYS AS IDENTITY ,acti_key int , date_start timestamp , num_min int) ; 
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (5,'2022-11-09 23:30',300 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (3,'2022-11-10 17:30',30 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (3,'2022-11-11 17:30',30 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (3,'2022-11-12 17:30',30 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (4,'2022-11-12 21:30',210 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (4,'2022-11-18 21:30',210 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (1,'2022-11-18 13:30',200 );
INSERT INTO  date_acty(acti_key,date_start,num_min ) VALUES (1,'2022-11-18 13:30',200 );

--select * from  date_acty;
--select * from  activity;

create table reservation( id_vac int , id_date_acti int , unique(id_vac,id_date_acti));
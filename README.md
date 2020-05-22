# Simple_db
本项目是用C++实现的简易数据库。

支持的命令语句以及格式如下：

CREATE DATABASE **name**;

USE **name**;

CREATE TABLE **name ** ( **参数1 数据类型**，**参数2 数据类型**……);

INSERT INTO **name** VALUES ( **数据1, 数据2**....);

或INSERT INTO **name** ( **参数1**, **参数2**...) VALUES ( **数据1**,**数据2**...);

SELECT * FROM **name**; 

或SELECT **name** FROM **name** WHERE **name** **op** **value**;

或SELECT * FROM **name** WHERE **name op value**;

UPDATE **name** SET **name** = **newValue** WHERE **name op value**;

DELETE FROM **name** WHERE **name op value**;

或DELETE **name**；

BACK；


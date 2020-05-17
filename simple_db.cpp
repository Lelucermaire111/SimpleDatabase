/**********************************************************
	Simple Database
	最终版本：2020/5/14
	本程序实现了一个简单的数据库。
	使用者通过输入一定的命令，实现文件的操作以及表的增删查改。
	支持的命令有：CREATE DATABASE（创建数据库）, USE（选择数据库） ,
	CREATE TABLE（创建数据表） , INSERT（插入数据） , SELECT（查询数据） ,
	DELETE（删除数据） , BACK（回到上级目录）。
	对于数据类型不需要加分号，对于表头中的字段需要加引号。
	对于数据中的字符型需要加引号，整型则不需要。
	注：按照习惯我们通产在表头中的字段加单引号，字符型数据加双引号。
	数据库进行的操作都是在workplace文件夹下进行的。
	log文件夹中保存了当天的输入日志。
***********************************************************/
#include"kernal_process.h"

int main() 
{	

	std::string cmd;
	KernalProcessing kp;
	while (std::getline(std::cin, cmd)) {

		kp.Analysis(cmd);
	}
	return 0;

}
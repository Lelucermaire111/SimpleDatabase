#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include"table.h"
#include<ctime>
#include"SQL_analysis.h"

class KernalProcessing :public Table
{
public:
	KernalProcessing();									//默认构造

	~KernalProcessing();								//析构函数

	void Analysis(std::string& cmd);					//核心处理语句

	void UseDatabase(std::string& name);				//实现选择数据库

	void CreateDatabase(std::string& name);				//实现创建数据库

	void Back();										//回到上级目录

private:
	Sql_Analysis m_SqlAnalysis;
	std::string m_StartTime;
	std::ofstream m_Log;
};
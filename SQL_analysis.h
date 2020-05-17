#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<regex>
#include<string>
#include<iostream>
class Sql_Analysis 
{
public:
	Sql_Analysis();							//默认构造

	Sql_Analysis(std::string& s);			//传入字符串

	~Sql_Analysis(){}						//析构函数

	void Analysis();						//进行句法分析

	void CommandHelp(int n);				//进行命令格式帮助

	void CreateDatabase();					//解析创建数据库的句法

	void UseDatabse();						//解析选择数据库的句法

	void CreateTable();						//解析创建表的句法

	void Insert();							//解析插入表的句法

	void Select();							//解析查找表的句法

	void Delete();							//解析删除表的句法

	void Update();							//解析更新表的句法

	void Back();							//解析回到上级目录的句法

	void SetStr(std::string& s);			//设置需要处理的字符串

	std::string& GetKeyWord();				//获得命令关键字

	std::vector<std::string>& GetPara();	//获得参数表

	bool isCorrect();						//判断命令是否正确

	void Clear();							//清空参数表

private:
	std::string m_Str;					//需要处理的字符串
	std::string m_KeyWord;				//命令关键字
	std::vector<std::string>m_Para;		//参数表
	bool m_Correct;						//命令是否正确	
}; 

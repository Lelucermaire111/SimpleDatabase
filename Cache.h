#pragma once
#include<map>
#include<vector>
#include<string>
#include<time.h>

typedef struct TableInfo
{
	TableInfo() {}
	TableInfo(std::vector<std::vector<std::string>>&t, std::vector<std::string>&d, int &a, int &b)
		:m_table(t), m_datatype(d), keywordnum(a), recordnum(b) 
	{
		m_CreateTime = time(NULL);
	}
	int m_CreateTime = 0;
	std::vector<std::vector<std::string>>m_table;
	std::vector<std::string>m_datatype;
	int keywordnum = 0;
	int recordnum = 0;
	void operator=(const TableInfo& t)
	{
		m_CreateTime = t.m_CreateTime;
		m_table = t.m_table;
		m_datatype = t.m_datatype;
		keywordnum = t.keywordnum;
		recordnum = t.recordnum;
	}

};

struct Cache
{
	std::map<std::string, TableInfo>MyCache;
	int QueryMyCache( std::string name, TableInfo& t);
	void Refresh();
};
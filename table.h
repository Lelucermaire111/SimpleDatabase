//TABLE的定义
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<vector>
#include "files_processing.h"

class Table {
public:
	Table();
	//默认构造函数
	~Table();
	//析构函数
	void CreateTable(std::vector<std::string>& para);	
	//创建表
	int  UseTable(std::string name);
	//选定该表，读取表头、数据，选定成功返回1，否则返回0
	void Insert(std::vector<std::string>& para);
	//将数据插入该表
	void Update(std::vector<std::string>& para);
	//更新所选数据
	void Delete(std::vector<std::string>& para);
	//删除所选数据
	void Select(std::vector<std::string>& para);
	//查看所选数据
	void Int_Op(int keyPos, std::string key, std::string op);
	//对于INT型数据筛选，并将序号保存
	void Str_Op(int keyPos, std::string key, std::string op);
	//对于CHAR型数据筛选，并将序号保存
	void Save();
	//完成表的操作，将表保存
	bool isStrLegal(int a, int b,std::vector<std::string> para);
	//判断CHAR型数据字符长度是否超过所给长度
	void Draw_line(std::vector<int> max, int columns);
	//查看表时打印边框
	void Draw_line(int max);
	//重载函数，对于指定某列的情况
	void Draw_Datas(std::vector<int> max, std::vector<std::vector<std::string>>table, int columns, int row);
	//查看表时打印数据
	void Draw_Datas(int max, std::vector<std::string>table, int row);
	//重载函数，对于指定某列的情况
	void TableClear();
	//每次操作后对表进行初始化
protected: FilesProcessing m_FileProcess;

private:
	std::string m_Name = " ";							//表的名字
	int m_KeyWordNum;									//表中列（关键字）的数量
	int m_RecordNum;									//表中数据的数量
	std::vector<std::vector<std::string>> m_Table;		//表的结构
	std::vector<std::string> m_DataType;				//表中参数的数据类型
	std::vector<int> m_Pos;								//对于WHERE条件中序号的保存
	std::vector<int>m_PosList;							//实现索引（本项目暂未实现）
};
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<io.h>
#include<direct.h>

class FilesProcessing 
{
public:
	int ChangePath(std::string path_name="");
	//更改当前路径
	void CreateFolder(std::string dir_name);
	//创建文件夹
	void ShowAllFiles();
	//显示所有文件
	void WriteTxt(std::string name, std::vector<std::string>& record);
	//写入文本
	void ReadTxt(std::string name, std::vector<std::string >& record);
	//读取文本
	void WriteTableHeader(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<std::string>& datatype);
	//写入表头
	void WriteTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table);
	//写入表的数据
	void WriteTableIndexes();
	//写入表的索引
	void ReadTableHeader(int& keywordnum, int& recordnum, std::vector<std::vector<std::string>>& table, std::vector<std::string>& datatype);
	//读取表头
	void ReadTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<int>& poslist);
	//读取表的数据
	void ReadTableIndexes();
	//读取表的索引
};
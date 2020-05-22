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
	//���ĵ�ǰ·��
	void CreateFolder(std::string dir_name);
	//�����ļ���
	void ShowAllFiles();
	//��ʾ�����ļ�
	void WriteTxt(std::string name, std::vector<std::string>& record);
	//д���ı�
	void ReadTxt(std::string name, std::vector<std::string >& record);
	//��ȡ�ı�
	void WriteTableHeader(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<std::string>& datatype);
	//д���ͷ
	void WriteTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table);
	//д��������
	void WriteTableIndexes();
	//д��������
	void ReadTableHeader(int& keywordnum, int& recordnum, std::vector<std::vector<std::string>>& table, std::vector<std::string>& datatype);
	//��ȡ��ͷ
	void ReadTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<int>& poslist);
	//��ȡ�������
	void ReadTableIndexes();
	//��ȡ�������
};
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
	KernalProcessing();									//Ĭ�Ϲ���

	~KernalProcessing();								//��������

	void Analysis(std::string& cmd);					//���Ĵ������

	void UseDatabase(std::string& name);				//ʵ��ѡ�����ݿ�

	void CreateDatabase(std::string& name);				//ʵ�ִ������ݿ�

	void Back();										//�ص��ϼ�Ŀ¼

private:
	Sql_Analysis m_SqlAnalysis;
	std::string m_StartTime;
	std::ofstream m_Log;
};
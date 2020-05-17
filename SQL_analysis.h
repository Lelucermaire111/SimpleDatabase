#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<regex>
#include<string>
#include<iostream>
class Sql_Analysis 
{
public:
	Sql_Analysis();							//Ĭ�Ϲ���

	Sql_Analysis(std::string& s);			//�����ַ���

	~Sql_Analysis(){}						//��������

	void Analysis();						//���о䷨����

	void CommandHelp(int n);				//���������ʽ����

	void CreateDatabase();					//�����������ݿ�ľ䷨

	void UseDatabse();						//����ѡ�����ݿ�ľ䷨

	void CreateTable();						//����������ľ䷨

	void Insert();							//���������ľ䷨

	void Select();							//�������ұ�ľ䷨

	void Delete();							//����ɾ����ľ䷨

	void Update();							//�������±�ľ䷨

	void Back();							//�����ص��ϼ�Ŀ¼�ľ䷨

	void SetStr(std::string& s);			//������Ҫ������ַ���

	std::string& GetKeyWord();				//�������ؼ���

	std::vector<std::string>& GetPara();	//��ò�����

	bool isCorrect();						//�ж������Ƿ���ȷ

	void Clear();							//��ղ�����

private:
	std::string m_Str;					//��Ҫ������ַ���
	std::string m_KeyWord;				//����ؼ���
	std::vector<std::string>m_Para;		//������
	bool m_Correct;						//�����Ƿ���ȷ	
}; 

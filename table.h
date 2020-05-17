//TABLE�Ķ���
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
	//Ĭ�Ϲ��캯��
	~Table();
	//��������
	void CreateTable(std::vector<std::string>& para);	
	//������
	int  UseTable(std::string name);
	//ѡ���ñ���ȡ��ͷ�����ݣ�ѡ���ɹ�����1�����򷵻�0
	void Insert(std::vector<std::string>& para);
	//�����ݲ���ñ�
	void Update(std::vector<std::string>& para);
	//������ѡ����
	void Delete(std::vector<std::string>& para);
	//ɾ����ѡ����
	void Select(std::vector<std::string>& para);
	//�鿴��ѡ����
	void Int_Op(int keyPos, std::string key, std::string op);
	//����INT������ɸѡ��������ű���
	void Str_Op(int keyPos, std::string key, std::string op);
	//����CHAR������ɸѡ��������ű���
	void Save();
	//��ɱ�Ĳ�����������
	bool isStrLegal(int a, int b,std::vector<std::string> para);
	//�ж�CHAR�������ַ������Ƿ񳬹���������
	void Draw_line(std::vector<int> max, int columns);
	//�鿴��ʱ��ӡ�߿�
	void Draw_line(int max);
	//���غ���������ָ��ĳ�е����
	void Draw_Datas(std::vector<int> max, std::vector<std::vector<std::string>>table, int columns, int row);
	//�鿴��ʱ��ӡ����
	void Draw_Datas(int max, std::vector<std::string>table, int row);
	//���غ���������ָ��ĳ�е����
	void TableClear();
	//ÿ�β�����Ա���г�ʼ��
protected: FilesProcessing m_FileProcess;

private:
	std::string m_Name = " ";							//�������
	int m_KeyWordNum;									//�����У��ؼ��֣�������
	int m_RecordNum;									//�������ݵ�����
	std::vector<std::vector<std::string>> m_Table;		//��Ľṹ
	std::vector<std::string> m_DataType;				//���в�������������
	std::vector<int> m_Pos;								//����WHERE��������ŵı���
	std::vector<int>m_PosList;							//ʵ������������Ŀ��δʵ�֣�
};
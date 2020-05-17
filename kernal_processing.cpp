#include"kernal_process.h"

KernalProcessing::KernalProcessing()
{
	//m_FileProcess.ChangePath();
	m_FileProcess.ChangePath("workplace");
	std::cout << "�����ռ���:" << std::endl;
	m_FileProcess.ShowAllFiles();
	time_t t = time(NULL);
	char date[64];
	strftime(date, sizeof(date), "%Y_%m_%d", localtime(&t));
	strcat(date, ".txt");
	m_StartTime = date;
	m_FileProcess.ChangePath("logs");
	m_Log.open(m_StartTime, std::ios::app);
	if (!m_Log.is_open())
		std::cout << "��־�ļ�����ʧ��" << std::endl;
	m_FileProcess.ChangePath();
}

KernalProcessing::~KernalProcessing()
{
	m_Log.close();
}

void KernalProcessing::Analysis(std::string& cmd)
{
	long t1 = GetTickCount();								//��ʱ��ʼ
	m_Log << cmd << std::endl;								//��ӡ��־
	m_SqlAnalysis.SetStr(cmd);								//�䷨����ģ�鴫������
	m_SqlAnalysis.Analysis();								//���о䷨����
	if (m_SqlAnalysis.isCorrect())
	{
		std::string temp = m_SqlAnalysis.GetKeyWord();		//ͨ���䷨����ģ��õ��ؼ���
		if ("CREATE DATABASE" == temp)			CreateDatabase(m_SqlAnalysis.GetPara()[0]);
		else if ("USE" == temp)					UseDatabase(m_SqlAnalysis.GetPara()[0]);
		else if ("CREATE TABLE" == temp)		CreateTable(m_SqlAnalysis.GetPara());
		else if ("INSERT" == temp)				Insert(m_SqlAnalysis.GetPara());
		else if ("SELECT" == temp)				Select(m_SqlAnalysis.GetPara());
		else if ("UPDATE" == temp)				Update(m_SqlAnalysis.GetPara());
		else if ("DELETE" == temp)			    Delete(m_SqlAnalysis.GetPara());
		else if ("BACK" == temp)				Back();
	}
	m_SqlAnalysis.Clear();											//��վ䷨
	long t2 = GetTickCount();										//��ʱ����
	std::cout << "��ʱ��:" << 0.001*(t2 - t1) << "��" << std::endl;	//��ӡʱ��
}

void KernalProcessing::UseDatabase(std::string& name)
{
	m_FileProcess.ChangePath(name);
	std::cout << "���ݿ�" << name;
	m_FileProcess.ShowAllFiles();
}

void KernalProcessing::CreateDatabase(std::string& name)
{
	m_FileProcess.CreateFolder(name);
	m_FileProcess.ShowAllFiles();
}

void KernalProcessing::Back()
{
	m_FileProcess.ChangePath();
	m_FileProcess.ShowAllFiles();
}
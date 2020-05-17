#include"kernal_process.h"

KernalProcessing::KernalProcessing()
{
	//m_FileProcess.ChangePath();
	m_FileProcess.ChangePath("workplace");
	std::cout << "工作空间下:" << std::endl;
	m_FileProcess.ShowAllFiles();
	time_t t = time(NULL);
	char date[64];
	strftime(date, sizeof(date), "%Y_%m_%d", localtime(&t));
	strcat(date, ".txt");
	m_StartTime = date;
	m_FileProcess.ChangePath("logs");
	m_Log.open(m_StartTime, std::ios::app);
	if (!m_Log.is_open())
		std::cout << "日志文件创建失败" << std::endl;
	m_FileProcess.ChangePath();
}

KernalProcessing::~KernalProcessing()
{
	m_Log.close();
}

void KernalProcessing::Analysis(std::string& cmd)
{
	long t1 = GetTickCount();								//计时开始
	m_Log << cmd << std::endl;								//打印日志
	m_SqlAnalysis.SetStr(cmd);								//句法分析模块传入命令
	m_SqlAnalysis.Analysis();								//进行句法分析
	if (m_SqlAnalysis.isCorrect())
	{
		std::string temp = m_SqlAnalysis.GetKeyWord();		//通过句法分析模块得到关键字
		if ("CREATE DATABASE" == temp)			CreateDatabase(m_SqlAnalysis.GetPara()[0]);
		else if ("USE" == temp)					UseDatabase(m_SqlAnalysis.GetPara()[0]);
		else if ("CREATE TABLE" == temp)		CreateTable(m_SqlAnalysis.GetPara());
		else if ("INSERT" == temp)				Insert(m_SqlAnalysis.GetPara());
		else if ("SELECT" == temp)				Select(m_SqlAnalysis.GetPara());
		else if ("UPDATE" == temp)				Update(m_SqlAnalysis.GetPara());
		else if ("DELETE" == temp)			    Delete(m_SqlAnalysis.GetPara());
		else if ("BACK" == temp)				Back();
	}
	m_SqlAnalysis.Clear();											//清空句法
	long t2 = GetTickCount();										//计时结束
	std::cout << "计时器:" << 0.001*(t2 - t1) << "秒" << std::endl;	//打印时间
}

void KernalProcessing::UseDatabase(std::string& name)
{
	m_FileProcess.ChangePath(name);
	std::cout << "数据库" << name;
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
#include "SQL_analysis.h"

Sql_Analysis::Sql_Analysis() {
	m_Correct = true;
}

Sql_Analysis::Sql_Analysis(std::string& s) {
	m_Correct = true;
	m_Str = s;
}

void Sql_Analysis::SetStr(std::string& s) {
	m_Str = s;
}
void Sql_Analysis::CommandHelp(int n)
{
	switch (n) {
	case 0: std::cout << "命令集包含以下关键字CREATE DATABASE,USE,CREATE TABLE,INSERT,SELECT,UPDATE,DELETE,BACK" << std::endl; break;
	case 1: std::cout << "格式应为 CREATE DATABASE <DB_NAME>;"<<std::endl; break;
	case 2: std::cout << "格式应为 USE <DB_NAME>;"<<std::endl; break;
	case 3: std::cout << "格式应为 CREATE TABLE <TABLE_NAME> (<参数1> <数据类型>, <参数2> <数据类型>);" << std::endl; break;
	case 4: std::cout << "格式应为 INSERT INTO <TABLE_NAME> VALUES (<数据1>,<数据2>....);" << std::endl
		<< "或 INSERT INTO <NAME> (<参数1>,<参数2>...) VALUES (<数据1>,<数据2>...);" << std::endl; break;
	case 5:	std::cout << "格式应为 SELECT * FROM <TABLE_NAME>;" << std::endl
		<< "或 SELECT <NAME> FROM <TABLE_NAME> WHERE <NAME> <OP> <VALUE>;" << std::endl; break;
	case 6:	std::cout << "格式应为 UPDATE <TABLE_NAME> SET <NAME> = <NEWVALUE> WHERE <NAME> <OP> <VALUE>;" << std::endl; break;
	case 7:	std::cout << "格式应为 DELETE FROM <TABLE_NAME> WHERE <NAME> <OP> <VALUE>;" << std::endl
		<<"或 DELETE <NAME>;";break;

	}
}
void Sql_Analysis::Analysis() 
{
	std::regex pattern[10];
	std::smatch temp;
	pattern[0] = std::regex("\\s*(CREATE DATABASE).*");
	pattern[1] = std::regex("\\s*(USE).*");
	pattern[2] = std::regex("\\s*(CREATE TABLE).*");
	pattern[3] = std::regex("\\s*(INSERT).*");
	pattern[4] = std::regex("\\s*(SELECT).*");
	pattern[5] = std::regex("\\s*(UPDATE).*");
	pattern[6] = std::regex("\\s*(DELETE).*");
	pattern[7] = std::regex("\\s*(BACK).*");
	for (int i = 0; i <= 8; ++i) {
		if (i == 8) {
			m_Correct = false;
			std::cout << "该命令不在支持的命令中" << std::endl;
			CommandHelp(0);				//命令输入有误
		}
		if (std::regex_match(m_Str, temp, pattern[i])) 
		{
			m_KeyWord = temp[1];
			switch (i) {
			case 0:CreateDatabase(); break;
			case 1:UseDatabse();	 break;
			case 2:CreateTable();	 break;
			case 3:Insert();		 break;
			case 4:Select();		 break;
			case 5:Update();		 break;
			case 6:Delete();		 break; 
			case 7:Back();			 break;
			}
			break;
		}
	}
}

void Sql_Analysis::CreateDatabase() {
	std::regex pattern ("\\s*CREATE DATABASE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;]\\s*");
	std::smatch temp;
	if (!std::regex_match(m_Str, temp, pattern)) {
		m_Para.clear();
		m_Correct = false;
		std::cout << "命令格式有误" << std::endl;
		CommandHelp(1);
	}
	else {
		m_Correct = true;
		std::cout << "命令正确" << std::endl;
		m_Para.push_back(temp[1]);
	}
}

void Sql_Analysis::UseDatabse() {
	std::regex pattern ("\\s*USE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;]\\s*");
	std::smatch temp;
	if (!std::regex_match(m_Str, temp, pattern)) {
		m_Para.clear();
		m_Correct = false;
		std::cout << "命令格式有误" << std::endl;
		CommandHelp(2);
	}
	else {
		m_Correct = true;
		m_Para.push_back(temp[1]);
	}
}

void Sql_Analysis::CreateTable() {
	std::regex pattern ("\\s*CREATE TABLE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*\\((\\s*\\S+\\s+[\\w\(\)]+\\s*[,\)])+[;]\\s*");
	std::smatch temp;
	if (!std::regex_match(m_Str, temp, pattern)) {
		m_Para.clear();
		m_Correct = false;
		std::cout << "命令格式有误" << std::endl;
		CommandHelp(3);
	}
	else {
		m_Para.push_back(temp[1]);
		std::regex pattern1 ("\\s*\\(?['\"](\\S+)['\"]\\s+(\\S+)\\s*[,\)]");
		std::string tempStr = m_Str;
		while (std::regex_search(tempStr, temp, pattern1))//查找可以匹配的子串
		{
			m_Para.push_back(temp[1]);
			m_Para.push_back(temp[2]);
			tempStr = temp.suffix().str();
		}
	}
	int length = m_Para.size();				//参数数量
	std::vector<int>len;
	for (int i = 2; i < length; i += 2) 
	{
		if (m_Para[i] == "INT")
		{
			m_Correct = true;
			continue;
		}
		else if (std::regex_match(m_Para[i], std::regex("VARCHAR\\(([0-9]+)\\)"))) 
		{
			std::regex_match(m_Para[i], temp, std::regex("VARCHAR\\(([0-9]+)\\)"));
			len.push_back(atoi(temp[1].str().c_str()));
			m_Correct = true;
		}
		else 
		{
			m_Correct = false;
			std::cout << "存在不支持的数据类型:" << m_Para[i] << std::endl;
			std::cout << "支持以下两种类型:INT 数值型; VARCHAR(字串长度) 字符串." << std::endl;
			m_Para.clear();
			break;
		}
	}
}

void Sql_Analysis::Insert() {
	std::smatch temp;
	std::regex pattern1 ("\\s*INSERT INTO\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s+VALUES\\s*\\((\\s*[\"]*\\S+[\"]*\\s*[,\\)])+\\s*[;]\\s*");
	std::regex pattern2 ("\\s*INSERT INTO\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s+\\((\\s*[']\\S+[']\\s*[,\\)])+\\s+VALUES\\s*\\((\\s*[\"]*\\S+[\"]*\\s*[,\\)])+\\s*[;]\\s*");
	if (std::regex_match(m_Str, temp, pattern1)) {
		m_Para.push_back(temp[1]);
		std::string tempStr = m_Str;
		m_Para.push_back("DEFAULT");
		std::regex pattern("\\s*[\"]*([^\"\\s\(\)]+)[\"]*\\s*[,\\)]");
		while (std::regex_search(tempStr, temp, pattern)) {
			m_Para.push_back(temp[1]);
			tempStr = temp.suffix().str();
		}
		m_Correct = true;
	}
	else if (std::regex_match(m_Str, temp, pattern2)) {
		m_Para.push_back(temp[1]);
		std::string tempStr=m_Str;
		m_Para.push_back("ASSIGNED");
		std::regex pattern3("\\s*[']\\s*(\\S+)\\s*[']\\s*[,\\)]");
		while (std::regex_search(tempStr, temp, pattern3)) {
			m_Para.push_back(temp[1]);
			tempStr = temp.suffix().str();
		}
		int paraNum = m_Para.size() - 2;
		std::regex pattern4("\\s*[\"]*\\s*([^\"\\s]+)\\s*[\"]*\\s*[,\\)]");
		while (std::regex_search(tempStr, temp, pattern4)) {
			m_Para.push_back(temp[1]);
			tempStr = temp.suffix().str();
		}
		int dataNum = m_Para.size() - paraNum - 2;
		if (dataNum != paraNum) {
			m_Para.clear();
			m_Correct = false;
			std::cout << "数据与字段数量不匹配" << std::endl;
		}
		else{
			m_Correct = true;
		}
	}
	else {
		m_Correct = false;
		m_Para.clear();
		std::cout << "命令格式有误" << std::endl;
		CommandHelp(4);
	}
}

void Sql_Analysis::Select()
{
	std::smatch temp;
	std::regex pattern1("\\s*SELECT\\s+\\*\\s+FROM\\s+(\\S+)\\s*[;]\\s*");
	std::regex pattern2("\\s*SELECT\\s+[']*([^'\"\\s]+)[']*\\s+FROM\\s+(\\S+)\\s+WHERE\\s+[']*([^'\"\\s]+)[']*\\s*([=!<>]+)\\s*['\"]*([^'\"\\s]+)['\"]*\\s*[;]\\s*");
	if (std::regex_match(m_Str, temp, pattern1))
	{
		m_Para.push_back("DEFAULT");
		m_Para.push_back(temp[1]);
		m_Correct = true;
	}
	else if (std::regex_match(m_Str, temp, pattern2))
	{
		m_Para.push_back("ASSIGNED");
		m_Para.push_back(temp[2]);
		m_Para.push_back(temp[1]);
		m_Para.push_back(temp[3]);
		m_Para.push_back(temp[4]);
		m_Para.push_back(temp[5]);
		m_Correct = true;
	}
	else
	{
		m_Correct = false;
		std::cout << "命令格式有误" << std::endl;
		CommandHelp(5);
	}

}

void Sql_Analysis::Update() 
{
	std::smatch temp;
	std::regex pattern("\\s*UPDATE\\s+(\\S+)\\s+SET\\s+[']*([^'\"\\s]+)[']*\\s*=\\s*[\"]*([^'\"\\s]+)[\"]*\\s+WHERE\\s+[']*([^'\"\\s]+)[']*\\s+([><!=]+)\\s+[\"]*([^'\"\\s]+)[\"]*\\s*[;]\\s*");
	if (std::regex_match(m_Str, temp, pattern))
	{
		m_Para.push_back(temp[1]);
		m_Para.push_back(temp[2]);
		m_Para.push_back(temp[3]);
		m_Para.push_back(temp[4]);
		m_Para.push_back(temp[5]);
		m_Para.push_back(temp[6]);
		m_Correct = true;
	}
	else
	{
		m_Correct = false;
		std::cout << "命令格式错误!" << std::endl;
		CommandHelp(6);
	}
}

void Sql_Analysis::Delete() 
{
	std::smatch temp;
	std::regex pattern1("\\s*DELETE FROM\\s+(\\S+)\\s+WHERE\\s+[\']*([^'\"\\s]+)[\']*\\s+([><!=]+)\\s+[\"]*([^'\"\\s]+)[\"]*\\s*[;]");
	std::regex pattern2("\\s*DELETE\\s+([^;\\s]+)\\s*[;]\\s*");
	if (std::regex_match(m_Str, temp, pattern1))
	{
		m_Para.push_back("ASSIGNED");
		m_Para.push_back(temp[1]);
		m_Para.push_back(temp[2]);
		m_Para.push_back(temp[3]);
		m_Para.push_back(temp[4]);
		m_Correct = true;
	}
	else if (std::regex_match(m_Str, temp, pattern2))
	{
		m_Para.push_back("DEFAULT");
		m_Para.push_back(temp[1]);
		m_Correct = true;
	}
	else
	{
		m_Correct = false;
		std::cout << "命令格式错误!" << std::endl;
		CommandHelp(7);
	}
}

void Sql_Analysis::Back()   {}
std::string& Sql_Analysis::GetKeyWord()
{
	return m_KeyWord;
}

bool Sql_Analysis::isCorrect()
{
	if (m_Correct)return true;
	else return false;
}

std::vector<std::string>& Sql_Analysis::GetPara()
{
	return m_Para;
}

void Sql_Analysis::Clear()
{
	m_Para.clear();
}
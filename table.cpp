#include"table.h"

Table::Table() {
	m_KeyWordNum = 0;
	m_RecordNum = 0;
	m_Info = TableInfo(m_Table, m_DataType, m_KeyWordNum, m_RecordNum);
}

Table::~Table() {

}

void Table::ReadCache()
{
	m_Table = m_Info.m_table;
	m_DataType = m_Info.m_datatype;
	m_KeyWordNum = m_Info.keywordnum;
	m_RecordNum = m_Info.recordnum;
}

void Table::CreateTable(std::vector<std::string>& para) {
	m_FileProcess.CreateFolder(para[0]);
	m_KeyWordNum = (para.size() - 1) / 2;					//确定表列（关键字）的数量
	m_Table.resize(m_KeyWordNum);
	for (int i = 0; i < m_KeyWordNum; i++)
	{
		m_Table[i].push_back(para[2 * i + 1]);
		m_DataType.push_back(para[2 * i + 2]);
	}
	m_FileProcess.ShowAllFiles();
	m_FileProcess.ChangePath(para[0]);
	TableClear();
}

int Table::UseTable(std::string name)
{
	if (m_FileProcess.ChangePath(name))
	{
		my_cache.Refresh();
		if (my_cache.QueryMyCache(name, m_Info))
		{
			ReadCache();
			std::cout << "读取缓存" << std::endl;
			return 2;
		}
		m_FileProcess.ReadTableHeader(m_KeyWordNum, m_RecordNum, m_Table, m_DataType);
		m_FileProcess.ReadTableRecord(m_KeyWordNum, m_RecordNum, m_Table, m_PosList);
		m_FileProcess.ReadTableIndexes();
		m_Info = TableInfo(m_Table, m_DataType, m_KeyWordNum, m_RecordNum);
		my_cache.MyCache[name] = m_Info;
		return 1;
	}
	else return 0;
}

bool isNum(std::string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (!isdigit(s[i]))return false;
	}
	return true;
}

bool Table::isStrLegal(int a, int b,std::vector<std::string> para)
{
	if (m_DataType[a].substr(0, 7) == "VARCHAR")
	{
		int start = m_DataType[a].find_first_of("(");
		int end = m_DataType[a].find_last_of(")");
		int len = atoi(m_DataType[a].substr(start + 1, end - start + 1).c_str());
		if (para[b].size() > len)
		{
			std::cout << para[b] << "字符串长度超过给定值" << len << std::endl;
			return false;
		}
	}
	return true;
}
void Table::Insert(std::vector<std::string>& para)
{
	if (UseTable(para[0]))
	{
		if (para[1] == "DEFAULT")
		{
			m_RecordNum++;
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				if (m_DataType[i] == "INT")
				{
					if (!isNum(para[i + 2]))
					{
						std::cout <<"'"<< para[i + 2] << "' 不是正确的数据类型INT" << std::endl;
						return;
					}
				}
				if (!isStrLegal(i , i + 2 , para))return;
				m_Table[i].push_back(para[i + 2]);
			}
		}

		if (para[1] == "ASSIGNED")
		{
			int len = (para.size() - 2) / 2;
			std::vector<int>temp;
			for (int i = 0; i < len; i++)
			{
				int pos;
				for (pos = 0; pos <= m_KeyWordNum && para[i + 2] == m_Table[pos][0]; pos++)
				{
					if (pos == m_KeyWordNum)
						std::cout << "表头中不存在字段 '" << para[i + 2] << " '" << std::endl;
					else temp.push_back(pos);
				}
			}
			m_RecordNum++;
			for (int i = 0; i < temp.size(); i++)
				m_Table[temp[i]].push_back(para[len + i + 2]);
			for (int i = 0; i < m_KeyWordNum; i++)
				if (m_Table[i].size() <= m_RecordNum)
					m_Table[i].push_back("*");
		}
		std::cout << "插入数据成功" << std::endl;
		TableClear();
	}
	else return;
}

void Table::Int_Op(int keyPos,std::string key, std::string op)
{
	for (int i = 1; i <= m_RecordNum; i++)
	{
		if (op == "=")
			if (atoi(m_Table[keyPos][i].c_str()) == atoi(key.c_str()))	m_Pos.push_back(i);
		if (op == ">")
			if (atoi(m_Table[keyPos][i].c_str()) > atoi(key.c_str()))	m_Pos.push_back(i);
		if (op == "<")
			if (atoi(m_Table[keyPos][i].c_str()) < atoi(key.c_str()))	m_Pos.push_back(i);
		if (op == ">=")
			if (atoi(m_Table[keyPos][i].c_str()) >= atoi(key.c_str()))	m_Pos.push_back(i);
		if (op == "<=")
			if (atoi(m_Table[keyPos][i].c_str()) <= atoi(key.c_str()))	m_Pos.push_back(i);
		if (op == "!=")
			if (atoi(m_Table[keyPos][i].c_str()) != atoi(key.c_str()))	m_Pos.push_back(i);
	}
}

void Table::Str_Op(int keyPos, std::string key, std::string op)
{
	for (int i = 1; i <= m_RecordNum; i++)
	{
		if (op == "=")
			if (m_Table[keyPos][i] == key)	m_Pos.push_back(i);
		if (op == ">")
			if (m_Table[keyPos][i] > key)	m_Pos.push_back(i);
		if (op == "<")
			if (m_Table[keyPos][i] < key)	m_Pos.push_back(i);
		if (op == ">=")
			if (m_Table[keyPos][i] >= key)	m_Pos.push_back(i);
		if (op == "<=")
			if (m_Table[keyPos][i] <= key)	m_Pos.push_back(i);
		if (op == "!=")
			if (m_Table[keyPos][i] != key)	m_Pos.push_back(i);
	}
}

void Table::Delete(std::vector<std::string>& para)
{
	if (para[0] == "DEFAULT")
	{
		m_FileProcess.ChangePath(para[1]);
		m_FileProcess.ChangePath();
		m_FileProcess.DeleteFolder(para[1]);
		std::cout << para[0] << "已删除" << std::endl;
		m_FileProcess.ShowAllFiles();

	}
	if (para[0] == "ASSIGNED") {
		if (UseTable(para[1]))
		{
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				if (m_Table[i][0] == para[2])
				{
					if (m_DataType[i] == "INT")
						Int_Op(i, para[4], para[3]);
					else
						Str_Op(i, para[4], para[3]);
					break;
				}
				if (i == m_KeyWordNum)
				{
					std::cout << "表头中不存在字段： " << para[2] << std::endl;
					return;
				}
			}
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				for (int j = 0; j < m_Pos.size(); j++)
				{
					std::vector<std::string>::iterator it = m_Table[i].begin();
					it += (m_Pos[j] - j);
					m_Table[i].erase(it);
				}
			}
			if (m_Pos.size() > 0)std::cout << "删除数据成功！" << std::endl;
			else std::cout << "未找到满足条件的数据！" << std::endl;
			m_RecordNum -= m_Pos.size();
			TableClear();
		}
		else return;
	}
}

void Table::Update(std::vector<std::string>& para)
{
	if (UseTable(para[0]))
	{
		int keyPos = -1;
		for (int i = 0; i < m_KeyWordNum; i++)
		{
			if (m_Table[i][0] == para[1])
			{
				keyPos = i;
				break;
			}
		}
		if (keyPos == -1)
		{
			std::cout << "表头中不存在字段： " << para[1] << std::endl;
			return;
		}
		for (int i = 0; i < m_KeyWordNum; i++)
		{
			if (m_Table[i][0] == para[3])
			{
				if (m_DataType[i] == "INT")
					Int_Op(i, para[5], para[4]);
				else
					Str_Op(i, para[5], para[4]);
				break;
			}
			if (i == m_KeyWordNum - 1)
			{
				std::cout << "表头中不存在字段： " << para[3] << std::endl;
				return;
			}
		}
		for (int j = 0; j < m_Pos.size(); j++)
		{
			if (!isStrLegal(keyPos, 2, para))return;
			m_Table[keyPos][m_Pos[j]] = para[2];
		}
		if (m_Pos.size() > 0)std::cout << "更新数据成功！" << std::endl;
		else std::cout << "未找到满足条件的数据！" << std::endl;
		TableClear();
	}
	else return;
}

void Table::Draw_line(int max)
{
	std::cout << "+-";
	for (int i = 0; i <= max; i++)
		std::cout << "-";
	std::cout << '+' << std::endl;
}
void Table::Draw_line(std::vector<int> max, int columns) {  //画行线
	for (int i = 0; i < columns; i++) {
		std::cout << "+-";
		for (int j = 0; j <= max[i]; j++) {
			std::cout << '-';
		}
	}
	std::cout << '+' << std::endl;
}

void Table::Draw_Datas(int max,std::vector<std::string>table,int row)
{
	Draw_line(max);
	std::cout << "| " << std::setw(max) << std::setiosflags(std::ios::left) << std::setfill(' ') << table[0] << ' ';
	std::cout << "|"<<std::endl;
	Draw_line(max);
	for (int i = 1; i <= row; i++)
	{
		std::cout << "| " << std::setw(max) << std::setiosflags(std::ios::left) << std::setfill(' ') << table[i] << ' ';
		std::cout << "|" << std::endl;
	}
	Draw_line(max);
}

void Table::Draw_Datas(std::vector<int> max, std::vector<std::vector<std::string>> table, int columns, int row) { 
	Draw_line(max, columns);
	for (int i = 0; i < table.size(); i++) {
		std::cout << "| " << std::setw(max[i]) << std::setiosflags(std::ios::left) << std::setfill(' ') << table[i][0] << ' ';
	}
	std::cout << '|' << std::endl;
	Draw_line(max, columns);
	for (int i = 1; i <= row; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << "| " << std::setw(max[j]) << std::setiosflags(std::ios::left) << std::setfill(' ');
			std::cout << table[j][i] << ' ';
		}
		std::cout << '|' << std::endl;
	}
	Draw_line(max, columns);
}

void Table::Select(std::vector<std::string>&para)
{
	if (UseTable(para[1]))
	{
		if (para[0] == "DEFAULT")
		{
			std::vector<int>max;
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				int _max = -INT_MAX;
				for (int j = 0; j <= m_RecordNum; j++)
					_max = _max > int(m_Table[i][j].size()) ? _max : m_Table[i][j].size();
				max.push_back(_max);
			}
			Draw_Datas(max, m_Table, m_KeyWordNum, m_RecordNum );
			max.clear();
			TableClear();
		}
		else if (para[0] == "ASSIGNED")
		{
			int keyPos = -1;
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				if (m_Table[i][0] == para[2])
					keyPos = i;
			}
			if (keyPos == -1)
			{
				std::cout << "表头中不存在字段： " << para[2] << std::endl;
				return;
			}
			for (int i = 0; i < m_KeyWordNum; i++)
			{
				if (m_Table[i][0] == para[3])
				{
					if (m_DataType[i] == "INT")
						Int_Op(i, para[5], para[4]);
					else Str_Op(i, para[5], para[4]);
					break;
				}
				if (i==m_KeyWordNum-1)
				{
					std::cout << "表头中不存在字段： " << para[3] << std::endl;
					return;
				}
			}
			int max = -INT_MAX;
			std::vector<std::string> ans;
			ans.push_back(m_Table[keyPos][0]);
			for (int i = 0; i < m_Pos.size(); i++)
				ans.push_back(m_Table[keyPos][m_Pos[i]]);
			for (int i = 0; i < ans.size(); i++)
				max = max > int(ans[i].size()) ? max : ans[i].size();
			if(ans.size() <= 1) std::cout << "未找到满足条件的数据！" << std::endl;
			Draw_Datas(max, ans, ans.size() - 1);
			ans.clear();								//清空满足条件的数据
			TableClear();
		}
	}
	else return;
}

void Table::TableClear()
{
	m_Pos.clear();								//清空满足条件的序号
	Save();										//保存
	m_Table.clear();							//清空表
	m_DataType.clear();							//清空数据类型
	m_FileProcess.ChangePath();					//更改文件路径
}
void Table::Save()
{
	//写表头
	m_FileProcess.WriteTableHeader(m_KeyWordNum, m_RecordNum, m_Table, m_DataType);
	//写数据
	m_FileProcess.WriteTableRecord(m_KeyWordNum, m_RecordNum, m_Table);
	//写索引
	m_FileProcess.WriteTableIndexes();
}
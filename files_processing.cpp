#include "files_processing.h"

int FilesProcessing::ChangePath(std::string path_name)
{

	if (path_name.empty()) {						//如果不传入参数，则返回上级目录
		char path[_MAX_DIR];
		_getcwd(path, _MAX_DIR);					//获得当前路径
		std::string tempPath = path;
		int temp = tempPath.find_last_of("/\\");
		path_name = tempPath.substr(0, temp);		//将上级目录赋给path_name
	}
	if (-1 == _chdir(path_name.c_str()))			//传入参数，查找该目录
	{
		std::cout << "不存在该目录" << std::endl;	//未找到该目录输出提示

		return 0;
	}
	return 1;
}

void FilesProcessing::CreateFolder(std::string dir_name)
{
	_mkdir(dir_name.c_str());
}

void FilesProcessing::DeleteFolder(std::string dir_name)
{
	_rmdir(dir_name.c_str());
}

void FilesProcessing::ShowAllFiles() 
{
	char path[_MAX_DIR];
	_getcwd(path, _MAX_DIR);
	strcat(path, "\\*");
	long handle;				   //用于查找的句柄
	std::vector<std::string>files; //保存文件名
	struct _finddata_t fileinfo;
	handle = _findfirst(path, &fileinfo);
	if (-1 == handle)
		std::cout << "不存在查找的目录" << std::endl;
	files.push_back(fileinfo.name);
	while (!_findnext(handle, &fileinfo)) 
	{
		files.push_back(fileinfo.name);
	}
	_findclose(handle);			//关闭句柄
	if (files.size() <= 2)
		std::cout << "不存在文件" << std::endl;
	else {
		std::cout << "存在以下文件:" << std::endl;
		for (int i = 2; i < files.size(); i++)
			std::cout << files[i] << std::endl;
	}
}

void FilesProcessing::WriteTxt(std::string name, std::vector<std::string>& record)
{
	std::ofstream wtxt;
	wtxt.open(name, std::ios::app);
	if (!wtxt.is_open())
		std::cout << "写入文件出错！" << std::endl;
	int len = record.size();
	for (int i = 0; i < len; i++)
		wtxt << record[i] << std::endl;
	wtxt.close();
}

void FilesProcessing::ReadTxt(std::string name, std::vector<std::string>& record) 
{
	std::ifstream rtxt(name, std::ios::in);
	if (!rtxt.is_open())
		std::cout << "读取文件出错！" << std::endl;
	std::string temp;
	while (getline(rtxt, temp))
		record.push_back(temp);
	rtxt.close();
}

void FilesProcessing::WriteTableHeader(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<std::string>& datatype)
{
	std::ofstream header("表头.txt", std::ios::out);
	if (!header.is_open())
		std::cout << "表头文件写入出错！" << std::endl;
	else {
		header << keywordnum << " " << recordnum << std::endl;
		for (int i = 0; i < keywordnum; i++)
			header << table[i][0] << " " << datatype[i] << std::endl;
		header.close();
	}
}

void FilesProcessing::WriteTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table)
{
	std::ofstream record("数据.txt", std::ios::out);
	if (!record.is_open())
		std::cout << "数据文件写入出错！" << std::endl;
	else {
		for (int i = 1; i <= recordnum; i++)
		{
			for (int j = 0; j < keywordnum - 1; j++)
				record << table[j][i] << " ";
			record << table[keywordnum - 1][i] << std::endl;
		}
		record.close();
	}
}

void FilesProcessing::WriteTableIndexes()
{

}

void FilesProcessing::ReadTableHeader(int& keywordnum, int& recordnum, std::vector<std::vector<std::string>>&table, std::vector<std::string>&datatype)
{
	std::ifstream header("表头.txt", std::ios::in);
	if (!header.is_open())
		std::cout << "表头文件读取出错！" << std::endl;
	else 
	{
		char str[300];
		header >> keywordnum >> recordnum;	
		table.resize(keywordnum);
		header.getline(str, 300);//吞掉换行符
		for (int i = 0; i < keywordnum; i++)
		{
			header.getline(str, 300);
			char* temp;
			temp = strtok(str, " ");
			table[i].push_back(temp);
			temp = strtok(NULL, " ");
			datatype.push_back(temp);
		}
	}
}

void FilesProcessing::ReadTableRecord(int keywordnum, int recordnum, std::vector<std::vector<std::string>>& table, std::vector<int>& poslist)
{
	std::ifstream record("数据.txt", std::ios::in);
	if (!record.is_open())
		std::cout << "数据文件读取出错！" << std::endl;
	else {
		char str[2560];
		poslist.push_back(0);
		for (int i = 1; i <= recordnum; i++)
		{
			poslist.push_back(i);
			record.getline(str, 2560);
			char* temp;
			temp = strtok(str, " ");
			for (int j = 0; j < keywordnum; j++)
			{
				table[j].push_back(temp);
				temp = strtok(NULL, " ");
			}
		}
	}
}

void FilesProcessing::ReadTableIndexes()
{

}

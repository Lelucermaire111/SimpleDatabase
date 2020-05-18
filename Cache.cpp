#include"Cache.h"
int ExpireTime = 300;
int Cache::QueryMyCache(std::string name, TableInfo& t)
{
	auto cache_iter = MyCache.find(name);
	if (cache_iter != MyCache.end())
	{
		const TableInfo& T = cache_iter->second;
		//�жϻ����Ƿ����
		if ((time(NULL) - T.m_CreateTime) < ExpireTime)
		{
			t = T;
			return 1;
		}
	}
	t.m_CreateTime = time(NULL);
	return 0;
}

//������ڵĻ���
void Cache::Refresh()
{
	for (auto it = MyCache.begin(); it != MyCache.end();)
	{
		if (time(NULL) - it->second.m_CreateTime > ExpireTime)
		{
			MyCache.erase(it++);
		}
		else
			it++;
	}
}
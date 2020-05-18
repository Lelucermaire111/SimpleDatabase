#include"Cache.h"
int ExpireTime = 300;
int Cache::QueryMyCache(std::string name, TableInfo& t)
{
	auto cache_iter = MyCache.find(name);
	if (cache_iter != MyCache.end())
	{
		const TableInfo& T = cache_iter->second;
		//判断缓存是否过期
		if ((time(NULL) - T.m_CreateTime) < ExpireTime)
		{
			t = T;
			return 1;
		}
	}
	t.m_CreateTime = time(NULL);
	return 0;
}

//清除过期的缓存
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
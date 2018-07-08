#pragma once
#include "Admin.h"
#include <map>
#include <fstream>
using namespace std;
class AdminMap
{
	friend class AdminHelper;
	friend class RootHelper;
	AdminMap() {}
	bool Add(const Admin& admin);
	bool Delete(const ID id);
	bool Find(const ID id, Admin& result)const;
	bool Find(const char* name, Admin& result)const;
	static AdminMap ReadMap(const char* path);
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteMap(const char* path)const;
	map<ID, Admin> adminMap;
};


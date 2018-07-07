#pragma once
#include "Admin.h"
#include <map>
#include <fstream>
using namespace std;
class AdminMap
{
public:
	AdminMap() {}
	bool Add(const Admin& admin);
	static AdminMap ReadMap(const char* path);
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteMap(const char* path)const;
private:
	map<ID, Admin> adminMap;
};


#pragma once
#include <map>
#include <fstream>
#include <cstring>
#include "User.h"
class UserMap
{
	friend class UserHelper;
	friend class AdminHelper;
	UserMap() {}
	bool Add(const User& user);
	bool Delete(ID id);
	bool Find(ID id, User& result)const;
	bool Find(const char* name, User& result)const;
	static UserMap ReadMap(const char* path);
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteMap(const char* path)const;
	//DEBUG用函数,发布时删除
	//void Print();
	map<ID, User> userMap;
};


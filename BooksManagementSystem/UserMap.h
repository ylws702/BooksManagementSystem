#pragma once
#include <map>
#include <fstream>
#include "User.h"
class UserMap
{
public:
	UserMap() {}
	bool Add(const User& user);
	bool Delete(ID id);
	bool Find(ID id, User& result)const;
	static UserMap ReadMap(const char* path);
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteMap(const char* path)const;
	//DEBUG用函数,发布时删除
	void Print();
private:
	map<ID, User> userMap;
};


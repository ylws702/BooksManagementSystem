#pragma once
#include <fstream>
using namespace std;
typedef long long unsigned ID;
class Root
{
	friend class RootHelper;
	Root();
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	char name[16];
	char password[32];
	static Root ReadRoot(const char* path);
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteRoot(const char* path)const;
};


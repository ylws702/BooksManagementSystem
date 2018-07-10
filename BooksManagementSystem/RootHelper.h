#pragma once
#include "AdminMap.h"
#include "Root.h"
#include <cstring>
class RootHelper
{
public:
	RootHelper() {}
	bool Login(const char* password);
	bool Logout();
	//************************************
	// 函数名 : TestPassword
	// 功  能 : 测试密码
	// 返回值 : bool : 是否成功
	// 参  数 : const char * password : 测试的密码
	//************************************
	bool TestPassword(const char* password);
	//************************************
	// 函数名 : ChangePassword
	// 功  能 : 修改密码
	// 返回值 : bool : 是否成功
	// 参  数 : const char * oldpw : 原密码
	// 参  数 : const char * newpw : 新密码
	//************************************
	bool ChangePassword(const char* oldpw, const char* newpw);
	//************************************
	// 函数名 : AddAdmin
	// 功  能 : 添加图书管理员
	// 返回值 : ID : 生成的图书管理员编号
	// 参  数 : const char * name : 图书管理员用户名
	// 参  数 : const char * password : 图书管理员密码
	//************************************
	ID AddAdmin(const char * name, const char * password);
	//************************************
	// 函数名 : RemoveAdmin
	// 功  能 : 移除图书管理员
	// 返回值 : bool : 是否成功
	// 参  数 : const ID id : 图书管理员编号
	//************************************
	bool RemoveAdmin(const ID id);
	const char * GetAdminName(const ID id);
	//************************************
	// 函数名 : Save
	// 功  能 : 保存至文件
	// 返回值 : bool : 是否成功
	//************************************
	bool Save()const;
private:
	const char*adminMapPath{ "admin" };
	const char*rootPath{ "root" };
	Root root{ Root::ReadRoot(rootPath) };
	AdminMap adminMap{ AdminMap::ReadMap(adminMapPath) };
	bool Loggedin{ false };
};


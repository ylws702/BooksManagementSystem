#pragma once
typedef long long unsigned ID;
class Admin
{
	//友元类:图书管理员映射
	friend class AdminMap;
	//友元类:图书管理员助手
	friend class AdminHelper;
	//友元类:系统管理员助手
	friend class RootHelper;
public:
	//删除默认构造函数
	Admin() = delete;
	//************************************
	// 函数名 : Admin
	// 功  能 : 使用编号构造图书管理员
	// 参  数 : const ID id : 图书管理员编号
	//************************************
	Admin(const ID id);
	//************************************
	// 函数名 : Admin
	// 功  能 : 使用全部信息构造图书管理员
	// 参  数 : const ID id : 图书管理员编号
	// 参  数 : const char * name : 
	// 参  数 : const char * password : 
	//************************************
	Admin(const ID id, const char *name, const char *password);
private:
	//************************************
	// 函数名 : SetName
	// 功  能 : 设置图书管理员用户名
	// 返回值 : bool : 是否成功,失败可能是用户名过长
	// 参  数 : const char * name : 设置的用户名
	//************************************
	bool SetName(const char *name);
	//************************************
	// 函数名 : SetPassword
	// 功  能 : 设置图书管理员密码
	// 返回值 : bool : 是否成功,失败可能是密码过长
	// 参  数 : const char * password : 设置的密码
	//************************************
	bool SetPassword(const char *password);
	//图书管理员编号,默认为0
	ID id{ 0 };
	//图书管理员用户名
	char name[16];
	//图书管理员密码
	char password[32];
};

#pragma once
#include <list>
#include "Date.h"
using namespace std;
typedef long long unsigned ID;
class User
{
	friend class UserMap;
	friend class UserHelper;
	friend class AdminHelper;
public:
	enum UserType
	{
		unknownType,
		undergraduate,
		postgraduate,
		professoriat
	};
	enum Gender
	{
		unknownGender,
		male,
		female
	};
	User() = delete;
	User(const ID id);
	User(const ID id,
		const char * name,
		const char * password,
		const Gender gender,
		const UserType type);
	User(const User& user);
	User operator=(const User& user);
private:
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	void SetBalance(const double balance);
	bool Borrow(const ID bookID);
	bool Return(const ID bookID);
	ID id{ 0 };
	//更改name长度需要同时修改SetName函数
	//更改成员还需同时修改UserMap::ReadMap和UserMap::WriteMap以及构造函数和赋值重载
	char name[16];
	Gender gender{ unknownGender };
	char password[32];
	UserType type{ unknownType };
	//挂失用
	bool isEnabled{ true };
	list<pair<ID, Date>> borrowList;
	double balance{ 0 };
	const uint borrowdays{ 30 };
	const uint maxBooks{ 30 };
};

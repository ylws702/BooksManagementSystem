#pragma once
#include <list>
#include "Date.h"
using namespace std;
typedef long long unsigned ID;
class User
{
	friend class UserMap;
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
	User(ID id);
	User(ID id, const char *name, const char *password);
	User(const User& user);
	~User();
	User operator=(const User& user);
	bool SetName(const char *name);
	void SetGender(Gender gender);
	bool SetPassword(const char *password);
	void SetType(UserType type);
	bool Borrow(ID bookID);
	bool Return(ID bookID);
private:
	ID id{ 0 };
	//更改name长度需要同时修改SetName函数
	char name[16];
	Gender gender{ unknownGender };
	char password[32];
	UserType type{ unknownType };
	//挂失用
	bool isEnabled{ true };
	list<pair<ID, Date>> borrowList;
	const uint borrowdays{ 30 };
	const uint maxBooks{ 30 };
};

#pragma once
#include "UserMap.h"
class UserHelper
{
public:
	UserHelper() {}
	bool Login(const char * name, const char* password);
	bool TestPassword(const char* password);
	bool ChangePassword(const char* oldpw, const char* newpw);
	bool GetBorrow(list<pair<ID, Date>>& result) const;
private:
	const char*userMapPath{ "user" };
	const char*logPath{ "log.txt" };
	User user{ User(0) };
	UserMap userMap{ UserMap::ReadMap(userMapPath) };
	bool Loggedin{ false };
};


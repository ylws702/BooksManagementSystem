#pragma once
#include "UserMap.h"
class UserHelper
{
public:
	UserHelper() = delete;
	UserHelper(const char* path);
	bool Login(const char * name, const char* password);
	bool ChangePassword(const char* oldpw, const char* newpw);
private:
	const char*mapPath;
	const char*logPath{ "log.txt" };
	User user;
	UserMap userMap;
	bool Loggedin{ false };
};


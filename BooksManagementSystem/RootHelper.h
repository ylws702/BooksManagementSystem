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
	bool TestPassword(const char* password);
	bool ChangePassword(const char* oldpw, const char* newpw);
private:
	const char*adminMapPath{ "admin" };
	const char*rootPath{ "root" };
	Root root{ Root::ReadRoot(rootPath) };
	AdminMap adminMap{ AdminMap::ReadMap(adminMapPath) };
	bool Loggedin{ false };
};


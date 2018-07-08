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
	ID AddAdmin(const char * name, const char * password);
	bool RemoveAdmin(const ID id);
	const char * GetAdminName(const ID id);
	bool Save()const;
private:
	const char*adminMapPath{ "admin" };
	const char*rootPath{ "root" };
	Root root{ Root::ReadRoot(rootPath) };
	AdminMap adminMap{ AdminMap::ReadMap(adminMapPath) };
	bool Loggedin{ false };
};


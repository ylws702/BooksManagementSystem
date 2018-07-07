#include "stdafx.h"
#include "UserHelper.h"


UserHelper::UserHelper(const char* p) :
	user(User(0))
{
	mapPath = p;
	userMap = UserMap::ReadMap(mapPath);
}

bool UserHelper::Login(const char * name, const char * password)
{
	if (!userMap.Find(name, user))
	{
		return Loggedin = false;
	}
	return Loggedin = strcmp(user.password, password) == 0;
}

bool UserHelper::ChangePassword(const char * oldpw, const char * newpw)
{
	if (strcmp(oldpw, user.password) != 0)
	{
		return false;
	}
	userMap.userMap.find(user.id)->second.SetPassword(newpw);
	userMap.WriteMap(mapPath);
	//TODO:LOG
}


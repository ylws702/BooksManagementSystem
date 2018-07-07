#include "stdafx.h"
#include "UserHelper.h"


bool UserHelper::Login(const char * name, const char * password)
{
	if (!userMap.Find(name, user))
	{
		return Loggedin = false;
	}
	return Loggedin = strcmp(user.password, password) == 0;
}

bool UserHelper::TestPassword(const char * password)
{
	if (!Loggedin)
	{
		return false;
	}
	return strcmp(password, user.password);
}

bool UserHelper::ChangePassword(const char * oldpw, const char * newpw)
{
	if (strcmp(oldpw, user.password) != 0)
	{
		return false;
	}
	if (!userMap.userMap.find(user.id)->second.SetPassword(newpw))
	{
		return false;
	}
	if (!userMap.WriteMap(userMapPath))
	{
		return false;
	}
	//TODO:LOG
	return true;
}

bool UserHelper::GetBorrow(list<pair<ID, Date>>& result) const
{
	if (!Loggedin)
	{
		return false;
	}
	result = user.borrowList;
	return true;
}


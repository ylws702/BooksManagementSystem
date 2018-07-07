#include "stdafx.h"
#include "RootHelper.h"

bool RootHelper::Login(const char * password)
{
	return Loggedin = strcmp(root.password, password) == 0;
}

bool RootHelper::Logout()
{
	return !(Loggedin = false);
}

bool RootHelper::TestPassword(const char * password)
{
	if (!Loggedin)
	{
		return false;
	}
	return strcmp(password, root.password) == 0;
}

bool RootHelper::ChangePassword(const char * oldpw, const char * newpw)
{
	if (strcmp(oldpw, root.password) != 0)
	{
		return false;
	}
	if (!root.SetPassword(newpw))
	{
		return false;
	}
	if (!root.WriteRoot(rootPath))
	{
		return false;
	}
	//TODO:LOG
	return true;
}

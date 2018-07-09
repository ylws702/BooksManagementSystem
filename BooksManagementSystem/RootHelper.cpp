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
//失败返回0
//成功返回ID
ID RootHelper::AddAdmin(const char * name, const char * password)
{
	if (!Loggedin)
	{
		return 0;
	}
	ID id = 1;
	for (auto p : adminMap.adminMap)
	{
		if (p.first>=id)
		{
			id = p.first + 1;
		}
	}
	if (!adminMap.Add(Admin(id, name, password)))
	{
		return 0;
	}
	return id;
}

bool RootHelper::RemoveAdmin(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!adminMap.Delete(id))
	{
		return false;
	}
	return true;
}

const char * RootHelper::GetAdminName(const ID id)
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (adminMap.adminMap.find(id)== adminMap.adminMap.end())
	{
		return nullptr;
	}
	return adminMap.adminMap.find(id)->second.name;
}

bool RootHelper::Save() const
{
	if (!Loggedin)
	{
		return false;
	}
	if (!adminMap.WriteMap(adminMapPath))
	{
		return false;
	}
	if (!root.WriteRoot(rootPath))
	{
		return false;
	}
	return true;
}

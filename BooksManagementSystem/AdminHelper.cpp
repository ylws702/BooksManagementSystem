#include "stdafx.h"
#include "AdminHelper.h"


bool AdminHelper::Login(const char * name, const char * password)
{
	if (!adminMap.Find(name, admin))
	{
		return Loggedin = false;
	}
	return Loggedin = strcmp(admin.password, password) == 0;
}

bool AdminHelper::Logout() 
{
	return !(Loggedin = false);
}

bool AdminHelper::TestPassword(const char * password)
{
	if (!Loggedin)
	{
		return false;
	}
	return strcmp(password,admin.password)==0;
}

bool AdminHelper::ChangePassword(const char * oldpw, const char * newpw)
{
	if (strcmp(oldpw, admin.password) != 0)
	{
		return false;
	}
	if (!adminMap.adminMap.find(admin.id)->second.SetPassword(newpw))
	{
		return false;
	}
	if (!adminMap.WriteMap(adminMapPath))
	{
		return false;
	}
	//TODO:LOG
	return true;
}

bool AdminHelper::AddUser(const ID id,
	const char * name,
	const char * password, 
	const User::Gender gender,
	const User::UserType type)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!userMap.Add(User(id, name, password, gender, type)))
	{
		return false;
	}
	return true;
}

bool AdminHelper::RemoveUser(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (userMap.Delete(id))
	{
		return false;
	}
	return true;
}

bool AdminHelper::ReportLoss(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	userMap.userMap.find(id)->second.isEnabled = false;
	return true;
}

bool AdminHelper::Accept(const ID userID, const ID bookID)
{
	if (!Loggedin)
	{
		return false;
	}
	userMap.userMap.find(userID)->second.Return(bookID);
	return true;
}

bool AdminHelper::Save() const
{
	if (!Loggedin)
	{
		return false;
	}
	if (!adminMap.WriteMap(adminMapPath))
	{
		return false;
	}
	if (!userMap.WriteMap(userMapPath))
	{
		return false;
	}
	if (!bookMap.WriteMap(bookMapPath))
	{
		return false;
	}
	return true;
}

//list<ID> AdminHelper::OverdueBookList()const
//{
//	list<ID> result;
//	for (auto i = userMap.userMap.begin(); i != userMap.userMap.end(); i++)
//	{
//		for (auto j : i->second.borrowList)
//		{
//			j.second + overdueDays;
//			if (Date::Now() > j.second + overdueDays)
//			{
//				result.emplace_back()
//			}
//		}
//	}
//	// TODO: insert return statement here
//}

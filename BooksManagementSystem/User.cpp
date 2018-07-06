#include "stdafx.h"
#include "User.h"



User::User(ID id):userID(id)
{
	SetName("无信息");
	SetPassword("无信息");
}


User::User(ID id, const char * name, const char * password) :
	userID(id)
{
	SetName(name);
	SetPassword(password);
}

bool User::SetName(const char * str)
{
	int i = 0;
	while (i<16)
	{
		name[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool User::SetPassword(const char * str)
{
	int i = 0;
	while (i<16)
	{
		password[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

User::~User()
{
}

void User::Borrow(ID bookId)
{
	pair<ID, Date> p(bookId, Date::Now() + borrowdays);
	borrowList.push_back(p);
}

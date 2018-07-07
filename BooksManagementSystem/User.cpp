#include "stdafx.h"
#include "User.h"

User::User(ID id) :
	id(id)
{
	SetName("无信息");
	SetPassword("123456");
}

User::User(ID id, const char * name, const char * password) :
	id(id)
{
	SetName(name);
	SetPassword(password);
}

User::User(const User & user) :
	id(user.id),
	gender(user.gender),
	type(user.type),
	isEnabled(user.isEnabled),
	borrowList(user.borrowList),
	balance(user.balance)
{
	SetName(user.name);
	SetPassword(user.password);
}

bool User::SetName(const char * str)
{
	int i = 0;
	while (i < 16)
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

void User::SetGender(const Gender g)
{
	gender = g;
}

bool User::SetPassword(const char * str)
{
	int i = 0;
	while (i < 16)
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

void User::SetType(const UserType t)
{
	type = t;
}

void User::SetBalance(const double b)
{
	balance = b;
}

User User::operator=(const User & user)
{
	if (this== &user)
	{
		return *this;
	}
	id = user.id;
	gender = user.gender;
	type = user.type;
	isEnabled = user.isEnabled;
	borrowList = user.borrowList;
	balance = user.balance;
	SetName(user.name);
	SetPassword(user.password);
	return *this;
}

bool User::Borrow(const ID bookId)
{
	if (!isEnabled)
	{
		return false;
	}
	for (auto pair : borrowList)
	{
		if (pair.first== bookId)
		{
			return false;
		}
	}
	pair<ID, Date> p(bookId, Date::Now() + borrowdays);
	borrowList.push_back(p);
	if (borrowList.size()>maxBooks)
	{
		isEnabled = false;
	}
	return true;
}

bool User::Return(const ID bookID)
{
	for (auto i = borrowList.begin(); i != borrowList.end(); i++)
	{
		if (i->first==bookID)
		{
			borrowList.erase(i);
			return true;
		}
	}
	//没找到
	return false;
}

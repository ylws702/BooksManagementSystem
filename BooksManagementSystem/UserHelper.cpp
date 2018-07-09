#include "stdafx.h"
#include "UserHelper.h"


bool UserHelper::Login(const ID id, const char * password)
{
	auto it = userMap.userMap.find(id);
	if (userMap.userMap.end() == it)
	{
		return Loggedin = false;
	}
	if (!it->second.isEnabled)
	{
		return Loggedin = false;
	}
	if (strcmp(it->second.password, password) != 0)
	{
		return Loggedin = false;
	}
	user = it->second;
	return Loggedin = true;
}

bool UserHelper::TestPassword(const char * password)const
{
	if (!Loggedin)
	{
		return false;
	}
	return strcmp(password, user.password) == 0;
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
	if (!user.SetPassword(newpw))
	{
		return false;
	}
	//TODO:LOG
	return true;
}

const char * UserHelper::GetUserName() const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	return user.name;
}

bool UserHelper::Borrow(const ID bookID)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(bookID);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.exist)
	{
		return false;
	}
	if (!it->second.SetExist(false))
	{
		return false;
	}
	auto itu = userMap.userMap.find(user.id);
	if (userMap.userMap.end() == itu)
	{
		return false;
	}
	pair<ID, Date> p(bookID, Date::Now());
	itu->second.borrowList.push_back(p);
	user.borrowList.push_back(p);
	return true;
}


const char * UserHelper::GetBookTitle(const ID id)const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return nullptr;
	}
	return bookMap.bookMap.find(id)->second.title;
}

const char * UserHelper::GetBookAuthor(const ID id)const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return nullptr;
	}
	return bookMap.bookMap.find(id)->second.author;
}

const char * UserHelper::GetBookPress(const ID id)const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return nullptr;
	}
	return bookMap.bookMap.find(id)->second.press;
}

const char * UserHelper::GetBookDate(const ID id)const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return nullptr;
	}
	return bookMap.bookMap.find(id)->second.date;
}

const char * UserHelper::GetBookType(const ID id)const
{
	if (!Loggedin)
	{
		return nullptr;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return nullptr;
	}
	return bookMap.bookMap.find(id)->second.type;
}

bool UserHelper::GetBookExist(const ID id) const
{
	if (!Loggedin)
	{
		return false;
	}
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return false;
	}
	return bookMap.bookMap.find(id)->second.exist;
}

list<pair<ID, Date>> UserHelper::GetBorrowList()const
{
	if (!Loggedin)
	{
		return list<pair<ID, Date>>();
	}
	return user.borrowList;
}

list<ID> UserHelper::FindBookByTitle(const char * str) const
{
	list<ID> result;
	if (!Loggedin)
	{
		return list<ID>();
	}
	if (nullptr == str || '\0' == *str)
	{
		return list<ID>();
	}
	char const *title;
	int start;
	for (auto p : bookMap.bookMap)
	{
		title = p.second.title;
		start = 0;
		while (start < 32 && title[start] != '\0')
		{
			for (int i = 0; i < 32; i++)
			{
				if ('\0' == str[i])
				{
					result.push_back(p.first);
					start = 32;
					break;
				}
				if ('\0' == title[start + i])
				{
					start = 32;
					break;
				}
				if (title[start + i] != str[i])
				{
					break;
				}
			}
			start++;
		}
	}
	return result;
}

bool UserHelper::Save() const
{
	if (!Loggedin)
	{
		return false;
	}
	if (!bookMap.WriteMap(bookMapPath))
	{
		return false;
	}
	if (!userMap.WriteMap(userMapPath))
	{
		return false;
	}
	return true;
}


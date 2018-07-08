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
	return strcmp(password, admin.password) == 0;
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

bool AdminHelper::AddBook(
	const ID id,
	const char * title,
	const char * author,
	const char * press,
	const char * date,
	const char * type)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!bookMap.Add(Book(id, title, author, press, date, type)))
	{
		return false;
	}
	return true;
}

bool AdminHelper::RemoveBook(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!bookMap.Delete(id))
	{
		return false;
	}
	return true;
}

const char* AdminHelper::GetBookTitle(const ID id)
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

const char * AdminHelper::GetBookAuthor(const ID id)
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

const char * AdminHelper::GetBookPress(const ID id)
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

const char * AdminHelper::GetBookDate(const ID id)
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

const char * AdminHelper::GetBookType(const ID id)
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

bool AdminHelper::SetBookTitle(const ID id, const char* title)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(id);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.SetTitle(title))
	{
		return false;
	}
	return true;
}

bool AdminHelper::SetBookAuthor(const ID id, const char* author)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(id);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.SetAuthor(author))
	{
		return false;
	}
	return true;
}

bool AdminHelper::SetBookPress(const ID id, const char * press)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(id);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.SetPress(press))
	{
		return false;
	}
	return true;
}

bool AdminHelper::SetBookDate(const ID id, const char * date)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(id);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.SetDate(date))
	{
		return false;
	}
	return true;
}

bool AdminHelper::SetBookType(const ID id, const char * type)
{
	if (!Loggedin)
	{
		return false;
	}
	auto it = bookMap.bookMap.find(id);
	if (bookMap.bookMap.end() == it)
	{
		return false;
	}
	if (!it->second.SetType(type))
	{
		return false;
	}
	return true;
}

bool AdminHelper::AddUser(const ID id,
	const char * name,
	const char * password,
	const int gender,
	const int type)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!userMap.Add(User(id, name, password, (User::Gender)gender, (User::UserType)type)))
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
	if (!userMap.Delete(id))
	{
		return false;
	}
	return true;
}

const char * AdminHelper::GetUserName(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (userMap.userMap.find(id) == userMap.userMap.end())
	{
		return nullptr;
	}
	return userMap.userMap.find(id)->second.name;
}

const char * AdminHelper::GetUserGender(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (userMap.userMap.find(id) == userMap.userMap.end())
	{
		return nullptr;
	}
	switch (userMap.userMap.find(id)->second.gender)
	{
	case User::male:
		return "男";
		break;
	case User::female:
		return "女";
		break;
	default:
		return "未知";
		break;
	}
}

const char * AdminHelper::GetUserType(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (userMap.userMap.find(id) == userMap.userMap.end())
	{
		return nullptr;
	}
	switch (userMap.userMap.find(id)->second.type)
	{
	case User::undergraduate:
		return "本科生";
		break;
	case User::postgraduate:
		return "研究生";
		break;
	case User::professoriat:
		return "教师";
		break;
	default:
		return "未知";
		break;
	}
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

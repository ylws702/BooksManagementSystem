#include "stdafx.h"
#include "AdminHelper.h"


bool AdminHelper::Login(const ID id,const char * name, const char * password)
{
	auto it = adminMap.adminMap.find(id);
	if (adminMap.adminMap.end()==it)
	{
		return Loggedin = false;
	}
	if (strcmp(it->second.name, name) != 0)
	{
		return Loggedin = false;
	}
	if (strcmp(it->second.password, password) != 0)
	{
		return Loggedin = false;
	}
	admin = it->second;
	return Loggedin = true;
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
	if (!admin.SetPassword(newpw))
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
	const char * type,
	const int number)
{
	if (!Loggedin)
	{
		return false;
	}
	if (!bookMap.Add(Book(id, title, author, press, date, type,number)))
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
	for (auto p:userMap.userMap)
	{
		for (auto i = p.second.borrowList.begin();i!=p.second.borrowList.end();i++)
		{
			if (i->first==id)
			{
				i = p.second.borrowList.erase(i);
			}
		}
	}
	return true;
}

bool AdminHelper::RemoveAllBooks()
{
	if (!Loggedin)
	{
		return false;
	}
	bookMap.bookMap.clear();
	for (auto p : userMap.userMap)
	{
		p.second.borrowList.clear();
	}
	return true;
}

const char* AdminHelper::GetBookTitle(const ID id)const
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

const char * AdminHelper::GetBookAuthor(const ID id)const
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

const char * AdminHelper::GetBookPress(const ID id)const
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

const char * AdminHelper::GetBookDate(const ID id)const
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

const char * AdminHelper::GetBookType(const ID id)const
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

bool AdminHelper::GetBookExist(const ID id) const
{
	if (!Loggedin)
	{
		return false;
	}
	//查无此书
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return false;
	}
	//书籍余量是否大于0;
	return bookMap.bookMap.find(id)->second.restCount > 0;
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

unsigned int AdminHelper::GetBookRestCount(const ID id) const
{
	if (!Loggedin)
	{
		return 0;
	}
	//查无此书
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return false;
	}
	return bookMap.bookMap.find(id)->second.restCount;
}

unsigned int AdminHelper::GetBookTotalCount(const ID id) const
{
	if (!Loggedin)
	{
		return 0;
	}
	//查无此书
	if (bookMap.bookMap.find(id) == bookMap.bookMap.end())
	{
		return false;
	}
	return bookMap.bookMap.find(id)->second.totalCount;
}

list<ID> AdminHelper::GetAllBooks() const
{
	list<ID> result;
	if (!Loggedin)
	{
		return result;
	}
	for (auto p:bookMap.bookMap)
	{
		result.push_back(p.first);
	}
	return result;
}

list<ID> AdminHelper::GetBorrowedBooks() const
{
	list<ID> result;
	if (!Loggedin)
	{
		return result;
	}
	for (auto p : bookMap.bookMap)
	{
		if (p.second.restCount<p.second.totalCount)
		{
			result.push_back(p.first);
		}
	}
	return result;
}

list<ID> AdminHelper::GetNotBorrowedBooks() const
{
	list<ID> result;
	if (!Loggedin)
	{
		return result;
	}
	for (auto p : bookMap.bookMap)
	{
		if (p.second.restCount == p.second.totalCount)
		{
			result.push_back(p.first);
		}
	}
	return result;
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
		return nullptr;
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
		return nullptr;
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
		return nullptr;
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
	if (userMap.userMap.find(id)== userMap.userMap.end())
	{
		return false;
	}
	userMap.userMap.find(id)->second.isEnabled = true;
	return true;
}

bool AdminHelper::UndoReportLoss(const ID id)
{
	if (!Loggedin)
	{
		return false;
	}
	if (userMap.userMap.find(id) == userMap.userMap.end())
	{
		return false;
	}
	userMap.userMap.find(id)->second.isEnabled = true;
	return true;
}

bool AdminHelper::Accept(const ID userID, const ID bookID)
{
	if (!Loggedin)
	{
		return false;
	}
	auto u = userMap.userMap.find(userID);
	if (userMap.userMap.end()==u)
	{
		return false;
	}
	if (!u->second.Return(bookID))
	{
		return false;
	}
	auto b = bookMap.bookMap.find(bookID);
	if (bookMap.bookMap.end()==b)
	{
		return false;
	}
	if (!b->second.Increase())
	{
		return false;
	}
	//bookMap.bookMap.find(bookID)->second.exist=true;
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

list<ID> AdminHelper::FindBookByTitle(const char* str) const
{
	list<ID> result;
	if (!Loggedin)
	{
		return list<ID>();
	}
	if (nullptr==str||'\0'==*str)
	{
		return list<ID>();
	}
	char const *title;
	int start;
	for (auto p : bookMap.bookMap)
	{
		title = p.second.title;
		start = 0;
		while (start<32&&title[start]!='\0')
		{
			for (int i = 0; i < 32; i++)
			{
				if ('\0' == str[i])
				{
					result.push_back(p.first);
					start = 32;
					break;
				}
				if ('\0'==title[start + i])
				{
					start = 32;
					break;
				}
				if (title[start+i]!=str[i])
				{
					break;
				}
			}
			start++;
		}
	}
	return result;
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

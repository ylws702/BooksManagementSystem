#pragma once
#include "UserMap.h"
#include "BookMap.h"
#include <cstring>
class UserHelper
{
public:
	UserHelper() {}
	bool Login(const ID id, const char* password);
	bool TestPassword(const char* password)const;
	bool ChangePassword(const char* oldpw, const char* newpw);
	const char* GetUserName()const;
	bool Borrow(const ID bookID);
	const char* GetBookTitle(const ID id)const;
	const char* GetBookAuthor(const ID id)const;
	const char* GetBookPress(const ID id)const;
	const char* GetBookDate(const ID id)const;
	//获取书籍类型
	const char* GetBookType(const ID id)const;
	//查找馆内是否有该书
	//不存在或余量不足均返回false
	bool GetBookExist(const ID id)const;
	unsigned int GetBookRestCount(const ID id)const;
	unsigned int GetBookTotalCount(const ID id)const;
	list<pair<ID, Date>> GetBorrowList()const;
	list<ID> FindBookByTitle(const char* title)const;
	list<ID> GetAllBooks()const;
	list<ID> GetBorrowedBooks()const;
	list<ID> GetNotBorrowedBooks()const;
	bool Save()const;
private:
	const char*userMapPath{ "user" };
	const char*bookMapPath{ "book" };
	//const char*userLogPath{ "user.log" };
	User user{ User(0) };
	UserMap userMap{ UserMap::ReadMap(userMapPath) };
	BookMap bookMap{ BookMap::ReadMap(bookMapPath) };
	bool Loggedin{ false };
};


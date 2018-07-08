#pragma once
#include "AdminMap.h"
#include "UserMap.h"
#include "BookMap.h"
#include <cstring>
class AdminHelper
{
public:
	AdminHelper() {}
	bool Login(const char * name, const char* password);
	bool Logout();
	bool TestPassword(const char* password);
	bool ChangePassword(const char* oldpw, const char* newpw);
	bool AddBook(const ID id, 
		const char* title,
		const char* author,
		const char* press,
		const char* date,
		const char* type);
	bool RemoveBook(const ID id);
	const char* GetBookTitle(const ID id);
	const char* GetBookAuthor(const ID id);
	const char* GetBookPress(const ID id);
	const char* GetBookDate(const ID id);
	const char* GetBookType(const ID id);
	bool SetBookTitle(const ID id,const char* title);
	bool SetBookAuthor(const ID id, const char* author);
	bool SetBookPress(const ID id, const char* press);
	bool SetBookDate(const ID id, const char* date);
	bool SetBookType(const ID id, const char* type);
	bool AddUser(const ID id,
		const char * name,
		const char * password,
		const int gender,
		const int type);
	bool RemoveUser(const ID id);
	const char* GetUserName(const ID id);
	const char* GetUserGender(const ID id);
	const char* GetUserType(const ID id);
	bool ReportLoss(const ID id);
	bool Accept(const ID userID, const ID bookID);
	bool Save()const;
	//list<ID> OverdueBookList()const;
private:
	const char*adminMapPath{ "admin" };
	const char*userMapPath{ "user" };
	const char*bookMapPath{ "book" };
	const char*logPath{ "log.txt" };
	const unsigned int overdueDays{ 90 };
	bool Loggedin{ false };
	AdminMap adminMap{ AdminMap::ReadMap(adminMapPath) };
	Admin admin{ Admin(0) };
	UserMap userMap{ UserMap::ReadMap(userMapPath) };
	BookMap bookMap{ BookMap::ReadMap(bookMapPath) };
};


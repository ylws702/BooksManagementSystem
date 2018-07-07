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
	bool AddUser(const ID id,
		const char * name,
		const char * password,
		const User::Gender gender,
		const User::UserType type);
	bool RemoveUser(const ID id);
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


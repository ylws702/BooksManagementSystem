#pragma once
#include "UserMap.h"
#include "BookMap.h"
#include <cstring>
class UserHelper
{
public:
	UserHelper() {}
	bool Login(const char * name, const char* password);
	bool TestPassword(const char* password);
	bool ChangePassword(const char* oldpw, const char* newpw);
	bool GetBorrow(list<pair<ID, Date>>& result) const;
	const char* GetBookTitle(const ID id);
	const char* GetBookAuthor(const ID id);
	const char* GetBookPress(const ID id);
	const char* GetBookDate(const ID id);
	const char* GetBookType(const ID id);
private:
	const char*userMapPath{ "user" };
	const char*bookMapPath{ "book" };
	const char*logPath{ "log.txt" };
	User user{ User(0) };
	UserMap userMap{ UserMap::ReadMap(userMapPath) };
	BookMap bookMap{ BookMap::ReadMap(bookMapPath) };
	bool Loggedin{ false };
};


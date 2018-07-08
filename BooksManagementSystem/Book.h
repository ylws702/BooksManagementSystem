#pragma once
#include <cstdlib>
typedef long long unsigned ID;
class Book
{
	friend class BookMap;
	friend class AdminHelper;
public:
	Book() = delete;
	Book(ID id);
private:
	Book(const ID id,
		const char* title,
		const char* author,
		const char* press,
		const char* date,
		const char* type);
	bool SetTitle(const char* title);
	bool SetAuthor(const char* author);
	bool SetPress(const char* press);
	bool SetDate(const char* date);
	bool SetType(const char* type);
	bool SetExist(bool exist);
	ID id{ 0 };
	char title[32];
	char author[32];
	char press[32];
	char date[32];
	char type[32];
	bool exist;
};


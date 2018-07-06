#pragma once
#include <cstdlib>
class Book
{
	friend class BookList;
public:
	Book()=delete;
	Book(size_t id);
	bool SetTitle(const char* title);
	bool SetAuthor(const char* author);
	bool SetPress(const char* press);
	bool SetDate(const char* date);
	bool SetType(const char* type);
	bool SetExist(bool exist);
	~Book();
private:
	size_t id;
	char title[32];
	char author[32];
	char press[32];
	char date[32];
	char type[32];
	bool exist;
};


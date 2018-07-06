#pragma once
class BookInfo
{
	friend class BookList;
public:
	BookInfo();
	BookInfo(size_t id);
	bool SetTitle(const char* title);
	bool SetAuthor(const char* author);
	~BookInfo();
private:
	size_t id;
	char title[32];
	char author[16];
};


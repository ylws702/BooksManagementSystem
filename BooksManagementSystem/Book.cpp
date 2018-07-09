#include "stdafx.h"
#include "Book.h"


Book::Book(ID id):
	id(id),exist(true),totalCount(1),restCount(1)
{
	SetAuthor("无信息");
	SetDate("无信息");
	SetPress("无信息");
	SetTitle("无信息");
	SetType("无信息");
}


Book::Book(
	const ID id,
	const char * title,
	const char * author, 
	const char * press,
	const char * date,
	const char * type,
	const int number):
	id(id),exist(true),totalCount(number),restCount(number)
{
	SetTitle(title);
	SetAuthor(author);
	SetPress(press);
	SetDate(date);
	SetType(type);
}

bool Book::SetTitle(const char * str)
{
	int i = 0;
	while (i<32)
	{
		title[i] = str[i];
		if ('\0'== str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Book::SetAuthor(const char * str)
{
	int i = 0;
	while (i<32)
	{
		author[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Book::SetPress(const char * str)
{
	int i = 0;
	while (i<32)
	{
		press[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Book::SetDate(const char * str)
{
	int i = 0;
	while (i<32)
	{
		date[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Book::SetType(const char * str)
{
	int i = 0;
	while (i<32)
	{
		type[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Book::SetTotalCount(const unsigned int count)
{
	totalCount = count;
	return true;
}

bool Book::SetRestCount(const unsigned int count)
{
	restCount = count;
	return true;
}

bool Book::Increase()
{
	restCount++;
	return true;
}

bool Book::Decrease()
{
	if (restCount<=0)
	{
		return false;
	}
	restCount--;
	return true;
}

bool Book::SetExist(bool exist)
{
	Book::exist = exist;
	return true;
}

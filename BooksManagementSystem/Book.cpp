#include "stdafx.h"
#include "Book.h"


Book::Book(ID id):
	id(id),exist(true)
{
	SetAuthor("����Ϣ");
	SetDate("����Ϣ");
	SetPress("����Ϣ");
	SetTitle("����Ϣ");
	SetType("����Ϣ");
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

bool Book::SetExist(bool exist)
{
	Book::exist = exist;
	return true;
}

Book::~Book()
{
}

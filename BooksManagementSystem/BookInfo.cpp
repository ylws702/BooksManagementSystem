#include "stdafx.h"
#include "BookInfo.h"


BookInfo::BookInfo()
{
}

BookInfo::BookInfo(size_t id):
	id(id)
{
}


bool BookInfo::SetTitle(const char * str)
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

bool BookInfo::SetAuthor(const char * str)
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

BookInfo::~BookInfo()
{
}

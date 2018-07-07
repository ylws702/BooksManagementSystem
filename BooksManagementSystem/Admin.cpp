#include "stdafx.h"
#include "Admin.h"

Admin::Admin(ID id):id(id)
{
	SetName("Œﬁ–≈œ¢");
	SetPassword("123456");
}

bool Admin::SetName(const char * str)
{
	int i = 0;
	while (i < 16)
	{
		name[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

bool Admin::SetPassword(const char * str)
{
	int i = 0;
	while (i < 32)
	{
		password[i] = str[i];
		if ('\0' == str[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

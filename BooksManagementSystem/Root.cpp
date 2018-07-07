#include "stdafx.h"
#include "Root.h"

Root::Root()
{
	SetName("000000");
	SetPassword("123456");
}

bool Root::SetName(const char * str)
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

bool Root::SetPassword(const char * str)
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

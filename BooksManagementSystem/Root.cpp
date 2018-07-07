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

Root Root::ReadRoot(const char * path)
{
	Root root;
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return root;
	}
	ifs.read((char*)&root, sizeof(root));
	ifs.close();
	return root;
}

bool Root::WriteRoot(const char * path) const
{
	ofstream ofs(path, ios::out | ios::binary);
	if (ofs.fail())
	{
		return false;
	}
	ofs.write((const char*)this, sizeof(Root));
	ofs.close();
	return true;
}

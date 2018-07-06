#include "stdafx.h"
#include "UserMap.h"


UserMap::UserMap()
{
}


UserMap::~UserMap()
{
}

bool UserMap::Add(const User & user)
{
	//用户已存在
	if (userMap.find(user.id) != userMap.end())
	{
		return false;
	}
	pair<size_t, User>p(user.id, user);
	userMap.insert(p);
	return true;
}

bool UserMap::Delete(ID id)
{
	if (userMap.find(id) == userMap.end())
	{
		return false;
	}
	userMap.erase(id);
	return true;
}

UserMap UserMap::ReadMap(const char * path)
{
	UserMap map;
	User current(0);
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return map;
	}
	while (!ifs.read((char*)&current, sizeof(User)).eof())
	{
		map.Add(current);
	}
	ifs.close();
	return map;
}

bool UserMap::WriteMap(const char * path) const
{
	ofstream ofs(path, ios::out | ios::binary);
	if (ofs.fail())
	{
		return false;
	}
	for (auto pair : userMap)
	{
		ofs.write((char*)&pair.second, sizeof(User));
	}
	ofs.close();
	return true;
}

#include<iostream>
#include<iomanip>
using namespace std;
void UserMap::Print()
{
	for (auto pair : userMap)
	{
		std::cout << setw(16) << pair.second.id
			<< setw(16) << pair.second.name
			<< setw(16) << pair.second.gender
			<< setw(16) << pair.second.isEnabled
			<< endl;
	}
}

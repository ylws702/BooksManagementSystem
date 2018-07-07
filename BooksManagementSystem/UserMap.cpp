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
	pair<ID, User>p(user.id, user);
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
	size_t n;
	pair<ID, Date>p;
	while (!ifs.read((char*)&current.id, sizeof(ID)).eof())
	{
		ifs.read(current.name, 16);
		ifs.read((char*)&current.gender, sizeof(User::Gender));
		ifs.read(current.password, 32);
		ifs.read((char*)&current.type, sizeof(User::type));
		ifs.read((char*)&current.isEnabled, sizeof(bool));
		ifs.read((char*)&n, sizeof(size_t));
		for (size_t i = 0; i < n; i++)
		{
			ifs.read((char*)&p, sizeof(pair<ID, Date>));
			current.borrowList.push_back(p);
		}
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
	size_t n;
	for (auto usrp : userMap)
	{
		ofs.write((char*)&usrp.second.id, sizeof(ID));
		ofs.write(usrp.second.name, 16);
		ofs.write((char*)&usrp.second.gender, sizeof(User::Gender));
		ofs.write(usrp.second.password, 32);
		ofs.write((char*)&usrp.second.type, sizeof(User::type));
		ofs.write((char*)&usrp.second.isEnabled, sizeof(bool));
		n = usrp.second.borrowList.size();
		ofs.write((char*)&n, sizeof(size_t));
		for (auto p : usrp.second.borrowList)
		{
			//ofs.write((char*)&p.first, sizeof(ID));
			//ofs.write((char*)&p.second, sizeof(Date));
			ofs.write((char*)&p, sizeof(pair<ID, Date>));
		}
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

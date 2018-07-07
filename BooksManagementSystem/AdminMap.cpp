#include "stdafx.h"
#include "AdminMap.h"

bool AdminMap::Add(const Admin & admin)
{
	//已在列表中
	if (adminMap.find(admin.id) != adminMap.end())
	{
		return false;
	}
	pair<ID, Admin>p(admin.id, admin);
	adminMap.insert(p);
	return true;
}

bool AdminMap::Find(ID id, Admin & result) const
{
	auto it = adminMap.find(id);
	if (it == adminMap.end())
	{
		return false;
	}
	result = it->second;
	return true;
}

bool AdminMap::Find(const char * name, Admin & result) const
{
	for (auto i = adminMap.begin(); i != adminMap.end(); i++)
	{
		if (0 == strcmp(i->second.name, name))
		{
			result = i->second;
			return true;
		}
	}
	return false;
}


AdminMap AdminMap::ReadMap(const char * path)
{
	AdminMap map;
	Admin current(0);
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return map;
	}
	while (!ifs.read((char*)&current, sizeof(Admin)).eof())
	{
		map.Add(current);
	}
	ifs.close();
	return map;
}

bool AdminMap::WriteMap(const char * path) const
{
	ofstream ofs(path, ios::out | ios::binary);
	if (ofs.fail())
	{
		return false;
	}
	for (auto pair : adminMap)
	{
		ofs.write((char*)&pair.second, sizeof(Admin));
	}
	ofs.close();
	return true;
}

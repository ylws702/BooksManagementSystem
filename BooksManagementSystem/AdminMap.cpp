#include "stdafx.h"
#include "AdminMap.h"

bool AdminMap::Add(const Admin & admin)
{
	//已在列表中
	if (adminMap.find(admin.id) != adminMap.end())
	{
		return false;
	}
	pair<size_t, Admin>p(admin.id, admin);
	adminMap.insert(p);
	return true;
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

#include "stdafx.h"
#include "BookMap.h"

bool BookMap::Add(const Book & book)
{
	//图书已在列表中
	if (bookMap.find(book.id) != bookMap.end())
	{
		return false;
	}
	pair<ID, Book>p(book.id, book);
	bookMap.insert(p);
	return true;
}

bool BookMap::Delete(ID id)
{
	if (bookMap.find(id)==bookMap.end())
	{
		return false;
	}
	bookMap.erase(id);
	return true;
}


BookMap BookMap::ReadMap(const char* path)
{
	BookMap map;
	Book current(0);
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return map;
	}
	while (!ifs.read((char*)&current, sizeof(Book)).eof())
	{
		map.Add(current);
	}
	ifs.close();
	return map;
}


bool BookMap::WriteMap(const char* path)const
{
	ofstream ofs(path, ios::out | ios::binary);
	if (ofs.fail())
	{
		return false;
	}
	for (auto pair : bookMap)
	{
		ofs.write((char*)&pair.second, sizeof(Book));
	}
	ofs.close();
	return true;
}
//#include<iostream>
//#include<iomanip>
//using namespace std;
//void BookMap::Print()
//{
//	for (auto pair : bookMap)
//	{
//		std::cout << setw(16) << pair.second.id
//			<< setw(16) << pair.second.title
//			<< setw(16) << pair.second.author
//			<< setw(16) << pair.second.press
//			<< setw(16) << pair.second.date
//			<< setw(16) << pair.second.type
//			<< setw(2) << pair.second.exist
//			<< endl;
//	}
//}

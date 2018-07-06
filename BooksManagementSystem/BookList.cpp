#include "stdafx.h"
#include "BookList.h"


BookList::BookList()
{
}


BookList::~BookList()
{
}

bool BookList::Add(const Book & book)
{
	//图书已在列表中
	if (bookMap.find(book.id) != bookMap.end())
	{
		return false;
	}
	pair<size_t, Book>p(book.id, book);
	bookMap.insert(p);
	return true;
}

bool BookList::Delete(long long unsigned id)
{
	if (bookMap.find(id)==bookMap.end())
	{
		return false;
	}
	bookMap.erase(id);
	return true;
}


BookList BookList::ReadList(const char* path)
{
	BookList list;
	Book current(0);
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return list;
	}
	while (!ifs.read((char*)&current, sizeof(Book)).eof())
	{
		list.Add(current);
	}
	return list;
}


bool BookList::WriteList(const char* path)const
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
#include<iostream>
#include<iomanip>
using namespace std;
void BookList::Print()
{
	for (auto pair : bookMap)
	{
		std::cout << setw(16) << pair.second.id
			<< setw(16) << pair.second.title
			<< setw(16) << pair.second.author
			<< setw(16) << pair.second.press
			<< setw(16) << pair.second.date
			<< setw(16) << pair.second.type
			<< setw(2) << pair.second.exist
			<< endl;
	}
}

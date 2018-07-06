#include "stdafx.h"
#include "BookList.h"


BookList::BookList()
{
}


BookList::~BookList()
{
}

bool BookList::Add(const BookInfo & book)
{
	//图书已在列表中
	if (bookMap.find(book.id) != bookMap.end())
	{
		return false;
	}
	pair<size_t, BookInfo>p(book.id, book);
	bookMap.insert(p);
	return true;
}


BookList BookList::ReadList(const char* path)
{
	BookList list;
	BookInfo current;
	ifstream ifs(path, ios::in | ios::binary);
	if (ifs.fail())
	{
		return list;
	}
	while (!ifs.read((char*)&current, sizeof(BookInfo)).eof())
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
		ofs.write((char*)&pair.second, sizeof(BookInfo));
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
			<< endl;
	}
}

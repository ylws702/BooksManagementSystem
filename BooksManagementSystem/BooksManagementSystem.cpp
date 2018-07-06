// BooksManagementSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BookList.h"
#include <iostream>
using namespace std;

int main()
{
	BookList list;
	BookInfo book1(13124), book2(21412);
	book1.SetAuthor("wang");
	book1.SetTitle("book1");
	book2.SetAuthor("li");
	book2.SetTitle("book2");
	cout << list.Add(book1) << endl;
	list.Print();
	list.WriteList("data");

	BookList list2;
	list2 = BookList::ReadList("data");
	list2.Print();
    return 0;
}


// BooksManagementSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BookList.h"
#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	cout << (Date::Now()+30).ToString();
    return 0;
}


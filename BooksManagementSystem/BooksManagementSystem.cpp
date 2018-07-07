// BooksManagementSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AdminHelper.h"
#include "ShowHelper.h"
#include <iostream>
using namespace std;

int main()
{
	cout << 12412;
	ShowHelper::Clear();
	while (true)
	{
		cout << (int)ShowHelper::GetCh()<<endl;
	}
	if (ShowHelper::GetCh()=='2')
	{
		cout << "press 2" << endl;
	}
    return 0;
}


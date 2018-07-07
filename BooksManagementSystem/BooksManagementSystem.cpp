// BooksManagementSystem.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "AdminHelper.h"
#include "Show.h"
using namespace std;

int main()
{
	Show::MainMenu();
	cout << 12412;
	Show::Clear();
	while (true)
	{
		cout << (int)Show::GetCh()<<endl;
	}
	if (Show::GetCh()=='2')
	{
		cout << "press 2" << endl;
	}
    return 0;
}


// BooksManagementSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BookMap.h"
#include "UserMap.h"
#include "Date.h"
#include <iostream>
using namespace std;

int main()
{
	UserMap map1;
	User user1(124124, "wudi", "124902");
	User user2(124125,"luzheng", "214325");
	map1.Add(user1);
	map1.WriteMap("map");
	UserMap map2 = UserMap::ReadMap("map");
	map2.Add(user2);
	map2.Print();
    return 0;
}


#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include "User.h"
#include "Book.h"
#include "ShowHelper.h"
#include "UserHelper.h"
#include "AdminHelper.h"
#include "RootHelper.h"
class Show
{
public:
	static void ShowUser(const User& user);
	static void ShowBook(const Book& book);
	static void Clear();
	static char GetCh();
	static void MainMenu();
	static void UserMenu();
	static void AdminMenu();
	static void RootMenu();
//private:
	static const int width{ 72 };
	static const int height{ 20 };
	static const int marginH{ 4 };
	static const int marginV{ 2 };
#ifdef __linux
#include <termios.h>
	static struct termios old, newer;
	static void initTermios(int echo)
	{
		tcgetattr(0, &old); /* grab old terminal i/o settings */
		newer = old; /* make newer settings same as old settings */
		newer.c_lflag &= ~ICANON; /* disable buffered i/o */
		if (echo) {
			newer.c_lflag |= ECHO; /* set echo mode */
		}
		else {
			newer.c_lflag &= ~ECHO; /* set no echo mode */
		}
		tcsetattr(0, TCSANOW, &newer); /* use these newer terminal i/o settings now */
	}
	/* Restore old terminal i/o settings */
	static void resetTermios(void)
	{
		tcsetattr(0, TCSANOW, &old);
	}
	/* Read 1 character - echo defines echo mode */
	static char getch_(int echo)
	{
		char ch;
		initTermios(echo);
		ch = getchar();
		resetTermios();
		return ch;
	}

	/* Read 1 character without echo */
	static char _getch(void)
	{
		return getch_(0);
	}
#endif // __linux

};


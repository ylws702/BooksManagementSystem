#pragma once
#include <cstdio>
#include "User.h"
#include "Book.h"
class ShowHelper
{
public:
	static void ShowUser(const User& user);
	static void ShowBook(const Book& book);
	static void Clear();
	static char GetCh();
private:
#ifdef __linux
#include <termios.h>
	static struct termios old, new;
	static void initTermios(int echo)
	{
		tcgetattr(0, &old); /* grab old terminal i/o settings */
		new = old; /* make new settings same as old settings */
		new.c_lflag &= ~ICANON; /* disable buffered i/o */
		if (echo) {
			new.c_lflag |= ECHO; /* set echo mode */
		}
		else {
			new.c_lflag &= ~ECHO; /* set no echo mode */
		}
		tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
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


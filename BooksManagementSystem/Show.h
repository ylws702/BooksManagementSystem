#pragma once

#ifdef __linux
#include <termios.h>
#endif // __linux

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

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
	static void Clear();
	enum Key
	{
		Up=40,
		Down=48,
		Left=43,
		Right=45
	};
	static char GetCh();
	static void MainMenu();
	static void UserMenu();
	static void FindBookByID(UserHelper& user);
	static void FindBookByTitle(UserHelper& user);
	static void FindBorrowedBooks(UserHelper& user);
	static void FindNotBorrowedBooks(UserHelper& user);
	static void FindAllBooks(UserHelper& user);
	static void BorrowBook(UserHelper& user);
	static void GetBorrowInfo(UserHelper& user);
	static void ChangeUserPassword(UserHelper& user);
	static void AdminMenu();
	static void AddBook(AdminHelper& admin);
	static void RemoveBookByID(AdminHelper& admin, ID bookID = 0);
	static void RemoveBookByTitle(AdminHelper& admin);
	static void ModifyBookByID(AdminHelper& admin, ID id = 0);
	static void ModifyBookByTitle(AdminHelper& admin);
	static void FindBookByID(AdminHelper& admin);
	static void FindBookByTitle(AdminHelper& admin);
	static void FindBorrowedBooks(AdminHelper& admin);
	static void FindNotBorrowedBooks(AdminHelper& admin);
	static void FindAllBooks(AdminHelper& admin);
	static void AddUser(AdminHelper& admin);
	static void RemoveUser(AdminHelper& admin);
	static void ReportLoss(AdminHelper& admin);
	static void UndoReportLoss(AdminHelper& admin);
	static void ReturnBook(AdminHelper& admin);
	static void ChangeAdminPassword(AdminHelper& admin);
	static void RootMenu();
	static void AddAdmin(RootHelper& root);
	static void RemoveAdmin(RootHelper& root);
	static void FindAdmin(RootHelper& root);
	static void ChangeRootPassword(RootHelper& root);
//private:
#ifdef __linux
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


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
#include <sstream>
#include "User.h"
#include "Book.h"
#include "ShowHelper.h"
#include "UserHelper.h"
#include "AdminHelper.h"
#include "RootHelper.h"
class Show
{
public:
	//************************************
	// 函数名 : Clear
	// 功  能 : 清屏
	//************************************
	static void Clear();
	//键值
	enum Key
	{
		Up = 40,
		Down = 48,
		Left = 43,
		Right = 45
	};
	//************************************
	// 函数名 : GetCh
	// 功  能 : 从键盘获取一个键入的按键
	// 返回值 : char : 键入的按键
	//************************************
	static char GetCh();
	static ID GetID();
	//************************************
	// 函数名 : GetUInt
	// 功  能 : 从键盘获取一个unsigned int
	// 返回值 : unsigned int : 获取的unsigned int
	//************************************
	static unsigned int GetUInt();
	//************************************
	// 函数名 : MainMenu
	// 功  能 : 主菜单
	//************************************
	static void MainMenu();
	//************************************
	// 函数名 : UserMenu
	// 功  能 : 用户菜单
	//************************************
	static void UserMenu();
	//************************************
	// 函数名 : FindBookByID
	// 功  能 : 按编号查找图书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void FindBookByID(UserHelper& user);
	//************************************
	// 函数名 : FindBookByTitle
	// 功  能 : 按标题关键字查找图书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void FindBookByTitle(UserHelper& user);
	//************************************
	// 函数名 : FindBorrowedBooks
	// 功  能 : 列出全部借出图书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void FindBorrowedBooks(UserHelper& user);
	//************************************
	// 函数名 : FindNotBorrowedBooks
	// 功  能 : 列出全部未借出图书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void FindNotBorrowedBooks(UserHelper& user);
	//************************************
	// 函数名 : FindAllBooks
	// 功  能 : 查找所有图书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void FindAllBooks(UserHelper& user);
	//************************************
	// 函数名 : BorrowBook
	// 功  能 : 借书
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void BorrowBook(UserHelper& user);
	//************************************
	// 函数名 : GetBorrowInfo
	// 功  能 : 获取借阅信息
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void GetBorrowInfo(UserHelper& user);
	//************************************
	// 函数名 : ChangeUserPassword
	// 功  能 : 更改用户密码
	// 参  数 : UserHelper & user : 用户
	//************************************
	static void ChangeUserPassword(UserHelper& user);
	//************************************
	// 函数名 : AdminMenu
	// 功  能 : 图书管理员菜单
	//************************************
	static void AdminMenu();
	//************************************
	// 函数名 : AddBook
	// 功  能 : 添加图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void AddBook(AdminHelper& admin);
	//************************************
	// 函数名 : RemoveBookByID
	// 功  能 : 以编号查找移除图书
	// 参  数 : AdminHelper & admin : 图书管理员
	// 参  数 : ID bookID : 图书编号
	//************************************
	static void RemoveBookByID(AdminHelper& admin, ID bookID = 0);
	//************************************
	// 函数名 : RemoveBookByTitle
	// 功  能 : 以标题关键字查找移除图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void RemoveBookByTitle(AdminHelper& admin);
	//************************************
	// 函数名 : RemoveAllBooks
	// 功  能 : 移除全部图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void RemoveAllBooks(AdminHelper& admin);
	//************************************
	// 函数名 : ModifyBookByID
	// 功  能 : 以编号查找编辑
	// 参  数 : AdminHelper & admin : 图书管理员
	// 参  数 : ID id : 
	//************************************
	static void ModifyBookByID(AdminHelper& admin, ID id = 0);
	//************************************
	// 函数名 : ModifyBookByTitle
	// 功  能 : 以标题关键字查找编辑
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void ModifyBookByTitle(AdminHelper& admin);
	//************************************
	// 函数名 : FindBookByID
	// 功  能 : 以编号查找
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void FindBookByID(AdminHelper& admin);
	//************************************
	// 函数名 : FindBookByTitle
	// 功  能 : 以标题关键字查找
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void FindBookByTitle(AdminHelper& admin);
	//************************************
	// 函数名 : FindBorrowedBooks
	// 功  能 : 列出有借出的图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void FindBorrowedBooks(AdminHelper& admin);
	//************************************
	// 函数名 : FindNotBorrowedBooks
	// 功  能 : 列出没有借出的图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void FindNotBorrowedBooks(AdminHelper& admin);
	//************************************
	// 函数名 : FindAllBooks
	// 功  能 : 列出全部图书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void FindAllBooks(AdminHelper& admin);
	//************************************
	// 函数名 : AddUser
	// 功  能 : 添加用户
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void AddUser(AdminHelper& admin);
	//************************************
	// 函数名 : RemoveUser
	// 功  能 : 按编号移除用户
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void RemoveUser(AdminHelper& admin);
	//************************************
	// 函数名 : ReportLoss
	// 功  能 : 挂失
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void ReportLoss(AdminHelper& admin);
	//************************************
	// 函数名 : UndoReportLoss
	// 功  能 : 解除挂失
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void UndoReportLoss(AdminHelper& admin);
	//************************************
	// 函数名 : ReturnBook
	// 功  能 : 还书
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void ReturnBook(AdminHelper& admin);
	//************************************
	// 函数名 : ChangeAdminPassword
	// 功  能 : 修改图书管理员密码
	// 参  数 : AdminHelper & admin : 图书管理员
	//************************************
	static void ChangeAdminPassword(AdminHelper& admin);
	//************************************
	// 函数名 : RootMenu
	// 功  能 : 系统管理员菜单
	//************************************
	static void RootMenu();
	//************************************
	// 函数名 : AddAdmin
	// 功  能 : 添加图书管理员
	// 参  数 : RootHelper & root : 系统管理员
	//************************************
	static void AddAdmin(RootHelper& root);
	//************************************
	// 函数名 : RemoveAdmin
	// 功  能 : 按编号移除图书管理员
	// 参  数 : RootHelper & root : 系统管理员
	//************************************
	static void RemoveAdmin(RootHelper& root);
	//************************************
	// 函数名 : FindAdmin
	// 功  能 : 按编号查找图书管理员
	// 参  数 : RootHelper & root : 系统管理员
	//************************************
	static void FindAdmin(RootHelper& root);
	//************************************
	// 函数名 : ChangeRootPassword
	// 功  能 : 更改系统管理员密码
	// 参  数 : RootHelper & root : 系统管理员
	//************************************
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


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
	// ������ : Clear
	// ��  �� : ����
	//************************************
	static void Clear();
	//��ֵ
	enum Key
	{
		Up = 40,
		Down = 48,
		Left = 43,
		Right = 45
	};
	//************************************
	// ������ : GetCh
	// ��  �� : �Ӽ��̻�ȡһ������İ���
	// ����ֵ : char : ����İ���
	//************************************
	static char GetCh();
	static ID GetID();
	//************************************
	// ������ : GetUInt
	// ��  �� : �Ӽ��̻�ȡһ��unsigned int
	// ����ֵ : unsigned int : ��ȡ��unsigned int
	//************************************
	static unsigned int GetUInt();
	//************************************
	// ������ : MainMenu
	// ��  �� : ���˵�
	//************************************
	static void MainMenu();
	//************************************
	// ������ : UserMenu
	// ��  �� : �û��˵�
	//************************************
	static void UserMenu();
	//************************************
	// ������ : FindBookByID
	// ��  �� : ����Ų���ͼ��
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void FindBookByID(UserHelper& user);
	//************************************
	// ������ : FindBookByTitle
	// ��  �� : ������ؼ��ֲ���ͼ��
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void FindBookByTitle(UserHelper& user);
	//************************************
	// ������ : FindBorrowedBooks
	// ��  �� : �г�ȫ�����ͼ��
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void FindBorrowedBooks(UserHelper& user);
	//************************************
	// ������ : FindNotBorrowedBooks
	// ��  �� : �г�ȫ��δ���ͼ��
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void FindNotBorrowedBooks(UserHelper& user);
	//************************************
	// ������ : FindAllBooks
	// ��  �� : ��������ͼ��
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void FindAllBooks(UserHelper& user);
	//************************************
	// ������ : BorrowBook
	// ��  �� : ����
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void BorrowBook(UserHelper& user);
	//************************************
	// ������ : GetBorrowInfo
	// ��  �� : ��ȡ������Ϣ
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void GetBorrowInfo(UserHelper& user);
	//************************************
	// ������ : ChangeUserPassword
	// ��  �� : �����û�����
	// ��  �� : UserHelper & user : �û�
	//************************************
	static void ChangeUserPassword(UserHelper& user);
	//************************************
	// ������ : AdminMenu
	// ��  �� : ͼ�����Ա�˵�
	//************************************
	static void AdminMenu();
	//************************************
	// ������ : AddBook
	// ��  �� : ���ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void AddBook(AdminHelper& admin);
	//************************************
	// ������ : RemoveBookByID
	// ��  �� : �Ա�Ų����Ƴ�ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	// ��  �� : ID bookID : ͼ����
	//************************************
	static void RemoveBookByID(AdminHelper& admin, ID bookID = 0);
	//************************************
	// ������ : RemoveBookByTitle
	// ��  �� : �Ա���ؼ��ֲ����Ƴ�ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void RemoveBookByTitle(AdminHelper& admin);
	//************************************
	// ������ : RemoveAllBooks
	// ��  �� : �Ƴ�ȫ��ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void RemoveAllBooks(AdminHelper& admin);
	//************************************
	// ������ : ModifyBookByID
	// ��  �� : �Ա�Ų��ұ༭
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	// ��  �� : ID id : 
	//************************************
	static void ModifyBookByID(AdminHelper& admin, ID id = 0);
	//************************************
	// ������ : ModifyBookByTitle
	// ��  �� : �Ա���ؼ��ֲ��ұ༭
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void ModifyBookByTitle(AdminHelper& admin);
	//************************************
	// ������ : FindBookByID
	// ��  �� : �Ա�Ų���
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void FindBookByID(AdminHelper& admin);
	//************************************
	// ������ : FindBookByTitle
	// ��  �� : �Ա���ؼ��ֲ���
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void FindBookByTitle(AdminHelper& admin);
	//************************************
	// ������ : FindBorrowedBooks
	// ��  �� : �г��н����ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void FindBorrowedBooks(AdminHelper& admin);
	//************************************
	// ������ : FindNotBorrowedBooks
	// ��  �� : �г�û�н����ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void FindNotBorrowedBooks(AdminHelper& admin);
	//************************************
	// ������ : FindAllBooks
	// ��  �� : �г�ȫ��ͼ��
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void FindAllBooks(AdminHelper& admin);
	//************************************
	// ������ : AddUser
	// ��  �� : ����û�
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void AddUser(AdminHelper& admin);
	//************************************
	// ������ : RemoveUser
	// ��  �� : ������Ƴ��û�
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void RemoveUser(AdminHelper& admin);
	//************************************
	// ������ : ReportLoss
	// ��  �� : ��ʧ
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void ReportLoss(AdminHelper& admin);
	//************************************
	// ������ : UndoReportLoss
	// ��  �� : �����ʧ
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void UndoReportLoss(AdminHelper& admin);
	//************************************
	// ������ : ReturnBook
	// ��  �� : ����
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void ReturnBook(AdminHelper& admin);
	//************************************
	// ������ : ChangeAdminPassword
	// ��  �� : �޸�ͼ�����Ա����
	// ��  �� : AdminHelper & admin : ͼ�����Ա
	//************************************
	static void ChangeAdminPassword(AdminHelper& admin);
	//************************************
	// ������ : RootMenu
	// ��  �� : ϵͳ����Ա�˵�
	//************************************
	static void RootMenu();
	//************************************
	// ������ : AddAdmin
	// ��  �� : ���ͼ�����Ա
	// ��  �� : RootHelper & root : ϵͳ����Ա
	//************************************
	static void AddAdmin(RootHelper& root);
	//************************************
	// ������ : RemoveAdmin
	// ��  �� : ������Ƴ�ͼ�����Ա
	// ��  �� : RootHelper & root : ϵͳ����Ա
	//************************************
	static void RemoveAdmin(RootHelper& root);
	//************************************
	// ������ : FindAdmin
	// ��  �� : ����Ų���ͼ�����Ա
	// ��  �� : RootHelper & root : ϵͳ����Ա
	//************************************
	static void FindAdmin(RootHelper& root);
	//************************************
	// ������ : ChangeRootPassword
	// ��  �� : ����ϵͳ����Ա����
	// ��  �� : RootHelper & root : ϵͳ����Ա
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


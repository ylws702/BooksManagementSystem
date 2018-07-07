#include "stdafx.h"
#include "ShowHelper.h"


void ShowHelper::ShowUser(const User & user)
{
}

void ShowHelper::ShowBook(const Book & book)
{
}

void ShowHelper::Clear()
{
#ifdef __linux
	system("clear");
#endif // !__linux
#ifdef _WIN32
	system("cls");
#endif // _WIN32

}
#ifdef __linux
using namespace std;
char ShowHelper::GetCh()
{
	char c;
	system("stty -echo");
	c = getchar();
	system("stty echo");
}
#endif // !__linux
#ifdef _WIN32
#include <conio.h>
char ShowHelper::GetCh()
{
	return _getch();
}
#endif // _WIN32




#include "stdafx.h"
#include "ShowHelper.h"


void ShowHelper::ShowUser(const User & user)
{
}

void ShowHelper::ShowBook(const Book & book)
{
}

#ifdef __linux
#define CLEAR "clear"
#endif // !__linux
#ifdef _WIN32
#define CLEAR "cls"
#endif // _WIN32
void ShowHelper::Clear()
{
	system(CLEAR);
}

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

char ShowHelper::GetCh()
{
	char c = _getch();
#ifdef _WIN32
	_getch();
#endif // _WIN32
	return c;
}


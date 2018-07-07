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
};


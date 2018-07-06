#include "stdafx.h"
#include "User.h"


User::User()
{
}


User::~User()
{
}

bool User::Borrow(ID id)
{
	borrowList.push_back(pair<ID, Date>(id, Date::Now()+ borrowdays));
	return true;
}

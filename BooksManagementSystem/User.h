#pragma once
#include <list>
#include "Date.h"
using namespace std;
typedef long long unsigned ID;
class User
{
public:
	User();
	~User();
	bool Borrow(ID id);
private:
	list<pair<ID,Date>> borrowList;
	const uint borrowdays{ 30 };
};

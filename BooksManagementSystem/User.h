#pragma once
#include <list>
#include "Date.h"
using namespace std;
typedef long long unsigned ID;
class User
{
public:
	User()=delete;
	User(ID id);
	User(ID id, const char *name, const char *password);
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	~User();
	void Borrow(ID bookID);
private:
	ID userID;
	//����name������Ҫͬʱ�޸�SetName����
	char name[16];
	char password[32];
	list<pair<ID,Date>> borrowList;
	const uint borrowdays{ 30 };
};

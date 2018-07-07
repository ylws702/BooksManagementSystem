#pragma once
typedef long long unsigned ID;
class Admin
{
	friend class AdminMap;
	friend class AdminHelper;
public:
	Admin() = delete;
	Admin(ID id);
private:
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	ID id{ 0 };
	char name[16];
	char password[32];
};

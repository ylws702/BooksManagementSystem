#pragma once
typedef long long unsigned ID;
class Admin
{
	friend class AdminMap;
public:
	Admin() = delete;
	Admin(ID id);
	bool SetName(const char *name);
	bool SetPassword(const char *password);
private:
	ID id{ 0 };
	char name[16];
	char password[32];
};

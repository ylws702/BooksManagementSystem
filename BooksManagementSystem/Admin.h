#pragma once
typedef long long unsigned ID;
class Admin
{
	friend class AdminMap;
	friend class AdminHelper;
	friend class RootHelper;
public:
	Admin() = delete;
	Admin(const ID id);
	Admin(const ID id, const char *name, const char *password);
private:
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	ID id{ 0 };
	char name[16];
	char password[32];
};

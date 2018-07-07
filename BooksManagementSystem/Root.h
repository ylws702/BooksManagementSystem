#pragma once
typedef long long unsigned ID;
class Root
{
private:
	Root();
	bool SetName(const char *name);
	bool SetPassword(const char *password);
	char name[16];
	char password[32];
};


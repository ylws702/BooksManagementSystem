#pragma once
#include "Admin.h"
#include <map>
#include <fstream>
using namespace std;
class AdminMap
{
public:
	AdminMap() {}
	bool Add(const Admin& admin);
	static AdminMap ReadMap(const char* path);
	//������:
	//path:�б�Ҫ����ĵ�ַ
	//����ֵ:
	//�ļ�����ɹ�����true,ʧ�ܷ���false
	bool WriteMap(const char* path)const;
private:
	map<ID, Admin> adminMap;
};


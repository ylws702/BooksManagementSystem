#pragma once
#include <map>
#include <fstream>
#include "User.h"
class UserMap
{
public:
	UserMap() {}
	bool Add(const User& user);
	bool Delete(ID id);
	bool Find(ID id, User& result)const;
	static UserMap ReadMap(const char* path);
	//������:
	//path:�б�Ҫ����ĵ�ַ
	//����ֵ:
	//�ļ�����ɹ�����true,ʧ�ܷ���false
	bool WriteMap(const char* path)const;
	//DEBUG�ú���,����ʱɾ��
	void Print();
private:
	map<ID, User> userMap;
};


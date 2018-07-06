#pragma once
#include "BookInfo.h"
#include <map>
#include <fstream>
using namespace std;
class BookList
{
public:
	BookList();
	~BookList();
	bool Add(const BookInfo& book);
	static BookList ReadList(const char* path);
	//������:
	//path:�б�Ҫ����ĵ�ַ
	//����ֵ:
	//�ļ�����ɹ�����true,ʧ�ܷ���false
	bool WriteList(const char* path)const;
	void Print();
private:
	map<size_t,BookInfo> bookMap;
};


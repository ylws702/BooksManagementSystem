#pragma once
#include "Book.h"
#include <map>
#include <fstream>
using namespace std;
class BookList
{
public:
	BookList();
	~BookList();
	bool Add(const Book& book);
	bool Delete(long long unsigned id);
	static BookList ReadList(const char* path);
	//������:
	//path:�б�Ҫ����ĵ�ַ
	//����ֵ:
	//�ļ�����ɹ�����true,ʧ�ܷ���false
	bool WriteList(const char* path)const;
	//DEBUG�ú���,����ʱɾ��
	void Print();
private:
	map<long long unsigned,Book> bookMap;
};


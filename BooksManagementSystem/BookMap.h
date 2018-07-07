#pragma once
#include "Book.h"
#include <map>
#include <fstream>
using namespace std;
class BookMap
{
public:
	BookMap();
	~BookMap();
	bool Add(const Book& book);
	bool Delete(ID id);
	static BookMap ReadMap(const char* path);
	//������:
	//path:�б�Ҫ����ĵ�ַ
	//����ֵ:
	//�ļ�����ɹ�����true,ʧ�ܷ���false
	bool WriteMap(const char* path)const;
	//DEBUG�ú���,����ʱɾ��
	void Print();
private:
	map<ID, Book> bookMap;
};


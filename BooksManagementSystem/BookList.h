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
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteList(const char* path)const;
	void Print();
private:
	map<size_t,BookInfo> bookMap;
};


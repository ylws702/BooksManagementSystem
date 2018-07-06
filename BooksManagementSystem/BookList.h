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
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteList(const char* path)const;
	//DEBUG用函数,发布时删除
	void Print();
private:
	map<long long unsigned,Book> bookMap;
};


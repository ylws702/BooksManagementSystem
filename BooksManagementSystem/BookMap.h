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
	//参数表:
	//path:列表要保存的地址
	//返回值:
	//文件保存成功返回true,失败返回false
	bool WriteMap(const char* path)const;
	//DEBUG用函数,发布时删除
	void Print();
private:
	map<ID, Book> bookMap;
};


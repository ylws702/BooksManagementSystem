#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class ShowHelper
{
public:
	//删除默认构造函数
	ShowHelper() = delete;
	//************************************
	// 函数名 : ShowHelper
	// 功  能 : 
	// 参  数 : const string & header : 
	// 参  数 : const string & footer : 
	//************************************
	ShowHelper(const string& header = "", const string&footer = "");
	//对齐方式
	enum Alignment
	{
		//居中对齐
		Center,
		//左对齐
		Left
	};
	//控制台窗口宽度
	static const int width{ 72 };
	//控制台窗口高度
	static const int height{ 20 };
	//控制台水平边距
	static const int marginH{ 4 };
	//控制台垂直边距
	static const int marginV{ 2 };
	//************************************
	// 函数名 : Header
	// 功  能 : 将str居中并以fill填充
	// 返回值 : std::string : 居中带填充字符的字符串
	// 参  数 : const string & str : 要处理的字符串
	// 参  数 : const char fill : 填充的字符
	//************************************
	static string Header(const string& str, const char fill = '-');
	//************************************
	// 函数名 : ToCenter
	// 功  能 : 将str居中并在marginH处添加margin
	// 返回值 : std::string : 居中并在边距处带边框字符的字符串
	// 参  数 : const string & str : 要处理的字符串
	// 参  数 : const char margin : 边框字符
	//************************************
	static string ToCenter(const string& str, const char margin = '|');
	//************************************
	// 函数名 : ToLeft
	// 功  能 : 将str左对齐距离左边框left并在marginH处添加margin
	// 返回值 : std::string : 左对齐并在边距处带边框字符的字符串
	// 参  数 : const string & str : 要处理的字符串
	// 参  数 : const unsigned int left : 到左边框的距离
	// 参  数 : const char margin : 边框字符
	//************************************
	static string ToLeft(const string& str, const unsigned int left = 4, const char margin = '|');
	//************************************
	// 函数名 : Add
	// 功  能 : 向框架内容中添加一定对齐处理的字符串
	// 参  数 : const string & str : 要添加的内容
	// 参  数 : const Alignment alignment : 对齐方式
	//************************************
	void Add(const string& str = "", const Alignment alignment = Left);
	//************************************
	// 函数名 : SetHeader
	// 功  能 : 设置页眉和页脚
	// 参  数 : const string & header : 要设置的页眉
	// 参  数 : const string & footer : 要设置的页脚
	//************************************
	void SetHeader(const string& header = "", const string&footer = "");
	//************************************
	// 函数名 : Reset
	// 功  能 : 清除设置的内容,并重新设置页眉和页脚
	// 参  数 : const string & header : 要重新设置的页眉
	// 参  数 : const string & footer : 要重新设置的页脚
	//************************************
	void Reset(const string& header = "", const string&footer = "");
	//************************************
	// 函数名 : Show
	// 功  能 : 打印格式化之后的字符串向量
	//************************************
	void Show()const;
	//************************************
	// 函数名 : Normalize
	// 功  能 : 对已经设置标头和内容字符串向量进行格式化
	// 返回值 : std::vector<std::string> : 格式化后的字符串向量
	//************************************
	vector<string> Normalize()const;
	//************************************
	// 函数名 : Clear
	// 功  能 : 清除已经设置的标头和内容
	//************************************
	void Clear();
private:
	//内容
	vector<pair<string, Alignment>> strs;
	//页眉
	string header;
	//页脚
	string footer;
};


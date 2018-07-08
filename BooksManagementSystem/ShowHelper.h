#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class ShowHelper
{
public:
	ShowHelper() {}
	ShowHelper(const string& header = "", const string&footer = "");
	enum Alignment
	{
		Center,
		Left
	};
	static const int width{ 72 };
	static const int height{ 20 };
	static const int marginH{ 4 };
	static const int marginV{ 2 };
	static string Header(const string& str, const char fill = '-');
	static string ToCenter(const string& str, const char margin = '|');
	static string ToLeft(const string& str, const unsigned int left = 4, const char margin = '|');
	void Add(const string& str = "", const Alignment alignment = Left);
	void SetHeader(const string& header = "", const string&footer = "");
	void Reset(const string& header = "", const string&footer = "");
	void Show()const;
	vector<string> Normalize()const;
	void Clear();
private:
	vector<pair<string, Alignment>> strs;
	string header;
	string footer;
};


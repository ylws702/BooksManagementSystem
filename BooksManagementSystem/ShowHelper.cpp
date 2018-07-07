#include "stdafx.h"
#include "ShowHelper.h"


ShowHelper::ShowHelper(const string & head, const string & foot):
	header(head),footer(foot)
{
}

string ShowHelper::Header(const string & str, const char fill)
{
	string result;
	int start;
	if (str.size() > width)
	{
		start = (str.size() - width) / 2;
		for (int i = 0; i < width; i++)
		{
			result.push_back(str[i + start]);
		}
		return result;
	}
	result.resize(width, fill);
	for (int i = 0; i < marginH; i++)
	{
		result[i] = ' ';
		result[width - i - 1] = ' ';
	}
	start = (width - str.size()) / 2;
	for (int i = 0; i < (int)str.size(); i++)
	{
		result[start + i] = str[i];
	}
	return result;
}

string ShowHelper::ToCenter(const string & str, const char margin)
{
	string result;
	result.resize(width, ' ');
	result[marginH] = margin;
	result[width - marginH - 1] = margin;
	int start;
	if (str.size() > width - 2 * marginH - 2)
	{
		start= (str.size() - width) / 2- marginH;
		for (int i = 0; i < width - 2 * marginH-2; i++)
		{
			result[i + margin + 1] = str[start+i];
		}
		return result;
	}
	start = (width - str.size()) / 2;
	for (int i = 0; i < (int)str.size(); i++)
	{
		result[start + i] = str[i];
	}
	return result;
}

string ShowHelper::ToLeft(const string & str, const unsigned int left, const char margin)
{
	string result;
	result.resize(width, ' ');
	result[marginH] = margin;
	result[width - marginH - 1] = margin;
	int i = 0;
	for (char c : str)
	{
		if (marginH + left + i + 1 >= width - marginH - 1)
		{
			return result;
		}
		result[marginH + left + i + 1] = c;
		i++;
	}
	return result;
}

void ShowHelper::Add(const string & str, const Alignment alignment)
{
	pair<string, Alignment>p(str, alignment);
	strs.push_back(p);
}

void ShowHelper::SetHeader(const string & head, const string & foot)
{
	header = head;
	footer = foot;
}

void ShowHelper::Reset(const string & head, const string & foot)
{
	strs.clear();
	header = head;
	footer = foot;
}

void ShowHelper::Show() const
{
	for (auto str : Normalize())
	{
		cout << str << endl;
	}
}

vector<string> ShowHelper::Normalize() const
{
	vector<string> result;
	if (strs.size()>height-2*marginV-2)
	{
		return result;
	}
	for (int i = 0; i < marginV; i++)
	{
		result.push_back(string());
	}
	result.push_back(Header(header));
	for (int i = 0; i < (int)(height - strs.size()) / 2 - marginV - 1; i++)
	{
		result.push_back(ToCenter(""));
	}
	for (auto p : strs)
	{
		switch (p.second)
		{
		case Center:
			result.push_back(ToCenter(p.first));
			break;
		case Left: default:
			result.push_back(ToLeft(p.first));
			break;
		}
	}
	for (int i = 0; i < (int)(height - strs.size()) / 2 - marginV - 1; i++)
	{
		result.push_back(ToCenter(""));
	}
	result.push_back(Header(footer));
	for (int i = 0; i < marginV; i++)
	{
		result.push_back(string());
	}
	return result;
}

void ShowHelper::Clear()
{
	strs.clear();
	header.clear();
	footer.clear();
}


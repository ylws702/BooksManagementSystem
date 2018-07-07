#include "stdafx.h"
#include "Show.h"


void Show::ShowUser(const User & user)
{
}

void Show::ShowBook(const Book & book)
{
}

#ifdef __linux
#define CLEAR "clear"
#endif // !__linux
#ifdef _WIN32
#define CLEAR "cls"
#endif // _WIN32
void Show::Clear()
{
	system(CLEAR);
}

#ifdef _WIN32
#include <conio.h>
#endif // _WIN32

char Show::GetCh()
{
	char c = _getch();
#ifdef _WIN32
	_getch();
#endif // _WIN32
	return c;
}

void Show::MainMenu()
{
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		helper.Reset("欢迎使用图书管理系统", "请选择数字键选择相应的服务");
		helper.Add("(1)  普通用户");
		helper.Add("(2)  图书管理员");
		helper.Add("(3)  系统管理员");
		helper.Add("(0)  退 出");
		for (auto str : helper.Normalize())
		{
			cout << str << endl;
		}
		switch (GetCh())
		{
		case '1':
			UserMenu();
			break;
		case '2':
			AdminMenu();
			break;
		case '3':
			RootMenu();
			break;
		case '0':
			Clear();
			helper.Reset("图书管理系统", "按任意键退出");
			helper.Add("谢 谢 使 用 !", ShowHelper::Center);
			for (auto str : helper.Normalize())
			{
				cout << str << endl;
			}
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::UserMenu()
{
	Clear();
	UserHelper user;
	char username[16], password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		cout << "用户名:";
		cin >> username;
		cout << "密码:";
		cin >> password;
		if (!user.Login(username, password))
		{
			Clear();
			helper.Reset("欢迎读者使用图书管理系统", "按任意键重试!");
			helper.Add("用户名或密码错误!", ShowHelper::Center);
			helper.Show();
			GetCh();
		}
	}
	while (true)
	{
		Clear();
		helper.Reset("欢迎读者使用图书管理系统", "请选择数字键选择相应的服务");
		helper.Add("(1)  查询书籍信息");
		helper.Add("(2)  查询借阅信息");
		helper.Add("(3)  修改登录密码");
		helper.Add("(0)  退 出");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			UserMenu();
			break;
		case '2':
			//Search();
			break;
		case '3':
			//DeleteBook();
			break;
		case '0':
			Clear();
			helper.Clear();
			helper.SetHeader("图书管理系统", "按任意键退出");
			helper.Add("谢 谢 使 用 !", ShowHelper::Center);
			for (auto str : helper.Normalize())
			{
				cout << str << endl;
			}
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::AdminMenu()
{
	Clear();
	UserHelper user;
	char username[16], password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		cout << "用户名:";
		cin >> username;
		cout << "密码:";
		cin >> password;
		if (!user.Login(username, password))
		{
			Clear();
			helper.Reset("欢迎读者使用图书管理系统", "按任意键重试!");
			helper.Add("用户名或密码错误!", ShowHelper::Center);
			helper.Show();
			GetCh();
		}
	}
	while (true)
	{
		Clear();
		helper.Reset("欢迎读者使用图书管理系统", "请选择数字键选择相应的服务");
		helper.Add("(1)  查询书籍信息");
		helper.Add("(2)  查询借阅信息");
		helper.Add("(3)  修改登录密码");
		helper.Add("(0)  退 出");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			UserMenu();
			break;
		case '2':
			//Search();
			break;
		case '3':
			//DeleteBook();
			break;
		case '0':
			Clear();
			helper.Clear();
			helper.SetHeader("图书管理系统", "按任意键退出");
			helper.Add("谢 谢 使 用 !", ShowHelper::Center);
			for (auto str : helper.Normalize())
			{
				cout << str << endl;
			}
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::RootMenu()
{
	Clear();
	RootHelper root;
	char password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		cout << "密码:";
		cin >> password;
		if (root.Login(password))
		{
			break;
		}
		Clear();
		helper.Reset("欢迎使用图书管理系统", "按任意键重试!");
		helper.Add("密码错误!", ShowHelper::Center);
		helper.Show();
		GetCh();
	}
	while (true)
	{
		Clear();
		helper.Reset("欢迎使用图书管理系统", "请选择数字键选择相应的服务");
		helper.Add("(1)  添加图书管理员");
		helper.Add("(2)  删除图书管理员");
		helper.Add("(3)  查找图书管理员");
		helper.Add("(0)  注 销");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			UserMenu();
			break;
		case '2':
			//Search();
			break;
		case '3':
			//DeleteBook();
			break;
		case '0':
			Clear();
			helper.Clear();
			helper.SetHeader("正在注销", "按任意键退回主菜单");
			helper.Add("谢 谢 使 用 !", ShowHelper::Center);
			for (auto str : helper.Normalize())
			{
				cout << str << endl;
			}
			GetCh();
			return;
		default:
			break;
		}
	}
}


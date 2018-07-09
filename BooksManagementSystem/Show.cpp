#include "stdafx.h"
#include "Show.h"
#include"debug.h"


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
	c += _getch();
#endif // _WIN32
	return c;
}

void Show::MainMenu()
{;
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		debug("正在创建界面，调用的是Show::MainMenu()，若要进行下一步调试。请按任意键");
		helper.Reset("欢迎使用图书管理系统", "请选择数字键选择相应的服务");
		helper.Add("(1)  普通用户");
		helper.Add("(2)  图书管理员");
		helper.Add("(3)  系统管理员");
		helper.Add("(0)  退 出");
		helper.Show();
		
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
	UserHelper user;
	char  password[32];
	string name;
	ID uid;
	ShowHelper helper("", "");
	while (true)
	{
		cout << "用户编号:";
		cin >> uid;
		cout << "密码:";
		cin >> password;
		debug("正在进行密码的验证，调用user.Login()，若要进行下一步调试。请按任意键");
		if (user.Login(uid, password))
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用helper.Reset(),helper.Add()，helper.Show(),判断字符是否为q,若要进行下一步调试。请按任意键");
		helper.Reset("普通用户登录", "按(q)返回主菜单,其余键重试!");
		helper.Add("用户名或密码错误!", ShowHelper::Center);
		helper.Show();
		switch (GetCh())
		{
		case 'q':
			return;
		default:
			break;
		}
	}
	name = user.GetUserName();
	Clear();
	debug("正在，若要进行下一步调试。请按任意键");
	helper.Reset(name + ",欢迎使用", "按任意键继续");
	helper.Add("登录成功", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("正在，若要进行下一步调试。请按任意键");
		helper.Reset("普通用户:" + name, "请选择数字键选择相应的服务");
		helper.Add("(1)  查询书籍");
		helper.Add("(2)  借书");
		helper.Add("(3)  查询借阅信息");
		helper.Add("(4)  更改密码");
		helper.Add("(0)  退 出");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			Clear();
			helper.Reset("查找书籍", "选择数字键选择方式,其余键返回");
			helper.Add("选择查找方式:");
			helper.Add();
			helper.Add("(1)  编号");
			helper.Add("(2)  标题");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				FindBookByID(user);
				break;
			case '2':
				FindBookByTitle(user);
				break;
			default:
				break;
			}
			break;
			break;
		case '2':
			BorrowBook(user);
			break;
		case '3':
			GetBorrowInfo(user);
			break;
		case '4':
			ChangeUserPassword(user);
			break;
		case '0':
			Clear();
			helper.Clear();
			debug("正在，若要进行下一步调试。请按任意键");
			helper.SetHeader("再见" + string(name), "按任意键返回主菜单");
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

void Show::FindBookByID(UserHelper & user)
{
	ID id;
	cout << "输入图书编号:";
	cin >> id;
	const char* title = user.GetBookTitle(id);
	const char* author = user.GetBookAuthor(id);
	const char* press = user.GetBookPress(id);
	const char* date = user.GetBookDate(id);
	const char* type = user.GetBookType(id);
	bool  exist = user.GetBookExist(id);
	ShowHelper helper("", "");
	if (nullptr == title)
	{
		Clear();
		debug("正在，若要进行下一步调试。请按任意键");
		helper.Reset("查找书籍", "按任意键返回上一级菜单");
		helper.Add("没有找到该编号的书籍!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在，若要进行下一步调试。请按任意键");
	helper.Reset("查找书籍", "按任意键返回上一级菜单");
	helper.Add("查找结果");
	helper.Add("《" + string(title) + "》", ShowHelper::Center);
	helper.Add();
	helper.Add("ID:" + to_string(id));
	helper.Add("作者:" + string(author));
	helper.Add("出版社:" + string(press));
	helper.Add("出版日期:" + string(date));
	helper.Add("类型:" + string(type));
	helper.Add();
	if (exist)
	{
		helper.Add("在馆");
	}
	else
	{
		helper.Add("不在馆");
	}
	helper.Show();
	GetCh();
}

void Show::FindBookByTitle(UserHelper & user)
{
	char str[32];
	cout << "输入图书标题关键字:";
	cin >> str;
	ShowHelper helper("", "");
	auto ids = user.FindBookByTitle(str);
	if (ids.size() == 0)
	{
		Clear();
		helper.Reset("查找书籍", "按任意键返回图书管理员菜单");
		helper.Add("没有找到标题含" + string(str) + "的书籍!");
		helper.Show();
		GetCh();
		return;
	}
	string size = to_string(ids.size());
	string title;
	string author;
	string press;
	string date;
	string type;
	bool exist;
	ID id;
	auto it = ids.begin();
	unsigned int i = 1;
	while (true)
	{
		Clear();
		id = *it;
		title = user.GetBookTitle(*it);
		author = user.GetBookAuthor(*it);
		press = user.GetBookPress(*it);
		date = user.GetBookDate(*it);
		type = user.GetBookType(*it);
		exist = user.GetBookExist(*it);
		helper.Reset("查询结果",
			"第" + to_string(i) + "页,共" + size + "页。" +
			"左右键翻页" +
			",其余键返回");
		helper.Add("《" + string(title) + "》", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("作者:" + author);
		helper.Add("出版社:" + press);
		helper.Add("出版日期:" + date);
		helper.Add("类型:" + type);
		helper.Add();
		if (exist)
		{
			helper.Add("在馆");
		}
		else
		{
			helper.Add("不在馆");
		}
		helper.Show();
		switch (GetCh())
		{
		case Right:case Down:
			if (i >= ids.size())
			{
				break;
			}
			i++;
			it++;
			break;
		case Left:case Up:
			if (i <= 1)
			{
				break;
			}
			i--;
			it--;
			break;
		default:
			return;
		}
	}
}

void Show::BorrowBook(UserHelper & user)
{
	bool goOn = false;
	ID id;
	const char* title;
	const char*author;
	const char* press;
	const char* date;
	const char* type;
	bool exist;
	bool flag;
	ShowHelper helper("", "");
	while (true)
	{
		cout << "输入图书编号:";
		cin >> id;
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		exist = user.GetBookExist(id);
		if (nullptr == title)
		{
			Clear();
			helper.Reset("借阅书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到该编号的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				break;
			default:
				return;
			}
			continue;
		}
		if (!exist)
		{
			Clear();
			helper.Reset("借阅书籍", "按(c)继续,其余键返回");
			helper.Add("该编号的书籍不在馆内!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				break;
			default:
				return;
			}
			continue;
		}
		while (true)
		{
			Clear();
			helper.Reset("确认借阅书籍", "(y)是------(n)否");
			helper.Add("ID:" + to_string(id));
			helper.Add();
			helper.Add("标题:" + string(title));
			helper.Add("作者:" + string(author));
			helper.Add("出版社:" + string(press));
			helper.Add("出版日期:" + string(date));
			helper.Add("类型:" + string(type));
			helper.Show();
			switch (GetCh())
			{
			case 'y':
				Clear();
				helper.Reset("借阅书籍", "按(c)继续,其余键返回");
				if (!(user.Borrow(id) && user.Save()))
				{
					helper.Add("借书失败");
				}
				else
				{
					helper.Add("借书成功");
				}
				helper.Add("ID:" + to_string(id));
				helper.Add();
				helper.Add("标题:" + string(title));
				helper.Show();
				switch (GetCh())
				{
				case 'c':
					break;
				default:
					return;
				}
				flag = true;
				break;
			case 'n':
				Clear();
				helper.Reset("借阅书籍", "按(c)继续,其余键返回");
				helper.Add("已取消操作",ShowHelper::Center);
				helper.Show();
				switch (GetCh())
				{
				case 'c':
					break;
				default:
					return;
				}
				flag = true;
				break;
			default:
				flag = false;
				break;
			}
			if (flag)
			{
				break;
			}
		}
	}

}

void Show::GetBorrowInfo(UserHelper & user)
{
	const list<pair<ID, Date>> ids = user.GetBorrowList();
	ShowHelper helper("", "");
	if (0 == ids.size())
	{
		Clear();
		helper.Reset("查询借阅信息", "按任意键返回上一级菜单");
		helper.Add("没有借阅信息!");
		helper.Show();
		GetCh();
		return;
	}
	string size = to_string(ids.size());
	string title;
	string author;
	string press;
	string date;
	string type;
	string borrowDate;
	string returnDate;
	ID id;
	auto it = ids.begin();
	unsigned int i = 1;
	while (true)
	{
		Clear();
		debug("正在，若要进行下一步调试。请按任意键");
		id = it->first;
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		borrowDate = it->second.ToString();
		returnDate = (it->second + 90).ToString();
		helper.Reset("借阅信息",
			"第" + to_string(i) + "页,共" + size + "页。" +
			"左右键翻页" +
			",其余键返回");
		helper.Add("《" + string(title) + "》", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("作者:" + author);
		helper.Add("出版社:" + press);
		helper.Add("出版日期:" + date);
		helper.Add("类型:" + type);
		helper.Add("借出日期:" + borrowDate);
		helper.Add("应还日期:" + returnDate);
		helper.Show();
		switch (GetCh())
		{
		case Right:case Down:
			if (i >= ids.size())
			{
				break;
			}
			i++;
			it++;
			break;
		case Left:case Up:
			if (i <= 1)
			{
				break;
			}
			i--;
			it--;
			break;
		default:
			return;
		}
	}
}

void Show::ChangeUserPassword(UserHelper & user)
{
	char oldpw[32];
	char newpw[32];
	char newpw2[32];
	ShowHelper helper("", "");
	while (true)
	{
		cout << "输入原密码:";
		cin >> oldpw;
		if (user.TestPassword(oldpw))
		{
			break;
		}
		Clear();
		helper.Reset("更改密码", "按(c)重试,其余键返回");
		helper.Add("密码错误!");
		helper.Show();
		switch (GetCh())
		{
		case 'c':
			break;
		default:
			return;
		}
	}
	while (true)
	{
		cout << "输入新密码:";
		cin >> newpw;
		cout << "再次输入新密码:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		helper.Reset("更改密码", "按任意键继续");
		helper.Add("两次输入的密码不匹配!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!user.ChangePassword(oldpw, newpw))
	{
		Clear();
		helper.Reset("更改密码", "按任意键返回图书管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("更改密码", "按任意键返回图书管理员菜单");
	helper.Add("保存成功!");
	helper.Add();
	helper.Add("已成功更改密码!");
	helper.Show();
	GetCh();
}

void Show::AdminMenu()
{
	AdminHelper admin;
	char name[16], password[32];
	ID id;
	ShowHelper helper("", "");
	while (true)
	{
		cout << "编号:";
		cin >> id;
		cout << "用户名:";
		cin >> name;
		cout << "密码:";
		cin >> password;
		if (admin.Login(id, name, password))
		{
			break;
		}
		Clear();
		helper.Reset("图书管理员登录", "按(q)返回主菜单,其余键重试!");
		helper.Add("编号或用户名或密码错误!", ShowHelper::Center);
		helper.Show();
		switch (GetCh())
		{
		case 'q':
			return;
		default:
			break;
		}
	}
	Clear();
	helper.Reset((string)name + ",欢迎使用图书管理系统", "按任意键继续");
	helper.Add("登录成功", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		helper.Reset("图书管理员:" + (string)name, "请选择数字键选择相应的服务");
		helper.Add("(1)  新增书籍");
		helper.Add("(2)  删除书籍");
		helper.Add("(3)  修改书籍信息");
		helper.Add("(4)  查询图书");
		helper.Add("(5)  添加读者用户");
		helper.Add("(6)  删除读者用户");
		helper.Add("(7)  借书证挂失");
		helper.Add("(8)  借书证解除挂失");
		helper.Add("(9)  更改密码");
		helper.Add("(a)  还书");
		helper.Add("(0)  退 出");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			AddBook(admin);
			break;
		case '2':
			RemoveBook(admin);
			break;
		case '3':
			ModifyBook(admin);
			break;
		case '4':
			Clear();
			helper.Reset("查找书籍", "选择数字键选择方式,其余键返回");
			helper.Add("选择查找方式:");
			helper.Add();
			helper.Add("(1)  编号");
			helper.Add("(2)  标题");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				FindBookByID(admin);
				break;
			case '2':
				FindBookByTitle(admin);
				break;
			default:
				break;
			}
			break;
		case '5':
			AddUser(admin);
			break;
		case '6':
			RemoveUser(admin);
			break;
		case '7':
			ReportLoss(admin);
			break;
		case '8':
			UndoReportLoss(admin);
			break;
		case '9':
			ChangeAdminPassword(admin);
			break;
		case 'a':
			ReturnBook(admin);
			break;
		case '0':
			Clear();
			helper.Clear();
			helper.SetHeader("再见" + string(name), "按任意键返回主菜单");
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

void Show::AddBook(AdminHelper & admin)
{
	while (true)
	{
		ID id;
		char title[32];
		char author[32];
		char press[32];
		char date[32];
		char type[32];
		cout << "输入编号:";
		cin >> id;
		cout << "输入标题:";
		cin >> title;
		cout << "输入作者:";
		cin >> author;
		cout << "输入出版社:";
		cin >> press;
		cout << "输入出版日期:";
		cin >> date;
		cout << "输入类型:";
		cin >> type;
		admin.AddBook(id, title, author, press, date, type);
		Clear();
		ShowHelper helper("添加书籍", "");
		helper.Add("正在保存修改...");
		helper.Show();
		Clear();
		helper.Reset("添加书籍", "按(c)继续,其余键返回图书管理员菜单");
		if (!admin.Save())
		{
			helper.Add("保存失败!");
		}
		else
		{
			helper.Add("成功保存修改!");
			helper.Add();
			helper.Add("已成功添加图书:《" + string(title) + "》");
			helper.Add("编号:" + to_string(id));
			helper.Add("作者:" + string(author));
			helper.Add("出版社:" + string(press));
			helper.Add("出版日期:" + string(date));
			helper.Add("类型:" + string(type));
		}
		helper.Show();
		switch (GetCh())
		{
		case 'c':
			break;
		default:
			return;
		}
	}
}

void Show::RemoveBook(AdminHelper & admin)
{
	ID id;
	cout << "输入书籍编号:";
	cin >> id;
	string title = admin.GetBookTitle(id);
	string author = admin.GetBookAuthor(id);
	string press = admin.GetBookPress(id);
	string date = admin.GetBookDate(id);
	string type = admin.GetBookType(id);
	ShowHelper helper("", "");
	if (nullptr == admin.GetBookTitle(id))
	{
		Clear();
		helper.Reset("删除书籍", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该书籍!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("删除书籍", "(y)是------(n)否");
	helper.Add("编号:" + to_string(id));
	helper.Add();
	helper.Add("标题:" + string(title));
	helper.Add("作者:" + string(author));
	helper.Add("出版社:" + string(press));
	helper.Add("出版日期:" + string(date));
	helper.Add("类型:" + string(type));
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':
			Clear();
			helper.Reset("删除书籍", "");
			helper.Add("正在保存修改...");
			helper.Show();
			if (!(admin.RemoveBook(id) && admin.Save()))
			{
				Clear();
				helper.Reset("删除书籍", "按任意键返回系统管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("删除书籍", "按任意键返回系统管理员菜单");
			helper.Add("成功保存修改!");
			helper.Add();
			helper.Add("已成功删除《" + title + "》");
			helper.Add();
			helper.Add("编号:" + to_string(id));
			helper.Add("作者:" + author);
			helper.Add("出版社:" + press);
			helper.Add("出版日期:" + date);
			helper.Add("类型:" + type);
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			helper.Reset("删除书籍", "按任意键返回系统管理员菜单");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::ModifyBook(AdminHelper & admin)
{
	ID id;
	cout << "输入书籍编号:";
	cin >> id;
	char str[32];
	string title;
	string author;
	string press;
	string date;
	string type;
	ShowHelper helper("", "");
	if (nullptr == admin.GetBookTitle(id))
	{
		Clear();
		helper.Reset("修改书籍", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该书籍!");
		helper.Show();
		GetCh();
		return;
	}
	while (true)
	{
		title = admin.GetBookTitle(id);
		author = admin.GetBookAuthor(id);
		press = admin.GetBookPress(id);
		date = admin.GetBookDate(id);
		type = admin.GetBookType(id);
		Clear();
		helper.Reset("修改书籍", "请选择数字键选择修改的内容,按(q)返回");
		helper.Add("编号:" + to_string(id));
		helper.Add();
		helper.Add("选择修改的内容:");
		helper.Add("(1)  标题:" + string(title));
		helper.Add("(2)  作者:" + string(author));
		helper.Add("(3)  出版社:" + string(press));
		helper.Add("(4)  出版日期:" + string(date));
		helper.Add("(5)  类型:" + string(type));
		helper.Show();
		switch (GetCh())
		{
		case '1':
			cout << "输入新标题:";
			cin >> str;
			if (!admin.SetBookTitle(id, str) && admin.Save())
			{
				Clear();
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			helper.Reset("修改书籍", "按任意键继续");
			helper.Add("修改成功！", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '2':
			cout << "输入新作者:";
			cin >> str;
			if (!admin.SetBookAuthor(id, str) && admin.Save())
			{
				Clear();
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改作者失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			helper.Reset("修改书籍", "按任意键继续");
			helper.Add("修改作者成功！", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '3':
			cout << "输入新出版社:";
			cin >> str;
			if (!admin.SetBookPress(id, str) && admin.Save())
			{
				Clear();
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改出版社失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			helper.Reset("修改书籍", "按任意键继续");
			helper.Add("修改出版社成功！", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '4':
			cout << "输入新出版日期:";
			cin >> str;
			if (!admin.SetBookDate(id, str) && admin.Save())
			{
				Clear();
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改出版社失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			helper.Reset("修改书籍", "按任意键继续");
			helper.Add("修改出版社成功！", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '5':
			cout << "输入新类型:";
			cin >> str;
			if (!admin.SetBookType(id, str) && admin.Save())
			{
				Clear();
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改类型失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			helper.Reset("修改书籍", "按任意键继续");
			helper.Add("修改类型成功！", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case 'q':
			return;
		default:
			break;
		}
	}
}

void Show::FindBookByID(AdminHelper & admin)
{
	ID id;
	cout << "输入图书编号:";
	cin >> id;
	const char* title = admin.GetBookTitle(id);
	const char* author = admin.GetBookAuthor(id);
	const char* press = admin.GetBookPress(id);
	const char* date = admin.GetBookDate(id);
	const char* type = admin.GetBookType(id);
	bool  exist = admin.GetBookExist(id);
	ShowHelper helper("", "");
	if (nullptr == title)
	{
		Clear();
		helper.Reset("查找书籍", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该编号的书籍!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("查找书籍", "按任意键返回图书管理员菜单");
	helper.Add("查找结果");
	helper.Add("《" + string(title) + "》", ShowHelper::Center);
	helper.Add();
	helper.Add("ID:" + to_string(id));
	helper.Add("作者:" + string(author));
	helper.Add("出版社:" + string(press));
	helper.Add("出版日期:" + string(date));
	helper.Add("类型:" + string(type));
	helper.Add();
	if (exist)
	{
		helper.Add("在馆");
	}
	else
	{
		helper.Add("不在馆");
	}
	helper.Show();
	GetCh();
}

void Show::FindBookByTitle(AdminHelper & admin)
{
	char str[32];
	cout << "输入图书标题关键字:";
	cin >> str;
	ShowHelper helper("", "");
	auto ids = admin.FindBookByTitle(str);
	if (ids.size() == 0)
	{
		Clear();
		helper.Reset("查找书籍", "按任意键返回图书管理员菜单");
		helper.Add("没有找到标题含" + string(str) + "的书籍!");
		helper.Show();
		GetCh();
		return;
	}
	string size = to_string(ids.size());
	string title;
	string author;
	string press;
	string date;
	string type;
	bool exist;
	ID id;
	auto it = ids.begin();
	unsigned int i = 1;
	while (true)
	{
		Clear();
		id = *it;
		title = admin.GetBookTitle(*it);
		author = admin.GetBookAuthor(*it);
		press = admin.GetBookPress(*it);
		date = admin.GetBookDate(*it);
		type = admin.GetBookType(*it);
		exist = admin.GetBookExist(*it);
		helper.Reset("查询结果",
			"第" + to_string(i) + "页,共" + size + "页。" +
			"左右键翻页" +
			",其余键返回");
		helper.Add("《" + string(title) + "》", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("作者:" + author);
		helper.Add("出版社:" + press);
		helper.Add("出版日期:" + date);
		helper.Add("类型:" + type);
		helper.Add();
		if (exist)
		{
			helper.Add("在馆");
		}
		else
		{
			helper.Add("不在馆");
		}
		helper.Show();
		switch (GetCh())
		{
		case Right:case Down:
			if (i >= ids.size())
			{
				break;
			}
			i++;
			it++;
			break;
		case Left:case Up:
			if (i <= 1)
			{
				break;
			}
			i--;
			it--;
			break;
		default:
			return;
		}
	}
}

void Show::AddUser(AdminHelper & admin)
{
	ID id;
	char name[16];
	char password[32];
	int gender;
	int type;
	cout << "输入用户编号:";
	cin >> id;
	cout << "输入用户名:";
	cin >> name;
	cout << "输入用户密码:";
	cin >> password;
	cout << "输入性别(1)男(2)女:";
	cin >> gender;
	cout << "输入类型(1)本科生(2)研究生(3)教师:";
	cin >> type;

	Clear();
	ShowHelper helper("添加用户", "");
	helper.Add("正在保存修改...");
	helper.Show();
	if (!(admin.AddUser(id, name, password, gender, type) && admin.Save()))
	{
		Clear();
		helper.Reset("添加管理员", "按任意键返回图书管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("添加管理员", "按任意键返回图书管理员菜单");
	helper.Add("成功保存修改!");
	helper.Add();
	helper.Add("已成功添加用户:" + string(name));
	helper.Add();
	helper.Add("编号:" + to_string(id));
	helper.Add("性别:" + string(admin.GetUserGender(id)));
	helper.Add("类型:" + string(admin.GetUserType(id)));
	helper.Show();
	GetCh();
}

void Show::RemoveUser(AdminHelper & admin)
{
	ID id;
	cout << "输入用户ID:";
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("删除用户", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("删除用户", "(y)是------(n)否");
	helper.Add("用户名:" + string(name));
	helper.Add();
	helper.Add("编号:" + to_string(id));
	helper.Add("性别:" + string(admin.GetUserGender(id)));
	helper.Add("类型:" + string(admin.GetUserType(id)));
	helper.Show();
	string namecopy = name;
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			helper.Reset("删除用户", "");
			helper.Add("正在保存修改...");
			helper.Show();
			if (!(admin.RemoveUser(id) && admin.Save()))
			{
				Clear();
				helper.Reset("删除用户", "按任意键返回图书管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("删除用户", "按任意键返回图书管理员菜单");
			helper.Add("成功保存修改!");
			helper.Add();
			helper.Add("已成功删除用户:");
			helper.Add(namecopy);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			helper.Reset("删除用户", "按任意键返回图书管理员菜单");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::ReportLoss(AdminHelper & admin)
{
	ID id;
	cout << "输入用户ID:";
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("挂失", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("挂失", "(y)是------(n)否");
	helper.Add("用户名:" + string(name));
	helper.Add();
	helper.Add("编号:" + to_string(id));
	helper.Add("性别:" + string(admin.GetUserGender(id)));
	helper.Add("类型:" + string(admin.GetUserType(id)));
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			if (!(admin.ReportLoss(id) && admin.Save()))
			{
				Clear();
				helper.Reset("挂失", "按任意键返回图书管理员菜单");
				helper.Add("挂失失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("挂失", "按任意键返回图书管理员菜单");
			helper.Add("挂失成功!");
			helper.Add();
			helper.Add(name);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			helper.Reset("挂失", "按任意键返回图书管理员菜单");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::UndoReportLoss(AdminHelper & admin)
{
	ID id;
	cout << "输入用户ID:";
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("解除挂失", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("解除挂失", "(y)是------(n)否");
	helper.Add("用户名:" + string(name));
	helper.Add();
	helper.Add("编号:" + to_string(id));
	helper.Add("性别:" + string(admin.GetUserGender(id)));
	helper.Add("类型:" + string(admin.GetUserType(id)));
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			if (!(admin.ReportLoss(id) && admin.Save()))
			{
				Clear();
				helper.Reset("解除挂失", "按任意键返回图书管理员菜单");
				helper.Add("解除挂失失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("解除挂失", "按任意键返回图书管理员菜单");
			helper.Add("解除挂失成功!");
			helper.Add();
			helper.Add(name);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			helper.Reset("挂失", "按任意键返回图书管理员菜单");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::ReturnBook(AdminHelper & admin)
{
	ID uid, bookID;
	cout << "输入用户编号:";
	cin >> uid;
	cout << "输入书籍编号:";
	cin >> bookID;
	Clear();
	ShowHelper helper("还书", "");
	helper.Add("正在保存修改...");
	helper.Show();
	if (!(admin.Accept(uid, bookID) && admin.Save()))
	{
		Clear();
		helper.Reset("还书", "按任意键返回图书管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("添加管理员", "按任意键返回图书管理员菜单");
	helper.Add("成功保存修改!");
	helper.Show();
	GetCh();
}

void Show::ChangeAdminPassword(AdminHelper & admin)
{
	char oldpw[32];
	char newpw[32];
	char newpw2[32];
	ShowHelper helper("", "");
	while (true)
	{
		cout << "输入原密码:";
		cin >> oldpw;
		if (admin.TestPassword(oldpw))
		{
			break;
		}
		Clear();
		helper.Reset("更改密码", "按(q)返回,其余键重试");
		helper.Add("密码错误!");
		helper.Show();
		switch (GetCh())
		{
		case 'q':
			return;
		default:
			break;
		}
	}
	while (true)
	{
		cout << "输入新密码:";
		cin >> newpw;
		cout << "再次输入新密码:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		helper.Reset("更改密码", "按任意键继续");
		helper.Add("两次输入的密码不匹配!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!admin.ChangePassword(oldpw, newpw))
	{
		Clear();
		helper.Reset("更改密码", "按任意键返回图书管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("更改密码", "按任意键返回图书管理员菜单");
	helper.Add("保存成功!");
	helper.Add();
	helper.Add("已成功更改密码!");
	helper.Show();
	GetCh();
}

void Show::RootMenu()
{
	RootHelper root;
	char password[32];
	ShowHelper helper("", "");
	while (true)
	{
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
		helper.Add("(4)  更改密码");
		helper.Add("(0)  注 销");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			AddAdmin(root);
			break;
		case '2':
			RemoveAdmin(root);
			break;
		case '3':
			FindAdmin(root);
			break;
		case '4':
			ChangeRootPassword(root);
			break;
		case '0':
			Clear();
			helper.Clear();
			helper.SetHeader("再见,系统管理员", "按任意键退回主菜单");
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

void Show::AddAdmin(RootHelper&root)
{
	char name[16];
	char password[32];
	cout << "输入用户名:";
	cin >> name;
	cout << "输入密码:";
	cin >> password;
	ID id = root.AddAdmin(name, password);
	Clear();
	ShowHelper helper("添加管理员", "");
	helper.Add("正在保存修改...");
	helper.Show();
	if (!root.Save())
	{
		Clear();
		helper.Reset("添加管理员", "按任意键返回系统管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("添加管理员", "按任意键返回系统管理员菜单");
	helper.Add("成功保存修改!");
	helper.Add();
	helper.Add("已成功添加管理员:");
	helper.Add(name);
	helper.Add();
	helper.Add("ID:");
	helper.Add(to_string(id));
	helper.Show();
	GetCh();
}

void Show::RemoveAdmin(RootHelper & root)
{
	ID id;
	cout << "输入管理员ID:";
	cin >> id;
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
		helper.Add("没有找到该管理员!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("删除管理员", "(y)是------(n)否");
	helper.Add("ID:");
	helper.Add(to_string(id));
	helper.Add();
	helper.Add("用户名:");
	helper.Add(name);
	helper.Show();
	string namecopy = name;
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			helper.Reset("删除管理员", "");
			helper.Add("正在保存修改...");
			helper.Show();
			if (!(root.RemoveAdmin(id) && root.Save()))
			{
				Clear();
				helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
			helper.Add("成功保存修改!");
			helper.Add();
			helper.Add("已成功删除管理员:");
			helper.Add(namecopy);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::FindAdmin(RootHelper & root)
{
	ID id;
	cout << "输入管理员ID:";
	cin >> id;
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
		helper.Add("没有找到该管理员!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("查找管理员", "按任意键返回系统管理员菜单");
	helper.Add("查找结果");
	helper.Add("ID:");
	helper.Add(to_string(id));
	helper.Add();
	helper.Add("用户名:");
	helper.Add(name);
	helper.Show();
	GetCh();
}

void Show::ChangeRootPassword(RootHelper & root)
{
	char oldpw[32];
	char newpw[32];
	while (true)
	{
		cout << "输入原密码:";
		cin >> oldpw;
		if (root.TestPassword(oldpw))
		{
			break;
		}
		cout << "密码错误!" << endl;
	}
	cout << "输入新密码:";
	cin >> newpw;
	Clear();
	ShowHelper helper("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!(root.ChangePassword(oldpw, newpw) && root.Save()))
	{
		Clear();
		helper.Reset("更改密码", "按任意键返回系统管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("更改密码", "按任意键返回系统管理员菜单");
	helper.Add("保存成功!");
	helper.Add();
	helper.Add("已成功更改密码!");
	helper.Show();
	GetCh();
}


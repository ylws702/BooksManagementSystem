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

char Show::GetCh()
{
	char c = _getch();
#ifdef _WIN32
	c += _getch();
#endif // _WIN32
	return c;
}

ID Show::GetID()
{
	ID id=0;
	stringstream ss;
	string s;
	cin >> s;
	ss << s;
	ss >> id;
	return id;
}

unsigned int Show::GetUInt()
{
	unsigned int uint=0;
	stringstream ss;
	string s;
	cin >> s;
	ss << s;
	ss >> uint;
	return uint;
}

void Show::MainMenu()
{
	;
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
		uid = GetID();
		cout << "密码:";
		//cin >> password;
		for (int i = 0; i < 32; i++)
		{
			password[i] = GetCh();
			if (13 == password[i])
			{
				password[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
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
	debug("调用helper.Reset()，helper.Add()输出登录信息，若要进行下一步调试。请按任意键");
	helper.Reset(name + ",欢迎使用", "按任意键继续");
	helper.Add("登录成功", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("正在创建用户界面，调用helper.Reset（），helper.Add（），helper.Show()，若要进行下一步调试。请按任意键");
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
			debug("正在创建查找书籍界面，使用helper.Reset（），helper.Add()，helper.Show()，若要进行下一步调试。请按任意键");
			helper.Reset("查找书籍", "选择数字键选择方式,其余键返回");
			helper.Add("选择查找方式:");
			helper.Add();
			helper.Add("(1)  编号");
			helper.Add("(2)  标题");
			helper.Add("(3)  有借出书籍");
			helper.Add("(4)  无借出书籍");
			helper.Add("(5)  全部书籍");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				debug("正在进行依靠ID查找，调用FindBookByID(user)，若要进行下一步调试。请按任意键");
				FindBookByID(user);
				break;
			case '2':
				debug("正在进行依靠名称查找，调用FindBookByTitle(user);，若要进行下一步调试。请按任意键");
				FindBookByTitle(user);
				break;
			case '3':
				debug("正在进行有借出书籍查找，调用FindBorrowedBooks(user)，若要进行下一步调试。请按任意键");
				FindBorrowedBooks(user);
				break;
			case '4':
				debug("正在进行无借出书籍查找，调用FindNotBorrowedBooks(user)，若要进行下一步调试。请按任意键");
				FindNotBorrowedBooks(user);
				break;
			case '5':
				debug("正在显示全部书籍，调用FindAllBooks(user)，若要进行下一步调试。请按任意键");
				FindAllBooks(user);
				break;
			default:
				break;
			}
			break;
			break;
		case '2':
			debug("正在进入借书界面，调用BorrowBook(user)，若要进行下一步调试。请按任意键");
			BorrowBook(user);
			break;
		case '3':
			debug("正在进入查询借书信息界面，调用GetBorrowInfo(user)，若要进行下一步调试。请按任意键");
			GetBorrowInfo(user);
			break;
		case '4':
			debug("正在更改密码操作，调用ChangeUserPassword(user)，若要进行下一步调试。请按任意键");
			ChangeUserPassword(user);
			break;
		case '0':
			debug("正在调用清屏函数Clear();helper.Clear(); ，若要进行下一步调试。请按任意键");
			Clear();
			helper.Clear();
			debug("正在输出结束信息，调用helper.SetHeader（），helper.Add（），若要进行下一步调试。请按任意键");
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
	const char* title;
	const char* author;
	const char* press;
	const char* date;
	const char* type;
	string totalCount;
	string restCount;
	//bool  exist;
	while (true)
	{
		cout << "输入图书编号:";
		id = GetID();
		debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
		debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		totalCount = to_string(user.GetBookTotalCount(id));
		restCount = to_string(user.GetBookRestCount(id));
		
		//exist = user.GetBookExist(id);
		ShowHelper helper("", "");
		if (nullptr == title)
		{
			Clear();
			debug("正在进行错误信息输出，调用helper.Reset（），helper.Add（），清屏函数Clear(),若要进行下一步调试。请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到该编号的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		Clear();
		debug("正在输出书本信息，调用函数，helper.Reset(),helper.Add(),清屏函数Clear(),若要进行下一步调试。请按任意键");
		helper.Reset("查找书籍", "按(c)继续,其余键返回");
		helper.Add("查找结果");
		helper.Add("《" + string(title) + "》", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("作者:" + string(author));
		helper.Add("出版社:" + string(press));
		helper.Add("出版日期:" + string(date));
		helper.Add("类型:" + string(type));
		helper.Add();
		helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
		/*if (exist)
		{
			helper.Add("在馆");
		}
		else
		{
			helper.Add("不在馆");
		}*/
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

void Show::FindBookByTitle(UserHelper & user)
{
	ShowHelper helper("", "");
	char str[32];
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		cout << "输入图书标题关键字:";
		cin >> str;
		auto ids = user.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset()，helper.Add(),helper.Show(),若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到标题含\"" + string(str) + "\"的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("正在输出书本信息，调用helper.Reset(),helper.Add(),helper.Show();，若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
				helper.Add("在馆");
			}
			else
			{
				helper.Add("不在馆");
			}*/
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
}

void Show::FindBorrowedBooks(UserHelper & user)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		debug("正在判断是否有这本书，调用auto ids = user.GetBorrowedBooks();，若要进行下一步调试，请按任意键");
		auto ids = user.GetBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear()，helper.Reset(),helper.Add(),helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有有借出的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id)); 
			debug("正在输出书本信息，调用helper.Reset()，helper.Add(),helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::FindNotBorrowedBooks(UserHelper & user)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		debug("正在判断是否有这本书，调用auto ids = user.GetNotBorrowedBooks();，若要进行下一步调试，请按任意键");
		auto ids = user.GetNotBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add,helper.Show()，若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有未借出的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("正在输出书本信息，调用helper.Reset()，helper.Add(),helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::FindAllBooks(UserHelper & user)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		
		auto ids = user.GetAllBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset()，helper.Add(),helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("正在输出书本信息，调用helper.Reset()，helper.Add(),helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
	string totalCount;
	string restCount;
	bool exist;
	bool flag;
	ShowHelper helper("", "");
	while (true)
	{
		cout << "输入图书编号:";
		debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
		debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
		id = GetID();
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		exist = user.GetBookExist(id);
		restCount = to_string(user.GetBookRestCount(id));
		totalCount = to_string(user.GetBookTotalCount(id));
		if (nullptr == title)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
			debug("正在输出借阅界面及书本信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("确认借阅书籍", "(y)是------(n)否");
			helper.Add("ID:" + to_string(id));
			helper.Add();
			helper.Add("标题:" + string(title));
			helper.Add("作者:" + string(author));
			helper.Add("出版社:" + string(press));
			helper.Add("出版日期:" + string(date));
			helper.Add("类型:" + string(type));
			helper.Add();
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			helper.Show();
			switch (GetCh())
			{
			case 'y':
				Clear();
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
				debug("正在输出借阅信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
				helper.Reset("借阅书籍", "按(c)继续,其余键返回");
				helper.Add("已取消操作", ShowHelper::Center);
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
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
		debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
		debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
		id = it->first;
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		borrowDate = it->second.ToString();
		returnDate = (it->second + 90).ToString();
		debug("正在输出书本信息，调用helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
		debug("正在输出提示，若要进行下一步调试，请按任意键");
		cout << "输入新密码:";
		cin >> newpw;
		cout << "再次输入新密码:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
		helper.Reset("更改密码", "按任意键继续");
		helper.Add("两次输入的密码不匹配!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("正在输出提示信息，若要进行下一步调试，请按任意键");
	helper.Reset("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!user.ChangePassword(oldpw, newpw))
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
		helper.Reset("更改密码", "按任意键返回用户菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("正在输出信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
	helper.Reset("更改密码", "按任意键返回用户菜单");
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
		debug("正在输出提示，若要进行下一步调试，请按任意键");
		cout << "编号:";
		id = GetID();
		cout << "用户名:";
		cin >> name;
		cout << "密码:";
		//cin >> password;

		for (int i = 0; i < 32; i++)
		{
			password[i] = GetCh();
			if (13 == password[i])
			{
				password[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		if (admin.Login(id, name, password))
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
	debug("正在输出界面，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
	helper.Reset((string)name + ",欢迎使用图书管理系统", "按任意键继续");
	helper.Add("登录成功", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("正在输出图书管理员界面，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
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
		helper.Add("(a)  还 书");
		helper.Add("(0)  退 出");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			AddBook(admin);
			break;
		case '2':
			Clear();
			debug("正在输出删除书籍界面，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("删除书籍", "选择数字键选择方式,其余键返回");
			helper.Add("选择查找方式");
			helper.Add();
			helper.Add("(1)  按书名删除");
			helper.Add("(2)  按编号删除");
			helper.Add("(d)  全部删除");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				RemoveBookByTitle(admin);
				break;
			case '2':
				RemoveBookByID(admin);
				break;
			case 'd':
				RemoveAllBooks(admin);
				break;
			default:
				break;
			}
			break;
		case '3':
			Clear();
			debug("正在输出修改方式，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("修改书籍信息", "选择数字键选择方式,其余键返回");
			helper.Add("选择修改方式");
			helper.Add();
			helper.Add("(1)  按书名修改");
			helper.Add("(2)  按编号修改");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				ModifyBookByTitle(admin);
				break;
			case '2':
				ModifyBookByID(admin);
				break;
			default:
				break;
			}
			break;
		case '4':
			Clear();
			debug("正在输出查询界面，调用清屏函数Clear(),helper.Reset(),helper.Add，helper.Show()若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "选择数字键选择方式,其余键返回");
			helper.Add("选择查找方式:");
			helper.Add();
			helper.Add("(1)  编号");
			helper.Add("(2)  标题");
			helper.Add("(3)  有借出书籍");
			helper.Add("(4)  无借出书籍");
			helper.Add("(5)  全部书籍");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				FindBookByID(admin);
				break;
			case '2':
				FindBookByTitle(admin);
				break;
			case '3':
				FindBorrowedBooks(admin);
				break;
			case '4':
				FindNotBorrowedBooks(admin);
				break;
			case '5':
				FindAllBooks(admin);
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
			debug("正在输出信息，调用清屏函数Clear(),helper.SetHeader(),helper.Add()，若要进行下一步调试，请按任意键");
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
	ID id;
	char title[32];
	char author[32];
	char press[32];
	char date[32];
	char type[32];
	int number;
	while (true)
	{
		debug("正在输出提示，若要进行下一步调试，请按任意键");
		cout << "输入编号:";
		id = GetID();
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
		cout << "输入数量:";
		number = GetUInt();
		admin.AddBook(id, title, author, press, date, type, number);
		Clear();
		debug("正在输出信息，调用清屏函数Clear(),helper.SetHeader(),helper.Add()，若要进行下一步调试，请按任意键");
		ShowHelper helper("添加书籍", "");
		helper.Add("正在保存修改...");
		helper.Show();
		Clear();
		debug("正在输出添加书籍信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，若要进行下一步调试，请按任意键");
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

void Show::RemoveBookByID(AdminHelper & admin, ID id)
{
	ShowHelper helper("", "");
	if (0 == id)
	{
		cout << "输入书籍编号:";
		id = GetID();
		const char* title = admin.GetBookTitle(id);
		if (nullptr == admin.GetBookTitle(id))
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除书籍", "按任意键返回图书管理员菜单");
			helper.Add("没有找到该书籍!");
			helper.Show();
			GetCh();
			return;
		}
	}
	string titleCopy = admin.GetBookTitle(id);
	string author = admin.GetBookAuthor(id);
	string press = admin.GetBookPress(id);
	string date = admin.GetBookDate(id);
	string type = admin.GetBookType(id);
	Clear();
	debug("正在输出删除书籍信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	helper.Reset("删除书籍", "(y)是------(n)否");
	helper.Add("编号:" + to_string(id));
	helper.Add();
	helper.Add("标题:" + titleCopy);
	helper.Add("作者:" + author);
	helper.Add("出版社:" + press);
	helper.Add("出版日期:" + date);
	helper.Add("类型:" + type);
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("删除书籍", "按任意键返回系统管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("正在输出删除书籍信息及书本信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除书籍", "按任意键返回");
			helper.Add("成功保存修改!");
			helper.Add();
			helper.Add("已成功删除《" + titleCopy + "》");
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
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除书籍", "按任意键返回");
			helper.Add("已取消操作!");
			helper.Show();
			GetCh();
			return;
		default:
			break;
		}
	}
}

void Show::RemoveBookByTitle(AdminHelper & admin)
{
	ShowHelper helper("", "");
	char str[32];
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		cout << "输入图书标题关键字:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到标题含\"" + string(str) + "\"的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear()，id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查询结果",
				"第" + to_string(i) + "页,共" + size + "页。" +
				"左右键翻页,(y)选择图书" +
				",其余键取消");
			helper.Add("《" + string(title) + "》", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("作者:" + author);
			helper.Add("出版社:" + press);
			helper.Add("出版日期:" + date);
			helper.Add("类型:" + type);
			helper.Add();
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
			case 'y':
				RemoveBookByID(admin, id);
			default:
				return;
			}
		}
	}
}

void Show::RemoveAllBooks(AdminHelper & admin)
{
	Clear();
	debug("正在输出删除全部书籍及确认信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	ShowHelper helper("删除全部书籍!!!", "按(y)删除,其余键返回");
	helper.Add("警告", ShowHelper::Center);
	helper.Add();
	helper.Add("这将删除全部书籍!!!");
	helper.Add("确认?");
	helper.Show();
	switch (GetCh())
	{
	case 'y':
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("删除全部书籍", "按任意键键返回");
		if (!(admin.RemoveAllBooks() && admin.Save()))
		{
			helper.Add("删除失败!", ShowHelper::Center);
		}
		else
		{
			helper.Add("删除成功!", ShowHelper::Center);
		}
		helper.Show();
		GetCh();
		return;
	default:
		Clear();
		debug("正在输出取消信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("删除全部书籍", "按任意键键返回");
		helper.Add("已取消操作!", ShowHelper::Center);
		helper.Show();
		GetCh();
		break;
	}
}

void Show::ModifyBookByID(AdminHelper & admin, ID id)
{
	char str[32];
	string title;
	string author;
	string press;
	string date;
	string type;
	ShowHelper helper("", "");
	if (0 == id)
	{
		cout << "输入书籍编号:";
		id = GetID();
		if (nullptr == admin.GetBookTitle(id))
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("修改书籍", "按任意键返回图书管理员菜单");
			helper.Add("没有找到该书籍!");
			helper.Show();
			GetCh();
			return;
		}
	}
	while (true)
	{
		debug("正在获得书本信息，调用id = *it;title = user.GetBookTitle(*it);请按任意键");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
		debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
		title = admin.GetBookTitle(id);
		author = admin.GetBookAuthor(id);
		press = admin.GetBookPress(id);
		date = admin.GetBookDate(id);
		type = admin.GetBookType(id);
		Clear();
		debug("正在输出修改书籍信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改作者失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改出版社失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改出版社失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("修改书籍", "按任意键继续");
				helper.Add("修改类型失败！", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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

void Show::ModifyBookByTitle(AdminHelper & admin)
{
	ShowHelper helper("", "");
	char str[32];
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		cout << "输入图书标题关键字:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到标题含\"" + string(str) + "\"的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear(),id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查询结果",
				"第" + to_string(i) + "页,共" + size + "页。" +
				"左右键翻页,(y)选择图书" +
				",其余键取消");
			helper.Add("《" + string(title) + "》", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("作者:" + author);
			helper.Add("出版社:" + press);
			helper.Add("出版日期:" + date);
			helper.Add("类型:" + type);
			helper.Add();
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
			case 'y':
				ModifyBookByID(admin, id);
			default:
				return;
			}
		}
	}
}

void Show::FindBookByID(AdminHelper & admin)
{
	ID id;
	const char* title;
	const char* author;
	const char* press;
	const char* date;
	const char* type;
	string totalCount;
	string restCount;
	//bool  exist;
	while (true)
	{
		cout << "输入图书编号:";
		debug("正在获得书本信息，调用id = *it;title = user.GetBookTitle(*it);请按任意键");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
		debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
		id = GetID();
		title = admin.GetBookTitle(id);
		author = admin.GetBookAuthor(id);
		press = admin.GetBookPress(id);
		date = admin.GetBookDate(id);
		type = admin.GetBookType(id);
		totalCount = to_string(admin.GetBookTotalCount(id));
		restCount = to_string(admin.GetBookRestCount(id));
		//exist = user.GetBookExist(id);
		ShowHelper helper("", "");
		if (nullptr == title)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到该编号的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		Clear();
		debug("正在输出书籍信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("查找书籍", "按(c)继续,其余键返回");
		helper.Add("查找结果");
		helper.Add("《" + string(title) + "》", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("作者:" + string(author));
		helper.Add("出版社:" + string(press));
		helper.Add("出版日期:" + string(date));
		helper.Add("类型:" + string(type));
		helper.Add();
		helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
		/*if (exist)
		{
		helper.Add("在馆");
		}
		else
		{
		helper.Add("不在馆");
		}*/
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

void Show::FindBookByTitle(AdminHelper & admin)
{
	ShowHelper helper("", "");
	char str[32];
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		cout << "输入图书标题关键字:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有找到标题含\"" + string(str) + "\"的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear(),id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::FindBorrowedBooks(AdminHelper & admin)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		auto ids = admin.GetBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有借出的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear(),id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::FindNotBorrowedBooks(AdminHelper & admin)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		auto ids = admin.GetNotBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有未借出的书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		size = to_string(ids.size());
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear(),id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::FindAllBooks(AdminHelper & admin)
{
	ShowHelper helper("", "");
	string size;
	string title;
	string author;
	string press;
	string date;
	string type;
	string totalCount;
	string restCount;
	//bool exist;
	ID id;
	unsigned int i;
	while (true)
	{
		auto ids = admin.GetAllBooks();
		size = to_string(ids.size());
		if (0 == ids.size())
		{
			Clear();
			debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("查找书籍", "按(c)继续,其余键返回");
			helper.Add("没有书籍!");
			helper.Show();
			switch (GetCh())
			{
			case 'c':
				continue;
			default:
				return;
			}
		}
		auto it = ids.begin();
		i = 1;
		while (true)
		{
			Clear();
			debug("正在获得书本信息，调用清屏函数Clear(),id = *it;title = user.GetBookTitle(*it);请按任意键");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); 请按任意键");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));请按任意键");
			debug("restCount = to_string(user.GetBookRestCount(id)); 请按任意键");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("正在输出查询结果，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			helper.Add("在馆/总量:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("在馆");
			}
			else
			{
			helper.Add("不在馆");
			}*/
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
}

void Show::AddUser(AdminHelper & admin)
{
	ID id;
	char name[16];
	char password[32];
	int gender;
	int type;
	while (true)
	{
		debug("正在输出提示，若要进行下一步调试，请按任意键");
		cout << "输入用户编号:";
		id = GetID();
		cout << "输入用户名:";
		cin >> name;
		cout << "输入用户密码:";
		cin >> password;
		cout << "输入性别(1)男(2)女:";
		gender = GetUInt();
		cout << "输入类型(1)本科生(2)研究生(3)教师:";
		type = GetUInt();
		Clear();
		debug("正在输出提示，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		ShowHelper helper("添加用户", "");
		helper.Add("正在保存修改...");
		helper.Show();
		Clear();
		debug("正在输出信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("添加用户", "按(c)继续添加,其他键返回");
		if (!(admin.AddUser(id, name, password, gender, type) && admin.Save()))
		{
			helper.Add("保存失败!");
		}
		else
		{
			helper.Add("成功保存修改!"); helper.Add();
			helper.Add("已成功添加用户:" + string(name));
			helper.Add();
			helper.Add("编号:" + to_string(id));
			helper.Add("性别:" + string(admin.GetUserGender(id)));
			helper.Add("类型:" + string(admin.GetUserType(id)));
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

void Show::RemoveUser(AdminHelper & admin)
{
	ID id;
	cout << "输入用户ID:";
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("删除用户", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出用户信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出删除用户信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除用户", "");
			helper.Add("正在保存修改...");
			helper.Show();
			if (!(admin.RemoveUser(id) && admin.Save()))
			{
				Clear();
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("删除用户", "按任意键返回图书管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出取消信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("挂失", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出用户信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("挂失", "按任意键返回图书管理员菜单");
				helper.Add("挂失失败!");
				helper.Show();
				GetCh();
				return;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出取消信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("解除挂失", "按任意键返回图书管理员菜单");
		helper.Add("没有找到该用户!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出用户信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("解除挂失", "按任意键返回图书管理员菜单");
				helper.Add("解除挂失失败!");
				helper.Show();
				GetCh();
				return;
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出取消信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
	uid = GetID();
	cout << "输入书籍编号:";
	bookID=GetID();
	Clear();
	debug("正在输出提示，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	ShowHelper helper("还书", "");
	helper.Add("正在保存修改...");
	helper.Show();
	if (!(admin.Accept(uid, bookID) && admin.Save()))
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("还书", "按任意键返回图书管理员菜单");
		helper.Add("还书失败!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	helper.Reset("添加管理员", "按任意键返回图书管理员菜单");
	helper.Add("还书成功!");
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
		for (int i = 0; i < 32; i++)
		{
			oldpw[i] = GetCh();
			if (13== oldpw[i])
			{
				oldpw[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		//cin >> oldpw;
		if (admin.TestPassword(oldpw))
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
		for (int i = 0; i < 32; i++)
		{
			newpw[i] = GetCh();
			if (13 == newpw[i])
			{
				newpw[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		//cin >> oldpw;
		cout << "再次输入新密码:";
		//cin >> newpw2;
		for (int i = 0; i < 32; i++)
		{
			newpw2[i] = GetCh();
			if (13 == newpw2[i])
			{
				newpw2[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("更改密码", "按任意键继续");
		helper.Add("两次输入的密码不匹配!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	helper.Reset("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!admin.ChangePassword(oldpw, newpw))
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("更改密码", "按任意键返回图书管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
		//cin >> password;
		for (int i = 0; i < 32; i++)
		{
			password[i] = GetCh();
			if (13 == password[i])
			{
				password[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		if (root.Login(password))
		{
			break;
		}
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("普通用户登录", "按(q)返回主菜单,其余键重试!");
		helper.Add("密码错误!", ShowHelper::Center);
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
		Clear();
		debug("正在输出图书管理系统界面，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出信息，调用清屏函数Clear(),helper.Reset(),helper.Add()若要进行下一步调试，请按任意键");
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
	debug("正在输出提示信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	ShowHelper helper("添加管理员", "");
	helper.Add("正在保存修改...");
	helper.Show();
	if (!root.Save())
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("添加管理员", "按任意键返回系统管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
	id = GetID();
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
		helper.Add("没有找到该管理员!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出用户信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
			helper.Reset("删除管理员", "");
			helper.Add("正在保存修改...");
			helper.Show();
			if (!(root.RemoveAdmin(id) && root.Save()))
			{
				Clear();
				debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
				helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
				helper.Add("删除失败!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
			debug("正在输出取消信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
	id = GetID();
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("删除管理员", "按任意键返回系统管理员菜单");
		helper.Add("没有找到该管理员!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("正在输出查找管理员界面信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
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
		//cin >> oldpw;
		for (int i = 0; i < 32; i++)
		{
			oldpw[i] = GetCh();
			if (13 == oldpw[i])
			{
				oldpw[i] = '\0';
				break;
			}
			cout << "*";
		}
		cout << endl;
		if (root.TestPassword(oldpw))
		{
			break;
		}
		cout << "密码错误!" << endl;
	}
	cout << "输入新密码:";
	for (int i = 0; i < 32; i++)
	{
		oldpw[i] = GetCh();
		if (13 == oldpw[i])
		{
			oldpw[i] = '\0';
			break;
		}
		cout << "*";
	}
	//cout << endl;
	cin >> newpw;
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	ShowHelper helper("更改密码", "");
	helper.Add("正在保存...");
	helper.Show();
	if (!(root.ChangePassword(oldpw, newpw) && root.Save()))
	{
		Clear();
		debug("正在输出错误信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
		helper.Reset("更改密码", "按任意键返回系统管理员菜单");
		helper.Add("保存失败!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("正在输出成功信息，调用清屏函数Clear(),helper.Reset(),helper.Add()，helper.Show();若要进行下一步调试，请按任意键");
	helper.Reset("更改密码", "按任意键返回系统管理员菜单");
	helper.Add("保存成功!");
	helper.Add();
	helper.Add("已成功更改密码!");
	helper.Show();
	GetCh();
}


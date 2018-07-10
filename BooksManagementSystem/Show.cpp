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
		debug("���ڴ������棬���õ���Show::MainMenu()����Ҫ������һ�����ԡ��밴�����");
		helper.Reset("��ӭʹ��ͼ�����ϵͳ", "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ��ͨ�û�");
		helper.Add("(2)  ͼ�����Ա");
		helper.Add("(3)  ϵͳ����Ա");
		helper.Add("(0)  �� ��");
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
			helper.Reset("ͼ�����ϵͳ", "��������˳�");
			helper.Add("л л ʹ �� !", ShowHelper::Center);
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
		cout << "�û����:";
		uid = GetID();
		cout << "����:";
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
		debug("���ڽ����������֤������user.Login()����Ҫ������һ�����ԡ��밴�����");
		if (user.Login(uid, password))
		{
			break;
		}
		Clear();
		debug("�������������Ϣ������helper.Reset(),helper.Add()��helper.Show(),�ж��ַ��Ƿ�Ϊq,��Ҫ������һ�����ԡ��밴�����");
		helper.Reset("��ͨ�û���¼", "��(q)�������˵�,���������!");
		helper.Add("�û������������!", ShowHelper::Center);
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
	debug("����helper.Reset()��helper.Add()�����¼��Ϣ����Ҫ������һ�����ԡ��밴�����");
	helper.Reset(name + ",��ӭʹ��", "�����������");
	helper.Add("��¼�ɹ�", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("���ڴ����û����棬����helper.Reset������helper.Add������helper.Show()����Ҫ������һ�����ԡ��밴�����");
		helper.Reset("��ͨ�û�:" + name, "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ��ѯ�鼮");
		helper.Add("(2)  ����");
		helper.Add("(3)  ��ѯ������Ϣ");
		helper.Add("(4)  ��������");
		helper.Add("(0)  �� ��");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			Clear();
			debug("���ڴ��������鼮���棬ʹ��helper.Reset������helper.Add()��helper.Show()����Ҫ������һ�����ԡ��밴�����");
			helper.Reset("�����鼮", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ����ҷ�ʽ:");
			helper.Add();
			helper.Add("(1)  ���");
			helper.Add("(2)  ����");
			helper.Add("(3)  �н���鼮");
			helper.Add("(4)  �޽���鼮");
			helper.Add("(5)  ȫ���鼮");
			helper.Show();
			switch (GetCh())
			{
			case '1':
				debug("���ڽ�������ID���ң�����FindBookByID(user)����Ҫ������һ�����ԡ��밴�����");
				FindBookByID(user);
				break;
			case '2':
				debug("���ڽ����������Ʋ��ң�����FindBookByTitle(user);����Ҫ������һ�����ԡ��밴�����");
				FindBookByTitle(user);
				break;
			case '3':
				debug("���ڽ����н���鼮���ң�����FindBorrowedBooks(user)����Ҫ������һ�����ԡ��밴�����");
				FindBorrowedBooks(user);
				break;
			case '4':
				debug("���ڽ����޽���鼮���ң�����FindNotBorrowedBooks(user)����Ҫ������һ�����ԡ��밴�����");
				FindNotBorrowedBooks(user);
				break;
			case '5':
				debug("������ʾȫ���鼮������FindAllBooks(user)����Ҫ������һ�����ԡ��밴�����");
				FindAllBooks(user);
				break;
			default:
				break;
			}
			break;
			break;
		case '2':
			debug("���ڽ��������棬����BorrowBook(user)����Ҫ������һ�����ԡ��밴�����");
			BorrowBook(user);
			break;
		case '3':
			debug("���ڽ����ѯ������Ϣ���棬����GetBorrowInfo(user)����Ҫ������һ�����ԡ��밴�����");
			GetBorrowInfo(user);
			break;
		case '4':
			debug("���ڸ����������������ChangeUserPassword(user)����Ҫ������һ�����ԡ��밴�����");
			ChangeUserPassword(user);
			break;
		case '0':
			debug("���ڵ�����������Clear();helper.Clear(); ����Ҫ������һ�����ԡ��밴�����");
			Clear();
			helper.Clear();
			debug("�������������Ϣ������helper.SetHeader������helper.Add��������Ҫ������һ�����ԡ��밴�����");
			helper.SetHeader("�ټ�" + string(name), "��������������˵�");
			helper.Add("л л ʹ �� !", ShowHelper::Center);
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
		cout << "����ͼ����:";
		id = GetID();
		debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
		debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
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
			debug("���ڽ��д�����Ϣ���������helper.Reset������helper.Add��������������Clear(),��Ҫ������һ�����ԡ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ��ñ�ŵ��鼮!");
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
		debug("��������鱾��Ϣ�����ú�����helper.Reset(),helper.Add(),��������Clear(),��Ҫ������һ�����ԡ��밴�����");
		helper.Reset("�����鼮", "��(c)����,���������");
		helper.Add("���ҽ��");
		helper.Add("��" + string(title) + "��", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("����:" + string(author));
		helper.Add("������:" + string(press));
		helper.Add("��������:" + string(date));
		helper.Add("����:" + string(type));
		helper.Add();
		helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
		/*if (exist)
		{
			helper.Add("�ڹ�");
		}
		else
		{
			helper.Add("���ڹ�");
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
		cout << "����ͼ�����ؼ���:";
		cin >> str;
		auto ids = user.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset()��helper.Add(),helper.Show(),��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ����⺬\"" + string(str) + "\"���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("��������鱾��Ϣ������helper.Reset(),helper.Add(),helper.Show();����Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
				helper.Add("�ڹ�");
			}
			else
			{
				helper.Add("���ڹ�");
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
		debug("�����ж��Ƿ����Ȿ�飬����auto ids = user.GetBorrowedBooks();����Ҫ������һ�����ԣ��밴�����");
		auto ids = user.GetBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("�������������Ϣ��������������Clear()��helper.Reset(),helper.Add(),helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���н�����鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id)); 
			debug("��������鱾��Ϣ������helper.Reset()��helper.Add(),helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
		debug("�����ж��Ƿ����Ȿ�飬����auto ids = user.GetNotBorrowedBooks();����Ҫ������һ�����ԣ��밴�����");
		auto ids = user.GetNotBorrowedBooks();
		if (0 == ids.size())
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add,helper.Show()����Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û��δ������鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("��������鱾��Ϣ������helper.Reset()��helper.Add(),helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset()��helper.Add(),helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = user.GetBookTitle(*it);
			author = user.GetBookAuthor(*it);
			press = user.GetBookPress(*it);
			date = user.GetBookDate(*it);
			type = user.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(user.GetBookTotalCount(id));
			restCount = to_string(user.GetBookRestCount(id));
			debug("��������鱾��Ϣ������helper.Reset()��helper.Add(),helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
		cout << "����ͼ����:";
		debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
		debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ��ñ�ŵ��鼮!");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("�ñ�ŵ��鼮���ڹ���!");
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
			debug("����������Ľ��漰�鱾��Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ȷ�Ͻ����鼮", "(y)��------(n)��");
			helper.Add("ID:" + to_string(id));
			helper.Add();
			helper.Add("����:" + string(title));
			helper.Add("����:" + string(author));
			helper.Add("������:" + string(press));
			helper.Add("��������:" + string(date));
			helper.Add("����:" + string(type));
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			helper.Show();
			switch (GetCh())
			{
			case 'y':
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�����鼮", "��(c)����,���������");
				if (!(user.Borrow(id) && user.Save()))
				{
					helper.Add("����ʧ��");
				}
				else
				{
					helper.Add("����ɹ�");
				}
				helper.Add("ID:" + to_string(id));
				helper.Add();
				helper.Add("����:" + string(title));
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
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�����鼮", "��(c)����,���������");
				helper.Add("��ȡ������", ShowHelper::Center);
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
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��ѯ������Ϣ", "�������������һ���˵�");
		helper.Add("û�н�����Ϣ!");
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
		debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
		debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
		id = it->first;
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		borrowDate = it->second.ToString();
		returnDate = (it->second + 90).ToString();
		debug("��������鱾��Ϣ������helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("������Ϣ",
			"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
			"���Ҽ���ҳ" +
			",���������");
		helper.Add("��" + string(title) + "��", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("����:" + author);
		helper.Add("������:" + press);
		helper.Add("��������:" + date);
		helper.Add("����:" + type);
		helper.Add("�������:" + borrowDate);
		helper.Add("Ӧ������:" + returnDate);
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
		cout << "����ԭ����:";
		cin >> oldpw;
		if (user.TestPassword(oldpw))
		{
			break;
		}
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "��(c)����,���������");
		helper.Add("�������!");
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
		debug("���������ʾ����Ҫ������һ�����ԣ��밴�����");
		cout << "����������:";
		cin >> newpw;
		cout << "�ٴ�����������:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "�����������");
		helper.Add("������������벻ƥ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("���������ʾ��Ϣ����Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!user.ChangePassword(oldpw, newpw))
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "������������û��˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("���������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��������", "������������û��˵�");
	helper.Add("����ɹ�!");
	helper.Add();
	helper.Add("�ѳɹ���������!");
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
		debug("���������ʾ����Ҫ������һ�����ԣ��밴�����");
		cout << "���:";
		id = GetID();
		cout << "�û���:";
		cin >> name;
		cout << "����:";
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
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ͼ�����Ա��¼", "��(q)�������˵�,���������!");
		helper.Add("��Ż��û������������!", ShowHelper::Center);
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
	debug("����������棬������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
	helper.Reset((string)name + ",��ӭʹ��ͼ�����ϵͳ", "�����������");
	helper.Add("��¼�ɹ�", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("�������ͼ�����Ա���棬������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ͼ�����Ա:" + (string)name, "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  �����鼮");
		helper.Add("(2)  ɾ���鼮");
		helper.Add("(3)  �޸��鼮��Ϣ");
		helper.Add("(4)  ��ѯͼ��");
		helper.Add("(5)  ��Ӷ����û�");
		helper.Add("(6)  ɾ�������û�");
		helper.Add("(7)  ����֤��ʧ");
		helper.Add("(8)  ����֤�����ʧ");
		helper.Add("(9)  ��������");
		helper.Add("(a)  �� ��");
		helper.Add("(0)  �� ��");
		helper.Show();
		switch (GetCh())
		{
		case '1':
			AddBook(admin);
			break;
		case '2':
			Clear();
			debug("�������ɾ���鼮���棬������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���鼮", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ����ҷ�ʽ");
			helper.Add();
			helper.Add("(1)  ������ɾ��");
			helper.Add("(2)  �����ɾ��");
			helper.Add("(d)  ȫ��ɾ��");
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
			debug("��������޸ķ�ʽ��������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮��Ϣ", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ���޸ķ�ʽ");
			helper.Add();
			helper.Add("(1)  �������޸�");
			helper.Add("(2)  ������޸�");
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
			debug("���������ѯ���棬������������Clear(),helper.Reset(),helper.Add��helper.Show()��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ����ҷ�ʽ:");
			helper.Add();
			helper.Add("(1)  ���");
			helper.Add("(2)  ����");
			helper.Add("(3)  �н���鼮");
			helper.Add("(4)  �޽���鼮");
			helper.Add("(5)  ȫ���鼮");
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
			debug("���������Ϣ��������������Clear(),helper.SetHeader(),helper.Add()����Ҫ������һ�����ԣ��밴�����");
			helper.SetHeader("�ټ�" + string(name), "��������������˵�");
			helper.Add("л л ʹ �� !", ShowHelper::Center);
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
		debug("���������ʾ����Ҫ������һ�����ԣ��밴�����");
		cout << "������:";
		id = GetID();
		cout << "�������:";
		cin >> title;
		cout << "��������:";
		cin >> author;
		cout << "���������:";
		cin >> press;
		cout << "�����������:";
		cin >> date;
		cout << "��������:";
		cin >> type;
		cout << "��������:";
		number = GetUInt();
		admin.AddBook(id, title, author, press, date, type, number);
		Clear();
		debug("���������Ϣ��������������Clear(),helper.SetHeader(),helper.Add()����Ҫ������һ�����ԣ��밴�����");
		ShowHelper helper("����鼮", "");
		helper.Add("���ڱ����޸�...");
		helper.Show();
		Clear();
		debug("�����������鼮��Ϣ��������������Clear(),helper.Reset(),helper.Add()����Ҫ������һ�����ԣ��밴�����");
		helper.Reset("����鼮", "��(c)����,���������ͼ�����Ա�˵�");
		if (!admin.Save())
		{
			helper.Add("����ʧ��!");
		}
		else
		{
			helper.Add("�ɹ������޸�!");
			helper.Add();
			helper.Add("�ѳɹ����ͼ��:��" + string(title) + "��");
			helper.Add("���:" + to_string(id));
			helper.Add("����:" + string(author));
			helper.Add("������:" + string(press));
			helper.Add("��������:" + string(date));
			helper.Add("����:" + string(type));
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
		cout << "�����鼮���:";
		id = GetID();
		const char* title = admin.GetBookTitle(id);
		if (nullptr == admin.GetBookTitle(id))
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���鼮", "�����������ͼ�����Ա�˵�");
			helper.Add("û���ҵ����鼮!");
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
	debug("�������ɾ���鼮��Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("ɾ���鼮", "(y)��------(n)��");
	helper.Add("���:" + to_string(id));
	helper.Add();
	helper.Add("����:" + titleCopy);
	helper.Add("����:" + author);
	helper.Add("������:" + press);
	helper.Add("��������:" + date);
	helper.Add("����:" + type);
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':
			Clear();
			helper.Reset("ɾ���鼮", "");
			helper.Add("���ڱ����޸�...");
			helper.Show();
			if (!(admin.RemoveBook(id) && admin.Save()))
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("ɾ���鼮", "�����������ϵͳ����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("�������ɾ���鼮��Ϣ���鱾��Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���鼮", "�����������");
			helper.Add("�ɹ������޸�!");
			helper.Add();
			helper.Add("�ѳɹ�ɾ����" + titleCopy + "��");
			helper.Add();
			helper.Add("���:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���鼮", "�����������");
			helper.Add("��ȡ������!");
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
		cout << "����ͼ�����ؼ���:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���鼮", "��(c)����,���������");
			helper.Add("û���ҵ����⺬\"" + string(str) + "\"���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear()��id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ���������helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ,(y)ѡ��ͼ��" +
				",�����ȡ��");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
	debug("�������ɾ��ȫ���鼮��ȷ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	ShowHelper helper("ɾ��ȫ���鼮!!!", "��(y)ɾ��,���������");
	helper.Add("����", ShowHelper::Center);
	helper.Add();
	helper.Add("�⽫ɾ��ȫ���鼮!!!");
	helper.Add("ȷ��?");
	helper.Show();
	switch (GetCh())
	{
	case 'y':
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ɾ��ȫ���鼮", "�������������");
		if (!(admin.RemoveAllBooks() && admin.Save()))
		{
			helper.Add("ɾ��ʧ��!", ShowHelper::Center);
		}
		else
		{
			helper.Add("ɾ���ɹ�!", ShowHelper::Center);
		}
		helper.Show();
		GetCh();
		return;
	default:
		Clear();
		debug("�������ȡ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ɾ��ȫ���鼮", "�������������");
		helper.Add("��ȡ������!", ShowHelper::Center);
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
		cout << "�����鼮���:";
		id = GetID();
		if (nullptr == admin.GetBookTitle(id))
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������ͼ�����Ա�˵�");
			helper.Add("û���ҵ����鼮!");
			helper.Show();
			GetCh();
			return;
		}
	}
	while (true)
	{
		debug("���ڻ���鱾��Ϣ������id = *it;title = user.GetBookTitle(*it);�밴�����");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
		debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
		title = admin.GetBookTitle(id);
		author = admin.GetBookAuthor(id);
		press = admin.GetBookPress(id);
		date = admin.GetBookDate(id);
		type = admin.GetBookType(id);
		Clear();
		debug("��������޸��鼮��Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("�޸��鼮", "��ѡ�����ּ�ѡ���޸ĵ�����,��(q)����");
		helper.Add("���:" + to_string(id));
		helper.Add();
		helper.Add("ѡ���޸ĵ�����:");
		helper.Add("(1)  ����:" + string(title));
		helper.Add("(2)  ����:" + string(author));
		helper.Add("(3)  ������:" + string(press));
		helper.Add("(4)  ��������:" + string(date));
		helper.Add("(5)  ����:" + string(type));
		helper.Show();
		switch (GetCh())
		{
		case '1':
			cout << "�����±���:";
			cin >> str;
			if (!admin.SetBookTitle(id, str) && admin.Save())
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������");
			helper.Add("�޸ĳɹ���", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '2':
			cout << "����������:";
			cin >> str;
			if (!admin.SetBookAuthor(id, str) && admin.Save())
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������");
			helper.Add("�޸����߳ɹ���", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '3':
			cout << "�����³�����:";
			cin >> str;
			if (!admin.SetBookPress(id, str) && admin.Save())
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸ĳ�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������");
			helper.Add("�޸ĳ�����ɹ���", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '4':
			cout << "�����³�������:";
			cin >> str;
			if (!admin.SetBookDate(id, str) && admin.Save())
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸ĳ�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������");
			helper.Add("�޸ĳ�����ɹ���", ShowHelper::Center);
			helper.Show();
			GetCh();
			break;
		case '5':
			cout << "����������:";
			cin >> str;
			if (!admin.SetBookType(id, str) && admin.Save())
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�޸��鼮", "�����������");
			helper.Add("�޸����ͳɹ���", ShowHelper::Center);
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
		cout << "����ͼ�����ؼ���:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ����⺬\"" + string(str) + "\"���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear(),id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ�����������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ,(y)ѡ��ͼ��" +
				",�����ȡ��");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
		cout << "����ͼ����:";
		debug("���ڻ���鱾��Ϣ������id = *it;title = user.GetBookTitle(*it);�밴�����");
		debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
		debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
		debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ��ñ�ŵ��鼮!");
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
		debug("��������鼮��Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("�����鼮", "��(c)����,���������");
		helper.Add("���ҽ��");
		helper.Add("��" + string(title) + "��", ShowHelper::Center);
		helper.Add();
		helper.Add("ID:" + to_string(id));
		helper.Add("����:" + string(author));
		helper.Add("������:" + string(press));
		helper.Add("��������:" + string(date));
		helper.Add("����:" + string(type));
		helper.Add();
		helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
		/*if (exist)
		{
		helper.Add("�ڹ�");
		}
		else
		{
		helper.Add("���ڹ�");
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
		cout << "����ͼ�����ؼ���:";
		cin >> str;
		auto ids = admin.FindBookByTitle(str);
		if (ids.size() == 0)
		{
			Clear();
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���ҵ����⺬\"" + string(str) + "\"���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear(),id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			exist = admin.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ�����������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û�н�����鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear(),id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ�����������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û��δ������鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear(),id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ�����������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
			debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����鼮", "��(c)����,���������");
			helper.Add("û���鼮!");
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
			debug("���ڻ���鱾��Ϣ��������������Clear(),id = *it;title = user.GetBookTitle(*it);�밴�����");
			debug("author = user.GetBookAuthor(*it);press = user.GetBookPress(*it); �밴�����");
			debug("date = user.GetBookDate(*it);type = user.GetBookType(*it);totalCount = to_string(user.GetBookTotalCount(id));�밴�����");
			debug("restCount = to_string(user.GetBookRestCount(id)); �밴�����");
			id = *it;
			title = admin.GetBookTitle(*it);
			author = admin.GetBookAuthor(*it);
			press = admin.GetBookPress(*it);
			date = admin.GetBookDate(*it);
			type = admin.GetBookType(*it);
			//exist = user.GetBookExist(*it);
			totalCount = to_string(admin.GetBookTotalCount(id));
			restCount = to_string(admin.GetBookRestCount(id));
			debug("���������ѯ�����������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ѯ���",
				"��" + to_string(i) + "ҳ,��" + size + "ҳ��" +
				"���Ҽ���ҳ" +
				",���������");
			helper.Add("��" + string(title) + "��", ShowHelper::Center);
			helper.Add();
			helper.Add("ID:" + to_string(id));
			helper.Add("����:" + author);
			helper.Add("������:" + press);
			helper.Add("��������:" + date);
			helper.Add("����:" + type);
			helper.Add();
			helper.Add("�ڹ�/����:   " + restCount + "/" + totalCount);
			/*if (exist)
			{
			helper.Add("�ڹ�");
			}
			else
			{
			helper.Add("���ڹ�");
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
		debug("���������ʾ����Ҫ������һ�����ԣ��밴�����");
		cout << "�����û����:";
		id = GetID();
		cout << "�����û���:";
		cin >> name;
		cout << "�����û�����:";
		cin >> password;
		cout << "�����Ա�(1)��(2)Ů:";
		gender = GetUInt();
		cout << "��������(1)������(2)�о���(3)��ʦ:";
		type = GetUInt();
		Clear();
		debug("���������ʾ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		ShowHelper helper("����û�", "");
		helper.Add("���ڱ����޸�...");
		helper.Show();
		Clear();
		debug("���������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("����û�", "��(c)�������,����������");
		if (!(admin.AddUser(id, name, password, gender, type) && admin.Save()))
		{
			helper.Add("����ʧ��!");
		}
		else
		{
			helper.Add("�ɹ������޸�!"); helper.Add();
			helper.Add("�ѳɹ�����û�:" + string(name));
			helper.Add();
			helper.Add("���:" + to_string(id));
			helper.Add("�Ա�:" + string(admin.GetUserGender(id)));
			helper.Add("����:" + string(admin.GetUserType(id)));
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
	cout << "�����û�ID:";
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������û���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("ɾ���û�", "(y)��------(n)��");
	helper.Add("�û���:" + string(name));
	helper.Add();
	helper.Add("���:" + to_string(id));
	helper.Add("�Ա�:" + string(admin.GetUserGender(id)));
	helper.Add("����:" + string(admin.GetUserType(id)));
	helper.Show();
	string namecopy = name;
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			debug("�������ɾ���û���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���û�", "");
			helper.Add("���ڱ����޸�...");
			helper.Show();
			if (!(admin.RemoveUser(id) && admin.Save()))
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
			helper.Add("�ɹ������޸�!");
			helper.Add();
			helper.Add("�ѳɹ�ɾ���û�:");
			helper.Add(namecopy);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			debug("�������ȡ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
			helper.Add("��ȡ������!");
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
	cout << "�����û�ID:";
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������û���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��ʧ", "(y)��------(n)��");
	helper.Add("�û���:" + string(name));
	helper.Add();
	helper.Add("���:" + to_string(id));
	helper.Add("�Ա�:" + string(admin.GetUserGender(id)));
	helper.Add("����:" + string(admin.GetUserType(id)));
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			if (!(admin.ReportLoss(id) && admin.Save()))
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
				helper.Add("��ʧʧ��!");
				helper.Show();
				GetCh();
				return;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
			helper.Add("��ʧ�ɹ�!");
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
			debug("�������ȡ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
			helper.Add("��ȡ������!");
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
	cout << "�����û�ID:";
	id = GetID();
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("�����ʧ", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������û���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("�����ʧ", "(y)��------(n)��");
	helper.Add("�û���:" + string(name));
	helper.Add();
	helper.Add("���:" + to_string(id));
	helper.Add("�Ա�:" + string(admin.GetUserGender(id)));
	helper.Add("����:" + string(admin.GetUserType(id)));
	helper.Show();
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			if (!(admin.ReportLoss(id) && admin.Save()))
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("�����ʧ", "�����������ͼ�����Ա�˵�");
				helper.Add("�����ʧʧ��!");
				helper.Show();
				GetCh();
				return;
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("�����ʧ", "�����������ͼ�����Ա�˵�");
			helper.Add("�����ʧ�ɹ�!");
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
			debug("�������ȡ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
			helper.Add("��ȡ������!");
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
	cout << "�����û����:";
	uid = GetID();
	cout << "�����鼮���:";
	bookID=GetID();
	Clear();
	debug("���������ʾ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	ShowHelper helper("����", "");
	helper.Add("���ڱ����޸�...");
	helper.Show();
	if (!(admin.Accept(uid, bookID) && admin.Save()))
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("����", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��ӹ���Ա", "�����������ͼ�����Ա�˵�");
	helper.Add("����ɹ�!");
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
		cout << "����ԭ����:";
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
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "��(q)����,���������");
		helper.Add("�������!");
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
		cout << "����������:";
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
		cout << "�ٴ�����������:";
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
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "�����������");
		helper.Add("������������벻ƥ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!admin.ChangePassword(oldpw, newpw))
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��������", "�����������ͼ�����Ա�˵�");
	helper.Add("����ɹ�!");
	helper.Add();
	helper.Add("�ѳɹ���������!");
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
		cout << "����:";
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
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��ͨ�û���¼", "��(q)�������˵�,���������!");
		helper.Add("�������!", ShowHelper::Center);
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
		debug("�������ͼ�����ϵͳ���棬������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��ӭʹ��ͼ�����ϵͳ", "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ���ͼ�����Ա");
		helper.Add("(2)  ɾ��ͼ�����Ա");
		helper.Add("(3)  ����ͼ�����Ա");
		helper.Add("(4)  ��������");
		helper.Add("(0)  ע ��");
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
			debug("���������Ϣ��������������Clear(),helper.Reset(),helper.Add()��Ҫ������һ�����ԣ��밴�����");
			helper.SetHeader("�ټ�,ϵͳ����Ա", "��������˻����˵�");
			helper.Add("л л ʹ �� !", ShowHelper::Center);
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
	cout << "�����û���:";
	cin >> name;
	cout << "��������:";
	cin >> password;
	ID id = root.AddAdmin(name, password);
	Clear();
	debug("���������ʾ��Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	ShowHelper helper("��ӹ���Ա", "");
	helper.Add("���ڱ����޸�...");
	helper.Show();
	if (!root.Save())
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��ӹ���Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��ӹ���Ա", "�����������ϵͳ����Ա�˵�");
	helper.Add("�ɹ������޸�!");
	helper.Add();
	helper.Add("�ѳɹ���ӹ���Ա:");
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
	cout << "�������ԱID:";
	id = GetID();
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("û���ҵ��ù���Ա!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("��������û���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("ɾ������Ա", "(y)��------(n)��");
	helper.Add("ID:");
	helper.Add(to_string(id));
	helper.Add();
	helper.Add("�û���:");
	helper.Add(name);
	helper.Show();
	string namecopy = name;
	while (true)
	{
		switch (GetCh())
		{
		case 'y':Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ������Ա", "");
			helper.Add("���ڱ����޸�...");
			helper.Show();
			if (!(root.RemoveAdmin(id) && root.Save()))
			{
				Clear();
				debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
				helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
			debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
			helper.Add("�ɹ������޸�!");
			helper.Add();
			helper.Add("�ѳɹ�ɾ������Ա:");
			helper.Add(namecopy);
			helper.Add();
			helper.Add("ID:");
			helper.Add(to_string(id));
			helper.Show();
			GetCh();
			return;
		case 'n':
			Clear();
			debug("�������ȡ����Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
			helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
			helper.Add("��ȡ������!");
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
	cout << "�������ԱID:";
	id = GetID();
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("û���ҵ��ù���Ա!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("����������ҹ���Ա������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("���ҹ���Ա", "�����������ϵͳ����Ա�˵�");
	helper.Add("���ҽ��");
	helper.Add("ID:");
	helper.Add(to_string(id));
	helper.Add();
	helper.Add("�û���:");
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
		cout << "����ԭ����:";
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
		cout << "�������!" << endl;
	}
	cout << "����������:";
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
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	ShowHelper helper("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!(root.ChangePassword(oldpw, newpw) && root.Save()))
	{
		Clear();
		debug("�������������Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
		helper.Reset("��������", "�����������ϵͳ����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	debug("��������ɹ���Ϣ��������������Clear(),helper.Reset(),helper.Add()��helper.Show();��Ҫ������һ�����ԣ��밴�����");
	helper.Reset("��������", "�����������ϵͳ����Ա�˵�");
	helper.Add("����ɹ�!");
	helper.Add();
	helper.Add("�ѳɹ���������!");
	helper.Show();
	GetCh();
}


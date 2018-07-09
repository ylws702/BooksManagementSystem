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
		cin >> uid;
		cout << "����:";
		cin >> password;
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
	debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
	helper.Reset(name + ",��ӭʹ��", "�����������");
	helper.Add("��¼�ɹ�", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
		debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
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
			helper.Reset("�����鼮", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ����ҷ�ʽ:");
			helper.Add();
			helper.Add("(1)  ���");
			helper.Add("(2)  ����");
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
			debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
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
	cout << "����ͼ����:";
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
		debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
		helper.Reset("�����鼮", "�������������һ���˵�");
		helper.Add("û���ҵ��ñ�ŵ��鼮!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
	helper.Reset("�����鼮", "�������������һ���˵�");
	helper.Add("���ҽ��");
	helper.Add("��" + string(title) + "��", ShowHelper::Center);
	helper.Add();
	helper.Add("ID:" + to_string(id));
	helper.Add("����:" + string(author));
	helper.Add("������:" + string(press));
	helper.Add("��������:" + string(date));
	helper.Add("����:" + string(type));
	helper.Add();
	if (exist)
	{
		helper.Add("�ڹ�");
	}
	else
	{
		helper.Add("���ڹ�");
	}
	helper.Show();
	GetCh();
}

void Show::FindBookByTitle(UserHelper & user)
{
	char str[32];
	cout << "����ͼ�����ؼ���:";
	cin >> str;
	ShowHelper helper("", "");
	auto ids = user.FindBookByTitle(str);
	if (ids.size() == 0)
	{
		Clear();
		helper.Reset("�����鼮", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����⺬" + string(str) + "���鼮!");
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
		if (exist)
		{
			helper.Add("�ڹ�");
		}
		else
		{
			helper.Add("���ڹ�");
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
		cout << "����ͼ����:";
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
			helper.Reset("ȷ�Ͻ����鼮", "(y)��------(n)��");
			helper.Add("ID:" + to_string(id));
			helper.Add();
			helper.Add("����:" + string(title));
			helper.Add("����:" + string(author));
			helper.Add("������:" + string(press));
			helper.Add("��������:" + string(date));
			helper.Add("����:" + string(type));
			helper.Show();
			switch (GetCh())
			{
			case 'y':
				Clear();
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
				helper.Reset("�����鼮", "��(c)����,���������");
				helper.Add("��ȡ������",ShowHelper::Center);
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
		debug("���ڣ���Ҫ������һ�����ԡ��밴�����");
		id = it->first;
		title = user.GetBookTitle(id);
		author = user.GetBookAuthor(id);
		press = user.GetBookPress(id);
		date = user.GetBookDate(id);
		type = user.GetBookType(id);
		borrowDate = it->second.ToString();
		returnDate = (it->second + 90).ToString();
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
		cout << "����������:";
		cin >> newpw;
		cout << "�ٴ�����������:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		helper.Reset("��������", "�����������");
		helper.Add("������������벻ƥ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!user.ChangePassword(oldpw, newpw))
	{
		Clear();
		helper.Reset("��������", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("��������", "�����������ͼ�����Ա�˵�");
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
		cout << "���:";
		cin >> id;
		cout << "�û���:";
		cin >> name;
		cout << "����:";
		cin >> password;
		if (admin.Login(id, name, password))
		{
			break;
		}
		Clear();
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
	helper.Reset((string)name + ",��ӭʹ��ͼ�����ϵͳ", "�����������");
	helper.Add("��¼�ɹ�", ShowHelper::Center);
	helper.Show();
	GetCh();
	while (true)
	{
		Clear();
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
		helper.Add("(a)  ����");
		helper.Add("(0)  �� ��");
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
			helper.Reset("�����鼮", "ѡ�����ּ�ѡ��ʽ,���������");
			helper.Add("ѡ����ҷ�ʽ:");
			helper.Add();
			helper.Add("(1)  ���");
			helper.Add("(2)  ����");
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
	while (true)
	{
		ID id;
		char title[32];
		char author[32];
		char press[32];
		char date[32];
		char type[32];
		cout << "������:";
		cin >> id;
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
		admin.AddBook(id, title, author, press, date, type);
		Clear();
		ShowHelper helper("����鼮", "");
		helper.Add("���ڱ����޸�...");
		helper.Show();
		Clear();
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

void Show::RemoveBook(AdminHelper & admin)
{
	ID id;
	cout << "�����鼮���:";
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
		helper.Reset("ɾ���鼮", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����鼮!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("ɾ���鼮", "(y)��------(n)��");
	helper.Add("���:" + to_string(id));
	helper.Add();
	helper.Add("����:" + string(title));
	helper.Add("����:" + string(author));
	helper.Add("������:" + string(press));
	helper.Add("��������:" + string(date));
	helper.Add("����:" + string(type));
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
				helper.Reset("ɾ���鼮", "�����������ϵͳ����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
			helper.Reset("ɾ���鼮", "�����������ϵͳ����Ա�˵�");
			helper.Add("�ɹ������޸�!");
			helper.Add();
			helper.Add("�ѳɹ�ɾ����" + title + "��");
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
			helper.Reset("ɾ���鼮", "�����������ϵͳ����Ա�˵�");
			helper.Add("��ȡ������!");
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
	cout << "�����鼮���:";
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
		helper.Reset("�޸��鼮", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����鼮!");
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
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
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
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
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
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸ĳ�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
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
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸ĳ�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
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
				helper.Reset("�޸��鼮", "�����������");
				helper.Add("�޸�����ʧ�ܣ�", ShowHelper::Center);
				GetCh();
				continue;
			}
			Clear();
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

void Show::FindBookByID(AdminHelper & admin)
{
	ID id;
	cout << "����ͼ����:";
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
		helper.Reset("�����鼮", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ��ñ�ŵ��鼮!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("�����鼮", "�����������ͼ�����Ա�˵�");
	helper.Add("���ҽ��");
	helper.Add("��" + string(title) + "��", ShowHelper::Center);
	helper.Add();
	helper.Add("ID:" + to_string(id));
	helper.Add("����:" + string(author));
	helper.Add("������:" + string(press));
	helper.Add("��������:" + string(date));
	helper.Add("����:" + string(type));
	helper.Add();
	if (exist)
	{
		helper.Add("�ڹ�");
	}
	else
	{
		helper.Add("���ڹ�");
	}
	helper.Show();
	GetCh();
}

void Show::FindBookByTitle(AdminHelper & admin)
{
	char str[32];
	cout << "����ͼ�����ؼ���:";
	cin >> str;
	ShowHelper helper("", "");
	auto ids = admin.FindBookByTitle(str);
	if (ids.size() == 0)
	{
		Clear();
		helper.Reset("�����鼮", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����⺬" + string(str) + "���鼮!");
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
		if (exist)
		{
			helper.Add("�ڹ�");
		}
		else
		{
			helper.Add("���ڹ�");
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
	cout << "�����û����:";
	cin >> id;
	cout << "�����û���:";
	cin >> name;
	cout << "�����û�����:";
	cin >> password;
	cout << "�����Ա�(1)��(2)Ů:";
	cin >> gender;
	cout << "��������(1)������(2)�о���(3)��ʦ:";
	cin >> type;

	Clear();
	ShowHelper helper("����û�", "");
	helper.Add("���ڱ����޸�...");
	helper.Show();
	if (!(admin.AddUser(id, name, password, gender, type) && admin.Save()))
	{
		Clear();
		helper.Reset("��ӹ���Ա", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("��ӹ���Ա", "�����������ͼ�����Ա�˵�");
	helper.Add("�ɹ������޸�!");
	helper.Add();
	helper.Add("�ѳɹ�����û�:" + string(name));
	helper.Add();
	helper.Add("���:" + to_string(id));
	helper.Add("�Ա�:" + string(admin.GetUserGender(id)));
	helper.Add("����:" + string(admin.GetUserType(id)));
	helper.Show();
	GetCh();
}

void Show::RemoveUser(AdminHelper & admin)
{
	ID id;
	cout << "�����û�ID:";
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
			helper.Reset("ɾ���û�", "");
			helper.Add("���ڱ����޸�...");
			helper.Show();
			if (!(admin.RemoveUser(id) && admin.Save()))
			{
				Clear();
				helper.Reset("ɾ���û�", "�����������ͼ�����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
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
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
				helper.Reset("��ʧ", "�����������ͼ�����Ա�˵�");
				helper.Add("��ʧʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
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
	cin >> id;
	const char* name = admin.GetUserName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("�����ʧ", "�����������ͼ�����Ա�˵�");
		helper.Add("û���ҵ����û�!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
				helper.Reset("�����ʧ", "�����������ͼ�����Ա�˵�");
				helper.Add("�����ʧʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
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
	cin >> uid;
	cout << "�����鼮���:";
	cin >> bookID;
	Clear();
	ShowHelper helper("����", "");
	helper.Add("���ڱ����޸�...");
	helper.Show();
	if (!(admin.Accept(uid, bookID) && admin.Save()))
	{
		Clear();
		helper.Reset("����", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
	helper.Reset("��ӹ���Ա", "�����������ͼ�����Ա�˵�");
	helper.Add("�ɹ������޸�!");
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
		cin >> oldpw;
		if (admin.TestPassword(oldpw))
		{
			break;
		}
		Clear();
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
		cin >> newpw;
		cout << "�ٴ�����������:";
		cin >> newpw2;
		if (strcmp(newpw, newpw2) == 0)
		{
			break;
		}
		Clear();
		helper.Reset("��������", "�����������");
		helper.Add("������������벻ƥ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!admin.ChangePassword(oldpw, newpw))
	{
		Clear();
		helper.Reset("��������", "�����������ͼ�����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
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
		cin >> password;
		if (root.Login(password))
		{
			break;
		}
		Clear();
		helper.Reset("��ӭʹ��ͼ�����ϵͳ", "�����������!");
		helper.Add("�������!", ShowHelper::Center);
		helper.Show();
		GetCh();
	}
	while (true)
	{
		Clear();
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
	ShowHelper helper("��ӹ���Ա", "");
	helper.Add("���ڱ����޸�...");
	helper.Show();
	if (!root.Save())
	{
		Clear();
		helper.Reset("��ӹ���Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
	cin >> id;
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("û���ҵ��ù���Ա!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
			helper.Reset("ɾ������Ա", "");
			helper.Add("���ڱ����޸�...");
			helper.Show();
			if (!(root.RemoveAdmin(id) && root.Save()))
			{
				Clear();
				helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
				helper.Add("ɾ��ʧ��!");
				helper.Show();
				GetCh();
			}
			Clear();
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
	cin >> id;
	const char* name = root.GetAdminName(id);
	ShowHelper helper("", "");
	if (nullptr == name)
	{
		Clear();
		helper.Reset("ɾ������Ա", "�����������ϵͳ����Ա�˵�");
		helper.Add("û���ҵ��ù���Ա!");
		helper.Show();
		GetCh();
		return;
	}
	Clear();
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
		cin >> oldpw;
		if (root.TestPassword(oldpw))
		{
			break;
		}
		cout << "�������!" << endl;
	}
	cout << "����������:";
	cin >> newpw;
	Clear();
	ShowHelper helper("��������", "");
	helper.Add("���ڱ���...");
	helper.Show();
	if (!(root.ChangePassword(oldpw, newpw) && root.Save()))
	{
		Clear();
		helper.Reset("��������", "�����������ϵͳ����Ա�˵�");
		helper.Add("����ʧ��!");
		helper.Show();
		GetCh();
	}
	Clear();
	helper.Reset("��������", "�����������ϵͳ����Ա�˵�");
	helper.Add("����ɹ�!");
	helper.Add();
	helper.Add("�ѳɹ���������!");
	helper.Show();
	GetCh();
}


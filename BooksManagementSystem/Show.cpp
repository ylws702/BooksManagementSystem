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
		helper.Reset("��ӭʹ��ͼ�����ϵͳ", "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ��ͨ�û�");
		helper.Add("(2)  ͼ�����Ա");
		helper.Add("(3)  ϵͳ����Ա");
		helper.Add("(0)  �� ��");
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
	Clear();
	UserHelper user;
	char username[16], password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		cout << "�û���:";
		cin >> username;
		cout << "����:";
		cin >> password;
		if (!user.Login(username, password))
		{
			Clear();
			helper.Reset("��ӭ����ʹ��ͼ�����ϵͳ", "�����������!");
			helper.Add("�û������������!", ShowHelper::Center);
			helper.Show();
			GetCh();
		}
	}
	while (true)
	{
		Clear();
		helper.Reset("��ӭ����ʹ��ͼ�����ϵͳ", "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ��ѯ�鼮��Ϣ");
		helper.Add("(2)  ��ѯ������Ϣ");
		helper.Add("(3)  �޸ĵ�¼����");
		helper.Add("(0)  �� ��");
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
			helper.SetHeader("ͼ�����ϵͳ", "��������˳�");
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

void Show::AdminMenu()
{
	Clear();
	UserHelper user;
	char username[16], password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
		cout << "�û���:";
		cin >> username;
		cout << "����:";
		cin >> password;
		if (!user.Login(username, password))
		{
			Clear();
			helper.Reset("��ӭ����ʹ��ͼ�����ϵͳ", "�����������!");
			helper.Add("�û������������!", ShowHelper::Center);
			helper.Show();
			GetCh();
		}
	}
	while (true)
	{
		Clear();
		helper.Reset("��ӭ����ʹ��ͼ�����ϵͳ", "��ѡ�����ּ�ѡ����Ӧ�ķ���");
		helper.Add("(1)  ��ѯ�鼮��Ϣ");
		helper.Add("(2)  ��ѯ������Ϣ");
		helper.Add("(3)  �޸ĵ�¼����");
		helper.Add("(0)  �� ��");
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
			helper.SetHeader("ͼ�����ϵͳ", "��������˳�");
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

void Show::RootMenu()
{
	Clear();
	RootHelper root;
	char password[32];
	ShowHelper helper("", "");
	while (true)
	{
		Clear();
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
		helper.Add("(0)  ע ��");
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
			helper.SetHeader("����ע��", "��������˻����˵�");
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


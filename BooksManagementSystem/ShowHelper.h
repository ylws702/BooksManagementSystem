#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class ShowHelper
{
public:
	//ɾ��Ĭ�Ϲ��캯��
	ShowHelper() = delete;
	//************************************
	// ������ : ShowHelper
	// ��  �� : 
	// ��  �� : const string & header : 
	// ��  �� : const string & footer : 
	//************************************
	ShowHelper(const string& header = "", const string&footer = "");
	//���뷽ʽ
	enum Alignment
	{
		//���ж���
		Center,
		//�����
		Left
	};
	//����̨���ڿ��
	static const int width{ 72 };
	//����̨���ڸ߶�
	static const int height{ 20 };
	//����̨ˮƽ�߾�
	static const int marginH{ 4 };
	//����̨��ֱ�߾�
	static const int marginV{ 2 };
	//************************************
	// ������ : Header
	// ��  �� : ��str���в���fill���
	// ����ֵ : std::string : ���д�����ַ����ַ���
	// ��  �� : const string & str : Ҫ������ַ���
	// ��  �� : const char fill : �����ַ�
	//************************************
	static string Header(const string& str, const char fill = '-');
	//************************************
	// ������ : ToCenter
	// ��  �� : ��str���в���marginH�����margin
	// ����ֵ : std::string : ���в��ڱ߾ദ���߿��ַ����ַ���
	// ��  �� : const string & str : Ҫ������ַ���
	// ��  �� : const char margin : �߿��ַ�
	//************************************
	static string ToCenter(const string& str, const char margin = '|');
	//************************************
	// ������ : ToLeft
	// ��  �� : ��str����������߿�left����marginH�����margin
	// ����ֵ : std::string : ����벢�ڱ߾ദ���߿��ַ����ַ���
	// ��  �� : const string & str : Ҫ������ַ���
	// ��  �� : const unsigned int left : ����߿�ľ���
	// ��  �� : const char margin : �߿��ַ�
	//************************************
	static string ToLeft(const string& str, const unsigned int left = 4, const char margin = '|');
	//************************************
	// ������ : Add
	// ��  �� : �������������һ�����봦����ַ���
	// ��  �� : const string & str : Ҫ��ӵ�����
	// ��  �� : const Alignment alignment : ���뷽ʽ
	//************************************
	void Add(const string& str = "", const Alignment alignment = Left);
	//************************************
	// ������ : SetHeader
	// ��  �� : ����ҳü��ҳ��
	// ��  �� : const string & header : Ҫ���õ�ҳü
	// ��  �� : const string & footer : Ҫ���õ�ҳ��
	//************************************
	void SetHeader(const string& header = "", const string&footer = "");
	//************************************
	// ������ : Reset
	// ��  �� : ������õ�����,����������ҳü��ҳ��
	// ��  �� : const string & header : Ҫ�������õ�ҳü
	// ��  �� : const string & footer : Ҫ�������õ�ҳ��
	//************************************
	void Reset(const string& header = "", const string&footer = "");
	//************************************
	// ������ : Show
	// ��  �� : ��ӡ��ʽ��֮����ַ�������
	//************************************
	void Show()const;
	//************************************
	// ������ : Normalize
	// ��  �� : ���Ѿ����ñ�ͷ�������ַ����������и�ʽ��
	// ����ֵ : std::vector<std::string> : ��ʽ������ַ�������
	//************************************
	vector<string> Normalize()const;
	//************************************
	// ������ : Clear
	// ��  �� : ����Ѿ����õı�ͷ������
	//************************************
	void Clear();
private:
	//����
	vector<pair<string, Alignment>> strs;
	//ҳü
	string header;
	//ҳ��
	string footer;
};


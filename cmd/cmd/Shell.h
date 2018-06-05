#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
using namespace std;
class Shell
{
public:
	Shell();
	~Shell();

	bool RunProcess(LPWSTR process);
	bool StopProcess();
	bool GetOutput(const string &endStr, int timeout, string &outstr);//��ȡ����ַ���  
	bool SetInput(const string &cmd);//ִ������ 
	Shell(LPWSTR process);
private:
	HANDLE m_hChildInputWrite;  //���ڸ��������ӽ��̷������� 
	HANDLE m_hChildInputRead;	//�����ӽ��̶��븸���̷��͵����ݵľ��
	HANDLE m_hChildOutputWrite; //�����ӽ����򸸽��̷�������  
	HANDLE m_hChildOutputRead;//���ڸ����̶�ȡ�ӽ��̷��͵�����
	PROCESS_INFORMATION m_cmdPI;//cmd������Ϣ  
};
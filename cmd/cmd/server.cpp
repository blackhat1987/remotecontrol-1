#include <stdio.h>
#include <winsock2.h>    
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")    

int main(int argc, char* argv[])
{
	//初始化WSA    
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字    
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		//printf("socket error !");
		return 0;
	}

	//绑定IP和端口    
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听    
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//循环接收数据    
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[5000];
	char sendData[100];
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	struct SIZE {
		int len;
		BYTE end;
	};
	if (sClient == INVALID_SOCKET)
	{
		printf("accept error !");
	}
	ZeroMemory(revData, 5000);
	int ret = recv(sClient, revData, 5000, 0);
	revData[ret] = 0x00;
	printf(revData);
		while (true)
		{



			//接收数据 
			
			if (ret > 0)
			{
				
				cin.getline(sendData, 100);
				send(sClient, sendData, strlen(sendData) + 1, 0);
				if (!strcmp(sendData, "000")) {
					break;
				}else if (sendData[0] == 'm'&sendData[1] == 'y'&sendData[2] == 'm') {
					ZeroMemory(revData, 5000);
					ret = recv(sClient, revData, 5000, 0);
					/*SIZE* s;
					s = (SIZE*)revData;
					PCHAR rb = new CHAR[s->len];

					recv(sClient, rb, s->len, 0);
					ofstream f1(&sendData[4],ios::binary);
					f1.write(rb, s->len);
					cout << hex<<s->len << endl;
			
					f1.close();

					delete[]rb;
					cout << "copy success!" << endl;
					cin.getline(sendData, 100);
					send(sClient, sendData, strlen(sendData) + 1, 0);*/
					DWORD* fsize = (DWORD*)revData;
					HANDLE hFile = CreateFileA(&sendData[4], GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					ret = recv(sClient, revData, 5000, 0);
					while (strcmp(revData,"gover")) {
						
						WriteFile(hFile, revData, ret, NULL, NULL);
						cout << revData <<"***"<< endl;
						ret = recv(sClient, revData, 5000, 0);
					}
					cout << "recv over!" << endl;
					CloseHandle(hFile);
			
				}
				else {
					ZeroMemory(revData, 5000);
					int ret = recv(sClient, revData, 5000, 0);
					revData[ret] = 0x00;
					printf(revData);
				}
				
			}

			//发送数据    



		}
	

		closesocket(sClient);
		closesocket(slisten);
		WSACleanup();

	return 0;
}
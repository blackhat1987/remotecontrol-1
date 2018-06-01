#include <stdio.h>
#include <winsock2.h>    
#include<string>
#include<iostream>
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
	if (sClient == INVALID_SOCKET)
	{
		printf("accept error !");
	}
	
		while (true)
		{



			//接收数据    
			int ret = recv(sClient, revData, 5000, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				printf(revData);
				cin.getline(sendData, 100);
				send(sClient, sendData, strlen(sendData) + 1, 0);
				if (!strcmp(sendData, "000")) {
					break;
				}
				
			}

			//发送数据    



		}
	

		closesocket(sClient);
		closesocket(slisten);
		WSACleanup();

	return 0;
}
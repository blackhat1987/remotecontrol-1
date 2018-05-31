#pragma once
#pragma comment (lib,"ws2_32.lib") 
#include<WinSock2.h>
#include<string>
#include<iostream>
using namespace std;
class MySocket
{
public:
	MySocket();
	~MySocket();
	bool SocketInit(const string ipaddr, unsigned short port);
	bool SocketSend(const string sendbuf) const;
	bool SocketRecv(string & recvbuf);
private:
	SOCKET sockClient;
	SOCKADDR_IN addrClient;
};


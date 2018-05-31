#include "MySocket.h"



MySocket::MySocket() = default;



MySocket::~MySocket()
{
	closesocket(sockClient);
	WSACleanup();
}
bool MySocket::SocketInit(const string ipaddr,unsigned short port) {
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData)) {
		return false;
	}
	/*if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return false;
	}*/
	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrClient.sin_addr.S_un.S_addr = inet_addr(ipaddr.c_str());
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port);
	if (connect(sockClient, (sockaddr *)&addrClient, sizeof(addrClient)) == SOCKET_ERROR)
	{  //¡¨Ω” ß∞‹   
		printf("connect error !");
		closesocket(sockClient);
		return 0;
	}
	return TRUE;
}
bool MySocket::SocketSend(const string sendbuf)const {
	send(sockClient, sendbuf.c_str(), sendbuf.size(), 0);
	return true;
}
bool MySocket::SocketRecv(string & recvbuf) {
	CHAR BUF[100];
	int rec=recv(sockClient, BUF, 100, 0);
	recvbuf = BUF;
	return true;
}
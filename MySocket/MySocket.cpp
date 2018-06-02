#include "MySocket.h"



MySocket::MySocket() = default;



MySocket::~MySocket()
{
	closesocket(sockClient);
	WSACleanup();
}
bool MySocket::SocketInit(const string ipaddr,unsigned short port, bool flag) {
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData)) {
		return false;
	}
	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrClient.sin_addr.S_un.S_addr = inet_addr(ipaddr.c_str());
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port);
	if (flag) {
		if (bind(sockClient, (LPSOCKADDR)&addrClient, sizeof(addrClient) == SOCKET_ERROR)) {
			return false;
		}
		/*������*/
	}
	else {
		if (connect(sockClient, (sockaddr *)&addrClient, sizeof(addrClient)) == SOCKET_ERROR)
		{  //����ʧ��   
			printf("connect error !");
			closesocket(sockClient);
			return 0;
		}
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
bool MySocket::SocketSendF(string &filename) {
	ifstream f1;
	f1.open(filename,ios::binary|ios::in);
	struct SIZE {
		int len;
		BYTE end;
	};
	SIZE s = {0,0};
	f1.seekg(0, ios::end);
	int axx=0;
	s.len= f1.tellg();
	s.len++;
	s.end = '\0';
	cout << s.len << endl;
	cout << s.end << endl;
	f1.seekg(0, ios::beg);
	PCHAR buffer = new CHAR[s.len];
	f1.read(buffer, s.len);
	f1.close();
	
	send(sockClient, (CHAR*)&s, sizeof SIZE, 0);
	send(sockClient, buffer, s.len, 0);
	delete[]buffer;
	return true;
}
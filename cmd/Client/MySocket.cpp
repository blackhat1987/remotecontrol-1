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
		/*服务器*/
	}
	else {
		if (connect(sockClient, (sockaddr *)&addrClient, sizeof(addrClient)) == SOCKET_ERROR)
		{  //连接失败   
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
	//ifstream f1;
	//f1.open(filename,ios::binary|ios::in);
	//struct SIZE {
	//	int len;
	//	BYTE end;
	//};
	//SIZE s = {0,0};
	//f1.seekg(0, ios::end);
	//int axx=0;
	//s.len= f1.tellg();
	//s.len++;
	//s.end = '\0';
	//cout << s.len << endl;
	//cout << s.end << endl;
	//f1.seekg(0, ios::beg);
	//PCHAR buffer = new CHAR[s.len];
	//f1.read(buffer, s.len);
	//f1.close();
	//
	//send(sockClient, (CHAR*)&s, sizeof SIZE, 0);
	//send(sockClient, buffer, s.len, 0);
	//delete[]buffer;
	//return true;
	HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//以共享读写的方式打开
	CHAR buffer[5000] = { 0 };//每次发送的大小，取500字节
	DWORD fsize = GetFileSize(hFile, NULL);
	cout << fsize << endl;
	send(sockClient, (char *)&fsize, sizeof DWORD, 0);
	DWORD k = 0,r=0;
	while (k < fsize) {
		ReadFile(hFile, buffer, 5000, &r, NULL);
		k += r;
		send(sockClient, buffer, r, 0);
		cout << buffer << "***"<<endl;
	}
	send(sockClient, "gover\0", 6, 0);
	cout << "Send over!" << endl;
	CloseHandle(hFile);
	return true;
}
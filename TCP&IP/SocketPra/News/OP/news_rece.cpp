#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#define BUF_SIZE 1024
#pragma comment(lib,"ws2_32.lib")
void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;

	SOCKET hRecvSock;
	SOCKADDR_IN adr;
	int strLen,iRet;
	ip_mreq joinAdr;

	char buf[BUF_SIZE];

	

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hRecvSock = socket(PF_INET, SOCK_DGRAM, 0);
	if (hRecvSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = INADDR_ANY;
	adr.sin_port = htons(9433);

	bool bOptval = true;

	iRet = setsockopt(hRecvSock, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptval, sizeof(bOptval));
	if (iRet != 0) {

		printf("1setsockopt fail:%d", WSAGetLastError());
		system("pause");
		return -1;
	}
	iRet = bind(hRecvSock, (sockaddr*)&adr, sizeof(adr));
	if (iRet != 0) {

		printf("bind fail:%d", WSAGetLastError());
		system("pause");
		return -1;
	}
	
	//加入多播组，多播使用D类IP地址
	joinAdr.imr_interface.s_addr = INADDR_ANY;
	joinAdr.imr_multiaddr.s_addr = inet_addr("234.2.3.3");
	

	iRet = setsockopt(hRecvSock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&joinAdr, sizeof(joinAdr));
	if (iRet != 0) {

		printf("2setsockopt fail:%d", WSAGetLastError());
		system("pause");
		return -1;
	}
	//接受多播信息
	while (true)
	{
		strLen = recvfrom(hRecvSock, buf, BUF_SIZE - 1, 0, NULL, 0);
		if (strLen < 0)
			break;
		buf[strLen] = 0;
		fputs(buf, stdout);
	}

	closesocket(hRecvSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	system("pause");
	fputc('\n', stderr);
	exit(1);
}

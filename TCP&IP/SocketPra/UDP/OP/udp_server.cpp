#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <unistd.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 1024
void ErrorHandling(const char *message);

int main22(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock ,clntSock;
	SOCKADDR_IN servAddr, clntAddr;
	socklen_t szClntAddr;
	FILE * fp;
	int readCnt;
	int strLen;
	char message[BUF_SIZE];


	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		system("pause");
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	fp = fopen("D:\\EXE\\close\\file_server_win.c", "rb");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("UDP socket() creation error");

	memset(&servAddr, 0, sizeof(servAddr));
	//自动获取服务端ip地址，
	//同一计算机可以有多个IP地址，取决于NIC数量（网卡），
	//INADDR_ANY可以获取所有的该服务端计算机的IP
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	//if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR_IN) == SOCKET_ERROR))
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	szClntAddr = sizeof(clntAddr);

	listen(hServSock, 5);
	clntSock = accept(hServSock, (SOCKADDR *)&clntAddr, &szClntAddr);
	
	// 把一个文件里的东西读出来，发给客户端，关闭输出流后，接受客户端的thanks
	while (true)
	{
		readCnt = fread((void *)message, 1, BUF_SIZE, fp);
		printf("readCnt is %d\n", readCnt);
		if (readCnt < BUF_SIZE)
		{
			send(clntSock, message, readCnt, 0);
			break;
		}
		send(clntSock, message, BUF_SIZE, 0);
	}
	shutdown(clntSock, SD_RECEIVE);
	recv(clntSock, message, BUF_SIZE, 0);
	printf("Message from client:%s \n", message);
	
	fclose(fp);
	closesocket(clntSock);
	closesocket(hServSock);
	WSACleanup();
	system("pause");

	return 0;
}
void ErrorHandling(const char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(1);
}

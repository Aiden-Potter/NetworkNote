#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <unistd.h>                                                                                                  m
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 1024
void ErrorHandling(const char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;

	TIMEVAL timeout;
	fd_set reads, cpyReads;

	int adrSz;
	int strLen, fdNum ,i;
	char buf[BUF_SIZE];

	if (argc != 2){
		printf("Usage : %s <port>\n",argv[0]);
		system("pause");
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup Error");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1])); 

	//servAdr.sin_port = htons(9090);
	if (bind(hServSock, (SOCKADDR *)&servAdr, sizeof(servAdr)))
		ErrorHandling("bind error");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen error");

	FD_ZERO(&reads);// 0 
	FD_SET(hServSock, &reads);

	while (true)
	{
		cpyReads = reads;//十分重要，select会改变cpyReads的值，每次循环都要更新
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;
		
		if ((fdNum = select(0, &cpyReads, 0, 0, &timeout)) == SOCKET_ERROR)
			break;

		if (fdNum == 0)
			continue;

		for (i = 0; i < reads.fd_count; ++i)
		{
			if (FD_ISSET(reads.fd_array[i], &cpyReads)) {
				if (reads.fd_array[i] == hServSock)
				{
					adrSz = sizeof(clntAdr);
					hClntSock = accept(hServSock, (SOCKADDR *)&clntAdr, &adrSz);
					FD_SET(hClntSock, &reads);
					printf("connected client: %d \n", hClntSock);
				}
				else {
					strLen = recv(reads.fd_array[i], buf, BUF_SIZE - 1, 0);
					if (strLen == 0)
					{
						printf("time wait1");
						FD_CLR(reads.fd_array[i], &reads);
						closesocket(cpyReads.fd_array[i]);
						printf("closed client:%d \n", cpyReads.fd_array[i]);
					}
					else
					{
						printf("time wait2");
						send(reads.fd_array[i], buf, strLen, 0);
					}
				}
			}
		}
	}

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

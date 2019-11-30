#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#define BUF_SIZE 1024
void ErrorHandling(const char* message);

int main2(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
	FILE * fp;
	char message[BUF_SIZE];
	int strLen = 0,readCnt;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	
	fp = fopen("D:\\EXE\\close\\flie.dat", "wb");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);//inet_addr将点分10进制转化成32位整型，127.0.0.1是回送地址，指计算机本身ip
	servAddr.sin_port = htons(atoi(argv[2]));//端口号相同

	if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
	{
		puts("Connected...............");
	}
	//connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr));

	while ((readCnt = recv(hSocket, message, BUF_SIZE, 0)) != 0)
		fwrite((void *)message, 1, readCnt, fp);
	puts("Received file data！");
	send(hSocket, "Thanks!", 8,0);
	fclose(fp);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

//void ErrorHandling(const char* message)
//{
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}

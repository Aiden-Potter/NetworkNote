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

	char message[BUF_SIZE];
	int strLen = 0, recvLen = 0, recvCnt = 0;
	int result=0;
	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);//inet_addr将点分10进制转化成32位整型，127.0.0.1是回送地址，指计算机本身ip
	//InetPton(AF_INET, argv[1], &servAddr.sin_addr);
	//InetPton(AF_INET, argv[1], &servAddr.sin_addr.S_un.S_addr);
		//inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));//端口号相同

	if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		//connect后要等待服务器accept
		ErrorHandling("connect() error!");
	else
	{
		puts("Connected...............");
	}

	while (true)
	{
		fputs("Input number of cal: ", stdout);
		fgets(message, BUF_SIZE, stdin);

		send(hSocket, message, strlen(message), 0);
		int n = atoi(message);
		recvLen = 0;
		for (int i = 0; i < n; ++i)
		{
			fputs("Input number:", stdout);
			fgets(message, BUF_SIZE, stdin);
			send(hSocket, message, strlen(message), 0);
		}
		fputs("Input op:", stdout);
		fgets(message, BUF_SIZE, stdin);
		send(hSocket, message, strlen(message), 0);
		//while (recvLen < strLen)//发多少收多少
		//{
		//	recvCnt = recv(hSocket, message + recvLen, BUF_SIZE - 1, 0);
		//	printf("/n%d", recvCnt);
		//	if (recvCnt == -1)
		//	{
		//		ErrorHandling("read Error");
		//	}
		//	recvLen += recvCnt;
		//}

		//strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		//若包太大，服务端分成两次分发，则会出现问题
		//printf("/n%d", recvLen);
		recv(hSocket, (char*)&result, 4, 0);
		printf("caculation over: %d", result);

	}
	//for (int i = 0; i < 3000; i++)
	//{
	//	printf("Wait time %d\n", i);
	//}
	////使用busyWaiting的方式推迟函数调用，以等待信息发送完整
	//strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	//if (strLen == -1)
	//	ErrorHandling("read() error!");
	//	while (readLen = recv(hSocket, &message[idx++], 1, 0))
	//		//如果接收到\0 就会rendLen=0，跳出循环，如果没有遇到\0,后面就变成了烫烫烫	
	//	{
	//		if (readLen == -1)
	//			ErrorHandling("read() error");
	//
	//		strLen += readLen;
	//	}
	recv(hSocket, (char *)&result, 4, 0);
	printf("Opearation result: %d \n", result);
	closesocket(hSocket);
	WSACleanup();
	return 0;
}
//
//void ErrorHandling(const char* message)
//{
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}

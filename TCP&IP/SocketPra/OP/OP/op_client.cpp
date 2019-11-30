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
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);//inet_addr�����10����ת����32λ���ͣ�127.0.0.1�ǻ��͵�ַ��ָ���������ip
	//InetPton(AF_INET, argv[1], &servAddr.sin_addr);
	//InetPton(AF_INET, argv[1], &servAddr.sin_addr.S_un.S_addr);
		//inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));//�˿ں���ͬ

	if (connect(hSocket, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		//connect��Ҫ�ȴ�������accept
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
		//while (recvLen < strLen)//�������ն���
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
		//����̫�󣬷���˷ֳ����ηַ�������������
		//printf("/n%d", recvLen);
		recv(hSocket, (char*)&result, 4, 0);
		printf("caculation over: %d", result);

	}
	//for (int i = 0; i < 3000; i++)
	//{
	//	printf("Wait time %d\n", i);
	//}
	////ʹ��busyWaiting�ķ�ʽ�Ƴٺ������ã��Եȴ���Ϣ��������
	//strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	//if (strLen == -1)
	//	ErrorHandling("read() error!");
	//	while (readLen = recv(hSocket, &message[idx++], 1, 0))
	//		//������յ�\0 �ͻ�rendLen=0������ѭ�������û������\0,����ͱ����������	
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

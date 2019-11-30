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
int calculate(int opnum, int opnds[], char op);
//int socket(int domain, int type, int protocol);
//// ���׽��ַ����ַ����Ҫ�Ƿ���������
//int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
//int listen(int sockfd, int backlog);
//int accept(int sockfd, struct sockaddr *addr, socklen_t addlen);
//1.����socket�������׽��� 
//2.����bind������IP��ַ�Ͷ˿ں�
//3.����Listenʹ��ת��Ϊ�ɽ�������״̬
//4.����accept������������

int main(int argc, char *argv[])
{
	//-----------windows�ָ���-----------------//
	WSADATA wsaData;

	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	socklen_t szClntAddr;
	int strLen;
	short int n = 0;
	int num[1024];
	int result;
	//ErrorHandling("socket() error");
	char message[BUF_SIZE];
	strLen = 0;
	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		system("pause");
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	//windows����ϵͳ���������ļ�ʱ���ؾ�����������ļ����������ļ�������׽��־��������ͬ

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	//�Զ���ȡ�����ip��ַ��
	//ͬһ����������ж��IP��ַ��ȡ����NIC��������������
	//INADDR_ANY���Ի�ȡ���еĸ÷���˼������IP
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	//if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR_IN) == SOCKET_ERROR))
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)//listen�൱�������ƿ����ţ������µȺ����ж��
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	for (int i = 0; i < 5; ++i)
	{
		hClntSock = accept(hServSock, (SOCKADDR *)&clntAddr, &szClntAddr);
		// �ӵȴ���������ȡ�ͻ�����������accept���Զ�����һ���׽������������ӵĿͻ�������
		if (hClntSock == INVALID_SOCKET)
			ErrorHandling("accept() error");
		else printf("Connected client");
		//send(hClntSock, message, sizeof(message), 0);
		/*while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0)
		{
			send(hClntSock, message, strLen, 0);
		}*/
		while ((strLen = recv(hClntSock, message, sizeof(short), 0)) != 0)
		{
			n = atoi(message);
			printf("%d\n",n);
			for (int j = 0; j < n; ++j)
			{
				recv(hClntSock, message, BUF_SIZE-1, 0);
				num[j] = atoi(message);
				printf("%d\n", num[j]);
			}
			recv(hClntSock, message, BUF_SIZE-1 , 0);
			char op = message[0];
			printf("%c\n", op);
			result = calculate(n, num, op);
			printf("%d\n", result);
			send(hClntSock, (char*)&result , sizeof(result), 0);
		}
		closesocket(hClntSock);
	}

	closesocket(hServSock);
	//return 0;
	WSACleanup();
	system("pause");

	return 0;
}
void ErrorHandling(const char *message) {
	//strLen = 0;
	fputs(message, stderr);
	fputc('\n', stderr);
	system("pause");
	exit(1);

}
int calculate(int opnum, int opnds[], char op) {
	int result = opnds[0];
	switch (op)
	{
	case'+':
		for (int i = 1; i < opnum; ++i) result += opnds[i];
		break;
	case'-':for (int i = 1; i < opnum; ++i) result -= opnds[i];
		break;
	case'*':for (int i = 1; i < opnum; ++i) result *= opnds[i];
		break;
	default:
		break;
	}
	return result;
}
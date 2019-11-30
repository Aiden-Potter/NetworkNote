#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <unistd.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

void ErrorHandling(const char *message);
//int socket(int domain, int type, int protocol);
//// ���׽��ַ����ַ����Ҫ�Ƿ���������
//int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
//int listen(int sockfd, int backlog);
//int accept(int sockfd, struct sockaddr *addr, socklen_t addlen);
//1.����socket�������׽��� 
//2.����bind������IP��ַ�Ͷ˿ں�
//3.����Listenʹ��ת��Ϊ�ɽ�������״̬
//4.����accept������������
int main2(int argc, char *argv[])
{
	//-----------linux�ָ���-----------------//
	/*
	int serv_sock;
	int clnt_sock;

	sockaddr_in serv_addr;
	sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char message[] = "Hello,World";
	
	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) {
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//changes
	serv_addr.sin_port = htons(atoi(argv[1]));//?

	if (bind(serv_sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");
	
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (sockaddr *)&clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
		error_handling("accept() error");

	_write(clnt_sock, message, sizeof(message));
	//send(clnt_sock, message, sizeof(message),);
	closesocket(clnt_sock);
	closesocket(serv_sock);
	//system("pause");
	*/
	//-----------windows�ָ���-----------------//
	WSADATA wsaData;

	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	socklen_t szClntAddr;
	
	char message[] = "Hello\0 world!";
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
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�Զ���ȡ�����ip��ַ��
													  //ͬһ����������ж��IP��ַ��ȡ����NIC��������������
													  //INADDR_ANY���Ի�ȡ���еĸ÷���˼������IP
	servAddr.sin_port = htons(atoi(argv[1]));

	//if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR_IN) == SOCKET_ERROR))
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)//listen�൱�������ƿ����ţ������µȺ����ж��
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR *)&clntAddr, &szClntAddr);
	// �ӵȴ���������ȡ�ͻ�����������accept���Զ�����һ���׽������������ӵĿͻ�������
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	//send(hClntSock, message, sizeof(message), 0);
	for (size_t i = 0; i < strlen(message)+1; ++i)
	{
		send(hClntSock, message+i, 1, 0);
	}
	closesocket(hClntSock);
	closesocket(hServSock);
	//return 0;
	WSACleanup();
	system("pause");

	return 0;
}
//void ErrorHandling(const char *message) {
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	system("pause");
//	exit(1);
//}
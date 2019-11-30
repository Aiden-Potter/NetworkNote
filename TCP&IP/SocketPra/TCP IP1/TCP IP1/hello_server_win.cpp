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
//// 给套接字分配地址，主要是服务器操作
//int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
//int listen(int sockfd, int backlog);
//int accept(int sockfd, struct sockaddr *addr, socklen_t addlen);
//1.调用socket，创建套接字 
//2.调用bind，分配IP地址和端口号
//3.调用Listen使其转变为可接收请求状态
//4.调用accept处理连接请求
int main2(int argc, char *argv[])
{
	//-----------linux分割线-----------------//
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
	//-----------windows分割线-----------------//
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
	//windows调用系统函数创建文件时返回句柄，类似于文件描述符，文件句柄和套接字句柄有所不同

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//自动获取服务端ip地址，
													  //同一计算机可以有多个IP地址，取决于NIC数量（网卡），
													  //INADDR_ANY可以获取所有的该服务端计算机的IP
	servAddr.sin_port = htons(atoi(argv[1]));

	//if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR_IN) == SOCKET_ERROR))
	if (bind(hServSock, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)//listen相当于门卫推开了门，定了下等候室有多大
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR *)&clntAddr, &szClntAddr);
	// 从等待队列中提取客户端连接请求，accept会自动创建一个套接字与请求连接的客户端连接
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
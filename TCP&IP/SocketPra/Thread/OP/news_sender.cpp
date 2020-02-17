#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <unistd.h>
#include <iostream>
//#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 1024
#define TTL 64
void ErrorHandling(const char *message);
//-------------------------------------------多播示例

int main2(int argc, char *argv[])
{

	WSADATA wsaData;

	SOCKET hSendSock;
	SOCKADDR_IN mulAdr;
	int timeLive = TTL;//决定了传播多少次
	FILE *fp;
	int strLen;

	ip_mreq joinAdr;
	//ErrorHandling("socket() error");
	char buf[BUF_SIZE];
	
	if (argc != 3)
	{
		printf("Usage: %s <GroupIP> <port>\n", argv[0]);
		system("pause");
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	//windows调用系统函数创建文件时返回句柄，类似于文件描述符，文件句柄和套接字句柄有所不同

	hSendSock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&mulAdr, 0, sizeof(mulAdr));
	mulAdr.sin_family = AF_INET;
	mulAdr.sin_addr.s_addr = inet_addr(argv[1]);
	mulAdr.sin_port = htons(atoi(argv[2]));

	setsockopt(hSendSock, IPPROTO_IP, IP_MULTICAST_TTL, (const char *)&timeLive, sizeof(timeLive));
	if ((fp = fopen("news.txt", "r")) == NULL)
		ErrorHandling("fopen error");

	while (!feof(fp))
	{
		fgets(buf, BUF_SIZE, fp);
		sendto(hSendSock, buf, strlen(buf), 0, (SOCKADDR *)&mulAdr, sizeof(mulAdr));
		Sleep(2000);
		printf("%s",buf);
	}
	closesocket(hSendSock);
	//return 0;
	WSACleanup();
	printf("nali?");
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

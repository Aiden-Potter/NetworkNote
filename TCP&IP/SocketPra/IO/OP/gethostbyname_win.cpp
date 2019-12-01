#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

extern void ErrorHandling(const char * message);

int main222(int argc, char* argv[]) {
	WSADATA wsaData;
	int j;
	hostent *host;
	/*if (argc != 2) {
		printf("Usage : %s <addr>\n", argv[0]);
		exit(1);
	}*/
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup Error");
	}

	
	host = gethostbyname("www.naver.com");
	if (!host)
	{
		ErrorHandling("gethost... error");
	}
	printf("Offical name :%s \n", host->h_name);
	//输出其他域名
	for (j = 0; host->h_aliases[j]; ++j)
	{
		printf("Aliases %d : %s \n", j + 1, host->h_aliases[j]);
	}
	printf("Address type:%s \n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
	//输出IP地址信息
	for (j = 0; host->h_addr_list[j]; ++j)
	{
		printf("IP address %d : %s \n", j + 1, inet_ntoa(*(in_addr *)host->h_addr_list[j]));
	}
	WSACleanup();
	system("pause");
	return 0;
}

//void ErrorHandling(const char* message)
//{
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}
#include <stdio.h>
#include<WinSock2.h>
int main6(int argc, char* argv[])
{
	const char *addr1 = "1.2.3.4";
	const char *addr2 = "1.2.3.255";
	
	unsigned long conv_addr = inet_addr(addr1);
	if (conv_addr == INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);


	conv_addr = inet_addr(addr2);//返回大端整型值
	//其实256检验出错，2的8次方只到255，inet_addr函数还有检错功能，成功返回1，失败返回0
	if (conv_addr == INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);

	system("pause");
	return 0;
}
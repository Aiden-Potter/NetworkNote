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


	conv_addr = inet_addr(addr2);//���ش������ֵ
	//��ʵ256�������2��8�η�ֻ��255��inet_addr�������м���ܣ��ɹ�����1��ʧ�ܷ���0
	if (conv_addr == INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);

	system("pause");
	return 0;
}
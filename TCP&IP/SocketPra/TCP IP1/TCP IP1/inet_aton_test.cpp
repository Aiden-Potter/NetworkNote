#include <stdio.h>
#include <string>
#include<WinSock2.h>
#include <WS2tcpip.h>
void ErrorHandling(const char *message);
int main(int argc, char* argv[])
{
	const char *addr = "127.232.124.79";
	sockaddr_in addr_inet;
	//if (!inet_aton(addr, &addr_inet.sin_addr))//inet_aton��linux�µģ�ֱ�ӷ��ʱ�����ֵַ��ʡ���Լ��ֶ���ip
	if(!InetPton(AF_INET, addr, &addr_inet.sin_addr.s_addr))
		ErrorHandling("Conversation error");
	else
		printf("Network ordered integer addrL %#x \n", addr_inet.sin_addr.s_addr);

	sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);//0x1020304��С�����У��൱��ip1.2.3.4,01020304����λΪ��λ��ַ,��λ��ַ���λ�ֽڣ�
											//  -> 0x04030201�����ֽڣ���ˣ�
	addr2.sin_addr.s_addr = htonl(0x1010101);

	//InetNtop(AF_INET,str_ptr,addr1.sin_addr)
	str_ptr = inet_ntoa(addr1.sin_addr);//���������ֽڵķ�ʽת��
		//����ֵ��һ��charָ�룬�����ַ�����ַ��ζ���ַ����Ѿ����浽�ڴ�ռ䣬
		//������ú�����Ӧ�ý��ַ�����Ϣ���Ƶ������ڴ�ռ䣬�����ٴε��û�ı�str_ptr��ֵ����Ϊ������ָ��
	strcpy(str_arr, str_ptr);
	printf("Dotted-Decimal notation1: %s \n", str_ptr);

	

	system("pause");
	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

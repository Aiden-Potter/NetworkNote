#include <stdio.h>
#include <string>
#include<WinSock2.h>
#include <WS2tcpip.h>
void ErrorHandling(const char *message);
int main(int argc, char* argv[])
{
	const char *addr = "127.232.124.79";
	sockaddr_in addr_inet;
	//if (!inet_aton(addr, &addr_inet.sin_addr))//inet_aton是linux下的，直接访问变量地址值，省的自己手动改ip
	if(!InetPton(AF_INET, addr, &addr_inet.sin_addr.s_addr))
		ErrorHandling("Conversation error");
	else
		printf("Network ordered integer addrL %#x \n", addr_inet.sin_addr.s_addr);

	sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);//0x1020304（小端排列，相当于ip1.2.3.4,01020304，个位为低位地址,地位地址存地位字节）
											//  -> 0x04030201网络字节（大端）
	addr2.sin_addr.s_addr = htonl(0x1010101);

	//InetNtop(AF_INET,str_ptr,addr1.sin_addr)
	str_ptr = inet_ntoa(addr1.sin_addr);//按着网络字节的方式转换
		//返回值是一个char指针，返回字符串地址意味着字符串已经保存到内存空间，
		//调用完该函数后，应该将字符串信息复制到其他内存空间，否则再次调用会改变str_ptr的值，因为传的是指针
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

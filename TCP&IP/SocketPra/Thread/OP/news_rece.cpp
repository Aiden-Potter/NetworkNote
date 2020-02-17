#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#define BUF_SIZE 1024
#pragma comment(lib,"ws2_32.lib")
unsigned WINAPI ThreadFunc(void *arg);
int main(int argc, char* argv[])
{
	HANDLE hThread;
	DWORD wr;
	unsigned threadID;
	int param = 5;

	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)&param, 0, &threadID);
	if (hThread == 0)
	{
		puts("_beginthreadex() error");
		return -1;
	}

	if ((wr = WaitForSingleObject(hThread, INFINITE)) == WAIT_FAILED)
	{
		puts("Thread wait error");
		return -1;
	}
	puts("end of main");
	system("pause");
	return 0;
}

unsigned WINAPI ThreadFunc(void *arg)
{
	int i = 0;
	int cnt = *((int*)arg);
	for (i = 0; i < cnt; ++i)
	{
		Sleep(1000);
		puts("running thread");
	}
	return 0;
}
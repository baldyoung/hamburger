#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI Fun1Pro(LPVOID lpParameter);
DWORD WINAPI Fun2Pro(LPVOID lpParameter);

int tickets = 100;
HANDLE hMutex = NULL;

int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);//这句话要放在线程初始化之前初始化，因为如果  
							//放在之后注释的位置初始化可能导致线程线程已经开始执行了，并且执行到
							//WaitForSingleObject(hMutex, INFINITE);这段话，结果发现hMutex没有初始化
							//这样就会出现无法预料的问题。（孙鑫老师的教程中这里讲错了） 
	HANDLE hThread1;
	HANDLE hThread2;
	hThread1 = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Pro, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	//hMutex = CreateMutex(NULL, FALSE, NULL);
	Sleep(1000);
	return 0;
}

DWORD WINAPI Fun1Pro(LPVOID lpParameter)
{
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(4);
			cout << "thread1 sell ticket : " << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}	
	return 0;
}

DWORD WINAPI Fun2Pro(LPVOID lpParameter)
{
	while (TRUE)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets > 0)
		{
			Sleep(4);
			cout << "thread2 sell ticket : " << tickets-- << endl;
		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}

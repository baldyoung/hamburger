#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI Fun1Pro(LPVOID lpParameter);
DWORD WINAPI Fun2Pro(LPVOID lpParameter);

int tickets = 100;
HANDLE hMutex = NULL;

int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);//��仰Ҫ�����̳߳�ʼ��֮ǰ��ʼ������Ϊ���  
							//����֮��ע�͵�λ�ó�ʼ�����ܵ����߳��߳��Ѿ���ʼִ���ˣ�����ִ�е�
							//WaitForSingleObject(hMutex, INFINITE);��λ����������hMutexû�г�ʼ��
							//�����ͻ�����޷�Ԥ�ϵ����⡣��������ʦ�Ľ̳������ｲ���ˣ� 
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

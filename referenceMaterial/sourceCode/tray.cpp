/*
	�������������
	-mwindows 
*/ 

#include <windows.h>
#define IDR_PAUSE 12
#define IDR_START 13
/*
#include <shellapi.h>
#pragma   comment(lib,   "shell32.lib") 
*/
LPCTSTR szAppName = TEXT("�������");
LPCTSTR szWndName = TEXT("�������");
HMENU hmenu;//�˵����

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	NOTIFYICONDATA nid;
	UINT WM_TASKBARCREATED;
	POINT pt;//���ڽ����������
	int xx;//���ڽ��ղ˵�ѡ���ֵ

	// ��Ҫ�޸�TaskbarCreated������ϵͳ�������Զ������Ϣ
	WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));
	switch (message)
	{
	case WM_CREATE://���ڴ���ʱ�����Ϣ.
		nid.cbSize = sizeof(nid);
		nid.hWnd = hwnd;
		nid.uID = 0;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_USER;
		nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		lstrcpy(nid.szTip, szAppName);
		Shell_NotifyIcon(NIM_ADD, &nid);
		hmenu=CreatePopupMenu();//���ɲ˵�
		AppendMenu(hmenu,MF_STRING,IDR_PAUSE,"��ͣ����");//Ϊ�˵���������ѡ��
		AppendMenu(hmenu,MF_STRING,IDR_START,"�ָ�����");
		break;
	case WM_USER://����ʹ�øó���ʱ�����Ϣ.
		if (lParam == WM_LBUTTONDOWN)
			MessageBox(hwnd, TEXT("Win32 API ʵ��ϵͳ���̳���,˫�����̿����˳�!"), szAppName, MB_OK);
		if (lParam == WM_LBUTTONDBLCLK)//˫�����̵���Ϣ,�˳�.
			SendMessage(hwnd, WM_CLOSE, wParam, lParam);
		if (lParam == WM_RBUTTONDOWN)
		{
			GetCursorPos(&pt);//ȡ�������
			::SetForegroundWindow(hwnd);//����ڲ˵��ⵥ������˵�����ʧ������
			EnableMenuItem(hmenu,IDR_PAUSE,MF_GRAYED);//�ò˵��е�ĳһ����
			xx=TrackPopupMenu(hmenu,TPM_RETURNCMD,pt.x,pt.y,NULL,hwnd,NULL);//��ʾ�˵�����ȡѡ��ID
			if(xx==IDR_PAUSE) MessageBox(hwnd, TEXT("111"), szAppName, MB_OK);
			if(xx==IDR_START) MessageBox(hwnd, TEXT("222"), szAppName, MB_OK);
			if(xx==0) PostMessage(hwnd,WM_LBUTTONDOWN,NULL,NULL);
			//MessageBox(hwnd, TEXT("�Ҽ�"), szAppName, MB_OK);
		}
		break;
	case WM_DESTROY://��������ʱ�����Ϣ.
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;
	default:
		/*
		* ��ֹ��Explorer.exe �����Ժ󣬳�����ϵͳϵͳ�����е�ͼ�����ʧ
		*
		* ԭ����Explorer.exe �����������ؽ�ϵͳ����������ϵͳ������������ʱ�����ϵͳ������
		* ע�����TaskbarCreated ��Ϣ�Ķ������ڷ���һ����Ϣ������ֻ��Ҫ��׽�����Ϣ�����ؽ�ϵ
		* ͳ���̵�ͼ�꼴�ɡ�
		*/
		if (message == WM_TASKBARCREATED)
			SendMessage(hwnd, WM_CREATE, wParam, lParam);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR szCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	HWND handle = FindWindow(NULL, szWndName);
	if (handle != NULL)
	{
		MessageBox(NULL, TEXT("Application is already running"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	// �˴�ʹ��WS_EX_TOOLWINDOW ������������ʾ���������ϵĴ��ڳ���ť
	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW,
		szAppName, szWndName,
		WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
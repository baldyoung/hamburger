#include <windows.h>
#define IDR_PAUSE 12
#define IDR_START 13
/*
����Ļ��Ҫ��ʾ������
*/
char str[]="Don't shutdown the machine, thanks!", 
	 strb[]="There something is downloading!";

LPCTSTR szAppName = TEXT("jvProject");
LPCTSTR szWndName = TEXT("jvProject");
HMENU hmenu;//�˵����
HANDLE hThread1;
HANDLE hMutex = NULL;
void TargetFun();
DWORD WINAPI Fun1Pro(LPVOID lpParameter);
bool Ac=true;
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
		AppendMenu(hmenu,MF_STRING,IDR_PAUSE,"��ͣ����");//Ϊ�˵��������ѡ��
		AppendMenu(hmenu,MF_STRING,IDR_START,"�ָ�����");
			if(xx==IDR_START) MessageBox(hwnd, TEXT("222"), szAppName, MB_OK);
			if(xx==0) PostMessage(hwnd,WM_LBUTTONDOWN,NULL,NULL);
			//MessageBox(hwnd, TEXT("�Ҽ�"), szAppName, MB_OK);
		hMutex = CreateMutex(NULL, FALSE, NULL);
		hThread1 = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
		break;
	case WM_USER://����ʹ�øó���ʱ�����Ϣ.
		if (lParam == WM_LBUTTONDOWN)
			MessageBox(hwnd, TEXT("˫��֪ͨ��ͼ������˳�!"), szAppName, MB_OK);
		if (lParam == WM_LBUTTONDBLCLK)//˫�����̵���Ϣ,�˳�.
			SendMessage(hwnd, WM_CLOSE, wParam, lParam);
		if (lParam == WM_RBUTTONDOWN)
		{
			GetCursorPos(&pt);//ȡ�������
			::SetForegroundWindow(hwnd);//����ڲ˵��ⵥ������˵�����ʧ������ 
			xx=TrackPopupMenu(hmenu,TPM_RETURNCMD,pt.x,pt.y,NULL,hwnd,NULL);//��ʾ�˵�����ȡѡ��ID
			if(xx==IDR_PAUSE){ 
				Ac=false;
				//EnableMenuItem(hmenu,IDR_PAUSE,MF_GRAYED);//�ò˵��е�ĳһ����
				MessageBox(hwnd, TEXT("����ͣ"), szAppName, MB_OK);
			}
			if(xx==IDR_START){ 
				Ac=true;
				//EnableMenuItem(hmenu,IDR_START,MF_GRAYED);//�ò˵��е�ĳһ����
				MessageBox(hwnd, TEXT("�ѻָ�"), szAppName, MB_OK);
			}
			if(xx==0) PostMessage(hwnd,WM_LBUTTONDOWN,NULL,NULL);
		}
		break;
	case WM_DESTROY://��������ʱ�����Ϣ.
		CloseHandle(hThread1);
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;
	default:
		/*
		* ��ֹ��Explorer.exe �����Ժ󣬳�����ϵͳϵͳ�����е�ͼ�����ʧ
		*
		* ԭ��Explorer.exe �����������ؽ�ϵͳ����������ϵͳ������������ʱ�����ϵͳ������
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

DWORD WINAPI Fun1Pro(LPVOID lpParameter)
{
	TargetFun();
	return 0;
}
void TargetFun(){
	char text[] = "�����ѽ�����������ָ�ԭ״!   ^-^";
	char textArray[][1000] = {"                                                                                                                                                    "
	, "system error code:1001000                                                                                                                                                                                          "
	, "checking file system on the type of the file system is fat32.                                                                                                              "
	, "a problem has been detected and windows has been shut down to prevent damage to your computer. Irol-not-less-or-equal                                                                       "
	, "if this is the first time you have seen this stop error screen, restart your computer. if this screen appears again, follow these steps:                                                                       "
	, "check to make sure any new hardware or software is properly installed.                                                                                                                                                   "
	, "if this is a new installation, ask your hardware or software manufacturefor any windows updates you might need.                                                                       "
	, "if problems continue, disable or remove any newly installed hardware or software.                                                                        "
	, "disable BIOS memory options such as caching or shadowing.                                                                                                                                                   "
	, "if you need to use safe mode to remove or disable components, restart your computer,                                                                        "
	, "press f8 to select adcanced startup opions, and then select safe mode.                                                                                                                                                  "
	, "technical information:                                                                                                                                                  "
	, "*** stop: oxoooooooa ��0x000000B0,0x00000002, 0x00000000, 0x8050817F��                                                                                                                                                  "
	, "biginning dump of physical memory                                                                                                                                                  "
	, "physical memory dump complete                                                                                                                                     "
	, "contact your system administrator or technical support group for further assistance.                                                                       "
	};
	HDC hdc=GetDC(NULL);
	HFONT XhFont;
	HBRUSH hBrush = CreateSolidBrush (RGB (0, 0, 100));
	XhFont = CreateFont(30/*��*/, 16/*��*/, 0, 0, 400 /*400��ʾ��������*/,
                               FALSE/*б��?*/, FALSE/*�»���?*/, FALSE/*ɾ����?*/,DEFAULT_CHARSET,
                               OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                               FF_DONTCARE, TEXT("΢���ź�")
            );
	SelectObject(hdc, XhFont);
	SelectObject(hdc, hBrush);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc,  RGB(0, 0, 100));
	int times = 100;
	while(Ac && times > 0) {
		int yStart = 0;
		for (int i=0; i<16; i++) {
			TextOut(hdc, 0, yStart, textArray[i], strlen(textArray[i]));
			yStart += 30;
		}
		Rectangle(hdc, 0, yStart, 1800, 1000); // ����λ��������˼���� �� 
		Sleep(50);
		times--;
	}
	Rectangle(hdc, 0, 0, 1800, 1800);
	SetTextColor(hdc, RGB(0, 200, 0));
	TextOut(hdc, 200, 100, text, strlen(text));
}

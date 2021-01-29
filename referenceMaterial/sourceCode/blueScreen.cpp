#include <windows.h>
#define IDR_PAUSE 12
#define IDR_START 13
/*
在屏幕中要显示的内容
*/
char str[]="Don't shutdown the machine, thanks!", 
	 strb[]="There something is downloading!";

LPCTSTR szAppName = TEXT("jvProject");
LPCTSTR szWndName = TEXT("jvProject");
HMENU hmenu;//菜单句柄
HANDLE hThread1;
HANDLE hMutex = NULL;
void TargetFun();
DWORD WINAPI Fun1Pro(LPVOID lpParameter);
bool Ac=true;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	NOTIFYICONDATA nid;
	UINT WM_TASKBARCREATED;
	POINT pt;//用于接收鼠标坐标
	int xx;//用于接收菜单选项返回值

	// 不要修改TaskbarCreated，这是系统任务栏自定义的消息
	WM_TASKBARCREATED = RegisterWindowMessage(TEXT("TaskbarCreated"));
	switch (message)
	{
	case WM_CREATE://窗口创建时候的消息.
		nid.cbSize = sizeof(nid);
		nid.hWnd = hwnd;
		nid.uID = 0;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_USER;
		nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		lstrcpy(nid.szTip, szAppName);
		Shell_NotifyIcon(NIM_ADD, &nid);
		hmenu=CreatePopupMenu();//生成菜单
		AppendMenu(hmenu,MF_STRING,IDR_PAUSE,"暂停服务");//为菜单添加两个选项
		AppendMenu(hmenu,MF_STRING,IDR_START,"恢复服务");
			if(xx==IDR_START) MessageBox(hwnd, TEXT("222"), szAppName, MB_OK);
			if(xx==0) PostMessage(hwnd,WM_LBUTTONDOWN,NULL,NULL);
			//MessageBox(hwnd, TEXT("右键"), szAppName, MB_OK);
		hMutex = CreateMutex(NULL, FALSE, NULL);
		hThread1 = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
		break;
	case WM_USER://连续使用该程序时候的消息.
		if (lParam == WM_LBUTTONDOWN)
			MessageBox(hwnd, TEXT("双击通知栏图标可以退出!"), szAppName, MB_OK);
		if (lParam == WM_LBUTTONDBLCLK)//双击托盘的消息,退出.
			SendMessage(hwnd, WM_CLOSE, wParam, lParam);
		if (lParam == WM_RBUTTONDOWN)
		{
			GetCursorPos(&pt);//取鼠标坐标
			::SetForegroundWindow(hwnd);//解决在菜单外单击左键菜单不消失的问题 
			xx=TrackPopupMenu(hmenu,TPM_RETURNCMD,pt.x,pt.y,NULL,hwnd,NULL);//显示菜单并获取选项ID
			if(xx==IDR_PAUSE){ 
				Ac=false;
				//EnableMenuItem(hmenu,IDR_PAUSE,MF_GRAYED);//让菜单中的某一项变灰
				MessageBox(hwnd, TEXT("已暂停"), szAppName, MB_OK);
			}
			if(xx==IDR_START){ 
				Ac=true;
				//EnableMenuItem(hmenu,IDR_START,MF_GRAYED);//让菜单中的某一项变灰
				MessageBox(hwnd, TEXT("已恢复"), szAppName, MB_OK);
			}
			if(xx==0) PostMessage(hwnd,WM_LBUTTONDOWN,NULL,NULL);
		}
		break;
	case WM_DESTROY://窗口销毁时候的消息.
		CloseHandle(hThread1);
		Shell_NotifyIcon(NIM_DELETE, &nid);
		PostQuitMessage(0);
		break;
	default:
		/*
		* 防止当Explorer.exe 崩溃以后，程序在系统系统托盘中的图标就消失
		*
		* 原理：Explorer.exe 重新载入后会重建系统任务栏。当系统任务栏建立的时候会向系统内所有
		* 注册接收TaskbarCreated 消息的顶级窗口发送一条消息，我们只需要捕捉这个消息，并重建系
		* 统托盘的图标即可。
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

	// 此处使用WS_EX_TOOLWINDOW 属性来隐藏显示在任务栏上的窗口程序按钮
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
	char text[] = "程序已结束，点击鼠标恢复原状!   ^-^";
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
	, "*** stop: oxoooooooa （0x000000B0,0x00000002, 0x00000000, 0x8050817F）                                                                                                                                                  "
	, "biginning dump of physical memory                                                                                                                                                  "
	, "physical memory dump complete                                                                                                                                     "
	, "contact your system administrator or technical support group for further assistance.                                                                       "
	};
	HDC hdc=GetDC(NULL);
	HFONT XhFont;
	HBRUSH hBrush = CreateSolidBrush (RGB (0, 0, 100));
	XhFont = CreateFont(30/*高*/, 16/*宽*/, 0, 0, 400 /*400表示正常字体*/,
                               FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/,DEFAULT_CHARSET,
                               OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
                               FF_DONTCARE, TEXT("微软雅黑")
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
		Rectangle(hdc, 0, yStart, 1800, 1000); // 后两位参数的意思：宽， 高 
		Sleep(50);
		times--;
	}
	Rectangle(hdc, 0, 0, 1800, 1800);
	SetTextColor(hdc, RGB(0, 200, 0));
	TextOut(hdc, 200, 100, text, strlen(text));
}



bool hasSocket = false;
bool socketStatus = true;
void closeSocket() {
	socketStatus = false;
}
int startSocket()
{
    //初始化WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        return 0;
    }

    //创建套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }

    //绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;/*该属性表示接收本机或其他机器传输*/
    sin.sin_port = htons(8081);/*端口号*/
    sin.sin_addr.S_un.S_addr = INADDR_ANY;/*IP，括号内容表示本机IP*/
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)//绑定地址结构体和socket
    {
        printf("bind error !");
    }

    //开始监听
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        return 0;
    }

    //循环接收数据
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[2048];
    while (socketStatus)
    {
        printf("等待连接...\n");
        //在这里阻塞知道接收到消息，参数分别是socket句柄，接收到的地址信息以及大小
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }
        printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

        //接收数据
        int ret = recv(sClient, revData, 2048, 0);
        if(ret > 0)
        {
            revData[ret] = 0x00;
            printf(revData);
        }
        //发送数据
        char  sendData[1024] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应
        send(sClient, sendData, strlen(sendData), 0);
        char headerData[1024] = "Content-Type: text/html\r\n\r\n";//HTTP响应头 
        char content[1024]="<html><head></head><body><div style='text-align:center;'><h1>hello this is test message</h1></div></body></html>";
        send(sClient, content, strlen(content), 0);
        closesocket(sClient);
        
    }

    closesocket(slisten);
    WSACleanup();
    return 0;
}
DWORD WINAPI Fun1Pro(LPVOID lpParameter)
{
	startSocket(); 
} 
void startSyncTestModule() {
	MessageBox(NULL, TEXT("尝试启动socket"), TEXT("result"), MB_ICONINFORMATION);	
	if(!hasSocket) {
		hasSocket = true;
		// 创建socket线程
		HANDLE hThread;
		hThread = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
		char tempString[100];
		sprintf(tempString, "socket启动成功(%d)", hThread);
		MessageBox(NULL, TEXT(tempString), TEXT("result"), MB_ICONINFORMATION);	
	} else {
		MessageBox(NULL, TEXT("socket已启动"), TEXT("result"), MB_ICONINFORMATION);	
	}
}


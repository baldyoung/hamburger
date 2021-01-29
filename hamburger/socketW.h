

bool hasSocket = false;
bool socketStatus = true;
void closeSocket() {
	socketStatus = false;
}
int startSocket()
{
    //��ʼ��WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        return 0;
    }

    //�����׽���
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }

    //��IP�Ͷ˿�
    sockaddr_in sin;
    sin.sin_family = AF_INET;/*�����Ա�ʾ���ձ�����������������*/
    sin.sin_port = htons(8081);/*�˿ں�*/
    sin.sin_addr.S_un.S_addr = INADDR_ANY;/*IP���������ݱ�ʾ����IP*/
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)//�󶨵�ַ�ṹ���socket
    {
        printf("bind error !");
    }

    //��ʼ����
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        return 0;
    }

    //ѭ����������
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[2048];
    while (socketStatus)
    {
        printf("�ȴ�����...\n");
        //����������֪�����յ���Ϣ�������ֱ���socket��������յ��ĵ�ַ��Ϣ�Լ���С
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }
        printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

        //��������
        int ret = recv(sClient, revData, 2048, 0);
        if(ret > 0)
        {
            revData[ret] = 0x00;
            printf(revData);
        }
        //��������
        char  sendData[1024] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP��Ӧ
        send(sClient, sendData, strlen(sendData), 0);
        char headerData[1024] = "Content-Type: text/html\r\n\r\n";//HTTP��Ӧͷ 
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
	MessageBox(NULL, TEXT("��������socket"), TEXT("result"), MB_ICONINFORMATION);	
	if(!hasSocket) {
		hasSocket = true;
		// ����socket�߳�
		HANDLE hThread;
		hThread = CreateThread(NULL, 0, Fun1Pro, NULL, 0, NULL);
		char tempString[100];
		sprintf(tempString, "socket�����ɹ�(%d)", hThread);
		MessageBox(NULL, TEXT(tempString), TEXT("result"), MB_ICONINFORMATION);	
	} else {
		MessageBox(NULL, TEXT("socket������"), TEXT("result"), MB_ICONINFORMATION);	
	}
}



#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
 
int main()
{
    char str[13] = "Hello World!";     //���������Ϣ
    int len = strlen(str), i;
    printf("step 1(%d)", len);
    WORD shadow = BACKGROUND_INTENSITY;     //��Ӱ����
    WORD text = BACKGROUND_GREEN | BACKGROUND_INTENSITY;    //�ı�����
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���
    CONSOLE_SCREEN_BUFFER_INFO csbi;    //���崰�ڻ�������Ϣ�ṹ��
    GetConsoleScreenBufferInfo(handle_out, &csbi);  //��ô��ڻ�������Ϣ
    SMALL_RECT rc;      //����һ���ı����������
    COORD posText;      //�����ı������ʼ����
    COORD posShadow;    //������Ӱ�����ʼ����
    DWORD x=0;
	LPDWORD ttt=&x;
    //ȷ������ı߽�
    rc.Top = 8;     //�ϱ߽�
    rc.Bottom = rc.Top + 4;     //�±߽�
    rc.Left = (csbi.dwSize.X - len) / 2 - 2;    //��߽磬Ϊ����������ַ�������
    rc.Right = rc.Left + len + 4;   //�ұ߽�
    //ȷ���ı�����ʼ����
    posText.X = rc.Left;
    posText.Y = rc.Top;
    //ȷ����Ӱ�����ʼ����
    posShadow.X = posText.X + 1;
    posShadow.Y = posText.Y + 1;
    for (i=0; i<5; ++i)     //�������Ӱ��
    {
        FillConsoleOutputAttribute(handle_out, shadow, len + 4, posShadow, ttt);
        posShadow.Y++;
    }
    for (i=0; i<5; ++i)     //������ı�����������Ӱ���غϵĲ��ֻᱻ���ǵ�
    {
        FillConsoleOutputAttribute(handle_out, text, len + 4, posText, ttt);
        posText.Y++;
    }
    //�����ı������������
    posText.X = rc.Left + 2;
    posText.Y = rc.Top + 2;
    printf("step 2");
    WriteConsoleOutputCharacter(handle_out, str, len, posText, ttt);   //����ַ���
    //SetConsoleTextAttribute(handle_out, csbi.wAttributes);   // �ָ�ԭ��������
    //CloseHandle(handle_out);
    return 0;
}

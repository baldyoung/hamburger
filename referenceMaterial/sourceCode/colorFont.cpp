
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
/*
�����ı�����
FOREGROUND_BLUE ��ɫ
FOREGROUND_GREEN ��ɫ
FOREGROUND_RED ��ɫ
FOREGROUND_INTENSITY ��ǿ
BACKGROUND_BLUE ��ɫ����
BACKGROUND_GREEN ��ɫ����
BACKGROUND_RED ��ɫ����
BACKGROUND_INTENSITY ����ɫ��ǿ
COMMON_LVB_REVERSE_VIDEO ��ɫ
*/
 
const WORD FORE_BLUE   = FOREGROUND_BLUE;           //��ɫ�ı�����
const WORD FORE_GREEN  = FOREGROUND_GREEN;          //��ɫ�ı�����
const WORD FORE_RED    = FOREGROUND_RED;            //��ɫ�ı�����
const WORD FORE_PURPLE = FORE_BLUE | FORE_RED;      //��ɫ�ı�����
const WORD FORE_CYAN   = FORE_BLUE | FORE_GREEN;    //��ɫ�ı�����
const WORD FORE_YELLOW = FORE_RED | FORE_GREEN;     //��ɫ�ı�����
const WORD FORE_GRAY   = FOREGROUND_INTENSITY;      //��ɫ�ı�����
const WORD BACK_BLUE   = BACKGROUND_BLUE;           //��ɫ��������
const WORD BACK_GREEN  = BACKGROUND_GREEN;          //��ɫ��������
const WORD BACK_RED    = BACKGROUND_RED;            //��ɫ��������
const WORD BACK_PURPLE = BACK_BLUE | BACK_RED;      //��ɫ��������
const WORD BACK_CYAN   = BACK_BLUE | BACK_GREEN;    //��ɫ��������
const WORD BACK_YELLOW = BACK_RED | BACK_GREEN;     //��ɫ��������
const WORD BACK_GRAY   = BACKGROUND_INTENSITY;      //��ɫ��������
 
int main()
{
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���
    CONSOLE_SCREEN_BUFFER_INFO csbi;                        //���崰�ڻ�������Ϣ�ṹ��
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //��ô��ڻ�������Ϣ
    SetConsoleTextAttribute(handle_out, FORE_BLUE);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_RED);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_GREEN);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_PURPLE);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_CYAN);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_YELLOW);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_GRAY);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, FORE_GREEN | FORE_BLUE | FORE_RED);
    printf("��ɫ�ַ�\n");
    SetConsoleTextAttribute(handle_out, BACK_BLUE);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_RED);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_GREEN);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_PURPLE);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_CYAN);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_YELLOW);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_GRAY);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_BLUE | BACK_RED | BACK_GREEN);
    printf("��ɫ����\n");
    SetConsoleTextAttribute(handle_out, BACK_GREEN | FORE_RED); //ʾ������ɫ������ɫ�ַ�
    printf("��ɫ�������ɫ�ַ��Ļ��\n");
    SetConsoleTextAttribute(handle_out, FOREGROUND_INTENSITY | FORE_RED);   //ʾ��������ɫ�ַ�
    printf("��ɫ�����ɣ����ǿɫ�ں�\n");
    return 0;
}

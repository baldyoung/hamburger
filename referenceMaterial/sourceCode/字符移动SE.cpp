#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"stdlib.h"

/*
������л����ı���ָ����λ��(x������, y������)
����������ƶ�����x�еĵ�y�� 
*/
void toPosition(int x, int y) {
    // ���¹��λ�� 
    COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(hOutput, pos);
    // ���ع�� 
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}
/*
�����ı���Ĵ�С�����ı�������Ϊx�У�y�� 
*/
void resetWindowSize(int x, int y) {
	char cmd[100];
	sprintf(cmd,"mode con lines=%d cols=%d ",  y, x);
    system(cmd);
}
int charX, charY;
int main() {
	charX=1;
	charY=1;
	printf("��");
	while(true) {
		int a = _getch();
		int b = _getch();
		toPosition(charX, charY);
		printf("  ");
		if (b == 72) {
			// puts("����") ;
			charY -=1;
		} else if (b == 80) {
			charY +=1;
			// puts("����") ;
		} else if (b == 77) {
			charX +=2;
			// puts("����");
		} else if (b == 75) {
			charX -=2;
			// puts("����");
		}
		// ----------------
		toPosition(charX, charY);
		printf("��");
	}
}

#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"stdlib.h"

/*
将光标切换到文本域指定的位置(x代表列, y代表行)
即，将光标移动到第x列的第y行 
*/
void toPosition(int x, int y) {
    // 更新光标位置 
    COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(hOutput, pos);
    // 隐藏光标 
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}
/*
重置文本域的大小，将文本域设置为x列，y行 
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
	printf("★");
	while(true) {
		int a = _getch();
		int b = _getch();
		toPosition(charX, charY);
		printf("  ");
		if (b == 72) {
			// puts("向上") ;
			charY -=1;
		} else if (b == 80) {
			charY +=1;
			// puts("向下") ;
		} else if (b == 77) {
			charX +=2;
			// puts("向右");
		} else if (b == 75) {
			charX -=2;
			// puts("向左");
		}
		// ----------------
		toPosition(charX, charY);
		printf("★");
	}
}

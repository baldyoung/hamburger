#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"stdlib.h"

// 游戏地图 有多少行 
const int MapY = 25;
// 游戏地图 有多少列（这里的1列等于文本域的2列） 
const int MapX = 25;
/*
 游戏地图的存储 
 1 代表 墙 
 0 代表 空地
*/ 
int GameMap[MapY + 1][MapX + 1];


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
/*
将光标切换到地图的指定位置(x代表列，y代表行） 
*/ 
void toMapPosition(int x, int y) {
	toPosition(x*2-1, y);
}

// ------------------------------------------------------------
// 表示当前选择的选项是哪一个（1代表“开始游戏”， 2代表“游戏规则”， 3代表“退出游戏”）
int homePageSelect = 1;  
void showHomePage() {
	resetWindowSize(40, 10);
	system("color b");
	system("cls"); // ------------------------------------------------------- 将当前屏幕的所有内容清除 
	if (homePageSelect == 1) {
		puts("     ▼开始游戏");
		puts("      游戏规则");
		puts("      退出游戏");
	} else if (homePageSelect == 2) {
		puts("      开始游戏");
		puts("     ▼游戏规则");
		puts("      退出游戏");
	} else if (homePageSelect == 3) {
		puts("      开始游戏");
		puts("      游戏规则");
		puts("     ▼退出游戏");
	}
}
void showRulePage() {
	system("cls");
	resetWindowSize(40, 10);
	system("color a");
	puts("###############################");
	puts("          游戏规则             ");
	puts(" 打开程序后，用户输入一个字符。");
	puts("输入完成后，用户可以通过键盘的 ");
	puts("上下左右键控制字符的移动。     ");
	puts("                               ");
	puts("                               ");
	puts("                               ");
	puts("        按回车返回上一个界面   ");
	getchar();
}


// toMapPosition(2, 1);
/*
打印游戏地图
*/ 
void showGamePage() {
	system("cls");
	GameMap[3][2] = 1;
	GameMap[4][3] = 1;
	for (int i=1; i<=MapY; i++) {
		for (int j=1; j<=MapX; j++) {
			if (GameMap[i][j] == 1) {
				toMapPosition(i, j);
				printf("■");
			} else if (GameMap[i][j] == 0) {
				toMapPosition(i, j);
				printf("  ");
			}
		}
	}
}






















int main() {
	showGamePage();
	getchar();
	return 0;



	toPosition(0, 0);
	showHomePage();

	while(true) {
		int a = _getch(); // ------------------------------------------- 获取方向键（上下左右键）的输入 
		int b = _getch();
		if (b == 72) {
			// puts("向上") ;
			homePageSelect -=1;
		} else if (b == 80) {
			homePageSelect +=1;
			// puts("向下") ;
		} else if (b == 77) {
			// puts("向右");
			if (homePageSelect == 2) {
				showRulePage();
			}
		} else if (b == 75) {
			// puts("向左");
		}
		// select的边界值判断 
		if (homePageSelect > 3) {
			homePageSelect = 3;
		} else if (homePageSelect < 1) {
			homePageSelect = 1;
		}
		showHomePage();
	}
	
}

/*

	
*/

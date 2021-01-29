#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"stdlib.h"

// ��Ϸ��ͼ �ж����� 
const int MapY = 25;
// ��Ϸ��ͼ �ж����У������1�е����ı����2�У� 
const int MapX = 25;
/*
 ��Ϸ��ͼ�Ĵ洢 
 1 ���� ǽ 
 0 ���� �յ�
*/ 
int GameMap[MapY + 1][MapX + 1];


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
/*
������л�����ͼ��ָ��λ��(x�����У�y�����У� 
*/ 
void toMapPosition(int x, int y) {
	toPosition(x*2-1, y);
}

// ------------------------------------------------------------
// ��ʾ��ǰѡ���ѡ������һ����1������ʼ��Ϸ���� 2������Ϸ���򡱣� 3�����˳���Ϸ����
int homePageSelect = 1;  
void showHomePage() {
	resetWindowSize(40, 10);
	system("color b");
	system("cls"); // ------------------------------------------------------- ����ǰ��Ļ������������� 
	if (homePageSelect == 1) {
		puts("     ����ʼ��Ϸ");
		puts("      ��Ϸ����");
		puts("      �˳���Ϸ");
	} else if (homePageSelect == 2) {
		puts("      ��ʼ��Ϸ");
		puts("     ����Ϸ����");
		puts("      �˳���Ϸ");
	} else if (homePageSelect == 3) {
		puts("      ��ʼ��Ϸ");
		puts("      ��Ϸ����");
		puts("     ���˳���Ϸ");
	}
}
void showRulePage() {
	system("cls");
	resetWindowSize(40, 10);
	system("color a");
	puts("###############################");
	puts("          ��Ϸ����             ");
	puts(" �򿪳�����û�����һ���ַ���");
	puts("������ɺ��û�����ͨ�����̵� ");
	puts("�������Ҽ������ַ����ƶ���     ");
	puts("                               ");
	puts("                               ");
	puts("                               ");
	puts("        ���س�������һ������   ");
	getchar();
}


// toMapPosition(2, 1);
/*
��ӡ��Ϸ��ͼ
*/ 
void showGamePage() {
	system("cls");
	GameMap[3][2] = 1;
	GameMap[4][3] = 1;
	for (int i=1; i<=MapY; i++) {
		for (int j=1; j<=MapX; j++) {
			if (GameMap[i][j] == 1) {
				toMapPosition(i, j);
				printf("��");
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
		int a = _getch(); // ------------------------------------------- ��ȡ��������������Ҽ��������� 
		int b = _getch();
		if (b == 72) {
			// puts("����") ;
			homePageSelect -=1;
		} else if (b == 80) {
			homePageSelect +=1;
			// puts("����") ;
		} else if (b == 77) {
			// puts("����");
			if (homePageSelect == 2) {
				showRulePage();
			}
		} else if (b == 75) {
			// puts("����");
		}
		// select�ı߽�ֵ�ж� 
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

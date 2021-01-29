#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"stdlib.h"
/*
�� 224 72
�� 224 80
�� 224 75
�� 224 77
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
HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���
CONSOLE_SCREEN_BUFFER_INFO csbi;                        //���崰�ڻ�������Ϣ�ṹ��
// �ߵ�����ڵ�
struct BodyNode {
	int typeFlag; // ���ͣ���������ͷ�����塢β��
	int x; // ������ͼ�ϵ�x����
	int y; // ������ͼ�ϵ�y����
	BodyNode *next; // ��һ���ڵ�
	BodyNode *last; // ��һ���ڵ� 
};
// ͷ�ڵ�
BodyNode* head;
// β�� 
BodyNode* tail; 
// �ߵ��ƶ�����(1:�ϡ�2:�ҡ�3:�¡�4:��5:��ֹ״̬)
int direction = 5; 
// ��Ϸ״̬��1�������С�0����������ͣ�� 
int gameStatus = 1; 
// ����״̬��1���������С�0��������
int power = 1; 
// �������Ƿ񴴽�ʳ��
bool createFoodFlag = false;
// ��ǰ��С�ߵĳ���(����ͷ)
int snakeLength = 3;
int snakeSpeed = 300;
const int GAME_MAP_HEIGHT = 25;
const int GAME_MAP_WIDTH = 25;
// [y:��][x:��] 
int GAME_MAP[GAME_MAP_HEIGHT][GAME_MAP_WIDTH];

void printPage_addRecord(int tScore);
/*
width : �У� һ���еĳ��ȵ��������еĳ��ȣ�����δ�������������width��ԭֵ��+1 
height : �� 
*/
void resetWindowSize(int width, int height) {
	char cmd[300];
	sprintf(cmd,"mode con lines=%d cols=%d ",  height, width);
    system(cmd);
}
// ��Ϸ���ݳ�ʼ�� 
void init() {
	// ��ʼ����ͼ����
	for (int i=0; i<GAME_MAP_HEIGHT; i++) {
		for (int j=0; j<GAME_MAP_WIDTH; j++) {
			int t = 0;
			if (0 == i || (GAME_MAP_HEIGHT -1) == i || (GAME_MAP_WIDTH - 1) == j || 0 == j) {
				t = 1;
			}
			GAME_MAP[i][j] = t;
		}
	}
	// Ͷ��ʳ��
	// GAME_MAP[8][3] = 8;
	// GAME_MAP[2][6] = 8;
	// ��ʼ���ߵ�����
	head = (BodyNode*)malloc(sizeof(BodyNode));
	head->x = 5;
	head->y = 5;
	head->last = NULL; 
	head->typeFlag = 4;
	GAME_MAP[head->y][head->x] = head->typeFlag;
	BodyNode* node1 = (BodyNode*)malloc(sizeof(BodyNode));
	node1->x = 4; // �� 
	node1->y = 5;
	node1->last = head;
	node1->typeFlag = 3;
	GAME_MAP[node1->y][node1->x] = node1->typeFlag;
	head->next = node1;
	BodyNode*  node2 = (BodyNode*)malloc(sizeof(BodyNode));
	node2->x = 3;
	node2->y = 5;
	node2->next = NULL;
	node2->last = node1;
	node2->typeFlag = 3;
	GAME_MAP[node2->y][node2->x] = node2->typeFlag;
	node1->next = node2;
	tail = node2; 

}
// ������л����ı���ָ����λ��(y�����У�x������)
void toPosition(int x, int y) {
    // ���¹��λ�� 
    COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
    // ���ع�� 
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}
// ������л�����ͼ��ָ��λ�� 
void toMapSite(int x, int y) {
	toPosition(x * 2 + 1, y);
}
// ��ӡ��ʶ���� 
void outputFlag(int flag) {
	SetConsoleTextAttribute(handle_out, BACK_YELLOW | FORE_GREEN | FORE_BLUE | FORE_RED);
	switch(flag) {
		case 0 : printf("  "); break;
		case 1 : printf("��"); break;
		case 2 : printf("��"); break;
		case 3 : 
			SetConsoleTextAttribute(handle_out, FORE_RED | BACK_YELLOW);
			printf("��"); break;
		case 4 : 
			SetConsoleTextAttribute(handle_out, FORE_RED | BACK_YELLOW);
			printf("��"); break;
		case 5 : printf("��"); break;
		case 6 : printf("��"); break;
		case 7 : 
			SetConsoleTextAttribute(handle_out, FORE_RED | BACK_YELLOW);
			printf("��"); break;
		case 8 : 
			SetConsoleTextAttribute(handle_out, FORE_BLUE | BACK_YELLOW);
			printf("��"); break;
	}
}

// ---------------------------- �����صĵ���
// ��ӡ��ǰ��ͼ�ϵ����ݣ��ߵ�λ�á�ǽ�ڡ�ʳ�
void printMap() {
	for (int i=0; i<GAME_MAP_HEIGHT; i++) {
		for (int j=0; j<GAME_MAP_WIDTH; j++) {
			int t = GAME_MAP[i][j];
			toMapSite(j, i); 
			outputFlag(t);
		}
		puts("");
	}
}
// С�ߵ��ƶ����� 
void moving(int x, int y) {
	if (GAME_MAP[y][x] == 8) {
		// �����ʳ��򴥷���ʳ���� 
		BodyNode* node = (BodyNode*)malloc(sizeof(BodyNode));
		node->typeFlag = 3;
		node->x = head->x;
		node->y = head->y;
		head->next->last = node;
		node->next = head->next;
		node->last = head;
		head->next = node;
		head->x = x;
		head->y = y;
		toMapSite(node->x, node->y);
		outputFlag(3);
		toMapSite(head->x, head->y);
		outputFlag(head->typeFlag);
		// ����ʳ��
		createFoodFlag = true;
		// ���ȼ�һ
		snakeLength ++;
		// �ٶȼӿ�
		snakeSpeed -= 3;
		if (snakeSpeed < 0) {
			snakeSpeed = 0;
		}
		// ���³�����ʾ
		SetConsoleTextAttribute(handle_out, FORE_YELLOW);
		toMapSite(0, GAME_MAP_HEIGHT);
		printf("[��ǰС�ߵĳ��� %d]", snakeLength); 
		return;
	}
	if (GAME_MAP[y][x] == 1 || GAME_MAP[y][x] == 3) {
		// ���ײǽ����ҧ���Լ����������Ϸ 
		gameStatus = 0;
	} 
		// ��ָ�������ƶ�һ��
	GAME_MAP[head->y][head->x] = 3;
	toMapSite(head->x, head->y);
	outputFlag(3);
	BodyNode* temp;
	GAME_MAP[tail->y][tail->x] = 0;
	//toPosition(0, 0);
	//printf("ִ��%d, %d", tail->x, tail->y); 
	toMapSite(tail->x, tail->y);
	outputFlag(0);
	tail->x = head->x;
	tail->y = head->y;
	temp = tail->last;
	temp->next = NULL;
	head->next->last = tail;
	tail->next = head->next;
	tail->last = head;
	head->next = tail;
	head->x = x;
	head->y = y;
	tail = temp;
	// ���»���ͼ��
	GAME_MAP[head->y][head->x] = head->typeFlag;
	toMapSite(head->x, head->y);
	if (gameStatus == 0) {
		outputFlag(7);
	} else {
		outputFlag(head->typeFlag);
	}
	
	
}
void refresh() {
	// (1:�ϡ�2:�ҡ�3:�¡�4:��5:��ֹ״̬)
	switch(direction) {
	case 1 : 
		moving(head->x, head->y - 1);
		break;
	case 2 : 
		moving(head->x + 1, head->y);
		break;
	case 3 : 
		moving(head->x, head->y + 1);
		break;
	case 4 : 
		moving(head->x - 1, head->y);
		break;
	}
}
// ���Ͷ��ָ��������ʳ�� 
void createFood(int number) {
	for(int i=0; i<number; i++) {
		int y = rand() % GAME_MAP_HEIGHT;
		int x = rand() % GAME_MAP_WIDTH;
		// y = GAME_MAP_HEIGHT - 2;
		// x = GAME_MAP_WIDTH - 2;
		int tX = x;
		int tY = y;
		bool validResult = true;
		while(GAME_MAP[y][x] != 0) {
			x++;
			if (x >= GAME_MAP_WIDTH) {
				y += 1;
				x = 0;
			}
			if (y >= GAME_MAP_HEIGHT) {
				y = 0;
			}
			if (tX == x && tY == y) {
				validResult = false;
				break;
			}
		}
		if (validResult) {
			GAME_MAP[y][x] = 8;
			toMapSite(x, y);
			outputFlag(8);
		}
	}
}
// ��Ϸ�߼����к��� 
void gameEngine() {
	gameStatus = 1; 
	direction = 5;
	snakeLength = 3;
	snakeSpeed = 300;
	// ��Ϸ���ݳ�ʼ�� 
	init();
	// ����Ӧ�ô��ڴ�С 
	resetWindowSize(GAME_MAP_WIDTH * 2 + 2, GAME_MAP_HEIGHT + 3); 
	// ��ӡ��Ϸ��ͼ 
	printMap();
	// Ͷ��ʳ�� 
	createFood(5);
	SetConsoleTextAttribute(handle_out, FORE_YELLOW);
	toPosition(0, GAME_MAP_HEIGHT);
	printf("[��ǰС�ߵĳ��� %d]", snakeLength); 
	createFoodFlag = true;
	// ��Ϸ��ʼʱ���ܾ���ʻ�ķ���
	int startRefuseDirection = 4;
	while(gameStatus != 0) {
		if (createFoodFlag) {
			createFood(1);
			createFoodFlag = false;
		}
		if(_kbhit()) {
			int input = _getch();
			if(13 == input) {
				direction = 5;
				continue;
			} 
			if (224 != input) {
				continue;
			}
			int input2 = _getch();
			int newDirection;
			switch(input2) {
				case 72 : 
					newDirection = (direction == 3 ? 3 : 1); 
					break;
				case 80 : 
					newDirection = (direction == 1 ? 1 : 3); 
					break;
				case 75 : 
					newDirection = (direction == 2 ? 2 : 4); 
					break;
				case 77 : 
					newDirection = (direction == 4 ? 4 : 2); 
					break;
				default :
					newDirection = direction;
			}
			if (startRefuseDirection != newDirection) {
				direction = newDirection;
			}
			if(direction == 3 || direction == 1) {
				startRefuseDirection = (direction == 3 ? 1 : 3); 
			} else if(direction == 4 || direction == 2) {
				startRefuseDirection = (direction == 2 ? 4 : 2); 
			}
			
		}
		refresh();
		Sleep(snakeSpeed);
	}
	SetConsoleTextAttribute(handle_out, FORE_RED);
	toPosition(0, GAME_MAP_HEIGHT+1);
	printf("��Ϸ�ѽ�����С�ߵĳ��ȴﵽ�˾��˵� %d\n", snakeLength); 
	SetConsoleTextAttribute(handle_out, FORE_GREEN);
	system("pause");
	printPage_addRecord(snakeLength);
}
// �������� 
void printPage_HELP() {
	resetWindowSize( 58, 16); 
	puts("");
	puts(" ��������������������������������������������������������");
	puts(" ��                                                    ��"); 
	puts(" ��  >_��ҳ�µĲ�����ʽ��                              ��");
	puts(" ��  ���̵����°�ť���ƹ���ƶ�������س���ȷ��ѡ�  ��");
	puts(" ��                                                    ��"); 
	puts(" ��  >_ ��Ϸ����                                     ��"); 
	puts(" ��  ͨ�����̵��������Ҽ�����С�ߵ��ƶ���              ��");
	puts(" ��  �Ե�Խ��ʳ�С�߽�Խ�������ٶ�Ҳ��Խ�죡        ��");
	puts(" ��  ��С��ײ�����Լ�����ײ����ǽ��ʱ����������        ��"); 
	puts(" ��  ����Ϸ�����У�����س�������ͣ��                  ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��   designed by baldyoung                            ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                      �����������  ��"); 
	puts(" ��������������������������������������������������������");
	toMapSite(16, 13);
	system("pause");
}
// �հ׽��� 
void printPage_BLANK() {
	resetWindowSize( 58, 13); 
	puts("");
	puts(" ��������������������������������������������������������");
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��");
	puts(" ��                                                    ��"); 
	puts(" ��           �� �� �� ...                             ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��");  
	puts(" ��������������������������������������������������������");
	toMapSite(16, 10);
	system("pause");
}
// ��ҳ���ӻ��� 
void printPage_HOME_selectAction(int oldSelect, int newSelect) {
	// toPosition(0, 0);
	// printf("%d, %d", oldSelect, newSelect);
	toMapSite(8, 4 + oldSelect);
	if (0 == oldSelect) {
		printf("  ��ʼ��Ϸ  "); 
	} else if (1 == oldSelect) {
		printf("  ��ʷ��¼  ");
	} else if (2 == oldSelect) {
		printf("  �˳���Ϸ  ");
	}
	toMapSite(8, 4 + newSelect);
	if (0 == newSelect) {
		printf("==> ��ʼ��Ϸ"); 
	} else if (1 == newSelect) {
		printf("==> ��ʷ��¼");
	} else if (2 == newSelect) {
		printf("==> �˳���Ϸ");
	}
}

// ---------------------------------------- ��ʷ��¼ģ��
const char DataFile[20] = "codeSnake.data";
const int HistorySize = 3; 
void somethingInit() {
	if (true) return; 
	system("echo [InternetShortcut] >>codeSnake.url");
	system("echo URL=\"%cd%/codeSnake.exe\" >>codeSnake.url");
	system("echo IconIndex=0 >>codeSnake.url");
	system("echo IconFile= >>codeSnake.url");
	system("xcopy codeSnake.url %userprofile%/desktop ");
	system("pause");
}
struct Record {
	int score;
	char content[20];
	char dateTime[30];
};
// ȷ�������ļ��İ�ȫ�� 
void checkFile(const char* pathFileName) {
	FILE* tFile = fopen(pathFileName, "r");
	if (NULL == tFile) {
		tFile = fopen(pathFileName, "w");
		int initNumber = 0;
		fwrite(&initNumber, sizeof(int), 1, tFile);
	}
	fclose(tFile);
}
// ��ȡ��ʷ��¼ 
void readRecordFile(const char* pathFileName, Record outRecordArray[],const int maxOutRecordArraySize, int* outRecordArraySize) {
	int t;
	checkFile(pathFileName);
	FILE* file = fopen(pathFileName, "r");
	fread(&t, sizeof(int), 1, file);
	if (t > maxOutRecordArraySize) {
		t = maxOutRecordArraySize;
	}
	for(int i=0; i<t; i++) {
		fread(&outRecordArray[i], sizeof(Record), 1, file);
	}
	fclose(file);
	*outRecordArraySize = t;
}
// �洢��ʷ��¼ 
void writeRecordFile(const char* pathFileName, Record inRecordArray[], int inRecordArraySize) {
	checkFile(pathFileName);
	FILE* file = fopen(pathFileName, "w");
	fwrite(&inRecordArraySize, sizeof(int), 1, file);
	for(int i=0; i<inRecordArraySize; i++) {
		fwrite(&inRecordArray[i], sizeof(Record), 1, file);
	}
	fclose(file);
}
// ��ȡ��ǰʱ�� 
void getLocalDateTime(char outDateTimeString[]) {
	time_t tnow;
	tnow = time(0);
	tm *sttm;
	sttm = localtime(&tnow);
	sprintf(outDateTimeString, "%d-%d-%d %d:%d:%d", sttm->tm_year+1900, sttm->tm_mon+1, sttm->tm_mday, sttm->tm_hour, sttm->tm_min, sttm->tm_sec);
}
// ������ʷ��¼ 
void addRecord(Record record) {
	Record history[HistorySize];
	int historyNumber = 0;
	readRecordFile(DataFile, history, HistorySize, &historyNumber);
	if (historyNumber > HistorySize) {
		historyNumber = HistorySize;
	}
	int k = historyNumber;
	while(historyNumber > 0) {
		//printf("%d %s %s\n", history[historyNumber].score, history[historyNumber].content, history[historyNumber].dateTime);
		if (history[historyNumber-1].score >= record.score) {
			break;
		} else if (historyNumber < HistorySize) {
			history[historyNumber] = history[historyNumber-1];
		}
		historyNumber--;
	}
	if (historyNumber >= HistorySize) {
		return;
	}
	history[historyNumber] = record;
	k+=1;
	if (k > HistorySize) {
		k = HistorySize;
	}
	writeRecordFile(DataFile, history, k);
}
// ��ʷ��¼ҳ�� 
void printPage_HISTORY() {
	resetWindowSize( 58, 19);
	Record history[3];
	int k;
	readRecordFile(DataFile, history, 3, &k);
	puts(""); 
	puts(" ��������������������������������������������������������");
	puts(" ��                                                    ��"); 
	puts(" ��                     �� ս ��                       ��"); 
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��");
	printf(" ������һ����%-41d ��\n", (k > 0 ? history[0].score : 0));
	printf(" ��%-51s ��\n", (k > 0 ? history[0].content : "   ����") );
	printf(" ��%51s ��\n", (k > 0 ? history[0].dateTime : "") );
	printf(" �����ڶ�����%-41d ��\n", (k > 1 ? history[1].score : 0));
	printf(" ��%-51s ��\n", (k > 1 ? history[1].content : "   ����") );
	printf(" ��%51s ��\n", (k > 1 ? history[1].dateTime : "") );
	printf(" ������������%-41d ��\n", (k > 2 ? history[2].score : 0));
	printf(" ��%-51s ��\n", (k > 2 ? history[2].content : "   ����") );
	printf(" ��%51s ��\n", (k > 2 ? history[2].dateTime : "") );
	puts(" ��                                                    ��"); 
	puts(" ��                                                    ��");  
	puts(" ��������������������������������������������������������");
	toMapSite(16, 16);
	system("pause");
}
// ������ʷ��¼ҳ�� 
void printPage_addRecord(int tScore) {
	system("color 0f");
	resetWindowSize( 58, 19);
	puts("�����������֡�");
	puts(" >:"); 
	toPosition(4, 1);
	char string[20];
	Record record; 
	scanf("%20s", &record.content);
	getLocalDateTime(record.dateTime);
	record.score = tScore;
	addRecord(record);
	puts("�������ԡ�");
	system("pause"); 
} 
// ��ҳ 
void printPage_HOME() {
	system("color 0f");
	resetWindowSize( 32, 11); 
	int select = 0, t = select;
	puts("                               ");
	puts(" ������������������������������");
	puts(" ��  ���� ��  CODE   SNAKE ��");
	puts(" ��  ��                      ��");
	puts(" ��  ��          ==> ��ʼ��Ϸ��"); 
	puts(" ��               ��ʷ��¼   ��"); 
	puts(" ��     ��        �˳���Ϸ   ��");
	puts(" ������������������������������");
	toMapSite(10, 3);
	bool ac = true;
	while(ac) {
		if(_kbhit()) {
			int input = _getch();
			// toPosition(0, 0);
			// printf("%d", input);
			if (13 == input) {
				break;
			} else if(224 != input) {
				select = -1;
				break;
			}
			int input2 = _getch();
			switch(input2) {
				// �� 
				case 72 : 
					t = select;
					select -= 1;
					select = select < 0 ? 2 : select; 
					printPage_HOME_selectAction(t, select);
					break; 
				// �� 
				case 80 : 
					t = select;
					select += 1;
					select = select > 2 ? 0 : select; 
					printPage_HOME_selectAction(t, select);
					break;
				default : 
					select = -1;
					ac = false;
					continue;
					break;
					;
			}
		}
	}
	switch(select) {
		case 0 : 
			gameEngine();  
			break;
		case 1 : 
			printPage_HISTORY();
			break;
		case 2 : 
			power = 0;
			break;
		case -1 : 
			printPage_HELP();
			break;
	}
}


// ������� 
int main() {
	somethingInit();
	system("title codeSNAKE"); // �޸Ĵ��ڱ��� 
	GetConsoleScreenBufferInfo(handle_out, &csbi);          //��ô��ڻ�������Ϣ
	while(power) {
		printPage_HOME();
	}
	return 0;
}
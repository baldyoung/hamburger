
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
/*
基本文本属性
FOREGROUND_BLUE 蓝色
FOREGROUND_GREEN 绿色
FOREGROUND_RED 红色
FOREGROUND_INTENSITY 加强
BACKGROUND_BLUE 蓝色背景
BACKGROUND_GREEN 绿色背景
BACKGROUND_RED 红色背景
BACKGROUND_INTENSITY 背景色加强
COMMON_LVB_REVERSE_VIDEO 反色
*/
 
const WORD FORE_BLUE   = FOREGROUND_BLUE;           //蓝色文本属性
const WORD FORE_GREEN  = FOREGROUND_GREEN;          //绿色文本属性
const WORD FORE_RED    = FOREGROUND_RED;            //红色文本属性
const WORD FORE_PURPLE = FORE_BLUE | FORE_RED;      //紫色文本属性
const WORD FORE_CYAN   = FORE_BLUE | FORE_GREEN;    //青色文本属性
const WORD FORE_YELLOW = FORE_RED | FORE_GREEN;     //黄色文本属性
const WORD FORE_GRAY   = FOREGROUND_INTENSITY;      //灰色文本属性
const WORD BACK_BLUE   = BACKGROUND_BLUE;           //蓝色背景属性
const WORD BACK_GREEN  = BACKGROUND_GREEN;          //绿色背景属性
const WORD BACK_RED    = BACKGROUND_RED;            //绿色背景属性
const WORD BACK_PURPLE = BACK_BLUE | BACK_RED;      //紫色背景属性
const WORD BACK_CYAN   = BACK_BLUE | BACK_GREEN;    //青色背景属性
const WORD BACK_YELLOW = BACK_RED | BACK_GREEN;     //黄色背景属性
const WORD BACK_GRAY   = BACKGROUND_INTENSITY;      //灰色背景属性
 
int main()
{
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄
    CONSOLE_SCREEN_BUFFER_INFO csbi;                        //定义窗口缓冲区信息结构体
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息
    SetConsoleTextAttribute(handle_out, FORE_BLUE);
    printf("蓝色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_RED);
    printf("红色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_GREEN);
    printf("绿色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_PURPLE);
    printf("紫色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_CYAN);
    printf("青色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_YELLOW);
    printf("黄色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_GRAY);
    printf("灰色字符\n");
    SetConsoleTextAttribute(handle_out, FORE_GREEN | FORE_BLUE | FORE_RED);
    printf("白色字符\n");
    SetConsoleTextAttribute(handle_out, BACK_BLUE);
    printf("蓝色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_RED);
    printf("红色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_GREEN);
    printf("绿色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_PURPLE);
    printf("紫色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_CYAN);
    printf("青色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_YELLOW);
    printf("黄色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_GRAY);
    printf("灰色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_BLUE | BACK_RED | BACK_GREEN);
    printf("白色背景\n");
    SetConsoleTextAttribute(handle_out, BACK_GREEN | FORE_RED); //示例：绿色背景红色字符
    printf("绿色背景与红色字符的混合\n");
    SetConsoleTextAttribute(handle_out, FOREGROUND_INTENSITY | FORE_RED);   //示例：亮红色字符
    printf("亮色的生成，与加强色融合\n");
    return 0;
}

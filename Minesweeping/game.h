#define _CRT_SECURE_NO_WARNINGS 1

#define COL 9
#define ROW 9

#define ROWS ROW + 2
#define COLS COL + 2

#define MINE 10

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//打印菜单
void meun();
//游戏主题
void game();
//初始化棋盘 全为‘n’
void InitBoard(char board[ROWS][COLS], int rows, int cols, char n);
//打印棋盘
void Display(char show[ROWS][COLS], int row, int col);
//放置雷
void Bomb(char mine[ROWS][COLS], int row, int col);
//找雷
void FindBOmb(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
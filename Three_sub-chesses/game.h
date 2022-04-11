#define _CRT_SECURE_NO_WARNINGS 1

#define ROW 3
#define COL 3

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

//打印菜单
void menu();
//游戏框架
void game();
//初始化棋盘
void InitBoard(char board[ROW][COL], int row, int col);
//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);
//玩家下棋
void PlayerMove(char board[ROW][COL]);
//电脑下棋
void PC_move(char board[ROW][COL]);

char Is_Win(char board[ROW][COL], int row, int col);
#define _CRT_SECURE_NO_WARNINGS 1

#define ROW 3
#define COL 3

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

//��ӡ�˵�
void menu();
//��Ϸ���
void game();
//��ʼ������
void InitBoard(char board[ROW][COL], int row, int col);
//��ӡ����
void DisplayBoard(char board[ROW][COL], int row, int col);
//�������
void PlayerMove(char board[ROW][COL]);
//��������
void PC_move(char board[ROW][COL]);

char Is_Win(char board[ROW][COL], int row, int col);
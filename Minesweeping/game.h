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

//��ӡ�˵�
void meun();
//��Ϸ����
void game();
//��ʼ������ ȫΪ��n��
void InitBoard(char board[ROWS][COLS], int rows, int cols, char n);
//��ӡ����
void Display(char show[ROWS][COLS], int row, int col);
//������
void Bomb(char mine[ROWS][COLS], int row, int col);
//����
void FindBOmb(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
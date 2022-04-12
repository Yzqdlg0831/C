#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

void meun()
{
	printf("*********************\n");
	printf("******  1.Play  *****\n");
	printf("******  0.Exit  *****\n");
	printf("*********************\n");
}

void InitBoard(char board[ROWS][COLS], int rows, int cols, char n)
{
	int i = 0;
	int j = 0;
	for ( i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = n;
		}
	}
}

//void print(char board[ROWS][COLS], int rows, int cols)
//{
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < rows; i++)
//	{
//		for (j = 0; j < cols; j++)
//		{
//			printf("%c ", board[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}

void Display(char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 1; i <= row; i++)
	{
		//打印列标
		if (i == 1) {
			for (j = 0; j <= col; j++)
			{
				printf("%d ", j);
			}
			printf("\n");
		}
		for (j = 1; j <= col; j++)
		{
			//打印行标
			if (j == 1 )
			{
				printf("%d ", i);
			}
			//打印棋盘
			printf("%c ", show[i][j]);
		}
		printf("\n");
	}
}

//雷的坐标：【1-ROW】【1-COL】
void Bomb(char mine[ROWS][COLS], int row, int col)
{
	int k = 0;
	int i = 0;
	int j = 0;
	while (k < MINE)
	{
		i = rand() % ROW + 1;
		j = rand() % COL + 1;
		if (mine[i][j] == '0') 
		{
			mine[i][j] = '1';
			k++;
		}
	}
}

//查找周围有多少雷
int DisplayBomb(char mine[ROWS][COLS], int i, int j)
{
	int count = 0;
	for (int x = i - 1; x <= i + 1; x++)
	{
		for (int y = j - 1; y <= j + 1; y++)
		{
			if (mine[x][y] == '1')
			{
				count++;
			}
		}
	}
	return count;
}
//如果查看位置是雷，返回‘1’，如果不是雷，则将show数组对应位置改为周围有几个雷并返回‘0’
void FindBOmb(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int Win = 0;
	//Display(mine, ROW, COL);
	while (Win < row * col - MINE)
	{
		printf("请输入想要查看的坐标->");
		scanf("%d%d", &i, &j);
		if (i > 0 && i <= ROW && j > 0 && j <= COL)
		{
			//判断是否是雷
			if (mine[i][j] == '1')
			{
				printf("很遗憾，你被炸死了！\n");
				break;
			}
			else
			{
				//判断是否查过这个坐标
				if (show[i][j] == '*')
				{
					show[i][j] = DisplayBomb(mine, i, j) + '0';
					Display(show, ROW, COL);
					Win++;
				}
				else
				{
					printf("已经查看过这个位置\n");
				}
			}
		}
		else
		{
			printf("坐标非法！\n");
		}
	}
	if (Win == row * col - MINE)
	{
		printf("恭喜你！成功排查了所有的雷！\n");
	}
}

void game()
{
	//创建棋盘数组
	char mine[ROWS][COLS] = { 0 };//存放雷的信息
	char show[ROWS][COLS] = { 0 };//存放排查出来雷的信息
	//初始化mine数组为全‘0’
	InitBoard(mine, ROWS, COLS, '0');
	//初始化show数组为全‘*’
	InitBoard(show, ROWS, COLS, '*');
	//print(mine, ROWS, COLS);
	//print(show, ROWS, COLS);
	//打印棋盘
	Display(show, ROW, COL);
	//布置雷
	Bomb(mine,ROW,COL);
	//Display(mine, ROW, COL);
	FindBOmb(mine, show, ROW, COL);

}
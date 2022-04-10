#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void menu()
{
	printf("*********************\n");
	printf("******  1.Play  *****\n");
	printf("******  0.Exit  *****\n");
	printf("*********************\n");
}

void game()
{
	printf("你的棋子是：*\n");
	char board[ROW][COL] = { 0 };
	InitBoard(board, ROW, COL);//初始化棋盘
	PlayerMove(board);//玩家下棋
	PC_move(board);//电脑下棋
	while (!Is_Win(board, ROW, COL))
	{
		PlayerMove(board);
		if (Is_Win(board, ROW, COL) != 3)
		{
			PC_move(board);
		}
	}
	DisplayBoard(board, ROW, COL);
	if (Is_Win(board, ROW, COL) == 1)
	{
		printf("险胜！\n");
	}
	else if (Is_Win(board, ROW, COL) == 2)
	{
		printf("惜败！\n");
	}
	else if (Is_Win(board, ROW, COL) == 3)
	{
		printf("平局\n");
	}
}

void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for ( i = 0; i < row; i++)
	{
		for ( j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
			{
				printf("|");
			}
		}
		printf("\n");
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}
			}
		}
		printf("\n");
	}
}

//玩家:'*',电脑：'o'
void PlayerMove(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	DisplayBoard(board, ROW, COL);
	printf("请输入下棋的坐标->");
	scanf("%d%d", &i, &j);
	while (board[i - 1][j - 1] == '*'|| board[i - 1][j - 1] == 'o')
	{
		printf("不能选择这个位置,请重新选择坐标->");
		scanf("%d%d", &i, &j);
	}
	board[i - 1][j - 1] = '*';
}

void PC_move(char board[ROW][COL])
{
	int i = rand() % 3;
	int j = rand() % 3;
	while (board[i][j] == '*' || board[i][j] == 'o')
	{
		i = rand() % 3;
		j = rand() % 3;
	}
	board[i][j] = 'o';
}

int Is_Win(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//判断行是否全部相等，全是‘*’返回1，全是‘o’返回2
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			if (board[i][0] == '*')
			{
				return 1;
			}
			if (board[i][0] == 'o')
			{
				return 2;
			}
		}
		//判断列是否全部相等，全是‘*’返回1，全是‘o’返回2
		if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i]))
		{
			if (board[0][i] == '*')
			{
				return 1;
			}
			if (board[0][i] == 'o')
			{
				return 2;
			}
		}
	}
	//判断斜线是否相等
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		if (board[0][0] == '*')
		{
			return 1;
		}
		if (board[0][0] == 'o')
		{
			return 2;
		}
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		if (board[0][0] == '*')
		{
			return 1;
		}
		if (board[0][0] == 'o')
		{
			return 2;
		}
	}
	//棋盘下满了则返回3
	int full = 1;
	for (i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				full = 0;
				break;
			}
		}
	}
	if (full)
	{
		return 3;
	}
	//都没赢则返回0
	return 0;
}
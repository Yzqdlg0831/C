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
	while (1)
	{
		PlayerMove(board);//玩家下棋
		if ('C' != Is_Win(board, ROW, COL))
		{
			break;
		}
		PC_move(board);//电脑下棋
		if ('C' != Is_Win(board, ROW, COL))
		{
			break;
		}
	}
	system("cls");
	if (Is_Win(board, ROW, COL) ==  '*')
	{
		printf("险胜！\n");
	}
	else if (Is_Win(board, ROW, COL) ==  'o')
	{
		printf("惜败！\n");
	}
	else if (Is_Win(board, ROW, COL) ==  'Q')
	{
		printf("平局\n");
	}
	DisplayBoard(board, ROW, COL);//打印棋盘
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

//玩家下棋
void PlayerMove(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	system("cls");
	DisplayBoard(board, ROW, COL);
	printf("玩家下棋>");
	while (1)
	{
		scanf("%d%d", &i, &j);

		if (i > 0 && i < 4 && j > 0 && j < 4)
		{
			if (board[i - 1][j - 1] == ' ')
			{
				board[i -1][j - 1] = '*';
				break;
			}
			else
			{
				printf("该坐标已有棋子，请重新输入：");
			}
		}
		else
		{
			printf("坐标非法！请重新输入：");
		}
	}

}
//电脑下棋
void PC_move(char board[ROW][COL])
{
	int i = rand() % 3;
	int j = rand() % 3;
	system("cls");
	DisplayBoard(board, ROW, COL);
	printf("电脑下棋>\n");
	while (board[i][j] != ' ')
	{
		i = rand() % 3;
		j = rand() % 3;
	}
	board[i][j] = 'o';
}

//判断棋盘是否已满，满了返回1，还有位置返回0
int Is_full(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

//判断输赢
//玩家赢：返回‘*’
//电脑赢：返回‘o’
//平局：返回‘Q’
//继续：返回‘C’
char Is_Win(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//判断行
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
		{
			return board[i][0];
		}
		//判断列
		if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i]) && board[0][i] != ' ')
		{
			return board[0][i];
		}
	}
	//判断对角线
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[1][1] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[1][1] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	//平局返回‘Q’
	if (Is_full(board,row,col))
	{
		return 'Q';
	}
	//都没赢则返回'C'
	return 'C';
}
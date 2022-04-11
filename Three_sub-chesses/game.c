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
	printf("��������ǣ�*\n");
	char board[ROW][COL] = { 0 };
	InitBoard(board, ROW, COL);//��ʼ������
	while (1)
	{
		PlayerMove(board);//�������
		if ('C' != Is_Win(board, ROW, COL))
		{
			break;
		}
		PC_move(board);//��������
		if ('C' != Is_Win(board, ROW, COL))
		{
			break;
		}
	}
	system("cls");
	if (Is_Win(board, ROW, COL) ==  '*')
	{
		printf("��ʤ��\n");
	}
	else if (Is_Win(board, ROW, COL) ==  'o')
	{
		printf("ϧ�ܣ�\n");
	}
	else if (Is_Win(board, ROW, COL) ==  'Q')
	{
		printf("ƽ��\n");
	}
	DisplayBoard(board, ROW, COL);//��ӡ����
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

//�������
void PlayerMove(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	system("cls");
	DisplayBoard(board, ROW, COL);
	printf("�������>");
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
				printf("�������������ӣ����������룺");
			}
		}
		else
		{
			printf("����Ƿ������������룺");
		}
	}

}
//��������
void PC_move(char board[ROW][COL])
{
	int i = rand() % 3;
	int j = rand() % 3;
	system("cls");
	DisplayBoard(board, ROW, COL);
	printf("��������>\n");
	while (board[i][j] != ' ')
	{
		i = rand() % 3;
		j = rand() % 3;
	}
	board[i][j] = 'o';
}

//�ж������Ƿ����������˷���1������λ�÷���0
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

//�ж���Ӯ
//���Ӯ�����ء�*��
//����Ӯ�����ء�o��
//ƽ�֣����ء�Q��
//���������ء�C��
char Is_Win(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//�ж���
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
		{
			return board[i][0];
		}
		//�ж���
		if ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i]) && board[0][i] != ' ')
		{
			return board[0][i];
		}
	}
	//�ж϶Խ���
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[1][1] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[1][1] && board[1][1] != ' ')
	{
		return board[1][1];
	}
	//ƽ�ַ��ء�Q��
	if (Is_full(board,row,col))
	{
		return 'Q';
	}
	//��ûӮ�򷵻�'C'
	return 'C';
}
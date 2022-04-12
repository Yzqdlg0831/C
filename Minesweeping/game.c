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
		//��ӡ�б�
		if (i == 1) {
			for (j = 0; j <= col; j++)
			{
				printf("%d ", j);
			}
			printf("\n");
		}
		for (j = 1; j <= col; j++)
		{
			//��ӡ�б�
			if (j == 1 )
			{
				printf("%d ", i);
			}
			//��ӡ����
			printf("%c ", show[i][j]);
		}
		printf("\n");
	}
}

//�׵����꣺��1-ROW����1-COL��
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

//������Χ�ж�����
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
//����鿴λ�����ף����ء�1������������ף���show�����Ӧλ�ø�Ϊ��Χ�м����ײ����ء�0��
void FindBOmb(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int Win = 0;
	//Display(mine, ROW, COL);
	while (Win < row * col - MINE)
	{
		printf("��������Ҫ�鿴������->");
		scanf("%d%d", &i, &j);
		if (i > 0 && i <= ROW && j > 0 && j <= COL)
		{
			//�ж��Ƿ�����
			if (mine[i][j] == '1')
			{
				printf("���ź����㱻ը���ˣ�\n");
				break;
			}
			else
			{
				//�ж��Ƿ����������
				if (show[i][j] == '*')
				{
					show[i][j] = DisplayBomb(mine, i, j) + '0';
					Display(show, ROW, COL);
					Win++;
				}
				else
				{
					printf("�Ѿ��鿴�����λ��\n");
				}
			}
		}
		else
		{
			printf("����Ƿ���\n");
		}
	}
	if (Win == row * col - MINE)
	{
		printf("��ϲ�㣡�ɹ��Ų������е��ף�\n");
	}
}

void game()
{
	//������������
	char mine[ROWS][COLS] = { 0 };//����׵���Ϣ
	char show[ROWS][COLS] = { 0 };//����Ų�����׵���Ϣ
	//��ʼ��mine����Ϊȫ��0��
	InitBoard(mine, ROWS, COLS, '0');
	//��ʼ��show����Ϊȫ��*��
	InitBoard(show, ROWS, COLS, '*');
	//print(mine, ROWS, COLS);
	//print(show, ROWS, COLS);
	//��ӡ����
	Display(show, ROW, COL);
	//������
	Bomb(mine,ROW,COL);
	//Display(mine, ROW, COL);
	FindBOmb(mine, show, ROW, COL);

}
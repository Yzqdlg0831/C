#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int main()
{
	printf("						     С�������Թ�С��Ϸ \n\n");

	printf("______________________________________________________________________________________________________________________\n");

	printf("							��ʼ��Ϸ  1\n\n");

	printf("							��Ϸ����  2\n\n");

	printf("							��Ϸ����  3\n\n");

	printf("							�ر���Ϸ  4\n\n");

	int k;
	scanf_s("%d", &k);
	system("cls");
	if (k == 1)
	{
		printf("ʹ��adsw�������������ƶ�\n\n\n");
		char a[100][100] = { "######",
							"#o #  ",
							"# ## #",
							"#  # #",
							"##   #",
							"######" };
		int i, x = 1, y = 1;//p,q�洢�Թ����ڵ�λ��
		for (i = 0; i < 6; i++)
			puts(a[i]);
		char ch;
		int count = 0;
		while (x != 1 || y != 5)
		{
			ch = _getch();
			count++;
			if (ch == 's')
			{
				if (a[x + 1][y] != '#')
				{
					a[x][y] = ' ';
					x++;
					a[x][y] = 'o';
				}
			}
			if (ch == 'w')
			{
				if (a[x - 1][y] != '#')
				{
					a[x][y] = ' ';
					x--;
					a[x][y] = 'o';
				}
			}
			if (ch == 'a')
			{
				if (a[x][y - 1] != '#')
				{
					a[x][y] = ' ';
					y--;
					a[x][y] = 'o';
				}
			}
			if (ch == 'd')
			{
				if (a[x][y + 1] != '#')
				{
					a[x][y] = ' ';
					y++;
					a[x][y] = 'o';
				}
			}

			system("cls");

			if (x == 1 && y == 5)

				printf("�ɹ�����\n\n\n");

			for (i = 0; i < 6; i++)

				puts(a[i]);

		}
		printf("��һ������%d��\n\n", count);
	}
	else if (k == 4)

		printf("��Ϸ����\n\n");

	else if (k == 2)

		printf("��qq���֣���ս�裬����...\n\n\n");

	else if (k == 3)

		printf("����ϵ���ߣ�������������Ҫ����Ϸ���ã�����CSDN����2654501228\n\n\n");

	system("pause");

	return 0;
}
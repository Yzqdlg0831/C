#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
int main()
{
	printf("						     小球球走迷宫小游戏 \n\n");

	printf("______________________________________________________________________________________________________________________\n");

	printf("							开始游戏  1\n\n");

	printf("							游戏音量  2\n\n");

	printf("							游戏设置  3\n\n");

	printf("							关闭游戏  4\n\n");

	int k;
	scanf_s("%d", &k);
	system("cls");
	if (k == 1)
	{
		printf("使用adsw控制上下左右移动\n\n\n");
		char a[100][100] = { "######",
							"#o #  ",
							"# ## #",
							"#  # #",
							"##   #",
							"######" };
		int i, x = 1, y = 1;//p,q存储迷宫出口的位置
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

				printf("成功过关\n\n\n");

			for (i = 0; i < 6; i++)

				puts(a[i]);

		}
		printf("你一共走了%d步\n\n", count);
	}
	else if (k == 4)

		printf("游戏结束\n\n");

	else if (k == 2)

		printf("打开qq音乐，放战歌，乌拉...\n\n\n");

	else if (k == 3)

		printf("请联系作者，并告诉他你想要的游戏设置，访问CSDN——2654501228\n\n\n");

	system("pause");

	return 0;
}
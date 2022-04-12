#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		meun();
		printf("扫雷游戏>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("推出游戏！");
			break;
		default:
			printf("选择错误！");
			break;
		}
	} while (input);

	return 0;
}
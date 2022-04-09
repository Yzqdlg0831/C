#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void meun()
{
	printf("***************************\n");
	printf("******    1.Play     ******\n");
	printf("******    0.exit     ******\n");
	printf("***************************\n");
}

void game()
{
	//rand生成的随机值范围0--0x7fff（32767）
	int num = rand() % 100 + 1;
	int n = 0;
	printf("猜数字开始！！！\n");
	while (1)
	{
		printf("请输入您要猜的数字：");
		scanf("%d", &n);
		if (n > num)
		{
			printf("猜大了！\n");
		}
		else if (n < num)
		{
			printf("猜小了！\n");
		}
		else
		{
			printf("恭喜您！猜对了！！！\n");
			break;
		}
	}
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{  
		//打印菜单
		meun();
		printf("\n请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏！\n");
			break;
		default:
			printf("选择错误！请重新选择\n");
			break;
		}
	} while (input);
	return 0;
}
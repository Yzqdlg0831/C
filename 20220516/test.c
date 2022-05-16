#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a[4][4], b[4][4], i, j;
	printf("input 16 numbers:\n");



	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			scanf("%d", &a[i][j]);
			b[3 - j][i] = a[i][j];

		}
	}
	printf("shuzu a:\n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}

	printf("逆时针旋转的矩阵为: \n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%4d", b[i][j]);


		}printf("\n");


	}
	system("pause");
	//getchar();
	return 0;
}
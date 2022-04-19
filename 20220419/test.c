#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
int main()
{
	char a = -128;//-128 ---> 可以理解为 -0
	printf("%d", a);
	return 0;
}
//判断大小端
int main1()
{
	int i = 1;
	char* p = (char*)&i;
	if (1 == *p)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{

	return 0;
}

int main0()
{
	int i = -20;
	unsigned int j = 10;
	printf("%d,%u", i + j, i + j);//-10,4294967286
	return 0;
}
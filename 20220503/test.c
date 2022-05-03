#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	//int arr[] = { 1,2,3,4,5 };
	//int(*p)[5] = arr;
	//printf("%p\n", p+1);
	//printf("%p\n", *p);
	//printf("%p\n", *p+1);
	//printf("%d\n", **p);
	char c2[] = { '\x10','\xa','\8' };
	double x[5] = { 2.0,4.0,6.0,8.0,10.0 };
	char c1[] = { '1','2','3','4','5' };
	int y[5 + 3] = { 0,1,3,5,7,9 };
	printf("%c", c2[2]);
	return 0;
}
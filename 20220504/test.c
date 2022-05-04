#define _CRT_SECURE_NO_WARNINGS 1
//输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。
//比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
//1. 用返回一个整数列表来代替打印
//2. n 为正整数，0 < n <= 5

#include<stdio.h>
#include<math.h>
#include<malloc.h>
static int arr[100001] = { 0 };
int* printNumbers(int n, int* returnSize)
{
	//将n设为最大值
	*returnSize= pow(10, n) - 1;
	int i = 0;
	for (i = 0; i < *returnSize; i++)
	{
		arr[i] = i + 1;
	}
	return arr;	
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int len = 0;
	int* a = printNumbers(n, &len);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", *(a + i));
	}
	return 0;
}
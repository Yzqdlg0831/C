#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
//2. ACM编程题 标题：倒置字符串 
//将一句话的单词进行倒置，标点不倒置。
//比如 I like beijing.经过函数后变为：beijing.like I 
//输入描述： 每个测试输入包含1个测试用例： I like beijing.输入用例长度不超过100 
//输出描述： 依次输出倒置之后的字符串, 以空格分割 示例1 : 输入I like beijing.输出beijing.like I
void reverse(char* left, char* right)
{
	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}

int main()
{
	char arr[] = "I like beijing.";
	char* left = arr;
	char* right = arr + strlen(arr) - 1;
	//交换整个句子
	reverse(left, right);
	//交换每个单词
	while (*left)
	{
		right = left;
		while (*right != ' ' && *right)
		{
			right++;
		}
		reverse(left, right - 1);
		printf("%s\n", arr);
		if (*right)
		{
			//right还没指向\0
			left = right + 1;
		}
		else
		{
			//right指向\0
			left = right;
		}
	}
	printf("%s\n", arr);
	return 0;
}


//1. ACM编程题 标题：求最小公倍数 
//正整数A和正整数B的最小公倍数是指能被A和B整除的最小的正整数值，
//设计一个算法，求输入A和B的最小公倍数。
//输入描述： 输入两个正整数A和B。
//输出描述： 输出A和B的最小公倍数。

int Least_common_multiple(int x, int y)
{
	int a = x;
	int b = y;
	while (a % b)
	{
		int tmp = a;
		a = b;
		b = tmp % b;
	}
	return  x * y / b;
}

int main1()
{
	int a = 72;
	int b = 28;
	int c = Least_common_multiple(a, b);
	printf("%d", c);
	return 0;
}
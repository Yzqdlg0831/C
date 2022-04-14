#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
	int n = 0;
	scanf("%d", &n);
	//打印上半部分
	for (int i = 1; i <= n; i++)
	{
		//打印空格
		for (int j = 1; j < n - i + 1; j++)
		{
			printf(" ");
		}
		//打印*
		for (int j = n - i + 1; j < 2 * i + n - i; j++)
		{
			printf("*");
		}
		//换行
		printf("\n");
	}
	//打印下半部分
	for (int i = n - 1; i > 0; i--)
	{
		//打印空格
		for (int j = 1; j < n - i + 1; j++)
		{
			printf(" ");
		}
		//打印*
		for (int j = n - i + 1; j < 2 * i + n - i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
int digits(int i)
{
	int count = 0;
	while (i > 0)
	{
		i = i / 10;
		count++;
	}
	return count;
}

int main5()
{
	int i = 0;
	for (i = 1; i < 100000; i++)
	{
		double sum = 0;
		int t = i;
		int n = digits(i);
		while (t)
		{
			sum += pow(t%10, n);
			t = t / 10;
		}
		if (sum == i)
		{
			printf("%d ", i);
		}
	}
	return 0;
}

int main4()
{
	int sum = 0;
	int n = 0;
	scanf("%d", &n);
	int m = n;
	for (int i = 0; i < 5; i++)
	{
		//printf("%d\n", n);
		sum += n;
		n = n * 10 + m;
	}
	printf("%d", sum);
	return 0;
}

void reverse(char* str, int len)
{
	char* right = &str[len - 1];
	char* left = str;
	char tmp = ' ';
	while (left < right)
	{
		tmp = *right;
		*right = *left;
		*left = tmp;
		right--;
		left++;
	}
}
int main3()
{
	char str[10000];
	gets(str);
	//reverse(str, strlen(str));
	printf("%s", str);
	return 0;
}

int main2()
{
	char arr[10000] = { 0 };
	gets(arr);
	for (int i = (int)strlen(arr); i >= 0; i--)
	{
		printf("%c", arr[i]);
	}
	return 0;
}

int main1()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* p = arr;
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", *(p + i));
	}
	return 0;
}

int main0()
{
	//int a = 10;
	//int* p = &a;
	//32位平台指针大小为4个字节，64位平台为8个字节
	//指针类型决定了在解引用的是一次能访问多少字节（指针的权限）
	//指针类型决定了指针向前或者向后走一步，走多大距离（单位是字节）
	//int* --->访问四个字节
	//char*--->访问一个字节	
	//eg：
	int a = 0x11223344;
	int* pa = &a;
	int b = 0x11223344;
	char* pb = &b;

	*pa = 0;
	*pb = 0;

	printf("%x\n", a);//00000000
	printf("%x\n", b);//11223300

	return 0;
}
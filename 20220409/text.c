#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>


void My_multiplication_tables(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%2d * %2d = %3d  ", i, j, i * j);
		}
		printf("\n");
	}
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	My_multiplication_tables(n);
	return 0;
}

void Swap(int *pa,int *pb)
{
	int t = *pa;
	*pa = *pb;
	*pb = t;
}

int main4()
{
	int a = 10;
	int b = 20;
	printf("交换前a = %d,b = %d\n", a, b);
	Swap(&a, &b);
	printf("交换后a = %d,b = %d", a, b);
	return 0;
}

void leap_year(int year)
{
	if (((year % 4 == 0) && (year % 400 != 0)) || (year % 400 == 0))
	{
		printf("%d年是闰年！！！", year);
	}
	else
	{
		printf("%d年不是闰年！！！", year);
	}
}

int main3()
{
	int year = 0;
	printf("请输入年份：");
	scanf("%d", &year);
	leap_year(year);
	return 0;
}


int PrimeNumber(int n)
{
	if (n % 2 == 0) 
	{
		return 0;
	}
	else 
	{
		for (int i = 3; i <= sqrt(n); i = i + 2)
		{
			if (n % i == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main2()
{
	for (int i = 100; i <= 200; i++)
	{
		if (PrimeNumber(i))
		{
			printf("%d ", i);
		}
	}
	return 0;
}


void Swap1(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

int main1()
{
	int a = 10;
	int b = 20;
	Swap(&a, &b);
	printf("%d %d", a, b);
	return 0;
}
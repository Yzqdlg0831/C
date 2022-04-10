#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>

//递归
int Fibonacci1(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return Fibonacci1(n - 1) + Fibonacci1(n - 2);
	}
}
//迭代
int Fibonacci2(int n)
{
	int a = 1;
	int b = 1;
	int c = 1;
	while (n > 2)
	{
		a = b;
		b = c;
		c = a + b;
		n--;
	}
	return c;
}

int main11()
{
	int n = 0;
	scanf("%d", &n);
	int ret = Fibonacci1(n);
	printf("%d\n", ret);
	ret = Fibonacci2(n);
	printf("%d\n", ret);
	return 0;
}

int Pow(int n, int k)
{
	if (k == 1)
	{
		return n;
	}
	else if (n == 1 || k == 0)
	{
		return 1;
	}
	else
	{
		return n * Pow(n, k - 1);
	}
}

int main9()
{
	int n = 0;
	int k = 0;
	scanf("%d%d", &n, &k);
	printf("%d", Pow(n, k));
	return 0;
}


int DigitSum(int n)
{
	if (n > 9)
	{
		return n % 10 + DigitSum(n / 10);
	}
	return n;
}
int main8()
{
	int n = 0;
	scanf("%d", &n);
	printf("%d", DigitSum(n));
	return 0;
}


void reverse_string(char* string)
{
	int sz = strlen(string);
	int tmp = *string;
	*string = *(string + sz - 1);
	*(string + sz - 1) = '\0';//因为只需要交换一半字符，所以本次交换完后最后一个字符变成'\0'。
	if (strlen(string + 1) > 1)
	{
		reverse_string(string + 1);
	}
	*(string + sz - 1) = tmp;
}

int main6()
{
	char arr[] = "abcdef";
	reverse_string(arr);
	for (int i = 0; i < strlen(arr); i++)
	{
		printf("%c", arr[i]);
	}
	return 0;
}

//递归
int fac1(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else
	{
		return n * fac1(n - 1);
	}
}
//迭代
int fac2(int n)
{
	int ret = 1;
	for (int i = 1; i <= n; i++)
	{
		ret *= i;
	}
	return ret;
}
int main5()
{
	printf("%d\n", fac1(5));
	printf("%d\n", fac2(5));
	return 0;
}

void print(int n)
{
	if (n > 9)
	{
		print(n / 10);
	}
	printf("%d ",n % 10);
}

int main7()
{
	int n = 123456;
	print(n);
	return 0;
}
//递归
int my_strlen1(char *s)
{
	if (*s == '\0')
	{
		return 0;
	}
	return my_strlen1(++s) + 1;
}
//迭代
int my_strlen2(char* s)
{
	int count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return count;
}
int main3()
{
	char arr[] = "abcefg";
	printf("%d\n", my_strlen1(arr));
	printf("%d\n", my_strlen2(arr));
	return 0;
}

int main2()
{

	printf("%d", printf("%d", printf("%d", 432)));
	return 0;
}


int numpulsone()
{
	static n = 0;
	return n++;
}

int main1()
{

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", numpulsone());
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
reverse_string(char* string)

int main()
{

	return 0;
}

//µİ¹é
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
//µü´ú
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

int main6()
{
	int n = 123456;
	print(n);
	return 0;
}
//µİ¹é
int my_strlen1(char *s)
{
	if (*s == '\0')
	{
		return 0;
	}
	return my_strlen1(++s) + 1;
}
//µü´ú
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
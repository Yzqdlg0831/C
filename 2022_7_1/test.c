#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
//指针
int ADD(int x, int y)
{
	return x + y;
}

void test()
{}
//int main()
//{
//	//指针地址
//	int (*pf)(int, int) = &ADD;
//	void (*pt)() = &test;
//	//printf("%p\n%p", &ADD, pf);
//	//printf("\n%p\n%p", &test, pt);
//	//对指针地址解引用（或者不解引用也可以），可以调用指向的函数
//	//int sum = (*pf)(3, 4);
//	int sum = pf(3, 4);
//	printf("%d", sum);
//	//数组指针
//	int arr[5];
//	int(*pa)[5] = &arr;
//	return 0;
//}

/*
写一个函数，判断一个字符串是否为另外一个字符串旋转之后的字符串。
例如：给定s1 =AABCD和s2 = BCDAA，返回1
给定s1=abcd和s2=ACBD，返回0.
AABCD左旋一个字符得到ABCDA
AABCD左旋两个字符得到BCDAA
AABCD右旋一个字符得到DAABC
AABCDAABCD
*/

int findRound(const char* src, char* find)
{
	char tmp[1000];
	strcpy(tmp, src);
	strcat(tmp, src);
	//char* ret;
	//ret = strstr(tmp, find);
	//printf("%s\n%s\n", tmp,ret);
	return strstr(tmp, find) != NULL;
}

int main()
{
	//
	//1.把0强制类型转换为void（*）（）类型函数指针
	//2.再去调用0地址处这个参数为无参，返回类型是void的函数
	//
	//(*(void (*)())0)();
	//
	//
	//signal 是一个函数声明
	//这个函数的参数有两个，第一个是int类型，第二个是
	//函数指针类型，该指针指向一个返回值为void，参数为int类型的
	//
	//signal函数的返回类型也是函数指针，该指针指向的函数返回值是
	//void，参数为int
	//
	//void(  *signal( int, void(*)(int) )  )(int);
	////如果要简化这段代码可以按下面方法写
	//typedef void(*pfun_t)(int);
	//pfun_t signal(int, void(*)(int));
	char s1[] = "AABCDD";
	char s2[] = "DDAABC";
	printf("%d\n", findRound(s1, s2));
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{

	char a = ' ';
	while (scanf("%c ", &a) != EOF)
	{
		if (a == 'A' || a == 'a' || a == 'E' || a == 'e' || a == 'I'
			|| a == 'i' || a == 'O' || a == 'o' || a == 'U' || a == 'u')
		{
			printf("Vowel\n");
		}
		else
		{
			printf("Consonant\n");
		}
	}
	return 0;
}

int main4()
{

	int a = 0;
	while (scanf("%d", &a) != EOF)
	{
		if (a % 2 == 0)
		{
			printf("Even\n");
		}
		else
		{
			printf("Odd\n");
		}
	}

	return 0;
}

int main2()
{
	//算术转换 比如 int类型和double类型运算时，int会转换为double进行运算
	//long double
	//double
	//float
	//unsigned long int
	//long int
	//unsigned int
	//int
	//如果某个操作数的类型在上面这个列表中排名较低，那么首先要转换为另外一个操作数的类型后执行运算。
	//警告：
	//但是算术转换要合理，要不然会有一些潜在的问题。
	//eg:
	/*float f = 3.14;
	int num = f;*///隐式转换，会有精度丢失
	//整形提升 char或short与其他类型进行运算时会发生整形提升
	//short
	//char
	char a = 5;
	char b = 126;
	char c = a + b;//c = -125  在下面一个main函数有详解
	int m = c;
	printf("%d", m);//-125
	return 0;
}

int main1()
{
	char a = 5;
	char b = 126;
	char c = a + b;
	//发生整型提升，表达式中各种长度可能小于int长度的整型值，都必须先转换为int或unsigned int，然后才能送入CPU去执行运算。
	//                                   转换为char类型8个字节
	//a-->00000000000000000000000000000101->00000101 
	//b-->00000000000000000000000001111110->01111110 
   //a+b->00000000000000000000000010000011->10000011
	//char 类型输出整形时发生整形提升即 
    //c:10000011 ->11111111111111111111111110000011(补码)
	//->11111111111111111111111110000010(反码)->10000000000000000000000001111101（源码）->-125
	printf("%d\n", c);
	//示例：
	printf("%d\n", sizeof(a));//1
	printf("%d\n", sizeof(+a));//4
	printf("%d\n", sizeof(-a));//4
	return 0;
}
int main0()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("%d\n", arr[9]);
	printf("%d\n", 9[arr]);
	return 0;
}
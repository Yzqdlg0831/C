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
	//����ת�� ���� int���ͺ�double��������ʱ��int��ת��Ϊdouble��������
	//long double
	//double
	//float
	//unsigned long int
	//long int
	//unsigned int
	//int
	//���ĳ������������������������б��������ϵͣ���ô����Ҫת��Ϊ����һ�������������ͺ�ִ�����㡣
	//���棺
	//��������ת��Ҫ����Ҫ��Ȼ����һЩǱ�ڵ����⡣
	//eg:
	/*float f = 3.14;
	int num = f;*///��ʽת�������о��ȶ�ʧ
	//�������� char��short���������ͽ�������ʱ�ᷢ����������
	//short
	//char
	char a = 5;
	char b = 126;
	char c = a + b;//c = -125  ������һ��main���������
	int m = c;
	printf("%d", m);//-125
	return 0;
}

int main1()
{
	char a = 5;
	char b = 126;
	char c = a + b;
	//�����������������ʽ�и��ֳ��ȿ���С��int���ȵ�����ֵ����������ת��Ϊint��unsigned int��Ȼ���������CPUȥִ�����㡣
	//                                   ת��Ϊchar����8���ֽ�
	//a-->00000000000000000000000000000101->00000101 
	//b-->00000000000000000000000001111110->01111110 
   //a+b->00000000000000000000000010000011->10000011
	//char �����������ʱ�������������� 
    //c:10000011 ->11111111111111111111111110000011(����)
	//->11111111111111111111111110000010(����)->10000000000000000000000001111101��Դ�룩->-125
	printf("%d\n", c);
	//ʾ����
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
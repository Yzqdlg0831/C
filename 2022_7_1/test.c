#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<stdio.h>
//ָ��
int ADD(int x, int y)
{
	return x + y;
}

void test()
{}
//int main()
//{
//	//ָ���ַ
//	int (*pf)(int, int) = &ADD;
//	void (*pt)() = &test;
//	//printf("%p\n%p", &ADD, pf);
//	//printf("\n%p\n%p", &test, pt);
//	//��ָ���ַ�����ã����߲�������Ҳ���ԣ������Ե���ָ��ĺ���
//	//int sum = (*pf)(3, 4);
//	int sum = pf(3, 4);
//	printf("%d", sum);
//	//����ָ��
//	int arr[5];
//	int(*pa)[5] = &arr;
//	return 0;
//}

/*
дһ���������ж�һ���ַ����Ƿ�Ϊ����һ���ַ�����ת֮����ַ�����
���磺����s1 =AABCD��s2 = BCDAA������1
����s1=abcd��s2=ACBD������0.
AABCD����һ���ַ��õ�ABCDA
AABCD���������ַ��õ�BCDAA
AABCD����һ���ַ��õ�DAABC
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
	//1.��0ǿ������ת��Ϊvoid��*���������ͺ���ָ��
	//2.��ȥ����0��ַ���������Ϊ�޲Σ�����������void�ĺ���
	//
	//(*(void (*)())0)();
	//
	//
	//signal ��һ����������
	//��������Ĳ�������������һ����int���ͣ��ڶ�����
	//����ָ�����ͣ���ָ��ָ��һ������ֵΪvoid������Ϊint���͵�
	//
	//signal�����ķ�������Ҳ�Ǻ���ָ�룬��ָ��ָ��ĺ�������ֵ��
	//void������Ϊint
	//
	//void(  *signal( int, void(*)(int) )  )(int);
	////���Ҫ����δ�����԰����淽��д
	//typedef void(*pfun_t)(int);
	//pfun_t signal(int, void(*)(int));
	char s1[] = "AABCDD";
	char s2[] = "DDAABC";
	printf("%d\n", findRound(s1, s2));
	return 0;
}
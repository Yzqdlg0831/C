#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
//2. ACM����� ���⣺�����ַ��� 
//��һ�仰�ĵ��ʽ��е��ã���㲻���á�
//���� I like beijing.�����������Ϊ��beijing.like I 
//���������� ÿ�������������1������������ I like beijing.�����������Ȳ�����100 
//��������� �����������֮����ַ���, �Կո�ָ� ʾ��1 : ����I like beijing.���beijing.like I
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
	//������������
	reverse(left, right);
	//����ÿ������
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
			//right��ûָ��\0
			left = right + 1;
		}
		else
		{
			//rightָ��\0
			left = right;
		}
	}
	printf("%s\n", arr);
	return 0;
}


//1. ACM����� ���⣺����С������ 
//������A��������B����С��������ָ�ܱ�A��B��������С��������ֵ��
//���һ���㷨��������A��B����С��������
//���������� ��������������A��B��
//��������� ���A��B����С��������

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
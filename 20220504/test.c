#define _CRT_SECURE_NO_WARNINGS 1
//�������� n����˳���ӡ���� 1 ������ n λʮ��������
//�������� 3�����ӡ�� 1��2��3 һֱ������ 3 λ�� 999��
//1. �÷���һ�������б��������ӡ
//2. n Ϊ��������0 < n <= 5

#include<stdio.h>
#include<math.h>
#include<malloc.h>
static int arr[100001] = { 0 };
int* printNumbers(int n, int* returnSize)
{
	//��n��Ϊ���ֵ
	*returnSize= pow(10, n) - 1;
	int i = 0;
	for (i = 0; i < *returnSize; i++)
	{
		arr[i] = i + 1;
	}
	return arr;	
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int len = 0;
	int* a = printNumbers(n, &len);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", *(a + i));
	}
	return 0;
}
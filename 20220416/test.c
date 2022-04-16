#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
//����977
//����һ���� �ǵݼ�˳�� ������������� nums��
//���� ÿ�����ֵ�ƽ�� ��ɵ������飬Ҫ��Ҳ�� �ǵݼ�˳�� ����
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    int left = 0;
    int right = numsSize - 1;
    int i = 0;
    int returnRight = numsSize - 1;
    (*returnSize) = numsSize;
    int* ans = malloc(sizeof(int) * numsSize);
    for (i = 0; i < numsSize; i++)
    {
        if (nums[left] * nums[left] > nums[right] * nums[right])
        {
            ans[returnRight--] = nums[left] * nums[left];
            left++;
        }
        else
        {
            ans[returnRight--] = nums[right] * nums[right];
            right--;
        }
    }
    return ans;
}

//����189
//����һ�����飬�������е�Ԫ��������ת k ��λ�ã����� k �ǷǸ���

//�����Լ��
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b, * b = t;
}

void rotate(int* nums, int numsSize, int k) {
    k = k % numsSize;
    int count = gcd(k, numsSize);
    for (int start = 0; start < count; ++start) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % numsSize;
            swap(&nums[next], &prev);
            current = next;
        } while (start != current);
    }
}

int count_number_of_1(int n)
{
	int count = 0;
	while (n)
	{
		//ÿ��ִ�ж����n�Ķ��������������ұߵ�1��ȥ��-----���������㷨ִ�еĴ�����n�Ķ�����λ��1�ĸ���
		//��������ʱ���Ч��
		//����ĳ�����ǲ���2�ı�����ʱ�򣬿���ʹ������������ʽ�����ִֻ��һ����ô����2�ı�����0���⣩�ǷǷǷǳ����������
		n = n & (n - 1);
		count++;
	}
	return count;
}


int main0()
{
    int money = 0;
    int total = 0;
    int empty = 0;


    scanf("%d", &money);

    //����2
    if (money <= 0)
    {
        total = 0;
    }
    else
    {
        total = money * 2 - 1;
    }
    printf("total = %d\n", total);


    return 0;
}

int main()
{
    int drink = 0;//��ˮ����
    int bottle = 0;//��ƿ����
    int money = 0;
    scanf("%d", &money);
    drink = money;
    bottle = drink;
    while (bottle > 1)
    {
        drink += bottle / 2;
        bottle = bottle / 2 + bottle % 2;//���еĿ�ƿ���� = ������ˮ������ + ʣ��Ŀ�ƿ����
    }
    printf("%d", drink);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
//力扣977
//给你一个按 非递减顺序 排序的整数数组 nums，
//返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。
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

//力扣189
//给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数

//求最大公约数
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
		//每次执行都会把n的二进制序列中最右边的1给去掉-----并且这种算法执行的次数是n的二进制位中1的个数
		//大大提高了时间的效率
		//当问某个数是不是2的倍数的时候，可以使用下面这个表达式，如果只执行一次那么就是2的倍数（0除外）非非非非常巧妙！！！！
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

    //方法2
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
    int drink = 0;//汽水数量
    int bottle = 0;//空瓶数量
    int money = 0;
    scanf("%d", &money);
    drink = money;
    bottle = drink;
    while (bottle > 1)
    {
        drink += bottle / 2;
        bottle = bottle / 2 + bottle % 2;//现有的空瓶数量 = 换成汽水的数量 + 剩余的空瓶数量
    }
    printf("%d", drink);
	return 0;
}
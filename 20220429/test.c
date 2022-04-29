#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>


//将数组中的奇数放到数组的前面，偶数放到数组后面
void reverse(int arr[], int sz)
{
	int* left = arr;
	int* right = arr + sz - 1;
	while (left < right)
	{
		while ((left < right) && *left % 2 != 0)
		{
			left++;
		}
		while ((left < right) && *right % 2 == 0)
		{
			right--;
		}

		if (left < right)
		{
			int tmp = *left;
			*left = *right;
			*right = tmp;
			right--;
			left++;
		}
	}

}

int main1()
{
	int arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	reverse(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
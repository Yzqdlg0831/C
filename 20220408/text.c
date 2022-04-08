#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>

int main() {

	char arr[] = { "abcdef" };
	printf("%d\n", (int)(sizeof(arr) / sizeof(arr[0])));
	printf("%d\n", (int)strlen(arr));
	return 0;
}

//二分法查找数组下标
int binarySearch(int arr[], int key, int len)
{
	int left = 0;
	int right = len - 1;
	int mid = left + (right - left) / 2;
	while(right >= left)
	{
		if (key > arr[mid]) {
			left = mid + 1;
			mid = left + (right - left);
		}
		else if (key < arr[mid]) {
			right = mid - 1;
			mid = left + (right - left) / 2;
		}
		else {
			return mid;
			break;
		}
	}
	if (right < left) {
		return -1;
	}

}


int main1() {

	int arr[8] = { 1,2,3,5,6,7,9,13 };
	int key = 1;
	int xiabiao = binarySearch(arr, key, sizeof(arr) / sizeof(arr[0]));
	if (xiabiao >= 0) {
		printf("找到了，下标是:%d", xiabiao);
	}
	else {
		printf("没有找到！！！");
	}
	return 0;
}
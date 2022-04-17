#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//void moveZeroes(int* nums, int numsSize) {
//    int i = 0;
//    int j = 0;
//    for (i = 0; i < numsSize - 1; i++)
//    {
//        for (j = 0; j < numsSize - i - 1; j++)
//        {
//            int tmp = 0;
//            if (nums[j] > nums[j + 1])
//            {
//                tmp = nums[j];
//                nums[j] = nums[j + 1];
//                nums[j + 1] = tmp;
//            }
//        }
//    } 
//    i = 0;
//    while (1)
//    {
//        if(0 == nums[0])
//        {
//            for (j = 0; j < numsSize - 1; j++)
//            {
//                nums[j] = nums[j + 1];
//            }
//            nums[numsSize - 1] = 0;
//            i++;
//        }
//        else
//        {
//            break;
//        }
//        if(numsSize - 1 == i)
//        {
//            break;
//        }
//
//    }
//}
//void moveZeroes(int* nums, int numsSize) {
//    int i = 0;
//    int j = 0;
//    int sz = numsSize;
//    for (i = 0; i < sz; i++)
//    {
//        if (nums[i] == 0)
//        {
//            for (j = i; j < numsSize - 1; j++)
//            {
//                nums[j] = nums[j + 1];
//            }
//            nums[numsSize - 1] = 0;
//            sz--;
//            i--;
//        }
//    }
//}
//力扣283
//给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//请注意 ，必须在不复制数组的情况下原地对数组进行操作。
void moveZeroes(int* nums, int numsSize) {
    int left = 0, right = 0;
    while (right < numsSize) {
        if (nums[right]) {
            int tmp = nums[right];
            nums[right] = nums[left];
            nums[left] = tmp;
            left++;
        }
        right++;
    }
}

//力扣167
//  给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，
//请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数
//分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。
//以长度为 2 的整数数组[index1, index2] 的形式返回这两个整数的下标 index1 和 index2。
//你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。
//你所设计的解决方案必须只使用常量级的额外空间。
//来源：力扣（LeetCode）
//链接：https ://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    for (int i = 0; i < numbersSize; i++)
    {
        int left = i + 1;
        int right = numbersSize - 1;
        int tmp = (right - left) / 2 + left;
        while (right >= left)
        {
            tmp = (right - left) / 2 + left;
            if ((numbers[i] + numbers[tmp]) > target)
            {
                right = tmp - 1;
            }
            else if ((numbers[i] + numbers[tmp]) < target)
            {
                left = tmp + 1;
            }
            else
            {
                break;
            }
        }
        if ((numbers[i] + numbers[tmp]) == target)
        {
            ret[1] = i > tmp ? i + 1 : tmp + 1;
            ret[0] = i > tmp ? tmp + 1 : i + 1;
            return ret;
        }
    }
    ret[0] = -1, ret[1] = -1;
    return ret;
}

int main()
{
    int arr[] = { 1,3,12,0,0};
    moveZeroes(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);  
    }
    
	return 0;
}
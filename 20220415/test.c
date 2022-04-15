#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
//力扣35
//给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
//如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
//请必须使用时间复杂度为 O(log n) 的算法。

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    int tmp = (right - left) / 2 + left;
    while (right >= left)
    {
        tmp = (right - left) / 2 + left;
        if (target > *(nums + tmp))
        {
            left = tmp + 1;
        }
        else if (target < *(nums + tmp))
        {
            right = tmp - 1;
        }
        else
        {
            return tmp;
        }
    }
    if (target > *(nums + tmp))
    {
        return tmp + 1;
    }
    else
    {
        return tmp;
    }
}

//力扣278
//你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。
//由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
//假设你有 n 个版本[1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
//你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。
//实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 0;
    int right = n;
    int tmp = (right - left) / 2 + left;
    while (right >= left)
    {
        tmp = (right - left) / 2 + left;
        if (isBadVersion(tmp))
        {
            right = tmp - 1;
        }
        else
        {
            left = tmp + 1;
        }
    }
    if (isBadVersion(tmp))
    {
        return tmp;
    }
    else
    {
        return tmp + 1;
    }
}

//力扣704
//给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target ，
//写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 - 1。
int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    while (right >= left)
    {
        int tmp = (right - left) / 2 + left;
        if (target > *(nums + tmp))
        {
            left = tmp + 1;
        }
        else if (target < *(nums + tmp))
        {
            right = tmp - 1;
        }
        else
        {
            return tmp;
        }
    }
    return -1;
}

int main()
{
	return 0;
}
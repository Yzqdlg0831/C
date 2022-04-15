#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
//����35
//����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ����������������
//���Ŀ��ֵ�������������У����������ᱻ��˳������λ�á�
//�����ʹ��ʱ�临�Ӷ�Ϊ O(log n) ���㷨��

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

//����278
//���ǲ�Ʒ����Ŀǰ���ڴ���һ���Ŷӿ����µĲ�Ʒ�����ҵ��ǣ���Ĳ�Ʒ�����°汾û��ͨ��������⡣
//����ÿ���汾���ǻ���֮ǰ�İ汾�����ģ����Դ���İ汾֮������а汾���Ǵ�ġ�
//�������� n ���汾[1, 2, ..., n]�������ҳ�����֮�����а汾����ĵ�һ������İ汾��
//�����ͨ������ bool isBadVersion(version) �ӿ����жϰ汾�� version �Ƿ��ڵ�Ԫ�����г���
//ʵ��һ�����������ҵ�һ������İ汾����Ӧ�þ������ٶԵ��� API �Ĵ�����
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

//����704
//����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target ��
//дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� - 1��
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
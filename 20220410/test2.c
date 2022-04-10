#define _CRT_SECURE_NO_WARNINGS 1

#include <string.h>
#include <stdio.h>


void swap_array(char A[], char B[], int len)
{
    for (int i = 0; i < len; i++)
    {
        char tmp = '0';
        tmp = A[i];
        A[i] = B[i];
        B[i] = tmp;
    }
}

int main15()
{
    char A[5] = { 'a','a','a','a','a' };
    char B[5] = { 'b','b','b','b','b' };
    swap_array(A, B, sizeof(A)/sizeof(A[0]));
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
    {
        printf("%c ", A[i]);
    }
    printf("\n");
    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++)
    {
        printf("%c ", B[i]);
    }
    return 0;
}

void init(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = i;
    }
}

void print1(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void reverse(int arr[], int len)
{
    int right = len - 1;
    int left = 0;
    int tmp = 0;
    while (right > left)
    {
        tmp = arr[right];
        arr[right] = arr[left];
        arr[left] = tmp;
        right--;
        left++;
    }
}

int main14()
{
    int arr[6];
    int len = sizeof(arr) / sizeof(arr[0]);
    init(arr, len);
    print1(arr, len);
    reverse(arr, len);
    print1(arr, len);
    return 0;
}

//√∞≈›≈≈–Ú
void bubble_sort(int arr[], int len)
{
    int tmp = arr[0];
    for (int i = 0; i < len - 1; i++)//’“µƒ¥Œ ˝
    {
        for (int j = 0; j < len - i -1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main13()
{
    int arr[] = { 5,6,8,2,3,1,56,94,23,7,62,4,61,36,9,0 };
    int len = sizeof(arr)/sizeof(arr[0]);
    bubble_sort(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}

int main12()
{
    int arr[] = { 1,2,(3,4,5),5 };
    printf("%d\n", sizeof(arr));
    printf("%d", arr[2]);
    return 0;
}
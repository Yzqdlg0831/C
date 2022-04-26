#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
{
    int len = 0;
    int arr[50] = { 0 };
    int deletenum = 0;
    int count = 0;
    scanf("%d", &len);
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &deletenum);
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == deletenum)
        {
            int j = i;
            for (; j < len - count - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            arr[j] = 0;
            count++;
            i--;
        }
    }
    for (int i = 0; i < len - count; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}

int main2()
{
    int arr[10][10] = { 0 };
    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", arr[j][i]);
        }
        printf("\n");
    }
}

int main1()
{
    int n = 0;
    while (scanf("%d ", &n) != EOF)
    {
        int k = n / 12;
        printf("%d", k * 4 + 2);
    }
    return 0;
}

int main0()
{
    int n;
    scanf("%d", &n);
    int i;
    int k = 0;
    int a[1000] = { 0 };
    for (i = 0; i < n; i++)
    {
        scanf("%d", &k);
        a[k]++;
    }
    for (i = 1; i < 100001; i++)
    {
        if (a[i])
            printf("%d ", i);
    }
    return 0;
}
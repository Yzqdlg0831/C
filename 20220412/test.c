#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int main()
{
    //�������м����������������
    int a = 12;
    int b = 21;
    printf("����ǰ��\na = %d\nb = %d\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("������\na = %d\nb = %d\n", a, b);
    return 0;
}

int NumberOf1(int n) {
    int count = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((n >> i) & 1)
        {
            count++;
        }
    }
    return count;
}

void Printbit(int num)
{
    printf("����λ��");
    for (int i = 31; i >= 1; i -= 2)
    {
        printf("%d ", (num >> i) & 1);
    }
    printf("\n");
    printf("ż��λ��");
    for (int i = 30; i >= 0; i -= 2)
    {
        printf("%d ", (num >> i) & 1);
    }
    printf("\n");
}

int main2()
{
    Printbit(14);
    printf("\n%d", NumberOf1(-1));
    return 0;
}

int main1()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int count = 0;
    scanf("%d %d", &a, &b);
    c = a ^ b;
    for (int i = 0; i < 32; i++)
    {
        if ((c >> i) & 1)
        {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}
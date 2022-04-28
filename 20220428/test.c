#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
//KiKi想获得某年某月有多少天，请帮他编程实现。输入年份和月份，计算这一年这个月有多少天。
int is_leap_year(int year)
{
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        return 1;
    }
    return 0;
}
int main()
{
    int year = 0;
    int month = 0;
    int arr1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
    while (scanf("%d %d", &year, &month) != EOF)
    {
        if (is_leap_year(year))
        {
            printf("%d\n", arr2[month - 1]);
        }
        else
        {
            printf("%d\n", arr1[month - 1]);
        }
    }
    return 0;
}
//从键盘输入a, b, c的值，编程计算并输出一元二次方程ax2 + bx + c = 0的根，
//当a = 0时，输出“Not quadratic equation”，当a ≠ 0时，
//根据△ = b2 - 4 * a * c的三种情况计算并输出方程的根。
int main4()
{
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    while (scanf("%f %f %f", &a, &b, &c) != EOF)
    {
        if (a == 0)
        {
            printf("Not quadratic equation\n");
        }
        else
        {
            double q = b * b - 4 * a * c;
            if (q == 0)
            {
                if (b != 0)
                {
                    printf("x1=x2=%.2f\n", -b / (2 * a));
                }
                else
                {
                    printf("x1=x2=%.2f\n", 0.0);
                }
            }
            else if (q > 0)
            {
                printf("x1=%.2f;x2=%.2f\n",
                    (-b - sqrt(q)) / (2 * a), (-b + sqrt(q)) / (2 * a));
            }
            else
            {
                if (a > 0)
                {
                    printf("x1=%.2f-%.2fi;x2=%.2f+%.2fi\n",
                        -b / (2 * a), sqrt(-q) / (2 * a), -b / (2 * a), sqrt(-q) / (2 * a));
                }
                else
                {
                    printf("x1=%.2f-%.2fi;x2=%.2f+%.2fi\n",
                        -b / (2 * a), -sqrt(-q) / (2 * a), -b / (2 * a), -sqrt(-q) / (2 * a));
                }
            }
        }
    }
    return 0;
}
//公务员面试现场打分。有7位考官，从键盘输入若干组成绩，每组7个分数（百分制），
//去掉一个最高分和一个最低分，输出每组的平均成绩。
//（注：本题有多组输入）
int main3()
{
    char arr[7] = { 0 };
    while (scanf("%d %d %d %d %d %d %d",
        arr, arr + 1, arr + 2, arr + 3, arr + 4, arr + 5, arr + 6) != EOF)
    {
        int max = arr[0];
        int min = arr[0];
        float sum = 0;
        for (int i = 0; i < 7; i++)
        {
            if (max < arr[i])
            {
                max = arr[i];
            }
            if (min > arr[i])
            {
                min = arr[i];
            }
            sum += arr[i];
        }
        printf("%.2f\n", (sum - max - min) / 5.0);
    }
    return 0;
}
//KiKi学习了循环，BoBo老师给他出了一系列打印图案的练习，该任务是打印用“* ”组成的带空格直角三角形图案。
int main2()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                printf("  ");
            }
            for (int j = 0; j <= i; j++)
            {
                printf("* ");
            }
            printf("\n");
        }
    }
    return 0;
}

//不使用累计乘法的基础上，通过移位运算（ << ）实现2的n次方的计算。
int main1()
{
    int n = 0;
    scanf("%d", &n);
    printf("%d", 1 << n);
    return 0;
}
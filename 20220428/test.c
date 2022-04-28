#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
//KiKi����ĳ��ĳ���ж����죬��������ʵ�֡�������ݺ��·ݣ�������һ��������ж����졣
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
//�Ӽ�������a, b, c��ֵ����̼��㲢���һԪ���η���ax2 + bx + c = 0�ĸ���
//��a = 0ʱ�������Not quadratic equation������a �� 0ʱ��
//���ݡ� = b2 - 4 * a * c������������㲢������̵ĸ���
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
//����Ա�����ֳ���֡���7λ���٣��Ӽ�������������ɼ���ÿ��7���������ٷ��ƣ���
//ȥ��һ����߷ֺ�һ����ͷ֣����ÿ���ƽ���ɼ���
//��ע�������ж������룩
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
//KiKiѧϰ��ѭ����BoBo��ʦ��������һϵ�д�ӡͼ������ϰ���������Ǵ�ӡ�á�* ����ɵĴ��ո�ֱ��������ͼ����
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

//��ʹ���ۼƳ˷��Ļ����ϣ�ͨ����λ���㣨 << ��ʵ��2��n�η��ļ��㡣
int main1()
{
    int n = 0;
    scanf("%d", &n);
    printf("%d", 1 << n);
    return 0;
}
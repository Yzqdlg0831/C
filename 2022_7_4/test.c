#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

struct Test
{
    int Num;
    char* pcName;
    short sDate;
    char cha[2];
    short sBa[4];
}*p;
//����p ��ֵΪ0x100000�� ���±���ʽ��ֵ�ֱ�Ϊ���٣�
//��֪���ṹ��Test���͵ı�����С��20���ֽ�
void test2()
{
    printf("%p\n", p + 0x1);
    printf("%p\n", (unsigned long)p + 0x1);
    printf("%p\n", (unsigned int*)p + 0x1);
}


void test1()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    int* ptr = (int*)(&a + 1);
    printf("%d,%d", *(a + 1), *(ptr - 1));//2,5
}

void test3()
{
    int a[4] = { 1, 2, 3, 4 };
    int* ptr1 = (int*)(&a + 1);
    int* ptr2 = (int*)((int)a + 1);
    printf("%x,%x", ptr1[-1], *ptr2);
    return 0;
}

void test4()
{
    int a[3][2] = { (0, 1), (2, 3), (4, 5) };
    int* p;
    p = a[0];
    printf("%d", p[0]);
    return 0;
}

void test5()
{
    int a[5][5];
    int(*p)[4];
    p = a;
    printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);
    return 0;
}

void test6()
{
    int aa[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* ptr1 = (int*)(&aa + 1);
    int* ptr2 = (int*)(*(aa + 1));
    printf("%d,%d", *(ptr1 - 1), *(ptr2 - 1));//10,5
    return 0;
}

void test7()
{
    char* a[] = { "work","at","alibaba" };
    char** pa = a;
    pa++;
    printf("%s\n", *pa);
    return 0;
}

void test8()
{
    char* c[] = { "ENTER","NEW","POINT","FIRST" };
    char** cp[] = { c + 3,c + 2,c + 1,c };
    char*** cpp = cp;
    printf("%s\n", **++cpp);//POINT
    printf("%s\n", *-- * ++cpp + 3);//ER
    printf("%s\n", *cpp[-2] + 3);//ST
    printf("%s\n", cpp[-1][-1] + 1);//EW
    return 0;
}

int main()
{
    //test8();
    printf("%s\n", "PPAASS"+2);//POINT
    return 0;
}
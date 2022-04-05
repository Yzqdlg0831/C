#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>

int binarySearch(int arr[], int x,int len) {
    int right = len - 1;
    int left = 0;
    int mid = left + (right - left) / 2;
    while (right >= left)
    {
        if (x > arr[mid]) {
            left = mid + 1;
            mid = left + (right - left) / 2;
        }
        else if (x < arr[mid]) {
            right = mid - 1;
            mid = left + (right - left) / 2;
        }
        else {
            return mid;
        }
    }
    return -1;
}

int main() {
    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
    int x = 3;
    int len = sizeof(arr) / sizeof(arr[0]);
    int t = binarySearch(arr, x,len);
    if ((-1) == t) {
        printf("没找到！！！");
    }
    else {
        printf("找到了，下标是：%d", t);
    }
    return 0;
}

int main17() {

    for (int i = 1; i < 10; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d*%d=%2d ", i, j, i * j);
        }
        printf("\n");
    }
    return 0;
}

int Max(int x, int y) {
    return x > y ? x : y;
}

int main16() {

    int arr[10] = {0};
    for (int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }
    int max = arr[0];
    for (int i = 0; i < 10; i++) {
        max = Max(arr[i], max);
    }
    printf("%d", max);
    return 0;
}

int main15() {
    double sum = 0;
    double flag = 1.0;
    for (int i = 1; i <= 100; i++) {
        sum += flag / i;
        flag = -flag;
    }
    printf("%lf\n", sum);
    return 0;
}

int main14() {
    int count = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 10 == 9) {
            count++;
        }
        if (i / 10 == 9) {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}

int main13() {

    for (int i = 100; i <= 200; i++) {
        int j = 2;
        for (; j <= (int)sqrt(i); j++) {
            if (i % j == 0) {
                break;
            }
        }
        if (j > (int)sqrt(i)) {
            printf("%d ", i);
        }
    }

    return 0;
}


int main12() {

    for (int i = 1000; i <= 2000; i++)
    {
        if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
            printf("%d ", i);
        }
    }
    return 0;
}

int main11() {

    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    int tmp = a % b;
    while (tmp)
    {
        a = b;
        b = tmp;
        tmp = a % b;
    }
    printf("%d", b);
    return 0;
}

int main10() {

    for (int i = 1; i < 100; i++) {
        if (0 == i % 3) {
            printf("%d ", i);
        }
    }

    return 0;

}

int main9()
{
    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d %d %d", &a, &b, &c);
    if (a < b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    if (a < c)
    {
        int tmp = a;
        a = c;
        c = tmp;
    }
    if (b < c)
    {
        int tmp = b;
        b = c;
        c = tmp;
    }
    printf("%d %d %d\n", a, b, c);
    return 0;
}

int main8()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d %d", a / b, a % b);
    return 0;
}

int main7()
{
    int x;
    scanf("%d", &x);
    for (int i = 0; i < 4; i++) {
        printf("%d", x % 10);
        x = x / 10;
    }
    return 0;
}

int main6()
{
    printf("Name    Age    Gender\n");
    printf("---------------------\n");
    printf("Jack    18     man\n");
    return 0;
}

int main5() {
    int i, a, sum = 0;
    float avg;
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &a);
        sum = sum + a;
    }
    avg = sum / 5.0f;
    printf("%.1f", avg);
    return 0;
}


int main4() {

    int secomds;
    scanf("%d", &secomds);
    int hour, minute, second;
    second = secomds % 60;
    hour = secomds / 3600;
    minute = secomds / 60 - hour * 60;
    printf("%d %d %d", hour, minute, second);
    return 0;
}

int fun(int x) {
    if (x < 0) {
        return 1;
    }
    else if (x == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

int main3() {
    int x;
    scanf("%d", &x);
    printf("%d", fun(x));
    return 0;
}
int main2() {
    int a = 40, c = 212;
    printf("%d", (-8 + 22) * a - 10 + c / 2);
    return 0;
}

int Max1(int x, int y) {
	return x > y ? x : y;
}

int main1()
{
	printf("%d",Max(1,3));
	return 0;
}
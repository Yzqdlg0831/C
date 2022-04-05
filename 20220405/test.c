#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()
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
    avg = sum / 5.0;
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

int Max(int x, int y) {
	return x > y ? x : y;
}

int main1()
{
	printf("%d",Max(1,3));
	return 0;
}
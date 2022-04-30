#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>

int c[1010];
int main()
{
	int t;
	scanf("%d",&t);
	while (t--) 
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &c[i]);
		}
		int left = 1, right = n;
		int count1 = 0;
		int flag = 0, x = 0;
		int p = 0, q = 0, now;
		while (left <= right) {
			if (flag == 0) {
				now = 0;
				while (x >= now && left <= right) {
					now = now + c[left++];
				}
				p = p + now;
				flag = 1; count1++;
			}
			else {
				now = 0;
				while (x >= now && left <= right) {
					now = now + c[right--];
				}
				q = q + now;
				flag = 0; count1++;
			}
			x = now;
		}
		printf("%d %d %d", count1, p, q);
	}
	return 0;
}

int main2()
{
	int t = 0;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		int j = 1;
		int n = 0;
		int k = 0;
		scanf("%d", &n);
		scanf("%d", &k);
		if (k > n)
		{
			int m = 1;
			while ((n * m) <= (k + m))
			{
				m++;
			}
			int p = n * (m - 1) + k % (n - 1);
			if (k % (n - 1) != 0)
			{
				printf("%d\n", p);
			}
			else {
				printf("%d\n", p - 1);
			}
		}
		else if(k == n)
		{
			
			printf("%d\n", k + 1);
		}
		else
		{
			printf("%d\n", k);
		}
	}
	return 0;
}


int main1()
{
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int num = 0;
		scanf("%d", &num);
		int num1 = num;
		int cont1 = 0;
		int cont2 = 0;
		while (num1)
		{
			cont1++;
			if (num1 % 10 != 0)
			{
				cont2++;
			}
			num1 = num1 / 10;
		}
		printf("%d\n", cont2);
		for (int j = 0; j < cont1; j++)
		{
			if (num % 10 != 0)
			{
				int k = (num % 10) * pow(10.0, j);
				printf("%d ", k);
			}
			num = num / 10;
		}
		printf("\n");
	}
	return 0;
}
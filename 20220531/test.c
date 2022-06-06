#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

int main()
{
	int s = 1;
	//k = 1 2 3 4 5 6 7 8 9 10
	for (int k = 1; k <= 10; k++)
	{
		if (k == 6)
		{
			break;
		}
		s += 1;
		printf("k = %d, s =  %d\n", k, s);
	}
	printf("%d\n", s);
	return 0;
}
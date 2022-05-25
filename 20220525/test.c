#define _CRT_SECURE_NO_WARNINGS 1
//#include<stdio.h>
//int main()
//{
//	for (int i = 0; i < 8; ++i)
//	{
//		for (int j = 0; j < 8; ++j)
//		{
//			if (i % 2 == 0)
//			{
//				if (j % 2 == 0)
//				{
//					printf("%c", 219);
//				}
//				else
//				{
//					printf("  ");
//				}
//			}
//			else
//			{
//				if (j % 2 == 0)
//				{
//					printf("  ");
//				}
//				else
//				{
//					printf("%c", 219);
//				}
//			}
//		}
//		printf("\n");
//	}
//	return 0;
//}
//
//

#include<stdio.h>
#include<stdlib.h>
#define M 5
int main()
{
	int a[M] = { 1,2,3,4,5 };
	int i, j, t;
	i = 0; j = M - 1;
	while (i < j)
	{
		t = *(a + i);
		*(a + i) = *(a + j);
		*(a + j) = t;
		i++; j--;
	}
	for (i = 0; i < M; i++) {
		printf("%d\n", *(a + i));
	}
}
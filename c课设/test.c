#include <stdio.h>
#include <math.h>
#define MAX 100
struct zhuzi//定义柱子的结构体
{
	int num[MAX];
	int size;
};
struct zhuzi zhuziNum[MAX];//定义结构体数组

int p(int a) //判断一个数是否为平方数
{
	for (int i = 2;; i++)
	{
		if (pow((double)i, 2) == a)
			return 1;
		else if (pow((double)i, 2) > a)
			return 0;
	}
}
int f(struct zhuzi zhuzi1, struct zhuzi zhuzi2) //判断第一个塔的最下面一个数与第二个塔的最上面的一个数的和是否为平方数
{
	return p(zhuzi1.num[0] + zhuzi2.num[zhuzi2.size - 1]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &zhuziNum[i].num[0]);
		zhuziNum[i].size = 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (f(zhuziNum[i], zhuziNum[j])) //如果发现可以移过去就将第一个塔中的所有数全部移到第二个塔上
			{
				for (int k = 0; k < zhuziNum[i].size; k++)
				{
					zhuziNum[j].num[zhuziNum[j].size + k] = zhuziNum[i].num[k];
				}
				zhuziNum[j].size = zhuziNum[j].size + zhuziNum[i].size;
				zhuziNum[i].size = 0;
				break;
			}
		}
	}
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		if (zhuziNum[i].size != 0)
		{
			c++;
			for (int j = zhuziNum[i].size - 1; j > 0; j--)
			{
				printf("%d->",zhuziNum[i].num[j]);
			}
			printf("%d,", zhuziNum[i].num[0]);
		}
	}
	printf("c=%d\n", c);
	return 0;
}
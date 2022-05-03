#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>

//杨氏矩阵，查找一个数在不在该矩阵中
//从右上方开始寻找，如果该数比要查找的数大就往左查找，否则就往下查找
int findnum(int arr[][3], int x, int y, int num)
{
	int i = 0;
	int j = y - 1;
	while ((i != x) && (j != -1))
	{
		if (num > arr[i][j])
		{
			i++;
		}
		else if (num < arr[i][j])
		{
			j--;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
	int num = 0;
	scanf("%d", &num);
	if (findnum(arr, 3, 3, num))
	{
		printf("存在\n");
	}
	else
	{
		printf("不存在\n");
	}
	return 0;
}


void reverse(char* s, int start, int end)
{
	while (start < end)
	{
		char a = *(s+start);
		*(s + start) = *(s + end);
		*(s + end) = a;
		start++;
		end--;
	}
}

void leftRound(char* s, int k)
{
	k = k % strlen(s);
	int len = (int)strlen(s);
	reverse(s, 0, k - 1);
	reverse(s, k, len - 1);
	reverse(s, 0, len - 1);
}


int main1()
{
	char s[] = "ABCD";
	int k = 0;
	scanf("%d", &k);
	leftRound(s,k);
	printf("%s\n", s);
	return 0;
}


//#include<stdio.h>
//#include<math.h>
//int main()
//{
//	float a = -0.0f;
//	printf("%f", a + 0);
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<math.h>
//BC117 小乐乐走台阶

//递归
// int retMethodNumber(int n)
// {
//     if(n == 1)
//     {
//         return 1;
//     }
//     if(n == 2)
//     {
//         return 2;
//     }
//     return retMethodNumber(n - 1) + retMethodNumber(n - 2);
// }

//迭代
int retMethodNumber(int n)
{
    int a = 1;
    int b = 2;
    int c = 3;
    if (1 == n)
    {
        return a;
    }
    else if (2 == n)
    {
        return b;
    }
    else
    {
        for (int i = 3; i < n; i++)
        {
            a = b;
            b = c;
            c = a + b;
        }
    }
    return c;
}

int main()
{
    int n = 0;
    while (scanf("%d ", &n) != EOF)
    {
        //         printf("%d",retMethodNumber(n));
        printf("%d", retMethodNumber(n));
    }
    return 0;
}

//牛客BC116改数字
int main4()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int len = 0;
        int tmp = n;
        int ret = 0;
        while (tmp)
        {
            len++;
            tmp /= 10;
        }
        for (int i = 0; i < len; i++)
        {
            int a = (((n % 10) % 2) == 0 ? 0 : 1) * pow(10, i);
            ret += a;
            n /= 10;
        }
        printf("%d", ret);
    }
    return 0;
}

//猜名次
//5位运动员参加了10米台跳水比赛，有人让他们预测比赛结果：
//A选手说：B第二，我第三；
//B选手说：我第二，E第四；
//C选手说：我第一，D第二；
//D选手说：C最后，我第三；
//E选手说：我第四，A第一；
//比赛结束后，每位选手都说对了一半，请编程确定比赛的名次。

void swapArgs(int* a, int* b) //交换函数
{
    int tmp;

    tmp = *a;   
    *a = *b;
    *b = tmp;
}

void diveRank(int* p, int n)
{
    if (n >= 5) //此时的n也是用来控制循环层数的。
    {
        if ((p[1] == 2) + (p[0] == 3) == 1 && //B第二，我第三
            (p[1] == 2) + (p[4] == 4) == 1 && //我第二，E第四
            (p[2] == 1) + (p[3] == 2) == 1 && //我第一，D第二
            (p[2] == 5) + (p[3] == 3) == 1 && //C最后，我第三
            (p[4] == 4) + (p[0] == 1) == 1)   //我第四，A第一
            //由于此时是执行的全排列，所以查重也省了。
        {
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", p[i]);
            }
            putchar('\n');
        }
        return;
    }

    int i;
    for (i = n; i < 5; i++) //这个递归方式就完成了对1~5的全排列，方法是从后向前不停的执行交换.
    {
        swapArgs(p + i, p + n);
        diveRank(p, n + 1);
        swapArgs(p + i, p + n);
    }
}

int main3()
{
    int p[5] = { 1, 2, 3, 4, 5 }; //当然由于是全排列，所以初值必须给好。

    diveRank(p, 0);

    return 0;
}

//猜凶手
//日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个嫌疑犯的一个。
//以下为4个嫌疑犯的供词:
//A说：不是我。
//B说：是C。
//C说：是D。
//D说：C在胡说
//已知3个人说了真话，1个人说的是假话。
//现在请根据这些信息，写一个程序来确定到底谁是凶手。

int main2()
{
    int killer = 0;
    for (killer = 'a'; killer <= 'd'; killer++)
    {
        if ((('a' != killer) + ('c' == killer) + ('d' == killer) + ('d' != killer)) == 3)
        {
            printf("凶手是：%c\n", (char)killer);
        }
    }
    return 0;
}

//打印杨辉三角
void print_Yang_Hui_triangle(int n)
{
    assert(n > 0);
    int* arr = (int*)calloc(n,sizeof(int));
    if (arr != NULL)
    {
        *arr = 1;
    }
    for (int j = 0; j < n; j++)
    {
        printf(" ");
    }
    printf("1\n");//打印第一行
    if (n > 1)//n == 1时已经输出了第一行所以没必要进入直接跳出即可
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < (n - i); j++)
            {
                printf(" ");
            }
            for (int j = i; j > 0; j--)
            {
                if ((arr + j) && (arr + j - 1))//避免 取消引用 NULL 指针 
                {
                    arr[j] = arr[j] + arr[j - 1];
                }
            }

            for (int j = 0; j <= i; j++)
            {
                if (arr + j)
                {
                    printf("%d ", arr[j]);
                }
            }
            printf("\n");
        }
        free(arr);
    }
}

int main1()
{
    int n = 0;
    scanf("%d", &n);   
    print_Yang_Hui_triangle(n);
    return 0;
}
//力扣
int lengthOfLongestSubstring(char* s)
{
    //类似于hash的思想
    //滑动窗口维护
    int left = 0;
    int right = 0;
    int max = 0;
    int i, j;
    int len = (int)strlen(s);
    int haveSameChar = 0;
    for (i = 0; i < len; i++)
    {
        if (left <= right)
        {
            //检测是否出现重复
             //循环遍历整个数组 left -> right
            haveSameChar = 0;
            for (j = left; j < right; j++)
            {
                if (s[j] == s[right])
                {
                    haveSameChar = 1;
                    break;
                }
            }
            if (haveSameChar)
            {
                //指向下一个
                left = j + 1;
            }
        }
        //统计最大的间距
        max = max < (right - left + 1) ? (right - left + 1) : max;
        right++;
    }
    return max;
}
int main0()
{
    char s[] = "abcabcbb";
    printf("%d", lengthOfLongestSubstring(s));
	return 0;	
}
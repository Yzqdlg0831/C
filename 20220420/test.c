#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<math.h>
//BC117 С������̨��

//�ݹ�
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

//����
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

//ţ��BC116������
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

//������
//5λ�˶�Ա�μ���10��̨��ˮ����������������Ԥ����������
//Aѡ��˵��B�ڶ����ҵ�����
//Bѡ��˵���ҵڶ���E���ģ�
//Cѡ��˵���ҵ�һ��D�ڶ���
//Dѡ��˵��C����ҵ�����
//Eѡ��˵���ҵ��ģ�A��һ��
//����������ÿλѡ�ֶ�˵����һ�룬����ȷ�����������Ρ�

void swapArgs(int* a, int* b) //��������
{
    int tmp;

    tmp = *a;   
    *a = *b;
    *b = tmp;
}

void diveRank(int* p, int n)
{
    if (n >= 5) //��ʱ��nҲ����������ѭ�������ġ�
    {
        if ((p[1] == 2) + (p[0] == 3) == 1 && //B�ڶ����ҵ���
            (p[1] == 2) + (p[4] == 4) == 1 && //�ҵڶ���E����
            (p[2] == 1) + (p[3] == 2) == 1 && //�ҵ�һ��D�ڶ�
            (p[2] == 5) + (p[3] == 3) == 1 && //C����ҵ���
            (p[4] == 4) + (p[0] == 1) == 1)   //�ҵ��ģ�A��һ
            //���ڴ�ʱ��ִ�е�ȫ���У����Բ���Ҳʡ�ˡ�
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
    for (i = n; i < 5; i++) //����ݹ鷽ʽ������˶�1~5��ȫ���У������ǴӺ���ǰ��ͣ��ִ�н���.
    {
        swapArgs(p + i, p + n);
        diveRank(p, n + 1);
        swapArgs(p + i, p + n);
    }
}

int main3()
{
    int p[5] = { 1, 2, 3, 4, 5 }; //��Ȼ������ȫ���У����Գ�ֵ������á�

    diveRank(p, 0);

    return 0;
}

//������
//�ձ�ĳ�ط�����һ��ıɱ��������ͨ���Ų�ȷ��ɱ�����ֱ�Ϊ4�����ɷ���һ����
//����Ϊ4�����ɷ��Ĺ���:
//A˵�������ҡ�
//B˵����C��
//C˵����D��
//D˵��C�ں�˵
//��֪3����˵���滰��1����˵���Ǽٻ���
//�����������Щ��Ϣ��дһ��������ȷ������˭�����֡�

int main2()
{
    int killer = 0;
    for (killer = 'a'; killer <= 'd'; killer++)
    {
        if ((('a' != killer) + ('c' == killer) + ('d' == killer) + ('d' != killer)) == 3)
        {
            printf("�����ǣ�%c\n", (char)killer);
        }
    }
    return 0;
}

//��ӡ�������
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
    printf("1\n");//��ӡ��һ��
    if (n > 1)//n == 1ʱ�Ѿ�����˵�һ������û��Ҫ����ֱ����������
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < (n - i); j++)
            {
                printf(" ");
            }
            for (int j = i; j > 0; j--)
            {
                if ((arr + j) && (arr + j - 1))//���� ȡ������ NULL ָ�� 
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
//����
int lengthOfLongestSubstring(char* s)
{
    //������hash��˼��
    //��������ά��
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
            //����Ƿ�����ظ�
             //ѭ�������������� left -> right
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
                //ָ����һ��
                left = j + 1;
            }
        }
        //ͳ�����ļ��
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
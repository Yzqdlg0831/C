#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>

int main()
{

    return 0;
}   

void swap_arr(int arr[], int sz)
{
    int left = 0;
    int right = sz - 1;
    while (right >= left)
    {
        if (arr[right] % 2 == 1)
        {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
        }
        else
        {
            right--;
        }
    }
}

int main9()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("����ǰ��\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    swap_arr(arr, sizeof(arr) / sizeof(arr[0]));
    printf("\n������\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}

char* my_strcpy(char* destination, const char* copy)
{
    assert(destination != NULL && copy != NULL);
    int* cpy = destination;
    while (*destination++ = *copy++);
    return cpy;
}

int my_strlen(const char* s)
{
    assert(s != NULL);

    const char* tmp = s;
    while (*s++ != '\0');
    return s - tmp - 1;
}

int main2()
{
    char arr[] = "abcdef";
    char a[] = "aaa";
    printf("%s", my_strcpy(arr, a));
    return 0;
}

//��ѭ����ӡhello bit 
//ԭ�� forѭ���У�i�������Ǵ�0��һֱ���ӵ�12��������ֻ��10���ռ䣬��˻�Խ�硣
//ÿ�η���arr����i��λ��ʱ�����Ὣ��λ����������Ϊ0�������ʵ�arr[12]ʱ��
//Ҳ�Ὣ��λ����������Ϊ0����λ��ǡ��Ϊi��λ�ã���a[12]ǡ�ɽ�i����Ϊ0����������ѭ����
int main1()
{
    int i = 0;
    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
    for (i = 0; i <= 12; i++)
    {
        //arr[i] = 0;
        printf("hello bit\n");
    }
    return 0;
}

//�����ַ���s
void reverseString(char* s, int sSize) {
    char tmp = 0;
    int left = 0;
    int right = sSize - 1;
    while (right >= left)
    {
        tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        right--;
        left++;
    }
}
//�����ַ�����ÿ�����ʣ��Կո�����
char* reverseWords(char* s) {
    int i = 0;
    int count = i;
    while (s[i] != '\0')
    {
        if (s[i] == ' ')
        {
            reverseString(&s[count], i - count);
            count = i + 1;//��¼���οո���һ����������ĸ��λ��
        }
        i++;
    }
    reverseString(&s[count], i - count - 1);//�������һ������
    return s;
}

int main0()
{
    char arr[] = "Let's take LeetCode contest";
    reverseWords(arr);
    printf("%s\n", arr);
	return 0;
}


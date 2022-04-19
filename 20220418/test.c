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
    printf("调整前：\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    swap_arr(arr, sizeof(arr) / sizeof(arr[0]));
    printf("\n调整后：\n");
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

//死循环打印hello bit 
//原因： for循环中，i的内容是从0，一直增加到12，而数组只有10个空间，因此会越界。
//每次访问arr数组i号位置时，都会将该位置内容设置为0，当访问到arr[12]时，
//也会将该位置内容设置为0，而位置恰好为i的位置，即a[12]恰巧将i设置为0，因此造成死循环。
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

//逆序字符串s
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
//逆序字符串中每个单词，以空格区分
char* reverseWords(char* s) {
    int i = 0;
    int count = i;
    while (s[i] != '\0')
    {
        if (s[i] == ' ')
        {
            reverseString(&s[count], i - count);
            count = i + 1;//记录本次空格下一个单词首字母的位置
        }
        i++;
    }
    reverseString(&s[count], i - count - 1);//逆置最后一个单词
    return s;
}

int main0()
{
    char arr[] = "Let's take LeetCode contest";
    reverseWords(arr);
    printf("%s\n", arr);
	return 0;
}


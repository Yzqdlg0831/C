#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Add(int x, int y)
{
	return x + y;
}

int main1()
{
	int (*pa)(int, int) = Add;//pa--->是指向Add函数的指针，类型：int (*)(int, int)
	int (*pfA[4])(int, int) = { pa };//pfA--->是存放函数指针的数组，每个元素类型为int (*)(int, int)
	int (*(*ppfA)[4])(int ,int) = &pfA;//ppfA-->是一个指针，指向了一个存放函数指针的数组，类型为：int (*(*)[4])(int ,int)
	printf("%d\n", Add(1, 2));
	printf("%d\n", (*pa)(1, 2));
	printf("%d\n", (*pfA[0])(1, 2));
	printf("%d\n", (*(*ppfA)[0])(1, 2));
	return 0;
}

//int cmp_int(const void* e1, const void* e2)
//{
//	return *(int*)e1 - *(int*)e2;
//}

void print_arr(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void my_swap(char* buf1, char* buf2, int width)
{
	int i = 0;
	for (i = 0; i < width; i++)
	{
		char tmp = *buf1;
		*buf1 = *buf2;
		*buf2 = tmp;
		buf1++;
		buf2++;
	}
}
//用冒泡排序实现qsort函数
//void qsort( void *base, size_t num, size_t width, int (__cdecl *compare )(const void *elem1, const void *elem2 ) );
void my_qsort(void* base, size_t num, size_t width, int(*cmp)(const void* e1, const void* e2))
{
	int i = 0;
	//确定趟数
	for (i = 0; i < num; i++)
	{
		int j = 0;
		//每一趟进行排序
		for (j = 0; j < num - 1 - i; j++)
		{
			if ((*cmp)(((char*)base+j*width),((char*)base+(j+1)*width)) > 0)
			{
				//如果只交换一次，则只会交换第一个字节，如:int类型的交换只会交换第一个字节后面三个字节都不会交换
				//这里结果正确的原因是因为0-9在内存中都只存在第一个字节上，后面三个字节的内容都是0，所以打印结果与预期一样，但是这样是错的
				//char tmp = *((char*)base + j * width);
				//*((char*)base + j * width) = *((char*)base + (j + 1) * width);
				//*((char*)base + (j + 1) * width) = tmp;
				my_swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
			}
		}
	}
}

//测试qsort函数
void test1()
{
	int arr[] = { 2,3,1,4,6,7,9,8,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	print_arr(arr, sz);
	//my_qsort(arr, sz, sizeof(arr[0]), cmp_int);
	print_arr(arr, sz);
}

struct Student
{
	char name[20];
	int age;
	float score;
};

void print_arr_int(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void print_arr_char(char arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%c ", arr[i]);
	}
	printf("\n");
}
void print_std(struct Student arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%s %d %.1f ", arr[i].name, arr[i].age, arr[i].score);
	}
	printf("\n");
}
int cmp_int(const void* e1, const void* e2)
{
	return *(int*)e1 - *(int*)e2;
}

int cmp_char(const void* e1, const void* e2)
{
	return strcmp((char*)e1, (char*)e2);
}

int cmp_std_by_age(const void* e1, const void* e2)
{
	return ((struct Student*)e1)->age - ((struct Student*)e2)->age;
}

void test2()
{
	int arr_int[] = { 2,5,7,8,9,3,1,4,6,0 };
	char arr_char[] = {'d','a','q','w'};
	struct Student std[] = { {"张三",18,85.5f},{"李四",16,78.5f},{"王五",19,90.0f},{"赵六",11,50.0f} };
	int sz = sizeof(arr_int) / sizeof(arr_int[0]);
	qsort(arr_int, sz, sizeof(arr_int[0]), cmp_int);
	print_arr_int(arr_int, sz);

	sz = sizeof(arr_char) / sizeof(arr_char[0]);
	qsort(arr_char, sz, sizeof(arr_char[0]), cmp_char);
	print_arr_char(arr_char, sz);

	sz = sizeof(std) / sizeof(std[0]);
	qsort(std, sz, sizeof(std[0]), cmp_std_by_age);
	print_std(std, sz);
}

void test3()
{
	//int a[] = { 1,2,3,4 };
	//printf("%u\n", sizeof(a));              //16
	//printf("%d\n", sizeof(a + 0));			//4\8
	//printf("%d\n", sizeof(*a));				//4
	//printf("%d\n", sizeof(a + 1));			//4\8
	//printf("%d\n", sizeof(a[1]));			//4
	//printf("%d\n", sizeof(&a));			    //4\8      
	//printf("%d\n", sizeof(*&a));			//16		
	//printf("%d\n", sizeof(&a + 1));			//4\8		
	//printf("%d\n", sizeof(&a[0]));			//4\8		
	//printf("%d\n", sizeof(&a[0] + 1));		//4\8		
	////字符数组
	//char arr[] = { 'a','b','c','d','e','f' };
	//printf("%d\n", sizeof(arr));			//6
	//printf("%d\n", sizeof(arr + 0));		//4\8		
	//printf("%d\n", sizeof(*arr));			//1
	//printf("%d\n", sizeof(arr[1]));			//1
	//printf("%d\n", sizeof(&arr));			//4\8		
	//printf("%d\n", sizeof(&arr + 1));		//4\8
	//printf("%d\n", sizeof(&arr[0] + 1));	//4/8
	//
	//printf("%d\n", strlen(arr));            //随机值
	//printf("%d\n", strlen(arr + 0));		//随机值
	//printf("%d\n", strlen(*arr));			//错误
	//printf("%d\n", strlen(arr[1]));			//错误
	//printf("%d\n", strlen(&arr));			//随机值
	//printf("%d\n", strlen(&arr + 1));		//随机值
	//printf("%d\n", strlen(&arr[0] + 1));	//随机值

	//char arr[] = "abcdef";
	//printf("%d\n", sizeof(arr));			//7
	//printf("%d\n", sizeof(arr + 0));		//***4\8
	//printf("%d\n", sizeof(*arr));			//1
	//printf("%d\n", sizeof(arr[1]));			//1
	//printf("%d\n", sizeof(&arr));			//4\8
	//printf("%d\n", sizeof(&arr + 1));		//4\8
	//printf("%d\n", sizeof(&arr[0] + 1));	//4\8

	//printf("%d\n", strlen(arr));			//6
	//printf("%d\n", strlen(arr + 0));		//6
	////printf("%d\n", strlen(*arr));			//错误
	////printf("%d\n", strlen(arr[1]));			//错误
	//printf("%d\n", strlen(&arr));			//6 
	//printf("%d\n", strlen(&arr + 1));		//随机值
	//printf("%d\n", strlen(&arr[0] + 1));	//5

	//char* p = "abcdef";
	//printf("%d\n", sizeof(p));				//        4\8
	//printf("%d\n", sizeof(p + 1));			//4\8      
	//printf("%d\n", sizeof(*p));				//1        1
	//printf("%d\n", sizeof(p[0]));			//1      1 
	//printf("%d\n", sizeof(&p));				//4/8       
	//printf("%d\n", sizeof(&p + 1));			//4\8       
	//printf("%d\n", sizeof(&p[0] + 1));		//4\8       

	//printf("%d\n", strlen(p));				//6			
	//printf("%d\n", strlen(p + 1));			//5
	////printf("%d\n", strlen(*p));			//错误
	////printf("%d\n", strlen(p[0]));			//错误
	//printf("%d\n", strlen(&p));				//随机值   3
	//printf("%d\n", strlen(&p + 1));			//随机值   11
	//printf("%d\n", strlen(&p[0] + 1));		//5

	//二维数组
	int a[3][4] = { 0 };
	printf("%d\n", sizeof(a));				//12*4=48
	printf("%d\n", sizeof(a[0][0]));		//4
	printf("%d\n", sizeof(a[0]));			//4\8	 16
	printf("%d\n", sizeof(a[0] + 1));		//4\8
	printf("%d\n", sizeof(*(a[0] + 1)));	//4
	printf("%d\n", sizeof(a + 1));			//4\8
	printf("%d\n", sizeof(*(a + 1)));		//16
	printf("%d\n", sizeof(&a[0] + 1));		//4\8
	printf("%d\n", sizeof(*(&a[0] + 1)));	//16		16
	printf("%d\n", sizeof(*a));				//16	
	printf("%d\n", sizeof(a[3]));			//4\8	16
	//a[0]如果没有放在sizeof里面的话a[0]--->a[0][0]
		/*总结：
		数组名的意义：
		1. sizeof(数组名)，这里的数组名表示整个数组，计算的是整个数组的大小。
		2. &数组名，这里的数组名表示整个数组，取出的是整个数组的地址。
		3. 除此之外所有的数组名都表示首元素的地址。*/
}

int main()
{
	test3();
	return 0;
}
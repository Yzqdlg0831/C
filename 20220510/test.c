#define _CRT_SECURE_NO_WARNINGS 1
//
//#include<stdio.h>
//#include<stdlib.h>
//
//struct freelink {
//
//    int len;
//
//    int address;
//
//    struct freelink* next;
//
//};
//
//struct busylink {
//
//    char name;
//
//    int len;  //len为分区长度
//
//    int address;//    address为分区起始地址
//    struct busylink* next;
//
//};
//
//struct freelink* free_head = NULL;    //自由链队列（带头结点）队首指针         
//
//struct busylink* busy_head = NULL;   //占用区队列队（带头结点）首指针                 
//
//struct busylink* busy_tail = NULL;   //占用区队列队尾指针
//
//void  start(void)  /* 设置系统初始状态*/
//
//{
//
//    struct freelink* p;
//
//    struct busylink* q;
//
//    free_head = (struct freelink*)malloc(sizeof(struct freelink));
//
//    if (free_head != NULL)
//    {
//        free_head->next = NULL;  // 创建自由链头结点
//    }
//
//    busy_head = busy_tail = (struct busylink*)malloc(sizeof(struct busylink));
//
//    if (busy_head != NULL)
//    {
//        busy_head->next = NULL;  // 创建占用链头结点
//    }
//    p = (struct freelink*)malloc(sizeof(struct freelink));
//    if (p != NULL)
//    {
//        p->address = 64;
//
//        p->len = 640 - 64;//OS占用了64K
//
//        p->next = NULL;
//    }
//    if (free_head != NULL)
//    {
//        free_head->next = p;
//    }
//    q = (struct busylink*)malloc(sizeof(struct busylink));
//    
//    if (q != NULL)
//    {
//        q->name = 'S';  /*  S表示操作系统占用  */
//    }
//
//    if (q != NULL)
//    {
//        q->len = 64;  q->address = 0;  q->next = NULL;
//    }
//    
//    if (busy_head != NULL)
//    {
//        busy_head->next = q;  busy_tail = q;
//    }
//}
//
//void  requireMemo(char  name, int  require) /*模拟内存分配*/
//
//{
//
//    struct freelink* w, * u, * v;
//
//    struct busylink* p;
//    if (free_head->next->len >= require)
//
//    {
//
//        p = (struct busylink*)malloc(sizeof(struct busylink));
//
//        if (p != NULL)
//        {
//            p->name = name;
//
//            p->address = free_head->next->address;
//
//            p->len = require;
//
//            p->next = NULL;
//        }
//        if (busy_tail != NULL)
//        {
//            busy_tail->next = p;
//
//            busy_tail = p;
//        }
//    }
//
//    else
//    {
//        printf("Can't allocate");
//    }
//
//
//    w = free_head->next;
//    if (free_head->next->len >= require)
//
//    {
//
//        p = (struct busylink*)malloc(sizeof(struct busylink));
//
//        if (p != NULL)
//        {
//            p->name = name;
//
//            p->address = free_head->next->address;
//
//            p->len = require;
//
//            p->next = NULL;
//        }
//        if (busy_tail != NULL)
//        {
//            busy_tail->next = p;
//
//            busy_tail = p;
//        }
//    }
//
//    else
//
//        printf("Can't allocate");
//    w = free_head->next;
//
//    free_head->next = w->next;
//
//    if (w->len == require)
//
//    {
//
//        free(w);
//
//    }
//
//    else
//
//    {
//
//        w->address = w->address + require;
//
//        w->len = w->len - require;
//
//    }
//
//    u = free_head;
//
//    v = free_head->next;
//    while ((v != NULL) && (v->len > w->len))
//
//    {
//        u = v;
//
//        v = v->next;
//
//    }
//
//    u->next = w;
//
//    w->next = v;
//
//}
//
//void freeMemo(char name) /* 模拟内存回收*/
//
//{
//
//    int len;
//
//    int address;
//
//    struct busylink* q, * p;
//    struct freelink* w, * u, * v;
//
//    q = busy_head;
//
//    p = busy_head->next;
//
//    while ((p != NULL) && (p->name != name))
//
//    {
//        q = p;
//
//        p = p->next;
//
//    }
//
//    if (p == NULL)
//
//    {
//
//        printf("%c is not exist", name);
//
//    }
//
//    else
//    {
//
//        if (p == busy_tail)
//
//        {
//            busy_tail = q;
//
//        }
//
//        else
//
//        {
//            q->next = p->next;
//
//            len = p->len;
//
//            address = p->address;
//
//            free(p);
//
//            w = (struct freelink*)malloc(sizeof(struct freelink));
//            if (w != NULL)
//            {
//                w->len = len;
//
//                w->address = address;
//            }
//            
//            u = free_head;
//
//            v = free_head->next;
//
//            while ((v != NULL) && (v->len > len))
//
//            {
//                u = v;
//
//                v = v->next;
//
//            }
//
//            u->next = w;
//
//            if (w != NULL)
//            {
//                w->next = v;
//            }
//        }
//
//    }
//
//}
//void  past(int  time) /* 模拟系统过了time 时间*/
//
//{
//
//    printf("过了时间%d后:\n", time);
//
//}
//
//void  printlink()  /* 输出内存空闲情况（自由链的结点） */
//
//{
//
//    struct freelink* p;
//
//    printf("内存的空闲情况为:\n");
//
//    p = (struct freelink*)malloc(sizeof(struct freelink));
//
//    p = free_head->next;
//
//    while (p != NULL)
//
//    {
//        printf("内存的起始地址和内存的大小%5d\t%5d:\n", p->address, p->len);
//        p = p->next;
//
//    }
//
//}
//
//
//
//int main()
//
//{
//
//    int t1 = 1, t2 = 2, t3 = 3, t4 = 4;
//
//    start();
//
//    past(t1);
//
//    requireMemo('A', 8);
//
//    requireMemo('B', 16);
//
//    requireMemo('C', 64);
//    requireMemo('D', 124);
//
//    printlink();
//
//    past(t2);
//
//    freeMemo('C');
//
//    printlink();
//
//    past(t3);
//
//    requireMemo('E', 50);
//
//    printlink();
//
//    past(t4);
//
//    freeMemo('D');
//
//    printlink();
//
//    return 0;
//
//}

#include<conio.h> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Myprintf printf("|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n") /*表格控制*/ 
#define bsize 4     //物理块大小
#define psize 16     //进程大小
typedef struct page
{
    int num;  /*记录页面号*/
    int time;  /*记录调入内存时间*/
}Page;                   /* 页面逻辑结构，结构为方便算法实现设计*/
Page b[bsize];            /*内存单元数*/
int c[bsize][psize];   /*暂保存内存当前的状态：缓冲区*/
int queue[100];      /*记录调入队列*/
int K;             /*调入队列计数变量*/
int phb[bsize] = { 0 };   //物理块标号
int pro[psize] = { 0 };   //进程序列号
int flag[bsize] = { 0 };  //进程等待次数(存放最久未被使用的进程标志)
int i = 0, j = 0, k = 0;   //i表示进程序列号,j表示物理块号
int m = -1, n = -1;       //物理块空闲和进程是否相同判断标志
int max = -1, maxflag = 0; //标记替换物理块进程下标
int count = 0;            //统计页面缺页次数


//随机产生序列号函数

int* build()
{
    printf("随机产生一个进程序列号为：\n");
    int i = 0;
    for (i = 0; i < psize; i++)
    {
        pro[i] = 10 * rand() / (RAND_MAX + 1) + 1;
        printf("%d  ", pro[i]);
    }
    printf("\n");
    return(pro);
}

//查找空闲物理块

int searchpb()
{
    for (j = 0; j < bsize; j++)
    {
        if (phb[j] == 0)
        {
            m = j;
            return m;
            break;
        }
    }
    return -1;
}

//查找相同进程

int searchpro()
{
    for (j = 0; j < bsize; j++)
    {
        if (phb[j] == pro[i])
        {
            n = j;
            return j;
        }
    }
    return -1;
}
//初始化内存

void empty()
{
    for (i = 0; i < bsize; i++)
        phb[i] = 0;
    count = 0;                //计数器置零
}

//先进先出页面置换算法

void FIFO()
{
    for (i = 0; i < psize; i++)
    {
        m = searchpb();
        n = searchpro();
        //找flag值最大的
        for (j = 0; j < bsize; j++)
        {
            if (flag[j] > maxflag)
            {
                maxflag = flag[j];
                max = j;
            }
        }
        if (n == -1)               //不存在相同进程
        {
            if (m != -1)            //存在空闲物理块
            {
                phb[m] = pro[i];   //进程号填入该空闲物理块
                count++;
                flag[m] = 0;
                for (j = 0; j <= m; j++)
                {
                    flag[j]++;
                }
                m = -1;
            }
            else                //不存在空闲物理块
            {
                phb[max] = pro[i];
                flag[max] = 0;
                for (j = 0; j < bsize; j++)
                {
                    flag[j]++;
                }
                max = -1;
                maxflag = 0;
                count++;
            }
        }
        else                    //存在相同的进程
        {
            phb[n] = pro[i];
            for (j = 0; j < bsize; j++)
            {
                flag[j]++;
            }
            n = -1;
        }
        for (j = 0; j < bsize; j++)
        {
            printf("%d  ", phb[j]);
        }
        printf("\n");
    }
    printf("缺页次数为：%d\n", count);
    printf("\n");

}
/*初始化内存单元、缓冲区*/

void Init(Page* b, int c[bsize][psize])
{
    int i, j;
    for (i = 0; i < psize; i++)
    {
        b[i].num = -1;
        b[i].time = psize - i - 1;
    }
    for (i = 0; i < bsize; i++)
        for (j = 0; j < psize; j++)
            c[i][j] = -1;
}
/*取得在内存中停留最久的页面,默认状态下为最早调入的页面*/

int GetMax(Page* b)
{
    int i;
    int max = -1;
    int tag = 0;
    for (i = 0; i < bsize; i++)
    {
        if (b[i].time > max)
        {
            max = b[i].time;
            tag = i;
        }
    }
    return tag;
}
/*判断页面是否已在内存中*/

int   Equation(int fold, Page* b)
{
    int i;
    for (i = 0; i < bsize; i++)
    {
        if (fold == b[i].num)
            return i;
    }
    return -1;
}
/*LRU核心部分*/

void Lruu(int fold, Page* b)
{
    int i;
    int val;
    val = Equation(fold, b);
    if (val >= 0)
    {
        b[val].time = 0;
        for (i = 0; i < bsize; i++)
            if (i != val)
                b[i].time++;
    }
    else
    {
        queue[++K] = fold;/*记录调入页面*/
        val = GetMax(b);
        b[val].num = fold;
        b[val].time = 0;
        for (i = 0; i < bsize; i++)
            if (i != val)
                b[i].time++;
    }
}

void LRU()
{
    int i, j;
    K = -1;
    Init(b, c);
    for (i = 0; i < psize; i++)
    {
        Lruu(pro[i], b);
        c[0][i] = pro[i];

        /*记录当前的内存单元中的页面*/

        for (j = 0; j < bsize; j++)
            c[j][i] = b[j].num;
    }

    /*结果输出*/

    printf("内存状态为：\n");
    Myprintf;
    for (j = 0; j < psize; j++)
        printf("|%2d ", pro[j]);
    printf("|\n");
    Myprintf;
    for (i = 0; i < bsize; i++)
    {
        for (j = 0; j < psize; j++)
        {
            if (c[i][j] == -1)
                printf("|%2c ", 32);
            else
                printf("|%2d ", c[i][j]);
        }
        printf("|\n");
    }
    Myprintf;
    printf("\n调入队列为:");
    for (i = 0; i < K + 1; i++)
        printf("%3d", queue[i]);
    printf("\n缺页次数为：%6d\n缺页率：%16.6f", K + 1, (float)(K + 1) / psize);

}

int main()
{
    int sel;
    do {
        printf("\t--------------------------------------\t\t\t\n");
        printf("\t         欢迎进入操作系统界面   \t\t\t\n");
        printf("\t--------------------------------------\t\t\t\n");
        printf("\t             虚拟内存                 \t\t\t\n");
        printf("\t --------------------------------    \t\t\t\n");
        printf("\t        1、产生随机序列            \t\t\t\n");
        printf("\t --------------------------------\t\t\t\n");
        printf("\t        2、最久未使用(LRU)         \t\t\t\n");
        printf("\t --------------------------------\t\t\t\n");
        printf("\t        3、先进先出(FIFO)          \t\t\t\n");
        printf("\t--------------------------------\t\t\t\n");
        printf("\t        4、两种算法的比较()        \t\t\t\n");
        printf("\t--------------------------------\t\t\t\n");
        printf("\t        0、退出(Exit)              \t\t\t\n");

        printf("<请选择所要执行的操作:(0)(1)(2)(3)(4)(5)>");
        scanf("%d", &sel);
        switch (sel)
        {
        case 0:printf("再见!\n"); break;
        case 1:build(); break;
        case 2:printf("最久未使用算法\n"); LRU(); empty(); printf("\n"); break;
        case 3:printf("先进先出算\n"); FIFO(); empty(); printf("\n"); break;
        case 4:printf("先进先出算法\n"); FIFO(); empty();
            printf("最久未使用算法\n"); LRU(); empty(); break;
        default: printf("请输入正确的选项号"); printf("\n\n"); break;
        }
    } while (sel != 0);
    return 0;
}
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
//    int len;  //lenΪ��������
//
//    int address;//    addressΪ������ʼ��ַ
//    struct busylink* next;
//
//};
//
//struct freelink* free_head = NULL;    //���������У���ͷ��㣩����ָ��         
//
//struct busylink* busy_head = NULL;   //ռ�������жӣ���ͷ��㣩��ָ��                 
//
//struct busylink* busy_tail = NULL;   //ռ�������ж�βָ��
//
//void  start(void)  /* ����ϵͳ��ʼ״̬*/
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
//        free_head->next = NULL;  // ����������ͷ���
//    }
//
//    busy_head = busy_tail = (struct busylink*)malloc(sizeof(struct busylink));
//
//    if (busy_head != NULL)
//    {
//        busy_head->next = NULL;  // ����ռ����ͷ���
//    }
//    p = (struct freelink*)malloc(sizeof(struct freelink));
//    if (p != NULL)
//    {
//        p->address = 64;
//
//        p->len = 640 - 64;//OSռ����64K
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
//        q->name = 'S';  /*  S��ʾ����ϵͳռ��  */
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
//void  requireMemo(char  name, int  require) /*ģ���ڴ����*/
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
//void freeMemo(char name) /* ģ���ڴ����*/
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
//void  past(int  time) /* ģ��ϵͳ����time ʱ��*/
//
//{
//
//    printf("����ʱ��%d��:\n", time);
//
//}
//
//void  printlink()  /* ����ڴ����������������Ľ�㣩 */
//
//{
//
//    struct freelink* p;
//
//    printf("�ڴ�Ŀ������Ϊ:\n");
//
//    p = (struct freelink*)malloc(sizeof(struct freelink));
//
//    p = free_head->next;
//
//    while (p != NULL)
//
//    {
//        printf("�ڴ����ʼ��ַ���ڴ�Ĵ�С%5d\t%5d:\n", p->address, p->len);
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
#define Myprintf printf("|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n") /*������*/ 
#define bsize 4     //������С
#define psize 16     //���̴�С
typedef struct page
{
    int num;  /*��¼ҳ���*/
    int time;  /*��¼�����ڴ�ʱ��*/
}Page;                   /* ҳ���߼��ṹ���ṹΪ�����㷨ʵ�����*/
Page b[bsize];            /*�ڴ浥Ԫ��*/
int c[bsize][psize];   /*�ݱ����ڴ浱ǰ��״̬��������*/
int queue[100];      /*��¼�������*/
int K;             /*������м�������*/
int phb[bsize] = { 0 };   //�������
int pro[psize] = { 0 };   //�������к�
int flag[bsize] = { 0 };  //���̵ȴ�����(������δ��ʹ�õĽ��̱�־)
int i = 0, j = 0, k = 0;   //i��ʾ�������к�,j��ʾ������
int m = -1, n = -1;       //�������кͽ����Ƿ���ͬ�жϱ�־
int max = -1, maxflag = 0; //����滻���������±�
int count = 0;            //ͳ��ҳ��ȱҳ����


//����������кź���

int* build()
{
    printf("�������һ���������к�Ϊ��\n");
    int i = 0;
    for (i = 0; i < psize; i++)
    {
        pro[i] = 10 * rand() / (RAND_MAX + 1) + 1;
        printf("%d  ", pro[i]);
    }
    printf("\n");
    return(pro);
}

//���ҿ��������

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

//������ͬ����

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
//��ʼ���ڴ�

void empty()
{
    for (i = 0; i < bsize; i++)
        phb[i] = 0;
    count = 0;                //����������
}

//�Ƚ��ȳ�ҳ���û��㷨

void FIFO()
{
    for (i = 0; i < psize; i++)
    {
        m = searchpb();
        n = searchpro();
        //��flagֵ����
        for (j = 0; j < bsize; j++)
        {
            if (flag[j] > maxflag)
            {
                maxflag = flag[j];
                max = j;
            }
        }
        if (n == -1)               //��������ͬ����
        {
            if (m != -1)            //���ڿ��������
            {
                phb[m] = pro[i];   //���̺�����ÿ��������
                count++;
                flag[m] = 0;
                for (j = 0; j <= m; j++)
                {
                    flag[j]++;
                }
                m = -1;
            }
            else                //�����ڿ��������
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
        else                    //������ͬ�Ľ���
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
    printf("ȱҳ����Ϊ��%d\n", count);
    printf("\n");

}
/*��ʼ���ڴ浥Ԫ��������*/

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
/*ȡ�����ڴ���ͣ����õ�ҳ��,Ĭ��״̬��Ϊ��������ҳ��*/

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
/*�ж�ҳ���Ƿ������ڴ���*/

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
/*LRU���Ĳ���*/

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
        queue[++K] = fold;/*��¼����ҳ��*/
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

        /*��¼��ǰ���ڴ浥Ԫ�е�ҳ��*/

        for (j = 0; j < bsize; j++)
            c[j][i] = b[j].num;
    }

    /*������*/

    printf("�ڴ�״̬Ϊ��\n");
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
    printf("\n�������Ϊ:");
    for (i = 0; i < K + 1; i++)
        printf("%3d", queue[i]);
    printf("\nȱҳ����Ϊ��%6d\nȱҳ�ʣ�%16.6f", K + 1, (float)(K + 1) / psize);

}

int main()
{
    int sel;
    do {
        printf("\t--------------------------------------\t\t\t\n");
        printf("\t         ��ӭ�������ϵͳ����   \t\t\t\n");
        printf("\t--------------------------------------\t\t\t\n");
        printf("\t             �����ڴ�                 \t\t\t\n");
        printf("\t --------------------------------    \t\t\t\n");
        printf("\t        1�������������            \t\t\t\n");
        printf("\t --------------------------------\t\t\t\n");
        printf("\t        2�����δʹ��(LRU)         \t\t\t\n");
        printf("\t --------------------------------\t\t\t\n");
        printf("\t        3���Ƚ��ȳ�(FIFO)          \t\t\t\n");
        printf("\t--------------------------------\t\t\t\n");
        printf("\t        4�������㷨�ıȽ�()        \t\t\t\n");
        printf("\t--------------------------------\t\t\t\n");
        printf("\t        0���˳�(Exit)              \t\t\t\n");

        printf("<��ѡ����Ҫִ�еĲ���:(0)(1)(2)(3)(4)(5)>");
        scanf("%d", &sel);
        switch (sel)
        {
        case 0:printf("�ټ�!\n"); break;
        case 1:build(); break;
        case 2:printf("���δʹ���㷨\n"); LRU(); empty(); printf("\n"); break;
        case 3:printf("�Ƚ��ȳ���\n"); FIFO(); empty(); printf("\n"); break;
        case 4:printf("�Ƚ��ȳ��㷨\n"); FIFO(); empty();
            printf("���δʹ���㷨\n"); LRU(); empty(); break;
        default: printf("��������ȷ��ѡ���"); printf("\n\n"); break;
        }
    } while (sel != 0);
    return 0;
}
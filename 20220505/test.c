#define _CRT_SECURE_NO_WARNINGS 1

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
struct PCB_type
{
    int pid;
    int priority;
    int size;
    char content[10];
    int state;     // 0表示不在内存，1表示在内存，2表示挂起
};
struct PCB_type storage[20];
int num = 0, hang_up = 0, bj, i, j, pid;/*定义相关参数变量*/
/*********************创建新进程*************************/
void create()
{
    if (num >= 20)   /*判断是否有存储空间*/
        printf("\n 内存已满，请删除或挂起其他程序");
    else {
        for (i = 0; i < 20; i++)
            if (storage[i].state == 0) break; /*按顺序在内存中寻找创建新进程的空间*/
        printf("\n请输入新建进程的pid值\n");
        scanf("%d", &storage[i].pid);
        for (j = 0; j < i; j++)   /*判断是否之前已存储相同pid进程*/
            if (storage[j].pid == storage[i].pid)
            {
                printf("\n该进程已存在于内存中");
                return;
            }
        printf("\n请输入新进程的优先级 \n");
        scanf("%d", &storage[i].priority);
        printf("\n请输入新进程的大小\n");
        scanf("%d", &storage[i].size);
        printf("\n请输入新进程的内容\n");
        scanf("%s", &storage[i].content);
        storage[i].state = 1;    /*将进程状态设为1，表示在内存中*/
        num++;/*内存中进程数目加一*/
    }
}
/********************查看当前运行进程**************************/
void run()
{
    bj = 0;
    for (i = 0; i < 20; i++)
        if (storage[i].state == 1)   /*若进程状态设为1，表示在内存中，输出查看*/
        {
            printf("\n pid=%d", storage[i].pid);
            printf("   priority=%d", storage[i].priority);
            printf("   size=%d", storage[i].size);
            printf("   content=%s", storage[i].content);
            bj = 1;/*存在于内存中的进程标记为1 */
        }
    if (bj == 0)
        printf("\n当前没有运行该进程\n");/*标记为0，表示该进程未创建于内存中*/
}

/********************换出进程***************************/

void swap_out()
{
    if (num == 0)  /*num=0,表示内存中无进程*/
    {
        printf("\n当前没有运行的进程\n");
        return;
    }
    printf("\n请输入要换出的进程的pid值\n");
    scanf("%d", &pid);
    bj = 0;
    for (i = 0; i < 20; i++)
    {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 1)
            {
                storage[i].state = 2; /*将该进程的状态设为挂起*/
                hang_up++;
                printf("\n该进程已成功挂起换出\n");
            }
            else if (storage[i].state == 0)
            {
                printf("\n要换出的进程不存在\n");
            }
            else 
            {
                printf("\n要换出的进程已经被挂起\n");
            }
            bj = 1; break;
        }
    }
    if (bj == 0) printf("\n要换出的进程不存在\n");
}

    /********************杀死进程***************************/
void kill()
{
    if (num == 0)
    {
        printf("\n当前没有运行的进程\n");
        return;
    }
    printf("\n请输入要杀死的进程的pid值\n");
    scanf("%d", &pid);
    bj = 0;
    for (i = 0; i < 20; i++)
    {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 1)
            {
                storage[i].state = 0; /*将该进程的状态设为不在内存中*/
                num--;  /*内存中的进程数目减少一个*/
                printf("\n该进程已成功杀死\n");
            }
            else if (storage[i].state == 0)
            {
                printf("\n要杀死的进程不存在\n");
            }
            else
            {
                printf("\n要杀死的进程已经被挂起\n");/*剩余状态为2，挂起*/
            }
            bj = 1; break;
           
        }
    }
    if (bj == 0) 
    {
        printf("\n要杀死的进程不存在\n");
    }
 }
    /********************唤醒进程***************************/
void rouse()
{
    if (num == 0)
    {
        printf("当前没有运行的进程\n");
        return;
    }
    if (hang_up == 0)  /*hang_up=0,表示没有挂起的进程*/
    {
        printf("\n当前没有换出的进程\n");
        return;
    }
    printf("\n请输入要唤醒的进程的pid值:\n");
    scanf("%d", &pid);
    for (i = 0; i < 20; i++) {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 2)
            {
                storage[i].state = 1; /*将该进程的状态设为挂起*/
                hang_up--;
                num++;
                printf("\n该进程已成功唤醒\n");
            }
            else if (storage[i].state == 0)
                printf("\n要唤醒的进程不存在\n");
            else printf("\n要唤醒的进程已经在内存中\n");
        }
    }
}
    /********************主程序***************************/
int main()
{
    int serial, n = 1, i;
    for (i = 0; i < 20; i++)
    {
        storage[i].state = 0; /*使所有进程都初始设为不在内存中*/
    }
    while (n) {
        printf("\n**********************************************");
        printf("\n*               进程演示系统                 *");
        printf("\n**********************************************");
        printf("\n     1.创建新的进程             2.查看运行进程");
        printf("\n     3.换出某个进程             4.杀死运行进程");
        printf("\n     5.唤醒某个进程             6.退出程序    ");
        printf("\n**********************************************");
        printf("\n请选择(1～6):");
        scanf("%d", &serial);
        switch (serial)
        {
        case 1: create(); break;
        case 2:run(); break;
        case 3:swap_out(); break;
        case 4:kill(); break;
        case 5:rouse(); break;
        case 6:exit(0);
        default: printf("输入错误！"); break;
        }
    }
    return 0;
}
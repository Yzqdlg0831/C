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
    int state;     // 0��ʾ�����ڴ棬1��ʾ���ڴ棬2��ʾ����
};
struct PCB_type storage[20];
int num = 0, hang_up = 0, bj, i, j, pid;/*������ز�������*/
/*********************�����½���*************************/
void create()
{
    if (num >= 20)   /*�ж��Ƿ��д洢�ռ�*/
        printf("\n �ڴ���������ɾ���������������");
    else {
        for (i = 0; i < 20; i++)
            if (storage[i].state == 0) break; /*��˳�����ڴ���Ѱ�Ҵ����½��̵Ŀռ�*/
        printf("\n�������½����̵�pidֵ\n");
        scanf("%d", &storage[i].pid);
        for (j = 0; j < i; j++)   /*�ж��Ƿ�֮ǰ�Ѵ洢��ͬpid����*/
            if (storage[j].pid == storage[i].pid)
            {
                printf("\n�ý����Ѵ������ڴ���");
                return;
            }
        printf("\n�������½��̵����ȼ� \n");
        scanf("%d", &storage[i].priority);
        printf("\n�������½��̵Ĵ�С\n");
        scanf("%d", &storage[i].size);
        printf("\n�������½��̵�����\n");
        scanf("%s", &storage[i].content);
        storage[i].state = 1;    /*������״̬��Ϊ1����ʾ���ڴ���*/
        num++;/*�ڴ��н�����Ŀ��һ*/
    }
}
/********************�鿴��ǰ���н���**************************/
void run()
{
    bj = 0;
    for (i = 0; i < 20; i++)
        if (storage[i].state == 1)   /*������״̬��Ϊ1����ʾ���ڴ��У�����鿴*/
        {
            printf("\n pid=%d", storage[i].pid);
            printf("   priority=%d", storage[i].priority);
            printf("   size=%d", storage[i].size);
            printf("   content=%s", storage[i].content);
            bj = 1;/*�������ڴ��еĽ��̱��Ϊ1 */
        }
    if (bj == 0)
        printf("\n��ǰû�����иý���\n");/*���Ϊ0����ʾ�ý���δ�������ڴ���*/
}

/********************��������***************************/

void swap_out()
{
    if (num == 0)  /*num=0,��ʾ�ڴ����޽���*/
    {
        printf("\n��ǰû�����еĽ���\n");
        return;
    }
    printf("\n������Ҫ�����Ľ��̵�pidֵ\n");
    scanf("%d", &pid);
    bj = 0;
    for (i = 0; i < 20; i++)
    {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 1)
            {
                storage[i].state = 2; /*���ý��̵�״̬��Ϊ����*/
                hang_up++;
                printf("\n�ý����ѳɹ����𻻳�\n");
            }
            else if (storage[i].state == 0)
            {
                printf("\nҪ�����Ľ��̲�����\n");
            }
            else 
            {
                printf("\nҪ�����Ľ����Ѿ�������\n");
            }
            bj = 1; break;
        }
    }
    if (bj == 0) printf("\nҪ�����Ľ��̲�����\n");
}

    /********************ɱ������***************************/
void kill()
{
    if (num == 0)
    {
        printf("\n��ǰû�����еĽ���\n");
        return;
    }
    printf("\n������Ҫɱ���Ľ��̵�pidֵ\n");
    scanf("%d", &pid);
    bj = 0;
    for (i = 0; i < 20; i++)
    {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 1)
            {
                storage[i].state = 0; /*���ý��̵�״̬��Ϊ�����ڴ���*/
                num--;  /*�ڴ��еĽ�����Ŀ����һ��*/
                printf("\n�ý����ѳɹ�ɱ��\n");
            }
            else if (storage[i].state == 0)
            {
                printf("\nҪɱ���Ľ��̲�����\n");
            }
            else
            {
                printf("\nҪɱ���Ľ����Ѿ�������\n");/*ʣ��״̬Ϊ2������*/
            }
            bj = 1; break;
           
        }
    }
    if (bj == 0) 
    {
        printf("\nҪɱ���Ľ��̲�����\n");
    }
 }
    /********************���ѽ���***************************/
void rouse()
{
    if (num == 0)
    {
        printf("��ǰû�����еĽ���\n");
        return;
    }
    if (hang_up == 0)  /*hang_up=0,��ʾû�й���Ľ���*/
    {
        printf("\n��ǰû�л����Ľ���\n");
        return;
    }
    printf("\n������Ҫ���ѵĽ��̵�pidֵ:\n");
    scanf("%d", &pid);
    for (i = 0; i < 20; i++) {
        if (pid == storage[i].pid)
        {
            if (storage[i].state == 2)
            {
                storage[i].state = 1; /*���ý��̵�״̬��Ϊ����*/
                hang_up--;
                num++;
                printf("\n�ý����ѳɹ�����\n");
            }
            else if (storage[i].state == 0)
                printf("\nҪ���ѵĽ��̲�����\n");
            else printf("\nҪ���ѵĽ����Ѿ����ڴ���\n");
        }
    }
}
    /********************������***************************/
int main()
{
    int serial, n = 1, i;
    for (i = 0; i < 20; i++)
    {
        storage[i].state = 0; /*ʹ���н��̶���ʼ��Ϊ�����ڴ���*/
    }
    while (n) {
        printf("\n**********************************************");
        printf("\n*               ������ʾϵͳ                 *");
        printf("\n**********************************************");
        printf("\n     1.�����µĽ���             2.�鿴���н���");
        printf("\n     3.����ĳ������             4.ɱ�����н���");
        printf("\n     5.����ĳ������             6.�˳�����    ");
        printf("\n**********************************************");
        printf("\n��ѡ��(1��6):");
        scanf("%d", &serial);
        switch (serial)
        {
        case 1: create(); break;
        case 2:run(); break;
        case 3:swap_out(); break;
        case 4:kill(); break;
        case 5:rouse(); break;
        case 6:exit(0);
        default: printf("�������"); break;
        }
    }
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

struct  PCB_type
{
	int  pid;     //������
	int   state;    //����״̬ 
				  //2--��ʾ"ִ��"״̬
				  //1--��ʾ"����"״̬ 
				  //0--��ʾ"����"״̬
	int  cpu_time;  //������Ҫ��CPUʱ�䣨�����е�ʱ��Ƭ������
};
struct QueueNode {
	struct  PCB_type   PCB;
	struct  QueueNode* next;
};
struct  QueueNode* ready_head = NULL,     //ready���ж���ָ��
	* ready_tail = NULL,     //ready���ж�βָ��
	* block_head = NULL,    //blocked���ж���ָ��
	* block_tail = NULL;     //blocked���ж�βָ��


int use_cpu, unuse_cpu;

void start_state()  //�����������ݣ�����ϵͳ��ʼ״̬
{
	int n, m;
	int i;
	struct  QueueNode* p, * q;
	printf("��������ڵ����n:");
	scanf("%d", &n);
	printf("���������ڵ����m:");
	scanf("%d", &m);
	p = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if (p != NULL)
	{
		p->next = NULL;
	}
	ready_head = ready_tail = p;
	for (i = 0; i < n; i++)
	{
		p = (struct QueueNode*)malloc(sizeof(struct QueueNode));
		if (p != NULL)
		{
			p->next = NULL;
			p->PCB.state = 1;
			printf("�����������%d��pid��cpu_time:", i + 1);
			scanf("%d%d", &p->PCB.pid, &p->PCB.cpu_time);
		}
		if (ready_tail != NULL)
		{
			ready_tail->next = p;
		}
		ready_tail = p;
	}
	q = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if (q != NULL)
	{
		q->next = NULL;
	}
	block_head = block_tail = q;
	for (i = 0; i < m; i++)
	{
		q = (struct QueueNode*)malloc(sizeof(struct QueueNode));
		if (q != NULL)
		{
			q->next = NULL;
			q->PCB.state = 0;
		}
		printf("������������%d��pid��cpu_time:", i + 1);
		if (q != NULL)
		{
			scanf("%d%d", &q->PCB.pid, &q->PCB.cpu_time);
		}
		if (block_tail != NULL)
		{
			block_tail->next = q;
		}
		block_tail = q;
	}

	printf("\n���ھ���״̬�Ľ�����:\n");
	
	if (ready_head != NULL)
	{
		p = ready_head->next;
	}
	i = 1;
	while (p)
	{
		printf("����%d��pid��state��cpu_time:%5d%5d%5d\n", i, p->PCB.pid, p->PCB.state, p->PCB.cpu_time);
		p = p->next;
		i++;
	}
}
void dispath()       //ģ�����
{
	int x = 0, t;
	use_cpu = 0;
	unuse_cpu = 0;
	printf("����t:");
	scanf("%d", &t);
	printf("��ʼ����\n");
	while (ready_head != ready_tail || block_head != block_tail)
	{
		struct  QueueNode* p, * q;

		if (ready_head != ready_tail)
		{
			p = ready_head->next;
			ready_head->next = p->next;
			p->next = NULL;
			if (ready_head->next == NULL)
			{
				ready_tail = ready_head;
			}
			p->PCB.state = 2;
			printf("����%d����\t\n", p->PCB.pid);
			use_cpu++;
			x++;
			p->PCB.cpu_time--;
			if (p->PCB.cpu_time)
			{
				ready_tail->next = p;
				ready_tail = p;
			}
			else
			{
				printf("����%d���\t\n", p->PCB.pid);
				free(p);
			}
		}
		else
		{
			unuse_cpu++;
			x++;
			printf("����һ��ʱ��Ƭ\t\n");
		}
		if (x == t && block_head != block_tail)
		{
			q = block_head->next;
			block_head->next = q->next;
			q->next = NULL;
			if (block_head->next == NULL)
			{
				block_tail = block_head;
			}
			ready_tail->next = q;
			ready_tail = q;
			x = 0;
		}
	}
}
void calculate()    //����CPU������
{
	printf("\ncpu��������%.2f\n", (float)use_cpu / (use_cpu + unuse_cpu));

}
int main()
{
	start_state();
	dispath();
	calculate();
	return 0;
}
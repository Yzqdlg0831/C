#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

struct  PCB_type
{
	int  pid;     //进程名
	int   state;    //进程状态 
				  //2--表示"执行"状态
				  //1--表示"就绪"状态 
				  //0--表示"阻塞"状态
	int  cpu_time;  //运行需要的CPU时间（需运行的时间片个数）
};
struct QueueNode {
	struct  PCB_type   PCB;
	struct  QueueNode* next;
};
struct  QueueNode* ready_head = NULL,     //ready队列队首指针
	* ready_tail = NULL,     //ready队列队尾指针
	* block_head = NULL,    //blocked队列队首指针
	* block_tail = NULL;     //blocked队列队尾指针


int use_cpu, unuse_cpu;

void start_state()  //读入假设的数据，设置系统初始状态
{
	int n, m;
	int i;
	struct  QueueNode* p, * q;
	printf("输入就绪节点个数n:");
	scanf("%d", &n);
	printf("输入阻塞节点个数m:");
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
			printf("输入就绪进程%d的pid和cpu_time:", i + 1);
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
		printf("输入阻塞进程%d的pid和cpu_time:", i + 1);
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

	printf("\n处于就绪状态的进程有:\n");
	
	if (ready_head != NULL)
	{
		p = ready_head->next;
	}
	i = 1;
	while (p)
	{
		printf("进程%d的pid和state和cpu_time:%5d%5d%5d\n", i, p->PCB.pid, p->PCB.state, p->PCB.cpu_time);
		p = p->next;
		i++;
	}
}
void dispath()       //模拟调度
{
	int x = 0, t;
	use_cpu = 0;
	unuse_cpu = 0;
	printf("输入t:");
	scanf("%d", &t);
	printf("开始调度\n");
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
			printf("进程%d调度\t\n", p->PCB.pid);
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
				printf("进程%d完成\t\n", p->PCB.pid);
				free(p);
			}
		}
		else
		{
			unuse_cpu++;
			x++;
			printf("空闲一个时间片\t\n");
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
void calculate()    //计算CPU利用率
{
	printf("\ncpu的利用率%.2f\n", (float)use_cpu / (use_cpu + unuse_cpu));

}
int main()
{
	start_state();
	dispath();
	calculate();
	return 0;
}
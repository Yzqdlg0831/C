#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void meun()
{
	printf("***************************\n");
	printf("******    1.Play     ******\n");
	printf("******    0.exit     ******\n");
	printf("***************************\n");
}

void game()
{
	//rand���ɵ����ֵ��Χ0--0x7fff��32767��
	int num = rand() % 100 + 1;
	int n = 0;
	printf("�����ֿ�ʼ������\n");
	while (1)
	{
		printf("��������Ҫ�µ����֣�");
		scanf("%d", &n);
		if (n > num)
		{
			printf("�´��ˣ�\n");
		}
		else if (n < num)
		{
			printf("��С�ˣ�\n");
		}
		else
		{
			printf("��ϲ�����¶��ˣ�����\n");
			break;
		}
	}
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{  
		//��ӡ�˵�
		meun();
		printf("\n��ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ��\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
	return 0;
}
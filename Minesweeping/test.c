#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		meun();
		printf("ɨ����Ϸ>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�Ƴ���Ϸ��");
			break;
		default:
			printf("ѡ�����");
			break;
		}
	} while (input);

	return 0;
}
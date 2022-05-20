#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#define HIGH 20  //��Ϸ����߶�
#define WIDTH 30  // ��Ϸ������
//#define NUM 10  //�л������ٶ�
int flag = 0;
int color(int c);          			 //����������ɫ
int position_x, position_y;  //�ɻ�λ��
int bullet_x, bullet_y;  //�ӵ�λ��
int enemy_x, enemy_y;  //�л�λ��
int score;  //�÷�
int i, j, p;
static int speed = 0;
int NUM = 10, vt;
int k;
typedef struct Node
{
    int x;
    int y;
    struct Node* pnext;
}PLANE;

PLANE* plane = NULL;
PLANE* pnew = NULL;//����һ���½ڵ㣬��ָ��ղ���ֹҰָ�룻
void CreateList()//��������
{
    plane = (PLANE*)malloc(sizeof(PLANE));
    plane->pnext = NULL;
}
void AddNode()  //���ӽڵ�
{
    //Ϊ�µĽڵ㿪�ٿռ�
    pnew = (PLANE*)malloc(sizeof(PLANE));

    pnew->x = rand() % HIGH;
    pnew->y = rand() % WIDTH;
    //�ѽڵ���������
    pnew->pnext = plane->pnext;//ͷ�巨
    plane->pnext = pnew;
}
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
    return 0;
}
void gotoxy(int x, int y) //����������(x,y)��λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void HideCursor()  //���ع����ʾ
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()//���ݵĳ�ʼ��
{
    //��ʼ���ɻ�
    position_x = HIGH / 2; //�߶�
    position_y = WIDTH / 2; //���

    //��ʼ���ӵ�
    bullet_x = -1;
    bullet_y = position_y;

    //��ʼ���л�
    enemy_x = 0;
    enemy_y = position_y;

    //��ʼ���÷�
    score = 0;
}

void show()//��ʾ����
{
    // system("cls"); //��������  
    gotoxy(0, 0); //ʹ���ص�0��0


    for (i = 0; i < HIGH; i++) //��
    {
        for (j = 0; j < WIDTH; j++) //��
        {
            if (i == position_x && j == position_y)//����ɻ�
            {
                printf("��");
            }
            else if (i == bullet_x && j == bullet_y)//����ӵ�
            {
                printf("|");
            }
            else if (i == enemy_x && j == enemy_y)//����л�
            {
                printf("��");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//��ӡ�߽� 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        if ((position_x == enemy_x) && (position_y == enemy_y))
        {
            //�ɻ�ײ�� ��Ϸ���� 
            system("cls");
            gotoxy(43, 15);
            printf("����ˣ���Ϸ����!!!\n");
            exit(0);
        }
        printf("\n");
    }

}

void show_2()//��ʾ����  ����ģʽ��չʾ
{
    // system("cls"); //��������  
    gotoxy(0, 0); //ʹ���ص�0��0


    for (i = 0; i < HIGH; i++) //��
    {
        for (j = 0; j < WIDTH; j++) //��
        {
            if (i == position_x && j == position_y)//����ɻ�
            {
                printf("��");
            }
            else if (i == bullet_x && j == bullet_y)//����ӵ�
            {
                printf("|");
            }
            else if (i == enemy_x && j == enemy_y)//����л�
            {
                printf("��");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//��ӡ�߽� 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

}
void bulletMove()   //�ӵ�׷��ģʽ
{
    if (bullet_x > enemy_x)
        bullet_x--;
    else if (bullet_x < enemy_x)
        bullet_x++;
    if (bullet_y > enemy_y)
        bullet_y--;
    else if (bullet_y < enemy_y)
        bullet_y++;
}

void leavehand()//����ģʽ
{
    if (position_y == enemy_y && flag == 0)
    {
        flag = 1;
        bullet_y = position_y;
        bullet_x = position_x - 1;
    }
    else if (position_y < enemy_y)
        position_y++;
    else
        position_y--;
}
void updateWitoutIput_1()//���û������޹صĸ���
{
    if (bullet_x > -1) //���ӵ�������
    {
        bullet_x--;
    }
    if (bullet_x == enemy_x && bullet_y == enemy_y) //���ел�
    {
        score++;  //�÷�+1

        enemy_x = -1;   //�����µķɻ�
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //���ӵ�ֱ�ӳ�����Ļ�⣬ֱ����һ�η����ӵ�
    }

    //���Ƶл������ٶ�
    if (speed < NUM)  //ÿ����NUM�εл�����һ��
    {
        speed++;
    }
    else
    {
        enemy_x++;
        speed = 0;
    }
    if (enemy_x > HIGH)  //�л�һֱ���䵽�ײ�
    {
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
    }

}

void updateWitoutIput_2()//���û������޹صĸ���
{
    if ((bullet_x > -1) && (bullet_y > -1))
        bulletMove();
    if (bullet_x == enemy_x && bullet_y == enemy_y) //���ел�
    {
        score++;  //�÷�+1

        enemy_x = -1;   //�����µķɻ�
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //���ӵ�ֱ�ӳ�����Ļ�⣬ֱ����һ�η����ӵ�
    }

    //���Ƶл������ٶ�
    if (speed < NUM)  //ÿ����NUM�εл�����һ��
    {
        speed++;
    }
    else
    {
        enemy_x++;
        speed = 0;
    }
    if (enemy_x > HIGH)  //�л�һֱ���䵽�ײ�
    {
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
    }

}
void updateWitoutIput_3()//���û������޹صĸ���
{
    if ((bullet_x > -1) && (bullet_y > -1))
        leavehand();
    if (bullet_x > -1)
        bullet_x--;
    if (bullet_x == enemy_x && bullet_y == enemy_y) //���ел�
    {
        score++;  //�÷�+1
        flag = 0;
        //bullet_y=40;
        enemy_x = -1;   //�����µķɻ�
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //���ӵ�ֱ�ӳ�����Ļ�⣬ֱ����һ�η����ӵ�
    }

}
void updateWithInput()//���û������йصĸ���
{
    //�û�����
    char input;//���Ʒɻ�����
    if (_kbhit())
    {
        input = _getch();
        if (input == 'w' && position_x > 1)
            position_x--;
        if (input == 's' && position_x < HIGH - 1)
            position_x++;
        if (input == 'a' && position_y > 1)
            position_y--;
        if (input == 'd' && position_y < WIDTH - 1)
            position_y++;
        if (input == ' ')
        {
            bullet_x = position_x - 1;
            bullet_y = position_y;
        }
    }
}
void moden()//�����Ѷ�
{
    if (vt == 1)
        NUM = 10;
    else if (vt == 2)
        NUM = 30;
    else if (vt == 3)
        NUM = 50;
    else
    {
        printf("��Ҫ̫Ƥ\n");
        exit(0);
    }
}
void scoreandtips()//��Ϸ�����ʾ 
{
    gotoxy(50, 8);
    color(14);
    printf("��Ϸ�÷֣�%d ", score);
    gotoxy(50, 10);
    printf("��W A S D �ֱ���Ʒɻ����ƶ�");
    gotoxy(50, 12);
    printf("���¿ո����Ϊ�����ڵ�");
    gotoxy(50, 14);
    printf("��  �����Ӿ��ǵ��˵ķɻ�");
    gotoxy(50, 16);
    printf("ײ��������Ŷ");
    gotoxy(50, 18);

}
void appearance()
{
    system("mode con cols=120 lines=30");
    color(15);
    gotoxy(43, 10);
    printf("    �� �� �� ս       \n");
    color(11);
    gotoxy(42, 12);
    printf("��ӭ�����ɻ���ս ��ѡ��ģʽ\n");
    gotoxy(45, 14);
    printf("  1.����ģʽ    \n");
    gotoxy(45, 15);
    printf("  2.�ƽ�ģʽ    \n");
    gotoxy(45, 16);
    printf("  3.˫���뿪����ģʽ\n");
    gotoxy(45, 17);
    printf("  4.�������\n");
    gotoxy(42, 18);
    printf("��ʾ��W A S D �ƶ����ո����ӵ�\n");
    gotoxy(45, 1);
    printf("ps:�����Ǳ�����");
    gotoxy(45, 20);
    scanf("%d", &p);
    //PlaySound(TEXT("D://δ������.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

}
void ssb()
{
    system("cls");
    gotoxy(45, 10);
    printf("��Ƥ����������Ϸ\n");
    gotoxy(45, 12);
    printf("������������666");
    gotoxy(45, 14);
    scanf("%d", &k);
    if (k == 666)
    {
        gotoxy(45, 16);
        color(11);
        printf("��");
        color(12);
        printf("��");
        color(13);
        printf("��");
        color(10);
        gotoxy(45, 17);
        printf("Ƥһ�ºܿ���");
        color(14);
    }
}
void alive() //�Զ�����ģʽ
{
    if ((position_x == enemy_x) && (position_y == enemy_y))
    {
        AddNode(); //���ӽڵ㣬���ɻ���
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
        position_x = pnew->x;
        position_y = pnew->y; //�ɻ�ײ�� �������ɷɻ��� 
    }

}
int main()
{
    appearance();
    if (p == 1)
    {
        gotoxy(0, 0);
        system("cls");
        color(6);
        gotoxy(43, 10);
        printf("�������Ѷ�\n");
        gotoxy(43, 11);
        printf("1.��  ���о��е㲻̫Э����\n");
        gotoxy(43, 12);
        printf("2.�ܼ� ���������ɣ�\n");
        gotoxy(43, 13);
        printf("3.����򵥣�̫�Ѹ��ˣ�\n");
        gotoxy(43, 14);
        scanf("%d", &vt);
        moden();//ѡ��ģʽ
        system("cls");
        startup();//��ʼ��
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)  //ѭ��ִ��
        {
            gotoxy(0, 0);
            scoreandtips();
            show();//��ʾ����   
            updateWitoutIput_1();//���û������޹صĸ���  �������� 
            updateWithInput(); //���û������йصĸ���  ������� 
        }
        system("pause");
        return 0;
    }

    if (p == 2)
    {
        system("cls");
        startup();//��ʼ��
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)
        {
            scoreandtips();
            show();//��ʾ����  
            updateWitoutIput_2();//���û������޹صĸ���  //��������
            updateWithInput(); //���û������йصĸ���  //�������
        }
        system("pause");//��ֹ����
        return 0;
    }
    if (p == 3)
    {
        system("cls");
        startup();//��ʼ��
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)
        {
            scoreandtips();
            show();//��ʾ���� 
            leavehand();
            updateWitoutIput_3();//���û������޹صĸ���  //��������

        }
        system("pause");//��ֹ����
        return 0;
    }
    if (p == 4)
    {

        system("cls");
        startup();//��ʼ��
        HideCursor();
        srand((unsigned)time(NULL));
        CreateList();
        while (1)  //ѭ��ִ��
        {
            gotoxy(0, 0);
            scoreandtips();
            show_2();//��ʾ����  
            alive();
            updateWitoutIput_1();//���û������޹صĸ���  �������� 
            updateWithInput(); //���û������йصĸ���  ������� 
        }
        system("pause");
        return 0;
    }
    else
        ssb();
}


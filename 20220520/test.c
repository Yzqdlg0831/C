#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#define HIGH 20  //游戏界面高度
#define WIDTH 30  // 游戏界面宽度
//#define NUM 10  //敌机下落速度
int flag = 0;
int color(int c);          			 //更改文字颜色
int position_x, position_y;  //飞机位置
int bullet_x, bullet_y;  //子弹位置
int enemy_x, enemy_y;  //敌机位置
int score;  //得分
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
PLANE* pnew = NULL;//定义一个新节点，并指向空并防止野指针；
void CreateList()//创建链表
{
    plane = (PLANE*)malloc(sizeof(PLANE));
    plane->pnext = NULL;
}
void AddNode()  //增加节点
{
    //为新的节点开辟空间
    pnew = (PLANE*)malloc(sizeof(PLANE));

    pnew->x = rand() % HIGH;
    pnew->y = rand() % WIDTH;
    //把节点连接起来
    pnew->pnext = plane->pnext;//头插法
    plane->pnext = pnew;
}
int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
    return 0;
}
void gotoxy(int x, int y) //将光标调整到(x,y)的位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void HideCursor()  //隐藏光标显示
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()//数据的初始化
{
    //初始化飞机
    position_x = HIGH / 2; //高度
    position_y = WIDTH / 2; //宽度

    //初始化子弹
    bullet_x = -1;
    bullet_y = position_y;

    //初始化敌机
    enemy_x = 0;
    enemy_y = position_y;

    //初始化得分
    score = 0;
}

void show()//显示画面
{
    // system("cls"); //清屏函数  
    gotoxy(0, 0); //使光标回到0，0


    for (i = 0; i < HIGH; i++) //行
    {
        for (j = 0; j < WIDTH; j++) //列
        {
            if (i == position_x && j == position_y)//输出飞机
            {
                printf("Ж");
            }
            else if (i == bullet_x && j == bullet_y)//输出子弹
            {
                printf("|");
            }
            else if (i == enemy_x && j == enemy_y)//输出敌机
            {
                printf("Ψ");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//打印边界 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        if ((position_x == enemy_x) && (position_y == enemy_y))
        {
            //飞机撞毁 游戏结束 
            system("cls");
            gotoxy(43, 15);
            printf("你挂了，游戏结束!!!\n");
            exit(0);
        }
        printf("\n");
    }

}

void show_2()//显示画面  复活模式的展示
{
    // system("cls"); //清屏函数  
    gotoxy(0, 0); //使光标回到0，0


    for (i = 0; i < HIGH; i++) //行
    {
        for (j = 0; j < WIDTH; j++) //列
        {
            if (i == position_x && j == position_y)//输出飞机
            {
                printf("Ж");
            }
            else if (i == bullet_x && j == bullet_y)//输出子弹
            {
                printf("|");
            }
            else if (i == enemy_x && j == enemy_y)//输出敌机
            {
                printf("Ψ");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//打印边界 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

}
void bulletMove()   //子弹追踪模式
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

void leavehand()//离手模式
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
void updateWitoutIput_1()//与用户输入无关的更新
{
    if (bullet_x > -1) //让子弹向上落
    {
        bullet_x--;
    }
    if (bullet_x == enemy_x && bullet_y == enemy_y) //命中敌机
    {
        score++;  //得分+1

        enemy_x = -1;   //生成新的飞机
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //让子弹直接出现屏幕外，直到下一次发射子弹
    }

    //控制敌机下落速度
    if (speed < NUM)  //每进行NUM次敌机下落一次
    {
        speed++;
    }
    else
    {
        enemy_x++;
        speed = 0;
    }
    if (enemy_x > HIGH)  //敌机一直下落到底部
    {
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
    }

}

void updateWitoutIput_2()//与用户输入无关的更新
{
    if ((bullet_x > -1) && (bullet_y > -1))
        bulletMove();
    if (bullet_x == enemy_x && bullet_y == enemy_y) //命中敌机
    {
        score++;  //得分+1

        enemy_x = -1;   //生成新的飞机
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //让子弹直接出现屏幕外，直到下一次发射子弹
    }

    //控制敌机下落速度
    if (speed < NUM)  //每进行NUM次敌机下落一次
    {
        speed++;
    }
    else
    {
        enemy_x++;
        speed = 0;
    }
    if (enemy_x > HIGH)  //敌机一直下落到底部
    {
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
    }

}
void updateWitoutIput_3()//与用户输入无关的更新
{
    if ((bullet_x > -1) && (bullet_y > -1))
        leavehand();
    if (bullet_x > -1)
        bullet_x--;
    if (bullet_x == enemy_x && bullet_y == enemy_y) //命中敌机
    {
        score++;  //得分+1
        flag = 0;
        //bullet_y=40;
        enemy_x = -1;   //生成新的飞机
        enemy_y = rand() % WIDTH;

        bullet_x = -1;  //让子弹直接出现屏幕外，直到下一次发射子弹
    }

}
void updateWithInput()//与用户输入有关的更新
{
    //用户输入
    char input;//控制飞机飞行
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
void moden()//设置难度
{
    if (vt == 1)
        NUM = 10;
    else if (vt == 2)
        NUM = 30;
    else if (vt == 3)
        NUM = 50;
    else
    {
        printf("不要太皮\n");
        exit(0);
    }
}
void scoreandtips()//游戏侧边提示 
{
    gotoxy(50, 8);
    color(14);
    printf("游戏得分：%d ", score);
    gotoxy(50, 10);
    printf("用W A S D 分别控制飞机的移动");
    gotoxy(50, 12);
    printf("按下空格键即为发射炮弹");
    gotoxy(50, 14);
    printf("Ж  的样子就是敌人的飞机");
    gotoxy(50, 16);
    printf("撞击会死亡哦");
    gotoxy(50, 18);

}
void appearance()
{
    system("mode con cols=120 lines=30");
    color(15);
    gotoxy(43, 10);
    printf("    飞 机 大 战       \n");
    color(11);
    gotoxy(42, 12);
    printf("欢迎来到飞机大战 请选择模式\n");
    gotoxy(45, 14);
    printf("  1.正常模式    \n");
    gotoxy(45, 15);
    printf("  2.破解模式    \n");
    gotoxy(45, 16);
    printf("  3.双手离开键盘模式\n");
    gotoxy(45, 17);
    printf("  4.随机复活\n");
    gotoxy(42, 18);
    printf("提示：W A S D 移动，空格发射子弹\n");
    gotoxy(45, 1);
    printf("ps:大佬们别挑刺");
    gotoxy(45, 20);
    scanf("%d", &p);
    //PlaySound(TEXT("D://未来初音.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

}
void ssb()
{
    system("cls");
    gotoxy(45, 10);
    printf("别皮！认真玩游戏\n");
    gotoxy(45, 12);
    printf("还想玩请输入666");
    gotoxy(45, 14);
    scanf("%d", &k);
    if (k == 666)
    {
        gotoxy(45, 16);
        color(11);
        printf("哈");
        color(12);
        printf("哈");
        color(13);
        printf("哈");
        color(10);
        gotoxy(45, 17);
        printf("皮一下很开心");
        color(14);
    }
}
void alive() //自动复活模式
{
    if ((position_x == enemy_x) && (position_y == enemy_y))
    {
        AddNode(); //增加节点，即飞机；
        enemy_x = -1;
        enemy_y = rand() % WIDTH;
        position_x = pnew->x;
        position_y = pnew->y; //飞机撞毁 重新生成飞机； 
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
        printf("请输入难度\n");
        gotoxy(43, 11);
        printf("1.简单  （感觉有点不太协调）\n");
        gotoxy(43, 12);
        printf("2.很简单 （就这样吧）\n");
        gotoxy(43, 13);
        printf("3.极其简单（太难搞了）\n");
        gotoxy(43, 14);
        scanf("%d", &vt);
        moden();//选择模式
        system("cls");
        startup();//初始化
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)  //循环执行
        {
            gotoxy(0, 0);
            scoreandtips();
            show();//显示画面   
            updateWitoutIput_1();//与用户输入无关的更新  更新数据 
            updateWithInput(); //与用户输入有关的更新  输入分析 
        }
        system("pause");
        return 0;
    }

    if (p == 2)
    {
        system("cls");
        startup();//初始化
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)
        {
            scoreandtips();
            show();//显示画面  
            updateWitoutIput_2();//与用户输入无关的更新  //更新数据
            updateWithInput(); //与用户输入有关的更新  //输入分析
        }
        system("pause");//防止闪屏
        return 0;
    }
    if (p == 3)
    {
        system("cls");
        startup();//初始化
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)
        {
            scoreandtips();
            show();//显示画面 
            leavehand();
            updateWitoutIput_3();//与用户输入无关的更新  //更新数据

        }
        system("pause");//防止闪屏
        return 0;
    }
    if (p == 4)
    {

        system("cls");
        startup();//初始化
        HideCursor();
        srand((unsigned)time(NULL));
        CreateList();
        while (1)  //循环执行
        {
            gotoxy(0, 0);
            scoreandtips();
            show_2();//显示画面  
            alive();
            updateWitoutIput_1();//与用户输入无关的更新  更新数据 
            updateWithInput(); //与用户输入有关的更新  输入分析 
        }
        system("pause");
        return 0;
    }
    else
        ssb();
}


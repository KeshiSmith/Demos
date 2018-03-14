///////////////////////////////////////////////////
//本游戏于15年元旦节完成，是我的第二个小游戏，
//本版本通过优化减少了游戏闪烁，
//程序通过VC2013编译。

#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
//宏定义常用关键字
#define uchar unsigned char
#define uint unsigned int
//函数声明
void gotoXY(int x, int y);//光标移动函数定义
void bound();		//分界线函数声明
char input(char);	//输入函数声明
void GUI();		//用户界面函数声明
void help();     //游戏说明函数声明
bool opt();		//难度选择函数声明
bool CG();		//开头动画函数声明
void print();	//游戏显示函数声明
void game();	//游戏操作函数声明
bool delay();	//延时检测函数声明
bool back();	//暂停菜单函数声明
void heart();	//心脏产生函数声明
void gameover();	//游戏结束函数声明
//全局变量声明
char hard, flag, lenth, direction, table[10][10], snake[101][2];
uint score;
//主函数
int main()
{
	char i, j;
	system("title 可是的贪吃蛇");
	system("mode con: cols=40 lines=18");
	while (true)
	{
		GUI();
		if (opt())
		{
			//游戏数据复位操作
			for (i = 0; i<10; i++)
				for (j = 0; j<10; j++)
					table[i][j] = 0;
			table[0][0] = 1; table[0][1] = 2;
			snake[0][0] = 0; snake[0][1] = 0;	//snake存放蛇身的坐标(x,y)
			snake[1][0] = 0; snake[1][1] = 1;
			for (i = 2; i<100; i++)
				snake[i][0] = 0;
			flag = 0; score = 0; lenth = 1;		//lenth存放蛇身长度-1的值
			direction = 4;
			//产生初始心脏
			srand(time(NULL) * 10);
			heart();
			if (CG())
				game();
		}
	}
	return 0;
}
//光标移动函数定义
void gotoXY(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//分界线函数定义
void bound()
{
	printf("----------------------------------------");
}
//输入函数定义
char input(char mode)		//mode==1 {输入等待模式} ;  mode==2 {实时检测模式}
{							//↑返回值为1     ↓返回值为2     ←返回值为3     →返回值为4
	uchar key1, key2;		//SPACE/ENTER返回值为5     ESC返回值为0     其他返回值-1
	if (mode || (!mode&&_kbhit()))
	{
		key1 = _getch();
		if (key1 == 27)
			return 0;
		if (key1 == 32 || key1 == 13)
			return 5;
		if (key1 == 224)
			key2 = _getch();
		switch (key2)
		{
		case 72: return 1;
		case 80: return 2;
		case 75: return 3;
		case 77: return 4;
		}
	}
	return  -1;
}
//用户界面函数定义
void GUI()
{
	char sta = 0, key, choose[7][20] = { "开始游戏", "-> 开始游戏 <-", "游戏说明", "-> 游戏说明 <-", "结束游戏", "-> 结束游戏 <-", "可 是 的 贪 吃 蛇" };
	while (true)
	{
		system("cls");
		bound();
		if (sta == 0)					//用户界面显示
		{
			printf("\n\n           %s\n", choose[6]);
			printf("\n\n\n\n            %s\n", choose[1]);
			printf("\n               %s\n", choose[2]);
			printf("\n               %s\n\n\n", choose[4]);
		}
		if (sta == 1)
		{
			printf("\n\n           %s\n", choose[6]);
			printf("\n\n\n\n               %s\n", choose[0]);
			printf("\n            %s\n", choose[3]);
			printf("\n               %s\n\n\n", choose[4]);
		}
		if (sta == 2)
		{
			printf("\n\n           %s\n", choose[6]);
			printf("\n\n\n\n               %s\n", choose[0]);
			printf("\n               %s\n", choose[2]);
			printf("\n            %s\n\n\n", choose[5]);
		}
		bound();
		key = input(1);
		if (key == 0)					//按键检测与操作
			exit(0);
		else if (sta == 0 && key == 5)
			break;
		else if (sta == 0 && key == 2)
			sta = 1;
		else if (sta == 1 && key == 5)
			help();
		else if (sta == 1 && key == 1)
			sta = 0;
		else if (sta == 1 && key == 2)
			sta = 2;
		else if (sta == 2 && key == 5)
			exit(0);
		else if (sta == 2 && key == 1)
			sta = 1;
	}
}
//游戏说明函数定义
void help()
{
	system("cls");
	bound();
	printf("           可 是 的 贪 吃 蛇\n");
	bound();
	printf("\n    游戏说明:这是一个悲伤的故事,一条受伤的蛇发誓要吃掉世界上所有人的心。现在，你来帮助这条蛇毁灭世界吧!\n");
	printf("\n    游戏要求:尽可能地吃到多的红心。\n");
	printf("\n    注意事项:不要撞到自己或墙壁。\n");
	printf("\n    游戏操作:方向键控制蛇前进的方向\n    SPACE确定/技能     ESC暂停/返回\n\n");
	bound();
	system("pause");
}
//难度选择函数定义
bool opt()
{
	char key, sta = 1, choose[5][5] = { "小白", "简单", "中等", "困难", "噩梦" };
	while (true)
	{
		system("cls");
		bound();
		printf("\n\n           可 是 的 贪 吃 蛇\n");
		printf("\n\n\n                       ——\n");
		printf("                       %s\n", choose[(sta + 1) % 5]);
		printf("                       —— \n");
		printf("          难度选择: -> %s <-\n", choose[sta]);
		printf("                       ——\n");
		printf("                       %s\n", choose[(sta + 4) % 5]);
		printf("                       ——\n\n");

		bound();
		key = input(1);
		if (key == 0)
			return false;
		else if (key == 2)
			sta = (sta + 1) % 5;
		else if (key == 1)
			sta = (sta + 4) % 5;
		else if (key == 5)
		{
			hard = sta + 1;
			return true;
		}
	}
}
//开头动画函数定义
bool CG()
{
	int i, j;
	char key, sta = 0, choose[4][15] = { "是", "-> 是 <-", "否", "-> 否 <-" };
	while (true)
	{
		system("cls");
		bound();
		printf("\n\n\n\n\n");
		if (sta == 0)
			printf("    是否跳过CG?     -> 是 <-     否\n");
		else
			printf("    是否跳过CG?        是     -> 否 <-\n");
		printf("\n\n\n\n\n\n\n\n");
		bound();
		key = input(1);
		if (key == 0)
			return false;
		else if (sta == 0 && key == 4)
			sta = 1;
		else if (sta == 1 && key == 3)
			sta = 0;
		else if (sta == 0 && key == 5)
			return true;
		else if (sta == 1 && key == 5)
			break;
	}
	//第一帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//第二帧
	system("cls");
	bound();
	printf("                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//第三帧
	system("cls");
	bound();
	printf("\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//第四帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(500);
	//第五帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n");
	printf("########################################");
	printf("\a#从前,有两个人类在大山中迷了路。       #");
	printf("#                                      #");
	bound();
	Sleep(2000);
	//第六帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n");
	printf("########################################");
	printf("\a#女: “我饿了!”                       #");
	printf("#                                      #");
	bound();
	Sleep(2000);
	//第七帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n");
	printf("########################################");
	printf("\a#男: “我也饿了!”                     #");
	printf("#                                      #");
	bound();
	Sleep(2000);
	//第八帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(500);
	//第九帧
	system("cls");
	bound();
	printf("\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//第十帧
	system("cls");
	bound();
	printf("                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//十一帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//十二帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("           ■■■      ■■■\n");
	bound();
	Sleep(200);
	//十三帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("           ■■■      ■■■\n\n");
	bound();
	Sleep(200);
	//十四帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("           ■■■      ■■■\n\n\n");
	bound();
	Sleep(500);
	//十五帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                   %c\n", 3);
	printf("           ■■■      ■■■\n\n\n");
	bound();
	Sleep(200);
	//十六帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                    %c\n", 3);
	printf("           ■■■      ■■■\n\n\n");
	bound();
	Sleep(200);
	//十七帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                  %c\n", 3);
	printf("           ■■■      ■■■\n\n\n");
	bound();
	Sleep(200);
	//十八帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                    %c\n", 3);
	printf("           ■■■      ■■■\n\n\n");
	bound();
	Sleep(200);
	//十九帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("                   %c\n", 3);
	printf("           ■■■      ■■■\n\n");
	bound();
	Sleep(200);
	//二十帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                    %c\n", 3);
	printf("           ■■■      ■■■\n");
	bound();
	Sleep(200);
	//二十一帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                  %c\n", 3);
	bound();
	Sleep(200);
	//二十二帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//二十三帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//二十四帧
	system("cls");
	bound();
	printf("                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//二十五帧
	system("cls");
	bound();
	printf("\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(200);
	//二十六帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(500);
	//二十七帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n");
	printf("########################################");
	printf("\a#女: “蛇可以吃吗?”                   #");
	printf("#                                      #");
	bound();
	Sleep(2000);
	//二十八帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n");
	printf("########################################");
	printf("\a#男: “蛇可以吃的,而且我敢打赌,蛇很好吃#");
	printf("#的。                                  #");
	bound();
	Sleep(2000);
	//二十九帧
	system("cls");
	bound();
	printf("\n\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(500);
	//三十帧
	system("cls");
	bound();
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("\n                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(100);
	//三十一帧
	system("cls");
	bound();
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("                  %c  %c\n", 1, 2);
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	bound();
	Sleep(100);
	//三十二帧~四十四帧
	for (i = 3; i<15; i++)
	{
		system("cls");
		bound();
		for (j = 0; j<i; j++)
			printf("■■■■■■■■■■■■■■■■■■■■");
		for (j = 0; j<14 - i; j++)
			printf("\n");
		bound();
		Sleep(100);
	}
	//四十五帧~五十三帧
	for (i = 1; i<9; i++)
	{
		system("cls");
		bound();
		for (j = 0; j<i; j++)
			printf("\n");
		for (j = 0; j<14 - i; j++)
			printf("■■■■■■■■■■■■■■■■■■■■");
		bound();

		Sleep(100);
	}
	//五十四帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	bound();
	Sleep(100);
	//五十五帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	bound();
	Sleep(100);
	//五十六帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	bound();
	Sleep(100);
	//五十七帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n\n");
	printf("■■■■■■■■■■■■■■■■■■■■");
	printf("■■■■■■■■■■■■■■■■■■■■");
	bound();
	Sleep(100);
	//五十八帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n\n");
	printf("            ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■");
	bound();
	Sleep(100);
	//五十九帧
	system("cls");
	bound();
	printf("\n\n\n\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n\n");
	printf("            ■\n");
	printf("          ! ■\n");
	bound();
	Sleep(500);
	//六十帧
	system("cls");
	bound();
	printf("\a#受伤的蛇: 不,不要……                 #");
	printf("#                                      #");
	printf("########################################");
	printf("\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n\n");
	printf("            ■\n");
	printf("          ! ■\n");
	bound();
	Sleep(2000);
	//六十一帧
	system("cls");
	bound();
	printf("\a#受伤的蛇: 可恶的人类,我要复仇……     #");
	printf("#                                      #");
	printf("########################################");
	printf("\n\n\n\n\n");
	printf("                  %c  %c\n", 1, 2);
	printf("                ■      ■\n");
	printf("                    ■    ■\n\n");
	printf("            ■\n");
	printf("          ! ■\n");
	bound();
	Sleep(4000);
	return true;
}
//游戏显示函数定义
void print()
{
	char i, j;
	gotoXY(0, 0);
	bound();
	printf("           可 是 的 贪 吃 蛇\n");
	bound();
	printf(" ###################### ############### ");
	for (i = 0; i<10; i++)
	{
		printf(" #");
		for (j = 0; j<10; j++)
			if (table[i][j] == 0)
				printf("  ");
			else if (table[i][j] == 4)
				printf("%c ", 3);
			else
				printf("■");
			switch (i)
			{
			case 1: printf("# #  分数:      # "); break;
			case 2: printf("# #     %6u  # ", score); break;
			case 4: printf("# ############### "); break;
			case 6: printf("# #  技能:      # "); break;
			case 8: flag<5 ? printf("# #     未充能  # ") : printf("# #   充能完毕  # "); break;
			default: printf("# #             # "); break;
			}
	}
	printf(" ###################### ############### ");
	bound();

}
//游戏操作函数定义
void game()
{
	char i;
	print();
	printf("          按下空格键以开始游戏");
	while (true)	//检验空格键进入游戏
	{
		i = input(1);
		if (i == 5)
			break;
		else if (i == 0)
			return;
	}
	//清空提示
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                    ");
	//游戏主循环开始
	while (true)
	{
		if (delay())
			break;
		switch (direction)	//分方向处理前进 1上 2下 3左 4右
		{
		case 1:
			//失败情况判定
			if (snake[lenth][0] - 1<0 || table[snake[lenth][0] - 1][snake[lenth][1]] == 2)
			{
				gameover();
				return;
			}
			//食用心脏判断
			else if (table[snake[lenth][0] - 1][snake[lenth][1]] == 4)
			{
				table[snake[lenth][0] - 1][snake[lenth][1]] = 2;
				snake[lenth + 1][0] = snake[lenth][0] - 1;
				snake[lenth + 1][1] = snake[lenth][1];
				lenth++; flag++; heart(); score += hard * 100;
				printf("\a");
			}
			//普通情况前进
			else
			{
				table[snake[0][0]][snake[0][1]] = 0;
				table[snake[1][0]][snake[1][1]] = 1;
				table[snake[lenth][0] - 1][snake[lenth][1]] = 2;
				snake[lenth + 1][0] = snake[lenth][0] - 1;
				snake[lenth + 1][1] = snake[lenth][1];
				for (i = 0; i<lenth + 1; i++)
				{
					snake[i][0] = snake[i + 1][0];
					snake[i][1] = snake[i + 1][1];
				}
				snake[lenth + 1][0] = snake[lenth + 1][1] = 0;
			}
			break;
		case 2:
			if (snake[lenth][0] + 1>9 || table[snake[lenth][0] + 1][snake[lenth][1]] == 2)
			{
				gameover();
				return;
			}
			else if (table[snake[lenth][0] + 1][snake[lenth][1]] == 4)
			{
				table[snake[lenth][0] + 1][snake[lenth][1]] = 2;
				snake[lenth + 1][0] = snake[lenth][0] + 1;
				snake[lenth + 1][1] = snake[lenth][1];
				lenth++; flag++; heart(); score += hard * 100;
				printf("\a");
			}
			else
			{
				table[snake[0][0]][snake[0][1]] = 0;
				table[snake[1][0]][snake[1][1]] = 1;
				table[snake[lenth][0] + 1][snake[lenth][1]] = 2;
				snake[lenth + 1][0] = snake[lenth][0] + 1;
				snake[lenth + 1][1] = snake[lenth][1];
				for (i = 0; i<lenth + 1; i++)
				{
					snake[i][0] = snake[i + 1][0];
					snake[i][1] = snake[i + 1][1];
				}
				snake[lenth + 1][0] = snake[lenth + 1][1] = 0;
			}
			break;
		case 3:
			if (snake[lenth][1] - 1<0 || table[snake[lenth][0]][snake[lenth][1] - 1] == 2)
			{
				gameover();
				return;
			}
			else if (table[snake[lenth][0]][snake[lenth][1] - 1] == 4)
			{
				table[snake[lenth][0]][snake[lenth][1] - 1] = 2;
				snake[lenth + 1][0] = snake[lenth][0];
				snake[lenth + 1][1] = snake[lenth][1] - 1;
				lenth++; flag++; heart(); score += hard * 100;
				printf("\a");
			}
			else
			{
				table[snake[0][0]][snake[0][1]] = 0;
				table[snake[1][0]][snake[1][1]] = 1;
				table[snake[lenth][0]][snake[lenth][1] - 1] = 2;
				snake[lenth + 1][0] = snake[lenth][0];
				snake[lenth + 1][1] = snake[lenth][1] - 1;
				for (i = 0; i<lenth + 1; i++)
				{
					snake[i][0] = snake[i + 1][0];
					snake[i][1] = snake[i + 1][1];
				}
				snake[lenth + 1][0] = snake[lenth + 1][1] = 0;
			}
			break;
		case 4:
			if (snake[lenth][1] + 1>9 || table[snake[lenth][0]][snake[lenth][1] + 1] == 2)
			{
				gameover();
				return;
			}
			else if (table[snake[lenth][0]][snake[lenth][1] + 1] == 4)
			{
				table[snake[lenth][0]][snake[lenth][1] + 1] = 2;
				snake[lenth + 1][0] = snake[lenth][0];
				snake[lenth + 1][1] = snake[lenth][1] + 1;
				lenth++; flag++; heart(); score += hard * 100;
				printf("\a");
			}
			else
			{
				table[snake[0][0]][snake[0][1]] = 0;
				table[snake[1][0]][snake[1][1]] = 1;
				table[snake[lenth][0]][snake[lenth][1] + 1] = 2;
				snake[lenth + 1][0] = snake[lenth][0];
				snake[lenth + 1][1] = snake[lenth][1] + 1;
				for (i = 0; i<lenth + 1; i++)
				{
					snake[i][0] = snake[i + 1][0];
					snake[i][1] = snake[i + 1][1];
				}
				snake[lenth + 1][0] = snake[lenth + 1][1] = 0;
			}
			break;
		}
		print();
	}
}

//延迟检测函数声明
bool delay()
{
	char i, j, key, temp = direction;
	for (i = 0; i<(6 - hard) * 10; i++)
	{

		key = input(0);
		if (key != -1)
		{
			switch (key)		//游戏中按键处理 暂停菜单/改变方向/发放技能
			{
			case 0: if (back()) return true;
					else
					{
						print();
						printf("          按下空格键以继续游戏");
						while (input(1) != 5);
					}
					//清空提示
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                    ");
					break;
			case 1: if (direction != 2) temp = 1; break;
			case 2: if (direction != 1) temp = 2; break;
			case 3: if (direction != 4) temp = 3; break;
			case 4: if (direction != 3) temp = 4; break;
			case 5:
			{
				if (flag >= 5)
				{
					table[snake[0][0]][snake[0][1]] = 0;
					table[snake[1][0]][snake[1][1]] = 1;
					for (j = 0; j<lenth; j++)
					{
						snake[j][0] = snake[j + 1][0];
						snake[j][1] = snake[j + 1][1];
					}
					snake[lenth][0] = snake[lenth][1] = 0;
					flag = 0; lenth--;
					system("cls");
					bound();
					printf("\n\n              技 能 发 动\n\a");
					printf("\n\n\n");
					printf("       #########################\n");
					printf("       #在埃里尼斯的威名下起誓:#\n");
					printf("       #                       #\n");
					printf("       #       我要减肥!       #\n");
					printf("       #########################\n\n\n\n");
					bound();
					Sleep(1000);
					print();
				}
			}
			}
		}
		Sleep(10);
	}
	direction = temp;
	return false;

}
//暂停菜单函数定义
bool back()
{
	char sta = 0, key, choose[7][15] = { "继续游戏", "-> 继续游戏 <-", "游戏帮助", "-> 游戏帮助 <-", "返回菜单", "-> 返回菜单 <-", "游 戏 已 暂 停" };
	while (true)
	{
		system("cls");
		bound();
		if (sta == 0)
		{
			printf("\n\n            %s\n", choose[6]);
			printf("\n\n\n\n            %s\n", choose[1]);
			printf("\n               %s\n", choose[2]);
			printf("\n               %s\n\n\n", choose[4]);
		}
		if (sta == 1)
		{
			printf("\n\n            %s\n", choose[6]);
			printf("\n\n\n\n               %s\n", choose[0]);
			printf("\n            %s\n", choose[3]);
			printf("\n               %s\n\n\n", choose[4]);
		}
		if (sta == 2)
		{
			printf("\n\n            %s\n", choose[6]);
			printf("\n\n\n\n               %s\n", choose[0]);
			printf("\n               %s\n", choose[2]);
			printf("\n            %s\n\n\n", choose[5]);
		}
		bound();
		key = input(1);
		if (key == 0)					//按键检测与操作
			return false;
		else if (sta == 0 && key == 5)
			return false;
		else if (sta == 0 && key == 2)
			sta = 1;
		else if (sta == 1 && key == 5)
			help();
		else if (sta == 1 && key == 1)
			sta = 0;
		else if (sta == 1 && key == 2)
			sta = 2;
		else if (sta == 2 && key == 5)
			return true;
		else if (sta == 2 && key == 1)
			sta = 1;
	}
}
//心脏产生函数定义
void heart()
{
	char i, j;
	while (true)
	{
		i = abs(rand()) % 10;
		j = abs(rand()) % 10;
		if (table[i][j] == 0)
		{
			table[i][j] = 4;
			break;
		}
	}
}
//游戏结束函数定义
void gameover()
{
	Sleep(200);
	system("cls");
	bound();
	printf("           可 是 的 贪 吃 蛇\n");
	bound();
	printf("\n\n");
	printf("               Game Over!\n");
	printf("\n\n\n\n");
	printf("               长度: %4d\n\n", lenth + 1);
	printf("              分数: %6d\n", score);
	printf("\n\n");
	bound();
	system("pause");
}

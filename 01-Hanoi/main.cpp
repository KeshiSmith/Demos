///////////////////////////////////////////////////
//本游戏于14年圣诞节完成，是我的第一个小游戏，
//受单片机编程的影响，萌发刷屏游戏的想法。
//本版本通过优化减少了游戏闪烁，
//最初版本通过VC6.0编译，
//此版本通过VS2013编译。

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//宏定义常用关键字
#define uchar unsigned char
#define uint unsigned int
//函数定义
void gotoXY(int x, int y);//光标移动函数声明
void bound();     //分界线函数声明
char input();     //按键输入函数声明
void GUI();     //用户界面函数声明
void help();     //游戏说明函数声明
bool opt();     //难度选择函数声明
void game();     //游戏操作函数声明
void print();     //游戏显示函数声明
void process();     //状态处理函数声明
void win();     //胜利结局函数声明
//全局变量声明
char hard, sta = 0, tower[3][11] = { 0 };			//hard(难度系数变量)   sta(状态变量)   tower(游戏数据变量)
//主函数
int main()
{
	char i, j;
	system("title 可是的汉诺塔");               //调整窗口标题
	system("color f3");                         //调整窗口颜色为白背景黑字
	system("mode con: cols=94 lines=18");      //调整窗口大小到最佳	
	while (true)
	{
		GUI();
		if (opt())
		{
			while (true)
			{
				//程序初始化操作
				for (i = 0; i<3; i++)
					for (j = 0; j<10; j++)
						tower[i][j] = 0;
				tower[0][10] = -1;
				tower[1][10] = 0;
				tower[2][10] = 0;
				sta = 0;
				//游戏开始
				game();
				if (sta == -2)     //返回主菜单判断
					break;
				if (sta != -1 && sta != -2)     //复位状态和胜利状态判断
				{
					win();
					break;
				}
			}
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
	printf("----------------------------------------------------------------------------------------------");
}
//按键输入函数定义
char input()					//↑返回值为1     ↓返回值为2     ←返回值为3     →返回值为4
{								//SPACE/ENTER返回值为0     ESC返回值为5     其他返回值-1
	uchar key1, key2;
	key1 = _getch();
	if (key1 == 27)
		return 5;
	if (key1 == 32 || key1 == 13)
		return 0;
	if (key1 == 224)
		key2 = _getch();
	switch (key2)
	{
	case 72: return 1;
	case 80: return 2;
	case 75: return 3;
	case 77: return 4;
	}
	return  -1;
}
//用户界面函数定义
void GUI()
{
	char sta = 0, key, choose[7][20] = { "开始游戏", "-> 开始游戏 <-", "游戏说明", "-> 游戏说明 <-", "结束游戏", "-> 结束游戏 <-", "可 是 的 汉 诺 塔" };
	while (true)
	{
		system("cls");
		bound();
		if (sta == 0)					//用户界面显示
		{
			printf("\n\n                                       %s\n", choose[6]);
			printf("\n\n\n\n                                         %s\n", choose[1]);
			printf("\n                                            %s\n", choose[2]);
			printf("\n                                            %s\n\n\n", choose[4]);
		}
		if (sta == 1)
		{
			printf("\n\n                                       %s\n", choose[6]);
			printf("\n\n\n\n                                            %s\n", choose[0]);
			printf("\n                                         %s\n", choose[3]);
			printf("\n                                            %s\n\n\n", choose[4]);
		}
		if (sta == 2)
		{
			printf("\n\n                                       %s\n", choose[6]);
			printf("\n\n\n\n                                            %s\n", choose[0]);
			printf("\n                                            %s\n", choose[2]);
			printf("\n                                         %s\n\n\n", choose[5]);
		}
		bound();
		key = input();
		if (key == 5)					//按键检测与操作
			exit(0);
		else if (sta == 0 && key == 0)
			break;
		else if (sta == 0 && key == 2)
			sta = 1;
		else if (sta == 1 && key == 0)
			help();
		else if (sta == 1 && key == 1)
			sta = 0;
		else if (sta == 1 && key == 2)
			sta = 2;
		else if (sta == 2 && key == 0)
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
	printf("                                       可 是 的 汉 诺 塔\n");
	bound();
	printf("\n             游戏说明:将最左塔座的方块借助中间的塔座全部右移到最塔座上。\n\n");
	printf("             游戏要求:一次只能取一块方块,任意大小的方块上只能放置比它更小的方块。\n");
	printf("\n\n\n\n\n");
	printf("            ↑      取方块           ↓     放置方块         SPACE     确定/重置\n");
	printf("            ←     光标左移          →     光标右移          ESC      返回/退出\n\n");
	bound();
	system("pause");
}
//难度选择函数定义
bool opt()
{
	uchar key;
	while (true)
	{
		system("cls");
		bound();
		puts("\n\n\n\n\n\n                                    请输入你想要的难度(1~7):\n\n\n\n\n\n\n");
		bound();
		key = _getch();
		if (key == 27)					//检测是否返回UI界面
			return false;
		hard = key - 48;
		if (hard>0 && hard<8)
			return true;
	}
}
//游戏操作函数定义
void game()
{
	for (char i = 0; i<hard; i++)	//游戏初始化
		tower[0][i] = hard - i;
	while (true)
	{
		print();
		process();
		if (sta == -1 || sta == -2)				//检测是否为复位状态或返回状态
			break;
		if (tower[2][hard - 1] == 1)				//检测是否胜利
		{
			print();
			system("pause");
			break;
		}
	}
}
//游戏显示函数定义
void print()
{
	gotoXY(0, 0);
	char i, j;
	bound();
	puts("                                       可 是 的 汉 诺 塔");
	bound();
	if (tower[0][10] == -1)				//打印光标
		printf("               ↓                                                                            ");
	else if (tower[1][10] == -1)
		printf("                                              ↓                                             ");
	else if (tower[2][10] == -1)
		printf("                                                                             ↓              ");
	else if (tower[0][10] != 0)
	{
		for (i = 0; i<15 - tower[0][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[0][10] + 1; i++)
			printf("■");
		for (i = 0; i<76 - 2 * tower[0][10]; i++)
			printf(" ");
	}
	else if (tower[1][10] != 0)
	{
		for (i = 0; i<46 - tower[1][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[1][10] + 1; i++)
			printf("■");
		for (i = 0; i<45 - 2 * tower[1][10]; i++)
			printf(" ");
	}
	else
	{
		for (i = 0; i<77 - tower[2][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[2][10] + 1; i++)
			printf("■");
		for (i = 0; i<14 - 2 * tower[2][10]; i++)
			printf(" ");
	}
	printf("\n\n");
	for (i = 9; i >= 0; i--)					//打印游戏主体
	{
		if (tower[0][i] == 0)
			printf("               ||              ");
		else
		{
			for (j = 0; j<15 - tower[0][i] * 2; j++)
				printf(" ");
			for (j = 0; j<2 * tower[0][i] + 1; j++)
				printf("■");
			for (j = 0; j<14 - tower[0][i] * 2; j++)
				printf(" ");
		}
		if (tower[1][i] == 0)
			printf("               ||              ");
		else
		{
			for (j = 0; j<15 - tower[1][i] * 2; j++)
				printf(" ");
			for (j = 0; j<2 * tower[1][i] + 1; j++)
				printf("■");
			for (j = 0; j<14 - tower[1][i] * 2; j++)
				printf(" ");
		}
		if (tower[2][i] == 0)
			puts("               ||              ");
		else
		{
			for (j = 0; j<15 - tower[2][i] * 2; j++)
				printf(" ");
			for (j = 0; j<2 * tower[2][i] + 1; j++)
				printf("■");
			for (j = 0; j<15 - tower[2][i] * 2; j++)
				printf(" ");
		}
	}
	bound();
}
//状态处理函数定义
void process()
{
	char i, key;
	key = input();
	switch (key)				//游戏按键操作处理
	{
	case 0: sta = -1; break;				//复位状态返回
	case 1:
	{
		if (sta == 0)
			if (tower[0][10] == -1 && tower[0][0] != 0)
			{
			for (i = 0; tower[0][i]; i++);
			tower[0][10] = tower[0][i - 1];
			tower[0][i - 1] = 0;
			}
		if (sta == 1)
			if (tower[1][10] == -1 && tower[1][0] != 0)
			{
			for (i = 0; tower[1][i]; i++);
			tower[1][10] = tower[1][i - 1];
			tower[1][i - 1] = 0;
			}
		if (sta == 2)
			if (tower[2][10] == -1 && tower[2][0] != 0)
			{
			for (i = 0; tower[2][i]; i++);
			tower[2][10] = tower[2][i - 1];
			tower[2][i - 1] = 0;
			}
		break;
	}
	case 2:
	{
		if (sta == 0)
			if (tower[0][10] != -1)
			{
			for (i = 0; tower[0][i]; i++);
			if (tower[0][10]<tower[0][i - 1] || tower[0][0] == 0)
			{
				tower[0][i] = tower[0][10];
				tower[0][10] = -1;
			}

			}
		if (sta == 1)
			if (tower[1][10] != -1)
			{
			for (i = 0; tower[1][i]; i++);
			if (tower[1][10]<tower[1][i - 1] || tower[1][0] == 0)
			{
				tower[1][i] = tower[1][10];
				tower[1][10] = -1;
			}
			}
		if (sta == 2)
			if (tower[2][10] != -1)
			{
			for (i = 0; tower[2][i]; i++);
			if (tower[2][10]<tower[2][i - 1] || tower[2][0] == 0)
			{
				tower[2][i] = tower[2][10];
				tower[2][10] = -1;
			}
			}
		break;
	}
	case 3:
	{
		if (sta == 0)
		{
			tower[2][10] = tower[0][10];
			tower[0][10] = 0;
			sta = 2;
		}
		else if (sta == 1)
		{
			tower[0][10] = tower[1][10];
			tower[1][10] = 0;
			sta = 0;
		}
		else
		{
			tower[1][10] = tower[2][10];
			tower[2][10] = 0;
			sta = 1;
		}
		break;
	}
	case 4:
	{
		if (sta == 0)
		{
			tower[1][10] = tower[0][10];
			tower[0][10] = 0;
			sta = 1;
		}
		else if (sta == 1)
		{
			tower[2][10] = tower[1][10];
			tower[1][10] = 0;
			sta = 2;
		}
		else
		{
			tower[0][10] = tower[2][10];
			tower[2][10] = 0;
			sta = 0;
		}
		break;
	}
	case 5: sta = -2; break;				//返回状态返回
	}
}
//胜利结局函数定义
void win()					//打印胜利界面"WIN !"
{
	system("cls");
	bound();
	puts("\n\n\n\n                             ■  ■  ■  ■■■  ■      ■  ■");
	puts("                             ■  ■  ■    ■    ■■    ■  ■");
	puts("                             ■  ■  ■    ■    ■  ■  ■  ■");
	puts("                             ■  ■  ■    ■    ■    ■■");
	puts("                             ■■■■■  ■■■  ■      ■  ■\n\n\n\n\n");
	bound();
	system("pause");
}

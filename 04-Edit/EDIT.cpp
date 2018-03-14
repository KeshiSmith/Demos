#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<graphics.h>
//宏定义常用关键字
#define uchar unsigned char
#define uint unsigned int
//全局变量声明
char K_Filename[64];					//文件名变量
char K_Filepath[128];					//文件路径变量
char K_Curtime = 0;						//光标闪烁控制变量
char K_Filesta = 0, K_Menusta = 0;		//文件菜单状态变量
int K_Line, K_Col;						//行数列数变量
int K_Maxline, K_Hline, K_Hcol;			//最大下标字符数变量
int K_Bline, K_Bcol, K_Eline, K_Ecol;	//字符选中反白变量
int K_Value, K_Backcup;					//字符复制粘贴变量
int K_Tab = 4;							//Tab键缩进变量
FILE *fp = NULL;						//文件路径指针变量
MOUSEMSG K_Hit;							//鼠标消息结构体变量
typedef struct K_Record				//剪切板结构体变量
{
	char ch;
	struct K_Record *next;
}K_Record;
typedef struct C_Node					//列结点结构体变量
{
	char ch;
	struct C_Node *next;
}C_Node;
typedef struct L_Node					//行结点结构体变量
{
	C_Node *next;
	struct L_Node *next1;
}L_Node;
L_Node *Hhead = NULL;					//行单链表变量
K_Record *Rhead = NULL;					//剪切板数据变量
//函数声明
void K_Print();							//界面显示函数声明
void K_Menu();							//菜单图形函数声明
void K_Stabar();						//状态栏图形函数声明
void K_Border();						//边框图形函数声明
void K_Schemove();						//进度条操作函数声明
char K_Input();							//输入检测函数声明
void K_Process();						//输入处理函数声明
bool K_Mouse(int, int, int, int);		//鼠标检测函数声明
void K_Curmove(int);					//光标移动函数声明
void K_Curflash();						//光标闪烁函数声明
void K_New();							//新建文件函数声明
void K_Open();							//文件打开函数声明
void K_Save();							//文件保存函数声明
void K_Saveas();						//文件另存为函数声明
void K_Close();							//文件关闭函数声明
void K_Exit();							//程序退出函数声明
void K_Copy();							//选中复制函数声明
void K_Paste();							//选中粘贴函数声明
void K_Clear();							//选中清除函数声明
void K_Settings();						//程序设置函数声明
void K_Commands();						//命令帮助函数声明
void K_About();							//关于帮助函数声明
void K_View();							//文本显示函数声明
char K_Check(int, int);					//常规字符判断函数声明
int K_Judge(int);						//常规字符计数函数声明
void K_Del(int, int);					//删除文本函数声明
void K_Insert(int, int, char);			//字符插入函数声明
void K_Inverse();						//字体选中函数声明
void K_Notinverse();					//选中取消函数声明
//主函数
int main()
{
	K_New();							//链表初始化
	initgraph(640, 480);
	settextstyle(16, 8, "Fixedsys");	//设置字体样式
	K_Print();							//屏幕初始化
	while (true)
	{
		K_Process();
		Sleep(10);
	}
	closegraph();
	return 0;
}
//界面显示函数定义
void K_Print()
{
	BeginBatchDraw();			//批量绘制开始
	K_Border();
	K_View();
	K_Menu();
	K_Stabar();
	EndBatchDraw();			//批量绘制结束
}
//菜单图形函数定义
void K_Menu()
{
	char nametemp[128];
	BeginBatchDraw();			//批量绘制开始
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 640, 15);	//设置菜单栏背景
	switch (K_Filesta)
	{
	case 0:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		break;
	case 1:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		settextcolor(WHITE);
		outtextxy(24, 0, 'F');
		outtextxy(72, 0, 'E');
		outtextxy(120, 0, 'S');
		outtextxy(184, 0, 'V');
		outtextxy(232, 0, 'O');
		outtextxy(304, 0, 'H');
		switch (K_Menusta)
		{
		case 1:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(16, 0, " File ");
			settextcolor(WHITE);
			outtextxy(24, 0, 'F');
			break;
		case 2:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(64, 0, " Edit ");
			settextcolor(WHITE);
			outtextxy(72, 0, 'E');
			break;
		case 3:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(112, 0, " Search ");
			settextcolor(WHITE);
			outtextxy(120, 0, 'S');
			break;
		case 4:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(176, 0, " View ");
			settextcolor(WHITE);
			outtextxy(184, 0, 'V');
			break;
		case 5:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(224, 0, " Options ");
			settextcolor(WHITE);
			outtextxy(232, 0, 'O');
			break;
		case 6:
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(296, 0, " Help ");
			settextcolor(WHITE);
			outtextxy(304, 0, 'H');
			break;
		}
		break;
	case 2:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(16, 0, " File ");
		//FILE下拉菜单
		setfillcolor(BLACK);
		solidrectangle(16, 32, 168, 208);
		setfillcolor(LIGHTGRAY);
		solidrectangle(8, 16, 152, 192);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(11, 24, 148, 25);
		solidrectangle(11, 120, 148, 121);
		solidrectangle(11, 152, 148, 153);
		solidrectangle(11, 184, 148, 185);
		solidrectangle(11, 24, 12, 185);
		solidrectangle(148, 24, 149, 185);
		//下拉菜单选项		
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(24, 32, "New");
		outtextxy(24, 48, "Open...");
		outtextxy(24, 64, "Save");
		outtextxy(24, 80, "Save As...");
		outtextxy(24, 96, "Close...");
		outtextxy(24, 128, "Print...");
		outtextxy(24, 160, "Exit");
		settextcolor(WHITE);
		outtextxy(24, 32, 'N');
		outtextxy(24, 48, 'O');
		outtextxy(24, 64, 'S');
		outtextxy(64, 80, 'A');
		outtextxy(24, 96, 'C');
		outtextxy(24, 128, 'P');
		outtextxy(32, 160, 'x');
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(16, 32, 144, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 32, "New");
			settextcolor(WHITE);
			outtextxy(24, 32, 'N');
			break;
		case 2:
			solidrectangle(16, 48, 144, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 48, "Open...");
			settextcolor(WHITE);
			outtextxy(24, 48, 'O');
			break;
		case 3:
			solidrectangle(16, 64, 144, 79);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 64, "Save");
			settextcolor(WHITE);
			outtextxy(24, 64, 'S');
			break;
		case 4:
			solidrectangle(16, 80, 144, 95);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 80, "Save As...");
			settextcolor(WHITE);
			outtextxy(64, 80, 'A');
			break;
		case 5:
			solidrectangle(16, 96, 144, 111);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 96, "Close...");
			settextcolor(WHITE);
			outtextxy(24, 96, 'C');
			break;
		case 6:
			solidrectangle(16, 128, 144, 143);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 128, "Print...");
			settextcolor(WHITE);
			outtextxy(24, 128, 'P');
			break;
		case 7:
			solidrectangle(16, 160, 144, 175);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(24, 160, "Exit");
			settextcolor(WHITE);
			outtextxy(32, 160, 'x');
			break;
		}
		break;
	case 3:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(64, 0, " Edit ");
		//EDIT下拉菜单
		setfillcolor(BLACK);
		solidrectangle(64, 32, 228, 128);
		setfillcolor(LIGHTGRAY);
		solidrectangle(56, 16, 212, 112);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(59, 24, 209, 25);
		solidrectangle(59, 104, 209, 105);
		solidrectangle(59, 24, 60, 105);
		solidrectangle(208, 24, 209, 105);
		//下拉菜单选项
		settextcolor(DARKGRAY);
		setbkcolor(LIGHTGRAY);
		outtextxy(72, 32, "Cut");
		outtextxy(152, 32, "Ctrl+X");
		outtextxy(72, 48, "Copy");
		outtextxy(152, 48, "Ctrl+C");
		outtextxy(72, 64, "Paste");
		outtextxy(152, 64, "Ctrl+V");
		outtextxy(72, 80, "Clear");
		outtextxy(152, 80, "Del");
		if (K_Value != 0)
		{
			settextcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			outtextxy(72, 32, "Cut");
			outtextxy(152, 32, "Ctrl+X");
			outtextxy(72, 48, "Copy");
			outtextxy(152, 48, "Ctrl+C");
			outtextxy(72, 80, "Clear");
			outtextxy(152, 80, "Del");
			settextcolor(WHITE);
			outtextxy(88, 32, 't');
			outtextxy(72, 48, 'C');
			outtextxy(88, 80, 'e');
		}
		if (K_Backcup != 0)
		{
			settextcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			outtextxy(72, 64, "Paste");
			outtextxy(152, 64, "Ctrl+V");
			settextcolor(WHITE);
			outtextxy(72, 64, 'P');
		}
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(64, 32, 204, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(72, 32, "Cut");
			outtextxy(152, 32, "Ctrl+X");
			if (K_Value != 0)
			{
				settextcolor(WHITE);
				outtextxy(88, 32, 't');
			}
			break;
		case 2:
			solidrectangle(64, 48, 204, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(72, 48, "Copy");
			outtextxy(152, 48, "Ctrl+C");
			if (K_Value != 0)
			{
				settextcolor(WHITE);
				outtextxy(72, 48, 'C');
			}
			break;
		case 3:
			solidrectangle(64, 64, 204, 79);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(72, 64, "Paste");
			outtextxy(152, 64, "Ctrl+V");
			if (K_Backcup != 0)
			{
				settextcolor(WHITE);
				outtextxy(72, 64, 'P');
			}
			break;
		case 4:
			solidrectangle(64, 80, 204, 95);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(72, 80, "Clear");
			outtextxy(152, 80, "Del");
			if (K_Value != 0)
			{
				settextcolor(WHITE);
				outtextxy(88, 80, 'e');
			}
			break;
		}
		break;
	case 4:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(112, 0, " Search ");
		//SEARCH下拉菜单
		setfillcolor(BLACK);
		solidrectangle(112, 32, 328, 112);
		setfillcolor(LIGHTGRAY);
		solidrectangle(104, 16, 312, 96);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(107, 24, 309, 25);
		solidrectangle(107, 87, 309, 88);
		solidrectangle(107, 24, 108, 88);
		solidrectangle(308, 24, 309, 88);
		//下拉菜单选项
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(120, 32, "Find...");
		outtextxy(120, 48, "Repeat Last Find");
		outtextxy(280, 48, "F3");
		outtextxy(120, 64, "Replace...");
		settextcolor(WHITE);
		outtextxy(120, 32, 'F');
		outtextxy(176, 48, 'L');
		outtextxy(120, 64, 'R');
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(112, 32, 304, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(120, 32, "Find...");
			settextcolor(WHITE);
			outtextxy(120, 32, 'F');
			break;
		case 2:
			solidrectangle(112, 48, 304, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(120, 48, "Repeat Last Find");
			outtextxy(280, 48, "F3");
			settextcolor(WHITE);
			outtextxy(176, 48, 'L');
			break;
		case 3:
			solidrectangle(112, 64, 304, 79);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(120, 64, "Replace...");
			settextcolor(WHITE);
			outtextxy(120, 64, 'R');
			break;
		}
		break;
	case 5:
		strcpy_s(nametemp, K_Filename);	//文件名长度处理
		if (strlen(nametemp) > 10)
		{
			nametemp[10] = nametemp[11] = nametemp[12] = '.';
			nametemp[13] = 0;
		}
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(224, 0, " Options ");
		outtextxy(296, 0, " Help ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(176, 0, " View ");
		//VIEW下拉菜单
		setfillcolor(BLACK);
		solidrectangle(176, 32, 392, 144);
		setfillcolor(LIGHTGRAY);
		solidrectangle(168, 16, 376, 128);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(171, 24, 373, 25);
		solidrectangle(171, 88, 373, 89);
		solidrectangle(171, 119, 373, 120);
		solidrectangle(171, 24, 172, 120);
		solidrectangle(372, 24, 373, 120);
		//下拉菜单选项
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(184, 32, "Split Window");
		outtextxy(304, 32, "Ctrl+F6");
		outtextxy(184, 96, '1');
		outtextxy(200, 96, nametemp);
		outtextxy(320, 96, "Alt+1");
		settextcolor(DARKGRAY);
		outtextxy(184, 48, "Size Window");
		outtextxy(304, 48, "Ctrl+F8");
		outtextxy(184, 64, "Close Window");
		outtextxy(304, 64, "Ctrl+F4");
		settextcolor(WHITE);
		outtextxy(184, 32, 'S');
		outtextxy(184, 96, '1');
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(176, 32, 368, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(184, 32, "Split Window");
			outtextxy(304, 32, "Ctrl+F6");
			settextcolor(WHITE);
			outtextxy(184, 32, 'S');
			break;
		case 2:
			solidrectangle(176, 48, 368, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(184, 48, "Size Window");
			outtextxy(304, 48, "Ctrl+F8");
			break;
		case 3:
			solidrectangle(176, 64, 368, 79);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(184, 64, "Close Window");
			outtextxy(304, 64, "Ctrl+F4");
			break;
		case 4:
			solidrectangle(176, 96, 368, 111);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(184, 96, '1');
			outtextxy(200, 96, nametemp);
			outtextxy(320, 96, "Alt+1");
			settextcolor(WHITE);
			outtextxy(184, 96, '1');
			break;
		}
		break;
	case 6:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(296, 0, " Help ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(224, 0, " Options ");
		//OPTIONS下拉菜单
		setfillcolor(BLACK);
		solidrectangle(224, 32, 384, 96);
		setfillcolor(LIGHTGRAY);
		solidrectangle(216, 16, 368, 80);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(219, 24, 365, 25);
		solidrectangle(219, 71, 365, 72);
		solidrectangle(219, 24, 220, 72);
		solidrectangle(364, 24, 365, 72);
		//下拉菜单选项
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(232, 32, "Settings...");
		outtextxy(232, 48, "Colors...");
		settextcolor(WHITE);
		outtextxy(232, 32, 'S');
		outtextxy(232, 48, 'C');
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(224, 32, 360, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(232, 32, "Settings...");
			settextcolor(WHITE);
			outtextxy(232, 32, 'S');
			break;
		case 2:
			solidrectangle(224, 48, 360, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(232, 48, "Colors...");
			settextcolor(WHITE);
			outtextxy(232, 48, 'C');
			break;
		}
		break;
	case 7:
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(16, 0, " File ");
		outtextxy(64, 0, " Edit ");
		outtextxy(112, 0, " Search ");
		outtextxy(176, 0, " View ");
		outtextxy(224, 0, " Options ");
		settextcolor(LIGHTGRAY);
		setbkcolor(BLACK);
		outtextxy(296, 0, " Help ");
		//HELP下拉菜单
		setfillcolor(BLACK);
		solidrectangle(296, 32, 416, 96);
		setfillcolor(LIGHTGRAY);
		solidrectangle(288, 16, 400, 80);
		//下拉菜单边框
		setfillcolor(BLACK);
		solidrectangle(291, 24, 397, 25);
		solidrectangle(291, 71, 397, 72);
		solidrectangle(291, 24, 292, 72);
		solidrectangle(396, 24, 397, 72);
		//下拉菜单选项
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		outtextxy(304, 32, "Commands...");
		outtextxy(304, 48, "About...");
		settextcolor(WHITE);
		outtextxy(304, 32, 'C');
		outtextxy(304, 48, 'A');
		switch (K_Menusta)
		{
		case 1:
			solidrectangle(296, 32, 392, 47);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(304, 32, "Commands...");
			settextcolor(WHITE);
			outtextxy(304, 32, 'C');
			break;
		case 2:
			solidrectangle(296, 48, 392, 63);
			settextcolor(LIGHTGRAY);
			setbkcolor(BLACK);
			outtextxy(304, 48, "About...");
			settextcolor(WHITE);
			outtextxy(304, 48, 'A');
			break;
		}
	}
	EndBatchDraw();				//批量绘制结束
}
//状态栏图形函数定义
void K_Stabar()
{
	char temp[8];
	BeginBatchDraw();				//批量绘制开始
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	switch (K_Filesta)
	{
	case 0:
		setfillcolor(BLACK);
		solidrectangle(436, 464, 437, 480);
		outtextxy(8, 464, "F1 = Help");
		outtextxy(456, 464, "Line:");
		outtextxy(552, 464, "Col:");
		_itoa_s(K_Line, temp, 10);
		outtextxy(496, 464, temp);	//打印行数
		_itoa_s(K_Col, temp, 10);
		outtextxy(584, 464, temp);	//打印列数
		break;
	case 1:
		switch (K_Menusta)
		{
		case 1:
			outtextxy(8, 464, "Commands for manipulating files");
			break;
		case 2:
			outtextxy(8, 464, "Commands for editing files");
			break;
		case 3:
			outtextxy(8, 464, "Commands for searching and replacing text");
			break;
		case 4:
			outtextxy(8, 464, "List of currently-loaded files");
			break;
		case 5:
			outtextxy(8, 464, "Commands for setting editor options");
			break;
		case 6:
			outtextxy(8, 464, "Help on Edit");
			break;
		}
		break;
	case 2:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "Commands for manipulating files");
			break;
		case 1:
			outtextxy(8, 464, "Creates a new file");
			break;
		case 2:
			outtextxy(8, 464, "Loads an existing file form disk");
			break;
		case 3:
			outtextxy(8, 464, "Saves current file");
			break;
		case 4:
			outtextxy(8, 464, "Saves current file with new name");
			break;
		case 5:
			outtextxy(8, 464, "Closes current file");
			break;
		case 6:
			outtextxy(8, 464, "Prints currently loaded file to printer");
			break;
		case 7:
			outtextxy(8, 464, "Exits the editor");
			break;
		}
		break;
	case 3:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "Commands for editing files");
			break;
		case 1:
			outtextxy(8, 464, "Deletes selected text and copies it to buffer");
			break;
		case 2:
			outtextxy(8, 464, "Copies selected text to buffer");
			break;
		case 3:
			outtextxy(8, 464, "Inserts buffer contents at current location");
			break;
		case 4:
			outtextxy(8, 464, "Deletes selected text without copying it to buffer");
			break;
		}
		break;
	case 4:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "Commands for searching and replacing text");
			break;
		case 1:
			outtextxy(8, 464, "Finds specified text (UNREALIZED)");
			break;
		case 2:
			outtextxy(8, 464, "Finds next occurrence of text specified in previous search (UNREALIZED)");
			break;
		case 3:
			outtextxy(8, 464, "Finds and changes specified text (UNREALIZED)");
			break;
		}
		break;
	case 5:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "List of currently-loaded files");
			break;
		case 1:
			outtextxy(8, 464, "Opens a second edit window (UNREALIZED)");
			break;
		case 2:
			outtextxy(8, 464, "Resizes the edit windows (UNREALIZED)");
			break;
		case 3:
			outtextxy(8, 464, "Closes the second edit window (UNREALIZED)");
			break;
		default:
			outtextxy(8, 464, "Selects a file to view (UNREALIZED)");
			break;
		}
		break;
	case 6:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "Commands for setting editor options");
			break;
		case 1:
			outtextxy(8, 464, "Changes editor settings");
			break;
		case 2:
			outtextxy(8, 464, "Changes editor screen colors (UNREALIZED)");
			break;
		}
		break;
	case 7:
		switch (K_Menusta)
		{
		case 0:
			outtextxy(8, 464, "Help on Edit");
			break;
		case 1:
			outtextxy(8, 464, "Help on Edit commands (UNREALIZED)");
			break;
		case 2:
			outtextxy(8, 464, "About Edit");
			break;
		}
		break;
	}
	EndBatchDraw();					//批量绘制结束
}
//边框图形函数声明
void K_Border()
{
	double up, down;
	BeginBatchDraw();					//批量绘制开始
	setfillcolor(BLACK);				//设置背景
	solidrectangle(0, 16, 7, 463);
	solidrectangle(632, 16, 639, 463);
	solidrectangle(0, 16, 639, 31);
	setfillcolor(LIGHTGRAY);			//设置边框
	solidrectangle(3, 24, 4, 463);
	solidrectangle(3, 24, 636, 25);
	solidrectangle(635, 24, 636, 31);
	settextcolor(BLACK);
	//设置文件标题
	setbkcolor(LIGHTGRAY);
	solidrectangle(312 - strlen(K_Filename) * 4, 16, 328 + strlen(K_Filename) * 4, 31);
	outtextxy(320 - strlen(K_Filename) * 4, 16, K_Filename);
	//设置进度条
	settextcolor(LIGHTGRAY);
	setbkcolor(BLACK);
	outtextxy(629, 32, "↑");
	outtextxy(629, 448, "↓");
	//进度条设置
	if ((K_Maxline - K_Hline) > 25)
	{
		up = ((K_Hline - 1.0) / K_Maxline*400.0);
		down = (K_Maxline - K_Hline - 26.0) / K_Maxline*400.0;
	}
	else
	{
		up = ((K_Hline - 1.0) / (K_Hline + 26.0)*400.0);
		down = 0.0;
	}
	setfillstyle(BS_HATCHED, HS_FDIAGONAL);
	solidrectangle(632, 48, 639, 447);
	setfillstyle(BS_SOLID, HS_FDIAGONAL);
	solidrectangle(632, 48 + (int)up, 639, 447 - (int)down);
	EndBatchDraw();				//批量绘制结束
}
//进度条操作函数定义
void K_Schemove()
{
	int high = K_Hit.y;
	char key;
	double up, down;
	if ((K_Maxline - K_Hline) > 25)
	{
		up = ((K_Hline - 1.0) / K_Maxline*400.0);
		down = (K_Maxline - K_Hline - 26.0) / K_Maxline*400.0;
	}
	else
	{
		up = ((K_Hline - 1.0) / (K_Hline + 26.0)*400.0);
		down = 0.0;
	}
	if (!K_Mouse(632, 48 + (int)up, 639, 447 - (int)down))
		return;
	while (GetKeyState(VK_LBUTTON) < 0)
	{
		Sleep(10);
		key = K_Input();
		if (high != K_Hit.y)
		{
			if (high > K_Hit.y)
			{
				if (high - K_Hit.y <= up)
				{
					down += (high - K_Hit.y);
					up -= (high - K_Hit.y);
				}
				else
				{
					down += up;
					up = 0.0;
				}
			}
			else if (high < K_Hit.y)
			{
				if (K_Hit.y - high <= down)
				{
					up += (K_Hit.y - high);
					down -= (K_Hit.y - high);
				}
				else
				{
					up += down;
					down = 0.0;
				}
			}
			high = K_Hit.y;
			K_Hline = (int)(up / 400 * K_Maxline) + 1;
			K_Border();
			K_View();
		}
	}
	if (K_Line<K_Hline)
		K_Line = K_Hline;
	if (K_Line>K_Hline + 26)
		K_Line = K_Hline + 26;
	if (K_Col > K_Judge(K_Line) + 1)
		K_Col = K_Judge(K_Line) + 1;
}
//输入检测函数定义
char K_Input()
{
	uchar key1, key2;
	if (_kbhit())				//实时键盘输入检测
	{
		key1 = _getch();
		if (key1 == 224)			//特殊键检测
			key2 = _getch();
		else return key1;		//返回基本按键
		switch (key2)
		{
		case 72:
			return -1;			//返回上方向键
		case 80:
			return -2;			//返回下方向键
		case 75:
			return -3;			//返回左方向键
		case 77:
			return -4;			//返回右方向键
		case 141:
			return -12;			//返回CTRL+↑
		case 145:
			return -13;			//返回CTRL+↓
		case 115:
			return -14;			//返回CTRL+←
		case 116:
			return -15;			//返回CTRL+→
		case 83:
			return -11;			//返回DEL键
		}
	}
	else if (GetKeyState(VK_SHIFT) < 0)	//返回SHIFT键
		return -10;
	else if (GetKeyState(VK_CONTROL) < 0)	//返回CTRL键
		return -9;
	else if (MouseHit())
	{
		K_Hit = GetMouseMsg();
		if (K_Hit.uMsg == WM_LBUTTONUP)		//返回左键松开
			return -8;
		else if (K_Hit.uMsg == WM_MOUSEMOVE)	//返回鼠标移动
			return -7;
		else if (K_Hit.uMsg == WM_LBUTTONDOWN)	//返回左键点击
			return -6;
	}
	else if (GetKeyState(VK_MENU) < 0)
		return -5;							//返回ALT键
	return NULL;							//无输入时返回NULL
}
//输入处理函数定义
void K_Process()
{
	int key, temp;							//按键暂存变量
	key = K_Input();
	if (key != 0)
	{
		switch (key)
		{
		case -3:							//检验左方向键
			if (K_Filesta > 1)
			{
				K_Filesta = (K_Filesta + 3) % 6 + 2;
				K_Menusta = 1;
				K_Print();
			}
			break;
		case -4:							//检验右方向键
			if (K_Filesta > 1)
			{
				K_Filesta = (K_Filesta - 1) % 6 + 2;
				K_Menusta = 1;
				K_Print();
			}
			break;
		case -7:							//检验鼠标移动
			if (K_Hit.mkLButton != true)
				break;
		case -6:							//检验左键点击
			temp = K_Filesta;
			if (K_Mouse(16, 0, 63, 15))
				K_Filesta = 2;
			else if (K_Mouse(64, 0, 111, 15))
				K_Filesta = 3;
			else if (K_Mouse(111, 0, 175, 15))
				K_Filesta = 4;
			else if (K_Mouse(176, 0, 223, 15))
				K_Filesta = 5;
			else if (K_Mouse(224, 0, 295, 15))
				K_Filesta = 6;
			else if (K_Mouse(296, 0, 343, 15))
				K_Filesta = 7;
			else break;
			if (temp != K_Filesta)				//检测状态是否改变以减少闪烁
			{
				K_Menusta = K_Curtime = 0;
				K_Print();
			}
			break;
		case -8:							//检验左键松开
			if (K_Mouse(16, 0, 343, 15))
			{
				K_Menusta = 1;
				K_Print();
			}
			break;
		}
	}
	switch (K_Filesta)
	{
	case 0:
		if (GetKeyState(VK_F1) < 0)					//检验F1键状态
		{
			K_Commands();
			K_Print();
		}
		else if (key != 0 && key != -7 && key != -8)
		{
			if (key != -9 && key != -10)					//光标消隐
			{
				K_Curtime = 50;
				K_Curflash();
				K_Curtime = 0;
			}
			switch (key)
			{
			case -1:
			case -2:
			case -3:
			case -4:
				K_Notinverse();
				K_Curmove(key);
				break;
			case -5:								//检验ALT键
				K_Filesta = 1;
				K_Menusta = 0;
				K_Menu();
				K_Menusta = 1;
				while (GetKeyState(VK_MENU) < 0)
				{
					if (GetKeyState(70) < 0)			//检验F键状态	
						K_Filesta = 2;
					else if (GetKeyState(69) < 0)		//检验E键状态
						K_Filesta = 3;
					else if (GetKeyState(83) < 0)		//检验S键状态
						K_Filesta = 4;
					else if (GetKeyState(86) < 0)		//检验V键状态
						K_Filesta = 5;
					else if (GetKeyState(79) < 0)		//检验O键状态	
						K_Filesta = 6;
					else if (GetKeyState(72) < 0)		//检验H键状态
						K_Filesta = 7;
					if (K_Filesta != 1)
					{
						K_Menu();
						K_Stabar();
						while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
							Sleep(10);
						break;
					}
				}
				K_Print();
				break;
			case -6:								//检验左键按下
				K_Curtime = 0;
				key = K_Hit.y / 16 + K_Hline - 2;
				temp = K_Hit.x / 8 + K_Hcol - 1;
				if (K_Mouse(632, 32, 640, 48) && K_Hline > 1)
				{
					temp = 1;
					do{
						K_Hline--;
						if (K_Line > K_Hline + 26)
							K_Curmove(-1);
						K_Border();
						K_View();
						if (temp == 1)
						{
							Sleep(450);
							temp = 0;
						}
						Sleep(50);
					} while (GetKeyState(VK_LBUTTON) < 0 && K_Hline > 1);
				}
				else if (K_Mouse(632, 448, 640, 464) && (K_Hline + 26) < K_Maxline)
				{
					temp = 1;
					do{
						K_Hline++;
						if (K_Line < K_Hline)
							K_Curmove(-2);
						K_Border();
						K_View();
						if (temp == 1)
						{
							Sleep(450);
							temp = 0;
						}
						Sleep(50);
					} while (GetKeyState(VK_LBUTTON) < 0 && (K_Hline + 26) < K_Maxline);
				}
				else if (K_Mouse(632, 48, 639, 447))
				{
					K_Schemove();
				}
				else if (key >= K_Hline&&key <= K_Hline + 26 && temp >= K_Hcol&&temp <= K_Hcol + 77)
				{
					if (K_Check(key, temp) > 0)
					{
						K_Line = key;
						K_Col = temp;
					}
					else if (temp > 1 && key <= K_Maxline)
					{
						K_Line = key;
						K_Col = K_Judge(K_Line) + 1;
					}
					K_Inverse();
				}
				K_Stabar();
				break;
			case -10:								//检验SHIFT键
				if (GetKeyState(VK_SHIFT) < 0)
					K_Inverse();
				else
					K_Curflash();
				break;
			case -11:								//检验DEL键
				if (K_Value != 0)
					K_Clear();
				else
				{
					if (K_Check(K_Line, K_Col) != 13)
						K_Del(K_Line, K_Col);
					else
					{
						K_Curmove(-4);
						K_Del(K_Line, K_Col - 1);
					}
				}
				break;
			case -12:								//检验CTRL+↑
				K_Notinverse();
				if (K_Line > 1)
				{
					K_Line--;
					K_Col = 2;
					K_Curmove(-3);
				}
				break;
			case -13:								//检验CTRL+↓
				K_Notinverse();
				if (K_Line < K_Maxline)
				{
					K_Line++;
					K_Col = 2;
					K_Curmove(-3);
				}
				break;
			case -14:								//检验CTRL+←
				K_Notinverse();
				K_Col = 2;
				K_Curmove(-3);
				break;
			case -15:								//检验CTRL+→
				K_Notinverse();
				K_Col = K_Judge(K_Line);
				K_Curmove(-4);
				break;
			case 8:									//检验BACKSPACE键
				if (K_Value != 0)
					K_Clear();
				else
					K_Del(K_Line, K_Col - 1);
				break;
			case 9:									//检验TAB键
				for (temp = 0; temp < K_Tab; temp++)
					K_Insert(K_Line, K_Col, 32);
				break;
			case 24:								//文本剪切CTRL+X
				if (K_Value != 0)
				{
					K_Copy();
					K_Clear();
				}
				break;
			case -9:								//文本复制CTRL+C
				if (GetKeyState(67) < 0 && K_Value != 0)
					K_Copy();
				else
					K_Curflash();
				break;
			case 22:								//文本粘贴CTRL+V
				if (K_Backcup != 0)
				{
					if (K_Value != 0)
						K_Clear();
					K_Paste();
				}
				break;
			default:
				if ((key > 31 && key < 127) || key == 13)
					K_Insert(K_Line, K_Col, key);
				break;
			}
		}
		else
			K_Curflash();
		break;
	case 1:
		if (key != 0)
		{
			if (GetKeyState(70) < 0 || (K_Menusta == 1 && key == 13))		//检验F键状态
				K_Filesta = 2;
			else if (GetKeyState(69) < 0 || (K_Menusta == 2 && key == 13))	//检验E键状态
				K_Filesta = 3;
			else if (GetKeyState(83) < 0 || (K_Menusta == 3 && key == 13))	//检验S键状态	
				K_Filesta = 4;
			else if (GetKeyState(86) < 0 || (K_Menusta == 4 && key == 13))	//检验V键状态
				K_Filesta = 5;
			else if (GetKeyState(79) < 0 || (K_Menusta == 5 && key == 13))	//检验O键状态
				K_Filesta = 6;
			else if (GetKeyState(72) < 0 || (K_Menusta == 6 && key == 13))	//检验H键状态
				K_Filesta = 7;
			else switch (key)
			{
			case -3:							//检验左方向键
				K_Menusta = (K_Menusta + 4) % 6 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -4:							//检验右方向键
				K_Menusta = K_Menusta % 6 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//检验ALT键
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 1)
			{
				K_Menusta = 1;
				K_Menu();
				K_Stabar();
			}
		}
		break;
	case 2:
		if (key != 0)
		{
			if (GetKeyState(78) < 0 || (K_Menusta == 1 && key == 13))		//检验N键状态
			{
				K_Filesta = 0;
				K_New();
			}
			else if (GetKeyState(79) < 0 || (K_Menusta == 2 && key == 13))	//检验O键状态
				K_Open();
			else if (GetKeyState(83) < 0 || (K_Menusta == 3 && key == 13))	//检验S键状态
				K_Save();
			else if (GetKeyState(65) < 0 || (K_Menusta == 4 && key == 13))	//检验A键状态
				K_Saveas();
			else if (GetKeyState(67) < 0 || (K_Menusta == 5 && key == 13))	//检验C键状态
				K_Close();
			else if (GetKeyState(88) < 0 || (K_Menusta == 7 && key == 13))	//检验X键状态
				K_Exit();
			else switch (key)
			{
			case -1:							//检验上方向键
				K_Menusta = (K_Menusta + 5) % 7 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 7 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验左键按下
				temp = K_Menusta;
				if (K_Mouse(16, 32, 144, 47))
					K_Menusta = 1;
				else if (K_Mouse(16, 48, 144, 63))
					K_Menusta = 2;
				else if (K_Mouse(16, 64, 144, 79))
					K_Menusta = 3;
				else if (K_Mouse(16, 80, 144, 95))
					K_Menusta = 4;
				else if (K_Mouse(16, 96, 144, 111))
					K_Menusta = 5;
				else if (K_Mouse(16, 128, 144, 143))
					K_Menusta = 6;
				else if (K_Mouse(16, 160, 144, 175))
					K_Menusta = 7;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu();
					K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 1:
					if (K_Mouse(16, 32, 144, 47))
					{
						K_Filesta = 0;
						K_New();
					}
					break;
				case 2:
					K_Open();
					break;
				case 3:
					K_Save();
					break;
				case 4:
					K_Saveas();
					break;
				case 5:
					K_Close();
					break;
				case 7:
					K_Exit();
					break;
				case 0:
					K_Filesta = 0;
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 2)
			{
				K_Menusta = 1;
				K_Print();
			}
		}
		break;
	case 3:
		if (key != 0)
		{
			if ((GetKeyState(84) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)		//检验T键状态
			{
				K_Filesta = 0;
				K_Copy();
				K_Clear();
			}
			else if ((GetKeyState(67) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)	//检验C键状态
			{
				K_Filesta = 0;
				K_Copy();
			}
			else if ((GetKeyState(80) < 0 || (K_Menusta == 1 && key == 13)) && K_Backcup != 0)	//检验P键状态
			{
				K_Filesta = 0;
				K_Paste();
			}
			if ((GetKeyState(69) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)		//检验E键状态
			{
				K_Filesta = 0;
				K_Clear();
			}
			else switch (key)
			{
			case -1:							//检验上方向键
				K_Menusta = (K_Menusta + 2) % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				K_Menusta = 2;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验鼠标左键
				temp = K_Menusta;
				if (K_Mouse(64, 32, 204, 47))
					K_Menusta = 1;
				else if (K_Mouse(64, 48, 204, 63))
					K_Menusta = 2;
				else if (K_Mouse(64, 64, 204, 79))
					K_Menusta = 3;
				else if (K_Mouse(64, 80, 204, 95))
					K_Menusta = 4;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu();
					K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 1:
					if (K_Mouse(64, 32, 204, 47) && K_Value != 0)
					{
						K_Filesta = 0;
						K_Copy();
						K_Clear();
					}
					break;
				case 2:
					if (K_Value != 0)
					{
						K_Filesta = 0;
						K_Copy();
					}
					break;
				case 3:
					if (K_Backcup != 0)
					{
						K_Filesta = 0;
						K_Paste();
					}
					break;
				case 4:
					if (K_Value != 0)
					{
						K_Filesta = 0;
						K_Clear();
					}
					break;
				case 0:
					K_Filesta = 0;
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 3)
				K_Print();
		}
		break;
	case 4:
		if (key != 0)
		{
			switch (key)
			{
			case -1:							//检验上方向键
				K_Menusta = (K_Menusta + 1) % 3 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 3 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				K_Menusta = 3;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验鼠标左键
				temp = K_Menusta;
				if (K_Mouse(112, 32, 304, 47))
					K_Menusta = 1;
				else if (K_Mouse(112, 48, 304, 63))
					K_Menusta = 2;
				else if (K_Mouse(112, 64, 304, 79))
					K_Menusta = 3;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu();
					K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 4)
				K_Print();
		}
		break;
	case 5:
		if (key != 0)
		{
			switch (key)
			{
			case -1:							//检验上方向键
				K_Menusta = (K_Menusta + 2) % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				K_Menusta = 4;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验鼠标左键
				temp = K_Menusta;
				if (K_Mouse(176, 32, 368, 47))
					K_Menusta = 1;
				else if (K_Mouse(176, 48, 368, 63))
					K_Menusta = 2;
				else if (K_Mouse(176, 64, 368, 79))
					K_Menusta = 3;
				else if (K_Mouse(176, 96, 368, 111))
					K_Menusta = 4;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu();
					K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 5)
				K_Print();
		}
		break;
	case 6:
		if (key != 0)
		{
			if (GetKeyState(83) < 0 || (K_Menusta == 1 && key == 13))		//检验S键状态
			{
				K_Settings();
			}
			else switch (key)
			{
			case -1:							//检验上方向键
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 2 + 1;
				K_Menu(); K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				K_Menusta = 5;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验鼠标左键
				temp = K_Menusta;
				if (K_Mouse(224, 32, 360, 47))
					K_Menusta = 1;
				else if (K_Mouse(224, 48, 360, 63))
					K_Menusta = 2;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu(); K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 1:
					if (K_Mouse(224, 32, 360, 47))
						K_Settings();
					break;
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 6)
				K_Print();
		}
		break;
	case 7:
		if (key != 0)
		{
			if (GetKeyState(67) < 0 || (K_Menusta == 1 && key == 13))		//检验C键状态
				K_Commands();
			else if (GetKeyState(65) < 0 || (K_Menusta == 2 && key == 13))	//检验A键状态
				K_About();
			else switch (key)
			{
			case -1:							//检验上方向键
			case -2:							//检验下方向键
				K_Menusta = K_Menusta % 2 + 1;
				K_Menu(); K_Stabar();
				break;
			case -5:							//检验ALT键
				K_Filesta = 1;
				K_Menusta = 6;
				while (GetKeyState(VK_MENU) < 0)	//检验按键是否松开
					Sleep(10);
				break;
			case -7:							//检验鼠标移动
				if (K_Hit.mkLButton != true) break;
			case -6:							//检验鼠标左键
				temp = K_Menusta;
				if (K_Mouse(296, 32, 392, 47))
					K_Menusta = 1;
				else if (K_Mouse(296, 48, 392, 63))
					K_Menusta = 2;
				else if (!K_Mouse(16, 0, 343, 15))
					K_Menusta = 0;
				if (temp != K_Menusta)
				{
					K_Menu();
					K_Stabar();
				}
				break;
			case -8:							//检验左键松开
				switch (K_Menusta)
				{
				case 1:
					if (K_Mouse(296, 32, 392, 47))
						K_Commands();
					break;
				case 2:
					K_About();
					break;
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//检验ESC键
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 7)
				K_Print();
		}
		break;
	}
	fflush(stdin);								//清除键盘缓存区
	FlushMouseMsgBuffer();					//清除鼠标缓存区
}
//光标移动函数定义
void K_Curmove(int key)
{
	int temp1 = K_Hline, temp2 = K_Hcol;
	K_Curtime = 0;
	switch (key)
	{
	case -1:
		if (K_Line > 1)						//检验是否不是第一行
		{
			if (K_Check(--K_Line, K_Col) < 0)
				K_Col = K_Judge(K_Line) + 1;
		}
		break;
	case -2:
		if (K_Line < K_Maxline)
		{
			if (K_Check(++K_Line, K_Col) < 0)
				K_Col = K_Judge(K_Line) + 1;
		}
		break;
	case -3:
		if ((K_Line > 1 || K_Col > 1) && (--K_Col < 1))//检验是否不是第一个字符
		{
			K_Line--;
			K_Col = K_Judge(K_Line) + 1;
		}
		break;
	case -4:
		if (K_Check(K_Line, ++K_Col) < 0)	//检验光标
		{
			if (K_Line < K_Maxline)
			{
				K_Line++;
				K_Col = 1;
			}
			else
				K_Col--;
		}
		break;
	}
	if (K_Line - K_Hline>26)					//判断并更改原点
		K_Hline = K_Line - 26;
	else if (K_Line < K_Hline)
		K_Hline = K_Line;
	if (K_Col - K_Hcol>77)
		K_Hcol = K_Col - 77;
	else if (K_Col < K_Hcol)
		K_Hcol = K_Col;
	if (temp1 != K_Hline)
	{
		K_Border();
		K_View();
	}
	if (temp2 != K_Hcol)
		K_View();
	K_Stabar();
}
//光标闪烁函数声明
void K_Curflash()
{
	BeginBatchDraw();				//批量绘制开始
	setfillcolor(LIGHTGRAY);
	settextcolor(LIGHTGRAY);
	setbkcolor(BLUE);
	//判断是否反白
	if (K_Value>0 && ((K_Line > K_Bline || (K_Line == K_Bline&&K_Col >= K_Bcol)) && \
		(K_Line < K_Eline || (K_Line == K_Eline&&K_Col<K_Ecol)) || (K_Line>K_Eline || (K_Line == K_Eline&&K_Col >= K_Ecol)) && \
		(K_Line < K_Bline || (K_Line == K_Bline&&K_Col < K_Bcol))))
	{
		setfillcolor(BLACK);
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
	}
	if (K_Curtime == 0)				//光标显示
	{
		solidrectangle((K_Col - K_Hcol + 1) * 8, 28 + (K_Line - K_Hline + 1) * 16, (K_Col - K_Hcol + 1) * 8 + 8 - 1, 31 + (K_Line - K_Hline + 1) * 16);
		K_Curtime++;
	}
	else if (K_Curtime == 50)			//光标消隐
	{
		if (K_Check(K_Line, K_Col) != 13)
			outtextxy((K_Col - K_Hcol + 1) * 8, 16 + (K_Line - K_Hline + 1) * 16, K_Check(K_Line, K_Col));
		else
			outtextxy((K_Col - K_Hcol + 1) * 8, 16 + (K_Line - K_Hline + 1) * 16, ' ');
		K_Curtime++;
	}
	else
		K_Curtime = (K_Curtime + 1) % 100;
	EndBatchDraw();					//批量绘制结束
}
//鼠标检测函数定义
bool K_Mouse(int X_L, int Y_U, int X_R, int Y_D)
{
	if (K_Hit.x >= X_L&&K_Hit.x <= X_R&&K_Hit.y >= Y_U&&K_Hit.y <= Y_D)
		return true;		//返回TRUE
	else
		return false;		//返回FALSE
}
//新建文件函数定义
void K_New()
{
	C_Node *p, *p1;				//列单链表变量
	L_Node *q, *q1;				//行单链表变量
	K_Record *r1, *r2;			//剪切板链表变量
	if (Hhead != NULL)
	{
		q = q1 = Hhead;
		while (q != NULL)
		{
			p = p1 = q->next;
			while (p != NULL)
			{
				p = p->next;
				free(p1);
				p1 = p;
			}
			q = q->next1;
			free(q1);
			q1 = q;
		}
		Hhead = NULL;
	}
	if (Rhead != NULL)				//释放剪切板链表
	{
		r1 = r2 = Rhead;
		while (r1 != NULL)
		{
			r1 = r1->next;
			free(r2);
			r2 = r1;
		}
		Rhead = NULL;
	}
	Hhead = (L_Node *)malloc(sizeof(L_Node));			//为行单链表分配内存空间
	q = Hhead;
	Hhead->next1 = NULL;
	p = q->next = (C_Node *)malloc(sizeof(C_Node));		//为列单链表分配内存空间
	p->ch = 13;
	p->next = NULL;
	Rhead = (K_Record *)malloc(sizeof(K_Record));		//为剪切板链表分配内存空间
	Rhead->ch = 0;
	Rhead->next = NULL;
	K_Line = K_Col = K_Hline = K_Hcol = K_Maxline = 1;
	K_Bline = K_Bcol = K_Eline = K_Ecol = 1;
	K_Value = K_Backcup = 0;							//全局变量初始化
	strcpy_s(K_Filename, "UNTITLED1");
	strcpy_s(K_Filepath, "UNTITLED1");
}
//文件打开函数定义
void K_Open()
{
	int i, num = 1, headch = 1, sta = 0, temp = 1, time = 0;
	char key, ch, temppath[128] = "\0";
	C_Node *p, *p1;
	L_Node *q;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(88, 176, 576, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(80, 160, 560, 288);
	setfillcolor(WHITE);
	solidrectangle(80, 160, 560, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(284, 160, "Open File");
	setbkcolor(LIGHTGRAY);
	outtextxy(112, 208, "File Path: [......................................]");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	while (true)
	{
		key = K_Input();
		fflush(stdin);								//清除键盘缓存区
		FlushMouseMsgBuffer();						//清除鼠标缓存区
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//检验左键状态
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(208, 256, 280, 280))
					sta = 1;
				else if (K_Hit.mkLButton == true && K_Mouse(360, 256, 432, 280))
					sta = 2;
				else
					sta = 0;
				break;
			case -8:
				if (K_Mouse(360, 256, 432, 280))
					return;
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//检验ENTER键
				if (num == 1)
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(0, 464, 640, 480);
					settextcolor(RED);
					setbkcolor(LIGHTGRAY);
					outtextxy(8, 464, "The path can't be null!");
					Sleep(1000);
					settextcolor(BLACK);
					solidrectangle(0, 464, 640, 480);
					outtextxy(8, 464, "Enter=OK  Cancel=ESC");
					break;							//路径错误跳出
				}
				if (fopen_s(&fp, temppath, "r"))
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(0, 464, 640, 480);
					settextcolor(RED);
					setbkcolor(LIGHTGRAY);
					outtextxy(8, 464, "The file is not exist.");
					Sleep(1000);
					settextcolor(BLACK);
					solidrectangle(0, 464, 640, 480);
					outtextxy(8, 464, "Enter=OK  Cancel=ESC");
					break;							//文件不存在跳出
				}
				K_New();
				strcpy_s(K_Filepath, temppath);
				for (i = num = 0; temppath[i] != '\0'; i++)
				{
					if (temppath[i] == '\\')
						num = i;
				}
				if (num != 0)
					strcpy_s(K_Filename, temppath + num + 1);
				else
					strcpy_s(K_Filename, temppath + num);
				q = Hhead;
				p = p1 = q->next;
				i = 1;								//行起始标志
				while ((ch = fgetc(fp)) != EOF)
				{
					if (i == 1)
					{
						i = 0;
						p1 = q->next = (C_Node *)malloc(sizeof(C_Node));
					}
					else
						p1 = p1->next = (C_Node *)malloc(sizeof(C_Node));
					if ((p1->ch = ch) == 10)				//换行符换行
					{
						i = 1;
						p1->ch = 13;
						K_Maxline++;
						q = q->next1 = (L_Node *)malloc(sizeof(L_Node));
						p1->next = NULL;
						p1 = q->next;
					}
					else if (p1->ch == 9)				//TAB转化为空格
					{
						p1->ch = 32;
						for (num = 0; num < K_Tab - 1; num++)
						{
							p1 = p1->next = (C_Node *)malloc(sizeof(C_Node));
							p1->ch = 32;
						}
					}
				}
				if (i == 1)							//链表连接最后的字符13
					q->next = p;
				else
					p1->next = p;
				q->next1 = NULL;
				fclose(fp);  fp = NULL;
				return;
			case 8:
				time = 0;
				if (num > 1)
				{
					temppath[num - 2] = '\0';
					num--;
				}
				if (num < headch + 38 && headch>1)
				{
					headch--;
					for (i = headch; i < headch + 37; i++)
						outtextxy(208 + (i - headch) * 8, 208, temppath[i - 1]);
					outtextxy(208 + (num - headch) * 8, 208, '.');
				}
				else
				{
					outtextxy(208 + (num - headch) * 8, 208, '.');
					outtextxy(208 + (num - headch + 1) * 8, 208, '.');
				}
				break;
			case 27:								//检验ESC键
				return;
			default:
				time = 0;
				if (key>31 && key < 127 && num < 128)
				{
					temppath[num - 1] = key;
					temppath[num] = '\0';
					settextcolor(BLACK);
					setbkcolor(LIGHTGRAY);
					outtextxy(208 + (num - headch) * 8, 208, temppath[num - 1]);
					num++;
					if (num > headch + 37)
					{
						headch++;
						for (i = headch; i < headch + 37; i++)
							outtextxy(208 + (i - headch) * 8, 208, temppath[i - 1]);
						outtextxy(208 + (num - headch) * 8, 208, '.');
					}
				}
				break;
			}
			if (temp != sta)
			{
				switch (sta)
				{
				case 0:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					solidrectangle(360, 256, 432, 280);
					setfillcolor(BLACK);
					solidrectangle(216, 264, 280, 280);
					solidrectangle(368, 264, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(208, 256, ">  OK  <");
					outtextxy(360, 256, ">Cancel<");
					break;
				case 1:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(216, 256, "   OK   ");
					break;
				case 2:
					setfillcolor(LIGHTGRAY);
					solidrectangle(360, 256, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(368, 256, ">Cancel<");
					break;
				}
				temp = sta;
			}
		}
		else
		{
			setfillcolor(BLACK);
			settextcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			if (time == 0)
			{
				solidrectangle(208 + (num - headch) * 8, 221, 215 + (num - headch) * 8, 223);
				time++;
			}
			else if (time == 50)
			{
				if (temppath[num - 1] != '\0')
					outtextxy(208 + (num - headch) * 8, 208, temppath[num - 1]);
				else
					outtextxy(208 + (num - headch) * 8, 208, '.');
				time++;
			}
			else
				time = (time + 1) % 100;
		}
		Sleep(10);
	}
}
//文件保存函数定义
void K_Save()
{
	int sta = 0, temp = 1;
	char ch;
	C_Node *p;
	L_Node *q;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//原名称另存为
	if (strcmp(K_Filename, "UNTITLED1") == 0)
	{
		K_Saveas();
		return;
	}
	if (fopen_s(&fp, K_Filepath, "r"))
	{
		fclose(fp);
		setfillcolor(LIGHTGRAY);
		solidrectangle(0, 464, 640, 480);
		settextcolor(RED);
		setbkcolor(LIGHTGRAY);
		outtextxy(8, 464, "Building the file is wrong!");
		Sleep(1000);
		settextcolor(BLACK);
		solidrectangle(0, 464, 640, 480);
		outtextxy(8, 464, "Enter=OK  Cancel=ESC");
		return;							//文件建造错误跳出
	}
	q = Hhead;
	while (q != NULL)
	{
		p = q->next;
		while (p != NULL)
		{
			if (p->ch == 13 && q->next1 == NULL)
				break;
			p->ch != 13 ? ch = p->ch : ch = 10;
			fputc(ch, fp);
			p = p->next;
		}
		q = q->next1;
	}
	fclose(fp);  fp = NULL;
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(RED);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "The file has been saved!");
	Sleep(1000);
	return;
}
//文件另存为函数定义
void K_Saveas()
{
	int i, num = 1, headch = 1, sta = 0, temp = 1, time = 0;
	char key, ch, temppath[128] = "\0";
	C_Node *p;
	L_Node *q;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(88, 176, 576, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(80, 160, 560, 288);
	setfillcolor(WHITE);
	solidrectangle(80, 160, 560, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(256, 160, "Save As New File");
	setbkcolor(LIGHTGRAY);
	outtextxy(112, 208, "File Path: [......................................]");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	while (true)
	{
		key = K_Input();
		fflush(stdin);								//清除键盘缓存区
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//检验左键状态
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(208, 256, 280, 280))
					sta = 1;
				else if (K_Hit.mkLButton == true && K_Mouse(360, 256, 432, 280))
					sta = 2;
				else
					sta = 0;
				break;
			case -8:
				FlushMouseMsgBuffer();				//清除鼠标缓存区
				if (K_Mouse(360, 256, 432, 280))
					return;
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//检验ENTER键
				if (num == 1)
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(0, 464, 640, 480);
					settextcolor(RED);
					setbkcolor(LIGHTGRAY);
					outtextxy(8, 464, "The path can't be null!");
					Sleep(1000);
					settextcolor(BLACK);
					solidrectangle(0, 464, 640, 480);
					outtextxy(8, 464, "Enter=OK  Cancel=ESC");
					break;							//路径错误跳出
				}
				else if (fopen_s(&fp, temppath, "r"))
				{
					fclose(fp);
					setfillcolor(LIGHTGRAY);
					solidrectangle(0, 464, 640, 480);
					settextcolor(RED);
					setbkcolor(LIGHTGRAY);
					outtextxy(8, 464, "The file has existed!");
					Sleep(1000);
					settextcolor(BLACK);
					solidrectangle(0, 464, 640, 480);
					outtextxy(8, 464, "Enter=OK  Cancel=ESC");
					break;							//文件存在跳出
				}
				if (fopen_s(&fp, temppath, "r"))
				{
					fclose(fp);
					setfillcolor(LIGHTGRAY);
					solidrectangle(0, 464, 640, 480);
					settextcolor(RED);
					setbkcolor(LIGHTGRAY);
					outtextxy(8, 464, "Building the file is wrong!");
					Sleep(1000);
					settextcolor(BLACK);
					solidrectangle(0, 464, 640, 480);
					outtextxy(8, 464, "Enter=OK  Cancel=ESC");
					return;							//文件建造错误跳出
				}
				q = Hhead;
				while (q != NULL)
				{
					p = q->next;
					while (p != NULL)
					{
						if (p->ch == 13 && q->next1 == NULL)
							break;
						p->ch != 13 ? ch = p->ch : ch = 10;
						fputc(ch, fp);
						p = p->next;
					}
					q = q->next1;
				}
				fclose(fp);  fp = NULL;
				setfillcolor(LIGHTGRAY);
				solidrectangle(0, 464, 640, 480);
				settextcolor(RED);
				setbkcolor(LIGHTGRAY);
				outtextxy(8, 464, "The file has been build!");
				Sleep(1000);
				return;
			case 8:
				time = 0;
				if (num > 1)
				{
					temppath[num - 2] = '\0';
					num--;
				}
				if (num < headch + 38 && headch>1)
				{
					headch--;
					for (i = headch; i < headch + 37; i++)
						outtextxy(208 + (i - headch) * 8, 208, temppath[i - 1]);
					outtextxy(208 + (num - headch) * 8, 208, '.');
				}
				else
				{
					outtextxy(208 + (num - headch) * 8, 208, '.');
					outtextxy(208 + (num - headch + 1) * 8, 208, '.');
				}
				break;
			case 27:								//检验ESC键
				return;
			default:
				time = 0;
				if (key>31 && key < 127 && num < 128)
				{
					temppath[num - 1] = key;
					temppath[num] = '\0';
					settextcolor(BLACK);
					setbkcolor(LIGHTGRAY);
					outtextxy(208 + (num - headch) * 8, 208, temppath[num - 1]);
					num++;
					if (num > headch + 37)
					{
						headch++;
						for (i = headch; i < headch + 37; i++)
							outtextxy(208 + (i - headch) * 8, 208, temppath[i - 1]);
						outtextxy(208 + (num - headch) * 8, 208, '.');
					}
				}
				break;
			}
			if (temp != sta)
			{
				switch (sta)
				{
				case 0:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					solidrectangle(360, 256, 432, 280);
					setfillcolor(BLACK);
					solidrectangle(216, 264, 280, 280);
					solidrectangle(368, 264, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(208, 256, ">  OK  <");
					outtextxy(360, 256, ">Cancel<");
					break;
				case 1:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(216, 256, "   OK   ");
					break;
				case 2:
					setfillcolor(LIGHTGRAY);
					solidrectangle(360, 256, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(368, 256, ">Cancel<");
					break;
				}
				temp = sta;
			}
		}
		else
		{
			setfillcolor(BLACK);
			settextcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			if (time == 0)
			{
				solidrectangle(208 + (num - headch) * 8, 221, 215 + (num - headch) * 8, 223);
				time++;
			}
			else if (time == 50)
			{
				if (temppath[num - 1] != '\0')
					outtextxy(208 + (num - headch) * 8, 208, temppath[num - 1]);
				else
					outtextxy(208 + (num - headch) * 8, 208, '.');
				time++;
			}
			else
				time = (time + 1) % 100;
		}
		Sleep(10);
	}
}
//文件关闭函数声明
void K_Close()
{
	int sta = 0, temp = 1;
	char key;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//文件空白判定
	if (Hhead->next1 == NULL&&Hhead->next->ch == 13)
	{
		K_New();
		return;
	}
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(88, 176, 576, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(80, 160, 560, 288);
	setfillcolor(WHITE);
	solidrectangle(80, 160, 560, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(280, 160, "Close File");
	setbkcolor(LIGHTGRAY);
	outtextxy(140, 208, "The file has not been saved yet. Save it now?");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	while (true)
	{
		key = K_Input();
		fflush(stdin);								//清除键盘缓存区
		if (key != 0)
		{
			switch (key)
			{
			case -8:
				FlushMouseMsgBuffer();						//清除鼠标缓存区
				if (K_Mouse(360, 256, 432, 280))
				{
					K_New();
					return;
				}
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//检验ENTER键
				//原名称另存为
				if (strcmp(K_Filename, "UNTITLED1") == 0)
				{
					K_Saveas();
					K_New();
					return;
				}
				K_Save();
				K_New();
				return;
			case 27:								//检验ESC键
				K_New();
				return;
			}
			if (temp != sta)
			{
				switch (sta)
				{
				case 0:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					solidrectangle(360, 256, 432, 280);
					setfillcolor(BLACK);
					solidrectangle(216, 264, 280, 280);
					solidrectangle(368, 264, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(208, 256, ">  OK  <");
					outtextxy(360, 256, ">Cancel<");
					break;
				case 1:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(216, 256, "   OK   ");
					break;
				case 2:
					setfillcolor(LIGHTGRAY);
					solidrectangle(360, 256, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(368, 256, ">Cancel<");
					break;
				}
				temp = sta;
			}
		}
		Sleep(10);
	}
}
//程序退出函数声明							
void K_Exit()
{
	K_Close();
	exit(0);
}
//选中复制函数定义
void K_Copy()
{
	int i;
	C_Node *p;
	L_Node *q;
	K_Record *r1, *r2;
	q = Hhead;  r1 = r2 = Rhead->next;
	while (r1 != NULL)
	{
		r1 = r1->next;
		free(r2);
		r2 = r1;
	}
	r1 = Rhead;
	if (K_Value != 0)
	{
		for (i = 1; i < K_Bline; i++)
			q = q->next1;
		p = q->next;
		for (i = 1; i < K_Bcol; i++)
			p = p->next;
		r1->ch = p->ch;
		for (K_Backcup = 1; K_Backcup < K_Value; K_Backcup++)
		{
			r1 = r1->next = (K_Record *)malloc(sizeof(K_Record));
			if (p->next != NULL)
			{
				p = p->next;
			}
			else
			{
				q = q->next1;
				p = q->next;
			}
			r1->ch = p->ch;
		}
		r1->next = NULL;
	}
}
//选中粘贴函数定义
void K_Paste()
{
	int i;
	C_Node *p, *p1;
	L_Node *q, *q1;
	K_Record *r;
	K_Notinverse();
	r = Rhead;
	q = Hhead;
	for (i = 1; i < K_Line; i++)
		q = q->next1;
	p = q->next;
	q1 = q->next1;
	for (i = 1; i < K_Col - 1; i++)
		p = p->next;
	if (K_Col == 1)
		p1 = q->next;
	else
		p1 = p->next;
	while (r != NULL)
	{
		if (K_Col == 1)
			p = q->next = (C_Node *)malloc(sizeof(C_Node));
		else
			p = p->next = (C_Node *)malloc(sizeof(C_Node));
		p->ch = r->ch;  r = r->next;  K_Col++;
		if (p->ch == 13)
		{
			p->next = NULL;
			q = q->next1 = (L_Node *)malloc(sizeof(L_Node));
			p = q->next;
			K_Line++;
			K_Col = 1;
			K_Maxline++;
		}
	}
	q->next1 = q1;
	if (K_Col == 1)
		q->next = p1;
	else
		p->next = p1;
	K_Curmove(-4);
	K_Border();
	K_View();
}
//选中清除函数定义
void K_Clear()
{
	int i;
	C_Node *p, *p1, *p2;
	L_Node *q, *q1, *q2;
	q = Hhead;
	for (i = 1; i < K_Bline; i++)			//定位至K_Bline行
		q = q->next1;
	p = q->next;
	for (i = 1; i < K_Bcol - 1; i++)			//定位至K_Bcol-1列
		p = p->next;
	if (K_Bcol == 1)
		p1 = p2 = p;
	else
		p1 = p2 = p->next;
	q1 = q2 = q->next1;
	for (i = 0; i < K_Value; i++)
	{
		p1 = p1->next;
		free(p2);					//释放列链表节点
		p2 = p1;
		if (p1 == NULL&&q1 != NULL)
		{
			p1 = p2 = q1->next;
			q1 = q1->next1;
			free(q2);				//释放行链表节点
			q2 = q1;
			K_Maxline--;
		}
	}
	if (K_Bcol == 1)
		q->next = p1;
	else
		p->next = p1;
	if (K_Bline != K_Eline)
		q->next1 = q1;
	K_Line = K_Bline;
	K_Col = K_Bcol;
	if (K_Maxline > 26 && K_Maxline - K_Hline < 26)
		K_Hline = K_Maxline - 26;
	else if (K_Maxline < 28)
		K_Hline = 1;
	if (K_Judge(K_Line)>76 && K_Judge(K_Line) - K_Hcol < 76)
		K_Hcol = K_Judge(K_Line) - 76;
	else if (K_Judge(K_Line) < 79)
		K_Hcol = 1;
	K_Border();
	K_Notinverse();
}
//程序设置函数声明
void K_Settings()
{
	int sta = 0, temp = 1, time = 0;
	char key, tabtemp = K_Tab;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(88, 176, 576, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(80, 160, 560, 288);
	setfillcolor(WHITE);
	solidrectangle(80, 160, 560, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(284, 160, "Open File");
	setbkcolor(LIGHTGRAY);
	outtextxy(112, 208, "Tab stops: [ .....................................]");
	outtextxy(208, 208, tabtemp + 48);
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(208, 256, 280, 280);
	solidrectangle(360, 256, 432, 280);
	setfillcolor(BLACK);
	solidrectangle(216, 264, 280, 280);
	solidrectangle(368, 264, 432, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(208, 256, ">  OK  <");
	outtextxy(360, 256, ">Cancel<");
	while (true)
	{
		key = K_Input();
		fflush(stdin);								//清除键盘缓存区
		FlushMouseMsgBuffer();						//清除鼠标缓存区
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//检验左键状态
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(208, 256, 280, 280))
					sta = 1;
				else if (K_Hit.mkLButton == true && K_Mouse(360, 256, 432, 280))
					sta = 2;
				else
					sta = 0;
				break;
			case -8:
				if (K_Mouse(360, 256, 432, 280))
					return;
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//检验ENTER键
				K_Tab = tabtemp;
				return;
			case 27:								//检验ESC键
				return;
			default:
				time = 0;
				if (key > 48 && key < 58)
				{
					tabtemp = key - 48;
					setfillcolor(BLACK);
					settextcolor(BLACK);
					setbkcolor(LIGHTGRAY);
					outtextxy(208, 208, tabtemp + 48);
				}
				break;
			}
			if (temp != sta)
			{
				switch (sta)
				{
				case 0:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					solidrectangle(360, 256, 432, 280);
					setfillcolor(BLACK);
					solidrectangle(216, 264, 280, 280);
					solidrectangle(368, 264, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(208, 256, ">  OK  <");
					outtextxy(360, 256, ">Cancel<");
					break;
				case 1:
					setfillcolor(LIGHTGRAY);
					solidrectangle(208, 256, 280, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(216, 256, "   OK   ");
					break;
				case 2:
					setfillcolor(LIGHTGRAY);
					solidrectangle(360, 256, 432, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(368, 256, ">Cancel<");
					break;
				}
				temp = sta;
			}
		}
		else
		{
			setfillcolor(BLACK);
			settextcolor(BLACK);
			setbkcolor(LIGHTGRAY);
			if (time == 0)
			{
				solidrectangle(216, 221, 223, 223);
				time++;
			}
			else if (time == 50)
			{
				outtextxy(216, 208, '.');
				time++;
			}
			else
				time = (time + 1) % 100;
		}
		Sleep(10);
	}
}
//命令帮助函数定义
void K_Commands()
{
	char key, sta = 0, temp = 1;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(88, 176, 576, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(80, 160, 560, 288);
	setfillcolor(WHITE);
	solidrectangle(80, 160, 560, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(292, 160, "No Help");
	setbkcolor(LIGHTGRAY);
	outtextxy(112, 192, "Edit was unable to find this help topic. Make sure");
	outtextxy(112, 208, "that the helpfile EDIT.HLP is in the same directory");
	outtextxy(112, 224, "as the edtor, and that it hasn't been moddified.");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(284, 256, 356, 280);
	setfillcolor(BLACK);
	solidrectangle(292, 264, 356, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(284, 256, ">  OK  <");
	while (true)
	{
		key = K_Input();
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//检验左键状态
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(284, 256, 356, 280))
					sta = 1;
				else
					sta = 0;
				break;
			case -8:
				if (K_Mouse(284, 256, 356, 280))
					return;
				break;
			case 13:								//检验ENTER键
				return;
			}
			if (temp != sta)
			{
				if (sta == 0)
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(284, 256, 356, 280);
					setfillcolor(BLACK);
					solidrectangle(292, 264, 356, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(284, 256, ">  OK  <");
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(284, 256, 356, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(292, 256, "   OK   ");
				}
				temp = sta;
			}
		}
		Sleep(10);
	}
}
//关于帮助函数定义
void K_About()
{
	char key, sta = 0, temp = 1;
	//初始化屏幕清除
	K_Filesta = K_Menusta = 0;
	K_Print();
	//更改状态栏
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK");
	//命令帮助菜单图形界面
	setfillcolor(BLACK);
	solidrectangle(136, 176, 528, 304);
	setfillcolor(LIGHTGRAY);
	solidrectangle(128, 160, 512, 288);
	setfillcolor(WHITE);
	solidrectangle(128, 160, 512, 176);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(280, 160, "About Edit");
	setbkcolor(LIGHTGRAY);
	outtextxy(248, 192, "KESHI-WIN32 Editor");
	outtextxy(268, 208, "Version 1.0.0");
	outtextxy(268, 224, "BY:KESHI 2015");
	//按钮图形界面
	setfillcolor(LIGHTGRAY);
	solidrectangle(284, 256, 356, 280);
	setfillcolor(BLACK);
	solidrectangle(292, 264, 356, 280);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	outtextxy(284, 256, ">  OK  <");
	while (true)
	{
		key = K_Input();
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//检验左键状态
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(284, 256, 356, 280))
					sta = 1;
				else
					sta = 0;
				break;
			case -8:
				if (K_Mouse(284, 256, 356, 280))
					return;
				break;
			case 13:								//检验ENTER键
				return;
			}
			if (temp != sta)
			{
				if (sta == 0)
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(284, 256, 356, 280);
					setfillcolor(BLACK);
					solidrectangle(292, 264, 356, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(284, 256, ">  OK  <");
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					solidrectangle(284, 256, 356, 280);
					settextcolor(BLACK);
					setbkcolor(WHITE);
					outtextxy(292, 256, "   OK   ");
				}
				temp = sta;
			}
		}
		Sleep(10);
	}
}
//文本显示函数定义
void K_View()
{
	int i, line, col, line1, col1;
	C_Node *p;
	L_Node *q;
	q = Hhead;
	col = line = 1;
	BeginBatchDraw();				//批量绘制开始
	settextcolor(LIGHTGRAY);
	setbkcolor(BLUE);
	setfillcolor(BLUE);
	solidrectangle(8, 32, 631, 463);
	for (i = 1; i < K_Hline; i++)			//定位至K_Hline行
	{
		q = q->next1;
		line++;
	}
	do{
		p = q->next;
		while (p->ch != 13 && (col - K_Hcol) < 78)
		{
			//判断在文本框内的数据输出
			if (line >= K_Hline&&col >= K_Hcol)
				outtextxy((col - K_Hcol + 1) * 8, 16 + (line - K_Hline + 1) * 16, p->ch);
			p = p->next;
			col++;
		}
		q = q->next1;
		col = 1;
		line++;
	} while (q != NULL && (line - K_Hline) < 27);
	if (K_Bline != K_Eline || K_Bcol != K_Ecol)
	{
		K_Value = 0;
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
		if (K_Bline < K_Eline || (K_Bline == K_Eline&&K_Bcol < K_Ecol))
		{
			line = K_Bline;
			col = K_Bcol;
			line1 = K_Eline;
			col1 = K_Ecol;
		}
		else
		{
			line = K_Eline;
			col = K_Ecol;
			line1 = K_Bline;
			col1 = K_Bcol;
		}
		q = Hhead;
		for (i = 1; i < line; i++)		//定位line行
			q = q->next1;
		p = q->next;
		for (i = 1; i < col; i++)		//定位col列
			p = p->next;
		while (line < line1 || (line == line1&&col < col1))
		{
			K_Value++;
			if (line >= K_Hline&&line <= K_Hline + 26 && col >= K_Hcol&&col <= K_Hcol + 77)
			{
				if (p->ch != 13)
					outtextxy((col - K_Hcol + 1) * 8, 16 + (line - K_Hline + 1) * 16, p->ch);
				else
					outtextxy((col - K_Hcol + 1) * 8, 16 + (line - K_Hline + 1) * 16, ' ');
			}
			if (p->next != NULL)
			{
				p = p->next;
				col++;
			}
			else
			{
				q = q->next1;
				p = q->next;
				line++;  col = 1;
			}
		}
	}
	EndBatchDraw();					//批量绘制结束
}
//常规字符判断函数定义
char K_Check(int m, int n)
{
	int i;
	L_Node *q;
	C_Node *p;
	q = Hhead;
	if (m < 1 || n < 1)
		return -1;							//不存在返回-1
	for (i = 1; i < m; i++)						//定位至m行
	{
		if (q->next1 == NULL)
			return -1;						//不存在返回-1
		q = q->next1;
	}
	p = q->next;
	for (i = 1; i < n; i++)						//定位至n列
	{
		if (p->next == NULL)
			return -1;						//不存在返回-1
		p = p->next;
	}
	if (p->ch == 13)
		return 13;							//回车返回13;
	if (p->ch>31 && p->ch < 127)
		return p->ch;						//返回常规字符
	else return 0;							//其他字符返回0
}
//常规字符计数函数定义
int K_Judge(int m)
{
	int i, num = 0;
	L_Node *q;
	C_Node *p;
	q = Hhead;
	for (i = 1; i < m; i++)
	{
		if (q == NULL) return -1;				//返回-1表示当前行不存在
		q = q->next1;
	}
	p = q->next;
	while (p->next != NULL)
	{
		p = p->next;
		num++;
	}
	return num;								//返回常规字符数
}
//删除文本函数定义
void K_Del(int m, int n)
{
	int i;
	L_Node *q, *q1;
	C_Node *p1, *p2;
	q = q1 = Hhead;
	K_Curmove(-3);
	//第1行 第0列不存在返回
	if (n == 0 && m == 1) return;
	if (m > 1)
	{
		for (i = 1; i < m - 1; i++)	//定位至m-1行
			q1 = q1->next1;
		q = q1->next1;
	}
	p1 = q->next;
	for (i = 1; i < n - 1; i++)		//定位至n-1列
		p1 = p1->next;
	p2 = p1->next;
	i = K_Hcol;				//标记
	if (n == 0)
	{
		K_Maxline--;
		p1 = q1->next;
		if (p1->ch != 13)		//m-1行不仅只有一个回车
		{
			while (p1->next->ch != 13)
				p1 = p1->next;
			free(p1->next);
			p1->next = q->next;
		}
		else				//m-1行有且仅有一个回车
		{
			free(p1);
			q1->next = q->next;
		}
		q1->next1 = q->next1;
		free(q);
		if (K_Maxline > 26 && K_Maxline - K_Hline < 26)
			K_Hline = K_Maxline - 26;
		K_Border();
	}
	else if (n == 1)
	{
		q->next = p1->next;
		free(p1);
	}
	else
	{
		p1->next = p2->next;
		free(p2);
	}
	if (K_Judge(K_Line)>76 && K_Judge(K_Line) - K_Hcol < 76)
		K_Hcol = K_Judge(K_Line) - 76;
	if (K_Check(m, n) != 13 || i != K_Hcol)
		K_View();
	else
	{
		settextcolor(LIGHTGRAY);
		setbkcolor(BLUE);
		outtextxy((n - K_Hcol + 1) * 8, 16 + (m - K_Hline + 1) * 16, ' ');
	}
}
//字符插入函数定义
void K_Insert(int m, int n, char word)
{
	int i;
	L_Node *q, *q1;
	C_Node *p, *p1;
	q = Hhead;
	if (K_Value != 0)			//判断是否选中
	{
		K_Clear();
		m = K_Line;
		n = K_Col;
	}
	for (i = 1; i < m; i++)		//定位至m行
		q = q->next1;
	p1 = q->next;
	for (i = 1; i < n - 1; i++)		//定位至n列
		p1 = p1->next;
	p = (C_Node *)malloc(sizeof(C_Node));
	p->ch = word;
	if (n == 1)				//前方无字符插入
	{
		p->next = q->next;
		q->next = p;
	}
	else					//前方有字符插入
	{
		p->next = p1->next;
		p1->next = p;
	}
	if (word == 13)
	{
		K_Maxline++;
		q1 = (L_Node *)malloc(sizeof(L_Node));
		q1->next = p->next;
		p->next = NULL;
		q1->next1 = q->next1;
		q->next1 = q1;
	}
	if (K_Check(K_Line, K_Col + 1) != 13)
		K_View();
	else
	{
		settextcolor(LIGHTGRAY);
		setbkcolor(BLUE);
		outtextxy((K_Col - K_Hcol + 1) * 8, 16 + (K_Line - K_Hline + 1) * 16, word);
	}
	K_Curmove(-4);			//光标右移
}
//字体选中函数定义
void K_Inverse()
{
	int i, temp, line, col;
	char key = 0;
	K_Notinverse();
	K_Bline = K_Eline = K_Line;
	K_Bcol = K_Ecol = K_Col;
	temp = K_Hit.y;
	while (GetKeyState(VK_SHIFT) < 0 || GetKeyState(VK_LBUTTON) < 0)
	{
		switch (key)
		{
		case -1:
		case -2:
		case -3:
		case -4:
			K_Curmove(key);
			K_Eline = K_Line;
			K_Ecol = K_Col;
			K_View();
			break;
		case -7:						//鼠标选中
			if (temp != K_Hit.y)
			{
				line = K_Hit.y / 16 + K_Hline - 2;
				col = K_Hit.x / 8 + K_Hcol - 1;
				if (line < K_Hline&&K_Hline>1)
					K_Line = (--K_Hline);
				else if (line > K_Hline + 26 && K_Hline + 26 < K_Maxline)
					K_Line = (++K_Hline) + 26;
				else if (line >= K_Hline&&line > K_Maxline)
					K_Line = K_Maxline;
				else if (line<1)
					K_Line = 1;
				else K_Line = line;
				if (col < K_Hcol&&K_Hcol>1)
					K_Col = (--K_Hcol);
				else if (col>K_Hcol + 77 && K_Hcol + 76 < K_Judge(K_Line))
					K_Col = (++K_Hcol) + 77;
				else if (col >= K_Hcol&&col > K_Judge(K_Line) + 1)
					K_Col = K_Judge(K_Line) + 1;
				else if (col < 1)
					K_Col = 1;
				else K_Col = col;
				K_Eline = K_Line;
				K_Ecol = K_Col;
				K_Border();
				K_View();
			}
			break;
		default:						//SHIFT+常规字符
			if (GetKeyState(VK_SHIFT) < 0 && isprint(key))
				K_Insert(K_Line, K_Col, key);
			break;
		}
		Sleep(10);
		K_Curflash();
		key = K_Input();
	}
	//行列交换
	if (K_Bline > K_Eline || (K_Bline == K_Eline&&K_Bcol > K_Ecol))
	{
		i = K_Bline;
		K_Bline = K_Eline;
		K_Eline = i;
		i = K_Bcol;
		K_Bcol = K_Ecol;
		K_Ecol = i;
	}
}
//选中取消函数定义
void K_Notinverse()
{
	if (K_Value != 0)
	{
		K_Eline = K_Bline;
		K_Ecol = K_Bcol;
		K_Value = 0;
		K_View();
	}
}

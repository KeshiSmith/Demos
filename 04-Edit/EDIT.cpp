#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<graphics.h>
//�궨�峣�ùؼ���
#define uchar unsigned char
#define uint unsigned int
//ȫ�ֱ�������
char K_Filename[64];					//�ļ�������
char K_Filepath[128];					//�ļ�·������
char K_Curtime = 0;						//�����˸���Ʊ���
char K_Filesta = 0, K_Menusta = 0;		//�ļ��˵�״̬����
int K_Line, K_Col;						//������������
int K_Maxline, K_Hline, K_Hcol;			//����±��ַ�������
int K_Bline, K_Bcol, K_Eline, K_Ecol;	//�ַ�ѡ�з��ױ���
int K_Value, K_Backcup;					//�ַ�����ճ������
int K_Tab = 4;							//Tab����������
FILE *fp = NULL;						//�ļ�·��ָ�����
MOUSEMSG K_Hit;							//�����Ϣ�ṹ�����
typedef struct K_Record				//���а�ṹ�����
{
	char ch;
	struct K_Record *next;
}K_Record;
typedef struct C_Node					//�н��ṹ�����
{
	char ch;
	struct C_Node *next;
}C_Node;
typedef struct L_Node					//�н��ṹ�����
{
	C_Node *next;
	struct L_Node *next1;
}L_Node;
L_Node *Hhead = NULL;					//�е��������
K_Record *Rhead = NULL;					//���а����ݱ���
//��������
void K_Print();							//������ʾ��������
void K_Menu();							//�˵�ͼ�κ�������
void K_Stabar();						//״̬��ͼ�κ�������
void K_Border();						//�߿�ͼ�κ�������
void K_Schemove();						//������������������
char K_Input();							//�����⺯������
void K_Process();						//���봦��������
bool K_Mouse(int, int, int, int);		//����⺯������
void K_Curmove(int);					//����ƶ���������
void K_Curflash();						//�����˸��������
void K_New();							//�½��ļ���������
void K_Open();							//�ļ��򿪺�������
void K_Save();							//�ļ����溯������
void K_Saveas();						//�ļ����Ϊ��������
void K_Close();							//�ļ��رպ�������
void K_Exit();							//�����˳���������
void K_Copy();							//ѡ�и��ƺ�������
void K_Paste();							//ѡ��ճ����������
void K_Clear();							//ѡ�������������
void K_Settings();						//�������ú�������
void K_Commands();						//���������������
void K_About();							//���ڰ�����������
void K_View();							//�ı���ʾ��������
char K_Check(int, int);					//�����ַ��жϺ�������
int K_Judge(int);						//�����ַ�������������
void K_Del(int, int);					//ɾ���ı���������
void K_Insert(int, int, char);			//�ַ����뺯������
void K_Inverse();						//����ѡ�к�������
void K_Notinverse();					//ѡ��ȡ����������
//������
int main()
{
	K_New();							//�����ʼ��
	initgraph(640, 480);
	settextstyle(16, 8, "Fixedsys");	//����������ʽ
	K_Print();							//��Ļ��ʼ��
	while (true)
	{
		K_Process();
		Sleep(10);
	}
	closegraph();
	return 0;
}
//������ʾ��������
void K_Print()
{
	BeginBatchDraw();			//�������ƿ�ʼ
	K_Border();
	K_View();
	K_Menu();
	K_Stabar();
	EndBatchDraw();			//�������ƽ���
}
//�˵�ͼ�κ�������
void K_Menu()
{
	char nametemp[128];
	BeginBatchDraw();			//�������ƿ�ʼ
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 640, 15);	//���ò˵�������
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
		//FILE�����˵�
		setfillcolor(BLACK);
		solidrectangle(16, 32, 168, 208);
		setfillcolor(LIGHTGRAY);
		solidrectangle(8, 16, 152, 192);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(11, 24, 148, 25);
		solidrectangle(11, 120, 148, 121);
		solidrectangle(11, 152, 148, 153);
		solidrectangle(11, 184, 148, 185);
		solidrectangle(11, 24, 12, 185);
		solidrectangle(148, 24, 149, 185);
		//�����˵�ѡ��		
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
		//EDIT�����˵�
		setfillcolor(BLACK);
		solidrectangle(64, 32, 228, 128);
		setfillcolor(LIGHTGRAY);
		solidrectangle(56, 16, 212, 112);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(59, 24, 209, 25);
		solidrectangle(59, 104, 209, 105);
		solidrectangle(59, 24, 60, 105);
		solidrectangle(208, 24, 209, 105);
		//�����˵�ѡ��
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
		//SEARCH�����˵�
		setfillcolor(BLACK);
		solidrectangle(112, 32, 328, 112);
		setfillcolor(LIGHTGRAY);
		solidrectangle(104, 16, 312, 96);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(107, 24, 309, 25);
		solidrectangle(107, 87, 309, 88);
		solidrectangle(107, 24, 108, 88);
		solidrectangle(308, 24, 309, 88);
		//�����˵�ѡ��
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
		strcpy_s(nametemp, K_Filename);	//�ļ������ȴ���
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
		//VIEW�����˵�
		setfillcolor(BLACK);
		solidrectangle(176, 32, 392, 144);
		setfillcolor(LIGHTGRAY);
		solidrectangle(168, 16, 376, 128);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(171, 24, 373, 25);
		solidrectangle(171, 88, 373, 89);
		solidrectangle(171, 119, 373, 120);
		solidrectangle(171, 24, 172, 120);
		solidrectangle(372, 24, 373, 120);
		//�����˵�ѡ��
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
		//OPTIONS�����˵�
		setfillcolor(BLACK);
		solidrectangle(224, 32, 384, 96);
		setfillcolor(LIGHTGRAY);
		solidrectangle(216, 16, 368, 80);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(219, 24, 365, 25);
		solidrectangle(219, 71, 365, 72);
		solidrectangle(219, 24, 220, 72);
		solidrectangle(364, 24, 365, 72);
		//�����˵�ѡ��
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
		//HELP�����˵�
		setfillcolor(BLACK);
		solidrectangle(296, 32, 416, 96);
		setfillcolor(LIGHTGRAY);
		solidrectangle(288, 16, 400, 80);
		//�����˵��߿�
		setfillcolor(BLACK);
		solidrectangle(291, 24, 397, 25);
		solidrectangle(291, 71, 397, 72);
		solidrectangle(291, 24, 292, 72);
		solidrectangle(396, 24, 397, 72);
		//�����˵�ѡ��
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
	EndBatchDraw();				//�������ƽ���
}
//״̬��ͼ�κ�������
void K_Stabar()
{
	char temp[8];
	BeginBatchDraw();				//�������ƿ�ʼ
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
		outtextxy(496, 464, temp);	//��ӡ����
		_itoa_s(K_Col, temp, 10);
		outtextxy(584, 464, temp);	//��ӡ����
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
	EndBatchDraw();					//�������ƽ���
}
//�߿�ͼ�κ�������
void K_Border()
{
	double up, down;
	BeginBatchDraw();					//�������ƿ�ʼ
	setfillcolor(BLACK);				//���ñ���
	solidrectangle(0, 16, 7, 463);
	solidrectangle(632, 16, 639, 463);
	solidrectangle(0, 16, 639, 31);
	setfillcolor(LIGHTGRAY);			//���ñ߿�
	solidrectangle(3, 24, 4, 463);
	solidrectangle(3, 24, 636, 25);
	solidrectangle(635, 24, 636, 31);
	settextcolor(BLACK);
	//�����ļ�����
	setbkcolor(LIGHTGRAY);
	solidrectangle(312 - strlen(K_Filename) * 4, 16, 328 + strlen(K_Filename) * 4, 31);
	outtextxy(320 - strlen(K_Filename) * 4, 16, K_Filename);
	//���ý�����
	settextcolor(LIGHTGRAY);
	setbkcolor(BLACK);
	outtextxy(629, 32, "��");
	outtextxy(629, 448, "��");
	//����������
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
	EndBatchDraw();				//�������ƽ���
}
//������������������
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
//�����⺯������
char K_Input()
{
	uchar key1, key2;
	if (_kbhit())				//ʵʱ����������
	{
		key1 = _getch();
		if (key1 == 224)			//��������
			key2 = _getch();
		else return key1;		//���ػ�������
		switch (key2)
		{
		case 72:
			return -1;			//�����Ϸ����
		case 80:
			return -2;			//�����·����
		case 75:
			return -3;			//���������
		case 77:
			return -4;			//�����ҷ����
		case 141:
			return -12;			//����CTRL+��
		case 145:
			return -13;			//����CTRL+��
		case 115:
			return -14;			//����CTRL+��
		case 116:
			return -15;			//����CTRL+��
		case 83:
			return -11;			//����DEL��
		}
	}
	else if (GetKeyState(VK_SHIFT) < 0)	//����SHIFT��
		return -10;
	else if (GetKeyState(VK_CONTROL) < 0)	//����CTRL��
		return -9;
	else if (MouseHit())
	{
		K_Hit = GetMouseMsg();
		if (K_Hit.uMsg == WM_LBUTTONUP)		//��������ɿ�
			return -8;
		else if (K_Hit.uMsg == WM_MOUSEMOVE)	//��������ƶ�
			return -7;
		else if (K_Hit.uMsg == WM_LBUTTONDOWN)	//����������
			return -6;
	}
	else if (GetKeyState(VK_MENU) < 0)
		return -5;							//����ALT��
	return NULL;							//������ʱ����NULL
}
//���봦��������
void K_Process()
{
	int key, temp;							//�����ݴ����
	key = K_Input();
	if (key != 0)
	{
		switch (key)
		{
		case -3:							//���������
			if (K_Filesta > 1)
			{
				K_Filesta = (K_Filesta + 3) % 6 + 2;
				K_Menusta = 1;
				K_Print();
			}
			break;
		case -4:							//�����ҷ����
			if (K_Filesta > 1)
			{
				K_Filesta = (K_Filesta - 1) % 6 + 2;
				K_Menusta = 1;
				K_Print();
			}
			break;
		case -7:							//��������ƶ�
			if (K_Hit.mkLButton != true)
				break;
		case -6:							//����������
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
			if (temp != K_Filesta)				//���״̬�Ƿ�ı��Լ�����˸
			{
				K_Menusta = K_Curtime = 0;
				K_Print();
			}
			break;
		case -8:							//��������ɿ�
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
		if (GetKeyState(VK_F1) < 0)					//����F1��״̬
		{
			K_Commands();
			K_Print();
		}
		else if (key != 0 && key != -7 && key != -8)
		{
			if (key != -9 && key != -10)					//�������
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
			case -5:								//����ALT��
				K_Filesta = 1;
				K_Menusta = 0;
				K_Menu();
				K_Menusta = 1;
				while (GetKeyState(VK_MENU) < 0)
				{
					if (GetKeyState(70) < 0)			//����F��״̬	
						K_Filesta = 2;
					else if (GetKeyState(69) < 0)		//����E��״̬
						K_Filesta = 3;
					else if (GetKeyState(83) < 0)		//����S��״̬
						K_Filesta = 4;
					else if (GetKeyState(86) < 0)		//����V��״̬
						K_Filesta = 5;
					else if (GetKeyState(79) < 0)		//����O��״̬	
						K_Filesta = 6;
					else if (GetKeyState(72) < 0)		//����H��״̬
						K_Filesta = 7;
					if (K_Filesta != 1)
					{
						K_Menu();
						K_Stabar();
						while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
							Sleep(10);
						break;
					}
				}
				K_Print();
				break;
			case -6:								//�����������
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
			case -10:								//����SHIFT��
				if (GetKeyState(VK_SHIFT) < 0)
					K_Inverse();
				else
					K_Curflash();
				break;
			case -11:								//����DEL��
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
			case -12:								//����CTRL+��
				K_Notinverse();
				if (K_Line > 1)
				{
					K_Line--;
					K_Col = 2;
					K_Curmove(-3);
				}
				break;
			case -13:								//����CTRL+��
				K_Notinverse();
				if (K_Line < K_Maxline)
				{
					K_Line++;
					K_Col = 2;
					K_Curmove(-3);
				}
				break;
			case -14:								//����CTRL+��
				K_Notinverse();
				K_Col = 2;
				K_Curmove(-3);
				break;
			case -15:								//����CTRL+��
				K_Notinverse();
				K_Col = K_Judge(K_Line);
				K_Curmove(-4);
				break;
			case 8:									//����BACKSPACE��
				if (K_Value != 0)
					K_Clear();
				else
					K_Del(K_Line, K_Col - 1);
				break;
			case 9:									//����TAB��
				for (temp = 0; temp < K_Tab; temp++)
					K_Insert(K_Line, K_Col, 32);
				break;
			case 24:								//�ı�����CTRL+X
				if (K_Value != 0)
				{
					K_Copy();
					K_Clear();
				}
				break;
			case -9:								//�ı�����CTRL+C
				if (GetKeyState(67) < 0 && K_Value != 0)
					K_Copy();
				else
					K_Curflash();
				break;
			case 22:								//�ı�ճ��CTRL+V
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
			if (GetKeyState(70) < 0 || (K_Menusta == 1 && key == 13))		//����F��״̬
				K_Filesta = 2;
			else if (GetKeyState(69) < 0 || (K_Menusta == 2 && key == 13))	//����E��״̬
				K_Filesta = 3;
			else if (GetKeyState(83) < 0 || (K_Menusta == 3 && key == 13))	//����S��״̬	
				K_Filesta = 4;
			else if (GetKeyState(86) < 0 || (K_Menusta == 4 && key == 13))	//����V��״̬
				K_Filesta = 5;
			else if (GetKeyState(79) < 0 || (K_Menusta == 5 && key == 13))	//����O��״̬
				K_Filesta = 6;
			else if (GetKeyState(72) < 0 || (K_Menusta == 6 && key == 13))	//����H��״̬
				K_Filesta = 7;
			else switch (key)
			{
			case -3:							//���������
				K_Menusta = (K_Menusta + 4) % 6 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -4:							//�����ҷ����
				K_Menusta = K_Menusta % 6 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//����ALT��
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
			case 27:							//����ESC��
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
			if (GetKeyState(78) < 0 || (K_Menusta == 1 && key == 13))		//����N��״̬
			{
				K_Filesta = 0;
				K_New();
			}
			else if (GetKeyState(79) < 0 || (K_Menusta == 2 && key == 13))	//����O��״̬
				K_Open();
			else if (GetKeyState(83) < 0 || (K_Menusta == 3 && key == 13))	//����S��״̬
				K_Save();
			else if (GetKeyState(65) < 0 || (K_Menusta == 4 && key == 13))	//����A��״̬
				K_Saveas();
			else if (GetKeyState(67) < 0 || (K_Menusta == 5 && key == 13))	//����C��״̬
				K_Close();
			else if (GetKeyState(88) < 0 || (K_Menusta == 7 && key == 13))	//����X��״̬
				K_Exit();
			else switch (key)
			{
			case -1:							//�����Ϸ����
				K_Menusta = (K_Menusta + 5) % 7 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//�����·����
				K_Menusta = K_Menusta % 7 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//�����������
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
			case -8:							//��������ɿ�
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
			case 27:							//����ESC��
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
			if ((GetKeyState(84) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)		//����T��״̬
			{
				K_Filesta = 0;
				K_Copy();
				K_Clear();
			}
			else if ((GetKeyState(67) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)	//����C��״̬
			{
				K_Filesta = 0;
				K_Copy();
			}
			else if ((GetKeyState(80) < 0 || (K_Menusta == 1 && key == 13)) && K_Backcup != 0)	//����P��״̬
			{
				K_Filesta = 0;
				K_Paste();
			}
			if ((GetKeyState(69) < 0 || (K_Menusta == 1 && key == 13)) && K_Value != 0)		//����E��״̬
			{
				K_Filesta = 0;
				K_Clear();
			}
			else switch (key)
			{
			case -1:							//�����Ϸ����
				K_Menusta = (K_Menusta + 2) % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//�����·����
				K_Menusta = K_Menusta % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				K_Menusta = 2;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//����������
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
			case -8:							//��������ɿ�
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
			case 27:							//����ESC��
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
			case -1:							//�����Ϸ����
				K_Menusta = (K_Menusta + 1) % 3 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//�����·����
				K_Menusta = K_Menusta % 3 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				K_Menusta = 3;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//����������
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
			case -8:							//��������ɿ�
				switch (K_Menusta)
				{
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//����ESC��
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
			case -1:							//�����Ϸ����
				K_Menusta = (K_Menusta + 2) % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -2:							//�����·����
				K_Menusta = K_Menusta % 4 + 1;
				K_Menu();
				K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				K_Menusta = 4;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//����������
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
			case -8:							//��������ɿ�
				switch (K_Menusta)
				{
				case 0:
					K_Filesta = 0;
					K_Print();
					break;
				}
				break;
			case 27:							//����ESC��
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
			if (GetKeyState(83) < 0 || (K_Menusta == 1 && key == 13))		//����S��״̬
			{
				K_Settings();
			}
			else switch (key)
			{
			case -1:							//�����Ϸ����
			case -2:							//�����·����
				K_Menusta = K_Menusta % 2 + 1;
				K_Menu(); K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				K_Menusta = 5;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//����������
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
			case -8:							//��������ɿ�
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
			case 27:							//����ESC��
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
			if (GetKeyState(67) < 0 || (K_Menusta == 1 && key == 13))		//����C��״̬
				K_Commands();
			else if (GetKeyState(65) < 0 || (K_Menusta == 2 && key == 13))	//����A��״̬
				K_About();
			else switch (key)
			{
			case -1:							//�����Ϸ����
			case -2:							//�����·����
				K_Menusta = K_Menusta % 2 + 1;
				K_Menu(); K_Stabar();
				break;
			case -5:							//����ALT��
				K_Filesta = 1;
				K_Menusta = 6;
				while (GetKeyState(VK_MENU) < 0)	//���鰴���Ƿ��ɿ�
					Sleep(10);
				break;
			case -7:							//��������ƶ�
				if (K_Hit.mkLButton != true) break;
			case -6:							//����������
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
			case -8:							//��������ɿ�
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
			case 27:							//����ESC��
				K_Filesta = 0;
				break;
			}
			if (K_Filesta != 7)
				K_Print();
		}
		break;
	}
	fflush(stdin);								//������̻�����
	FlushMouseMsgBuffer();					//�����껺����
}
//����ƶ���������
void K_Curmove(int key)
{
	int temp1 = K_Hline, temp2 = K_Hcol;
	K_Curtime = 0;
	switch (key)
	{
	case -1:
		if (K_Line > 1)						//�����Ƿ��ǵ�һ��
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
		if ((K_Line > 1 || K_Col > 1) && (--K_Col < 1))//�����Ƿ��ǵ�һ���ַ�
		{
			K_Line--;
			K_Col = K_Judge(K_Line) + 1;
		}
		break;
	case -4:
		if (K_Check(K_Line, ++K_Col) < 0)	//������
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
	if (K_Line - K_Hline>26)					//�жϲ�����ԭ��
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
//�����˸��������
void K_Curflash()
{
	BeginBatchDraw();				//�������ƿ�ʼ
	setfillcolor(LIGHTGRAY);
	settextcolor(LIGHTGRAY);
	setbkcolor(BLUE);
	//�ж��Ƿ񷴰�
	if (K_Value>0 && ((K_Line > K_Bline || (K_Line == K_Bline&&K_Col >= K_Bcol)) && \
		(K_Line < K_Eline || (K_Line == K_Eline&&K_Col<K_Ecol)) || (K_Line>K_Eline || (K_Line == K_Eline&&K_Col >= K_Ecol)) && \
		(K_Line < K_Bline || (K_Line == K_Bline&&K_Col < K_Bcol))))
	{
		setfillcolor(BLACK);
		settextcolor(BLACK);
		setbkcolor(LIGHTGRAY);
	}
	if (K_Curtime == 0)				//�����ʾ
	{
		solidrectangle((K_Col - K_Hcol + 1) * 8, 28 + (K_Line - K_Hline + 1) * 16, (K_Col - K_Hcol + 1) * 8 + 8 - 1, 31 + (K_Line - K_Hline + 1) * 16);
		K_Curtime++;
	}
	else if (K_Curtime == 50)			//�������
	{
		if (K_Check(K_Line, K_Col) != 13)
			outtextxy((K_Col - K_Hcol + 1) * 8, 16 + (K_Line - K_Hline + 1) * 16, K_Check(K_Line, K_Col));
		else
			outtextxy((K_Col - K_Hcol + 1) * 8, 16 + (K_Line - K_Hline + 1) * 16, ' ');
		K_Curtime++;
	}
	else
		K_Curtime = (K_Curtime + 1) % 100;
	EndBatchDraw();					//�������ƽ���
}
//����⺯������
bool K_Mouse(int X_L, int Y_U, int X_R, int Y_D)
{
	if (K_Hit.x >= X_L&&K_Hit.x <= X_R&&K_Hit.y >= Y_U&&K_Hit.y <= Y_D)
		return true;		//����TRUE
	else
		return false;		//����FALSE
}
//�½��ļ���������
void K_New()
{
	C_Node *p, *p1;				//�е��������
	L_Node *q, *q1;				//�е��������
	K_Record *r1, *r2;			//���а��������
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
	if (Rhead != NULL)				//�ͷż��а�����
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
	Hhead = (L_Node *)malloc(sizeof(L_Node));			//Ϊ�е���������ڴ�ռ�
	q = Hhead;
	Hhead->next1 = NULL;
	p = q->next = (C_Node *)malloc(sizeof(C_Node));		//Ϊ�е���������ڴ�ռ�
	p->ch = 13;
	p->next = NULL;
	Rhead = (K_Record *)malloc(sizeof(K_Record));		//Ϊ���а���������ڴ�ռ�
	Rhead->ch = 0;
	Rhead->next = NULL;
	K_Line = K_Col = K_Hline = K_Hcol = K_Maxline = 1;
	K_Bline = K_Bcol = K_Eline = K_Ecol = 1;
	K_Value = K_Backcup = 0;							//ȫ�ֱ�����ʼ��
	strcpy_s(K_Filename, "UNTITLED1");
	strcpy_s(K_Filepath, "UNTITLED1");
}
//�ļ��򿪺�������
void K_Open()
{
	int i, num = 1, headch = 1, sta = 0, temp = 1, time = 0;
	char key, ch, temppath[128] = "\0";
	C_Node *p, *p1;
	L_Node *q;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
	//��ťͼ�ν���
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
		fflush(stdin);								//������̻�����
		FlushMouseMsgBuffer();						//�����껺����
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//�������״̬
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
			case 13:								//����ENTER��
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
					break;							//·����������
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
					break;							//�ļ�����������
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
				i = 1;								//����ʼ��־
				while ((ch = fgetc(fp)) != EOF)
				{
					if (i == 1)
					{
						i = 0;
						p1 = q->next = (C_Node *)malloc(sizeof(C_Node));
					}
					else
						p1 = p1->next = (C_Node *)malloc(sizeof(C_Node));
					if ((p1->ch = ch) == 10)				//���з�����
					{
						i = 1;
						p1->ch = 13;
						K_Maxline++;
						q = q->next1 = (L_Node *)malloc(sizeof(L_Node));
						p1->next = NULL;
						p1 = q->next;
					}
					else if (p1->ch == 9)				//TABת��Ϊ�ո�
					{
						p1->ch = 32;
						for (num = 0; num < K_Tab - 1; num++)
						{
							p1 = p1->next = (C_Node *)malloc(sizeof(C_Node));
							p1->ch = 32;
						}
					}
				}
				if (i == 1)							//�������������ַ�13
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
			case 27:								//����ESC��
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
//�ļ����溯������
void K_Save()
{
	int sta = 0, temp = 1;
	char ch;
	C_Node *p;
	L_Node *q;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//ԭ�������Ϊ
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
		return;							//�ļ������������
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
//�ļ����Ϊ��������
void K_Saveas()
{
	int i, num = 1, headch = 1, sta = 0, temp = 1, time = 0;
	char key, ch, temppath[128] = "\0";
	C_Node *p;
	L_Node *q;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
		fflush(stdin);								//������̻�����
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//�������״̬
			case -7:
				if (K_Hit.mkLButton == true && K_Mouse(208, 256, 280, 280))
					sta = 1;
				else if (K_Hit.mkLButton == true && K_Mouse(360, 256, 432, 280))
					sta = 2;
				else
					sta = 0;
				break;
			case -8:
				FlushMouseMsgBuffer();				//�����껺����
				if (K_Mouse(360, 256, 432, 280))
					return;
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//����ENTER��
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
					break;							//·����������
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
					break;							//�ļ���������
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
					return;							//�ļ������������
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
			case 27:								//����ESC��
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
//�ļ��رպ�������
void K_Close()
{
	int sta = 0, temp = 1;
	char key;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//�ļ��հ��ж�
	if (Hhead->next1 == NULL&&Hhead->next->ch == 13)
	{
		K_New();
		return;
	}
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
		fflush(stdin);								//������̻�����
		if (key != 0)
		{
			switch (key)
			{
			case -8:
				FlushMouseMsgBuffer();						//�����껺����
				if (K_Mouse(360, 256, 432, 280))
				{
					K_New();
					return;
				}
				else if (!K_Mouse(208, 256, 280, 280))
					break;
			case 13:								//����ENTER��
				//ԭ�������Ϊ
				if (strcmp(K_Filename, "UNTITLED1") == 0)
				{
					K_Saveas();
					K_New();
					return;
				}
				K_Save();
				K_New();
				return;
			case 27:								//����ESC��
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
//�����˳���������							
void K_Exit()
{
	K_Close();
	exit(0);
}
//ѡ�и��ƺ�������
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
//ѡ��ճ����������
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
//ѡ�������������
void K_Clear()
{
	int i;
	C_Node *p, *p1, *p2;
	L_Node *q, *q1, *q2;
	q = Hhead;
	for (i = 1; i < K_Bline; i++)			//��λ��K_Bline��
		q = q->next1;
	p = q->next;
	for (i = 1; i < K_Bcol - 1; i++)			//��λ��K_Bcol-1��
		p = p->next;
	if (K_Bcol == 1)
		p1 = p2 = p;
	else
		p1 = p2 = p->next;
	q1 = q2 = q->next1;
	for (i = 0; i < K_Value; i++)
	{
		p1 = p1->next;
		free(p2);					//�ͷ�������ڵ�
		p2 = p1;
		if (p1 == NULL&&q1 != NULL)
		{
			p1 = p2 = q1->next;
			q1 = q1->next1;
			free(q2);				//�ͷ�������ڵ�
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
//�������ú�������
void K_Settings()
{
	int sta = 0, temp = 1, time = 0;
	char key, tabtemp = K_Tab;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK  Cancel=ESC");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
	//��ťͼ�ν���
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
		fflush(stdin);								//������̻�����
		FlushMouseMsgBuffer();						//�����껺����
		if (key != 0)
		{
			switch (key)
			{
			case -6:								//�������״̬
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
			case 13:								//����ENTER��
				K_Tab = tabtemp;
				return;
			case 27:								//����ESC��
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
//���������������
void K_Commands()
{
	char key, sta = 0, temp = 1;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
			case -6:								//�������״̬
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
			case 13:								//����ENTER��
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
//���ڰ�����������
void K_About()
{
	char key, sta = 0, temp = 1;
	//��ʼ����Ļ���
	K_Filesta = K_Menusta = 0;
	K_Print();
	//����״̬��
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 464, 640, 480);
	settextcolor(BLACK);
	setbkcolor(LIGHTGRAY);
	outtextxy(8, 464, "Enter=OK");
	//��������˵�ͼ�ν���
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
	//��ťͼ�ν���
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
			case -6:								//�������״̬
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
			case 13:								//����ENTER��
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
//�ı���ʾ��������
void K_View()
{
	int i, line, col, line1, col1;
	C_Node *p;
	L_Node *q;
	q = Hhead;
	col = line = 1;
	BeginBatchDraw();				//�������ƿ�ʼ
	settextcolor(LIGHTGRAY);
	setbkcolor(BLUE);
	setfillcolor(BLUE);
	solidrectangle(8, 32, 631, 463);
	for (i = 1; i < K_Hline; i++)			//��λ��K_Hline��
	{
		q = q->next1;
		line++;
	}
	do{
		p = q->next;
		while (p->ch != 13 && (col - K_Hcol) < 78)
		{
			//�ж����ı����ڵ��������
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
		for (i = 1; i < line; i++)		//��λline��
			q = q->next1;
		p = q->next;
		for (i = 1; i < col; i++)		//��λcol��
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
	EndBatchDraw();					//�������ƽ���
}
//�����ַ��жϺ�������
char K_Check(int m, int n)
{
	int i;
	L_Node *q;
	C_Node *p;
	q = Hhead;
	if (m < 1 || n < 1)
		return -1;							//�����ڷ���-1
	for (i = 1; i < m; i++)						//��λ��m��
	{
		if (q->next1 == NULL)
			return -1;						//�����ڷ���-1
		q = q->next1;
	}
	p = q->next;
	for (i = 1; i < n; i++)						//��λ��n��
	{
		if (p->next == NULL)
			return -1;						//�����ڷ���-1
		p = p->next;
	}
	if (p->ch == 13)
		return 13;							//�س�����13;
	if (p->ch>31 && p->ch < 127)
		return p->ch;						//���س����ַ�
	else return 0;							//�����ַ�����0
}
//�����ַ�������������
int K_Judge(int m)
{
	int i, num = 0;
	L_Node *q;
	C_Node *p;
	q = Hhead;
	for (i = 1; i < m; i++)
	{
		if (q == NULL) return -1;				//����-1��ʾ��ǰ�в�����
		q = q->next1;
	}
	p = q->next;
	while (p->next != NULL)
	{
		p = p->next;
		num++;
	}
	return num;								//���س����ַ���
}
//ɾ���ı���������
void K_Del(int m, int n)
{
	int i;
	L_Node *q, *q1;
	C_Node *p1, *p2;
	q = q1 = Hhead;
	K_Curmove(-3);
	//��1�� ��0�в����ڷ���
	if (n == 0 && m == 1) return;
	if (m > 1)
	{
		for (i = 1; i < m - 1; i++)	//��λ��m-1��
			q1 = q1->next1;
		q = q1->next1;
	}
	p1 = q->next;
	for (i = 1; i < n - 1; i++)		//��λ��n-1��
		p1 = p1->next;
	p2 = p1->next;
	i = K_Hcol;				//���
	if (n == 0)
	{
		K_Maxline--;
		p1 = q1->next;
		if (p1->ch != 13)		//m-1�в���ֻ��һ���س�
		{
			while (p1->next->ch != 13)
				p1 = p1->next;
			free(p1->next);
			p1->next = q->next;
		}
		else				//m-1�����ҽ���һ���س�
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
//�ַ����뺯������
void K_Insert(int m, int n, char word)
{
	int i;
	L_Node *q, *q1;
	C_Node *p, *p1;
	q = Hhead;
	if (K_Value != 0)			//�ж��Ƿ�ѡ��
	{
		K_Clear();
		m = K_Line;
		n = K_Col;
	}
	for (i = 1; i < m; i++)		//��λ��m��
		q = q->next1;
	p1 = q->next;
	for (i = 1; i < n - 1; i++)		//��λ��n��
		p1 = p1->next;
	p = (C_Node *)malloc(sizeof(C_Node));
	p->ch = word;
	if (n == 1)				//ǰ�����ַ�����
	{
		p->next = q->next;
		q->next = p;
	}
	else					//ǰ�����ַ�����
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
	K_Curmove(-4);			//�������
}
//����ѡ�к�������
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
		case -7:						//���ѡ��
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
		default:						//SHIFT+�����ַ�
			if (GetKeyState(VK_SHIFT) < 0 && isprint(key))
				K_Insert(K_Line, K_Col, key);
			break;
		}
		Sleep(10);
		K_Curflash();
		key = K_Input();
	}
	//���н���
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
//ѡ��ȡ����������
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

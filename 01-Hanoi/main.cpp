///////////////////////////////////////////////////
//����Ϸ��14��ʥ������ɣ����ҵĵ�һ��С��Ϸ��
//�ܵ�Ƭ����̵�Ӱ�죬�ȷ�ˢ����Ϸ���뷨��
//���汾ͨ���Ż���������Ϸ��˸��
//����汾ͨ��VC6.0���룬
//�˰汾ͨ��VS2013���롣

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
//�궨�峣�ùؼ���
#define uchar unsigned char
#define uint unsigned int
//��������
void gotoXY(int x, int y);//����ƶ���������
void bound();     //�ֽ��ߺ�������
char input();     //�������뺯������
void GUI();     //�û����溯������
void help();     //��Ϸ˵����������
bool opt();     //�Ѷ�ѡ��������
void game();     //��Ϸ������������
void print();     //��Ϸ��ʾ��������
void process();     //״̬����������
void win();     //ʤ����ֺ�������
//ȫ�ֱ�������
char hard, sta = 0, tower[3][11] = { 0 };			//hard(�Ѷ�ϵ������)   sta(״̬����)   tower(��Ϸ���ݱ���)
//������
int main()
{
	char i, j;
	system("title ���ǵĺ�ŵ��");               //�������ڱ���
	system("color f3");                         //����������ɫΪ�ױ�������
	system("mode con: cols=94 lines=18");      //�������ڴ�С�����	
	while (true)
	{
		GUI();
		if (opt())
		{
			while (true)
			{
				//�����ʼ������
				for (i = 0; i<3; i++)
					for (j = 0; j<10; j++)
						tower[i][j] = 0;
				tower[0][10] = -1;
				tower[1][10] = 0;
				tower[2][10] = 0;
				sta = 0;
				//��Ϸ��ʼ
				game();
				if (sta == -2)     //�������˵��ж�
					break;
				if (sta != -1 && sta != -2)     //��λ״̬��ʤ��״̬�ж�
				{
					win();
					break;
				}
			}
		}
	}
	return 0;
}
//����ƶ���������
void gotoXY(int x, int y){
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//�ֽ��ߺ�������
void bound()
{
	printf("----------------------------------------------------------------------------------------------");
}
//�������뺯������
char input()					//������ֵΪ1     ������ֵΪ2     ������ֵΪ3     ������ֵΪ4
{								//SPACE/ENTER����ֵΪ0     ESC����ֵΪ5     ��������ֵ-1
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
//�û����溯������
void GUI()
{
	char sta = 0, key, choose[7][20] = { "��ʼ��Ϸ", "-> ��ʼ��Ϸ <-", "��Ϸ˵��", "-> ��Ϸ˵�� <-", "������Ϸ", "-> ������Ϸ <-", "�� �� �� �� ŵ ��" };
	while (true)
	{
		system("cls");
		bound();
		if (sta == 0)					//�û�������ʾ
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
		if (key == 5)					//������������
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
//��Ϸ˵����������
void help()
{
	system("cls");
	bound();
	printf("                                       �� �� �� �� ŵ ��\n");
	bound();
	printf("\n             ��Ϸ˵��:�����������ķ�������м������ȫ�����Ƶ��������ϡ�\n\n");
	printf("             ��ϷҪ��:һ��ֻ��ȡһ�鷽��,�����С�ķ�����ֻ�ܷ��ñ�����С�ķ��顣\n");
	printf("\n\n\n\n\n");
	printf("            ��      ȡ����           ��     ���÷���         SPACE     ȷ��/����\n");
	printf("            ��     �������          ��     �������          ESC      ����/�˳�\n\n");
	bound();
	system("pause");
}
//�Ѷ�ѡ��������
bool opt()
{
	uchar key;
	while (true)
	{
		system("cls");
		bound();
		puts("\n\n\n\n\n\n                                    ����������Ҫ���Ѷ�(1~7):\n\n\n\n\n\n\n");
		bound();
		key = _getch();
		if (key == 27)					//����Ƿ񷵻�UI����
			return false;
		hard = key - 48;
		if (hard>0 && hard<8)
			return true;
	}
}
//��Ϸ������������
void game()
{
	for (char i = 0; i<hard; i++)	//��Ϸ��ʼ��
		tower[0][i] = hard - i;
	while (true)
	{
		print();
		process();
		if (sta == -1 || sta == -2)				//����Ƿ�Ϊ��λ״̬�򷵻�״̬
			break;
		if (tower[2][hard - 1] == 1)				//����Ƿ�ʤ��
		{
			print();
			system("pause");
			break;
		}
	}
}
//��Ϸ��ʾ��������
void print()
{
	gotoXY(0, 0);
	char i, j;
	bound();
	puts("                                       �� �� �� �� ŵ ��");
	bound();
	if (tower[0][10] == -1)				//��ӡ���
		printf("               ��                                                                            ");
	else if (tower[1][10] == -1)
		printf("                                              ��                                             ");
	else if (tower[2][10] == -1)
		printf("                                                                             ��              ");
	else if (tower[0][10] != 0)
	{
		for (i = 0; i<15 - tower[0][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[0][10] + 1; i++)
			printf("��");
		for (i = 0; i<76 - 2 * tower[0][10]; i++)
			printf(" ");
	}
	else if (tower[1][10] != 0)
	{
		for (i = 0; i<46 - tower[1][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[1][10] + 1; i++)
			printf("��");
		for (i = 0; i<45 - 2 * tower[1][10]; i++)
			printf(" ");
	}
	else
	{
		for (i = 0; i<77 - tower[2][10] * 2; i++)
			printf(" ");
		for (i = 0; i<2 * tower[2][10] + 1; i++)
			printf("��");
		for (i = 0; i<14 - 2 * tower[2][10]; i++)
			printf(" ");
	}
	printf("\n\n");
	for (i = 9; i >= 0; i--)					//��ӡ��Ϸ����
	{
		if (tower[0][i] == 0)
			printf("               ||              ");
		else
		{
			for (j = 0; j<15 - tower[0][i] * 2; j++)
				printf(" ");
			for (j = 0; j<2 * tower[0][i] + 1; j++)
				printf("��");
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
				printf("��");
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
				printf("��");
			for (j = 0; j<15 - tower[2][i] * 2; j++)
				printf(" ");
		}
	}
	bound();
}
//״̬����������
void process()
{
	char i, key;
	key = input();
	switch (key)				//��Ϸ������������
	{
	case 0: sta = -1; break;				//��λ״̬����
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
	case 5: sta = -2; break;				//����״̬����
	}
}
//ʤ����ֺ�������
void win()					//��ӡʤ������"WIN !"
{
	system("cls");
	bound();
	puts("\n\n\n\n                             ��  ��  ��  ������  ��      ��  ��");
	puts("                             ��  ��  ��    ��    ����    ��  ��");
	puts("                             ��  ��  ��    ��    ��  ��  ��  ��");
	puts("                             ��  ��  ��    ��    ��    ����");
	puts("                             ����������  ������  ��      ��  ��\n\n\n\n\n");
	bound();
	system("pause");
}

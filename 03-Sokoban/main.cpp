////////////////////////////////////////////////////////////
//����һ�������ӵĽ���С��Ϸ��
//���£���Դ����

//ͷ�ļ�����
#include"game.h"
#include<windows.h>
#include<graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

//������
int main()
{
	int i,num;//���α���
	IMAGE img;
	system("title ���ص���·��");
	Openfile();//�򿪴浵��ȡ����

	initgraph(640, 480);
	//��������
	loadimage(&img,"img/gui/enter");
	BeginBatchDraw();//��ʼ������ͼ
	setfillcolor(BLACK);
	for(i=96;i>=0;i--)
	{
		putimage(0,0,&img);
		solidcircle(320,240,i*10);
		FlushBatchDraw();//ִ��δ��ɵĻ�ͼ����
		Sleep(10);
	}
	Sleep(1000);
	EndBatchDraw();//����������ͼ
	TheSwitch();	

	//���ű�������
	PlaySound("sound/BGM/bgm1.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	while(true)
	{
		switch(MainInterface())
		{
		case 3://��ʼ��Ϸѯ���Ƿ�ȷ��ɾ���浵
			if(!TheMessage("��ʼ��Ϸ��ɾ��ԭ�ȵĴ浵���Ƿ������"))
				break;
		case 0://��ʼ��Ϸ
			BeginGame();
		case 2://������Ϸ
		
			while(true)
			{
				num=TheChapter();
				if(num==-1)
					break;
				//PlayGame����ֵΪfalse�ص����˵�������ֵΪtrue�ص��ؿ�����
				if(!PlayGame(num))
					break;
			}
			break;
		case 1:
		case 4://�˳���Ϸ
			ExitGame();
		}
		TheSwitch();//�л�����
	}
	closegraph();
	return 0;
}

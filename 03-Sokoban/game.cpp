//ͷ�ļ�����
#include"game.h"
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h> 
#include<string.h>
#include<windows.h>
#include<graphics.h>

//�浵���ݽṹ��
struct SavedData
{
	bool bIsSaved;//�Ƿ��д浵��־
	int iFinishChapter;//��ɵĹؿ���־
	time_t timer;//�浵����ʱ���־

	bool bIsPlay;//�Ƿ������Ϸ��־

	int iEndFlag;//���ս�ֱ�־
}mysave;

//�������ݽṹ��
typedef struct BlockData
{
	int num;//����ID
	IMAGE *img;
	BlockData * pNext;
}BlockData;
//��������ͷָ��(������ԴID������)
BlockData *pBlock=NULL;

//�ж����ݼ�¼�ṹ��
typedef struct MyStep
{
	int num;//�ж�����
	MyStep * pNext;
}MyStep;
//�ж����ݼ�¼����(�����ж�������)
MyStep *pStep=NULL;

//�����ݽṹ��
typedef struct ThePoint
{
	int x;
	int y;
}ThePoint;

//��ͼ���ݽṹ��
struct MapData
{
	ThePoint OriPoint;

	ThePoint MapSize1;
	char TheMap1[15][20];//��ͼ����
	int TheNum1;//Ŀ�����
	ThePoint MyPlace1[10];//Ŀ������

	ThePoint MapSize2;
	char TheMap2[15][20];//��ͼ����
	int TheNum2;//Ŀ�����
	ThePoint MyPlace2[10];//Ŀ������

	bool bIsTrueWorld;//�Ƿ���������
	ThePoint ThePlayer;//���λ��
}world;

//ȫ�ֱ�������
int iAtChapter;//�����ڵڼ���
int iStepNum;//����ɲ���
bool bIsWin;//�Ƿ�ʤ��

int LineSize,ColSize;
char (*themap)[20];

void Openfile()//�򿪴浵�ļ�����
{
	FILE *fp1,*fp2;//�ļ�ָ��
	struct SavedData tmp;//��ʱ�ṹ��

	if((fp1=fopen("save/save.dat","rb"))==NULL)
	{
		mysave.bIsSaved=false;
		mysave.iFinishChapter=0;
		mysave.iEndFlag=0;
		mysave.bIsPlay=false;
		//�½��浵��������
		SaveFile();
		return;
	}
	fread(&mysave,sizeof(mysave),1,fp1);
	//�򿪱����ļ�save.back
	if((fp2=fopen("save/save.back","rb"))!=NULL)
	{
		fread(&tmp,sizeof(mysave),1,fp2);
		if(tmp.timer-mysave.timer>0)
		{
			fclose(fp1);
			rewind(fp2);//�����ļ���ͷ
			fp1=fp2;
			fread(&mysave,sizeof(mysave),1,fp1);
		}
	}
	fclose(fp1);//�ر��ļ�
}

void SaveFile()//����浵�ļ�
{
	FILE *fp;//�ļ�ָ��
	MyStep *p;//�ж����ݼ�¼ָ��
	int iFlag=0;//�浵�ɹ�λ

	mysave.timer=time(NULL);//��ȡ��ǰʱ��
	if((fp=fopen("save/save.dat","wb"))!=NULL)
	{
		fwrite(&mysave,sizeof(mysave),1,fp);
		fclose(fp);//�ر��ļ�
		iFlag++;//�ɹ�����
	}
	if((fp=fopen("save/save.back","wb"))!=NULL)
	{
		fwrite(&mysave,sizeof(mysave),1,fp);
		fclose(fp);//�ر��ļ�
		iFlag++;//�ɹ�����
	}
	if(!iFlag)
	{
		TheMessage("�����󣡴浵�����ļ��洢ʧ�ܣ�����");
		ExitGame();
	}

	if(mysave.bIsPlay)
	{
		//�洢δ�����Ϸ��ͼ
		if((fp=fopen("save/map.dat","wb"))!=NULL)
		{
			putw(iAtChapter,fp);
			putw(iStepNum,fp);
			fwrite(&bIsWin,sizeof(bool),1,fp);
			fwrite(&world,sizeof(world),1,fp);
			fclose(fp);//�ر��ļ�
		}
		else
		{
			TheMessage("�����󣡴浵�����ļ��洢ʧ�ܣ�����");
			ExitGame();
		}
		//����δ�����Ϸ�ж�
		if((fp=fopen("save/step.dat","wb"))!=NULL)
		{
			p=pStep;
			while(p!=NULL)
			{
				putw(p->num,fp);
				p=p->pNext;
			}
			fclose(fp);
		}
		else
		{
			TheMessage("�����󣡴浵�����ļ��洢ʧ�ܣ�����");
			ExitGame();
		}
	}
}

char KeyInput(int mode)		//mode==0 {����ȴ�ģʽ} ; mode==1 {ʵʱ���ģʽ}
{							//������ֵΪ1     ������ֵΪ2     ������ֵΪ3     ������ֵΪ4
	uchar key1,key2;		//Esc����ֵΪ0 Sapce&&Enter����ֵΪ5     R������ֵΪ6     F1����ֵΪ7
	if(!mode||(mode&&kbhit()))
	{
		key1=getch();
		if(key1==27)
			return 0;
		if(key1==32||key1==13)
			return 5;
		if(key1=='r'||key1=='R')
			return 6;
		//����Ƿ�Ϊ�����
		if(key1==0||key1==224)
			key2=getch();
		if(key1==0&&key2==59)
			return 7;
		else if(key1==224)
		{
			switch(key2)
			{
			case 72: return 1;
			case 80: return 2;
			case 75: return 3;
			case 77: return 4;
			}
		}
	}
	return  -1;//mode==1ʱ,����ֵΪ-1��ʾû������
}

void TheSwitch()//�л���������
{
	int i;//���α���

	//return;

	setfillcolor(BLACK);
	for(i=0;i<=96;i++)
	{
		solidcircle(320,240,i*10);
		Sleep(10);
	}
}

int MainInterface()//�����溯������
{
	int GuiSta=-1,iGuiSta;//������״̬��־
	char cInputKey;//���������־λ
	char sGuiPath[]="img/gui/gui0";//GUI������Դ·��

	if(mysave.bIsSaved)//������״̬��ʼ��
		iGuiSta=2;
	else
		iGuiSta=0;

	while(true)
	{
		if(GuiSta!=iGuiSta)
		{
			sGuiPath[11]=iGuiSta+48;//����ת��Ϊ�ַ���
			loadimage(NULL,sGuiPath);//����GUI��Դ
			GuiSta=iGuiSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//���봦��
		{
		case 1:
		case 2://���°�������
			if(mysave.bIsSaved)
			{
				GuiSta>2&&cInputKey==1? iGuiSta--:0;
				GuiSta<4&&cInputKey==2? iGuiSta++:0;	
			}
			else
			{
				GuiSta>0&&cInputKey==1? iGuiSta--:0;
				GuiSta<1&&cInputKey==2? iGuiSta++:0;
			}
			break;
		case 5://ȷ�ϰ�������
			return GuiSta;
		case 0://���ذ�������
			ExitGame();
		}
	}
}

int TheChapter()//�ؿ����溯������
{
	int i,ChapterSta=-1,iChapterSta;//�½ڱ�־

	IMAGE img_Title,img_Chapter,img_Map;
	char cInputKey;//���������־λ
	char sChapter[30];
	char sMap[30];
	char sChange[30];

	FILE *fp;//�ļ�����
	char sTitleName[30];

	TheSwitch();//�л�����

	if(mysave.bIsPlay)//�浵������Ϸ��־Ϊ��
	{
		//���ؼ�����Ϸ��ͼ�浵
		if((fp=fopen("save/map.dat","rb"))==NULL)
		{
			TheMessage("�����󣡵�ͼ�浵�ļ�����ʧ�ܣ�����");
			ExitGame();
		}
		//����δ��ɹؿ��Ͳ���
		iAtChapter=getw(fp);
		fclose(fp);
		return iAtChapter;
	}
	//�򿪱������������ļ�
	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("�����󣡱�����Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}

	iChapterSta=mysave.iFinishChapter;//״̬��ʼ��
	loadimage(&img_Title,"img/chapter/title");//���������Դ

	while(true)
	{
		if(ChapterSta!=iChapterSta)
		{
			BeginBatchDraw();//��ʼ������ͼ
			putimage(0, 0, &img_Title);//��ʾ����
			rewind(fp);//�����ļ���ͷ
			for(i=0;i<=iChapterSta;i++)
				fscanf(fp,"%s",sTitleName);//��ȡ�ļ����
			settextstyle(40,20,"����������");//�����ʼ��
			setbkmode(TRANSPARENT);//�������屳��ģʽΪ͸��
			settextcolor(BLACK);//����������ɫ
			outtextxy((640-textwidth(sTitleName))/2,5,sTitleName);

			sprintf(sChapter,"%s%d","img/chapter/chapter",iChapterSta);
			loadimage(&img_Chapter,sChapter);
			putimage(0, 50, &img_Chapter);//��ʾ�½ڵ�ͼ

			sprintf(sMap,"%s%d","img/map/chapter",iChapterSta);
			loadimage(&img_Map,sMap);
			putimage(0, 330, &img_Map);//��ʾ�����ͼ
			EndBatchDraw();//����������ͼ

			ChapterSta=iChapterSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//���봦��
		{
		case 3://���Ұ�������
			if(ChapterSta>0)
			{
				iChapterSta--;
				//�л�����
				for(i=0;i<=18;i++)
				{
					sprintf(sChange,"%s%d","img/map/map",i);
					loadimage(&img_Map,sChange);
					putimage(0, 330, &img_Map);
					Sleep(5);
				}
			}
			break;
		case 4:
			if(ChapterSta<mysave.iFinishChapter)
			{
				iChapterSta++;
				//�л�����
				for(i=18;i>=0;i--)
				{
					sprintf(sChange,"%s%d","img/map/map",i);
					loadimage(&img_Map,sChange);
					putimage(0, 330, &img_Map);
					Sleep(5);
				}
			}
			break;
		case 5://ȷ�ϰ�������
			fclose(fp);//�ر��ļ�
			return ChapterSta;
		case 6:
			for(i=50;i&&GetKeyState('R')<0;i--)
				Sleep(10);
			if(i==0&&ChapterSta!=0&&ChapterSta!=11)
			{
				RePlay(ChapterSta);
				ChapterSta=-1;//״̬�ı�ˢ�»���
			}
			break;
		case 0://���ذ�������
			fclose(fp);//�ر��ļ�
			return -1;
		}
	}

	return 0;
}

bool TheMessage(char *sMessages)//��Ϣ��������
{
	int MessageSta=-1,iMessageSta=0;
	IMAGE img_State;
	char cInputKey;///���������־λ
	char sState[]="img/gui/state0";
	
	settextstyle(40,20,"����������");//�����ʼ��
	settextcolor(WHITE);//����������ɫ
	setbkmode(TRANSPARENT);//�������屳��ģʽΪ͸��

	setbkcolor(BLACK);
	cleardevice();//����豸
	RECT rect={80,100,560,300};//�����Ϣ����Ϣ
	drawtext(sMessages,&rect,DT_WORDBREAK);

	while(true)
	{

		if(MessageSta!=iMessageSta)
		{
			sState[13]=iMessageSta+48;//����ת��Ϊ�ַ���
			loadimage(&img_State,sState);//����״̬��Դ
			putimage(0,400,&img_State);
			MessageSta=iMessageSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//���봦��
		{
		case 3:
			iMessageSta=0;
			break;
		case 4:
			iMessageSta=1;
			break;
		case 5:
			if(MessageSta==0)
				return true;
		case 0:
			return false;
		}
	}
}

void BeginGame()//��ʼ��Ϸ����
{
	//���ݳ�ʼ��
	mysave.bIsSaved=true;
	mysave.iFinishChapter=1;
	mysave.iEndFlag=0;
	mysave.bIsPlay=false;
	SaveFile();
	//ɾ���ж���¼�ļ���
	//system("rmdir /s /q data/record");
	//mkdir("data/record");

	PlayGame(0);//�������¶���
	TheHelp();//��Ϸ����
}

void PlayMovie(char *sMoviePath)//�������ź���
{
	/*FILE *fp;//�ļ�ָ��
	IMAGE img_CG;
	int num,time,x,y;//���α���
	char sPlayPath[30];//������Դ·��
	char sTmp[30];//��ʱ�����ַ���
	sprintf(sPlayPath,"%s%s",sMoviePath,"/play.dat");
	if((fp=fopen(sPlayPath,"r"))==NULL)
	{
		TheMessage("�����󣡶�����Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}

	while(!feof(fp))
	{
		fscanf(fp,"%d",&num);
		switch(num)
		{
		case 0://����ͼƬ
			break;
		case 2://��չ�����
			break;
		case 3://��ʾ����
			break;
		case 4://������Ч
			break;
		case 5://��������
			break;
		}
	}
	fclose(fp);*/
}                
     
bool PlayGame(int num)//��Ϸ��ʼ����
{
	FILE *fp;//�ļ�ָ��
	MyStep *p;//�ж�ָ��
	int i;//���α���
	char sTitleName[30];
	char sRecord[30];
	char cInputKey;//������־
	ThePoint Tpoint1,Tpoint2;

	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("�����󣡱�����Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}
	else
	{
		rewind(fp);//�����ļ���ͷ
		for(i=0;i<=num;i++)
			fscanf(fp,"%s",sTitleName);//��ȡ�ļ����
		settextstyle(40,20,"����������");//�����ʼ��
		settextcolor(WHITE);//����������ɫ
		setbkmode(TRANSPARENT);//�������屳��ģʽΪ͸��

		setbkcolor(BLACK);//���ñ���ɫ
		cleardevice();//����豸
		outtextxy((640-textwidth(sTitleName))/2,200,sTitleName);
		Sleep(2000);//��ʾ������ӳ�����
		fflush(stdin);//������̻�������ע��û��Ч����

		fclose(fp);//�ر��ļ�
	}

	switch(num)
	{
	case 0:
		PlayMovie("movie/OP");
		return true;
	case 11:
		if(mysave.iEndFlag>5)
			PlayMovie("movie/ED1");
		else
			PlayMovie("movie/ED2");
		return true;
	default://���ص�ͼ����
		LoadGame(num);
	}

	TheSwitch();//�л�����

	//��Ϸ�������Ĳ���
	PrintGame();
	while(true)
	{
 		cInputKey=KeyInput(0);
		switch(cInputKey)
		{
		case 1:
			Tpoint1.x=world.ThePlayer.x-1;
			Tpoint1.y=world.ThePlayer.y;
			Tpoint2.x=world.ThePlayer.x-2;
			Tpoint2.y=world.ThePlayer.y;
			break;
		case 2:
			Tpoint1.x=world.ThePlayer.x+1;
			Tpoint1.y=world.ThePlayer.y;
			Tpoint2.x=world.ThePlayer.x+2;
			Tpoint2.y=world.ThePlayer.y;
			break;
		case 3:
			Tpoint1.x=world.ThePlayer.x;
			Tpoint1.y=world.ThePlayer.y-1;
			Tpoint2.x=world.ThePlayer.x;
			Tpoint2.y=world.ThePlayer.y-2;
			break;
		case 4:
			Tpoint1.x=world.ThePlayer.x;
			Tpoint1.y=world.ThePlayer.y+1;
			Tpoint2.x=world.ThePlayer.x;
			Tpoint2.y=world.ThePlayer.y+2;
			break;
		case 5://�����л�
			if(world.bIsTrueWorld&&
				(world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==3)||
				!world.bIsTrueWorld&&
				(world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==3))
			{
				world.bIsTrueWorld=!world.bIsTrueWorld;
				PrintGame();//�ı������ػ�����

				AddStep(5);//����ж�����
			}
			continue;
		case 6://�ؿ���Ϸ
			for(i=50;i&&GetKeyState('R')<0;i--)
				Sleep(10);
			if(i==0)
			{
				LoadGame(num);//���¼��ص�ͼ
				PrintGame();//ˢ�������ػ�����
			}
			continue;
		case 7:
			TheHelp();//��Ϸ����
			TheSwitch();//�л�����
			PrintGame();
			continue;
		case 0:
			switch(TheBack())
			{
			case 1:
				mysave.bIsPlay=false;
				return true;
			case 2:
				//���������Ϸ��ͼ�浵
				if((fp=fopen("save/map.dat","wb"))==NULL)
				{
					TheMessage("��������Ϸ����ʧ�ܣ�����");
					return false;
				}
				//����δ��ɹؿ��Ͳ���
				putw(iAtChapter,fp);
				putw(iStepNum,fp);
				fwrite(&bIsWin,sizeof(bool),1,fp);
				fwrite(&world,sizeof(world),1,fp);
				fclose(fp);

				mysave.bIsPlay=true;
				SaveFile();//����浵
				return false;
			case 0:
				TheSwitch();//�л�����
				PrintGame();//�ػ�����
				break;
			}
		default:
			continue;
		}
		//����ƶ�
		if(themap[Tpoint1.x][Tpoint1.y]==2||themap[Tpoint1.x][Tpoint1.y]==3)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;		
		}
		//�ƶ�����
		else if((themap[Tpoint1.x][Tpoint1.y]==4||themap[Tpoint1.x][Tpoint1.y]==5)&&
			(Tpoint2.x>=0&&Tpoint2.x<LineSize&&Tpoint2.y>=0&&Tpoint2.y<ColSize)&&
			(themap[Tpoint2.x][Tpoint2.y]==2||themap[Tpoint2.x][Tpoint2.y]==3))
		{
			themap[Tpoint1.x][Tpoint1.y]-=2;
			themap[Tpoint2.x][Tpoint2.y]+=2;
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			IsWin();//�ж��������Ƿ��������
		}
		//�����Ϸ
		else if(bIsWin&&themap[Tpoint1.x][Tpoint1.y]==6)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			AddStep(cInputKey);//����ж�����
			iStepNum++;//�����ۼ�
			//���ս�ֱ�־��һ
			if(world.bIsTrueWorld&&mysave.iFinishChapter==iAtChapter)
				mysave.iEndFlag++;
			//�ؿ���ɱ�־��һ
			if(mysave.iFinishChapter<11&&mysave.iFinishChapter==iAtChapter)
				mysave.iFinishChapter++;
			//���ݴ浵����
			mysave.bIsPlay=false;
			SaveFile();
			//�����¼�¼
			sprintf(sRecord,"%s%d%s","data/record/record",num,".dat");
			i=(LoadStep(1,sRecord));//ԭ��¼�ж���
			if(i<=0||iStepNum<i)
			{
				if((fp=fopen(sRecord,"wb"))!=NULL)
				{
					p=pStep;
					while(p!=NULL)
					{
						putw(p->num,fp);
						p=p->pNext;
					}
					fclose(fp);
				}
			}
			//ˢ��������ʾ
			PrintGame();
			Sleep(500);//��ʱ��ʾ
 			return true;
		}
		else continue;

		AddStep(cInputKey);//����ж�����

		iStepNum++;//�����ۼ�
		PrintGame();//ˢ������
	}
	return true;
}

void RePlay(int num)//��¼�طź���
{
	FILE *fp;//�ļ�ָ��
	MyStep *p;//�ж�ָ��
	int i;//���α���
	char sTitleName[30];
	char sRecord[30];
	char cInputKey;//������־
	ThePoint Tpoint1,Tpoint2;

	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("�����󣡱�����Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}
	else
	{
		rewind(fp);//�����ļ���ͷ
		for(i=0;i<=num;i++)
			fscanf(fp,"%s",sTitleName);//��ȡ�ļ����
		settextstyle(40,20,"����������");//�����ʼ��
		settextcolor(WHITE);//����������ɫ
		setbkmode(TRANSPARENT);//�������屳��ģʽΪ͸��

		setbkcolor(BLACK);//���ñ���ɫ
		cleardevice();//����豸
		outtextxy((640-textwidth(sTitleName))/2,200,sTitleName);
		Sleep(2000);//��ʾ������ӳ�����
		fflush(stdin);//������̻�������ע��û��Ч����

		fclose(fp);//�ر��ļ�
	}

	//���ص�ͼ����
	LoadGame(num);
	//�����ж�����
	sprintf(sRecord,"data/record/record%d.dat",num);
	if(LoadStep(0,sRecord)<=0)
	{
		TheMessage("�񱾹ؿ���δ�����¼�������ز���");
		return;
	}
	p=pStep;//�ж�����ָ���ʼ��

	TheSwitch();
	//��Ϸ�������Ĳ���
	PrintGame();
	while(true)
	{
 		if(KeyInput(1)==5)
		{
			Sleep(500);
			TheSwitch();//�л�����
			return;
		}
		if(p!=NULL)
		{
			cInputKey=p->num;
			p=p->pNext;
		}
		Sleep(500);//��ʱ��ʾ
		switch(cInputKey)
		{
		case 1:
			Tpoint1.x=world.ThePlayer.x-1;
			Tpoint1.y=world.ThePlayer.y;
			Tpoint2.x=world.ThePlayer.x-2;
			Tpoint2.y=world.ThePlayer.y;
			break;
		case 2:
			Tpoint1.x=world.ThePlayer.x+1;
			Tpoint1.y=world.ThePlayer.y;
			Tpoint2.x=world.ThePlayer.x+2;
			Tpoint2.y=world.ThePlayer.y;
			break;
		case 3:
			Tpoint1.x=world.ThePlayer.x;
			Tpoint1.y=world.ThePlayer.y-1;
			Tpoint2.x=world.ThePlayer.x;
			Tpoint2.y=world.ThePlayer.y-2;
			break;
		case 4:
			Tpoint1.x=world.ThePlayer.x;
			Tpoint1.y=world.ThePlayer.y+1;
			Tpoint2.x=world.ThePlayer.x;
			Tpoint2.y=world.ThePlayer.y+2;
			break;
		case 5://�����л�
			if(world.bIsTrueWorld&&
				(world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==3)||
				!world.bIsTrueWorld&&
				(world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==3))
			{
				world.bIsTrueWorld=!world.bIsTrueWorld;
				PrintGame();//�ı������ػ�����
			}
			continue;
		}
		//����ƶ�
		if(themap[Tpoint1.x][Tpoint1.y]==2||themap[Tpoint1.x][Tpoint1.y]==3)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;		
		}
		//�ƶ�����
		else if((themap[Tpoint1.x][Tpoint1.y]==4||themap[Tpoint1.x][Tpoint1.y]==5)&&
			(Tpoint2.x>=0&&Tpoint2.x<LineSize&&Tpoint2.y>=0&&Tpoint2.y<ColSize)&&
			(themap[Tpoint2.x][Tpoint2.y]==2||themap[Tpoint2.x][Tpoint2.y]==3))
		{
			themap[Tpoint1.x][Tpoint1.y]-=2;
			themap[Tpoint2.x][Tpoint2.y]+=2;
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			IsWin();//�ж��������Ƿ��������
		}
		//�����Ϸ
		else if(bIsWin&&themap[Tpoint1.x][Tpoint1.y]==6)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			iStepNum++;//�����ۼ�
			//ˢ��������ʾ
			PrintGame();
			Sleep(500);//��ʱ��ʾ
			//�л�����
			TheSwitch();
 			return;
		}
		else continue;

		iStepNum++;//�����ۼ�
		PrintGame();//ˢ������
	}
}
//�ж����ݼ�¼���غ���
int LoadStep(int mode,char *path)//modeΪ0-�������� modeΪ1-ֻ����������
{
	int num=0,tmp;
	FILE *fp;//�ļ�ָ��
	MyStep *p=pStep;
	//�����ж����ݼ�¼
	if((fp=fopen(path,"rb"))==NULL)
		return -1;
	//�ж����ݶ�ȡ
	tmp=getw(fp);
	if(mode==0)
	{
		while(!feof(fp))
		{
			if(pStep==NULL)
				p=pStep=(MyStep *)malloc(sizeof(MyStep));
			else
				p=p->pNext=(MyStep *)malloc(sizeof(MyStep));
			p->num=tmp;
			//�ж���������
			if(p->num!=5)
				num++;
			tmp=getw(fp);
		}
		if(p!=NULL)//��ֹҰָ��
		p->pNext=NULL;
	}
	else
	{
		while(!feof(fp))
		{
			//�ж���������
			if(tmp!=5)
				num++;
			tmp=getw(fp);
		}
	}
	fclose(fp);
	return num;//�����ж�����
}

void LoadGame(int num)//��Ϸ���غ���
{
	FILE *fp;//�ļ��ṹ��ָ��
	char sMapPath[30];
	char sBlockPath[30];
	char sTemp[30];

	BlockData *p=pBlock;//������Դָ��

	//���ط�����ԴID
	if(pBlock==NULL)
	{
		if((fp=fopen("data/block.dat","r"))==NULL)
		{
			TheMessage("�����󣡷�����ԴID�ļ�����ʧ�ܣ�����");
			ExitGame();
		}
		while(!feof(fp))
		{
			if(pBlock==NULL)
				p=pBlock=(BlockData *)malloc(sizeof(BlockData));
			else
				p=p->pNext=(BlockData *)malloc(sizeof(BlockData));

			fscanf(fp,"%d %s",&p->num,sTemp);
			sprintf(sBlockPath,"img/block/%s",sTemp);
			p->img=new IMAGE;//������Դ����
			loadimage(p->img,sBlockPath);//������Դ
			
		}
		if(p!=NULL)
			p->pNext=NULL;
		fclose(fp);
		
	}	
	//��ȫ��ͼ��Դ·��
	sprintf(sMapPath,"%s%d%s","data/map/map",num,".dat");
	
	if(mysave.bIsPlay)//�浵������Ϸ��־Ϊ��
	{
		//�����ж����ݼ�¼
		if(LoadStep(0,"save/step.dat")==-1)
		{
			TheMessage("�������ж����ݼ�¼�ļ�����ʧ�ܣ�����");
			ExitGame();
		}
		//���ؼ�����Ϸ��ͼ�浵
		if((fp=fopen("save/map.dat","rb"))==NULL)
		{
			TheMessage("�����󣡵�ͼ�浵�ļ�����ʧ�ܣ�����");
			ExitGame();
		}
		//����δ��ɹؿ��Ͳ���
		iAtChapter=getw(fp);
		iStepNum=getw(fp);
		fread(&bIsWin,sizeof(bool),1,fp);
		//���ݼ��غ���λΪfalse
		mysave.bIsPlay=false;
	}
	//���ص�ͼ��Դ
	else if((fp=fopen(sMapPath,"rb"))==NULL)
	{
		TheMessage("�����󣡵�ͼ��Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}
	else//����δ��ɹؿ��Ͳ���
	{
		iAtChapter=num;
		iStepNum=0;
		FreeStep();//ˢ���ж�����
		bIsWin=false;
	}
	fread(&world,sizeof(world),1,fp);
	fclose(fp);
	return;
}

IMAGE * GetMyImg(int bID)//block��Դ����
{
	BlockData *p=pBlock;
	//��ͼID����ԴIDת��
	if(world.bIsTrueWorld)
	{
		switch(bID)
		{
		case 1:
			bID=WALL;
			break;
		case 2:
			bID=PATH;
			break;
		case 3:
			bID=PLACE;
			break;
		case 4:
			bID=LAMP_OFF;
			break;
		case 5:
			bID=LAMP_ON;
			break;
		case 6:
			if(bIsWin)
				bID=PATH;
			else
				bID=DOOR_WOOD;
			break;
		case 7:
			bID=PLAYER;
			break;
		default:
			return NULL;
		}
	}
	else switch(bID)
	{
		case 1:
			bID=WALL_I;
			break;
		case 2:
			bID=PATH_I;
			break;
		case 3:
			bID=PLACE_I;
			break;
		case 4:
			bID=STONE_BLUE;
			break;
		case 5:
			bID=STONE_RED;
			break;
		case 6:
			if(bIsWin)
				bID=PATH_I;
			else
				bID=DOOR_IRON;
			break;
		case 7:
			bID=PLAYER;
			break;
		default:
			return NULL;
	}
	//��ѯ������Դָ��
	while(p)
	{
		if(p->num==bID)
			return p->img;
		p=p->pNext;
	}

	return NULL;
}

void IsWin()//ʤ���жϺ���
{
	int i;
	bIsWin=true;//��ʼ����Ϊ��
	for(i=0;i<world.TheNum1;i++)
	{
		if(world.TheMap1[world.MyPlace1[i].x][world.MyPlace1[i].y]!=5)
		{
			bIsWin=false;
			return;
		}
	}
	for(i=0;i<world.TheNum2;i++)
	{
		if(world.TheMap2[world.MyPlace2[i].x][world.MyPlace2[i].y]!=5)
		{
			bIsWin=false;
			return;
		}
	}
}

void PrintGame()//��Ϸ��ʾ����
{
	int i,j;
	char sTitleName[30];
	FILE *fp;//�ļ�ָ��
	IMAGE *img;//ͼ��ָ��

	//�򿪱����ļ�
	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("�����󣡱�����Դ�ļ�����ʧ�ܣ�����");
		ExitGame();
	}
	settextstyle(24,12,"����������");//�����ʼ��
	setbkmode(TRANSPARENT);//�������屳��ģʽΪ͸��
	for(i=0;i<=iAtChapter;i++)
				fscanf(fp,"%s",sTitleName);//��ȡ�ļ����
	settextcolor(BLACK);//����������ɫ

	//��ʼ��������
	BeginBatchDraw();
	//�ж��Ƿ�����ʵ����
	if(world.bIsTrueWorld)
	{
		loadimage(NULL,"img/block/world1.bmp");
		LineSize=world.MapSize1.x;
		ColSize=world.MapSize1.y;
		themap=world.TheMap1;
	}
	else
	{
		loadimage(NULL,"img/block/world2.bmp");
		LineSize=world.MapSize2.x;
		ColSize=world.MapSize2.y;
		themap=world.TheMap2;
	}
	

	if(world.bIsTrueWorld&&
		(world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==2||
		world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==3)||
		!world.bIsTrueWorld&&
		(world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==2||
		world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==3))
		outtextxy(148,132,"��");
	else
		outtextxy(148,132,"��");
	//���ر��ر���
	outtextxy((250-textwidth(sTitleName+8))/2,50,sTitleName+8);
	sprintf(sTitleName,"%4d ��",iStepNum);
	outtextxy(120,195,sTitleName);
	//���ص�ͼ�С�
	for(i=0;i<LineSize;i++)
		for(j=0;j<ColSize;j++)
			if((img=GetMyImg(themap[i][j]))!=NULL)
				putimage(world.OriPoint.y+32*j,world.OriPoint.x+32*i,img);

	//���������Դ
	putimage(world.OriPoint.y+32*world.ThePlayer.y,world.OriPoint.x+32*world.ThePlayer.x,GetMyImg(7));
	//������������
	EndBatchDraw();
}

int TheBack()//��Ϸ��ͣ����
{
	int BackSta=-1,iBackSta=0;
	char sBackPath[30];
	char cInputKey;//������־

	TheSwitch();//�л�����

	while(true)
	{
		if(BackSta!=iBackSta)
		{
			sprintf(sBackPath,"%s%d%s","img/back/back",iBackSta,".bmp");
			loadimage(NULL,sBackPath);
			BackSta=iBackSta;
		}

		cInputKey=KeyInput(0);
		switch(cInputKey)
		{
		case 1:
			if(BackSta>0)
				iBackSta--;
			break;
		case 2:
			if(BackSta<2)
				iBackSta++;
			break;
		case 5:
			switch(BackSta)
			{
			case 1:
				if(TheMessage("��ѡ��ؿ���ʧȥ���еĽ��ȣ��Ƿ������"))
					return BackSta;
				BackSta=-1;//����ˢ�½���
				break;
			case 2:
				if(TheMessage("��Ҫ������Ȳ��˻ز˵����Ƿ������"))
					return BackSta;
				BackSta=-1;//����ˢ�½���
				break;
			case 0:
				return BackSta;
			}
			break;
		case 0:
			return 0;
		}
	}
}

void TheHelp()//��Ϸ��������
{
	int HelpSta=-1,iHelpSta=0;
	char sHelpPath[30];
	char cInputKey;//������־

	TheSwitch();//�л�����

	while(true)
	{
		if(HelpSta!=iHelpSta)
		{
			sprintf(sHelpPath,"%s%d%s","img/help/help",iHelpSta,".bmp");
			loadimage(NULL,sHelpPath);
			HelpSta=iHelpSta;
		}

		cInputKey=KeyInput(0);
		switch(cInputKey)
		{
		case 3:
			if(HelpSta>0)
				iHelpSta--;
			break;
		case 4:
			if(HelpSta<2)
			{
				iHelpSta++;
				break;
			}
		case 0:
			return;
		}
	}
}

void AddStep(int num)//�ж���¼��Ӻ���
{
	MyStep *p=pStep;//�ж�����ָ��

	if(pStep!=NULL)
		while(p->pNext!=NULL)
			p=p->pNext;

	if(pStep==NULL)
		p=pStep=(MyStep *)malloc(sizeof(MyStep));
	else
		p=p->pNext=(MyStep *)malloc(sizeof(MyStep));

	p->num=num;
	p->pNext=NULL;
}

void FreeStep()//�ж���¼�ͷź���
{
	MyStep *p1,*p2;//�ж�����ָ��
	p1=p2=pStep;//ָ���ʼ��
	while(p1!=NULL)
	{
		p2=p2->pNext;
		free(p1);
		p1=p2;
	}
	pStep=NULL;//��ֹҰָ��
}

void ExitGame()//��Ϸ�˳�����
{
	BlockData *p1,*p2;//��������ָ��
	p1=p2=pBlock;//ָ���ʼ��
	//�ͷ���ԴID�ڴ���Դ
	while(p1!=NULL)
	{
		p2=p2->pNext;
		free(p1->img);//�ͷ���Դ
		free(p1);//�ͷ�����ڵ�
		p1=p2;
	}
	pBlock=NULL;//��ֹҰָ��
	FreeStep();//�ͷ��ж���¼
	TheSwitch();//�л�����
	//�˳���Ϸ�ͻ���
	exit(0);
}

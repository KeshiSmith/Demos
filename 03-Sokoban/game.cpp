//头文件声明
#include"game.h"
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<direct.h> 
#include<string.h>
#include<windows.h>
#include<graphics.h>

//存档数据结构体
struct SavedData
{
	bool bIsSaved;//是否有存档标志
	int iFinishChapter;//完成的关卡标志
	time_t timer;//存档保存时间标志

	bool bIsPlay;//是否继续游戏标志

	int iEndFlag;//最终结局标志
}mysave;

//方块数据结构体
typedef struct BlockData
{
	int num;//方块ID
	IMAGE *img;
	BlockData * pNext;
}BlockData;
//方块数据头指针(建立资源ID链表用)
BlockData *pBlock=NULL;

//行动数据记录结构体
typedef struct MyStep
{
	int num;//行动方向
	MyStep * pNext;
}MyStep;
//行动数据记录数据(建立行动链表用)
MyStep *pStep=NULL;

//点数据结构体
typedef struct ThePoint
{
	int x;
	int y;
}ThePoint;

//地图数据结构体
struct MapData
{
	ThePoint OriPoint;

	ThePoint MapSize1;
	char TheMap1[15][20];//地图数据
	int TheNum1;//目标个数
	ThePoint MyPlace1[10];//目标数据

	ThePoint MapSize2;
	char TheMap2[15][20];//地图数据
	int TheNum2;//目标个数
	ThePoint MyPlace2[10];//目标数据

	bool bIsTrueWorld;//是否在外世界
	ThePoint ThePlayer;//玩家位置
}world;

//全局变量声明
int iAtChapter;//现在在第几关
int iStepNum;//已完成步数
bool bIsWin;//是否胜利

int LineSize,ColSize;
char (*themap)[20];

void Openfile()//打开存档文件函数
{
	FILE *fp1,*fp2;//文件指针
	struct SavedData tmp;//临时结构体

	if((fp1=fopen("save/save.dat","rb"))==NULL)
	{
		mysave.bIsSaved=false;
		mysave.iFinishChapter=0;
		mysave.iEndFlag=0;
		mysave.bIsPlay=false;
		//新建存档保存数据
		SaveFile();
		return;
	}
	fread(&mysave,sizeof(mysave),1,fp1);
	//打开备份文件save.back
	if((fp2=fopen("save/save.back","rb"))!=NULL)
	{
		fread(&tmp,sizeof(mysave),1,fp2);
		if(tmp.timer-mysave.timer>0)
		{
			fclose(fp1);
			rewind(fp2);//返回文件开头
			fp1=fp2;
			fread(&mysave,sizeof(mysave),1,fp1);
		}
	}
	fclose(fp1);//关闭文件
}

void SaveFile()//保存存档文件
{
	FILE *fp;//文件指针
	MyStep *p;//行动数据记录指针
	int iFlag=0;//存档成功位

	mysave.timer=time(NULL);//获取当前时间
	if((fp=fopen("save/save.dat","wb"))!=NULL)
	{
		fwrite(&mysave,sizeof(mysave),1,fp);
		fclose(fp);//关闭文件
		iFlag++;//成功储存
	}
	if((fp=fopen("save/save.back","wb"))!=NULL)
	{
		fwrite(&mysave,sizeof(mysave),1,fp);
		fclose(fp);//关闭文件
		iFlag++;//成功储存
	}
	if(!iFlag)
	{
		TheMessage("△错误！存档数据文件存储失败！！！");
		ExitGame();
	}

	if(mysave.bIsPlay)
	{
		//存储未完成游戏地图
		if((fp=fopen("save/map.dat","wb"))!=NULL)
		{
			putw(iAtChapter,fp);
			putw(iStepNum,fp);
			fwrite(&bIsWin,sizeof(bool),1,fp);
			fwrite(&world,sizeof(world),1,fp);
			fclose(fp);//关闭文件
		}
		else
		{
			TheMessage("△错误！存档数据文件存储失败！！！");
			ExitGame();
		}
		//储存未完成游戏行动
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
			TheMessage("△错误！存档数据文件存储失败！！！");
			ExitGame();
		}
	}
}

char KeyInput(int mode)		//mode==0 {输入等待模式} ; mode==1 {实时检测模式}
{							//↑返回值为1     ↓返回值为2     ←返回值为3     →返回值为4
	uchar key1,key2;		//Esc返回值为0 Sapce&&Enter返回值为5     R键返回值为6     F1返回值为7
	if(!mode||(mode&&kbhit()))
	{
		key1=getch();
		if(key1==27)
			return 0;
		if(key1==32||key1==13)
			return 5;
		if(key1=='r'||key1=='R')
			return 6;
		//检测是否为特殊键
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
	return  -1;//mode==1时,返回值为-1表示没有输入
}

void TheSwitch()//切换动画函数
{
	int i;//整形变量

	//return;

	setfillcolor(BLACK);
	for(i=0;i<=96;i++)
	{
		solidcircle(320,240,i*10);
		Sleep(10);
	}
}

int MainInterface()//主界面函数定义
{
	int GuiSta=-1,iGuiSta;//主界面状态标志
	char cInputKey;//按键输入标志位
	char sGuiPath[]="img/gui/gui0";//GUI界面资源路径

	if(mysave.bIsSaved)//主界面状态初始化
		iGuiSta=2;
	else
		iGuiSta=0;

	while(true)
	{
		if(GuiSta!=iGuiSta)
		{
			sGuiPath[11]=iGuiSta+48;//整型转化为字符型
			loadimage(NULL,sGuiPath);//加载GUI资源
			GuiSta=iGuiSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//输入处理
		{
		case 1:
		case 2://上下按键处理
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
		case 5://确认按键处理
			return GuiSta;
		case 0://返回按键处理
			ExitGame();
		}
	}
}

int TheChapter()//关卡界面函数定义
{
	int i,ChapterSta=-1,iChapterSta;//章节标志

	IMAGE img_Title,img_Chapter,img_Map;
	char cInputKey;//按键输入标志位
	char sChapter[30];
	char sMap[30];
	char sChange[30];

	FILE *fp;//文件变量
	char sTitleName[30];

	TheSwitch();//切换动画

	if(mysave.bIsPlay)//存档继续游戏标志为真
	{
		//加载继续游戏地图存档
		if((fp=fopen("save/map.dat","rb"))==NULL)
		{
			TheMessage("△错误！地图存档文件加载失败！！！");
			ExitGame();
		}
		//加载未完成关卡和步数
		iAtChapter=getw(fp);
		fclose(fp);
		return iAtChapter;
	}
	//打开标题名称数据文件
	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("△错误！标题资源文件加载失败！！！");
		ExitGame();
	}

	iChapterSta=mysave.iFinishChapter;//状态初始化
	loadimage(&img_Title,"img/chapter/title");//载入标题资源

	while(true)
	{
		if(ChapterSta!=iChapterSta)
		{
			BeginBatchDraw();//开始批量绘图
			putimage(0, 0, &img_Title);//显示标题
			rewind(fp);//返回文件开头
			for(i=0;i<=iChapterSta;i++)
				fscanf(fp,"%s",sTitleName);//读取文件输出
			settextstyle(40,20,"方正喵呜体");//字体初始化
			setbkmode(TRANSPARENT);//设置字体背景模式为透明
			settextcolor(BLACK);//设置字体颜色
			outtextxy((640-textwidth(sTitleName))/2,5,sTitleName);

			sprintf(sChapter,"%s%d","img/chapter/chapter",iChapterSta);
			loadimage(&img_Chapter,sChapter);
			putimage(0, 50, &img_Chapter);//显示章节地图

			sprintf(sMap,"%s%d","img/map/chapter",iChapterSta);
			loadimage(&img_Map,sMap);
			putimage(0, 330, &img_Map);//显示迷你地图
			EndBatchDraw();//结束批量绘图

			ChapterSta=iChapterSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//输入处理
		{
		case 3://左右按键处理
			if(ChapterSta>0)
			{
				iChapterSta--;
				//切换动画
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
				//切换动画
				for(i=18;i>=0;i--)
				{
					sprintf(sChange,"%s%d","img/map/map",i);
					loadimage(&img_Map,sChange);
					putimage(0, 330, &img_Map);
					Sleep(5);
				}
			}
			break;
		case 5://确认按键处理
			fclose(fp);//关闭文件
			return ChapterSta;
		case 6:
			for(i=50;i&&GetKeyState('R')<0;i--)
				Sleep(10);
			if(i==0&&ChapterSta!=0&&ChapterSta!=11)
			{
				RePlay(ChapterSta);
				ChapterSta=-1;//状态改变刷新画面
			}
			break;
		case 0://返回按键处理
			fclose(fp);//关闭文件
			return -1;
		}
	}

	return 0;
}

bool TheMessage(char *sMessages)//消息框函数定义
{
	int MessageSta=-1,iMessageSta=0;
	IMAGE img_State;
	char cInputKey;///按键输入标志位
	char sState[]="img/gui/state0";
	
	settextstyle(40,20,"方正喵呜体");//字体初始化
	settextcolor(WHITE);//设置字体颜色
	setbkmode(TRANSPARENT);//设置字体背景模式为透明

	setbkcolor(BLACK);
	cleardevice();//清除设备
	RECT rect={80,100,560,300};//输出消息框消息
	drawtext(sMessages,&rect,DT_WORDBREAK);

	while(true)
	{

		if(MessageSta!=iMessageSta)
		{
			sState[13]=iMessageSta+48;//整型转化为字符型
			loadimage(&img_State,sState);//加载状态资源
			putimage(0,400,&img_State);
			MessageSta=iMessageSta;
		}
		cInputKey=KeyInput(0);
		switch(cInputKey)//输入处理
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

void BeginGame()//开始游戏函数
{
	//数据初始化
	mysave.bIsSaved=true;
	mysave.iFinishChapter=1;
	mysave.iEndFlag=0;
	mysave.bIsPlay=false;
	SaveFile();
	//删除行动记录文件夹
	//system("rmdir /s /q data/record");
	//mkdir("data/record");

	PlayGame(0);//播放序章动画
	TheHelp();//游戏帮助
}

void PlayMovie(char *sMoviePath)//动画播放函数
{
	/*FILE *fp;//文件指针
	IMAGE img_CG;
	int num,time,x,y;//整形变量
	char sPlayPath[30];//动画资源路径
	char sTmp[30];//临时数据字符串
	sprintf(sPlayPath,"%s%s",sMoviePath,"/play.dat");
	if((fp=fopen(sPlayPath,"r"))==NULL)
	{
		TheMessage("△错误！动画资源文件加载失败！！！");
		ExitGame();
	}

	while(!feof(fp))
	{
		fscanf(fp,"%d",&num);
		switch(num)
		{
		case 0://播放图片
			break;
		case 2://清空工作区
			break;
		case 3://显示文字
			break;
		case 4://播放音效
			break;
		case 5://播放音乐
			break;
		}
	}
	fclose(fp);*/
}                
     
bool PlayGame(int num)//游戏开始函数
{
	FILE *fp;//文件指针
	MyStep *p;//行动指针
	int i;//整形变量
	char sTitleName[30];
	char sRecord[30];
	char cInputKey;//按键标志
	ThePoint Tpoint1,Tpoint2;

	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("△错误！标题资源文件加载失败！！！");
		ExitGame();
	}
	else
	{
		rewind(fp);//返回文件开头
		for(i=0;i<=num;i++)
			fscanf(fp,"%s",sTitleName);//读取文件输出
		settextstyle(40,20,"方正喵呜体");//字体初始化
		settextcolor(WHITE);//设置字体颜色
		setbkmode(TRANSPARENT);//设置字体背景模式为透明

		setbkcolor(BLACK);//设置背景色
		cleardevice();//清除设备
		outtextxy((640-textwidth(sTitleName))/2,200,sTitleName);
		Sleep(2000);//显示标题后延迟两秒
		fflush(stdin);//清除键盘缓存区（注：没有效果）

		fclose(fp);//关闭文件
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
	default://加载地图数据
		LoadGame(num);
	}

	TheSwitch();//切换动画

	//游戏操作核心部分
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
		case 5://世界切换
			if(world.bIsTrueWorld&&
				(world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==3)||
				!world.bIsTrueWorld&&
				(world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==3))
			{
				world.bIsTrueWorld=!world.bIsTrueWorld;
				PrintGame();//改变世界重画界面

				AddStep(5);//添加行动数据
			}
			continue;
		case 6://重开游戏
			for(i=50;i&&GetKeyState('R')<0;i--)
				Sleep(10);
			if(i==0)
			{
				LoadGame(num);//重新加载地图
				PrintGame();//刷新世界重画界面
			}
			continue;
		case 7:
			TheHelp();//游戏帮助
			TheSwitch();//切换动画
			PrintGame();
			continue;
		case 0:
			switch(TheBack())
			{
			case 1:
				mysave.bIsPlay=false;
				return true;
			case 2:
				//保存继续游戏地图存档
				if((fp=fopen("save/map.dat","wb"))==NULL)
				{
					TheMessage("△错误！游戏保存失败！！！");
					return false;
				}
				//保存未完成关卡和步数
				putw(iAtChapter,fp);
				putw(iStepNum,fp);
				fwrite(&bIsWin,sizeof(bool),1,fp);
				fwrite(&world,sizeof(world),1,fp);
				fclose(fp);

				mysave.bIsPlay=true;
				SaveFile();//保存存档
				return false;
			case 0:
				TheSwitch();//切换动画
				PrintGame();//重画世界
				break;
			}
		default:
			continue;
		}
		//玩家移动
		if(themap[Tpoint1.x][Tpoint1.y]==2||themap[Tpoint1.x][Tpoint1.y]==3)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;		
		}
		//推动箱子
		else if((themap[Tpoint1.x][Tpoint1.y]==4||themap[Tpoint1.x][Tpoint1.y]==5)&&
			(Tpoint2.x>=0&&Tpoint2.x<LineSize&&Tpoint2.y>=0&&Tpoint2.y<ColSize)&&
			(themap[Tpoint2.x][Tpoint2.y]==2||themap[Tpoint2.x][Tpoint2.y]==3))
		{
			themap[Tpoint1.x][Tpoint1.y]-=2;
			themap[Tpoint2.x][Tpoint2.y]+=2;
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			IsWin();//判断推箱子是否完成任务
		}
		//完成游戏
		else if(bIsWin&&themap[Tpoint1.x][Tpoint1.y]==6)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			AddStep(cInputKey);//添加行动数据
			iStepNum++;//步数累加
			//最终结局标志加一
			if(world.bIsTrueWorld&&mysave.iFinishChapter==iAtChapter)
				mysave.iEndFlag++;
			//关卡完成标志加一
			if(mysave.iFinishChapter<11&&mysave.iFinishChapter==iAtChapter)
				mysave.iFinishChapter++;
			//数据存档保存
			mysave.bIsPlay=false;
			SaveFile();
			//保存新纪录
			sprintf(sRecord,"%s%d%s","data/record/record",num,".dat");
			i=(LoadStep(1,sRecord));//原记录行动数
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
			//刷新世界显示
			PrintGame();
			Sleep(500);//延时显示
 			return true;
		}
		else continue;

		AddStep(cInputKey);//添加行动数据

		iStepNum++;//步数累加
		PrintGame();//刷新世界
	}
	return true;
}

void RePlay(int num)//记录回放函数
{
	FILE *fp;//文件指针
	MyStep *p;//行动指针
	int i;//整形变量
	char sTitleName[30];
	char sRecord[30];
	char cInputKey;//按键标志
	ThePoint Tpoint1,Tpoint2;

	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("△错误！标题资源文件加载失败！！！");
		ExitGame();
	}
	else
	{
		rewind(fp);//返回文件开头
		for(i=0;i<=num;i++)
			fscanf(fp,"%s",sTitleName);//读取文件输出
		settextstyle(40,20,"方正喵呜体");//字体初始化
		settextcolor(WHITE);//设置字体颜色
		setbkmode(TRANSPARENT);//设置字体背景模式为透明

		setbkcolor(BLACK);//设置背景色
		cleardevice();//清除设备
		outtextxy((640-textwidth(sTitleName))/2,200,sTitleName);
		Sleep(2000);//显示标题后延迟两秒
		fflush(stdin);//清除键盘缓存区（注：没有效果）

		fclose(fp);//关闭文件
	}

	//加载地图数据
	LoadGame(num);
	//加载行动数据
	sprintf(sRecord,"data/record/record%d.dat",num);
	if(LoadStep(0,sRecord)<=0)
	{
		TheMessage("●本关卡尚未保存记录，不能重播！");
		return;
	}
	p=pStep;//行动数据指针初始化

	TheSwitch();
	//游戏操作核心部分
	PrintGame();
	while(true)
	{
 		if(KeyInput(1)==5)
		{
			Sleep(500);
			TheSwitch();//切换动画
			return;
		}
		if(p!=NULL)
		{
			cInputKey=p->num;
			p=p->pNext;
		}
		Sleep(500);//延时显示
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
		case 5://世界切换
			if(world.bIsTrueWorld&&
				(world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap2[world.ThePlayer.x][world.ThePlayer.y]==3)||
				!world.bIsTrueWorld&&
				(world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==2||
				world.TheMap1[world.ThePlayer.x][world.ThePlayer.y]==3))
			{
				world.bIsTrueWorld=!world.bIsTrueWorld;
				PrintGame();//改变世界重画界面
			}
			continue;
		}
		//玩家移动
		if(themap[Tpoint1.x][Tpoint1.y]==2||themap[Tpoint1.x][Tpoint1.y]==3)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;		
		}
		//推动箱子
		else if((themap[Tpoint1.x][Tpoint1.y]==4||themap[Tpoint1.x][Tpoint1.y]==5)&&
			(Tpoint2.x>=0&&Tpoint2.x<LineSize&&Tpoint2.y>=0&&Tpoint2.y<ColSize)&&
			(themap[Tpoint2.x][Tpoint2.y]==2||themap[Tpoint2.x][Tpoint2.y]==3))
		{
			themap[Tpoint1.x][Tpoint1.y]-=2;
			themap[Tpoint2.x][Tpoint2.y]+=2;
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			IsWin();//判断推箱子是否完成任务
		}
		//完成游戏
		else if(bIsWin&&themap[Tpoint1.x][Tpoint1.y]==6)
		{
			world.ThePlayer.x=Tpoint1.x;
			world.ThePlayer.y=Tpoint1.y;
			iStepNum++;//步数累加
			//刷新世界显示
			PrintGame();
			Sleep(500);//延时显示
			//切换动画
			TheSwitch();
 			return;
		}
		else continue;

		iStepNum++;//步数累加
		PrintGame();//刷新世界
	}
}
//行动数据记录加载函数
int LoadStep(int mode,char *path)//mode为0-加载数据 mode为1-只计数不加载
{
	int num=0,tmp;
	FILE *fp;//文件指针
	MyStep *p=pStep;
	//加载行动数据记录
	if((fp=fopen(path,"rb"))==NULL)
		return -1;
	//行动数据读取
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
			//行动步数增加
			if(p->num!=5)
				num++;
			tmp=getw(fp);
		}
		if(p!=NULL)//防止野指针
		p->pNext=NULL;
	}
	else
	{
		while(!feof(fp))
		{
			//行动步数增加
			if(tmp!=5)
				num++;
			tmp=getw(fp);
		}
	}
	fclose(fp);
	return num;//返回行动步数
}

void LoadGame(int num)//游戏加载函数
{
	FILE *fp;//文件结构体指针
	char sMapPath[30];
	char sBlockPath[30];
	char sTemp[30];

	BlockData *p=pBlock;//方块资源指针

	//加载方块资源ID
	if(pBlock==NULL)
	{
		if((fp=fopen("data/block.dat","r"))==NULL)
		{
			TheMessage("△错误！方块资源ID文件加载失败！！！");
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
			p->img=new IMAGE;//建立资源对象
			loadimage(p->img,sBlockPath);//加载资源
			
		}
		if(p!=NULL)
			p->pNext=NULL;
		fclose(fp);
		
	}	
	//补全地图资源路径
	sprintf(sMapPath,"%s%d%s","data/map/map",num,".dat");
	
	if(mysave.bIsPlay)//存档继续游戏标志为真
	{
		//加载行动数据记录
		if(LoadStep(0,"save/step.dat")==-1)
		{
			TheMessage("△错误！行动数据记录文件加载失败！！！");
			ExitGame();
		}
		//加载继续游戏地图存档
		if((fp=fopen("save/map.dat","rb"))==NULL)
		{
			TheMessage("△错误！地图存档文件加载失败！！！");
			ExitGame();
		}
		//加载未完成关卡和步数
		iAtChapter=getw(fp);
		iStepNum=getw(fp);
		fread(&bIsWin,sizeof(bool),1,fp);
		//数据加载后置位为false
		mysave.bIsPlay=false;
	}
	//加载地图资源
	else if((fp=fopen(sMapPath,"rb"))==NULL)
	{
		TheMessage("△错误！地图资源文件加载失败！！！");
		ExitGame();
	}
	else//设置未完成关卡和步数
	{
		iAtChapter=num;
		iStepNum=0;
		FreeStep();//刷新行动链表
		bIsWin=false;
	}
	fread(&world,sizeof(world),1,fp);
	fclose(fp);
	return;
}

IMAGE * GetMyImg(int bID)//block资源函数
{
	BlockData *p=pBlock;
	//地图ID与资源ID转换
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
	//查询返回资源指针
	while(p)
	{
		if(p->num==bID)
			return p->img;
		p=p->pNext;
	}

	return NULL;
}

void IsWin()//胜利判断函数
{
	int i;
	bIsWin=true;//初始设置为真
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

void PrintGame()//游戏显示函数
{
	int i,j;
	char sTitleName[30];
	FILE *fp;//文件指针
	IMAGE *img;//图像指针

	//打开标题文件
	if((fp=fopen("data/title.dat","r"))==NULL)
	{
		TheMessage("△错误！标题资源文件加载失败！！！");
		ExitGame();
	}
	settextstyle(24,12,"方正喵呜体");//字体初始化
	setbkmode(TRANSPARENT);//设置字体背景模式为透明
	for(i=0;i<=iAtChapter;i++)
				fscanf(fp,"%s",sTitleName);//读取文件输出
	settextcolor(BLACK);//设置字体颜色

	//开始批量绘制
	BeginBatchDraw();
	//判断是否在真实世界
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
		outtextxy(148,132,"★");
	else
		outtextxy(148,132,"☆");
	//加载本关标题
	outtextxy((250-textwidth(sTitleName+8))/2,50,sTitleName+8);
	sprintf(sTitleName,"%4d 步",iStepNum);
	outtextxy(120,195,sTitleName);
	//加载地图中…
	for(i=0;i<LineSize;i++)
		for(j=0;j<ColSize;j++)
			if((img=GetMyImg(themap[i][j]))!=NULL)
				putimage(world.OriPoint.y+32*j,world.OriPoint.x+32*i,img);

	//加载玩家资源
	putimage(world.OriPoint.y+32*world.ThePlayer.y,world.OriPoint.x+32*world.ThePlayer.x,GetMyImg(7));
	//结束批量绘制
	EndBatchDraw();
}

int TheBack()//游戏暂停函数
{
	int BackSta=-1,iBackSta=0;
	char sBackPath[30];
	char cInputKey;//按键标志

	TheSwitch();//切换动画

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
				if(TheMessage("●选择关卡将失去现有的进度，是否继续？"))
					return BackSta;
				BackSta=-1;//返回刷新界面
				break;
			case 2:
				if(TheMessage("●将要保存进度并退回菜单，是否继续？"))
					return BackSta;
				BackSta=-1;//返回刷新界面
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

void TheHelp()//游戏帮助函数
{
	int HelpSta=-1,iHelpSta=0;
	char sHelpPath[30];
	char cInputKey;//按键标志

	TheSwitch();//切换动画

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

void AddStep(int num)//行动记录添加函数
{
	MyStep *p=pStep;//行动数据指针

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

void FreeStep()//行动记录释放函数
{
	MyStep *p1,*p2;//行动数据指针
	p1=p2=pStep;//指针初始化
	while(p1!=NULL)
	{
		p2=p2->pNext;
		free(p1);
		p1=p2;
	}
	pStep=NULL;//防止野指针
}

void ExitGame()//游戏退出函数
{
	BlockData *p1,*p2;//方块数据指针
	p1=p2=pBlock;//指针初始化
	//释放资源ID内存资源
	while(p1!=NULL)
	{
		p2=p2->pNext;
		free(p1->img);//释放资源
		free(p1);//释放链表节点
		p1=p2;
	}
	pBlock=NULL;//防止野指针
	FreeStep();//释放行动记录
	TheSwitch();//切换动画
	//退出游戏客户端
	exit(0);
}

////////////////////////////////////////////////////////////
//这是一个推箱子的解谜小游戏。
//以下，是源程序。

//头文件声明
#include"game.h"
#include<windows.h>
#include<graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

//主函数
int main()
{
	int i,num;//整形变量
	IMAGE img;
	system("title 神秘的引路人");
	Openfile();//打开存档读取数据

	initgraph(640, 480);
	//开场动画
	loadimage(&img,"img/gui/enter");
	BeginBatchDraw();//开始批量绘图
	setfillcolor(BLACK);
	for(i=96;i>=0;i--)
	{
		putimage(0,0,&img);
		solidcircle(320,240,i*10);
		FlushBatchDraw();//执行未完成的绘图工作
		Sleep(10);
	}
	Sleep(1000);
	EndBatchDraw();//结束批量绘图
	TheSwitch();	

	//播放背景音乐
	PlaySound("sound/BGM/bgm1.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

	while(true)
	{
		switch(MainInterface())
		{
		case 3://开始游戏询问是否确定删除存档
			if(!TheMessage("●开始游戏将删除原先的存档，是否继续？"))
				break;
		case 0://开始游戏
			BeginGame();
		case 2://继续游戏
		
			while(true)
			{
				num=TheChapter();
				if(num==-1)
					break;
				//PlayGame返回值为false回到主菜单，返回值为true回到关卡界面
				if(!PlayGame(num))
					break;
			}
			break;
		case 1:
		case 4://退出游戏
			ExitGame();
		}
		TheSwitch();//切换动画
	}
	closegraph();
	return 0;
}

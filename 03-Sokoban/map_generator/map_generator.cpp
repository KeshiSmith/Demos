#include<conio.h>
#include<stdio.h>
#include<windows.h>

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

//函数声明
void ChangeMap();
void CreateMap();

int main()
{
	int i;
	printf("《神秘的引路人-推箱子》地图生成器\n正在打开中……\n");
	Sleep(2000);
	while(true)
	{
		system("cls");
		printf("1:修改世界 2:创造世界\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			ChangeMap();
			break;
		case 2:
			CreateMap();
			break;
		case 0:
			exit(0);
		}
	}
	return 0;
}

void ChangeMap()
{
	FILE *fp;

	if((fp=fopen("map.dat","rb"))==NULL)
	{
		system("cls");
		printf("无法打开map.dat文件\n");
		system("pause");
		exit(0);
	}
	fread(&world,sizeof(world),1,fp);
	fclose(fp);//关闭文件

	if((fp=fopen("map.dat","wb"))==NULL)
	{
		system("cls");
		printf("无法打开map.dat文件\n");
		system("pause");
		exit(0);
	}

	system("cls");
	printf("请输入世界原点坐标x，y：\n");
	scanf("%d%d",&world.OriPoint.x,&world.OriPoint.y);

	system("cls");
	fwrite(&world,sizeof(world),1,fp);
	printf("地图文件map.dat修改成功！\n");
	system("pause");
	Sleep(1000);
	fclose(fp);//关闭文件
}

void CreateMap()
{
	int i,j;//临时变量
	FILE *fp;//文件指针

	system("cls");
	printf("请输入世界原点坐标x，y：\n");
	scanf("%d%d",&world.OriPoint.x,&world.OriPoint.y);
	
	//真实世界数据记录
	system("cls");
	printf("请输入真实世界大小m，n：\n");
	scanf("%d%d",&world.MapSize1.x,&world.MapSize1.y);
	
	system("cls");
	printf("0：空白，1：墙壁，2.地面，3.目标，4.地面+箱子，5.目标+箱子，6.出口\n");
	printf("请输入真实世界地图数据：\n");
	
	world.TheNum1=0;
	for(i=0;i<world.MapSize1.x;i++)
		for(j=0;j<world.MapSize1.y;j++)
		{
			scanf("%d",&world.TheMap1[i][j]);
			if(world.TheMap1[i][j]==3||world.TheMap1[i][j]==5)
			{
				world.MyPlace1[world.TheNum1].x=i;
				world.MyPlace1[world.TheNum1].y=j;
				world.TheNum1++;
			}
		}
	//里世界数据记录
		
	system("cls");
	printf("请输入里世界大小m，n：\n");
	scanf("%d%d",&world.MapSize2.x,&world.MapSize2.y);
	
	system("cls");
	printf("");
	printf("请输入里世界地图数据：\
		\n(0：空白，1：墙壁，2.地面，3.目标，4.地面+箱子，5.目标+箱子，6.出口)\n");
	
	world.TheNum2=0;
	for(i=0;i<world.MapSize2.x;i++)
		for(j=0;j<world.MapSize2.y;j++)
		{
			scanf("%d",&world.TheMap2[i][j]);
			if(world.TheMap2[i][j]==3||world.TheMap2[i][j]==5)
			{
				world.MyPlace2[world.TheNum2].x=i;
				world.MyPlace2[world.TheNum2].y=j;
				world.TheNum2++;
			}
		}
		//公用数据记录
		system("cls");
		printf("起始玩家是否在真实世界（0.不在，1.在）：\n");
		scanf("%d",&world.bIsTrueWorld);
		
		system("cls");
		printf("请输入玩家坐标x，y：\n");
		scanf("%d%d",&world.ThePlayer.x,&world.ThePlayer.y);
			
		while(true)
		{
			system("cls");
			fflush(stdin);//清除键盘缓存区
			if((fp=fopen("map.dat","rb"))!=NULL)
			{
				
				printf("本目录下已存在map.dat文件！回车键覆盖，其他键重试。");
				if(getch()!=13)
					continue;
				fclose(fp);
			}
			if((fp=fopen("map.dat","wb"))!=NULL)
			{
				system("cls");
				fwrite(&world,sizeof(world),1,fp);
				printf("地图文件map.dat生成成功！\n");
				system("pause");
				fclose(fp);
				break;
			}
			else
			{
				printf("地图文件map.dat生成失败！回车键重试,其他键退出。");
				if(getch()!=13)
					break;
			}
		}
}
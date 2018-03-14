#include<conio.h>
#include<stdio.h>
#include<windows.h>

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

//��������
void ChangeMap();
void CreateMap();

int main()
{
	int i;
	printf("�����ص���·��-�����ӡ���ͼ������\n���ڴ��С���\n");
	Sleep(2000);
	while(true)
	{
		system("cls");
		printf("1:�޸����� 2:��������\n");
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
		printf("�޷���map.dat�ļ�\n");
		system("pause");
		exit(0);
	}
	fread(&world,sizeof(world),1,fp);
	fclose(fp);//�ر��ļ�

	if((fp=fopen("map.dat","wb"))==NULL)
	{
		system("cls");
		printf("�޷���map.dat�ļ�\n");
		system("pause");
		exit(0);
	}

	system("cls");
	printf("����������ԭ������x��y��\n");
	scanf("%d%d",&world.OriPoint.x,&world.OriPoint.y);

	system("cls");
	fwrite(&world,sizeof(world),1,fp);
	printf("��ͼ�ļ�map.dat�޸ĳɹ���\n");
	system("pause");
	Sleep(1000);
	fclose(fp);//�ر��ļ�
}

void CreateMap()
{
	int i,j;//��ʱ����
	FILE *fp;//�ļ�ָ��

	system("cls");
	printf("����������ԭ������x��y��\n");
	scanf("%d%d",&world.OriPoint.x,&world.OriPoint.y);
	
	//��ʵ�������ݼ�¼
	system("cls");
	printf("��������ʵ�����Сm��n��\n");
	scanf("%d%d",&world.MapSize1.x,&world.MapSize1.y);
	
	system("cls");
	printf("0���հף�1��ǽ�ڣ�2.���棬3.Ŀ�꣬4.����+���ӣ�5.Ŀ��+���ӣ�6.����\n");
	printf("��������ʵ�����ͼ���ݣ�\n");
	
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
	//���������ݼ�¼
		
	system("cls");
	printf("�������������Сm��n��\n");
	scanf("%d%d",&world.MapSize2.x,&world.MapSize2.y);
	
	system("cls");
	printf("");
	printf("�������������ͼ���ݣ�\
		\n(0���հף�1��ǽ�ڣ�2.���棬3.Ŀ�꣬4.����+���ӣ�5.Ŀ��+���ӣ�6.����)\n");
	
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
		//�������ݼ�¼
		system("cls");
		printf("��ʼ����Ƿ�����ʵ���磨0.���ڣ�1.�ڣ���\n");
		scanf("%d",&world.bIsTrueWorld);
		
		system("cls");
		printf("�������������x��y��\n");
		scanf("%d%d",&world.ThePlayer.x,&world.ThePlayer.y);
			
		while(true)
		{
			system("cls");
			fflush(stdin);//������̻�����
			if((fp=fopen("map.dat","rb"))!=NULL)
			{
				
				printf("��Ŀ¼���Ѵ���map.dat�ļ����س������ǣ����������ԡ�");
				if(getch()!=13)
					continue;
				fclose(fp);
			}
			if((fp=fopen("map.dat","wb"))!=NULL)
			{
				system("cls");
				fwrite(&world,sizeof(world),1,fp);
				printf("��ͼ�ļ�map.dat���ɳɹ���\n");
				system("pause");
				fclose(fp);
				break;
			}
			else
			{
				printf("��ͼ�ļ�map.dat����ʧ�ܣ��س�������,�������˳���");
				if(getch()!=13)
					break;
			}
		}
}
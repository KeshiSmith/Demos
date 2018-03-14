#pragma once
#include<graphics.h>

//�궨�峣�ùؼ���
#define uchar unsigned char
#define uint unsigned int

//�궨�巽����
#define PLAYER 0
#define MIAO 1
#define WALL 2
#define PATH 3
#define PLACE 4
#define LAMP_OFF 5
#define LAMP_ON 6
#define DOOR_WOOD 7
#define WALL_I 8
#define PATH_I 9
#define PLACE_I 10
#define STONE_BLUE 11
#define STONE_RED 12
#define DOOR_IRON 13

//��������
void Openfile();//�򿪴浵�ļ�����
void SaveFile();//�رմ浵�ļ�����
char KeyInput(int);//�������뺯��
void TheSwitch();//�л���������
int MainInterface();//�����溯��
int TheChapter();//�ؿ����溯��
bool TheMessage(char *);//��Ϣ����
void BeginGame();//��ʼ��Ϸ����
void PlayMovie(char *);//�������ź���
bool PlayGame(int);//��Ϸ��ʼ����
void RePlay(int);//��¼�طź���
int LoadStep(int,char *);//�ж���¼���غ���
void LoadGame(int);//��Ϸ���غ���
IMAGE * GetMyImg(int);//block��Դ����
void IsWin();//ʤ���жϺ���
void PrintGame();//��Ϸ��ʾ����
int TheBack();//��Ϸ��ͣ����
void TheHelp();//��Ϸ��������
void AddStep(int);//�ж���¼��Ӻ���
void FreeStep();//�ж���¼�ͷź���
void ExitGame();//��Ϸ�˳�����
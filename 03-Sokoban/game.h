#pragma once
#include<graphics.h>

//宏定义常用关键字
#define uchar unsigned char
#define uint unsigned int

//宏定义方块编号
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

//函数声明
void Openfile();//打开存档文件函数
void SaveFile();//关闭存档文件函数
char KeyInput(int);//键盘输入函数
void TheSwitch();//切换动画函数
int MainInterface();//主界面函数
int TheChapter();//关卡界面函数
bool TheMessage(char *);//消息框函数
void BeginGame();//开始游戏函数
void PlayMovie(char *);//动画播放函数
bool PlayGame(int);//游戏开始函数
void RePlay(int);//记录回放函数
int LoadStep(int,char *);//行动记录加载函数
void LoadGame(int);//游戏加载函数
IMAGE * GetMyImg(int);//block资源函数
void IsWin();//胜利判断函数
void PrintGame();//游戏显示函数
int TheBack();//游戏暂停函数
void TheHelp();//游戏帮助函数
void AddStep(int);//行动记录添加函数
void FreeStep();//行动记录释放函数
void ExitGame();//游戏退出函数
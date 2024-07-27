#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <process.h>
#include <mmsystem.h>
#include <stdlib.h>

int Pc1 = 0;
int Pc2 = 7;

enum ColorType //커서 색상 바꿀 때 영어로도 입력 가능
{
    BLACK,  	//0
    DARKBLUE,	//1
    DARKGREEN,	//2
    DARKSKYBLUE,//3
    DARKRED,  	//4
    DARKPURPLE,	//5
    DARKYELLOW,	//6
    GRAY,		//7
    DARKGRAY,	//8
    BLUE,		//9
    GREEN,		//10
    SKYBLUE,	//11
    RED,		//12
    PURPLE,		//13
    YELLOW,		//14
    WHITE		//15
} COLOR;

typedef struct //플레이어의 구조체
{
    int x;
    int y;
    int HP;
    int Prex;
    int Prey;
}Player;

int map[50][50] = //기본적인 맵
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void ResetScreen(); //화면 초기화
void GameStart(); //게임시작
void DrawMap(); //맵 그리미
void Render(int px1, int py1, int px2, int py2);
void GotoXY(int x, int y); //커서 움직이기
void TextColor(int colornum); //폰트 색 변경
void CursorView(int size, bool dVisible); //커서 외형 설정
bool IsAlive(int hp, int x, int y); //생사여부
void PrintInfo(int px1, int py1, int php1, int px2, int py2, int php2); //다목적 정보확인
int IsP1XMove(); //P1의 x좌표 움직임
int IsP1YMove(); //P1의 y좌표 움직임
int IsP2XMove(); //P2의 x좌표 움직임
int IsP2YMove(); //P2의 y좌표 움직임
void GameMenu(); //게임 메뉴
int shooting1(int who, int px, int py, int d, int ex, int ey); //총알 발사
int shooting2(int who, int px, int py, int d, int ex, int ey); //무한의 대검
int shooting3(int who, int px, int py, int d, int ex, int ey); //즉사
bool hit(int x, int y, int ex, int ey); //히트 판정  
void LoadingScreen(); //로딩화면
void EndingScreen(int winner); //사망 정보창


int main()
{
    SetConsoleOutputCP(65001);
    CursorView(1, FALSE); //커서 깜빡임 끄기
    system("mode con:cols=100 lines=54"); //콘솔창 크기 설정
    GameMenu();
}

void GameStart()
{
    ResetScreen();
    Player P1;
    Player P2;
    P1.x = 50;
    P1.y = 10;
    P2.x = 50;
    P2.y = 40;
    P1.HP = 50;
    P2.HP = 50;
    P1.Prex = 50;
    P1.Prey = 10;
    P2.Prex = 50;
    P2.Prey = 40;
    int temp1, temp2, temp3, temp4;
    bool pa1 = true;
    bool pa2 = true;
    while (pa1 && pa2)
    {
        temp1 = IsP1XMove();
        temp2 = IsP1YMove();
        temp3 = IsP2XMove();
        temp4 = IsP2YMove();
        P1.x += temp1;
        P1.y += temp2;
        P2.x += temp3;
        P2.y += temp4;
        TextColor(YELLOW);
        if (GetAsyncKeyState(0x30) & 0x8000) //숫자키0 : P1 1번 무기 발사
        {
            if (temp1 == 1)
            {
                P2.HP += shooting1(1, P1.x, P1.y, 2, P2.x, P2.y);
            }
            else if (temp1 == -1)
            {
                P2.HP += shooting1(1, P1.x, P1.y, 4, P2.x, P2.y);
            }
            else
            {
                if (temp2 == 1)
                {
                    P2.HP += shooting1(1, P1.x, P1.y, 1, P2.x, P2.y);
                }
                else if (temp2 == -1)
                {
                    P2.HP += shooting1(1, P1.x, P1.y, 3, P2.x, P2.y);
                }
            }
        }
        if (GetAsyncKeyState(0x35) & 0x8000) //숫자키5 : P2 1번 무기 발사
        {
            if (temp3 == 1)
            {
                P1.HP += shooting1(2, P2.x, P2.y, 2, P1.x, P1.y);
            }
            else if (temp3 == -1)
            {
                P1.HP += shooting1(2, P2.x, P2.y, 4, P1.x, P1.y);
            }
            else
            {
                if (temp4 == 1)
                {
                    P1.HP += shooting1(2, P2.x, P2.y, 1, P1.x, P1.y);
                }
                else if (temp4 == -1)
                {
                    P1.HP += shooting1(2, P2.x, P2.y, 3, P1.x, P1.y);
                }
            }
        }
        if (GetAsyncKeyState(0x31) & 0x8000) //숫자키1 : P1 2번 무기 발사 
        {
            if (temp1 == 1)
            {
                P2.HP += shooting2(1, P1.x, P1.y, 2, P2.x, P2.y);
            }
            else if (temp1 == -1)
            {
                P2.HP += shooting2(1, P1.x, P1.y, 4, P2.x, P2.y);
            }
            else
            {
                if (temp2 == 1)
                {
                    P2.HP += shooting2(1, P1.x, P1.y, 1, P2.x, P2.y);
                }
                else if (temp2 == -1)
                {
                    P2.HP += shooting2(1, P1.x, P1.y, 3, P2.x, P2.y);
                }
            }
        }
        if (GetAsyncKeyState(0x36) & 0x8000) //숫자키6 : P2 2번 무기 발사
        {
            if (temp3 == 1)
            {
                P1.HP += shooting2(2, P2.x, P2.y, 2, P1.x, P1.y);
            }
            else if (temp3 == -1)
            {
                P1.HP += shooting2(2, P2.x, P2.y, 4, P1.x, P1.y);
            }
            else
            {
                if (temp4 == 1)
                {
                    P1.HP += shooting2(2, P2.x, P2.y, 1, P1.x, P1.y);
                }
                else if (temp4 == -1)
                {
                    P1.HP += shooting2(2, P2.x, P2.y, 3, P1.x, P1.y);
                }
            }
        }
        if (GetAsyncKeyState(0x32) & 0x8000) //숫자키2 : P1 3번 무기 발사
        {
            if (temp1 == 1)
            {
                P2.HP += shooting3(1, P1.x, P1.y, 2, P2.x, P2.y);
            }
            else if (temp1 == -1)
            {
                P2.HP += shooting3(1, P1.x, P1.y, 4, P2.x, P2.y);
            }
            else
            {
                if (temp2 == 1)
                {
                    P2.HP += shooting3(1, P1.x, P1.y, 1, P2.x, P2.y);
                }
                else if (temp2 == -1)
                {
                    P2.HP += shooting3(1, P1.x, P1.y, 3, P2.x, P2.y);
                }
            }
        }
        if (GetAsyncKeyState(0x37) & 0x8000) //숫자키7 : P2 3번 무기 발사
        {
            if (temp3 == 1)
            {
                P1.HP += shooting3(2, P2.x, P2.y, 2, P1.x, P1.y);
            }
            else if (temp3 == -1)
            {
                P1.HP += shooting3(2, P2.x, P2.y, 4, P1.x, P1.y);
            }
            else
            {
                if (temp4 == 1)
                {
                    P1.HP += shooting3(2, P2.x, P2.y, 1, P1.x, P1.y);
                }
                else if (temp4 == -1)
                {
                    P1.HP += shooting3(2, P2.x, P2.y, 3, P1.x, P1.y);
                }
            }
        }
        if (GetAsyncKeyState(0x34) & 0x8000) //숫자키4 : 30초 퍼즈
        {
            Sleep(3000);
        }
        Render(P1.x, P1.y, P2.x, P2.y);
        pa1 = IsAlive(P1.HP, P1.x, P1.y);
        pa2 = IsAlive(P2.HP, P2.x, P2.y);
        PrintInfo(P1.x, P1.y, P1.HP, P2.x, P2.y, P2.HP);
        Sleep(100); //화면 새로 고침 빈도 조정(숫자가 클수록 프레임이 낮아짐) 프레임이 높을수록 더 반짝임 주의
        if (pa1)
        {

        }
        else
        {
            EndingScreen(1);
        }
        if (pa2)
        {

        }
        else
        {
            EndingScreen(2);
        }
    }
}

void Render(int px1, int py1, int px2, int py2)
{
    DrawMap();
    GotoXY(px1, py1);
    TextColor(Pc1);
    printf("◆");
    GotoXY(px2, py2);
    TextColor(Pc2);
    printf("◆");
    GotoXY(px1, py1);
    TextColor(Pc1);
    printf("◆");
    GotoXY(px2, py2);
    TextColor(Pc2);
    printf("◆");
}

void ResetScreen()
{
    system("cls");
}

void DrawMap()
{
    TextColor(WHITE);
    GotoXY(0, 0);
    for (int h = 0; h < 50; h++)
    {
        for (int w = 0; w < 50; w++)
        {
            if (map[h][w] == 1)
            {
                printf("■");
            }
            else if (map[h][w] == 0)
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void TextColor(int colornum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colornum);
}

void CursorView(int size, bool dVisible)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

bool IsAlive(int hp, int x, int y)
{
    if (hp > 0 && 1 <= x && x <= 97 && 0 <= y && y <= 49)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void PrintInfo(int px1, int py1, int php1, int px2, int py2, int php2)
{
    TextColor(Pc1);
    GotoXY(2, 51);
    printf("P1.x : %d", px1);
    GotoXY(15, 51);
    printf("P1.y : %d", py1);
    GotoXY(28, 51);
    printf("P1.hp : %d", php1);
    TextColor(Pc2);
    GotoXY(52, 51);
    printf("P2.x : %d", px2);
    GotoXY(65, 51);
    printf("P2.y : %d", py2);
    GotoXY(78, 51);
    printf("P2.hp : %d", php2);
}

int IsP1XMove()
{
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) //P1 왼쪽
    {
        return -1;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //P1 오른쪽
    {
        return 1;
    }
}

int IsP1YMove()
{
    if (GetAsyncKeyState(VK_UP) & 0x8000) //P1 위
    {
        return -1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) //P1 아래
    {
        return 1;
    }
}

int IsP2XMove()
{
    if (GetAsyncKeyState(0x41) & 0x8000) //P2 왼쪽
    {
        return -1;
    }
    if (GetAsyncKeyState(0x44) & 0x8000) //P2 오른쪽
    {
        return 1;
    }
}

int IsP2YMove()
{
    if (GetAsyncKeyState(0x57) & 0x8000) //P2 위
    {
        return -1;
    }
    if (GetAsyncKeyState(0x53) & 0x8000) //P2 아래
    {
        return 1;
    }
}

void GameMenu()
{
    LoadingScreen();
    ResetScreen();
    int player[10][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };
    GotoXY(42, 40);
    printf("Select Color");
    while (1)
    {
        if (Pc1 <= 0)
        {
            Pc1 = 15;
        }
        else if (Pc1 >= 16)
        {
            Pc1 = 0;
        }
        if (Pc2 <= 0)
        {
            Pc2 = 15;
        }
        else if (Pc2 >= 16)
        {
            Pc2 = 0;
        }
        TextColor(Pc1);
        GotoXY(25, 20);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (player[i][j] == 1)
                {
                    printf("■");
                }
                else
                {
                    printf("  ");
                }
            }
            GotoXY(25, 20 + i);
        }
        TextColor(Pc2);
        GotoXY(60, 20);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (player[i][j] == 1)
                {
                    printf("■");
                }
                else
                {
                    printf("  ");
                }
            }
            GotoXY(60, 20 + i);
        }
        if (GetAsyncKeyState(0x41) & 0x8000) //P2 색변경
        {
            Pc2--;
        }
        else if (GetAsyncKeyState(0x44) & 0x8000) //P2 오른쪽
        {
            Pc2++;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) //P1 왼쪽
        {
            Pc1--;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //P1 오른쪽
        {
            Pc1++;
        }
        if (GetAsyncKeyState(0x34) & 0x8000) //4 클릭 시 게임 시작
        {
            GameStart();
            return;
        }
        Sleep(100);
    }
}

int shooting1(int who, int px, int py, int d, int ex, int ey)
{
    int x = px;
    int y = py;
    while (1 < x && x < 97 && 0 < y && y < 48)
    {
        static clock_t st, et;
        st = clock();
        GotoXY(x, y);
        printf("º");
        while (1)
        {
            if (clock() - st >= 5)
            {
                break;
            }
        }
        GotoXY(x, y);
        printf("  ");
        if (d == 1)
        {
            y++;
        }
        else if (d == 2)
        {
            x++;
        }
        else if (d == 3)
        {
            y--;
        }
        else
        {
            x--;
        }
        if (hit(x, y, ex, ey))
        {
            return -5;
        }
        else
        {
            continue;
        }
    }
    return 0;
}

int shooting2(int who, int px, int py, int d, int ex, int ey)
{
    int x = px;
    int y = py;
    while (1 < x && x < 97 && 0 < y && y < 48)
    {
        static clock_t st, et;
        st = clock();
        GotoXY(x, y);
        printf("＠");
        while (1)
        {
            if (clock() - st >= 5)
            {
                break;
            }
        }
        GotoXY(x, y);
        printf("  ");
        if (d == 1)
        {
            y++;
        }
        else if (d == 2)
        {
            x++;
        }
        else if (d == 3)
        {
            y--;
        }
        else
        {
            x--;
        }
        if (hit(x, y, ex, ey))
        {
            if (rand() % 4 == 1)
            {
                return -20;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            continue;
        }
    }
    return 0;
}

int shooting3(int who, int px, int py, int d, int ex, int ey)
{
    int x = px;
    int y = py;
    while (1 < x && x < 97 && 0 < y && y < 48)
    {
        static clock_t st, et;
        st = clock();
        GotoXY(x, y);
        printf("▣");
        while (1)
        {
            if (clock() - st >= 5)
            {
                break;
            }
        }
        GotoXY(x, y);
        printf("  ");
        if (d == 1)
        {
            y++;
        }
        else if (d == 2)
        {
            x++;
        }
        else if (d == 3)
        {
            y--;
        }
        else
        {
            x--;
        }
        if (hit(x, y, ex, ey))
        {
            return 1;
        }
        else
        {
            continue;
        }
    }
    return 0;
}

bool hit(int x, int y, int ex, int ey)
{
    if (ex == x && y == ey)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void EndingScreen(int winner)
{
    ResetScreen();
    TextColor(WHITE);
    printf(" ######      ###    ##     ## ########     ######   ##     ## ######## ########  \n");
    printf("##    ##    ## ##   ###   ### ##          ##    ##  ##     ## ##       ##     ## \n");
    printf("##         ##   ##  #### #### ##          ##    ##  ##     ## ##       ##     ## \n");
    printf("##   #### ##     ## ## ### ## ######      ##    ##  ##     ## ######   ########  \n");
    printf("##    ##  ######### ##     ## ##          ##    ##   ##   ##  ##       ##   ##   \n");
    printf("##    ##  ##     ## ##     ## ##          ##    ##    ## ##   ##       ##    ##  \n");
    printf(" ######   ##     ## ##     ## ########     ######      ###    ######## ##     ## \n");
    GotoXY(40, 23);
    printf("%dP Win", winner);
    while (1)
    {
        if (GetAsyncKeyState(0x34) & 0x8000) //4 클릭 시 게임 시작
        {
            GameStart();
            return;
        }
    }

}

void LoadingScreen()
{
    int i;
    int loadingLength = 34;


    TextColor(15);


    GotoXY(29, 10);
    printf("Wait....");
    Sleep(2000);
    GotoXY(29, 12);
    printf("LOADING");
    GotoXY(29, 14);
    printf("□□□□□□□□□□□□□□□□□□");
    for (i = 0; i <= loadingLength; i += 2)
    {
        GotoXY(29 + i, 14);
        printf("■");
        fflush(stdout);
        Sleep(200);
    }
    GotoXY(35, 18);
    printf("Loading Complete!");
    Sleep(1000);
}

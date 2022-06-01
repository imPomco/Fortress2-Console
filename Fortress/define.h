/*
extern을 모든 소스파일에 각각 입력하는 것 대신 이 헤더 파일에 extern 함수를 선언한 후
다른 파일들에서 이 곳에 선언된 함수를 사용하는 것으로 지정
*/
#include <winsock2.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <Digitalv.h>
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")

#define MAX_X_WIDTH 159
#define MAX_Y_HEIGHT 40
static int lang_lines = 0;

extern char map[40][160];
extern char lang[30][20];
extern void printMenu();
extern void selMul();
extern void netStart();
extern void client();
extern void kor();
extern void setLang();
extern void gotoxy(int, int);
extern void readMap();
extern void printMap();
extern void localStart();
extern void singleStart();
extern void playMusic(int);
extern void stopMusic(int);
extern void playFX(int);

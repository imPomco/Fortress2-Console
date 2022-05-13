/*
extern을 모든 소스파일에 각각 입력하는 것 대신 이 헤더 파일에 extern 함수를 선언한 후
다른 파일들에서 이 곳에 선언된 함수를 사용하는 것으로 지정
*/
#include <stdio.h>
#include <Windows.h>
#include <Digitalv.h>
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")

#define MAX_X_WIDTH 160
#define MAX_Y_HEIGHT 50


extern char map[40][320];
extern char ch[30][20];
extern void printMenu();
extern void kor();
extern void setLang();
extern void gotoxy(int, int);
extern void readMap();
extern void printMap();
extern void singleStart();
/*
extern�� ��� �ҽ����Ͽ� ���� �Է��ϴ� �� ��� �� ��� ���Ͽ� extern �Լ��� ������ ��
�ٸ� ���ϵ鿡�� �� ���� ����� �Լ��� ����ϴ� ������ ����
*/
#include <stdio.h>
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
extern void kor();
extern void setLang();
extern void gotoxy(int, int);
extern void readMap();
extern void printMap();
extern void multiStart();
extern void playMusic(int);
extern void stopMusic(int);
extern void playFX(int);
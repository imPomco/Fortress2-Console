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
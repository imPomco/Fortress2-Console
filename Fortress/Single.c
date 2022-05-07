#include "define.h"

#define KEYDOWN(VK_SPACE) ((GetAsyncKeyState(VK_SPACE)? 1 : 0))

void single() {
	int flag = 1;
	int health = 100;
	int angle;
	int power = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("cls");
	gotoxy(0, 40);

	for (int i = 0; i < MAX_X_WIDTH; i++)
		printf("-");

		gotoxy(30, 42);
		printf("체력 ");

	for (int i = 0; i < health / 2; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		if (health < 30)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		else if (health < 50)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		printf("■");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(30, 44);
	printf("파워 ");
	if (KEYDOWN(VK_SPACE)) {
		if (power < 100 && flag == 1) {
			power++;
			if (power == 100)
				flag = 0;
		}
		else {
			power--;
			if (power == 0)
				flag = 1;
		}
		Sleep(30);
		printf("%d", power);
	}
}
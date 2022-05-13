#include "define.h"

#define KEYDOWN(VK_SPACE) ((GetAsyncKeyState(VK_SPACE) & 0x8000 ? 1 : 0))

void countDown();
void enemyTurn();
int fire(int, int, int, int, int);
void init();
void myTurn();

static int fireFlag = 0;
static int countFlag = 1;
static int count = 15;
static int my_tank_x = 10, my_tank_y = 20; // 나의 탱크 좌표를 저장하는 변수
static int enemy_tank_x = 150, enemy_tank_y = 20; // 적의 탱크 좌표를 저장하는 변수



void multiStart() {
	readMap();
	myTurn();
}
void myTurn() {
	static int my_health = 100;
	int angle = 45;
	int power = 0;
	int move = 100;

	static int headingFlag = 1; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char my_tank = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(my_tank_x, my_tank_y);
		printf("%c", my_tank);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemy_tank_x, enemy_tank_y);
		printf("%c", my_tank);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i < MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("체력 ");

		for (int i = 0; i < my_health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (my_health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (my_health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		gotoxy(30, 44);
		printf("파워 ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			Sleep(100);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					my_health -= fire(angle, power, my_tank_x, my_tank_y, headingFlag);
					enemyTurn();
				}
				if (power == 100) {
					power = 0;
					break;
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(30, 46);
		printf("이동 ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for (int i = 0; i < move; i++)
			printf("|");
		if (KEYDOWN(VK_RIGHT)) { // 오른쪽 방향키 입력 시 우측으로 이동
			if (my_tank_x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(100);
				gotoxy(my_tank_x, my_tank_y);
				printf(" ");
				while (map[my_tank_y + 1][my_tank_x + 1] != '1') { // 내려갈 때
					if (my_tank_y == 40)
						exit(0);
					my_tank_y++;
				}
				while (map[my_tank_y][my_tank_x + 1] == '1' && map[my_tank_y - 1][my_tank_x + 1] == '0') {// 올라갈 때
					my_tank_y--;
				}
				if (map[my_tank_y - 1][my_tank_x + 1] != '1' && map[my_tank_y - 2][my_tank_x + 1] != '1')
					my_tank_x++;
				else
					move += 5;
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (my_tank_x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b     ");
				Sleep(100);
				gotoxy(my_tank_x, my_tank_y);
				printf(" ");

				while (map[my_tank_y + 1][my_tank_x - 1] != '1') {// 내려갈 때
					if (my_tank_y == 40)
						exit(0);
					my_tank_y++;
				}
				while (map[my_tank_y][my_tank_x - 1] == '1' && map[my_tank_y - 1][my_tank_x - 1] == '0') { // 올라갈 때
					my_tank_y--;
				}
				if (map[my_tank_y - 1][my_tank_x - 1] != '1' && map[my_tank_y - 2][my_tank_x - 1] != '1')
					my_tank_x--;
				else
					move += 5;
			}
		}
		gotoxy(150, 46);
		printf("%02d", count);
	}
	enemyTurn();
}
void enemyTurn() {
	static int enemy_health = 100;
	int angle = 45;
	int power = 0;
	int move = 100;

	static int headingFlag = 2; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char enemy_tank = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(my_tank_x, my_tank_y);
		printf("%c", enemy_tank);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemy_tank_x, enemy_tank_y);
		printf("%c", enemy_tank);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i < MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("체력 ");

		for (int i = 0; i < enemy_health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (enemy_health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (enemy_health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		gotoxy(30, 44);
		printf("파워 ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			Sleep(100);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					fire(angle, power, enemy_tank_x, enemy_tank_y, headingFlag);
					myTurn();
				}
				if (power == 100) {
					power = 0;
					break;
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(30, 46);
		printf("이동 ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for (int i = 0; i < move; i++)
			printf("|");
		if (KEYDOWN(VK_RIGHT)) { // 오른쪽 방향키 입력 시 우측으로 이동
			if (my_tank_x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(100);
				gotoxy(enemy_tank_x, enemy_tank_y);
				printf(" ");

				while (map[enemy_tank_y + 1][enemy_tank_x + 1] != '1') { // 내려갈 때
					if (enemy_tank_y == 40)
						exit(0);
					enemy_tank_y++;
				}
				while (map[enemy_tank_y][enemy_tank_x + 1] == '1' && map[enemy_tank_y - 1][enemy_tank_x + 1] == '0') {// 올라갈 때
					enemy_tank_y--;
				}
				if (map[enemy_tank_y - 1][enemy_tank_x + 1] != '1' && map[enemy_tank_y - 2][enemy_tank_x + 1] != '1')
					enemy_tank_x++;
				else
					move += 5;
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (my_tank_x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(100);
				gotoxy(enemy_tank_x, enemy_tank_y);
				printf(" ");

				while (map[enemy_tank_y + 1][enemy_tank_x - 1] != '1') {// 내려갈 때
					if (enemy_tank_y == 40)
						exit(0);
					enemy_tank_y++;
				}
				while (map[enemy_tank_y][enemy_tank_x - 1] == '1' && map[enemy_tank_y - 1][enemy_tank_x - 1] == '0') { // 올라갈 때
					enemy_tank_y--;
				}
				if (map[enemy_tank_y - 1][enemy_tank_x - 1] != '1' && map[enemy_tank_y - 2][enemy_tank_x - 1] != '1')
					enemy_tank_x--;
				else
					move += 5;
			}
		}

		gotoxy(150, 46);
		printf("%02d", count);
	}
	myTurn();
}
int fire(int angle, int power, int tank_x, int tank_y, int heading) {
	const double GRAVITY = 9.8;
	double radian, time = 0;
	int x, y, dmg = 0;

	power /= 2;
	radian = angle * 3.14 / 180;

	while (1) {
		time += 0.01;
		if (heading  == 1)
			x = tank_x + (power * cos(radian) * time);
		else
			x = tank_x - (power * cos(radian) * time);
		y = tank_y - (power * sin(radian) * time - 0.5 * GRAVITY * time * time);
		if (y > 0) {
			gotoxy(x, y);
			printf("%s", "○");
			Sleep(10);
			printf("\b\b  ");
		}
		else
			Sleep(10);
		if (map[y][x] == '1') { // 포탄이 지형에 닿았을 경우 지형이 파이는 효과 구현
			for (int i = 0; i < 5; i++) {
				map[y][x + i] = '0';
				map[y][x - i] = '0';
			}
			for (int j = 0; j < 3; j++) {
				map[y + 1][x + j] = '0';
				map[y + 1][x - j] = '0';
			}
			if (map[enemy_tank_y + 1][enemy_tank_x] == '0')
				while (map[enemy_tank_y + 1][enemy_tank_x] != '1') {
					if (enemy_tank_y == 40)
						exit(0);
					else
						enemy_tank_y++;
				}
			if (map[my_tank_y + 1][my_tank_x] == '0')
				while (map[my_tank_y + 1][my_tank_x] != '1') {
					if (my_tank_y == 40)
						exit(0);
					else
						my_tank_y++;
				}
			break;
		}
		if (x > MAX_X_WIDTH || y >= 40) // 포탄이 맵의 x축 또는 y축을 벗어날 경우
			break;
	}
	return dmg;
}
void countDown() { // 카운트다운 스레드 선언
	while (count > 0 && fireFlag == 0)
	{
		Sleep(1000);
		count--;
	}
	countFlag = 0;
	return;
}
void init() { // 초기화 함수
	_beginthreadex(NULL, 0, countDown, 0, 0, NULL);
	fireFlag = 0;
	countFlag = 1;
	count = 15;
	while (map[my_tank_y + 1][my_tank_x + 1] != '1') {
		my_tank_y++;
	}
	while (map[enemy_tank_y + 1][enemy_tank_x + 1] != '1') {
		enemy_tank_y++;
	}
}
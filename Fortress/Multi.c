#include "define.h"

#define KEYDOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000 ? 1 : 0))

struct tank { //탱크의 좌표 정보와 체력 정보를 가지는 구조체 생성
	int x;
	int y;
	int health;
};

unsigned __stdcall countDown();
void enemyTurn();
void fire(int, int, int, int, int);
void init();
void myTurn();

static int fireFlag = 0;
static int countFlag = 1;
static int count = 15;
struct tank my_tank = { 10, 20, 100 };
struct tank enemy_tank = { 30, 20, 100 };

void multiStart() {
	stopMusic(1);
	playMusic(2);
	readMap();
	myTurn();
}
void myTurn() {
	static int angle = 45;
	int power = 0;
	int move = 100;

	static int headingFlag = 1; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(my_tank.x, my_tank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemy_tank.x, enemy_tank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < my_tank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (my_tank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (my_tank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], angle);
		if (KEYDOWN(VK_UP)) {
			if (angle < 90) {
				Sleep(30);
				angle++;
			}
		}
		if (KEYDOWN(VK_DOWN)) {
			if (angle > 10) {
				Sleep(30);
				angle--;
			}
		}
		gotoxy(30, 44);
		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			Sleep(150);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					fire(angle, power, my_tank.x, my_tank.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireFlag = 1;
					fire(angle, power, my_tank.x, my_tank.y, headingFlag);
					break;
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(30, 46);
		printf("%s ", lang[8]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for (int i = 0; i < move; i++)
			printf("|");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		if (KEYDOWN(VK_RIGHT)) { // 오른쪽 방향키 입력 시 우측으로 이동
			if (my_tank.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(my_tank.x, my_tank.y);
				printf(" ");
				gotoxy(enemy_tank.x, enemy_tank.y - 2);

				while (map[my_tank.y + 1][my_tank.x + 1] != '1') { // 내려갈 때
					if (my_tank.y == 40)
						exit(0);
					my_tank.y++;
				}
				while (map[my_tank.y][my_tank.x + 1] == '1' && map[my_tank.y - 1][my_tank.x + 1] == '0') { // 올라갈 때
					my_tank.y--;
				}
				if (map[my_tank.y][my_tank.x + 1] != '1') // 이동이 가능하면 x축 조정
					my_tank.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (my_tank.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(my_tank.x, my_tank.y);
				printf(" ");
				gotoxy(enemy_tank.x, enemy_tank.y - 2);

				while (map[my_tank.y + 1][my_tank.x - 1] != '1') {// 내려갈 때
					if (my_tank.y == 40)
						exit(0);
					my_tank.y++;
				}
				while (map[my_tank.y][my_tank.x - 1] == '1' && map[my_tank.y - 1][my_tank.x - 1] == '0') { // 올라갈 때
					my_tank.y--;
				}
				if (map[my_tank.y][my_tank.x - 1] != '1') // 이동이 가능하면 x축 조정
					my_tank.x--;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		gotoxy(150, 46);
		printf("%02d", count);
	}
	Sleep(10);
	enemyTurn();
}
void enemyTurn() {
	static int angle = 45;
	int power = 0;
	int move = 100;

	static int headingFlag = 2; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(my_tank.x, my_tank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemy_tank.x, enemy_tank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < enemy_tank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (enemy_tank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (enemy_tank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], angle);
		if (KEYDOWN(VK_UP)) {
			if (angle < 90) {
				Sleep(30);
				angle++;
			}
		}
		if (KEYDOWN(VK_DOWN)) {
			if (angle > 10) {
				Sleep(30);
				angle--;
			}
		}
		gotoxy(30, 44);
		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			Sleep(150);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					fire(angle, power, enemy_tank.x, enemy_tank.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireFlag = 1;
					fire(angle, power, enemy_tank.x, enemy_tank.y, headingFlag);
					break;
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(30, 46);
		printf("%s ", lang[8]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for (int i = 0; i < move; i++)
			printf("|");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		if (KEYDOWN(VK_RIGHT)) { // 오른쪽 방향키 입력 시 우측으로 이동
			if (enemy_tank.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(enemy_tank.x, enemy_tank.y);
				printf(" ");

				while (map[enemy_tank.y + 1][enemy_tank.x + 1] != '1') { // 내려갈 때
					if (enemy_tank.y == 40)
						exit(0);
					enemy_tank.y++;
				}
				while (map[enemy_tank.y][enemy_tank.x + 1] == '1' && map[enemy_tank.y - 1][enemy_tank.x + 1] == '0') {// 올라갈 때
					enemy_tank.y--;
				}
				if (map[enemy_tank.y][enemy_tank.x + 1] != '1') // 이동이 가능하면 x축 조정
					enemy_tank.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (enemy_tank.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(enemy_tank.x, enemy_tank.y);
				printf(" ");

				while (map[enemy_tank.y + 1][enemy_tank.x - 1] != '1') { // 내려갈 때
					if (enemy_tank.y == 40)
						exit(0);
					enemy_tank.y++;
				}
				while (map[enemy_tank.y][enemy_tank.x - 1] == '1' && map[enemy_tank.y - 1][enemy_tank.x - 1] == '0') { // 올라갈 때
					enemy_tank.y--;
				}
				if (map[enemy_tank.y][enemy_tank.x - 1] != '1') // 이동이 가능하면 x축 조정
					enemy_tank.x--;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}

		gotoxy(150, 46);
		printf("%02d", count);
	}
	Sleep(10);
	myTurn();
}
void fire(int angle, int power, int tank_x, int tank_y, int heading) { // 발사했을 때 포탄의 포물선 계산과 포탄 출력 역할 
	const double GRAVITY = 9.8;
	double radian, time = 0;
	int x, y;

	power /= 2;
	radian = angle * 3.14 / 180;

	playFX(4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	while (1) {
		time += 0.01;
		if (heading  == 1)
			x = (int)(tank_x + (power * cos(radian) * time));
		else
			x = (int)(tank_x - (power * cos(radian) * time));

		y = (int)(tank_y - (power * sin(radian) * time - 0.5 * GRAVITY * time * time));

		if (x <= 0 || x >= MAX_X_WIDTH || y > 40) // 포탄이 맵의 x축 또는 y축 하단을 벗어날 경우
			break;

		if (y > 0) {
			gotoxy(x, y);
			printf("%s", "●");
			Sleep(8);
			printf("\b\b  ");
		}
		else
			Sleep(8);
		if (map[y][x] == '1') { // 포탄이 지형에 닿았을 경우 지형이 파이는 효과 구현
			playFX(rand() % 3 + 5);
			for (int i = 0; i < 5; i++) {
				if (x + i == my_tank.x) {
					switch (i) {
						case 0:
							my_tank.health -= 30;
							break;
						case 1:
							my_tank.health -= 16;
							break;
						case 2:
							my_tank.health -= 14;
							break;
						case 3:
							my_tank.health -= 12;
							break;
						case 4:
							my_tank.health -= 10;
					}
				}
				if (x + i == enemy_tank.x) {
					switch (i) {
					case 0:
						enemy_tank.health -= 30;
						break;
					case 1:
						enemy_tank.health -= 16;
						break;
					case 2:
						enemy_tank.health -= 14;
						break;
					case 3:
						enemy_tank.health -= 12;
						break;
					case 4:
						enemy_tank.health -= 10;
					}
				}
				if (x + i <= MAX_X_WIDTH) {
					map[y][x + i] = '0';
					map[y][x - i] = '0';
				}
			}
			for (int j = 0; j < 3; j++) {
				if (x + j <= MAX_X_WIDTH) {
					map[y + 1][x + j] = '0';
					map[y + 1][x - j] = '0';
				}
			}
			if (map[enemy_tank.y + 1][enemy_tank.x] == '0')
				while (map[enemy_tank.y + 1][enemy_tank.x] != '1') {
					if (enemy_tank.y == 40)
						exit(0);
					else
						enemy_tank.y++;
				}
			if (map[my_tank.y + 1][my_tank.x] == '0')
				while (map[my_tank.y + 1][my_tank.x] != '1') {
					if (my_tank.y == 40)
						exit(0);
					else
						my_tank.y++;
				}
			break;
		}
	}
}
unsigned __stdcall countDown() { // 카운트다운 스레드 선언
	while (count > 0 && fireFlag == 0) {
		Sleep(1000);
		count--;
		if (count >= 5)
			playFX(1);
		else
			playFX(2);
	}
	countFlag = 0;
	return;
}
void init() { // 초기화 함수
	_beginthreadex(NULL, 0, countDown, 0, 0, NULL);
	fireFlag = 0;
	countFlag = 1;
	count = 15;
	while (map[my_tank.y + 1][my_tank.x + 1] != '1') {
		my_tank.y++;
	}
	while (map[enemy_tank.y + 1][enemy_tank.x + 1] != '1') {
		enemy_tank.y++;
	}
}
#include "define.h"

#define KEYDOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000 ? 1 : 0))

struct tank { //탱크의 좌표 정보와 체력 정보를 가지는 구조체 생성
	int x;
	int y;
	int health;
	int angle;
};

unsigned __stdcall countDown();
void enemyTurn();
void fire(int, int, int, int, int);
void init();
void myTurn();

static int mapRand;
static int fireFlag = 0;
static int countStop = 0;
static int countFlag = 1;
static int count = 15;
struct tank myTank = { 10, 10, 100, 45 };
struct tank enemyTank = { 150, 10, 100, 45 };

void localStart() {
	stopMusic(1);
	srand(time(NULL));
	mapRand = rand() % 3 + 1;
	readMap(mapRand);
	myTank.x = 10;
	myTank.y = 10;
	myTank.health = 100;
	myTank.angle = 45;
	enemyTank.x = 150;
	enemyTank.y = 10;
	enemyTank.health = 100;
	enemyTank.angle = 45;
 	myTurn();
}
void myTurn() {
	int power = 0;
	int move = 100;

	static int headingFlag = 1; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(myTank.x, myTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemyTank.x, enemyTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < myTank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (myTank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (myTank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], myTank.angle);
		if (KEYDOWN(VK_UP)) {
			if (myTank.angle < 90) {
				Sleep(30);
				myTank.angle++;
			}
		}
		if (KEYDOWN(VK_DOWN)) {
			if (myTank.angle > 10) {
				Sleep(30);
				myTank.angle--;
			}
		}
		gotoxy(30, 44);
		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			countStop = 1;
			Sleep(150);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					fire(myTank.angle, power, myTank.x, myTank.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireFlag = 1;
					fire(myTank.angle, power, myTank.x, myTank.y, headingFlag);
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
			if (myTank.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(myTank.x, myTank.y);
				printf(" ");
				gotoxy(enemyTank.x, enemyTank.y - 2);

				while (map[myTank.y + 1][myTank.x + 1] != '1') { // 내려갈 때
					if (myTank.y == 40) {// 맵 밖으로 이탈했을 때
						countStop = 1;
						p2VictoryLocal();
					}
					myTank.y++;
				}
				while (map[myTank.y][myTank.x + 1] == '1' && map[myTank.y - 1][myTank.x + 1] == '0') { // 올라갈 때
					myTank.y--;
				}
				if (map[myTank.y][myTank.x + 1] != '1') // 이동이 가능하면 x축 조정
					myTank.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (myTank.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(myTank.x, myTank.y);
				printf(" ");
				gotoxy(enemyTank.x, enemyTank.y - 2);

				while (map[myTank.y + 1][myTank.x - 1] != '1') {// 내려갈 때
					if (myTank.y == 40) {
						countStop = 1;
						p2VictoryLocal();
					}
					myTank.y++;
				}
				while (map[myTank.y][myTank.x - 1] == '1' && map[myTank.y - 1][myTank.x - 1] == '0') { // 올라갈 때
					myTank.y--;
				}
				if (map[myTank.y][myTank.x - 1] != '1') // 이동이 가능하면 x축 조정
					myTank.x--;
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
	int power = 0;
	int move = 100;

	static int headingFlag = 2; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	init();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(myTank.x, myTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(enemyTank.x, enemyTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < enemyTank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (enemyTank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (enemyTank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], enemyTank.angle);
		if (KEYDOWN(VK_UP)) {
			if (enemyTank.angle < 90) {
				Sleep(30);
				enemyTank.angle++;
			}
		}
		if (KEYDOWN(VK_DOWN)) {
			if (enemyTank.angle > 10) {
				Sleep(30);
				enemyTank.angle--;
			}
		}
		gotoxy(30, 44);
		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (KEYDOWN(VK_SPACE)) {
			countStop = 1;
			Sleep(150);
			while (power <= 100) {
				power++;
				Sleep(30);
				printf("|");
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					fire(enemyTank.angle, power, enemyTank.x, enemyTank.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireFlag = 1;
					fire(enemyTank.angle, power, enemyTank.x, enemyTank.y, headingFlag);
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
			if (enemyTank.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(enemyTank.x, enemyTank.y);
				printf(" ");

				while (map[enemyTank.y + 1][enemyTank.x + 1] != '1') { // 내려갈 때
					if (enemyTank.y == 40) { // 맵 밖으로 이탈했을 때
						countStop = 1;
						p1VictoryLocal();
					}
					enemyTank.y++;
				}
				while (map[enemyTank.y][enemyTank.x + 1] == '1' && map[enemyTank.y - 1][enemyTank.x + 1] == '0') {// 올라갈 때
					enemyTank.y--;
				}
				if (map[enemyTank.y][enemyTank.x + 1] != '1') // 이동이 가능하면 x축 조정
					enemyTank.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (enemyTank.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(enemyTank.x, enemyTank.y);
				printf(" ");

				while (map[enemyTank.y + 1][enemyTank.x - 1] != '1') { // 내려갈 때
					if (enemyTank.y == 40) {
						countStop = 1;
						p2VictoryLocal();
					}
					enemyTank.y++;
				}
				while (map[enemyTank.y][enemyTank.x - 1] == '1' && map[enemyTank.y - 1][enemyTank.x - 1] == '0') { // 올라갈 때
					enemyTank.y--;
				}
				if (map[enemyTank.y][enemyTank.x - 1] != '1') // 이동이 가능하면 x축 조정
					enemyTank.x--;
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
	int dmg = 0;

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
		if (map[y][x] == '1') { // 포탄이 지형에 닿았을 경우 지형이 파이는 효과와 피격시 데미지 구현
			playFX(rand() % 3 + 5);
			for (int i = 0; i < 5; i++) {
				if (x + i == myTank.x || x - i == myTank.x) {
					switch (i) {
						case 0:
							dmg = 30;
							break;
						case 1:
							dmg = 16;
							break;
						case 2:
							dmg = 14;
							break;
						case 3:
							dmg = 12;
							break;
						case 4:
							dmg = 10;
					}
				}
				if (x + i == enemyTank.x || x - i == enemyTank.x) {
					switch (i) {
					case 0:
						dmg = 30;
						break;
					case 1:
						dmg = 16;
						break;
					case 2:
						dmg = 14;
						break;
					case 3:
						dmg = 12;
						break;
					case 4:
						dmg = 10;
					}
				}
				if (x + i <= MAX_X_WIDTH) {
					map[y][x + i] = '0';
					map[y][x - i] = '0';
				}
			}
			for (int j = 0; j < 3; j++) {
				if ((x + j == myTank.x || x - j == myTank.x) && (y == myTank.y || y - 1 == myTank.y || y + 1 == myTank.y)) {
						myTank.health -= dmg;
						if (myTank.health <= 0)
							p2VictoryLocal();
				}
				if ((x + j == enemyTank.x || x - j == enemyTank.x) && (y == enemyTank.y || y - 1 == enemyTank.y || y + 1 == enemyTank.y)) {
						enemyTank.health -= dmg;
						if (enemyTank.health <= 0)
							p1VictoryLocal();
				}
				if (x + j <= MAX_X_WIDTH) {
					map[y + 1][x + j] = '0';
					map[y + 1][x - j] = '0';
				}
			}
			if (map[enemyTank.y + 1][enemyTank.x] == '0')
				while (map[enemyTank.y + 1][enemyTank.x] != '1') {
					if (enemyTank.y == 40)
						p1VictoryLocal();
					else
						enemyTank.y++;
				}
			if (map[myTank.y + 1][myTank.x] == '0')
				while (map[myTank.y + 1][myTank.x] != '1') {
					if (myTank.y == 40)
						p2VictoryLocal();
					else
						myTank.y++;
				}
			break;
		}
	}
}
unsigned __stdcall countDown() { // 카운트다운 스레드 선언
	while (count > 0 && fireFlag == 0) {
		Sleep(1000);
		if (!countStop) {
			count--;
			if (count >= 5)
				playFX(1);
			else
				playFX(2);
		}
	}
	countFlag = 0;
	return;
}
void init() { // 초기화 함수
	_beginthreadex(NULL, 0, countDown, 0, 0, NULL);
	fireFlag = 0;
	countStop = 0;
	countFlag = 1;
	count = 15;
	while (map[myTank.y + 1][myTank.x] != '1') {
		myTank.y++;
	}
	while (map[enemyTank.y + 1][enemyTank.x] != '1') {
		enemyTank.y++;
	}
}
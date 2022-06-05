#include "define.h"

#define KEYDOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000 ? 1 : 0))

struct tank { //탱크의 좌표 정보와 체력 정보를 가지는 구조체 생성
	int x;
	int y;
	int health;
	int angle;
};

unsigned __stdcall countDownSingle();
void comTurn(int, int);
void fireSingle(int, int, int, int, int);
void initSingle();
void initSingleCom();
void myTurnSingle();

static int mapRand;
static int fireSingleFlag = 0;
static int countStop = 0;
static int countFlag = 1;
static int count = 15;
struct tank myTankSingle = { 10, 10, 100, 45 };
struct tank comTank = { 150, 10, 100, 45 };

void singleStart() {
	srand(time(NULL));
	stopMusic(1);
	mapRand = rand() % 3 + 1;
	readMap(mapRand);
	myTankSingle.x = 10;
	myTankSingle.y = 10;
	myTankSingle.health = 100;
	myTankSingle.angle = 45;
	comTank.x = 150;
	comTank.y = 10;
	comTank.health = 100;
	comTank.angle = 45;
	myTurnSingle();
}
void myTurnSingle() {
	int power = 0;
	int move = 100;

	static int headingFlag = 1; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	initSingle();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(myTankSingle.x, myTankSingle.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(comTank.x, comTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < myTankSingle.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (myTankSingle.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (myTankSingle.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], myTankSingle.angle);
		if (KEYDOWN(VK_UP)) {
			if (myTankSingle.angle < 90) {
				Sleep(30);
				myTankSingle.angle++;
			}
		}
		if (KEYDOWN(VK_DOWN)) {
			if (myTankSingle.angle > 10) {
				Sleep(30);
				myTankSingle.angle--;
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
					fireSingleFlag = 1;
					fireSingle(myTankSingle.angle, power, myTankSingle.x, myTankSingle.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireSingleFlag = 1;
					fireSingle(myTankSingle.angle, power, myTankSingle.x, myTankSingle.y, headingFlag);
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
			if (myTankSingle.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(myTankSingle.x, myTankSingle.y);
				printf(" ");
				gotoxy(comTank.x, comTank.y - 2);

				while (map[myTankSingle.y + 1][myTankSingle.x + 1] != '1') { // 내려갈 때
					if (myTankSingle.y == 40) {
						countStop = 1;
						comVictorySingle();
					}
					myTankSingle.y++;
				}
				while (map[myTankSingle.y][myTankSingle.x + 1] == '1' && map[myTankSingle.y - 1][myTankSingle.x + 1] == '0') { // 올라갈 때
					myTankSingle.y--;
				}
				if (map[myTankSingle.y][myTankSingle.x + 1] != '1') // 이동이 가능하면 x축 조정
					myTankSingle.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (myTankSingle.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(myTankSingle.x, myTankSingle.y);
				printf(" ");
				gotoxy(comTank.x, comTank.y - 2);

				while (map[myTankSingle.y + 1][myTankSingle.x - 1] != '1') {// 내려갈 때
					if (myTankSingle.y == 40) {
						countStop = 1;
						comVictorySingle();
					}
					myTankSingle.y++;
				}
				while (map[myTankSingle.y][myTankSingle.x - 1] == '1' && map[myTankSingle.y - 1][myTankSingle.x - 1] == '0') { // 올라갈 때
					myTankSingle.y--;
				}
				if (map[myTankSingle.y][myTankSingle.x - 1] != '1') // 이동이 가능하면 x축 조정
					myTankSingle.x--;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		gotoxy(150, 46);
		printf("%02d", count);
	}
	Sleep(10);
	comTurn(myTankSingle.angle + (rand() % 5 - 5), power + (rand() % 7 - 7));
}
void comTurn(int ang, int pow) {
	static int angle = 45;
	int power = 0;
	int move = 100;

	static int headingFlag = 2; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

	char t = '@';

	initSingleCom();
	system("cls");
	printMap();

	while (countFlag) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(myTankSingle.x, myTankSingle.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(comTank.x, comTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);
		for (int i = 0; i < comTank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (comTank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (comTank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], angle);
		while (angle != ang) {
			if (angle > ang)
				angle--;
			else
				angle++;
			gotoxy(20, 44);
			printf("%s %d", lang[6], angle);
			Sleep(30);
		}
		gotoxy(30, 44);
		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		while (power != pow) {
			if (pow <= 0)
				pow = rand() % 80 + 20;
			power++;
			Sleep(30);
			printf("|");
		}
		fireSingle(angle, power, comTank.x, comTank.y, headingFlag);
		break;
	}
	Sleep(10);
	myTurnSingle();
}
void fireSingle(int angle, int power, int tank_x, int tank_y, int heading) { // 발사했을 때 포탄의 포물선 계산과 포탄 출력 역할 
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
		if (heading == 1)
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
				if (x + i == myTankSingle.x || x - i == myTankSingle.x) {
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
				if (x + i == comTank.x || x - i == comTank.x) {
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
				if ((x + j == myTankSingle.x || x - j == myTankSingle.x) && (y == myTankSingle.y || y - 1 == myTankSingle.y || y + 1 == myTankSingle.y)) {
					myTankSingle.health -= dmg;
					if (myTankSingle.health <= 0)
						comVictorySingle();
				}
				if ((x + j == comTank.x || x - j == comTank.x) && (y == comTank.y || y - 1 == comTank.y || y + 1 == comTank.y)) {
					comTank.health -= dmg;
					if (comTank.health <= 0)
						p1VictorySingle();
				}
				if (x + j <= MAX_X_WIDTH) {
					map[y + 1][x + j] = '0';
					map[y + 1][x - j] = '0';
				}
			}
			if (map[comTank.y + 1][comTank.x] == '0')
				while (map[comTank.y + 1][comTank.x] != '1') {
					if (comTank.y == 40)
						p1VictorySingle();
					else
						comTank.y++;
				}
			if (map[myTankSingle.y + 1][myTankSingle.x] == '0')
				while (map[myTankSingle.y + 1][myTankSingle.x] != '1') {
					if (myTankSingle.y == 40)
						comVictorySingle();
					else
						myTankSingle.y++;
				}
			break;
		}
	}
}
unsigned __stdcall countDownSingle() { // 카운트다운 스레드 선언
	while (count > 0 && fireSingleFlag == 0) {
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
void initSingle() { // 초기화 함수
	_beginthreadex(NULL, 0, countDownSingle, 0, 0, NULL);
	fireSingleFlag = 0;
	countStop = 0;
	countFlag = 1;
	count = 15;
	while (map[myTankSingle.y + 1][myTankSingle.x] != '1') {
		myTankSingle.y++;
	}
	while (map[comTank.y + 1][comTank.x] != '1') {
		comTank.y++;
	}
}
void initSingleCom() { // 컴퓨터 초기화 함수
	fireSingleFlag = 0;
	countFlag = 1;
	while (map[myTankSingle.y + 1][myTankSingle.x] != '1') {
		myTankSingle.y++;
	}
	while (map[comTank.y + 1][comTank.x] != '1') {
		comTank.y++;
	}
}
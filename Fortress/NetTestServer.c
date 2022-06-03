#include "define.h"
#define KEYDOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000 ? 1 : 0))

struct tank { //탱크의 좌표 정보와 체력 정보를 가지는 구조체 생성
	int x;
	int y;
	int health;
};
unsigned __stdcall countDownSer();
void fireSer(int, int, int, int, int);
void initSer();
void serTurnSer(SOCKET, SOCKADDR_IN, int);
void cliTurnSer(SOCKET, SOCKADDR_IN, int);
void sendToCli(SOCKET, SOCKADDR_IN, int, int, int, int);
void server();

static int sendFireToCli = 0;
static int fireFlag = 0;
static int countFlag = 1;
static int count;
static int headingFlag = 1; // 탱크가 보는 방향 설정, 1 : 오른쪽, 2 : 왼쪽

static struct tank serTank = { 10, 20, 100 };
static struct tank cliTank = { 30, 20, 100 };

void netStartSer() {
	readMap();
	server();
}
void server() {
	static SOCKADDR_IN sin, cli_addr;
	static SOCKET s, cs;
	static WSADATA wsaData;
	static int cli_size;

	system("cls");

	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {

		printf("WSAStartup 실패, 에러코드 : %d\n", WSAGetLastError());
		return;
	}
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (s == INVALID_SOCKET) {
		printf("소켓 생성 실패, 에러코드 : %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5000);
	sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);

	if (bind(s, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("bind 실패 , 에러코드 : %d\n", WSAGetLastError());
		closesocket(s); WSACleanup();
		return;
	}
	if (listen(s, SOMAXCONN) != 0) {
		printf("listen 모드 설정 실패 , 에러코드 : %d\n", WSAGetLastError());
		closesocket(s); WSACleanup();
		return;
	}
	printf("서버 생성 완료\n");
	printf("상대방의 접속을 기다리는 중 ...\n");
	cli_size = sizeof(cli_addr);
	cs = accept(s, (SOCKADDR*)&cli_addr, &cli_size);

	if (cs == INVALID_SOCKET) {
		printf("접속 승인 실패, 에러코드 : %d\n", WSAGetLastError());
		closesocket(s); WSACleanup();
		return;
	}
	stopMusic(1);
	playMusic(2);
	serTurnSer(cs, cli_addr, cli_size);
}
void serTurnSer(SOCKET s, SOCKADDR_IN c_addr, int c_size) {
	static int angle = 45;
	int power = 0;
	int move = 100;

	SOCKET cs = s;
	SOCKADDR_IN cli_addr = c_addr;
	int cli_size = c_size;

	char t = '@';

	initSer();
	system("cls");
	printMap();

	while (countFlag) {
		sendToCli(cs, cli_addr, cli_size, move, angle, power);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(serTank.x, serTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(cliTank.x, cliTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < serTank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (serTank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (serTank.health < 50)
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
				sendToCli(cs, cli_addr, cli_size, move, angle, power);
				if (KEYDOWN(VK_SPACE)) {
					fireFlag = 1;
					sendToCli(cs, cli_addr, cli_size, move, angle, power);
					fireSer(angle, power, serTank.x, serTank.y, headingFlag);
					break;
				}
				if (power == 100) {
					fireFlag = 1;
					sendToCli(cs, cli_addr, cli_size, move, angle, power);
					fireSer(angle, power, serTank.x, serTank.y, headingFlag);
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
			if (serTank.x < MAX_X_WIDTH) {
				headingFlag = 1;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(serTank.x, serTank.y);
				printf(" ");

				while (map[serTank.y + 1][serTank.x + 1] != '1') { // 내려갈 때
					if (serTank.y == 40) // 맵 밖으로 이탈했을 때
						exit(0);
					serTank.y++;
				}
				while (map[serTank.y][serTank.x + 1] == '1' && map[serTank.y - 1][serTank.x + 1] == '0') { // 올라갈 때
					serTank.y--;
				}
				if (map[serTank.y][serTank.x + 1] != '1') // 이동이 가능하면 x축 조정
					serTank.x++;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		if (KEYDOWN(VK_LEFT)) { // 왼쪽 방향키 입력 시 좌측으로 이동
			if (serTank.x > 0) {
				headingFlag = 2;
				if (move <= 0)
					continue;
				move -= 5;
				printf("\b\b\b\b\b      ");
				Sleep(80);
				gotoxy(serTank.x, serTank.y);
				printf(" ");

				while (map[serTank.y + 1][serTank.x - 1] != '1') {// 내려갈 때
					if (serTank.y == 40)
						exit(0);
					serTank.y++;
				}
				while (map[serTank.y][serTank.x - 1] == '1' && map[serTank.y - 1][serTank.x - 1] == '0') { // 올라갈 때
					serTank.y--;
				}
				if (map[serTank.y][serTank.x - 1] != '1') // 이동이 가능하면 x축 조정
					serTank.x--;
				else
					move += 5; // 이동이 불가능하면 이동 게이지 다시 증가
				playFX(3);
			}
		}
		gotoxy(150, 46);
		printf("%02d", count);
	}
	cliTurnSer(cs, cli_addr, cli_size);
}
void cliTurnSer(SOCKET s, SOCKADDR_IN c_addr, int c_size) {
	SOCKET cs = s;
	SOCKADDR_IN cli_addr = c_addr;
	int cli_size = c_size;

	static int angle = 45;
	int moveTemp = 100;
	int xTemp = cliTank.x;
	int yTemp = cliTank.y;
	int power = 0;
	int move = 100;

	char t = '@';

	initSer();
	system("cls");
	printMap();

	while (countFlag) {
		recvfrom(cs, &move, sizeof(move), 0, &cli_addr, &cli_size);
		recvfrom(cs, &angle, sizeof(angle), 0, &cli_addr, &cli_size);
		recvfrom(cs, &power, sizeof(power), 0, &cli_addr, &cli_size);
		recvfrom(cs, &cliTank.x, sizeof(cliTank.x), 0, &cli_addr, &cli_size);
		recvfrom(cs, &cliTank.y, sizeof(cliTank.y), 0, &cli_addr, &cli_size);
		recvfrom(cs, &fireFlag, sizeof(fireFlag), 0, &cli_addr, &cli_size);
		recvfrom(cs, &headingFlag, sizeof(headingFlag), 0, &cli_addr, &cli_size);

		if (moveTemp != move) {
			gotoxy(xTemp, yTemp);
			printf(" ");
		}
		moveTemp = move;
		xTemp = cliTank.x;
		yTemp = cliTank.y;

		if (fireFlag)
			fireSer(angle, power, cliTank.x, cliTank.y, headingFlag);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		gotoxy(serTank.x, serTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		gotoxy(cliTank.x, cliTank.y);
		printf("%c", t);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 40);
		for (int i = 0; i <= MAX_X_WIDTH; i++)
			printf("-");

		gotoxy(30, 42);
		printf("%s ", lang[5]);

		for (int i = 0; i < cliTank.health; i++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			if (cliTank.health < 30)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			else if (cliTank.health < 50)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("|");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(20, 44);
		printf("%s %d", lang[6], angle);
		gotoxy(30, 44);

		printf("%s ", lang[7]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int i = 0; i < power; i++)
			printf("|");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(30, 46);
		printf("%s ", lang[8]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for (int i = 0; i < move; i++)
			printf("|");
		if (move < 100) {
			printf("|||||");
			for (int i = 0; i < (100 - move) / 5; i++)
				printf("\b\b\b\b\b      ");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(150, 46);
		printf("%02d", count);

	}
	serTurnSer(cs, cli_addr, cli_size);

}
void netStopSer() {
	//if (closesocket(cs) != 0 || closesocket(s) != 0) {
	//	printf("소켓 제거 실패, 에러코드 : %d\n", WSAGetLastError());
	//	WSACleanup();
	//	return;
	//}
	//if (WSACleanup() != 0) {
	//	printf("WSACleanup 실패, 에러코드 : %d\n", WSAGetLastError());
	//	return;
	//}
	//printf("서버를 종료합니다\n");
	//return;
}
void fireSer(int angle, int power, int tank_x, int tank_y, int heading) { // 발사했을 때 포탄의 포물선 계산과 포탄 출력 역할 
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
				if (x + i == serTank.x || x - i == serTank.x) {
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
				if (x + i == cliTank.x || x - i == cliTank.x) {
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
				if ((x + j == serTank.x || x - j == serTank.x) && (y == serTank.y || y - 1 == serTank.y || y + 1 == serTank.y)) {
					serTank.health -= dmg;
				}
				if ((x + j == cliTank.x || x - j == cliTank.x) && (y == cliTank.y || y - 1 == cliTank.y || y + 1 == cliTank.y)) {
					cliTank.health -= dmg;
				}
				if (x + j <= MAX_X_WIDTH) {
					map[y + 1][x + j] = '0';
					map[y + 1][x - j] = '0';
				}
			}
			if (map[cliTank.y + 1][cliTank.x] == '0')
				while (map[cliTank.y + 1][cliTank.x] != '1') {
					if (cliTank.y == 40)
						exit(0);
					else
						cliTank.y++;
				}
			if (map[serTank.y + 1][serTank.x] == '0')
				while (map[serTank.y + 1][serTank.x] != '1') {
					if (serTank.y == 40)
						exit(0);
					else
						serTank.y++;
				}
			break;
		}
	}
}
unsigned __stdcall countDownSer() { // 카운트다운 스레드 선언
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
void initSer() { // 초기화 함수
	_beginthreadex(NULL, 0, countDownSer, 0, 0, NULL);
	fireFlag = 0;
	countFlag = 1;
	count = 99;
	while (map[serTank.y + 1][serTank.x + 1] != '1') {
		serTank.y++;
	}
	while (map[cliTank.y + 1][cliTank.x + 1] != '1') {
		cliTank.y++;
	}
}
void sendToCli(SOCKET cs, SOCKADDR_IN cli_addr, int cli_size, int move, int angle, int power) {
	sendto(cs, &move, sizeof(move), 0, &cli_addr, &cli_size);
	sendto(cs, &angle, sizeof(angle), 0, &cli_addr, &cli_size);
	sendto(cs, &power, sizeof(power), 0, &cli_addr, &cli_size);
	sendto(cs, &serTank.x, sizeof(serTank.x), 0, &cli_addr, &cli_size);
	sendto(cs, &serTank.y, sizeof(serTank.y), 0, &cli_addr, &cli_size);
	sendto(cs, &fireFlag, sizeof(fireFlag), 0, &cli_addr, &cli_size);
	sendto(cs, &headingFlag, sizeof(headingFlag), 0, &cli_addr, &cli_size);
}
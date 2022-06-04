#include "define.h"

int vicFlag;
int netSerCliCheck;
void vicMenuSel();

void p1VictoryLocal() {
	vicFlag = 1;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
	system("cls");
	gotoxy(0, 2);
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■■■      ■■  \n");
	printf("\t\t\t\t    ■■■   ■■     ■■        ■■            ■■     ■■     ■■ ■■     ■■  \n");
	printf("\t\t\t\t  ■■■■   ■■     ■■        ■■            ■■     ■■     ■■  ■■    ■■  \n");
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■   ■■   ■■  \n");
	printf("\t\t\t\t      ■■   ■■                 ■■   ■■     ■■     ■■     ■■    ■■  ■■  \n");
	printf("\t\t\t\t      ■■   ■■                  ■■  ■■    ■■      ■■     ■■     ■■ ■■  \n");
	printf("\t\t\t\t      ■■   ■■                   ■■■   ■■■        ■■     ■■      ■■■■  \n");
	vicMenuSel();
}
void p2VictoryLocal() {
	vicFlag = 1;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
	system("cls");
	gotoxy(0, 2);
	printf("\t\t\t\t      ■■■     ■■■■■          ■■            ■■     ■■     ■■■■      ■■  \n");
	printf("\t\t\t\t    ■■  ■■   ■■     ■■       ■■            ■■     ■■     ■■ ■■     ■■  \n");
	printf("\t\t\t\t         ■■    ■■     ■■       ■■            ■■     ■■     ■■  ■■    ■■  \n");
	printf("\t\t\t\t       ■■      ■■■■■          ■■            ■■     ■■     ■■   ■■   ■■  \n");
	printf("\t\t\t\t     ■■        ■■                ■■   ■■     ■■     ■■     ■■    ■■  ■■  \n");
	printf("\t\t\t\t   ■■          ■■                 ■■  ■■    ■■      ■■     ■■     ■■ ■■  \n");
	printf("\t\t\t\t   ■■■■■    ■■                  ■■■   ■■■        ■■     ■■      ■■■■  \n");
	vicMenuSel();
}
void p1VictorySingle() {
	vicFlag = 2;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
	system("cls");
	gotoxy(0, 2);
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■■■      ■■  \n");
	printf("\t\t\t\t    ■■■   ■■     ■■        ■■            ■■     ■■     ■■ ■■     ■■  \n");
	printf("\t\t\t\t  ■■■■   ■■     ■■        ■■            ■■     ■■     ■■  ■■    ■■  \n");
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■   ■■   ■■  \n");
	printf("\t\t\t\t      ■■   ■■                 ■■   ■■     ■■     ■■     ■■    ■■  ■■  \n");
	printf("\t\t\t\t      ■■   ■■                  ■■  ■■    ■■      ■■     ■■     ■■ ■■  \n");
	printf("\t\t\t\t      ■■   ■■                   ■■■   ■■■        ■■     ■■      ■■■■  \n");
	vicMenuSel();
}
void comVictorySingle() {
	vicFlag = 2;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
	system("cls");
	gotoxy(0, 2);
	printf("\t\t\t      ■■■    ■■■■■     ■■      ■■      ■■            ■■     ■■     ■■■■      ■■ \n");
	printf("\t\t\t    ■■        ■■     ■■  ■■      ■■      ■■            ■■     ■■     ■■ ■■     ■■ \n");
	printf("\t\t\t  ■■          ■■     ■■  ■■      ■■      ■■            ■■     ■■     ■■  ■■    ■■ \n");
	printf("\t\t\t  ■■          ■■■■■     ■■      ■■      ■■            ■■     ■■     ■■   ■■   ■■ \n");
	printf("\t\t\t  ■■          ■■           ■■      ■■      ■■   ■■     ■■     ■■     ■■    ■■  ■■ \n");
	printf("\t\t\t    ■■        ■■            ■■    ■■        ■■  ■■    ■■      ■■     ■■     ■■ ■■ \n");
	printf("\t\t\t      ■■■    ■■              ■■■■           ■■■   ■■■        ■■     ■■      ■■■■ \n");
	vicMenuSel();
}
void p1VictoryNet(int value) {
	vicFlag = 3;
	netSerCliCheck = value;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
    system("cls");
	gotoxy(0, 2);
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■■■      ■■  \n");
	printf("\t\t\t\t    ■■■   ■■     ■■        ■■            ■■     ■■     ■■ ■■     ■■  \n");
	printf("\t\t\t\t  ■■■■   ■■     ■■        ■■            ■■     ■■     ■■  ■■    ■■  \n");
	printf("\t\t\t\t      ■■   ■■■■■           ■■            ■■     ■■     ■■   ■■   ■■  \n");
	printf("\t\t\t\t      ■■   ■■                 ■■   ■■     ■■     ■■     ■■    ■■  ■■  \n");
	printf("\t\t\t\t      ■■   ■■                  ■■  ■■    ■■      ■■     ■■     ■■ ■■  \n");
	printf("\t\t\t\t      ■■   ■■                   ■■■   ■■■        ■■     ■■      ■■■■  \n");
	vicMenuSel();
}
void p2VictoryNet(int value) {
	vicFlag = 3;
	netSerCliCheck = value;
	stopMusic(2);
	stopMusic(3);
	stopMusic(4);
	playMusic(6);
	system("cls");
	gotoxy(0, 2);
	printf("\t\t\t\t      ■■■     ■■■■■          ■■            ■■     ■■     ■■■■      ■■  \n");
	printf("\t\t\t\t    ■■  ■■   ■■     ■■       ■■            ■■     ■■     ■■ ■■     ■■  \n");
	printf("\t\t\t\t         ■■    ■■     ■■       ■■            ■■     ■■     ■■  ■■    ■■  \n");
	printf("\t\t\t\t       ■■      ■■■■■          ■■            ■■     ■■     ■■   ■■   ■■  \n");
	printf("\t\t\t\t     ■■        ■■                ■■   ■■     ■■     ■■     ■■    ■■  ■■  \n");
	printf("\t\t\t\t   ■■          ■■                 ■■  ■■    ■■      ■■     ■■     ■■ ■■  \n");
	printf("\t\t\t\t   ■■■■■    ■■                  ■■■   ■■■        ■■     ■■      ■■■■  \n");
	vicMenuSel();
}
void vicMenuSel() {
	int flag = 1;
	int x = 50, y = 39;
	gotoxy(0, 35);
	printf("\t\t\t\t\t _________________________________________________________________________ \n");
	printf("\t\t\t\t\t|                                                                         |\n");
	printf("\t\t\t\t\t|                                                                         |\n");
	printf("\t\t\t\t\t|                                                                         |\n");
	printf("\t\t\t\t\t|                                                                         |\n");
	printf("\t\t\t\t\t|                                                                         |\n");
	printf("\t\t\t\t\t|_________________________________________________________________________|\n");
	gotoxy(x, y);
	printf("%s\n", lang[26]);
	gotoxy(x + 45, y);
	printf("%s\n", lang[11]);
	gotoxy(x, y - 2);
	printf("   ▼");
	while (1) {
		if (GetAsyncKeyState(VK_LEFT)) { // 방향키 왼쪽이 입력되었을 때
			if (flag == 2) {
				gotoxy(x, y - 2);
				printf("     ");
				gotoxy(x -= 45, y - 2);
				printf("   ▼");
				Sleep(200);
				flag--;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) { // 방향키 오른쪽이 입력되었을 때
			if (flag == 1) {
				gotoxy(x, y - 2);
				printf("     ");
				gotoxy(x += 45, y - 2);
				printf("   ▼");
				Sleep(200);
				flag++;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // 스페이스키가 입력되었을 때
			stopMusic(6);
			switch (flag) {
			case 1: // 다시 하기
				if (vicFlag == 1)
					localStart();
				if (vicFlag == 2)
					singleStart();
				if (vicFlag == 3) {
					if (netSerCliCheck == 1)
						netStartSer();
					if (netSerCliCheck == 2)
						netStartCli();
				}
				break;
			case 2: // 메인 메뉴
				Sleep(100);
				printMenu();
				break;
			}
		}
	}
}
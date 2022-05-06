#include <Windows.h>
#include "define.h"

void printMenu() { // 메인 메뉴 출력
    int flag = 1; //사용자가 어떤 메뉴를 선택했는지 확인하는 변수
    int i = 0;
    int x = 74, y = 40;

    system("mode con cols=160 lines=50"); // 콘솔 창 크기 지정 cols : 가로, lines : 세로

    gotoxy(0, 2);
    printf("\t\t\t\t\t########  #######  ########  ######## ########  ########  ######   ###### \n");
    printf("\t\t\t\t\t##       ##     ## ##     ##    ##    ##     ## ##       ##    ## ##    ##\n");
    printf("\t\t\t\t\t##       ##     ## ##     ##    ##    ##     ## ##       ##       ##  \n");
    printf("\t\t\t\t\t######   ##     ## ########     ##    ########  ######    ######   ######   \n");
    printf("\t\t\t\t\t##       ##     ## ##   ##      ##    ##   ##   ##             ##       ##\n");
    printf("\t\t\t\t\t##       ##     ## ##    ##     ##    ##    ##  ##       ##    ## ##    ##\n");
    printf("\t\t\t\t\t##        #######  ##     ##    ##    ##     ## ########  ######   ###### \n");

    gotoxy(x, 36);
    printf("%s\n", ch[i++]);
    gotoxy(x - 4, y);
    printf("▶  %s", ch[i++]);
    gotoxy(x, y + 2);
    printf("%s", ch[i++]);
    gotoxy(x, y + 4);
    printf("%s", ch[i++]);
    gotoxy(x, y + 6);
    printf("%s", ch[i++]);
    gotoxy(x, y);
    while (1) {
        if (GetAsyncKeyState(VK_UP)) { // 방향키 위가 입력되었을 때
            if (y > 40) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y -= 2);
                printf("▶");
                Sleep(100);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_DOWN)) { // 방향키 아래가 입력되었을 때
            if (y <= 44) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y += 2);
                printf("▶");
                Sleep(100);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) { // 스페이스키가 입력되었을 때
            switch (flag) {
            case 1:
                break; // 1인 플레이
            case 2:
                break; // 2인 플레이
            case 3:
                Sleep(200);
                setLang();
                break; // 언어 선택
            case 4: // 게임 종료
                exit(0);

            }
        }
    }
}
#include "define.h"

void selSerCli();

void selMul() { // 멀티 선택 화면 출력 
    int flag = 1; //사용자가 어떤 메뉴를 선택했는지 확인하는 변수
    int x = 45, y = 19;
    gotoxy(0, 15);
    printf("\t\t\t\t\t _________________________________________________________________________ \n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|_________________________________________________________________________|\n");
    gotoxy(x, y);
    printf(lang[9]);
    gotoxy(x + 27, y);
    printf(lang[10]);
    gotoxy(x + 57, y);
    printf(lang[11]);
    gotoxy(x, y - 2);
    printf("  ▼");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { // 방향키 왼쪽이 입력되었을 때
            if (flag > 1) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 29, y - 2);
                printf("  ▼");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // 방향키 오른쪽이 입력되었을 때
            if (flag < 3) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 29, y - 2);
                printf("  ▼");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // 스페이스키가 입력되었을 때
            //switch 문을 사용해 메뉴가 선택되면 그에 맞는 함수를 호출
            switch (flag) {
            case 1: // 로컬 플레이
                Sleep(200);
                localStart();
                break;
            case 2: // 네트워크 플레이
                Sleep(200);
                selSerCli();
                break;
            case 3: // 메인 메뉴
                Sleep(200);
                printMenu();
                break;
            }
        }
    }
}
void selSerCli() {
    int flag = 1; //사용자가 어떤 메뉴를 선택했는지 확인하는 변수
    int x = 45, y = 19;
    gotoxy(0, 15);
    printf("\t\t\t\t\t _________________________________________________________________________ \n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|                                                                         |\n");
    printf("\t\t\t\t\t|_________________________________________________________________________|\n");
    gotoxy(x, y);
    printf(lang[12]);
    gotoxy(x + 27, y);
    printf(lang[13]);
    gotoxy(x + 57, y);
    printf(lang[14]);
    gotoxy(x, y - 2);
    printf("  ▼");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { // 방향키 왼쪽이 입력되었을 때
            if (flag > 1) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 29, y - 2);
                printf("  ▼");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // 방향키 오른쪽이 입력되었을 때
            if (flag < 3) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 29, y - 2);
                printf("  ▼");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // 스페이스키가 입력되었을 때
            switch (flag) {
            case 1: // 서버
                Sleep(100);
                netStartSer();
                break;
            case 2: // 클라이언트
                Sleep(100);
                netStartCli();
                break;
            case 3: // 메인 메뉴
                Sleep(100);
                printMenu();
                break;
            }
        }
    }
}
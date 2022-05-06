#include <stdio.h>
#include <Windows.h>

void printMenu();
void gotoxy(int, int);
void hideCursor();

extern char ch[30][20];
extern void lang();

void main() {
    korean();
    printMenu();
}
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printMenu() {
    int flag = 1;
    int i = 0;
    int x = 74, y = 40;

    hideCursor();
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
        if (GetAsyncKeyState(VK_UP)) { // 위
            if (y > 40) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y -= 2);
                printf("▶");
                Sleep(100);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_DOWN)) { // 아래
            if (y <= 44) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y += 2);
                printf("▶");
                Sleep(100);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) { // 스페이스
            switch (flag) {
                case 1:
                    break;//1인 플레이
                case 2:
                    break;//2인 플레이
                case 3:
                    Sleep(100);
                    lang();
                    break;//언어 선택
                case 4: //게임 종료
                    exit(0);

            }
        }
    }
}
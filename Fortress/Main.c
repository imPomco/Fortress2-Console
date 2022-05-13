#include "define.h"

void gotoxy(int, int);
void hideCursor();


void main() {
    //PlaySound(TEXT("sounds\\main.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
    hideCursor();
    kor(); // 언어의 기본값을 한국어로 설정
    printMenu(); // 메뉴 출력
}
void gotoxy(int x, int y) { // 콘솔 좌표 이동
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void hideCursor() { // 콘솔 창에 뜨는 커서를 제거하는 함수
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
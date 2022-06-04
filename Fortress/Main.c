#include "define.h"

void gotoxy(int, int);
void hideCursor();
/* 구현 또는 추가가 필요한 목록
   서버 생성 및 연결시 인터페이스 제작
   언어 번역
   게임 중 강제로 메인 메뉴로 나가는 버튼 추가 (네트워크 플레이 시에는 제외)
   맵 제작 / 선택
*/


/* 조작법
   방향키 좌우 : 메뉴 선택 및 탱크 좌우 조작
   방향키 상하 : 메뉴 선택 및 탱크 포탄 발사 각도 조작
   스페이스바 : 선택한 메뉴 결정 및 포탄 파워 조작 (스페이스를 한번 누르면 파워 게이지 상승, 원하는 파워 게이지에서 스페이스바 한번 더 입력)
*/

void main() {
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
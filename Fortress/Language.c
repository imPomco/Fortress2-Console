#include "define.h"

void kor();
void eng();

char lang[30][20] = { 0, };

void setLang() { // 언어 설정 화면 출력 
    int flag = 1; //사용자가 무슨 언어를 선택했는지 확인하는 변수
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
    printf("한국어");
    gotoxy(x + 30, y);
    printf("English");
    gotoxy(x + 60, y);
    printf("中國語");
    gotoxy(x, y - 2);
    printf("  ▼");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { // 방향키 왼쪽이 입력되었을 때
            if (x > 45) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 30, y - 2);
                printf("  ▼");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // 방향키 오른쪽이 입력되었을 때
            if (x <= 105) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 30, y - 2);
                printf("  ▼");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_RETURN)) { // 스페이스키가 입력되었을 때
            /*
            switch 문을 사용해 해당언어가 선택되면 그에 맞는 언어 함수를 호출하고,
            printMenu 함수를 호출해 다시 메인 메뉴로 돌아감 
            */
            switch (flag) {
                case 1: // 한국어
                    kor();
                    Sleep(100);
                    break;
                case 2: // 영어
                    eng();
                    Sleep(100);
                    break;
                case 3: // 중국어
                    break;
            }
            printMenu();
        }
    }
}
/*
프로젝트 폴더내부에 존재하는 언어 파일(ex. language\korean.txt) 내부에 있는 문자열을 한 줄씩 읽어와
ch 2차원 배열에 문자열 형태로 저장.
*/
void kor() {
    int i = 0;

    FILE* file = fopen("language\\korean.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            fgets(lang[i], 20, file);
            for (int j = 1; j < 20; j++)
                if (lang[i][j - 1] == '\n')
                    lang[i][j - 1] = '\0';
            i++;
        }
        fclose(file);
    }
}
void eng() {
    int i = 0;

    FILE* file = fopen("language\\english.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            fgets(lang[i], 20, file);
            for (int j = 1; j < 20; j++)
                if (lang[i][j - 1] == '\n')
                    lang[i][j - 1] = '\0';
            i++;
        }
        fclose(file);
    }
}
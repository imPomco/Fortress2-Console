#include <stdio.h>
#include <Windows.h>

void korean();
void english();

extern void printMenu();
extern void gotoxy(int, int);

char ch[30][20] = { 0, };

void lang() {
    int flag = 1;
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
    printf("ÇÑ±¹¾î");
    gotoxy(x + 30, y);
    printf("English");
    gotoxy(x + 60, y);
    printf("ñéÏÐåÞ");
    gotoxy(x, y - 2);
    printf("  ¡å");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { //ÁÂ
            if (x > 45) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 30, y - 2);
                printf("  ¡å");
                Sleep(200);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_RIGHT)) { //¿ì
            if (x <= 105) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 30, y - 2);
                printf("  ¡å");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) { // ½ºÆäÀÌ½º
            switch (flag) {
                case 1: // ÇÑ±¹¾î
                    korean();
                    printMenu();
                    break;
                case 2: // ¿µ¾î
                    english();
                    printMenu();
                    break;
                case 3: // Áß±¹¾î
                    break;
            }
        }
    }
}
void korean() {
    int i = 0;

    FILE* file = fopen("korean.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            fgets(ch[i], 30, file);
            i++;
        }
        fclose(file);
    }
    return;
}
void english() {
    int i = 0;

    FILE* file = fopen("english.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            fgets(ch[i], 30, file);
            i++;
        }
        fclose(file);
    }
    return;
}
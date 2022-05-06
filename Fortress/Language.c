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
    printf("�ѱ���");
    gotoxy(x + 30, y);
    printf("English");
    gotoxy(x + 60, y);
    printf("������");
    gotoxy(x, y - 2);
    printf("  ��");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { //��
            if (x > 45) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 30, y - 2);
                printf("  ��");
                Sleep(200);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_RIGHT)) { //��
            if (x <= 105) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 30, y - 2);
                printf("  ��");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) { // �����̽�
            switch (flag) {
                case 1: // �ѱ���
                    korean();
                    printMenu();
                    break;
                case 2: // ����
                    english();
                    printMenu();
                    break;
                case 3: // �߱���
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
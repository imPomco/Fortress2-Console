#include "define.h"

void kor();
void eng();

char lang[30][20] = { 0, };

void setLang() { // ��� ���� ȭ�� ��� 
    int flag = 1; //����ڰ� ���� �� �����ߴ��� Ȯ���ϴ� ����
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
        if (GetAsyncKeyState(VK_LEFT)) { // ����Ű ������ �ԷµǾ��� ��
            if (x > 45) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 30, y - 2);
                printf("  ��");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // ����Ű �������� �ԷµǾ��� ��
            if (x <= 105) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 30, y - 2);
                printf("  ��");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_RETURN)) { // �����̽�Ű�� �ԷµǾ��� ��
            /*
            switch ���� ����� �ش�� ���õǸ� �׿� �´� ��� �Լ��� ȣ���ϰ�,
            printMenu �Լ��� ȣ���� �ٽ� ���� �޴��� ���ư� 
            */
            switch (flag) {
                case 1: // �ѱ���
                    kor();
                    Sleep(100);
                    break;
                case 2: // ����
                    eng();
                    Sleep(100);
                    break;
                case 3: // �߱���
                    break;
            }
            printMenu();
        }
    }
}
/*
������Ʈ �������ο� �����ϴ� ��� ����(ex. language\korean.txt) ���ο� �ִ� ���ڿ��� �� �پ� �о��
ch 2���� �迭�� ���ڿ� ���·� ����.
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
#include "define.h"

void selSerCli();

void selMul() { // ��Ƽ ���� ȭ�� ��� 
    int flag = 1; //����ڰ� � �޴��� �����ߴ��� Ȯ���ϴ� ����
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
    printf("  ��");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { // ����Ű ������ �ԷµǾ��� ��
            if (flag > 1) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 29, y - 2);
                printf("  ��");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // ����Ű �������� �ԷµǾ��� ��
            if (flag < 3) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 29, y - 2);
                printf("  ��");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // �����̽�Ű�� �ԷµǾ��� ��
            //switch ���� ����� �޴��� ���õǸ� �׿� �´� �Լ��� ȣ��
            switch (flag) {
            case 1: // ���� �÷���
                Sleep(200);
                localStart();
                break;
            case 2: // ��Ʈ��ũ �÷���
                Sleep(200);
                selSerCli();
                break;
            case 3: // ���� �޴�
                Sleep(200);
                printMenu();
                break;
            }
        }
    }
}
void selSerCli() {
    int flag = 1; //����ڰ� � �޴��� �����ߴ��� Ȯ���ϴ� ����
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
    printf("  ��");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT)) { // ����Ű ������ �ԷµǾ��� ��
            if (flag > 1) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x -= 29, y - 2);
                printf("  ��");
                Sleep(200);
                flag--;
            }
        }
        if (GetAsyncKeyState(VK_RIGHT)) { // ����Ű �������� �ԷµǾ��� ��
            if (flag < 3) {
                gotoxy(x, y - 2);
                printf("    ");
                gotoxy(x += 29, y - 2);
                printf("  ��");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // �����̽�Ű�� �ԷµǾ��� ��
            switch (flag) {
            case 1: // ����
                Sleep(100);
                netStartSer();
                break;
            case 2: // Ŭ���̾�Ʈ
                Sleep(100);
                netStartCli();
                break;
            case 3: // ���� �޴�
                Sleep(100);
                printMenu();
                break;
            }
        }
    }
}
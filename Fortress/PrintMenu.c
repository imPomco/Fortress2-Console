#include <Windows.h>
#include "define.h"

void printMenu() { // ���� �޴� ���
    int flag = 1; //����ڰ� � �޴��� �����ߴ��� Ȯ���ϴ� ����
    int i = 0;
    int x = 74, y = 40;

    system("mode con cols=160 lines=50"); // �ܼ� â ũ�� ���� cols : ����, lines : ����

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
    printf("��  %s", ch[i++]);
    gotoxy(x, y + 2);
    printf("%s", ch[i++]);
    gotoxy(x, y + 4);
    printf("%s", ch[i++]);
    gotoxy(x, y + 6);
    printf("%s", ch[i++]);
    gotoxy(x, y);
    while (1) {
        if (GetAsyncKeyState(VK_UP)) { // ����Ű ���� �ԷµǾ��� ��
            if (y > 40) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y -= 2);
                printf("��");
                Sleep(100);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_DOWN)) { // ����Ű �Ʒ��� �ԷµǾ��� ��
            if (y <= 44) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y += 2);
                printf("��");
                Sleep(100);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE)) { // �����̽�Ű�� �ԷµǾ��� ��
            switch (flag) {
            case 1:
                break; // 1�� �÷���
            case 2:
                break; // 2�� �÷���
            case 3:
                Sleep(200);
                setLang();
                break; // ��� ����
            case 4: // ���� ����
                exit(0);

            }
        }
    }
}
#include "define.h"

void printMenu() { // ���� �޴� ���
    lang_lines = 0;
    int flag = 1; //����ڰ� � �޴��� �����ߴ��� Ȯ���ϴ� ����
    int x = 74, y = 40;

    system("mode con cols=160 lines=50 | title=Fortress"); // �ܼ� â ũ�� ���� cols : ����, lines : ����

    playMusic(1);
    gotoxy(0, 2);
    printf("\t\t\t\t\t########  #######  ########  ######## ########  ########  ######   ###### \n");
    printf("\t\t\t\t\t##       ##     ## ##     ##    ##    ##     ## ##       ##    ## ##    ##\n");
    printf("\t\t\t\t\t##       ##     ## ##     ##    ##    ##     ## ##       ##       ##  \n");
    printf("\t\t\t\t\t######   ##     ## ########     ##    ########  ######    ######   ######   \n");
    printf("\t\t\t\t\t##       ##     ## ##   ##      ##    ##   ##   ##             ##       ##\n");
    printf("\t\t\t\t\t##       ##     ## ##    ##     ##    ##    ##  ##       ##    ## ##    ##\n");
    printf("\t\t\t\t\t##        #######  ##     ##    ##    ##     ## ########  ######   ###### \n");

    gotoxy(x, 36);
    printf("%s\n", lang[lang_lines++]);
    gotoxy(x - 4, y);
    printf("��  %s", lang[lang_lines++]);
    gotoxy(x, y + 2);
    printf("%s", lang[lang_lines++]);
    gotoxy(x, y + 4);
    printf("%s", lang[lang_lines++]);
    gotoxy(x, y + 6);
    printf("%s", lang[lang_lines++]);
    gotoxy(x, y);
    while (1) {
        if (GetAsyncKeyState(VK_UP)) { // ����Ű ���� �ԷµǾ��� ��
            if (y > 40) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y -= 2);
                printf("��");
                Sleep(200);
                flag--;
            }

        }
        if (GetAsyncKeyState(VK_DOWN)) { // ����Ű �Ʒ��� �ԷµǾ��� ��
            if (y <= 44) {
                gotoxy(x - 4, y);
                printf("  ");
                gotoxy(x - 4, y += 2);
                printf("��");
                Sleep(200);
                flag++;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // �����̽�Ű�� �ԷµǾ��� ��
            switch (flag) {
            case 1: // 1�� �÷���
                singleStart();
                break; 
            case 2: // 2�� �÷���
                Sleep(200);
                selMul();
                break; 
            case 3: // ��� ����
                Sleep(200);
                setLang();
                break;
            case 4: // ���� ����
                exit(0);

            }
        }
    }
}
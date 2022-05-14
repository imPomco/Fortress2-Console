#include "define.h"

char map[40][160] = { 0 }; // 40 : 맵 y 좌표, 160 : 맵 x 좌표

void printMap() {
    for (int i = 39; i >= 0; i--) {
        for (int j = 0; j < 160; j++) {
            gotoxy(j, i);
            switch (map[i][j])
            {
                case '0':
                    printf(" ");
                    break;
                case '1':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                    printf("*");
                    break;
                case '2':
                    printf("/");
                    break;
            }
        }
    }
}
void readMap() {
    int i = 0;
    char ch = NULL;

    FILE* fp = fopen("map\\map.bin", "r");
    if (fp != NULL) {
        while (!feof(fp)) {
            fgets(map[i], 162, fp);
            i++;
        }
        fclose(fp);
    }
}
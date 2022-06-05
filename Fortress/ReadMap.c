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
            }
        }
    }
}
void readMap(int mapRand) {
    FILE* fp;
    int i = 0;
    char ch = NULL;
    switch (mapRand) {
        case 1:
            fp = fopen("map\\map1.map", "r");
            playMusic(2);
            if (fp != NULL) {
                while (!feof(fp)) {
                    fgets(map[i], 162, fp);
                    i++;
                }
                fclose(fp);
                break;
        case 2:
            fp = fopen("map\\map2.map", "r");
            playMusic(3);
            if (fp != NULL) {
                while (!feof(fp)) {
                    fgets(map[i], 162, fp);
                    i++;
                }
                fclose(fp);
                break;
            }
        case 3:
            fp = fopen("map\\map3.map", "r");
            playMusic(4);
            if (fp != NULL) {
                while (!feof(fp)) {
                    fgets(map[i], 162, fp);
                    i++;
                }
                fclose(fp);
                break;
            }
        }
    }
}
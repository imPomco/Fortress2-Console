#include "define.h"

void playMusic(int flag) { // 음악 재생 함수

	switch (flag) {
		case 1:
			mciSendString(L"play sounds\\main_bgm.mp3 repeat", NULL, 0, 0);
			break;
		case 2:
			mciSendString(L"play sounds\\map1_bgm.mp3 repeat", NULL, 0, 0);
			break;
		case 3:
			mciSendString(L"play sounds\\map2_bgm.mp3 repeat", NULL, 0, 0);
			break;
		case 4:
			mciSendString(L"play sounds\\map3_bgm.mp3 repeat", NULL, 0, 0);
			break;
		case 5:
			mciSendString(L"play sounds\\net_wait.mp3 repeat", NULL, 0, 0);
			break;
		case 6:
			mciSendString(L"play sounds\\victory.mp3 repeat", NULL, 0, 0);
			break;
	}
}
void stopMusic(int flag) { // 음악 중단 함수

	switch (flag) {
		case 1:
			mciSendString(L"close sounds\\main_bgm.mp3", NULL, 0, 0);
			break;
		case 2:
			mciSendString(L"close sounds\\map1_bgm.mp3", NULL, 0, 0);
			break;
		case 3:
			mciSendString(L"close sounds\\map2_bgm.mp3", NULL, 0, 0);
			break;
		case 4:
			mciSendString(L"close sounds\\map3_bgm.mp3", NULL, 0, 0);
			break;
		case 5:
			mciSendString(L"close sounds\\net_wait.mp3", NULL, 0, 0);
			break;
		case 6:
			mciSendString(L"close sounds\\victory.mp3", NULL, 0, 0);
			break;
	}
}
void playFX(int flag) { // 효과음 재생 함수 (효과음 길이가 길지 않아 중단 함수 제작 X)
	switch (flag) {
		case 1:
			mciSendString(L"play sounds\\count_down.mp3", NULL, 0, 0); // 카운트 다운 효과음
			break;
		case 2:
			mciSendString(L"play sounds\\count_down_2.mp3", NULL, 0, 0); // 카운트 다운 5초 미만으로 남았을 때 효과음
			break;
		case 3:
			mciSendString(L"play sounds\\tank_move.mp3", NULL, 0, 0); // 탱크 이동 효과음
			break;
		case 4:
			mciSendString(L"play sounds\\fire.mp3", NULL, 0, 0); // 포탄 발사 효과음
			break;
		case 5:
			mciSendString(L"play sounds\\bomb_1.mp3", NULL, 0, 0); // 포탄 착탄 효과음
			break;
		case 6:
			mciSendString(L"play sounds\\bomb_2.mp3", NULL, 0, 0); // 
			break;
		case 7:
			mciSendString(L"play sounds\\bomb_3.mp3", NULL, 0, 0);
			break;
	}
}
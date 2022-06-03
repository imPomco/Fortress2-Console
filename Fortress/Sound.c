#include "define.h"

void playMusic(int flag) { // ���� ��� �Լ�

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
void stopMusic(int flag) { // ���� �ߴ� �Լ�

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
void playFX(int flag) { // ȿ���� ��� �Լ� (ȿ���� ���̰� ���� �ʾ� �ߴ� �Լ� ���� X)
	switch (flag) {
		case 1:
			mciSendString(L"play sounds\\count_down.mp3", NULL, 0, 0); // ī��Ʈ �ٿ� ȿ����
			break;
		case 2:
			mciSendString(L"play sounds\\count_down_2.mp3", NULL, 0, 0); // ī��Ʈ �ٿ� 5�� �̸����� ������ �� ȿ����
			break;
		case 3:
			mciSendString(L"play sounds\\tank_move.mp3", NULL, 0, 0); // ��ũ �̵� ȿ����
			break;
		case 4:
			mciSendString(L"play sounds\\fire.mp3", NULL, 0, 0); // ��ź �߻� ȿ����
			break;
		case 5:
			mciSendString(L"play sounds\\bomb_1.mp3", NULL, 0, 0); // ��ź ��ź ȿ����
			break;
		case 6:
			mciSendString(L"play sounds\\bomb_2.mp3", NULL, 0, 0); // 
			break;
		case 7:
			mciSendString(L"play sounds\\bomb_3.mp3", NULL, 0, 0);
			break;
	}
}
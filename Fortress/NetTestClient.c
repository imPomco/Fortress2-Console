#include "define.h"


void client() {
	static int angle = 45;
	int power = 0;
	int move = 100;
	SOCKET s;
	WSADATA wsaData;
	SOCKADDR_IN sin;
	char addrInput[40];

	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
		printf("WSAStartup ����, �����ڵ� : %d\n", WSAGetLastError());
		return;
	}

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		printf("���� ���� ����, �����ڵ� : %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	printf("������ IP �ּҸ� �Է��� �ּ��� : ");
	scanf("%s", addrInput);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5000);
	sin.sin_addr.S_un.S_addr = inet_addr(addrInput);

	if (connect(s, (SOCKADDR*)&sin, sizeof(sin)) != 0) {
		printf("���� ����\n");
		closesocket(s); WSACleanup();
		return;
	}
	int sAddr = sizeof(sin);
	printf("������ ����Ǿ����ϴ�.\n");

	while (1) {
		Sleep(5);
		recvfrom(s, &power, sizeof(power), 0, &sin, &sAddr);
		recvfrom(s, &move, sizeof(move), 0, &sin, &sAddr);
		recvfrom(s, &angle, sizeof(angle), 0, &sin, &sAddr);
		//sendto(s, &power, sizeof(power), 0, &sin, &sAddr);
		//printf("[�������� ���� ������]\n%d\n", power);
		printf("[�������� ���� ������]\n%d\n", move);
		//printf("[�������� ���� ������]\n%d\n", angle);
	}
}
void serTurnCli(SOCKET c, SOCKADDR_IN server_addr, int c_size) {
	SOCKET ss = c;
	SOCKADDR_IN ser_addr = server_addr;
	int ser_size = c_size;
}
void cliTurnCli(SOCKET c, SOCKADDR_IN ser_addr, int c_size) {

}
void netStopCli() {
	//if (closesocket(s) != 0) {
	//	printf("���� ���� ����, ���� �ڵ� : %d\n", WSAGetLastError());
	//	WSACleanup();
	//	return;
	//}

	//if (WSACleanup() != 0) {
	//	printf("WSACleanup ����, �����ڵ� : %d\n", WSAGetLastError());
	//	return;
	//}
}
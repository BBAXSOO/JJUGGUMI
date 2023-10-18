#include <stdio.h>
#include <Windows.h>  // Windows API 헤더 파일
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 맵과 플레이어 정보를 저장하는 변수들 선언
char map[100][300];
int playerx[5], playery[5];
int playerAlive[5];
int tick = 0;
int move_tick = 0;
int cameraOn = 0;  // 카메라 상태 (0: 꺼짐, 1: 켜짐)
char flowerMessage[] = "무궁화꽃이 피었습니다";
int messageIndex = 0;
int messageSpeed = 300;  // 메시지 출력 간격 (3초에 10번 이동)

// 커서를 특정 위치로 이동시키는 함수
void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 맵을 그리는 함수
void draw(void) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            gotoxy(i, j);
            printf("%c", map[i][j]);
        }
    }
}

// 맵을 초기화하는 함수
void initializeMap(void) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (i == 0 || i == 10 || j == 0 || j == 44) {
                map[i][j] = '#';
            } else if (i >= 4 && i <= 6 && j <= 1) {
                map[i][j] = '@';
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

// 플레이어 위치를 업데이트하는 함수
void updatePlayerPosition(int player) {
    map[playerx[player]][playery[player]] = '0' + player;
}

// 플레이어를 이동시키는 함수
void movePlayer(int player, int dx, int dy) {
    if (playerAlive[player] == 0) return;
    int nx = playerx[player] + dx;
    int ny = playery[player] + dy;

    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 && map[nx][ny] != '1' && map[nx][ny] != '2'
        && map[nx][ny] != '3' && map[nx][ny] != '4') {
        map[playerx[player]][playery[player]] = ' ';
        playerx[player] = nx;
        playery[player] = ny;
        updatePlayerPosition(player);
    }
}

// 무작위로 플레이어를 이동시키는 함수
void moveRandomPlayers(void) {
    for (int i = 1; i <= 4; i++) {
        if (playerAlive[i] == 0) continue;
        int randomMove = rand() % 10 + 1;
        int dx = 0, dy = 0;

        if (randomMove <= 7) {
            dy = -1;  // 왼쪽으로 이동
        } else if (randomMove == 8) {
            dx = -1;  // 위로 이동
        } else if (randomMove == 9) {
            dx = 1;   // 아래로 이동
        }

        movePlayer(i, dx, dy);
    }
}

// 꽃 메시지를 출력하는 함수
void printFlowerMessage(int x, int y) {
    for (int i = 0; i < strlen(flowerMessage); i++) {
        gotoxy(x, y);
        printf("%c", flowerMessage[i]);
        Sleep(messageSpeed);
        y++;
    }
}

// 플레이어 충돌을 확인하는 함수
int checkPlayerCollisions(void) {
    for (int i = 1; i <= 3; i++) {
        if (playerAlive[i] && playerx[i] == playerx[0] && (playery[i] == playery[0] - 1 || playery[i] == playery[0] || playery[i] == playery[0] + 1)) {
            playerAlive[i] = 0;
            draw();
        }
    }
}

// 메인 함수
int main(void) {
    srand(time(NULL));  // 시드 설정

    for (int i = 0; i < 5; i++) {
        playerx[i] = i;  // 플레이어 x 위치 초기화
        playery[i] = 42;  // 플레이어 y 위치 초기화
        playerAlive[i] = 1;  // 플레이어 생존 여부 설정
    }

    // 게임 루프
    while (1) {
        initializeMap();  // 맵 초기화
        for (int i = 0; i < 5; i++) {
            if (playerAlive[i]) {
                updatePlayerPosition(i);
            }
        }

        draw();  // 맵 그리기

        movePlayer(0, 0, -1); // 사용자가 위로 이동할 수 있도록 함
        draw();  // 맵 그리기
        move_tick += 1000;  // 이동 시간 증가

        checkPlayerCollisions();  // 플레이어 충돌 확인

        if (move_tick % 20000 == 0) {
            int playersLeft = 0;
            for (int i = 1; i <= 4; i++) {
                if (playerAlive[i]) {
                    playersLeft++;
                }
            }

            if (playersLeft > 0) {
                if (cameraOn == 0) {
                    cameraOn = 1;
                    // 카메라가 켜진 상태에서 움직인 플레이어는 탈락하지 않음
                    moveRandomPlayers();
                    draw();
                }
            } else {
                printFlowerMessage(4, 4);
                gotoxy(5, 0);
                printf("4 player20, 2 dead!");
                gotoxy(6, 0);
                printf("5 player5, 5 dead!");
                break;
            }
        }

        Sleep(300);  // 잠시 대기
        tick += 1000;  // 시간 업데이트
    }

    return 0;
}

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int row, int col);
void draw(void);

int tick = 0;
char map[10][20], front[10][20];
int numPlayers = 5;  // 총 플레이어 수
int playerX[5], playerY[5];  // 플레이어 위치 배열
int playerDir[5] = { 3, 2, 0, 1, 3 };  // 플레이어 이동 방향 배열

void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        pos
    );
}

void draw(void) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(i, j);
                printf("%c", front[i][j]);
            }
        }
    }
}

int main(void) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 19)
                map[i][j] = '#';
            else
                map[i][j] = ' ';

        }
    }

    // 초기 플레이어 위치 설정
    for (int i = 0; i < numPlayers; i++) {
        playerX[i] = 1;
        playerY[i] = 1 + i;
        map[playerX[i]][playerY[i]] = '*';
    }

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    while (1) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 'w':
                playerDir[0] = 0;
                break;
            case 's':
                playerDir[0] = 1;
                break;
            case 'a':
                playerDir[0] = 2;
                break;
            case 'd':
                playerDir[0] = 3;
                break;
            case 'q':
                return 0;
            }
        }

        if (tick % 100 == 0) {
            for (int i = 0; i < numPlayers; i++) {
                int nx = playerX[i] + dx[playerDir[i]];
                int ny = playerY[i] + dy[playerDir[i]];

                if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
                    map[playerX[i]][playerY[i]] = ' ';
                    playerX[i] = nx;
                    playerY[i] = ny;
                    map[playerX[i]][playerY[i]] = '*';
                }
            }
        }
        draw();
        Sleep(10);
        tick += 10;
    }
    return 0;
}

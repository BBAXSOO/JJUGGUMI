#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h> // srand, rand 함수를 사용하기 위해 추가
#include <time.h>   // 시간을 기반으로 무작위 값을 생성하기 위해 추가


void gotoxy(int row, int col);
void draw(void);

int tick = 0;
char map[100][300], front[100][300];

void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        pos
    );
}

void draw(void) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 60; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(i, j);
                printf("%c", front[i][j]);
            }
        }
    }
}

int main(void) {
    srand(time(NULL)); // 난수 발생을 위한 시드 설정

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 60; j++) {
            if (i == 0 || i == 19 || j == 0 || j == 59)
                map[i][j] = '#';
            else
                map[i][j] = ' ';

        }
    }
    map[1][1] = '*';

    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };
    int x = 1, y = 1;
    int dir = 3;

    int playerx[4];
    int playery[4];

    // 초기 플레이어 위치 설정
    for (int i = 0; i < 4; i++) {
        playerx[i] = rand() % 18 + 1;
        playery[i] = rand() % 58 + 1;
        map[playerx[i]][playery[i]] = '1' + i; // 무작위 플레이어를 다른 문자로 표시
    }

    while (1) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 'w':
                dir = 0;
                break;
            case 's':
                dir = 1;
                break;
            case 'a':
                dir = 2;
                break;
            case 'd':
                dir = 3;
                break;
            case 'q':
                return 0;
            }
        }

        if (tick % 80 == 0) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 1 && nx < 19 && ny >= 1 && ny < 59) { // 수정된 조건
                map[x][y] = ' ';
                x = nx; y = ny;
                map[x][y] = '*';
            }

            // 무작위 플레이어 이동
            for (int i = 0; i < 4; i++) {
                int randomDirection = rand() % 4;
                nx = playerx[i] + dx[randomDirection];
                ny = playery[i] + dy[randomDirection];

                if (nx >= 1 && nx < 19 && ny >= 1 && ny < 59) { // 수정된 조건
                    map[playerx[i]][playery[i]] = ' ';
                    playerx[i] = nx;
                    playery[i] = ny;
                    map[playerx[i]][playery[i]] = '1' + i; // 무작위 플레이어를 다른 문자로 표시
                }
            }
        }
        draw();
        Sleep(10);
        tick += 10;
    }
    return 0;
}

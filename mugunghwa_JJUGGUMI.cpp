#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define Row_MAX     40
#define COL_MAX     80

char front_buf;
void gotoxy(int row, int col);
void draw(void);

int tick = 0;
char map[100][300], front[100][300];

void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw(void) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(i, j);
                printf("%c", front[i][j]);
            }
        }
    }
}


int main(void) {
    srand(time(NULL));

    //벽
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (i == 0 || i == 10 || j == 0 || j == 44)
            {
                map[i][j] = '#';
            }
            else
            {
                map[i][j] = ' ';
            }

        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            if (i >= 4 && i <= 6 && j <= 1)
            {
                map[i][j] = '#';

            }

        }
    }



    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };
    int x = 2, y = 42;
    int dir = 3;

    int playerx[4];
    int playery[4];

    //랜덤하게 움직이는 것들의 위치
    for (int i = 0; i < 4; i++) {
        playerx[i] = 3 + i;
        playery[i] = 43;
        map[3][43] = '1';
    }



    //입력 받아서 움직임
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


        //플레이어 이동
        if (tick % 80 == 0) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                map[x][y] = ' ';
                x = nx; y = ny;
                map[x][y] = '0';
            }


            for (int i = 0; i < 4; i++) {
                int randommove = rand() % 10 + 1;

                if (randommove <= 7)
                {
                    int nx = playerx[i];
                    int ny = playery[i] - 1;

                    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                        map[playerx[i]][playery[i]] = ' ';
                        playerx[i] = nx;
                        playery[i] = ny;
                        map[playerx[i]][playery[i]] = '1' + i;
                    }
                }


                if (randommove <= 1)
                {
                    int nx = playerx[i] - 1;
                    int ny = playery[i];

                    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                        map[playerx[i]][playery[i]] = ' ';
                        playerx[i] = nx;
                        playery[i] = ny;
                        map[playerx[i]][playery[i]] = '1' + i;
                    }
                }


                if (randommove <= 1)
                {
                    int nx = playerx[i];
                    int ny = playery[i] - 1;

                    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                        map[playerx[i]][playery[i]] = ' ';
                        playerx[i] = nx;
                        playery[i] = ny;
                        map[playerx[i]][playery[i]] = '1' + i;
                    }
                }

                if (randommove <= 1)
                {
                    int nx = playerx[i];
                    int ny = playery[i];

                    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                        map[playerx[i]][playery[i]] = ' ';
                        playerx[i] = nx;
                        playery[i] = ny;
                        map[playerx[i]][playery[i]] = '1' + i;
                    }
                }

            }
        }
        draw();
        Sleep(100);
        tick += 100;
    }





    return 0;
}

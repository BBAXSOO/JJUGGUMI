#include <stdio.h>
#include <stdlib.h>

#include "jjuggumi.h"
#include "keyin.h"
#include "canvas.h"

#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS
#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void move_manual(key_t key);
void move_random(int i, int dir);
void move_tail(int i, int nx, int ny);

int is_player_at_goal[PLAYER_MAX]; // 플레이어가 목표에 도달했는지 여부
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

void initializeMap(void) {
    map_init(9, 30);
    int x, y;
    for (int i = 0; i < n_player; i++) {
        // 같은 자리가 나오면 다시 생성
        x = 2 + i;
        y = N_COL - 2;
        px[i] = x;
        py[i] = y;
        period[i] = randint(100, 500);

        back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
    }

    tick = 0;
}

void move_manual(key_t key) {
    // 각 방향으로 움직일 때 x, y값 delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // 움직일 방향(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // 움직여서 놓일 자리
    int nx, ny;
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (!placable(nx, ny)) {
        return;
    }

    move_tail(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤


void move_random(int player, int dir) {
    int p = player;  // 이름이 길어서...
    int nx, ny;  // 움직여서 다음에 놓일 자리

    // 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)	
    int move_x;
    int move_y;
    do {
        move_x = randint(0, 9);
        move_y = randint(0, 9);

        if (move_x == 0) {
            move_x = -1;
        }
        else if (move_x == 1) {
            move_x = 1;
        }
        else {
            move_x = 0;
        }

        if (move_y < 7) {
            move_y = -1;
        }
        else {
            move_y = 0;
        }

        nx = px[p] + move_x;
        ny = py[p] + move_y;
    } while (!placable(nx, ny));

    move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void move_tail(int player, int nx, int ny) {
    int p = player;  // 이름이 길어서...
    back_buf[nx][ny] = back_buf[px[p]][py[p]];
    back_buf[px[p]][py[p]] = ' ';
    px[p] = nx;
    py[p] = ny;
}

int is_arrived(int pos) {
    if (py[pos] == 1 && px[pos] == 2) {
        return 1;
    }
    else if (py[pos] == 2 && px[pos] == 3) {
        return 1;
    }
    else if (py[pos] == 2 && px[pos] == 4) {
        return 1;
    }
    else if (py[pos] == 2 && px[pos] == 5) {
        return 1;
    }
    else if (py[pos] == 1 && px[pos] == 6) {
        return 1;
    }

    return 0;
}

void printFlowerMessage(int move_tick) {

    //const char* slow_part = "무 궁 화 꽃 이";
    //const char* fast_part = "피 었 습 니 다";

    //// 무궁화꽃이 부분은 점점 느리게 출력
    //int delay = 0;
    //for (int i = 0; slow_part[i] != '\0'; ++i) {
    //    gotoxy(10, 2 * i);
    //    putchar(slow_part[i]);
    //    fflush(stdout);
    //    Sleep(delay);
    //    delay = delay + 50;
    //}

    //// 피었습니다 부분은 점점 빠르게 출력
    //delay = 500;
    //for (int i = 0; fast_part[i] != '\0'; ++i) {
    //    gotoxy(10, 30 + 2 * i);
    //    putchar(fast_part[i]);
    //    fflush(stdout);
    //    Sleep(delay);
    //    delay = delay - 30;
    //}

    //return 0;

    if (move_tick == 100) {
        gotoxy(10, 0);
        printf("무");
    }
    else if (move_tick == 300) {
        gotoxy(10, 5);
        printf("궁");
    }
    else if (move_tick == 600) {
        gotoxy(10, 10);
        printf("화");
    }
    else if (move_tick == 1000) {
        gotoxy(10, 15);
        printf("꽃");
    }
    else if (move_tick == 1500) {
        gotoxy(10, 20);
        printf("이");
    }
    else if (move_tick == 2100) {
        gotoxy(10, 25);
        printf("피");
    }
    else if (move_tick == 2600) {
        gotoxy(10, 30);
        printf("었");
    }
    else if (move_tick == 3000) {
        gotoxy(10, 35);
        printf("습");
    }
    else if (move_tick == 3300) {
        gotoxy(10, 40);
        printf("니");
    }
    else if (move_tick == 3500) {
        gotoxy(10, 45);
        printf("다");
    }
}



int* pos_change(int bef_px[], int bef_py[]) {
    int* res = (int*)malloc(sizeof(int) * PLAYER_MAX);

    for (int i = 0; i < PLAYER_MAX; i++) res[i] = 0;

    int is_back = 0;
    for (int i = 0; i < PLAYER_MAX; i++) {
        if (px[i] != bef_px[i]) { // 플레이어들 뒤에 있는지 없는지 검사
            for (int j = 0; j < PLAYER_MAX; j++) {
                if (i == j) {
                    continue;
                }
                else {
                    if (px[i] == px[j] && py[j] == py[i]) {
                        is_back = 1;
                        break;
                    }
                }
            }
            if (is_back == 0) {
                res[i] = 1;
                player[i] = false;
                n_player--;
            }
            is_back = 0;
        }
        if (py[i] != bef_py[i]) { // y가 다른 경우
            res[i] = 1;
            player[i] = false;
            n_player--;
        }
    }

    return res;
}

void mugunghwa(void) {
    initializeMap();

    int move_tick = 0;
    int out = 0;

    int bef_px[PLAYER_MAX];
    int bef_py[PLAYER_MAX];

    int* pc = (int*)malloc(sizeof(int) * PLAYER_MAX);

    for (int i = 0; i < PLAYER_MAX; i++) {
        bef_px[i] = px[i];
        bef_py[i] = py[i];
    }

    system("cls");
    display();
    Sleep(3000);

    while (1) {
        
        if (tick == 13000) {
            system("cls");
            ending(); break;
        }


        gotoxy(3, 1);
        printf("#");
        gotoxy(4, 1);
        printf("#");
        gotoxy(5, 1);
        printf("#");

        // player 0만 손으로 움직임(4방향)
        key_t key = get_key();
        if (key == K_QUIT) {
            game_q();  break;
        }
        else if (key != K_UNDEFINED) {
            move_manual(key);
        }

        // player 1 부터는 랜덤으로 움직임(8방향)
        for (int i = 1; i < n_player; i++) {
            if (tick % period[i] == 0) {
                if (is_arrived(i) == 1) continue;
                move_random(i, -1);
            }
        }
        display();
        Sleep(10);
        move_tick += 10;
        printFlowerMessage(move_tick);

        if (move_tick >= 3500) { // 무궁화~ 메세지 띄움
            gotoxy(3, 1);
            printf("@");
            gotoxy(4, 1);
            printf("@");
            gotoxy(5, 1);
            printf("@");

            for (int i = 0; i < PLAYER_MAX; i++) {
                bef_px[i] = px[i];
                bef_py[i] = py[i];
            }

            for (int i = 0; i < 300; i++) { // 3초 대기 중 10% 확률로 무작위 이동
                for (int i = 1; i < n_player; i++) {
                    if (tick % period[i] == 0) {
                        if (is_arrived(i) == 1) {
                            continue;
                        }
                        int random = randint(0,9);
                        if (random == 0) {
                            move_random(i, -1);
                        }
                        else {
                            continue;
                        }
                    }
                }
                Sleep(10);
            }
            pc = pos_change(bef_px, bef_py);

            for (int i = 0; i < PLAYER_MAX; i++) {
                if (pc[i] == 1) {
                    out = 1;
                    break;
                }
            }

            move_tick = 0;
            for (int i = 0; i < 100; i++) {
                gotoxy(10, i);
                printf(" ");
            }
        }

        if (out == 1) {
            int dead_count = 0;

            for (int i = 0; i < PLAYER_MAX; i++) {
                if (pc[i] == 1) dead_count++;
            }
            printf("\n");

            char* s1 = (char*)malloc(sizeof(char) * 100);
            char* s2 = (char*)malloc(sizeof(char) * 100);

            sprintf(s1, "%d player ", dead_count);
          
            int check = 0;
            for (int i = 0; i < PLAYER_MAX; i++) {
                if (pc[i] == 1) {
                    if (check == 0) {
                        sprintf(s2, "%d", i);
                        check = 1;
                    }
                    else {
                        char* temp = (char*)malloc(sizeof(char) * 50);
                        sprintf(temp, ", %d", i);
                        strcat(s2, temp);
                    }
                }
            }
            strcat(s1, s2);
            strcat(s1, " dead!");

            dialog(s1);
            out = 0;

            free(s1);
            free(s2);
            
        }
        tick += 10;
    }// 제한 시간 넣어서 시간 다지나고 나서 도착한 사람만 우승자를 뽑는 것.

    
    return;
}
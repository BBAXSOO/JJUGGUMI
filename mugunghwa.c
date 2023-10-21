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

int is_player_at_goal[PLAYER_MAX]; // �÷��̾ ��ǥ�� �����ߴ��� ����
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void initializeMap(void) {
    map_init(9, 30);
    int x, y;
    for (int i = 0; i < n_player; i++) {
        // ���� �ڸ��� ������ �ٽ� ����
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
    // �� �������� ������ �� x, y�� delta
    static int dx[4] = { -1, 1, 0, 0 };
    static int dy[4] = { 0, 0, -1, 1 };

    int dir;  // ������ ����(0~3)
    switch (key) {
    case K_UP: dir = DIR_UP; break;
    case K_DOWN: dir = DIR_DOWN; break;
    case K_LEFT: dir = DIR_LEFT; break;
    case K_RIGHT: dir = DIR_RIGHT; break;
    default: return;
    }

    // �������� ���� �ڸ�
    int nx, ny;
    nx = px[0] + dx[dir];
    ny = py[0] + dy[dir];
    if (!placable(nx, ny)) {
        return;
    }

    move_tail(0, nx, ny);
}

// 0 <= dir < 4�� �ƴϸ� ����


void move_random(int player, int dir) {
    int p = player;  // �̸��� ��...
    int nx, ny;  // �������� ������ ���� �ڸ�

    // ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)	
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

// back_buf[][]�� ���
void move_tail(int player, int nx, int ny) {
    int p = player;  // �̸��� ��...
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

    //const char* slow_part = "�� �� ȭ �� ��";
    //const char* fast_part = "�� �� �� �� ��";

    //// ����ȭ���� �κ��� ���� ������ ���
    //int delay = 0;
    //for (int i = 0; slow_part[i] != '\0'; ++i) {
    //    gotoxy(10, 2 * i);
    //    putchar(slow_part[i]);
    //    fflush(stdout);
    //    Sleep(delay);
    //    delay = delay + 50;
    //}

    //// �Ǿ����ϴ� �κ��� ���� ������ ���
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
        printf("��");
    }
    else if (move_tick == 300) {
        gotoxy(10, 5);
        printf("��");
    }
    else if (move_tick == 600) {
        gotoxy(10, 10);
        printf("ȭ");
    }
    else if (move_tick == 1000) {
        gotoxy(10, 15);
        printf("��");
    }
    else if (move_tick == 1500) {
        gotoxy(10, 20);
        printf("��");
    }
    else if (move_tick == 2100) {
        gotoxy(10, 25);
        printf("��");
    }
    else if (move_tick == 2600) {
        gotoxy(10, 30);
        printf("��");
    }
    else if (move_tick == 3000) {
        gotoxy(10, 35);
        printf("��");
    }
    else if (move_tick == 3300) {
        gotoxy(10, 40);
        printf("��");
    }
    else if (move_tick == 3500) {
        gotoxy(10, 45);
        printf("��");
    }
}



int* pos_change(int bef_px[], int bef_py[]) {
    int* res = (int*)malloc(sizeof(int) * PLAYER_MAX);

    for (int i = 0; i < PLAYER_MAX; i++) res[i] = 0;

    int is_back = 0;
    for (int i = 0; i < PLAYER_MAX; i++) {
        if (px[i] != bef_px[i]) { // �÷��̾�� �ڿ� �ִ��� ������ �˻�
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
        if (py[i] != bef_py[i]) { // y�� �ٸ� ���
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

        // player 0�� ������ ������(4����)
        key_t key = get_key();
        if (key == K_QUIT) {
            game_q();  break;
        }
        else if (key != K_UNDEFINED) {
            move_manual(key);
        }

        // player 1 ���ʹ� �������� ������(8����)
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

        if (move_tick >= 3500) { // ����ȭ~ �޼��� ���
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

            for (int i = 0; i < 300; i++) { // 3�� ��� �� 10% Ȯ���� ������ �̵�
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
    }// ���� �ð� �־ �ð� �������� ���� ������ ����� ����ڸ� �̴� ��.

    
    return;
}
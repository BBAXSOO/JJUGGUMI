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


void handle_encounter(int player_index) {
    char message[100];
    snprintf(message, sizeof(message), "(1. ��Ż, 2. ȸ��, 3. ����)");
    dialog(message);

    int choice = _getch();
    switch (choice) {
    case '1':
        if (player[player_index].str > player[0].str) {
            dialog("��Ż ����");
            player[0].stamina -= 0.6 * player[0].stamina;
        }
        else {
            player[0].stamina -= 0.4 * player[0].stamina;
            player[0].str += 2;
            dialog("��Ż ����");
        }
        break;

    case '2':
        if (player[player_index].intel > player[0].intel) {
            dialog("ȸ�� ����");
            player[0].intel += 2;
            player[0].stamina -= 0.2 * player[0].stamina;
        }
        else {
            dialog("ȸ�� ����");
            player[0].stamina -= 0.4 * player[0].stamina;
        }
        break;

    case '3':
        dialog("����");
        break;


    }
}


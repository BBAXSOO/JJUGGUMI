#pragma once
#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// ȭ�� ũ��(�� ũ��x. �� + ����â)
#define ROW_MAX		40
#define COL_MAX		80
// �ٴٸ��� �� ũ�� �� ���۸� ����
#define jul_x           28
#define jul_y           3
// �ٴٸ��� ũ�� ��������
char jul_buffer[jul_y][jul_x];
char jul_buffer_clon[jul_y][jul_x];
// ���� ���۸�
// back_buf[][]�� ���̰�, 
// front_buf[][]�� ȭ�鿡 ����ϱ� ���� ����
// ����: https://codevang.tistory.com/39
// ������API�ε� ����: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];

// �� ũ��(���� buf�� �ؽ�Ʈ���� ������ ĵ���� ũ��)
int N_ROW, N_COL;

void map_init(int n_row, int n_col);
void dialog(char message[]);
bool placable(int row, int col);
void display(void);
void jul_str_draw_p(void);
void jul_str_draw_m(void);
void gotoxy(int x, int y);
void printxy(char ch, int row, int col);
void game_q(void);
void intro_JJU(void);
void intro_op(void);
void ending(void);



#endif 
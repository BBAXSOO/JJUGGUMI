#pragma once
#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// 화면 크기(맵 크기x. 맵 + 상태창)
#define ROW_MAX		40
#define COL_MAX		80
// 줄다리기 맵 크기 및 버퍼링 설정
#define jul_x           28
#define jul_y           3
// 줄다리기 크기 전역변수
char jul_buffer[jul_y][jul_x];
char jul_buffer_clon[jul_y][jul_x];
// 더블 버퍼링
// back_buf[][]가 맵이고, 
// front_buf[][]는 화면에 출력하기 위한 정보
// 참고: https://codevang.tistory.com/39
// 윈도우API로도 가능: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];

// 맵 크기(위의 buf는 텍스트까지 포함한 캔버스 크기)
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
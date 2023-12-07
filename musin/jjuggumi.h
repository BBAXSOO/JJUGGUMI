#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10
#define ITEM_MAX		10

typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
}ITEM;


typedef struct {
	int id;
	char name[100];

	int intel, str, stamina;

	bool is_alive;
	bool hasitem;
	ITEM item;
} PLAYER;


typedef struct {
	double str_left; // 홀수 (예: 1, 3, 5)   왼쪽  4 5 3 >> 2, 2.5 1.5= 6   
} LEFT_SUM;

typedef struct {
	double str_light; // 짝수 (예: 0, 2, 4) 오른쪽  7 6 4 --> 3.5 3,2= 8.5  만약 아이템버프도 있으면 더 늘어나는게 정상!
} LIGHT_SUM;

ITEM item[ITEM_MAX];
PLAYER player[PLAYER_MAX];
 
int n_player, n_alive, n_item;
int tick;  // 시계
double str_a;// 유효 힘
int str_w;// 14 정 가운데 칸 번호  총 이동 가동범위는 4~ 24
//   4  5   6  7   8  9 10 11 12 13  14  15 16  17  18  19   20  21   22   23   24
//   x  x   x  x   x  1  3  5 -  -    -   -  -   0   2   4   x   x    x    x     x 
//                      
// 미니게임
//void sample(void);
//void mugunghwa(void);
//void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif

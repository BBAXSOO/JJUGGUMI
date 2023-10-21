#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10

typedef
struct {
	int s0_count;
	int s1_count;
	int s2_count;
	int s3_count;
} m_player;

bool player[PLAYER_MAX];  // 기본값 true, 탈락하면 false
int n_player, n_alive;
int tick;  // 시계

// 미니게임
//void sample(void);
void mugunghwa(void);
//void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif

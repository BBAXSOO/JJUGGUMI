

/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define	DATA_FILE	"jjuggumi.dat"


#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		10

bool player[PLAYER_MAX];  // 기본값 true, 탈락하면 false
int n_player, n_alive;
int tick;  // 시계

// 미니게임
void sample(void);
//void mugunghwa(void);
//void mugunghwa(void);
//void nightgame(void);
//void juldarigi(void);
//void jebi(void);

int randint(int low, int high);

#endif

int jjuggumi_init(void);

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

int main(void) {
	jjuggumi_init();
	sample();
	//mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}*/
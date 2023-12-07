#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define	DATA_FILE	"jjuggumi.dat"



// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

void jjuggumi_init(void) {
	
	srand((unsigned int)time(NULL));

	intro_op();
	system("cls");
	

	srand((unsigned int)time(NULL));

	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");
	if (fp == NULL)
	{
		return -1;
	}
	fscanf_s(fp, "%d", &n_player);
	for (int i = 0; i < n_player; i++)
	{
		int playeridx = i;
		PLAYER* p = &player[playeridx];
		fscanf_s(fp, "%s%d%d%d",
			p->name, (unsigned int)sizeof(p->name),
			&(p->intel), &(p->str), &(p->stamina));

		p->stamina = 50;

		p->is_alive = true;
		p->hasitem = false;
	}


	int num_item;
	fscanf_s(fp, "%d", &num_item);
	for (int i = 0; i < num_item; i++)
	{
		fscanf_s(fp, "%s%d%d%d",
			item[i].name, (unsigned int)sizeof(item[i].name),
			&(item[i].intel_buf),
			&(item[i].str_buf),
			&(item[i].stamina_buf));
	}

	fclose(fp);
	n_alive = n_player;

	return 0;


}
/*
int main(void) {
	//jjuggumi_init();
	//sample();
	//mugunghwa();
	nightgame();
	//juldarigi();
	//jebi();
	return 0;
}*/
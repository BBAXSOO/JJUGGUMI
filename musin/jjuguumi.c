#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "jjuggumi.h"
#include "canvas.h"
#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}


int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	FILE* fp;
	fopen_s(&fp, DATA_FILE, "r");
	if (fp == NULL) {
		return -1;// -1 �����ϸ� �����Լ����� ó���ϰ� ����
	}
	// �÷��̾� ������ load
	fscanf_s(fp, "%d", &n_player);
	for (int i = 0; i < n_player; i++) {
		PLAYER* p = &player[i];
		
		fscanf_s(fp, "%s%d%d%d",
						p->name, (unsigned int)sizeof(p->name),
						&(p->intel), &(p->str), &(p->stamina)); // ����ü �÷��̾� �ּҾȿ� ����
		p->id = i;
		p->stamina = 50;
		p->is_alive = true;
		p->hasitem = false;
	}
	fscanf_s(fp, "%d", &n_item);   //����ü ������ �ּ� �ȿ� ����
	for (int i = 0; i < n_item; i++) {
					fscanf_s(fp, "%s%d%d%d",
									item[i].name, (unsigned int)sizeof(item[i].name),
									&(item[i].intel_buf),
									&(item[i].str_buf),
									&(item[i].stamina_buf));
	}
	fclose(fp);
	
	
	return 0;
}


int main(void) {		
	jjuggumi_init();
	//sample();
	//mugunghwa();
	//nightgame();
	juldarigi();
	//jebi();

	
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"


#define DATA_FILE "jjuggumi.dat"
 
int jul_cm = 0; // ����jul_mm 14�� �ٰ����� 5�� ������� ī��Ʈ 1�� ���� �׷����� 1�� �Ǹ� 5�� �Է��̵Ǹ�ȴ�
int jul_cp = 0; // ���� jul_pp�� 14�� �ٰ����� 0�� ������� ī��Ʈ 1�� ���� �׷����� 1�� �Ǹ� 0�� �Է��̵Ǹ�ȴ�


int jul_mm = 11; // jul_mm�� 14�� �ٰ����� 5�� ����� ��������� ī��Ʈ �� �������� ������� -1  
int jul_pp = 17; //jul_pp�� 14�� �ٰ����� 0�� ����� �� ���������� ������� +1 


void jul_str(void);
//void juldarigi_move(void);
void jul_random(PLAYER*, LEFT_SUM*, LIGHT_SUM*, int);


//
// Ȧ���� ���� ¦���� ������ ������
void jul_random(PLAYER* play, LEFT_SUM* le_s, LIGHT_SUM* Li_s,int a) {
    if (a % 2 == 0) { // ¦�� 
        (double)Li_s->str_light +=( (double)(play->str + play->item.str_buf) * ((double)(play->stamina)/100));
        
    }
    else { // Ȧ��   
        (double)le_s->str_left += ((double)(play->str + play->item.str_buf) * ((double)(play->stamina)/100));
    }
   
}

// str �� ����
void jul_str(void) {
    PLAYER* pp;

    // ����ü �迭 �޸� �Ҵ��ϱ�
    LEFT_SUM* le_s = (LEFT_SUM*)malloc(sizeof(LEFT_SUM));
    LIGHT_SUM* Li_s = (LIGHT_SUM*)malloc(sizeof(LIGHT_SUM));
    // �޸𸮰� �����ϸ� �ٷ� ����
    if (le_s == NULL || Li_s == NULL) {
        return 1;
    }
    // �޸𸮸� �Ҵ� ���ϸ� �ʱ�ȭ�����ʾҴٸ鼭 ������ ��� ����.... �ᱹ �޸� �Ҵ��� �� �ۿ�����
    // str �� �� ���ϱ� 
    le_s->str_left = 0;
    Li_s->str_light = 0;

    for (int i = 0; i < n_player; i++) {
        pp = &player[i];

        // �� �÷��̾ ���� ����ü �ʱ�ȭ
        LEFT_SUM le_s_player = { 0 };
        LIGHT_SUM Li_s_player = { 0 };

        jul_random(pp, &le_s_player, &Li_s_player, i);

      
        Li_s->str_light += Li_s_player.str_light;
        le_s->str_left += le_s_player.str_left;

    }
    printf("\n\n\n\n\n");
    str_a = (-le_s->str_left) + Li_s->str_light;
    printf("str:%.2lf\n\n\n",str_a);
    if (str_a < 0) {
        // ���� ������ ��� �������� �̵�

    }
    else if (str_a > 0) {
        // ���� ����� ��� ���������� �̵�

    }
    //  �޸� ����
  
}

void jul_str_draw_m(void) { //�����϶�

    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if ((i == 1) && (j >= 4 && j <= 24)) {
                jul_buffer_clon[i][j] = ' ';

            }
        }
    }
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if ((i == 1) && (j >= 4 && j <= 24)) {

                if (jul_pp == 17) {
                    if (jul_buffer[i][9] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }

                    if (jul_buffer[i][10] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][9] = '-';
                        }
                        else {
                            jul_buffer_clon[i][9] = '3';
                        }
                    }
                    if (jul_buffer[i][11] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][10] = '-';
                        }
                        else {
                            jul_buffer_clon[i][10] = '5';
                        }
                    }
                    if (jul_buffer[i][12] == '-') {
                        jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][17] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][16] = '-';
                        }
                        else {
                            jul_buffer_clon[i][16] = '0';
                        }
                    }
                    if (jul_buffer[i][18] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][17] = '-';
                        }
                        else {
                            jul_buffer_clon[i][17] = '2';
                        }
                    }
                    if (jul_buffer[i][19] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][18] = '-';
                        }
                        else {
                            jul_buffer_clon[i][18] = '4';
                        }
                    }
                }

                //   4  5   6  7   8  9 10 11 12 13  14  15 16  17  18  19   20  21   22   23   24
//                x  x   x  x   x  1  3  5 -  -    -   -  -   0   2   4   x   x    x    x     x 
                else if (jul_pp == 16) {
                    //����

                    if (jul_buffer[i][8] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][9] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '3';
                        }
                    }
                    if (jul_buffer[i][10] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][9] = '-';
                        }
                        else {
                            jul_buffer_clon[i][9] = '5';
                        }
                    }
                    if (jul_buffer[i][11] == '-') {
                        jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][16] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '0';
                        }
                    }
                    if (jul_buffer[i][17] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][16] = '-';
                        }
                        else {
                            jul_buffer_clon[i][16] = '2';
                        }
                    }
                    if (jul_buffer[i][18] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][17] = '-';
                        }
                        else {
                            jul_buffer_clon[i][17] = '4';
                        }
                    }

                }
                else if (jul_pp == 15) {
                    jul_cp++;
                    if (jul_buffer[i][7] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][8] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '3';
                        }
                    }
                    if (jul_buffer[i][9] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '5';
                        }
                    }
                    if (jul_buffer[i][10] == '-') {
                        jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][15] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '0';
                        }
                    }
                    if (jul_buffer[i][16] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '2';
                        }
                    }
                    if (jul_buffer[i][15] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '4';
                        }
                    }

                }
                if (jul_pp == 14) {
                    jul_cp++;
                    if (jul_buffer[i][6] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][5] = '-';
                        }
                        else {
                            jul_buffer_clon[i][5] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][7] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '3';
                        }
                    }
                    if (jul_buffer[i][8] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '5';
                        }
                    }
                    if (jul_buffer[i][9] == '-') {
                        jul_buffer_clon[i][10] = '-'; jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][14] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '0';
                        }
                    }
                    if (jul_buffer[i][15] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '2';
                        }
                    }
                    if (jul_buffer[i][16] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '4';
                        }
                    }
                }
                if (jul_pp == 13) {
                    jul_cp++;
                    if (jul_buffer[i][5] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][4] = '-';
                        }
                        else {
                            jul_buffer_clon[i][4] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][6] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][5] = '-';
                        }
                        else {
                            jul_buffer_clon[i][5] = '3';
                        }
                    }
                    if (jul_buffer[i][7] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '5';
                        }
                    }
                    if (jul_buffer[i][8] == '-') {
                        jul_buffer_clon[i][9] = '-'; jul_buffer_clon[i][10] = '-'; jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][13] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '0';
                        }
                    }
                    if (jul_buffer[i][14] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '2';
                        }
                    }
                    if (jul_buffer[i][15] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '4';
                        }
                    }
                }
            }
        }
    }
    jul_pp--;
    jul_mm++;

}
void jul_str_draw_p(void) {// ����϶� ���������� ����� ���� ����

    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if ((i == 1) && (j >= 4 && j <= 24)) {
                jul_buffer_clon[i][j] = ' ';

            }
        }
    }
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if ((i == 1) && (j >= 4 && j <= 24)) {

                if (jul_pp == 17) {
                    if (jul_buffer[i][9] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][10] = '-';
                        }
                        else {
                            jul_buffer_clon[i][10] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][10] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][11] = '-';
                        }
                        else {
                            jul_buffer_clon[i][11] = '3';
                        }
                    }
                    if (jul_buffer[i][11] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '5';
                        }
                    }
                    if (jul_buffer[i][12] == '-') {
                        jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][17] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][18] = '-';
                        }
                        else {
                            jul_buffer_clon[i][18] = '0';
                        }
                    }
                    if (jul_buffer[i][18] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][19] = '-';
                        }
                        else {
                            jul_buffer_clon[i][19] = '2';
                        }
                    }
                    if (jul_buffer[i][19] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][20] = '-';
                        }
                        else {
                            jul_buffer_clon[i][20] = '4';
                        }
                    }
                }


                else if (jul_pp == 18) {
                    //����

                    if (jul_buffer[i][10] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][11] = '-';
                        }
                        else {
                            jul_buffer_clon[i][11] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][11] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '3';
                        }
                    }
                    if (jul_buffer[i][12] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '5';
                        }
                    }
                    if (jul_buffer[i][13] == '-') {
                        jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][18] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][19] = '-';
                        }
                        else {
                            jul_buffer_clon[i][19] = '0';
                        }
                    }
                    if (jul_buffer[i][19] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][20] = '-';
                        }
                        else {
                            jul_buffer_clon[i][20] = '2';
                        }
                    }
                    if (jul_buffer[i][20] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][21] = '-';
                        }
                        else {
                            jul_buffer_clon[i][21] = '4';
                        }
                    }

                }
                else if (jul_pp == 19) {
                    jul_cm++;
                    if (jul_buffer[i][11] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][12] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '3';
                        }
                    }
                    if (jul_buffer[i][13] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '5';
                        }
                    }
                    if (jul_buffer[i][14] == '-') {
                        jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][19] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][20] = '-';
                        }
                        else {
                            jul_buffer_clon[i][20] = '0';
                        }
                    }
                    if (jul_buffer[i][20] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][21] = '-';
                        }
                        else {
                            jul_buffer_clon[i][21] = '2';
                        }
                    }
                    if (jul_buffer[i][21] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][22] = '-';
                        }
                        else {
                            jul_buffer_clon[i][22] = '4';
                        }
                    }

                }
                if (jul_pp == 20) {
                    jul_cm++;
                    if (jul_buffer[i][12] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][13] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '3';
                        }
                    }
                    if (jul_buffer[i][14] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '5';
                        }
                    }
                    if (jul_buffer[i][15] == '-') {
                        jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-'; jul_buffer_clon[i][20] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][20] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][21] = '-';
                        }
                        else {
                            jul_buffer_clon[i][21] = '0';
                        }
                    }
                    if (jul_buffer[i][21] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][22] = '-';
                        }
                        else {
                            jul_buffer_clon[i][22] = '2';
                        }
                    }
                    if (jul_buffer[i][22] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][23] = '-';
                        }
                        else {
                            jul_buffer_clon[i][23] = '4';
                        }
                    }
                }
                if (jul_pp == 21) {

                    if (jul_buffer[i][13] == '1') { // 18�̶�� ó�� ������ �� �ǹ� �׷� i j�� �Ȱ��ƾ��� 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '1';  // �� �� ����� j�� j+1�� �Ǿߴ�!! 
                        } // ���� �� ���۷� �Է��ϸ� ���� ���ǹ��� �����̾ȵ�  1 7
                    }
                    if (jul_buffer[i][14] == '3') { // 3 �� 10���� 11�� ���� ��    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '3';
                        }
                    }
                    if (jul_buffer[i][15] == '5') { // 3 �� 10���� 11�� ���� ��     1 9
                        if (jul_cm >= 1) { // �̰� ���������� ������ �� j=14 �� 5�� 14ĭ�� ���� �� cm �� �ö󰡼� �������� -�� ����
                            jul_buffer_clon[i][16] = '-';
                        }
                        else {
                            jul_buffer_clon[i][16] = '5';
                        }
                    }
                    if (jul_buffer[i][16] == '-') {
                        jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-'; jul_buffer_clon[i][20] = '-'; jul_buffer_clon[i][21] = '-';

                    }
                    // ������ 
                    if (jul_buffer[i][21] == '0') { //�ٹ��۴� �̸� �Է��ϱ����� �ٴٸ��� �� ����ü��
                        //�����س��� �׷��� �ٹ��۸� ����
                    // ���� �س��� �� 
                        if (jul_cp >= 1) {
                            jul_buffer_clon[i][22] = '-';
                        }
                        else {
                            jul_buffer_clon[i][22] = '0';
                        }
                    }
                    if (jul_buffer[i][22] == '2') {
                        if (jul_cp >= 2) {
                            jul_buffer_clon[i][23] = '-';
                        }
                        else {
                            jul_buffer_clon[i][23] = '2';
                        }
                    }
                    if (jul_buffer[i][23] == '4') {
                        if (jul_cp >= 3) {
                            jul_buffer_clon[i][24] = '-';
                        }
                        else {
                            jul_buffer_clon[i][24] = '4';
                        }
                    }
                }
            }
        }
    }
    jul_pp++;
    jul_mm--;

}


void juldarigi(void) {
    PLAYER* pp;
    LEFT_SUM* le_s = (LEFT_SUM*)malloc(sizeof(LEFT_SUM));
    LIGHT_SUM* Li_s = (LIGHT_SUM*)malloc(sizeof(LIGHT_SUM));
    if (le_s == NULL || Li_s == NULL) {
        return 1;
    }

    // �׾��� ����� �츮��
    for (int i = 0; i < n_player; i++) {
        pp = &player[i];
        if (pp->is_alive == 0) {
            pp->is_alive == 1;
            pp->hasitem == 0;
        }
    }

    tick = 100;

    jul_but_init();// ���ۿ��ٰ� �ϴ� �Է��س��� .. �׷��� while ���� �ȳ־ ��� ���
    while (1) {

        for (int i = 0; i < jul_y; i++) {
            for (int j = 0; j < jul_x; j++) {
                jul_buffer[i][j] = jul_buffer_clon[i][j];

            }
        }
        for (int i = 0; i < jul_y; i++) {
            for (int j = 0; j < jul_x; j++) {
                gotoxy(i, j);
                printf("%c", jul_buffer_clon[i][j]);

            }
        }
        le_s->str_left = 0;
        Li_s->str_light = 0;


        for (int i = 0; i < n_player; i++) {
            pp = &player[i];

            // �� �÷��̾ ���� ����ü �ʱ�ȭ
            LEFT_SUM le_s_player = { 0 };
            LIGHT_SUM Li_s_player = { 0 };

            jul_random(pp, &le_s_player, &Li_s_player, i);


            Li_s->str_light += Li_s_player.str_light;
            le_s->str_left += le_s_player.str_left;

        }
        printf("\n\n\n\n\n");
        str_a = (-le_s->str_left) + Li_s->str_light;

        if (tick % 1000 == 0) {
            if (str_a < 0) {
                // ���� ������ ��� �������� �̵�
                jul_str_draw_m();
                // ���⿡ �������� �����̴� �Լ��ֱ�(������ "����"������ �ؾߴ� �ٷ� ����ϴ°� �ƴ�)
            }
            else if (str_a > 0) {
                // ���� ����� ��� ���������� �̵�

                jul_str_draw_p();
                // ���⿡ ���������� �̵��ϴ� �Լ� �ֱ� (�ֳĸ� ��� �Լ��� �����ֱ� ������ ���۷� �����ϰ�)
                // ��µǰ� �ϸ� ��

            }
            else if (str_a == 0) {

            }
        }

        printf("str:%.2lf\n\n\n", str_a);
        jul_display();


        tick += 100;
        Sleep(60);


        // ¦�� �¸� �� Ȧ�� �¸� ����ǰ �������� �� Ż���� ���
        if (jul_buffer_clon[1][24] == '4') {
            system("cls");
            printf("¦���� ���ں�Ȱ�� ���!!\n");
            for (int i = 0; i <= 4; i += 2) {
                pp = &player[i];
                //�¸���
                if (pp->is_alive == 0) {
                    pp->is_alive = 1;
                    pp->hasitem = 0;
                }
            }
            //�й���
            for (int i = 1; i <= 5; i += 2) {
                pp = &player[i];
                if (pp->is_alive == 1) {
                    pp->hasitem = 0;
                    pp->str /= 2;
                    pp->intel /= 2;
                }
            }
            break;

        }
        else if (jul_buffer_clon[1][4] == '1') {
            system("cls");
            printf("Ȧ���� ���ں�Ȱ�� ���!!\n");
            //�¸���
            for (int i = 1; i <= 5; i += 2) {
                pp = &player[i];
                if (pp->is_alive == 0) {
                    pp->is_alive = 1;
                    pp->hasitem = 0;
                }

            }
            //�й���
            for (int i = 0; i <= 4; i += 2) {
                pp = &player[i];
                if (pp->is_alive == 1) {
                    pp->hasitem = 0;
                    pp->str /= 2;
                    pp->intel /= 2;
                }
            }

            break;
        }
       
    }
    free(le_s);
    free(Li_s);

    printf(" ���� ������ ����̱��Դϴ�!!");
    return 0;
}


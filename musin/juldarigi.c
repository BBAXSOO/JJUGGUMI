#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"


#define DATA_FILE "jjuggumi.dat"
 
int jul_cm = 0; // 만약jul_mm 14에 다가가서 5가 사라지면 카운트 1이 증가 그런다음 1이 되면 5은 입력이되면안댐
int jul_cp = 0; // 만약 jul_pp가 14에 다가가서 0이 사라지면 카운트 1이 증가 그런다음 1이 되면 0은 입력이되면안댐


int jul_mm = 11; // jul_mm이 14에 다가가면 5가 사라짐 사라졌으면 카운트 단 왼쪽으로 당겨지면 -1  
int jul_pp = 17; //jul_pp가 14에 다가가면 0이 사라짐 단 오른쪽으로 당겨지면 +1 


void jul_str(void);
//void juldarigi_move(void);
void jul_random(PLAYER*, LEFT_SUM*, LIGHT_SUM*, int);


//
// 홀수는 왼쪽 짝수는 오른쪽 나누기
void jul_random(PLAYER* play, LEFT_SUM* le_s, LIGHT_SUM* Li_s,int a) {
    if (a % 2 == 0) { // 짝수 
        (double)Li_s->str_light +=( (double)(play->str + play->item.str_buf) * ((double)(play->stamina)/100));
        
    }
    else { // 홀수   
        (double)le_s->str_left += ((double)(play->str + play->item.str_buf) * ((double)(play->stamina)/100));
    }
   
}

// str 합 정의
void jul_str(void) {
    PLAYER* pp;

    // 구조체 배열 메모리 할당하기
    LEFT_SUM* le_s = (LEFT_SUM*)malloc(sizeof(LEFT_SUM));
    LIGHT_SUM* Li_s = (LIGHT_SUM*)malloc(sizeof(LIGHT_SUM));
    // 메모리가 부족하면 바로 종료
    if (le_s == NULL || Li_s == NULL) {
        return 1;
    }
    // 메모리를 할당 못하면 초기화되지않았다면서 오류가 계속 생김.... 결국 메모리 할당할 수 밖에없음
    // str 총 합 구하기 
    le_s->str_left = 0;
    Li_s->str_light = 0;

    for (int i = 0; i < n_player; i++) {
        pp = &player[i];

        // 각 플레이어에 대한 구조체 초기화
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
        // 힘이 음수일 경우 왼쪽으로 이동

    }
    else if (str_a > 0) {
        // 힘이 양수일 경우 오른쪽으로 이동

    }
    //  메모리 해제
  
}

void jul_str_draw_m(void) { //음수일때

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
                    if (jul_buffer[i][9] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }

                    if (jul_buffer[i][10] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][9] = '-';
                        }
                        else {
                            jul_buffer_clon[i][9] = '3';
                        }
                    }
                    if (jul_buffer[i][11] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][10] = '-';
                        }
                        else {
                            jul_buffer_clon[i][10] = '5';
                        }
                    }
                    if (jul_buffer[i][12] == '-') {
                        jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][17] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    //왼쪽

                    if (jul_buffer[i][8] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][9] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '3';
                        }
                    }
                    if (jul_buffer[i][10] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][9] = '-';
                        }
                        else {
                            jul_buffer_clon[i][9] = '5';
                        }
                    }
                    if (jul_buffer[i][11] == '-') {
                        jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][16] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    if (jul_buffer[i][7] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][8] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '3';
                        }
                    }
                    if (jul_buffer[i][9] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][8] = '-';
                        }
                        else {
                            jul_buffer_clon[i][8] = '5';
                        }
                    }
                    if (jul_buffer[i][10] == '-') {
                        jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][15] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    if (jul_buffer[i][6] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][5] = '-';
                        }
                        else {
                            jul_buffer_clon[i][5] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][7] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '3';
                        }
                    }
                    if (jul_buffer[i][8] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][7] = '-';
                        }
                        else {
                            jul_buffer_clon[i][7] = '5';
                        }
                    }
                    if (jul_buffer[i][9] == '-') {
                        jul_buffer_clon[i][10] = '-'; jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][14] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    if (jul_buffer[i][5] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][4] = '-';
                        }
                        else {
                            jul_buffer_clon[i][4] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][6] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][5] = '-';
                        }
                        else {
                            jul_buffer_clon[i][5] = '3';
                        }
                    }
                    if (jul_buffer[i][7] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][6] = '-';
                        }
                        else {
                            jul_buffer_clon[i][6] = '5';
                        }
                    }
                    if (jul_buffer[i][8] == '-') {
                        jul_buffer_clon[i][9] = '-'; jul_buffer_clon[i][10] = '-'; jul_buffer_clon[i][11] = '-'; jul_buffer_clon[i][12] = '-'; jul_buffer_clon[i][13] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][13] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
void jul_str_draw_p(void) {// 양수일때 오른쪽으로 땡기는 버퍼 저장

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
                    if (jul_buffer[i][9] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][10] = '-';
                        }
                        else {
                            jul_buffer_clon[i][10] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][10] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][11] = '-';
                        }
                        else {
                            jul_buffer_clon[i][11] = '3';
                        }
                    }
                    if (jul_buffer[i][11] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '5';
                        }
                    }
                    if (jul_buffer[i][12] == '-') {
                        jul_buffer_clon[i][13] = '-'; jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][17] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    //왼쪽

                    if (jul_buffer[i][10] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][11] = '-';
                        }
                        else {
                            jul_buffer_clon[i][11] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][11] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '3';
                        }
                    }
                    if (jul_buffer[i][12] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '5';
                        }
                    }
                    if (jul_buffer[i][13] == '-') {
                        jul_buffer_clon[i][14] = '-'; jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][18] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    if (jul_buffer[i][11] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][12] = '-';
                        }
                        else {
                            jul_buffer_clon[i][12] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][12] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '3';
                        }
                    }
                    if (jul_buffer[i][13] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '5';
                        }
                    }
                    if (jul_buffer[i][14] == '-') {
                        jul_buffer_clon[i][15] = '-'; jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][19] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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
                    if (jul_buffer[i][12] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][13] = '-';
                        }
                        else {
                            jul_buffer_clon[i][13] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][13] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '3';
                        }
                    }
                    if (jul_buffer[i][14] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '5';
                        }
                    }
                    if (jul_buffer[i][15] == '-') {
                        jul_buffer_clon[i][16] = '-'; jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-'; jul_buffer_clon[i][20] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][20] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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

                    if (jul_buffer[i][13] == '1') { // 18이라면 처음 땡겼을 때 의미 그럼 i j는 똑같아야함 
                        if (jul_cm >= 3) {
                            jul_buffer_clon[i][14] = '-';
                        }
                        else {
                            jul_buffer_clon[i][14] = '1';  // 두 번 땡기면 j는 j+1이 되야댐!! 
                        } // 만약 줄 버퍼로 입력하면 다음 조건문에 성립이안됨  1 7
                    }
                    if (jul_buffer[i][14] == '3') { // 3 이 10에서 11로 갔을 때    1 8
                        if (jul_cm >= 2) {
                            jul_buffer_clon[i][15] = '-';
                        }
                        else {
                            jul_buffer_clon[i][15] = '3';
                        }
                    }
                    if (jul_buffer[i][15] == '5') { // 3 이 10에서 11로 갔을 때     1 9
                        if (jul_cm >= 1) { // 이건 오른쪽으로 땡겼을 때 j=14 즉 5가 14칸에 갔을 때 cm 이 올라가서 없어진후 -가 생성
                            jul_buffer_clon[i][16] = '-';
                        }
                        else {
                            jul_buffer_clon[i][16] = '5';
                        }
                    }
                    if (jul_buffer[i][16] == '-') {
                        jul_buffer_clon[i][17] = '-'; jul_buffer_clon[i][18] = '-'; jul_buffer_clon[i][19] = '-'; jul_buffer_clon[i][20] = '-'; jul_buffer_clon[i][21] = '-';

                    }
                    // 오른쪽 
                    if (jul_buffer[i][21] == '0') { //줄버퍼는 미리 입력하기전에 줄다리기 맵 그자체로
                        //저장해놓음 그래서 줄버퍼를 조건
                    // 으로 해놓은 것 
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

    // 죽었던 사람들 살리기
    for (int i = 0; i < n_player; i++) {
        pp = &player[i];
        if (pp->is_alive == 0) {
            pp->is_alive == 1;
            pp->hasitem == 0;
        }
    }

    tick = 100;

    jul_but_init();// 버퍼에다가 싹다 입력해놓음 .. 그래서 while 문에 안넣어도 계속 출력
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

            // 각 플레이어에 대한 구조체 초기화
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
                // 힘이 음수일 경우 왼쪽으로 이동
                jul_str_draw_m();
                // 여기에 왼쪽으로 움직이는 함수넣기(무조건 "버퍼"식으로 해야댐 바로 출력하는게 아닌)
            }
            else if (str_a > 0) {
                // 힘이 양수일 경우 오른쪽으로 이동

                jul_str_draw_p();
                // 여기에 오른쪽으로 이동하는 함수 넣기 (왜냐면 출력 함수는 위에있기 때문에 버퍼로 저장하고)
                // 출력되게 하면 됨

            }
            else if (str_a == 0) {

            }
        }

        printf("str:%.2lf\n\n\n", str_a);
        jul_display();


        tick += 100;
        Sleep(60);


        // 짝수 승리 및 홀수 승리 전리품 가져가기 및 탈락자 배분
        if (jul_buffer_clon[1][24] == '4') {
            system("cls");
            printf("짝수팀 패자부활전 우승!!\n");
            for (int i = 0; i <= 4; i += 2) {
                pp = &player[i];
                //승리자
                if (pp->is_alive == 0) {
                    pp->is_alive = 1;
                    pp->hasitem = 0;
                }
            }
            //패배자
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
            printf("홀수팀 패자부활전 우승!!\n");
            //승리자
            for (int i = 1; i <= 5; i += 2) {
                pp = &player[i];
                if (pp->is_alive == 0) {
                    pp->is_alive = 1;
                    pp->hasitem = 0;
                }

            }
            //패배자
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

    printf(" 다음 게임은 제비뽑기입니다!!");
    return 0;
}


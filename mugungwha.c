#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
char front_buf;
void gotoxy(int row, int col);
void draw(void);
int map_tick = 0;
int tick = 0;
int move_tick = 0;
char map[100][300], front[100][300], front_mu_tick[100]; front_mu[100];
char mug_name[] = "무궁화꽃이피었습니다";
int mu_count = 0;


void printxy(char ch, int row, int col) {
    gotoxy(row, col);
    printf("%c", ch);
}
void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void draw(void) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(i, j);
                printf("%c", front[i][j]);
            }


        }
    }

}
void mudraw(void) {
    for (int i = 11; i <= 11; i++) { //말그대로 총 3번 반복되면 0.9초임 즉 3번 반복되면 무궁이 출력되어야함 
        for (int j = 0; j <= mu_count; j++) {
            if (front_mu[i] != mug_name[i]) { // 얘네들은 더블 버퍼링으로써 렉 안걸리게하려고 복붙하는거
                front_mu[i] = mug_name[i];// 또한 좌표 출력에 상관없음 얘네는 그냥 무궁화 문장 복붙임
                gotoxy(i, j);// 이놈은 j,i에 출력해주는거임 
                putchar(front_mu);
            }
        }
    }
}
// 무궁화 꽃 문장만의 tick 을 만들어서 몇초가 지나면 카운트되고 그 카운트 된걸 message[i]에 입력하는거? 만약 tick 1이면 
// for(int 1=0;i<=1;i++) 하고 0,1 까지 계속 반복하면 무만 나올거잖아!!!!!!!!!!!!!1

// 문제점: 무궁화꽃 문장이 출력되는동안 draw함수가 실행이 안되서 실시간 출력이 안됨 따라서 실시간 출력이
//되면서 무궁화꽃이 출력이 되어야함
// 그래서 실시간 출력이 되면서 삭제됐다 다시 출력됐다를 몇초간 지속되게 하고
// 계속 출력해 나가면 되지않을까 
//문자가 출력된 후 무가 출력되고 나서 다시 출력이됨 그리고 1초후 무궁이 출력되고 다시 1초후에 무궁화가 출력이됨
// 이렇게 출력을 하다보면 되지않을까 싶음..
// 아니면 변수 하나 만들어서 무가 다 출력되면 숫자를 2번 늘려서 2개 출력하게 하는 방법도있음( 한글은 2byte)

//0.3초 일때 1000, 3초일때 10000, 9초일때 30000 , 9.9초일때 33000

int main(void) {
    srand(time(NULL));
    int mu[] = strlen(mug_name);
    //벽이랑 술래 전환
    while (1) {
        if (mu_count >= 30) {// 무카운트가 30을 넘으면 30번 반복이 되기에 0으로 초기화 시킴 
            int mu_count = 0;
        }
      
        for (int i = 0; i < 11; i++) {

            for (int j = 0; j < 45; j++) {

                if (i == 0 || i == 10 || j == 0 || j == 44) {
                    map[i][j] = '#';

                }
                else if (i >= 4 && i <= 6 && j <= 1)
                {
                    if (map_tick >= 10000 && map_tick <= 13000)
                    {
                        map[i][j] = '@';
                    }
                    else
                    {
                        map[i][j] = '#';
                    }
                }
                else
                {
                    map[i][j] = ' ';
                }

                if (map_tick <= 13000)
                {
                    map_tick += 1000;
                }
                else
                {
                    if (map_tick > 13000)
                    {
                        map_tick == 0;
                    }
                }

            }
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 45; j++)
                {
                    gotoxy(i, j);
                    printf("%c", map[i][j]);
                    fflush(stdout);
                }
            }

            draw();




        }

        //0.3초 일때 1000, 3초일때 10000, 9초일때 30000 , 9.9초일때 33000

        for (int i = 11; i <= 11; i++) { //말그대로 총 3번 반복되면 0.9초임 즉 3번 반복되면 무궁이 출력되어야함 
            for (int j = 0; j <= mu_count; j++) {
                gotoxy(i, j);
                putchar(mug_name[i]);
            }
        }

       



        //움직이는거
        int dx[4] = { -1, 1, 0, 0 };
        int dy[4] = { 0, 0, -1, 1 };
        int x = 3, y = 42;
        int dir = 3;

        int playerx[4];
        int playery[4];



        //랜덤하게 움직이는 것들의 위치
        for (int i = 0; i < 4; i++)
        {
            playerx[i] = 4 + i;
            playery[i] = 43;
            map[playerx[i]][playery[i]] = '1' + i;

        }

        //입력 받아서 움직임
        while (1) {
            if (_kbhit()) {
                int key = _getch();
                switch (key) {
                case 'w':
                    dir = 0;
                    break;
                case 's':
                    dir = 1;
                    break;
                case 'a':
                    dir = 2;
                    break;
                case 'd':
                    dir = 3;
                    break;
                case 'q':
                    return 0;
                }
            }




            //플레이어 이동


            if (move_tick % 10000 == 0)
            {



                if (tick % 50 == 0) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];



                    if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                        if (map[nx][ny] != '1' && map[nx][ny] != '2'
                            && map[nx][ny] != '3' && map[nx][ny] != '4') {
                            map[x][y] = ' ';
                            x = nx;
                            y = ny;
                            map[x][y] = '0';

                            if (ny == 1)
                            {
                                map[x][y] = ' ';
                            }

                        }
                    }


                    for (int i = 0; i < 4; i++) {

                        if (nx < 1) {
                            // 왼쪽 벽과 충돌하는 경우 처리
                            map[playerx[i]][playery[i]] = ' '; // 해당 문자를 공백 문자로 변경하여 화면에서 사라지게 함
                        }
                        else {
                            map[playerx[i]][playery[i]] = '1' + i; // 그 외의 경우에는 원래 문자를 유지
                        }
                        int randommove = rand() % 10 + 1;
                        int randommove_up = rand() % 10 + 1;
                        int randommove_down = rand() % 10 + 1;
                        int randommove_stay = rand() % 10 + 1;


                        if (randommove <= 7)
                        {
                            int nx = playerx[i];
                            int ny = playery[i] - 1;

                            if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                                map[nx][ny] != '1' && map[nx][ny] != '2'
                                && map[nx][ny] != '3' && map[nx][ny] != '4') {
                                map[playerx[i]][playery[i]] = ' ';
                                playerx[i] = nx;
                                playery[i] = ny;
                                map[playerx[i]][playery[i]] = '1' + i;
                            }
                        }


                        if (randommove_up <= 1)
                        {
                            int nx = playerx[i] - 1;
                            int ny = playery[i];

                            if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                                map[nx][ny] != '1' && map[nx][ny] != '2'
                                && map[nx][ny] != '3' && map[nx][ny] != '4') {
                                map[playerx[i]][playery[i]] = ' ';
                                playerx[i] = nx;
                                playery[i] = ny;
                                map[playerx[i]][playery[i]] = '1' + i;
                            }
                        }


                        if (randommove_down <= 1)
                        {
                            int nx = playerx[i] + 1;
                            int ny = playery[i];

                            if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                                map[nx][ny] != '1' && map[nx][ny] != '2'
                                && map[nx][ny] != '3' && map[nx][ny] != '4') {
                                map[playerx[i]][playery[i]] = ' ';
                                playerx[i] = nx;
                                playery[i] = ny;
                                map[playerx[i]][playery[i]] = '1' + i;
                            }
                        }

                        if (randommove_stay <= 1)
                        {
                            int nx = playerx[i];
                            int ny = playery[i];

                            if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                                map[nx][ny] != '1' && map[nx][ny] != '2'
                                && map[nx][ny] != '3' && map[nx][ny] != '4') {
                                map[playerx[i]][playery[i]] = ' ';
                                playerx[i] = nx;
                                playery[i] = ny;
                                map[playerx[i]][playery[i]] = '1' + i;
                            }
                        }

                        if (map[nx] == '1' && map[nx] == '2'
                            && map[nx] == '3' && map[nx] == '4')
                        {
                            int ny = playery[i] - 1;
                        }


                    }

                }

            }



            draw();
            Sleep(300);
            tick += 1000; 

        }




        Sleep(300);
        mu_count++;
    }
    return 0;


}
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


char front_buf;
void gotoxy(int row, int col);
void draw(void);
int map_tick = 0;
int tick = 0;
int move_tick = 0;
char map[100][300], front[100][300];

void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printxy(char ch, int row, int col) {
    gotoxy(row, col);
    printf("%c", ch);
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




int main(void) {
    srand(time(NULL));

    //벽이랑 술래 전환
    while (1) {

        for (int i = 0; i < 11; i++) {
            
            for (int j = 0; j < 45; j++) {
               
                if (i == 0 || i == 10 || j == 0 || j == 44) {
                    map[i][j] = '#';
                    
                }
                else if (i >= 4 && i <= 6  && j <= 1 )
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


        //무궁화 꽃이 피었습니다.
        for (int i = 12; i < 13; i++)
        {
            for (int i = 1; i <= 1; i++)
            {
                printf("\n");
                printf("무궁화꽃이피었습니다");
            }
        }

        //플레이어 상태창 출력

        printf("\n");
        char alive[100], dead[100];
        for (int i = 13; i < 14; i++)
        {
            for (int j = 1; j <= 1; j++)
            {   
                printf("\n");
                printf("no. of players left : 5\n");
                
                    for (int i = 0; i < 5; i++)
                    {
                        printf("%d player : alive\n", i);
                    }

                    printf("%d", map_tick);
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





    }
        return 0;
    

}

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

    //���̶� ���� ��ȯ
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


        //����ȭ ���� �Ǿ����ϴ�.
        for (int i = 12; i < 13; i++)
        {
            for (int i = 1; i <= 1; i++)
            {
                printf("\n");
                printf("����ȭ�����Ǿ����ϴ�");
            }
        }

        //�÷��̾� ����â ���

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




        //�����̴°�
        int dx[4] = { -1, 1, 0, 0 };
        int dy[4] = { 0, 0, -1, 1 };
        int x = 3, y = 42;
        int dir = 3;

        int playerx[4];
        int playery[4];



        //�����ϰ� �����̴� �͵��� ��ġ
        for (int i = 0; i < 4; i++)
        {
            playerx[i] = 4 + i;
            playery[i] = 43;
            map[playerx[i]][playery[i]] = '1' + i;

        }

        //�Է� �޾Ƽ� ������
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




            //�÷��̾� �̵�

            
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
                            // ���� ���� �浹�ϴ� ��� ó��
                            map[playerx[i]][playery[i]] = ' '; // �ش� ���ڸ� ���� ���ڷ� �����Ͽ� ȭ�鿡�� ������� ��
                        }
                        else {
                            map[playerx[i]][playery[i]] = '1' + i; // �� ���� ��쿡�� ���� ���ڸ� ����
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

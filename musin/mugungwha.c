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
char mug_name[] = "����ȭ�����Ǿ����ϴ�";
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
    for (int i = 11; i <= 11; i++) { //���״�� �� 3�� �ݺ��Ǹ� 0.9���� �� 3�� �ݺ��Ǹ� ������ ��µǾ���� 
        for (int j = 0; j <= mu_count; j++) {
            if (front_mu[i] != mug_name[i]) { // ��׵��� ���� ���۸����ν� �� �Ȱɸ����Ϸ��� �����ϴ°�
                front_mu[i] = mug_name[i];// ���� ��ǥ ��¿� ������� ��״� �׳� ����ȭ ���� ������
                gotoxy(i, j);// �̳��� j,i�� ������ִ°��� 
                putchar(front_mu);
            }
        }
    }
}
// ����ȭ �� ���常�� tick �� ���� ���ʰ� ������ ī��Ʈ�ǰ� �� ī��Ʈ �Ȱ� message[i]�� �Է��ϴ°�? ���� tick 1�̸� 
// for(int 1=0;i<=1;i++) �ϰ� 0,1 ���� ��� �ݺ��ϸ� ���� ���ð��ݾ�!!!!!!!!!!!!!1

// ������: ����ȭ�� ������ ��µǴµ��� draw�Լ��� ������ �ȵǼ� �ǽð� ����� �ȵ� ���� �ǽð� �����
//�Ǹ鼭 ����ȭ���� ����� �Ǿ����
// �׷��� �ǽð� ����� �Ǹ鼭 �����ƴ� �ٽ� ��µƴٸ� ���ʰ� ���ӵǰ� �ϰ�
// ��� ����� ������ ���������� 
//���ڰ� ��µ� �� ���� ��µǰ� ���� �ٽ� ����̵� �׸��� 1���� ������ ��µǰ� �ٽ� 1���Ŀ� ����ȭ�� ����̵�
// �̷��� ����� �ϴٺ��� ���������� ����..
// �ƴϸ� ���� �ϳ� ���� ���� �� ��µǸ� ���ڸ� 2�� �÷��� 2�� ����ϰ� �ϴ� ���������( �ѱ��� 2byte)

//0.3�� �϶� 1000, 3���϶� 10000, 9���϶� 30000 , 9.9���϶� 33000

int main(void) {
    srand(time(NULL));
    int mu[] = strlen(mug_name);
    //���̶� ���� ��ȯ
    while (1) {
        if (mu_count >= 30) {// ��ī��Ʈ�� 30�� ������ 30�� �ݺ��� �Ǳ⿡ 0���� �ʱ�ȭ ��Ŵ 
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

        //0.3�� �϶� 1000, 3���϶� 10000, 9���϶� 30000 , 9.9���϶� 33000

        for (int i = 11; i <= 11; i++) { //���״�� �� 3�� �ݺ��Ǹ� 0.9���� �� 3�� �ݺ��Ǹ� ������ ��µǾ���� 
            for (int j = 0; j <= mu_count; j++) {
                gotoxy(i, j);
                putchar(mug_name[i]);
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




        Sleep(300);
        mu_count++;
    }
    return 0;


}
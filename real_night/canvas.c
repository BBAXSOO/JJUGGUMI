#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"
#include <conio.h>
#include <time.h>
#include<string.h>
//char front_buf;
void gotoxy(int row, int col);
void draw(void);
int map_tick = 0;
int tick = 0;
int move_tick = 0;
char map[100][300], front[100][300], front_mu_tick[100]; front_mu[100];


#define ITEM_CHAR 'I'
#define	DATA_FILE	"jjuggumi.dat"
#define _CRT_SECURE_NO_WARNINGS
#define DIALOG_DURATION_SEC		2
#define ROW_MAX 45
#define COL_MAX 11
#define MAX_ITEMS 10
int n_player = 6;

ITEM items[ITEM_MAX];

// 인트로
void intro_JJU(void) {
    printf("; ::::~::~~~~~~:~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~: ~~~~~: ~: ~:::: :\n");
    printf("~,,..................... .......   .. ..   . .. .....  .   . . . ... .  .......................,,,,,\n");
    printf("~,.,............................ . ..  .   . .  . ..    .   . ..... . ...... ...................,-,,\n");
    printf("~,.,.,..............................  . .. . ..    .  ..   ...;*=* ............................-=#$;\n");
    printf("~.....,,,,,,,,,,......... ... .. .... .  .. .    . .      .  .###=..  .........................~###$\n");
    printf("~....~$##########$$$#=. .. . .  ..      .          .  .    . .###=  .. . ............. ........-####\n");
    printf("~....!@@@@@@@@@@@@@@@#.. ..            .      .              .###$.  ......  .. ...............,####\n");
    printf("~....;#@@@@@@@@@@###@$.. . .   . .                  .   ..   .###$....  .  ....................,####\n");
    printf("~....,,-,~!=@@@=**===~  ..    ..           .     .****==$$$$..####.  ..     .. ...,~!$*:... .. ,####\n");
    printf("~....,....,=$##*.....  ..   . .             .    .=*=*$$#$#=..####,. ...  .. ....-===$$#$~.....,####\n");
    printf("~.........:=$##$:. .... .. . ..,,..... ..,,..    .***!**==$$..####,  .   .  . ..~=$$$=*$##:....,####\n");
    printf("~........,$$$=$#*... ..   . .=@####$$$$#####$~   .=*;    ==$. $###,   .   . .  .*===:,:=##$....,####\n");
    printf("~........;$#$=$#$*. ...     ,#@##############=   .**!    *==. =###,      .   ..:===,...,*$$;...,####\n");
    printf(":.......,=$$=~=#$=-. .      .$###############=   .!*!    =$$. =###,    .  .  ..!#=-.....~$#*....####\n");
    printf(":.......*=$$;.;$$$*.. .    . ;$#$$####!;;;$##*   .==!    $$$. =###,  .      . .*$$,.....,##=....$###\n");
    printf(":......-$$$$;!;$#$@:  ...    . .. ;###,  .###*   .$=$=$*$#$=. *###,          ..*=#- ....-$#=....$###\n");
    printf(":......=$#==$$=$###$..    ..      !###,  ,###*   .=$##$$$##$. *###.       ..  .;$#=,.. ,=##;....$###\n");
    printf(":,....~$#$$##=$###$$;.            !###,  -###*   .==$$==*===. *##$.        .  .,$$#=:-:*$==,....$###\n");
    printf(":,....!****=!*=======.. .         !###,  :###*                *##$. .       ....~#$$#$$$$=~....,$#$#\n");
    printf(":,......... ...,,,,,...   .       *###,  :###=                *##$.             .~#$#$$@$:.....,$###\n");
    printf("!@#$$$=$$$$$$$##@@####$,          =###,  :###$            ....-::;...   ...  ...  ,:*=*:,......,$###\n");
    printf("!@@@@@@@@@@@@@@@@@@@@@@~.        .$###-  -****.             ,....  ..... .....  .......,,,,,.,,.:!!!\n");
    printf("!@@@@@@@@@@@@@@@@@@@@@@;           -::,   .,..             ,####$!:::,...::..$=;......$##########$*.\n");
    printf(":!;!~~~;!*=@@@@=!;;;::~.~****!;:~,,,,,,,,-----..           ,########=..$##!.,###-. ...$############.\n");
    printf("~.........-@@@@-. .   . =######################.           ,########,..$##;.,###-.. ..$#####$$#####.\n");
    printf("~.......  ,@@@@-    .  .=######################-           .$#$$####- .$##; ,###,. ...$##:,.,,,~###.\n");
    printf("~.........-@@@@-.  ..   ~###======$####$======!.            ..  ###!. ,###: -###, . ..$##~.....,###.\n");
    printf("~.........,@@@@~. . .  . ....     ;####*                      .-###*!!!###; -###.  . .$##~......$##.\n");
    printf("~..........*$$$-. .    .          ~####=                      .=##########* ~###......$##:......$##.\n");
    printf("~...... ......  ....          .   .####=.                     ,$##########* ~###..  ..$##~.....,$## \n");
    printf("~............. .....  ....         =###=                     .,##*::~~:###* ~###.. ...$$#~......$##.\n");
    printf("~.........................         *###=                    ..-#$.    .###* -###......$##!~~~~--$##.\n");
    printf("-.........  ..,..  .,..  ..,.      ~$##!                    ..##~     ,###* ,###..  ..$############.\n");
    printf("-.........  ..,..  ....  ..,..      .,,                     .,#=.     ,###* ,###......$############.\n");
    printf("~................................                          -.:#:      .###~ ,###,. ...$############.\n");
    printf("~....... ..... .....  ..... .... .   .                    . .$$.       ,,-. .###,.....=#####$$=*$$$.\n");
    printf("~......  ..,.   .,..  ..,.   .,..  . .                    . ~#*..    ..   ..,###, ....-~-,.  .,,..  \n");
    printf("~............. ..... ...... ..... . ..                    ..$#-     ..  . . ,###. ......... ...... .\n");
    printf("~......................................                   .:#*.    . . .... ~###,....... ...........\n");
    printf("-... .....  ..,..  .,,.  ..,.   .,..  ..            .     .:*,   .....  .. .;###,........ .,..  ..,.\n");
    printf("~.........  ..,..  ....  ..,..  ....  ... . . .         . .       . .  .....*#$#,........ ....  ..,.\n");
    printf("~....................................      .     .  .   ..   . ..  . .......*###,...................\n");
    printf("~....... ..... .....  ....  .....  ...   .     ...    .   . ... .. .. ......~*!:..... ..,..  ....  .\n");
    printf("~......  ..,.   .,..  ..,.   .,..  ..   ..       .    .. ..    ......... ............. .,..  ..,.   \n");
    printf(";~~~~~~~~~~~~~~~~~~~::~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:~~~~~~~~~~~~~~~~~\n");
    Sleep(2000);
    system("cls");
}
void intro_op(void) {
    intro_JJU();
    printf("\n");
    printf(" 반갑습니다 ");
    for (int i = 1; i < 6; i++) {
        printf("."); Sleep(200);
    }
    printf(" 밤이 되었습니다!\n");
    Sleep(800);
    printf(" 거~ 운동하기 딱 좋은 날씨네\n");
    for (int i = 1; i < 5; i++) {
        printf(". \n"); Sleep(500);
    }
    printf("\n\n");
    printf("\"(나 너무 무서워... 이러다 다 죽어 ㅠㅠㅠ)\"");
    printf("\n");
    printf("진행시켜!!\n");
    printf("Enter\n");
    getchar();
    
    
    system("cls");
}








void dialog(char message[]) {
    int len = strlen(message);
    gotoxy(3, 7);
    for (int i = 0; i < len + 5; i++) {
        printf("*");
    }
    gotoxy(5, 7);
    for (int i = 0; i < len + 5; i++) {
        printf("*");
    }
    for (int i = 0; i < DIALOG_DURATION_SEC; i++) {
        gotoxy(4, 7);
        printf("*%d ", DIALOG_DURATION_SEC - i);
        for (int j = 0; j < len; j++) {
            printf("%c", message[j]);
        }
        printf(" *");
        Sleep(1000);
    }
    gotoxy(3, 7);
    for (int i = 0; i < len + 5; i++) {
        printf(" ");
    }
    gotoxy(5, 7);
    for (int i = 0; i < len + 5; i++) {
        printf(" ");
    }
    for (int i = 0; i < DIALOG_DURATION_SEC; i++) {
        gotoxy(4, 7);
        printf("  ");
        for (int j = 0; j < len; j++) {
            printf(" ");
        }
        printf("   ");
    }
}








void map_init(int n_row, int n_col) {
    // 두 버퍼를를 완전히 비우기
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            back_buf[i][j] = front_buf[i][j] = ' ';
        }
    }

    N_ROW = n_row;
    N_COL = n_col;
    for (int i = 0; i < N_ROW; i++) {
        for (int j = 0; j < N_COL; j++) {
            if (i == 0 || i == N_ROW - 1 || j == 0 || j == N_COL - 1) {
                back_buf[i][j] = '#';
            }
            else {
                // Randomly place items on the map
                if (rand() % 80 == 0) {
                    back_buf[i][j] = 'I';
                }
                else {
                    back_buf[i][j] = ' ';
                }
            }
        }
    }
}


// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
    if (row < 0 || row >= N_ROW ||
        col < 0 || col >= N_COL ||
        back_buf[row][col] != ' ') {
        return false;
    }
    return true;
}

void printxy(char ch, int row, int col) {
    gotoxy(row, col);
    printf("%c", ch);
}
void gotoxy(int row, int col) {
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool n_player_alive[PLAYER_MAX] = { true, true, true, true, true, true };

void print_status(void) {
    gotoxy(12, 0);
    printf("SURVIVE:%d         intel       str    stamina\n", n_player);
    PLAYER* p_p;
    for (int p = 0; p < n_player; p++) {
        p_p = &player[p];// 각 플레이어에 대한 포인터를 가져오도록 수정
        if (p_p->is_alive == 0) {
            p_p->hasitem = false;
        }


        if ((p_p->is_alive) == 1) {
            printf("player %d: %5s", p, p_p->is_alive ? "alive" : "DEAD");
        }
        else if ((p_p->is_alive) == 0) {
            printf("player %d: %6s", p, "alive*");
            p_p->is_alive = 1;
        }

        if ((p_p->is_alive) == 1) {
            printf("  %2d(+%d)     %2d(+%d)    %3d%%",

                p_p->intel,
                p_p->item.intel_buf,
                p_p->str,
                p_p->item.str_buf,
                p_p->stamina);
        }


        printf("\n");
    }
}




typedef struct {
    int intel_buf;
    int str_buf;
    int stamina_buf;
    char display_char; 
} GAME_ITEM;

GAME_ITEM itemss[ITEM_MAX] = {
    {1, 0, 0, 'P'},
    {4, 0, 0, 'G'},
    {0, 1, 2, 'S'},
    {0, 5, 0, 'B'},

};
void update_front_array(void) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        int row = i + 1;
        int col = 1;

        gotoxy(row, col);

        if (map[row][col] == ITEM_CHAR) {
            if (rand() % 10 == 0) {
               
                int selectedItemIndex = rand() % ITEM_MAX;

               
                for (int p = 0; p < n_player; p++) {
                    if (player[p].is_alive) {
                        player[p].intel += items[selectedItemIndex].intel_buf;
                        player[p].str += items[selectedItemIndex].str_buf;
                        player[p].stamina += items[selectedItemIndex].stamina_buf;
                    }
                }

               
                map[row][col] = ' ';
                break;
            }
        }
    }
}

void draw(void) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 45; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(3, 9);
                printf("I");
                gotoxy(6, 20);
                printf("I");
                gotoxy(7, 40);
                printf("I");
                gotoxy(3, 30);
                printf("I");

                gotoxy(i, j);
                printf("%c", front[i][j]);

                

            }
        }
    }

    update_front_array();
}
void handle_item() {

    dialog("아이템! 1.get 2.pass");
    int choice;
    while (1) {
        int key = _getch();
        if (key == '1') {
            dialog("get!");
            for (int i = 0; i < n_player; i++) {
                player[i].intel += item[i].intel_buf;
                player[i].str += item[i].str_buf;
                player[i].stamina += item[i].stamina_buf;
            }

            
            break;
        }
        else if (key == '2') {
            dialog("pass");

            break;
        }
    }

}

void display(void) {
    
    draw();
    gotoxy(N_ROW + 4, 0);
    print_status();

}



void draw_m(void) {
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 45; col++) {
         
            if (back_buf[row][col] == ITEM_CHAR) {
                printxy(ITEM_CHAR, row, col);
            }
            else if (front_buf[row][col] != back_buf[row][col]) {
               
                front_buf[row][col] = back_buf[row][col];
                printxy(front_buf[row][col], row, col);
            }
        }
    }
}




// 엔딩 
void ending() {
    system("cls");
    printf("                             아침이 밝았습니다.\n ");
    return 0;

}

// 즉시종료 엔딩
void game_q() {
    system("cls");
    for (int row = 0; row <= 0; row++) {
        for (int col = 54; col < 64; col++) {
            gotoxy(row, col);
            printf("#");
        }
    }
    gotoxy(1, 54);
    printf("#");
    gotoxy(1, 55);
    printf("동작그만");
    gotoxy(1, 63);
    printf("#");
    for (int row = 2; row <= 2; row++) {
        for (int col = 54; col < 64; col++) {
            gotoxy(row, col);
            printf("#");
        }
    }
    printf("\n");
    
}













int main(void) {
    //intro_JJU();
    //intro_op();
    jjuggumi_init();
    
    int game_duration = 50000;
    clock_t start_time = clock();
    int playerx[7];
    int playery[7];

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 45; j++)
        {
            if (i == 0 || i == 10 || j == 0 || j == 44)
            {
                gotoxy(i, j);
                printf("%c", '#');
                fflush(stdout);
            }
        }
    }
    draw();




    //움직이는거
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };
    int x = 3, y = 42;
    int dir = 3;


    for (int i = 0; i < 5; i++)
    {
        playerx[i] = rand() % (N_ROW - 2) + 1;
        playery[i] = rand() % (N_COL - 2) + 1;
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
                game_q();
                return 0;
                
            }
        }
        clock_t current_time = clock();
        if ((current_time - start_time) >= game_duration) {
            ending();
            return 0;  // Add this line to exit the loop after calling ending()
        }


        if (move_tick % 10000 == 0)
        {
            if (tick % 50 == 0) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                    if (map[nx][ny] != '1' && map[nx][ny] != '2'
                        && map[nx][ny] != '3' && map[nx][ny] != '4' && map[nx][ny] != '5') {
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


               

                if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                    
                    if (map[nx][ny] >= '1' && map[nx][ny] <= '5') {
                        int playerNumber = map[nx][ny] - '1';
                        handle_encounter(playerNumber);
                    }
                }

                if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44) {
                   
                    for (int i = 1; i < 10; i++) {
                        
                        if ((playerx[i] == 3 && playery[i] == 9) ||
                            (playerx[i] == 6 && playery[i] == 20) ||
                            (playerx[i] == 7 && playery[i] == 40) ||
                            (playerx[i] == 3 && playery[i] == 30)) {

                            
                            handle_item(i);
                            map[nx][ny] = ' ';
                        }
                    }
                }





                for (int i = 0; i < 4; i++) {



                    int randommove_left = rand() % 10 + 1;
                    int randommove_up = rand() % 10 + 1;
                    int randommove_down = rand() % 10 + 1;
                    int randommove_right = rand() % 10 + 1;
                    


                    if (randommove_left <= 2)
                    {
                        int nx = playerx[i];
                        int ny = playery[i] - 1;

                        if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                             map[nx][ny] != '1' && map[nx][ny] != '2'
                            && map[nx][ny] != '3' && map[nx][ny] != '4'
                            && map[nx][ny] != '5') {
                            map[playerx[i]][playery[i]] = ' ';
                            playerx[i] = nx;
                            playery[i] = ny;
                            map[playerx[i]][playery[i]] = '1' + i;
                        }
                    }
                    if (randommove_right <= 5)
                    {
                        int nx = playerx[i];
                        int ny = playery[i] + 1;

                        if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                            map[nx][ny] != '1' && map[nx][ny] != '2'
                            && map[nx][ny] != '3' && map[nx][ny] != '4' && map[nx][ny] != '5') {
                            map[playerx[i]][playery[i]] = ' ';
                            playerx[i] = nx;
                            playery[i] = ny;
                            map[playerx[i]][playery[i]] = '1' + i;
                        }
                    }


                    if (randommove_up <= 2)
                    {
                        int nx = playerx[i] - 1;
                        int ny = playery[i];

                        if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                             map[nx][ny] != '1' && map[nx][ny] != '2'
                            && map[nx][ny] != '3' && map[nx][ny] != '4' && map[nx][ny] != '5') {
                            map[playerx[i]][playery[i]] = ' ';
                            playerx[i] = nx;
                            playery[i] = ny;
                            map[playerx[i]][playery[i]] = '1' + i;
                        }
                    }


                    if (randommove_down <= 2)
                    {
                        int nx = playerx[i] + 1;
                        int ny = playery[i];

                        if (nx >= 1 && nx < 10 && ny >= 1 && ny < 44 &&
                             map[nx][ny] != '1' && map[nx][ny] != '2'
                            && map[nx][ny] != '3' && map[nx][ny] != '4' && map[nx][ny] != '5') {
                            map[playerx[i]][playery[i]] = ' ';
                            playerx[i] = nx;
                            playery[i] = ny;
                            map[playerx[i]][playery[i]] = '1' + i;
                        }
                    }



                }

                for (int i = 0; i < 5; i++) {
                    map[playerx[i]][playery[i]] = '1' + i;
                }



            }

            display();
            Sleep(300);
            tick += 1000;

        }


        
    }
    
   
    return 0;
}

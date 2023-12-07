#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4




void draw(void);
//void print_status(void);
void jul_print_status(void);
void draw_j(void);
void jul_draw(void);
void jul_display(void);

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
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
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
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

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	//print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void draw_m(void){
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 5; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}


//원본
void draw_j(void) {
 
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if (i == 1 && (j == 0 || j == 27)) {
                jul_buffer[i][j] = '#';
            }
            else if (j == 14 || i == 1) {
                jul_buffer[i][j] = ' ';
            }
            else {
                jul_buffer[i][j] = '#';
            }
        }
    }
   
 
   
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            for (int z = 0; z < n_player; z++) {
                PLAYER* p_move = &player[z];
               // i==1 및 j=20 일 때 반복문 아예 종료
                if (i == 1 && j == 20) {
                    j = jul_x + 1; i = jul_y + 1;
                    break;
                }
                else if ((i == 1 && (j >= 9 && j <= 11)) || (i == 1 && (j >= 17 && j <= 19))) {
                    if (z % 2 == 0) { // 짝수 
                        if (j >= 17 && j <= 19) {// 오른쪽 
                             if (p_move->id == 4 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                if (j==19) {
                                    jul_buffer[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 2 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                 if (j==18) {
                                     jul_buffer[i][j] = '0' + p_move->id;
                                     break;
                                 }
                            }
                            else if (p_move->id == 0 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                
                                 if (j == 17) {
                                     jul_buffer[i][j] = '0' + p_move->id;
                                     break;
                                 }
                        }
                            
                        }
                    }
                    else if (z % 2 == 1) { // 홀수 
                        if (j >= 9 && j <= 11) {// 왼쪽
                            if (p_move->id == 5 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                if (j == 11) {
                                    jul_buffer[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 3 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                if (j == 10) {
                                    jul_buffer[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 1 && (jul_buffer[i][j] == ' ' || jul_buffer[i][j] == p_move->id)) {
                                if (j == 9) {
                                    jul_buffer[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                        }
                    }
                }
                else if (i == 1 && (j >= 12 && j <= 16)) {
                    jul_buffer[i][j] = '-';
                    break;
                }
            }
        }
    }
}

    




// 상태창
void jul_print_status(void) {
    printf("no. of players left: %d\n", n_player);
    PLAYER* p_p;
    
    printf("%23s%11s%12s\n","(intel)","(str)", "(stamina)");
    
    for (int p = 0; p < n_player; p++) {
        p_p = &player[p];// 각 플레이어에 대한 포인터를 가져오도록 수정
       
        if (p_p->is_alive == 0) {
            p_p->hasitem = false;
        }
        if ((p_p->is_alive)==1) {
            printf("player %d: %5s", p_p->id, p_p->is_alive ? "alive" : "DEAD"); // 사실 p로 할 수 있는데 그냥 id 정해서 함
        }
        else if ((p_p->is_alive) == 0) {
            p_p->is_alive = 1;
            printf("player %d: %6s", p_p->id, "alive*"); // >>이것도 
        }

        if ((p_p->is_alive)==1) {
            printf("  %2d(+%d)     %2d(+%d)    %3d%%",
               
                p_p->intel,
                p_p->item.intel_buf,  // 어차피 PLAYER 속에 item이 있어서 PLAYER 만 선언하고 뒤에 item.intel_buf
                p_p->str,
                p_p->item.str_buf,
                p_p->stamina);
        }
       
        printf("\n");
    }
}

// 더블 버퍼링 클론
void jul_buf(char jul_buffer_clon[][jul_x]) {
   
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            if (i == 1 && (j == 0 || j == 27)) {
                jul_buffer_clon[i][j] = '#';
            }
            else if (j == 14 || i == 1) {
                jul_buffer_clon[i][j] = ' ';
            }
            else {
                jul_buffer_clon[i][j] = '#';
            }
        }
    }
    for (int i = 0; i < jul_y; i++) {
        for (int j = 0; j < jul_x; j++) {
            for (int z = 0; z < n_player; z++) {
                PLAYER* p_move = &player[z];
                if (i == 1 && j == 20) {
                    j = jul_x + 1; i = jul_y + 1;
                    break;
                }
                else if ((i == 1 && (j >= 9 && j <= 11)) || (i == 1 && (j >= 17 && j <= 19))) {
                    if (z % 2 == 0) { // 짝수 
                        if (j >= 17 && j <= 19) {// 오른쪽 
                            if (p_move->id == 4 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 19) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 2 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 18) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 0 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 17) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }

                        }
                    }
                    else if (z % 2 == 1) { // 홀수 
                        if (j >= 9 && j <= 11) {// 왼쪽
                            if (p_move->id == 5 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 11) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 3 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 10) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                            else if (p_move->id == 1 && (jul_buffer_clon[i][j] == ' ' || jul_buffer_clon[i][j] == p_move->id)) {
                                if (j == 9) {
                                    jul_buffer_clon[i][j] = '0' + p_move->id;
                                    break;
                                }
                            }
                        }
                    }
                }
                else if (i == 1 && (j >= 12 && j <= 16)) {
                    jul_buffer_clon[i][j] = '-';
                    break;
                }
            }
        }
    }
    
}

void jul_but_init(void) {
    //원본
    draw_j();
    // 줄다리기 맵 원본 그리는건 아님 저장해두는거임 
    // 클론
    jul_buf(jul_buffer_clon);
    
   

}



void jul_display(void) {

    
    jul_print_status();
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
    printf(" 참가자 여러분들!\n");
    Sleep(800);
    printf(" 게임에서 승리하시고 상금 차지하세요!!!\n");
    for (int i = 1; i < 5; i++) {
        printf(". \n"); Sleep(500);
    }
    printf("\n\n");
    printf("\"엔터를 누르시면 게임이 시작됩니다\"");
    printf("\n");

    char get = getchar();
    get = getchar();
    system("cls");


}


// 엔딩 
void ending() {
    printf("                      제한시간 초과로 인해  \"무궁화 꽃이 피었습니다.\"는 끝났습니다!\n ");
    printf("                     게임을 이긴 참가자분들은 다음 게임으로 속히 이동해 주시길 바라겠습니다.");

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
    printf("스탑!");
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


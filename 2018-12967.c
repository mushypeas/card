#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#define down  258
#define up    259
#define left  260
#define right 261

int key_in;

typedef struct{
	char name;
	int status;         // 0: Hidden 1: Shown -1: Removed
}card;

typedef struct{
	char name;
	int num;
}pick;

card cards[4][4];		// Cards
int on[2] = {0,0};      // The card the player is on
int menu = 0;           // 0: game start 1: exit
int status = 0;         // 0: menu 1: game
int end = 0;

void initialize();
void display(int s);
void display_menu();
void display_gameboard();
int box_char(int x);
void card_box();

int main() {	
	srand(time(NULL));
	initialize();
    start_color();
    init_color(8, 999, 999, 999);
    init_pair(1, COLOR_BLACK, 8);
	while(1) {
		end = 1;
		display(status);
		int flip_count=0;
		char flip_name[2] = {'\0', '\0'};
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++){
				if(cards[i][j].status == 1)
					flip_name[flip_count++] = cards[i][j].name;
				else if(cards[i][j].status != -1)
					end = 0;
			}
		if(flip_count == 2){
			if(flip_name[0] == flip_name[1]){
				sleep(1);
				for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						if(cards[i][j].status == 1)
							cards[i][j].status = -1;
			}
			else{
				sleep(1);
				for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						if(cards[i][j].status == 1)
							cards[i][j].status = 0;
			}
		}
		if(end){
			move(LINES/2,COLS/2);
			system("clear");
			printw("YOU'RE WINNER\n");
			scanf("%[\n]", &menu);
			status = 0;
		}
		display(status);
		key_in = getch();
		if(status){     //If in game
			if(key_in == up){
				if(on[0] == 0)
					on[0] = 3;
				else
					on[0] -= 1;
			}
			else if(key_in == down){
				if(on[0] == 3)
					on[0] = 0;
				else
					on[0] += 1;
			}
			else if(key_in == left){
				if(on[1] == 0)
					on[1] = 3;
				else
					on[1] -= 1;
			}
			else if(key_in == right){
				if(on[1] == 3)
					on[1] = 0;
				else
					on[1] += 1;
			}
			else if(key_in == 'Q' || key_in == 'q')
				status = 0;
			else if(key_in == ' ')
				if(cards[on[0]][on[1]].status == 0)
					cards[on[0]][on[1]].status = 1;
		}
		else{          //If in menu
			if(key_in == up)
				menu=0;
			else if(key_in == down)
				menu=1;
			else if(key_in == ' '){
				if(menu)
					break;
				else{
					initialize();
					status = 1;
				}
			}
		}
	}

	endwin();	// Do NOT modify
	return 0;
}

void initialize() {
	initscr();				// Initialize NCURSES library
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	pick list[8];
	for(int i=0; i<8; i++){
		list[i].num = 2;
		list[i].name = 'A' + i;
	}
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++){
			cards[i][j].name = '\0';
			cards[i][j].status = 0;
			while(cards[i][j].name == '\0'){
				int mere = rand()%8;
				if(list[mere].num > 0){
					cards[i][j].name = list[mere].name;
					list[mere].num--;
				}
			}
		}
	display(status);
}

void display(int s) {
	clear();
	if(s)
		display_gameboard();
	else
		display_menu();
	refresh();
}
void display_menu(){
    mvprintw(0,0,"*Monospaced font recommended");
    int y = LINES/2 - 2, x = COLS/2-1;
    move(y-4, x-3);
    printw("Card Match");
    move(y-2, x);
    printw("MENU");
    x = COLS/2 - 10;
    move(y, x);
    if(menu){
		addch(box_char(7)),printw("                    "),addch(box_char(9)), move(y+1,x);
		addch(box_char(11)),printw("     GAME START     "),addch(box_char(11)), move(y+2,x);
		addch(box_char(1)),printw("                    "),addch(box_char(3)), move(y+3,x);
		addch(box_char(7)),printw("                    "),addch(box_char(9)), move(y+4,x);
		addch(box_char(11)),attron(COLOR_PAIR(1)),printw(" -      QUIT      - "),attroff(COLOR_PAIR(1)),addch(box_char(11)), move(y+5,x);
		addch(box_char(1)),printw("                    "),addch(box_char(3));
	}
    else{
		addch(box_char(7)),printw("                    "),addch(box_char(9)), move(y+1,x);
		addch(box_char(11)),attron(COLOR_PAIR(1)),printw(" -   GAME START   - "),attroff(COLOR_PAIR(1)),addch(box_char(11)), move(y+2,x);
		addch(box_char(1)),printw("                    "),addch(box_char(3)), move(y+3,x);
		addch(box_char(7)),printw("                    "),addch(box_char(9)), move(y+4,x);
		addch(box_char(11)),printw("        QUIT        "),addch(box_char(11)), move(y+5,x);
		addch(box_char(1)),printw("                    "),addch(box_char(3));
	}
	return;
}
void card_box(card cards,int y,int x){
	if(cards.status == 1){
		addch(box_char(7)),addch(box_char(10)),addch(box_char(10)),addch(box_char(10)),addch(box_char(9)), move(y+1,x);
		addch(box_char(11)),printw(" %c ", cards.name),addch(box_char(11)), move(y+2,x);
		addch(box_char(1)),addch(box_char(10)),addch(box_char(10)),addch(box_char(10)),addch(box_char(3));
	}
	else if(cards.status == 0){
		addch(box_char(7)),addch(box_char(10)),addch(box_char(10)),addch(box_char(10)),addch(box_char(9)), move(y+1,x);
		addch(box_char(11)),printw("   "),addch(box_char(11)), move(y+2,x);
		addch(box_char(1)),addch(box_char(10)),addch(box_char(10)),addch(box_char(10)),addch(box_char(3));
	}
	else{
		printw("     "), move(y+1,x);
		printw("     "), move(y+2,x);
		printw("     ");
	}
	return;
}
void display_gameboard() {
    mvprintw(0,0,"*Monospaced font recommended");
	for(int i=0;i<4;i++)
		for(int j=0; j<4; j++){
            int y=LINES/2+(i-2)*3, x=COLS/2+(j-2)*5;
			move(y,x);
			if(on[0] == i && on[1] == j){
			    attron(COLOR_PAIR(1));
			    card_box(cards[i][j],y,x);
			    attroff(COLOR_PAIR(1));
			}
			else{
				card_box(cards[i][j],y,x);
			}
		}
}
// If you don't need this function, you can delete it. Also you can modify it as you want.
int box_char(int x) {
	switch(x) {
		case 1: return ACS_LLCORNER;
		case 2: return ACS_BTEE;
		case 3: return ACS_LRCORNER;
		case 4: return ACS_LTEE;
		case 5: return ACS_PLUS;
		case 6: return ACS_RTEE;
		case 7: return ACS_ULCORNER;
		case 8: return ACS_TTEE;
		case 9: return ACS_URCORNER;
		case 10: return ACS_HLINE;		// Horizontal Line	'-'
		case 11: return ACS_VLINE;		// Vertical Line	'|'
	}
	return 0;
}

// You will draw a lot of boxes during this project.
// To make it easier, we recommend you to implement draw_box function.
// Arguments are just example. You can change it as you want.
// 		Example)
// 		lines and cols can be a coordinate of upper-left-corner
//		height and width indicates box size

#include <ncurses.h>

int key_in;

char cards[4][4];		// Cards

void initialize();
void display();
void display_gameboard();
int box_char(int x);
void draw_box(int line, int col, int height, int width);

int main() {	

	initialize();

	while(1) {
		key_in = getch();

		// TODO
		// Input processing. When 'q' or 'Q' are pressed, break this while loop.
		// Initialize 16 cards A, B, C, ..., P

		display();
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

	display();
}

void display() {
	clear();
	display_gameboard();
	refresh();
}

void display_gameboard() {
	/* TODO */
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
void draw_box(int lines, int cols, int height, int width) {
	/* TODO */
}

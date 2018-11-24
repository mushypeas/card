#include <ncurses.h>

void initialize() {
	initscr();			// Initialize NCURSES screen. This line is necessary. Do NOT delete.

	// We'll use following functions for initial setting.
	// Delete some of following lines and check the difference.
	// You can simply put // in front of each line to make it as comment.

	raw();							// Get raw keyboard input. Keyboard input goes directly into this program.
	keypad(stdscr, TRUE);			// Use extended keyboard input. It allows us to use arrow keys such as KEY_UP, KEY_DOWN, ...
	curs_set(0);					// Hide cursor. If you don't use this function, (or change its argument as 1) cursor will appears on screen at the end of last print line.
	noecho();						// In default, your keyboard input appears on screen. This line hide that input.
}

int main() {	
	initialize();

	int key_in;			// Notice that key_in is integer type variable.

	while(1) {
		
		key_in = getch();		// Get Keyboard Input

		if (key_in == 'q' || key_in == 'Q') break;		// To terminate your program, press 'q'

		clear();										// Delete all previous screen data.
		mvprintw(LINES/2, COLS/2, "%c %d", key_in, key_in);		// Print data on internal screen.

		// You can put more print lines (addch, mvaddch, printw, mvprintw) here

		refresh();										// Show internal screen to terminal.
	}

	endwin();			// Close NCURSES scren. This line is necessary. Do NOT delete.
	return 0;
}

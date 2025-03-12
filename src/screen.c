#include <stdlib.h>

////////////////////////
// TERMINAL
////////////////////////

void terminal_size(int* w, int* h){
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	*w = win.ws_col - 1;
	*h = win.ws_row - 1;
}

////////////////////////
// SCREEN
////////////////////////

Screen new_screen(){
	Screen screen;
	terminal_size(&screen.w, &screen.h);
	fill_screen(&screen, ' ');
	return screen;
}

void render_screen(Screen *screen){
}

void write_screen(Screen *screen, char* str){
}

void fill_screen(Screen *screen, char c){
}

void destroy_screen(Screen *screen){}

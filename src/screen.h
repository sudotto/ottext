#ifndef SCREEN
#define SCREEN

#include <stdlib.h>

////////////////////////
// TERMINAL
////////////////////////

void terminal_size(int* w, int* h);

////////////////////////
// SCREEN
////////////////////////

typedef struct {
	char chars[200][200];
	int w;
	int h;
	int cursor_x;
	int cursor_y;
} Screen;

Screen new_screen();
void newline_screen(Screen* screen);
void write_char_screen(Screen* screen, char c);
void write_screen(Screen *screen, char* str);
void fill_screen(Screen *screen, char c);
void render_screen(Screen *screen);

#endif

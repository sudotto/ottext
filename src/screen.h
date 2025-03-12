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
	char[200][200];
	int w;
	int h;
} Screen;

Screen new_screen();
void render_screen(Screen *screen);
void write_screen(Screen *screen, char* str);
void fill_screen(Screen *screen, char c);
void destroy_screen(Screen *screen);

#endif

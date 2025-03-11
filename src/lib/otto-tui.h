// otto-tui by sudotto

#ifndef CANVAS_H
#define CANVAS_H

#include <stdlib.h>
#include <stdbool.h>

///////////////////
// COLORS
///////////////////

#define FG_BLACK  "\e[30m"
#define FG_RED    "\e[31m"
#define FG_GREEN  "\e[32m"
#define FG_YELLOW "\e[33m"
#define FG_BLUE   "\e[34m"
#define FG_PURPLE "\e[35m"
#define FG_CYAN   "\e[36m"
#define FG_WHITE  "\e[37m"

#define BG_BLACK  "\e[40m"
#define BG_RED    "\e[41m"
#define BG_GREEN  "\e[42m"
#define BG_YELLOW "\e[43m"
#define BG_BLUE   "\e[44m"
#define BG_PURPLE "\e[45m"
#define BG_CYAN   "\e[46m"
#define BG_WHITE  "\e[47m"

///////////////////
// TERMINAL INFO
///////////////////

void get_terminal_size(int* w, int* h);

///////////////////
// GLYPH STRUCTURE
///////////////////

typedef struct {
	char ch;
	char* fg;
	char* bg;
	bool invert;
} Glyph;

Glyph new_glyph(char ch, char* fg, char* bg, bool invert);
Glyph* new_glyph_string(char* str, char* fg, char* bg, bool invert);
void render_glyph(Glyph* glyph, int x, int y);

///////////////////
// CANVAS STRUCTURE
///////////////////

typedef struct {
	Glyph glyphs[300][300];
	int w;
	int h;
} Canvas;

Canvas new_canvas();
void print_char_canvas(Canvas* canvas, Glyph glyph, int x, int y);
void print_string_canvas(Canvas* canvas, Glyph* glyph_string, int x, int y);
void fill_canvas(Canvas* canvas, Glyph glyph);
void render_canvas(Canvas* canvas);

///////////////////
// EZ-INPUT
///////////////////

typedef struct {
	char* key;
	char* string;
	int* number;
} Ezi;

Ezi new_ezi();
void get_keypress_ezi(Ezi *ezi);
void get_string_ezi(Ezi *ezi);
void get_number_ezi(Ezi *ezi);

///////////////////
// SIMPLE AUDIO
///////////////////

void play_bell();

#endif

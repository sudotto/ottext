//  ####  ###### ######  ####        ###### ## ## ######
// ##  ##   ##     ##   ##  ##         ##   ## ##   ##
// ##  ##   ##     ##   ##  ## ######  ##   ## ##   ##
// ##  ##   ##     ##   ##  ##         ##   ## ##   ##
//  ####    ##     ##    ####          ##    ###  ######
// otto-tui by sudotto

#ifndef CANVAS_H
#define CANVAS_H

#include <stdlib.h>
#include <stdbool.h>

///////////////////
// TERMINAL INFO
///////////////////

void get_terminal_size(int* w, int* h);

///////////////////
// GLYPH STRUCTURE
///////////////////

typedef struct {
	char ch;
	bool invert;
} Glyph;

Glyph new_glyph(char ch, bool invert);

///////////////////
// CANVAS STRUCTURE
///////////////////

typedef struct {
	Glyph glyphs[500][500];
	int w;
	int h;
} Canvas;

Canvas new_canvas();
void print_char_canvas(Canvas* canvas, char ch, bool invert, int x, int y);
void print_string_canvas(Canvas* canvas, char* string, bool invert, int x, int y);
void fill_line_canvas(Canvas* canvas, char ch, bool invert, int line);
void fill_canvas(Canvas* canvas, char ch, bool invert);
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

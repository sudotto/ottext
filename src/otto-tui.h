#ifndef CANVAS_H
#define CANVAS_H

#include <stdlib.h>
#include <stdbool.h>

///////////////////
// TERMINAL INFO
///////////////////

void get_term_size(int* w, int* h);

///////////////////
// GLYPH STRUCTURE
///////////////////

typedef struct {
	char c;
	bool inv;
} glyph;

glyph create_glyph(char c, bool inv);

///////////////////
// CANVAS STRUCTURE
///////////////////

typedef struct {
	glyph glyphs[500][500];
	int w;
	int h;
} canvas;

canvas create_canvas();
void write_canvas(canvas* canv, char c, bool inv, int x, int y);
void fill_line(canvas* canv, char c, bool inv, int line);
void fill_canvas(canvas* canv, char c, bool inv);
void print_canvas(canvas* canv, char* str, bool inv, int x, int y);
void render_canvas(canvas* canv);

///////////////////
// EZ-INPUT
///////////////////

typedef struct {
	char* key;
	char* string;
	int* number;
} ezi;

ezi create_ezi();
void destroy_ezi(ezi *e);
void ezi_keypress(ezi *e);
void ezi_string(ezi *e);
void ezi_number(ezi *e);

#endif

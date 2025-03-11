// otto-tui by sudotto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "otto_canvas.h"

///////////////////
// TERMINAL INFO
///////////////////

void get_terminal_size(int* w, int* h){
	struct winsize t;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &t);
	*w = t.ws_col;
	*h = t.ws_row;
}

///////////////////
// GLYPH STRUCTURE
///////////////////

Glyph new_glyph(char ch, char* fg, char* bg, bool invert){
	Glyph glyph;
	glyph.ch = ch;
	glyph.fg = fg;
	glyph.bg = bg;
	glyph.invert = invert;
	return glyph;
}

Glyph* new_glyph_string(char* string, char* fg, char* bg, bool invert){
	Glyph* glyphs = malloc(100*sizeof(Glyph));
	for(int i = 0; i < strlen(string); i++){
		glyphs[i].ch = string[i];
		glyphs[i].fg = fg;
		glyphs[i].bg = bg;
		glyphs[i].invert = invert;
	}
	return glyphs;
}

void render_glyph(Glyph* glyph, int x, int y){
	if(glyph->invert){
		write(1, "\e[7m", 5);
	}
	write(1, glyph->fg, 6);
	write(1, glyph->bg, 6);
	switch(glyph->ch){
		case '\n':
			write(1, " ", 1);
			break;
		default:
			write(1, &glyph->ch, 1);
			break;
	}
	write(1, "\e[0m", 5);
}

///////////////////
// CANVAS STRUCTURE
///////////////////

Canvas new_canvas(){
	Canvas canvas;
	int w, h;
	get_terminal_size(&w, &h);
	canvas.w = w - 4;
	canvas.h = h - 3;
	for(int y = 0; y <= h; y++){
		for(int x = 0; x <= w; x++){
			canvas.glyphs[y][x] = new_glyph(' ', FG_WHITE, BG_BLACK, false);
		}
	}
	return canvas;
}

void print_char_canvas(Canvas *canvas, Glyph glyph, int x, int y){
	if(x >= 0 && x <= canvas->w && y >= 0 && y <= canvas->h){
		canvas->glyphs[y][x] = glyph;
	}
}

void print_string_canvas(Canvas* canvas, Glyph* glyphs, int x, int y){
	for(int i = 0; i < 100; i++){
		if(!glyphs[i].ch){
			break;
		}
		print_char_canvas(canvas, glyphs[i], x, y);
		x++;
	}
}

void fill_line_canvas(Canvas *canvas, Glyph glyph, int line){
	for(int x = 0; x <= canvas->w; x++){
		print_char_canvas(canvas, glyph, x, line);
	}
}

void fill_canvas(Canvas* canvas, Glyph glyph){
	for(int y = 0; y <= canvas->h; y++){
		fill_line_canvas(canvas, glyph, y);
	}
}

void render_canvas(Canvas* canvas){
	for(int y = 0; y <= canvas->h; y++){
		for(int x = 0; x <= canvas->w; x++){
			render_glyph(&canvas->glyphs[y][x], x, y);
		}
		write(1, "\n", 2); // 2 maybe needs to turn into one idk
	}
}

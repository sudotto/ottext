// otto-tui by sudotto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "otto-tui.h"

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

///////////////////
// EZ-INPUT
///////////////////

Ezi new_ezi(){
	Ezi ezi;
	ezi.key = malloc(20*sizeof(char));
	ezi.string = malloc(100*sizeof(char));
	return ezi;
}

void destroy_ezi(Ezi* ezi){
	free(ezi->key);
	free(ezi->string);
}

void get_keypress_ezi(Ezi* ezi){
	char seq[3];

	// get stdin data

	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

	int seq_count = read(STDIN_FILENO, seq, 3);

	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

	// parse stdin data

	if(seq[0] > 126 || seq[0] < 33){
		switch(seq[0]){
			case 127:
				strcpy(ezi->key, "backspace");
				break;
			case 9:
				strcpy(ezi->key, "tab");
				break;
			case 10:
				strcpy(ezi->key, "return");
				break;
			case 27:
				strcpy(ezi->key, "escape");
				switch(seq[1]){
					case '[':
						switch(seq[2]){
							case 'A':
								strcpy(ezi->key, "up");
								break;
							case 'B':
								strcpy(ezi->key, "down");
								break;
							case 'C':
								strcpy(ezi->key, "right");
								break;
							case 'D':
								strcpy(ezi->key, "left");
								break;
						break;
					case '~':
						strcpy(ezi->key, "delete");
						break;
					}
				}
				break;
		}
	} else {
		ezi->key[0] = seq[0];
		ezi->key[1] = '\0';
	}
}

void get_string_ezi(Ezi *ezi){
	scanf("%100s", ezi->string);
}

void get_number_ezi(Ezi *ezi){
	scanf("%i", ezi->number);
}

///////////////////
// SIMPLE AUDIO
///////////////////

void play_bell(){
	printf("\a");
}

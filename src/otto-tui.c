//  ####  ###### ######  ####        ###### ## ## ######
// ##  ##   ##     ##   ##  ##         ##   ## ##   ##
// ##  ##   ##     ##   ##  ## ######  ##   ## ##   ##
// ##  ##   ##     ##   ##  ##         ##   ## ##   ##
//  ####    ##     ##    ####          ##    ###  ######
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

Glyph new_glyph(char ch, bool invert){
	Glyph glyph;
	switch(ch){
		case '\n':                                         // NEWLINE
			glyph.ch = ' ';
			break;
		case 9:                                            // TAB
			glyph.ch = ' ';
			break;
		default:                                           // any other character
			glyph.ch = ch;
			break;
	}
	glyph.invert = invert;
	return glyph;
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
			canvas.glyphs[y][x] = new_glyph(' ', false);
		}
	}
	return canvas;
}

void print_char_canvas(Canvas *canvas, char ch, bool invert, int x, int y){
	if(x >= 0 && x <= canvas->w && y >= 0 && y <= canvas->h){
		canvas->glyphs[y][x] = new_glyph(ch, invert);
	}
}

void print_string_canvas(Canvas* canvas, char* string, bool invert, int x, int y){
	for(int i = 0; i < strlen(string); i++){
		print_char_canvas(canvas, string[i], invert, x, y);
		x++;
	}
}

void fill_line_canvas(Canvas *canvas, char ch, bool invert, int line){
	for(int x = 0; x <= canvas->w; x++){
		print_char_canvas(canvas, ch, invert, x, line);
	}
}

void fill_canvas(Canvas* canvas, char ch, bool invert){
	for(int y = 0; y <= canvas->h; y++){
		fill_line_canvas(canvas, ch, invert, y);
	}
}

void render_canvas(Canvas* canvas){
	for(int y = 0; y <= canvas->h; y++){
		for(int x = 0; x <= canvas->w; x++){
			if(canvas->glyphs[y][x].invert){
				printf("\033[7m");
			}
			printf("%c", canvas->glyphs[y][x].ch);
			printf("\033[0m");
		}
		printf("\n");
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
		*ezi->key = seq[0];
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

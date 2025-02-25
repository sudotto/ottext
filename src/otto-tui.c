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

void get_term_size(int* w, int* h){
	struct winsize t;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &t);
	*w = t.ws_col;
	*h = t.ws_row;
}

///////////////////
// GLYPH STRUCTURE
///////////////////

glyph create_glyph(char c, bool inv){
	glyph inst;
	switch(c){
		case '\n':                                         // NEWLINE
			inst.c = ' ';
			break;
		case 9:                                            // TAB
			inst.c = ' ';
			break;
		default:                                           // any other character
			inst.c = c;
			break;
	}
	inst.inv = inv;
	return inst;
}

///////////////////
// CANVAS STRUCTURE
///////////////////

canvas create_canvas(){
	canvas inst;
	int w, h;
	get_term_size(&w, &h);
	inst.w = w - 4;
	inst.h = h - 3;
	for(int y = 0; y <= h; y++){
		for(int x = 0; x <= w; x++){
			inst.glyphs[y][x] = create_glyph(' ', false);
		}
	}
	return inst;
}

void write_canvas(canvas* canv, char c, bool inv, int x, int y){
	if(x >= 0 && x <= canv->w && y >= 0 && y <= canv->h){
		canv->glyphs[y][x] = create_glyph(c, inv);
	}
}

void fill_line(canvas* canv, char c, bool inv, int line){
	for(int x = 0; x <= canv->w; x++){
		write_canvas(canv, c, inv, x, line);
	}
}

void fill_canvas(canvas* canv, char c, bool inv){
	for(int y = 0; y <= canv->h; y++){
		fill_line(canv, c, inv, y);
	}
}

void print_canvas(canvas* canv, char* str, bool inv, int x, int y){
	for(int i = 0; i < strlen(str); i++){
		write_canvas(canv, str[i], inv, x, y);
		x++;
	}
}

void render_canvas(canvas* canv){
	for(int y = 0; y <= canv->h; y++){
		for(int x = 0; x <= canv->w; x++){
			if(canv->glyphs[y][x].inv){
				printf("\033[7m");
			}
			printf("%c", canv->glyphs[y][x].c);
			printf("\033[0m");
		}
		printf("\n");
	}
}

///////////////////
// EZ-INPUT
///////////////////

ezi create_ezi(){
	ezi e;
	e.key = malloc(5*sizeof(char));
	e.string = malloc(50*sizeof(char));
	return e;
}

void destroy_ezi(ezi *e){
	free(e->key);
	free(e->string);
}

void ezi_keypress(ezi* e){
	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	e->key = malloc(5*sizeof(char));
	char seq[3];
	int seq_count = read(STDIN_FILENO, seq, 3);
	*e->key = seq[0];
	if(*e->key > 126 || *e->key < 33){
		switch(*e->key){
			case 127:
				e->key = "backspace";
				break;
			case 9:
				e->key = "tab";
				break;
			case 10:
				e->key = "return";
				break;
			case 27:
				e->key = "escape";
				switch(seq[1]){
					case '[':
						switch(seq[2]){
							case 'A':
								e->key = "up";
								break;
							case 'B':
								e->key = "down";
								break;
							case 'C':
								e->key = "right";
								break;
							case 'D':
								e->key = "left";
								break;
						break;
					case '~':
						e->key = "delete";
						break;
					}
				}
				break;
			default:
				printf("%i", *e->key);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

void ezi_string(ezi *e){

}

void ezi_number(ezi *e){

}

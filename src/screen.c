#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h> 
#include <termios.h>

#include "screen.h"

////////////////////////
// TERMINAL
////////////////////////

void terminal_size(int* w, int* h){
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	*w = win.ws_col - 5;
	*h = win.ws_row - 5;
}

////////////////////////
// SCREEN
////////////////////////

Screen new_screen(){
	Screen screen;
	terminal_size(&screen.w, &screen.h);
	screen.cursor_x = 0;
	screen.cursor_y = 0;
	fill_screen(&screen, ' ');
	return screen;
}

void cursor_home(){
	
}

void cursor_newline(Screen* screen){
	if(screen->cursor_y > screen->h){
		screen->cursor_x = 0;
		screen->cursor_y = 0;
	}
}

void move_cursor_screen(Screen* screen, int dx, int dy){
	if(screen->cursor_x > screen->w){
		screen->cursor_x = 0;
		screen->cursor_y += 1;
	}
	if(screen->cursor_y > screen->h){
		screen->cursor_x = 0;
		screen->cursor_y = 0;
	}
	if(screen->cursor_x < 0){
		screen->cursor_x = 0;
		screen->cursor_y -= 1;
	}
	if(screen->cursor_y < 0){
		screen->cursor_x = 0;
		screen->cursor_y = 0;
	}
}

void write_char_screen(Screen* screen, char c){
	switch(c){
		case '\n':
			
			break;
		case '\b':
			screen->cursor_x -= 1;
			screen->chars[screen->cursor_y][screen->cursor_x] = ' ';
			break;
		default:
			screen->chars[screen->cursor_y][screen->cursor_x] = c;
			screen->cursor_x += 1;
			break;
	}
}

void write_screen(Screen *screen, char* str){
	for(int i = 0; i < strlen(str); i++){
		write_char_screen(screen, str[i]);
	}
}

void fill_screen(Screen *screen, char c){
	terminal_size(&screen->w, &screen->h);
	for(int y = 0; y <= screen->h; y++){
		for(int x = 0; x <= screen->w; x++){
			write_char_screen(screen, c);
		}
	}
	screen->cursor_x = 0;
	screen->cursor_y = 0;
}

void render_screen(Screen *screen){
	system("clear");
	for(int y = 0; y <= screen->h; y++){
		for(int x = 0; x <= screen->w; x++){
			putchar(screen->chars[y][x]);
		}
		putchar('\n');
	}
}

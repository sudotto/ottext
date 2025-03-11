// otto-tui by sudotto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "otto_ezi.h"

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

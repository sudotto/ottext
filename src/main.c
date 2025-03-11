#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lib/otto_canvas.h"
#include "lib/otto_ezi.h"
#include "lib/otto_sound.h"

int main(){
	bool run = true;
	Canvas canvas = new_canvas();
	Ezi ezi = new_ezi();
	while(run){
		play_bell();
		fill_canvas(&canvas, new_glyph(' ', FG_WHITE, BG_BLACK, false));
		system("clear");
		char* lines[20] = {
			"    ####  ###### ######  ####        ###### ## ## ###### ",
			"   ##  ##   ##     ##   ##  ##         ##   ## ##   ##   ",
			"   ##  ##   ##     ##   ##  ## ######  ##   ## ##   ##   ",
			"   ##  ##   ##     ##   ##  ##         ##   ## ##   ##   ",
			"    ####    ##     ##    ####          ##    ###  ###### ",
			"",
			"<this is a demo of otto-tui by sudotto>",
			" - (to exit press \"esc\")",
			" - (for documentation please read the README file)",
			" - (if you are using this library please read the license)",
			" - (thank you for using otto-tui)",
			"",
		};
		for(int i = 0; i < 20; i++){
			if(lines[i]){
				print_string_canvas(&canvas, new_glyph_string(lines[i], FG_WHITE, BG_BLACK, false), 0, i);
			}
			if(i == 12){
				char u_pressed_msg[50] = "you pressed: ";
				char* t = "test";
				strcat(u_pressed_msg, ezi.key);
				print_string_canvas(&canvas, new_glyph_string(u_pressed_msg, FG_WHITE, BG_BLACK, false), 0, 12);
			}
		}
		render_canvas(&canvas);
		get_keypress_ezi(&ezi);
		if(!strcmp(ezi.key, "escape")){
			run = false;
		}
	}
}

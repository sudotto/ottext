#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "otto-tui.h"

int main(){
	bool run = true;
	Canvas canvas = new_canvas();
	Ezi ezi = new_ezi();
	while(run){
		//system("clear");
		char* lines[20] = {
			"    ####  ###### ######  ####        ###### ## ## ###### ",
			"   ##  ##   ##     ##   ##  ##         ##   ## ##   ##   ",
			"   ##  ##   ##     ##   ##  ## ######  ##   ## ##   ##   ",
			"   ##  ##   ##     ##   ##  ##         ##   ## ##   ##   ",
			"    ####    ##     ##    ####          ##    ###  ###### ",
			"",
			"<this is a demo of otto-tui by sudotto>",
			" - (to exit press \"q\")",
			" - (for documentation please read the README file)",
			" - (if you are using this library please read the license)",
			" - (thank you for using otto-tui)",
			"",
		};
		for(int i = 0; i < 20; i++){
			if(lines[i]){
				print_string_canvas(&canvas, lines[i], false, 0, i);
			}
			if(i == 12){
				char u_pressed_msg[50] = "you pressed: ";
				char* t = "test";
				strcat(u_pressed_msg, ezi.key);
				print_string_canvas(&canvas, u_pressed_msg, false, 0, 12);
			}
		}
		render_canvas(&canvas);
		get_keypress_ezi(&ezi);
	}
}

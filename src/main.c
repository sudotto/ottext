#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

int main(){
	bool run = true;
	Screen screen = new_screen();
	while(run){
		fill_screen(&screen, ' ');
		write_screen(&screen, "");
		render_screen(&screen);
		getchar();
	}
}

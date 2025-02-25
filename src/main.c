#include "otto-tui.h"
#include <stdio.h>
#include <stdbool.h>

int main(){
	bool run = true;
	ezi e;
	while(run){
		ezi_keypress(&e);
		printf("%s\n", e.key);
	}
	destroy_ezi(&e);
}

// otto-tui by sudotto

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "otto_sound.h"

///////////////////
// SIMPLE AUDIO
///////////////////

void play_bell(){
	printf("\a");
}


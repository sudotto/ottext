// otto-tui by sudotto

#ifndef EZI
#define EZI

#include <stdlib.h>
#include <stdbool.h>

///////////////////
// EZ-INPUT
///////////////////

typedef struct {
	char* key;
	char* string;
	int* number;
} Ezi;

Ezi new_ezi();
void get_keypress_ezi(Ezi *ezi);
void get_string_ezi(Ezi *ezi);
void get_number_ezi(Ezi *ezi);

#endif

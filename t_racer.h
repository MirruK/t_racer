#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>

/* game.c declarations */
void disable_raw_mode(void);
void take_char(char*, int*);
int validate(char*, int, int);

/* fetch_text.c declarations */
void text_from_file(char *file, char *buffer);

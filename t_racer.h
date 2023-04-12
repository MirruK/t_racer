#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>

/* game.c declarations */
void disable_raw_mode(void);

/* text_helpers.c declarations */
void take_char(char*, int*);
int validate(char*, int, int);
void wrap_text(char *text, char *out_buffer, int limit);
void print_text_with_caret(char* text, int position);

/* fetch_text.c declarations */
void text_from_file(char *file, char *buffer);

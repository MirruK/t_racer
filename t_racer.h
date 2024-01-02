#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <term.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/* game.c declarations */
void disable_raw_mode(void);

/* text_helpers.c declarations */
void take_char(char *buf, int *buf_top);
int validate(char *, int, int, int wrong_count);
void wrap_text(char *text, char *out_buffer, int limit);
void print_text_with_caret(char *text, int position, int wrong_count);

/* fetch_text.c declarations */
void text_from_file(char *file, char *buffer);

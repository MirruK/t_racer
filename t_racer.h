#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>

void disable_raw_mode(void);
void take_char(char*, int*);
int validate(char*, int, int);

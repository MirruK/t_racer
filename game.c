#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>


static char test_text[] =   "Type this text correctly to win.";
static char empty_text[] =  "                                ";
struct termios orig_termios;

void clearScreen() {
  if (!cur_term)
    {
    int result;
    setupterm( NULL, STDOUT_FILENO, &result );
    if (result <= 0) return;
    }

  putp( tigetstr( "clear" ) );
}

void disable_raw_mode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    system("stty cooked");
}

void enable_raw_mode(){
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_oflag &= ~(OPOST);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void take_char(char *buf, int* buf_top){
    char c = getchar();
    if(c == 3 || c == 27){
        disable_raw_mode();
        exit(0);
    }
    buf[*buf_top] = c;
    *buf_top += 1;
}

int validate(char *buf, int buf_top){
    //if(buf[buf_top] == '\b') return 3;
    if(test_text[buf_top] == '\0' && test_text[buf_top-1] == buf[buf_top-1]) return 2;
    return test_text[buf_top-1] == buf[buf_top-1];
}

void game_loop(int mode){
    char buf[100];
    int result, stdin_empty;
    int buf_top = 0;
    clearScreen();
    printf("\n%s\n", test_text);
    if(mode == 1){
        while(1){
            empty_text[buf_top] = '^';
            printf("%s\r", empty_text);
            empty_text[buf_top] = ' ';
            take_char(buf, &buf_top);
            result = validate(buf, buf_top);
            if(result == 0) {
                clearScreen();
                printf("\n%s\n", test_text);
                printf("%s\r", empty_text);
                printf("\r\nYou typed the wrong character: %c, try %c\r\n", buf[buf_top-1], test_text[buf_top-1]);
                buf_top--;
            }
            else if(result == 2){
                printf("\r\nCongratulations, you are a capable typist\r\n");
                return;
            }
            else if(result == 3){
                buf[--buf_top] = '\0';
            }
        }
    }
}

int main(int argc, char *argv[]){
    enable_raw_mode();
    game_loop(1);
    exit(0);
}

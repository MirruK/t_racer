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

int validate(char *buf, int buf_top, int text_head){
    // if(buf[buf_top] == '\b') return 3;
    if(test_text[text_head+1] == '\0' && test_text[text_head] == buf[buf_top-1]) return 2;
    return test_text[text_head] == buf[buf_top-1];
}

void game_loop(int mode){
    char buf[100];
    int result, buf_top, text_head;
    result =  text_head = 0;
    buf_top = 1;
    if(mode == 1){
        // Init
        // Step 1.
        clearScreen();
        // Step 2.
        printf("\n%s\r\n", test_text);
        // Step 3.
        empty_text[text_head] = '^';
        printf("%s\r\n", empty_text);
        empty_text[text_head] = ' ';
        while(1){
            /*
             * Init Step 1. Clear screen
             * Init Step 2. Draw text to type
             * Init Step 3. Draw carret
             *
             * Step 1. take user input
             * Step 2. Validate input
             * Step 3. Draw according to input and start from step 1
             * */

            // Step 1.
            take_char(buf, &buf_top);
            
            clearScreen();
            // Step 2. 
            switch(validate(buf, buf_top, text_head)) {
                case 0:
                printf("\r\nYou typed the wrong character: %c, try %c\r\n", buf[buf_top-1], test_text[text_head]);
                buf_top--;
                break;
            case 1:
                text_head++; 
                break;
            case 2:
                printf("\r\nCongratulations, you are a capable typist\r\n");
                return;
            case 3:
                text_head--;
                buf_top--;
                break;
            default:
                break;
            }
            // Step 3.
            // Step 3.1.
            printf("\n%s\r\n", test_text);
            // Step 3.2.
            empty_text[text_head] = '^';
            printf("%s\r", empty_text);
            empty_text[text_head] = ' ';
        }
    }
}

int main(int argc, char *argv[]){
    enable_raw_mode();
    game_loop(1);
    exit(0);
}

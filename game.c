#include "t_racer.h"

char test_text[2000];
char print_text[2000];
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

void game_loop(int mode){
    char buf[1000];
    int result, buf_top, text_head, wrong_count;
    result = text_head = wrong_count = 0;
    buf_top = 1;
    if(mode == 1){
        clearScreen();
        print_text_with_caret(print_text, text_head, wrong_count);
        while(1){
            /*
             * Init Step 1. Clear screen
             * Init Step 2. Draw text to type
             * Init Step 3. Draw caret
             *
             * Step 1. take user input
             * Step 2. Validate input
             * Step 3. Draw according to input and start from step 1
             * */
            take_char(buf, &buf_top);
            clearScreen();
            print_text_with_caret(print_text, text_head, wrong_count);
            switch(validate(buf, buf_top, text_head, wrong_count)) {
                case 0:
                //printf("\r\nYou typed the wrong character: %c, try %c\r\n", buf[buf_top-1], test_text[text_head]);
                wrong_count++;
                buf_top--;
                break;
            case 1:
                if(wrong_count) buf_top--;
                else text_head++;
                break;
            case 2:
                printf("\r\nCongratulations, you are a capable typist\r\n");
                disable_raw_mode();
                exit(0);
            case 3:
                if(wrong_count)
                wrong_count--;
                else text_head--;
                buf[buf_top] = '\0';
                buf_top--;
                break;
            default:
                break;
            }
                clearScreen();
                print_text_with_caret(print_text, text_head, wrong_count);
        }
    }
}

int main(int argc, char *argv[]){
    if(argc > 1) text_from_file(argv[1], test_text);
    else text_from_file("texts/sample.txt", test_text);
    wrap_text(test_text, print_text, 70);
    enable_raw_mode();
    game_loop(1);
    disable_raw_mode();
    exit(0);
}

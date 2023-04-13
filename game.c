#include "t_racer.h"

char test_text[2000];
char print_text[2000];
struct termios orig_termios;

/* Get clock time with millisecond accuracy 
 * Function by Daniel on stackoverflow
 * thread answer: https://stackoverflow.com/a/64539170 */
int64_t millis()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return ((int64_t) now.tv_sec) * 1000 + ((int64_t) now.tv_nsec) / 1000000;
}

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
    clock_t start, end;
    double cpu_time_used;
    int total_chars_written, wrong_chars_written;
    total_chars_written = wrong_chars_written = 0;
    char buf[1000];
    int result, buf_top, text_head, wrong_count, timer_started;
    result = text_head = wrong_count = timer_started = 0;
    buf_top = 1;
    if(mode == 1){
        clearScreen();
        print_text_with_caret(print_text, text_head, wrong_count);
        while(1){
            take_char(buf, &buf_top);
            if(!timer_started){
                start = millis();
                timer_started = 1;
            }
            clearScreen();
            print_text_with_caret(print_text, text_head, wrong_count);
            switch(validate(buf, buf_top, text_head, wrong_count)) {
                case 0:
                    total_chars_written++;
                    wrong_chars_written++;
                    wrong_count++;
                    buf_top--;
                    break;
                case 1:
                    total_chars_written++;
                    if(wrong_count) buf_top--;
                    else text_head++;
                    break;
                case 2:
                    end = millis();
                    printf("\r\nCongratulations, you are a capable typist\r\n");
                    // Assumes text is in english (characters divided by chars_per_word)
                    double words_in_text = strlen(test_text) / 5.0;
                    // WPM = words divided by time_in_minutes
                    int wpm = words_in_text / ((end-start)/60000.0); 
                    float typing_accuracy = 100 - (100 * (wrong_chars_written / (float)total_chars_written));
                    printf("Your typing speed is: %d WPM\r\n", wpm);
                    printf("Your typing accuracy is: %.1f%%\r\n", typing_accuracy);
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

#include "t_racer.h"

extern char test_text[];

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

/* Takes a text buffer and insert carriage-return+newline-combinations
 * if the text reches the end of the line.
 * This also inserts the lines where the carret will be printed*/
void wrap_text(char *text, char *out_buffer, int limit){
    /*
     * Desired output for text where we wrap at 4 chars: Hi I am text.
     * -> Hi I
     *    ^
     *    am t
     *    ext.
     * */
    
}

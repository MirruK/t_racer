#include "t_racer.h"
#include <stdio.h>

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
    if(buf[buf_top-1] == 8 || buf[buf_top-1] == 127) return 3;
    if((test_text[text_head+1] == '\0' || test_text[text_head+1] == EOF) && test_text[text_head] == buf[buf_top-1]) return 2;
    return test_text[text_head] == buf[buf_top-1];
}

/* Takes a text buffer and insert carriage-return+newline-combinations
 * if the text reches the end of the line.
 * This also inserts the lines where the caret will be printed*/
void wrap_text(char *text, char *out_buffer, int limit){
    /*
     * Desired output for text where we wrap at 4 chars: Hi I am text.
     * -> Hi I
     *    ^
     *    am t
     *    ext.
     * */
    int col, try_wrap;
    col = try_wrap = 0;
    for(int i = 0; text[i] != EOF && text[i] != '\0'; i++){
        out_buffer[i] = text[i];
        if(col >= limit) try_wrap = 1;
        col++;
        if(try_wrap && text[i] == ' ') out_buffer[i] = '\n', col = 0, try_wrap = 0;
    }    
}

void print_text_with_caret(char* text, int position){
    int i, end, col;
    i = end = col = 0;
    while(!end){
        col = 0;
        for(; text[i] != '\n' && text[i] != '\0' && text[i] != EOF; i++, col++)
            putchar(text[i]);
        if(position >= i-col && position < i){
            putchar('\r');
            putchar('\n');
            for(int j = i-col; j<i; j++){
                if(j != position)
                    putchar(' ');
                else putchar('^');
            }
        }
        if(text[i+1] == '\0' || text[i+1] == EOF) return;
        putchar('\r');
        putchar('\n');
        i++;
    }
}

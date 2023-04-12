#include "t_racer.h"
#include <stdio.h>

#define KNRM  "\x1B[0m" //"\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

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

int validate(char *buf, int buf_top, int text_head, int wrong_count){
    if(buf[buf_top-1] == 8 || buf[buf_top-1] == 127) return 3;
    if(wrong_count) return 0;
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

void print_text_with_caret(char* text, int position, int wrong_count){
    int i, end, col;
    i = end = col = 0;
    while(!end){
        col = 0;
        for(; text[i] != '\n' && text[i] != '\0' && text[i] != EOF; i++, col++){
            if(i >= position && i < position+wrong_count && wrong_count>0) printf("%s%c", KRED,text[i]); // Make text red
            else if(i<position) printf("%s%c", KGRN,text[i]); // Make text green
            else printf("%s%c", KNRM, text[i]); // Make text normal color
        }
        if(position >= i-col && position < i){
            putchar('\r');
            putchar('\n');
            for(int j = i-col; j<i; j++){
                if(j != position+wrong_count)
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

#include "t_racer.h"
#include <stdio.h>
#include <stdlib.h>

/* Get text from a file into a buffer that is allocated by the caller */
void text_from_file(char *file_name, char *buffer){
    char *line_buf;
    size_t linesize = 0;
    FILE* text = fopen(file_name, "r");
    int buf_ind = 0;
    for(;getline(&line_buf, &linesize, text) != -1;){
        for(int i = 0; line_buf[i] != '\n' && line_buf[i] != '\0'; i++){
            buffer[buf_ind++] = line_buf[i];
        }
        buffer[buf_ind++] = ' ';
    }
    fclose(text);
    free(line_buf);
}

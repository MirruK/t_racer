#include "t_racer.h"

/* Get text from a file into a buffer that is allocated by the caller */
void text_from_file(char *file_name, char *buffer) {
  char *line_buf;
  size_t linesize = 0;
  FILE *text = fopen(file_name, "r");
  if (text == NULL) {
    perror("fopen error while opening game text: ");
    exit(1);
  }
  int buf_ind = 0;
  for (; getline(&line_buf, &linesize, text) != -1;) {
    for (int i = 0;
         line_buf[i] != '\n' && line_buf[i] != '\0' && line_buf[i] != EOF;
         i++) {
      buffer[buf_ind++] = line_buf[i];
    }
    buffer[buf_ind++] = ' ';
  }
  // Seek end of buffer
  for (; buffer[buf_ind] != '\0' && buffer[buf_ind] != EOF; buf_ind++)
    ;
  // Strip extra whitespace from the back of the text
  while (isspace(buffer[buf_ind])) {
    buf_ind--;
  }
  buffer[buf_ind - 1] = '\0';
  fclose(text);
  free(line_buf);
}

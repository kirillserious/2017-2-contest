#include <stdlib.h>
#include <stdio.h>
     
char *getline2(FILE *f) {
    char *line;
    int line_size = 0;

    line = NULL;

    int ch, i = 0;
    while ((ch = getc(f)) != EOF) {

        if (i >= line_size - 1) {
            line_size += 100;               
            line = realloc(line, line_size * sizeof(char));
            if (line == NULL) {
                return NULL;
            }
        }

        line[i] = ch;
        i++;

        if (ch == (int)'\n') {
            break;
        }
    }

    if (i) {
        line[i] = 0;
    }

    return line;
}
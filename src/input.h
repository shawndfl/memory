#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include <stdio.h>
#include <stdlib.h>

/*
 * Reads in a line from std.
 * The calling function will need to 
 * free the return pointer.
 * 
 * Returns: A pointer to the text read from stdin
 *          The calling function will own this memory. 
 */
char * inputLine(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
        {
            line--; //We don't want the \n char
            break;
        }
    }
    *line = '\0';
    return linep;
}


#endif

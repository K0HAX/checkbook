#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transaction.h"

char *command()
{
    unsigned int len_max = 12;
    unsigned int current_size = 0;

    char *pStr = malloc(len_max);
    current_size = len_max;

    printf(">");

    if(pStr != NULL)
    {
        int c = EOF;
        unsigned int i = 0;
        while ((c = getchar() ) != '\n' && c != EOF)
        {
            pStr[i++]=(char)c;

            if(i == current_size)
            {
                current_size = i+len_max;
                pStr = realloc(pStr, current_size);
            }
        }
        pStr[i] = '\0';
        return pStr;
    }
    return NULL;
}

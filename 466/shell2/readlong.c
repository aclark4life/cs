#include "stdio.h"
#define INCREMENT 100
void * check_malloc();
void * realloc();

/* read a string of indeterminate length */
char *read_long1()
{
    int c;
    char *cp, *buff;
    int len, buff_size;

    buff = NULL;
    buff_size = 0;
    for(len = 0; ((c = getchar()) != EOF); len++)
    {
        if (len == buff_size)
        {
            buff_size = buff_size + INCREMENT;
            if (buff == NULL)
                buff = check_malloc(buff_size);
            else
                buff = realloc(buff, buff_size);

            if (buff == NULL)
                abort1("No Core");

            cp = buff + len;
        }

        if (c == '\n')
        {
            *cp = '\0';
            return(buff);
        }
        *cp++ = c;
    }
    return (len == 0 ? NULL : buff);
}


/* read a string of indeterminate length */
char *read_long2()
{
    int c;
    char *buff;
    int len;

    buff = check_malloc(1);
    *buff = '\0';

    for(len = 0; ((c = getchar()) != EOF); len++)
    {
        if (c == '\n')
        {
            buff[len] = '\0';
            return(buff);
        }
        buff = realloc(buff, len+2);
        if (buff == NULL)
            abort1("No Core");

        buff[len] = c;
    }

    if (len == 0)
    {
        free(buff);
        return(NULL);
    }
    else
        return(buff);
}


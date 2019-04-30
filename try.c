/* first pipe example from Haviland */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 255

char string[MSGSIZE];
char final[] = "termina";

int main()
{
    char inbuf[MSGSIZE];

    int p[2];

    /* open pipe */

    if (pipe(p) == -1)
    {
        perror("pipe call error");
        exit(1);
    }

    /* repeat forever*/

    while (1)
    {
        /* get string from console */
        gets(string);

        /* write down pipe */
        write(p[1], string, MSGSIZE);

        /* Exit condition */
        if (strcmp(string, final) == 0)
        {
            exit(0);
        }

        /* read pipe */
        read(p[0], inbuf, MSGSIZE);
        printf("%s\n", inbuf);
    }
}
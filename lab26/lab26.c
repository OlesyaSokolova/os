#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES_NUMBER 3
#define SYMBOLS_TO_READ 100
#define STDOUT 1

int main()
{
    FILE * out;
    char *text[LINES_NUMBER] = {"Example text\n",
                           "abcUPPERghid\n",
                           "last Line oF examPle text\n"};

    out = popen("./lowerCaseUpperCase.out", "w");

    if(out == NULL)
    {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    for(i = 0; i < LINES_NUMBER; i++)
    {
        fputs(text[i], out);
    }

    int checkClose = pclose(out);
    if(checkClose == -1)
    {
        perror("Unable to close #0 file descriptor");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
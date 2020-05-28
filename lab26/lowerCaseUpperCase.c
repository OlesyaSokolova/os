#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOLS_TO_READ 100
#define STDIN 0
#define STDOUT 1

int main()
{
    char input[SYMBOLS_TO_READ];
    int readRes;
    int writeCheck;
    int i;
    while((readRes = read(STDIN, input, SYMBOLS_TO_READ))>0)
    {
        for(i = 0; i < readRes; i++)
        {
            if(islower(input[i]))
            {
                input[i] = toupper(input[i]);
            }
        }
    writeCheck = write(STDOUT, input, readRes);
    if(writeCheck == -1)
    {
            printf("Unable to write");
    }
    }
    exit(EXIT_SUCCESS);
}
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES_NUMBER 3
#define SYMBOLS_TO_READ 100
#define STDOUT 1

int main(int argc, char**argv)
{
    int pid;
    int fd[2];
    char *text[LINES_NUMBER] = {"\nExample text\n",
                           "abcUPPERghid\n",
                           "last Line oF examPle text"};
    int pipeCheck = pipe(fd);
    if(pipeCheck == -1)
    {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    int checkClose;
    pid = fork();
    if(pid > 0)
    {
        checkClose = close(fd[0]);
        if(checkClose == -1)
        {
            perror("Unable to close #0 file descriptor");
            exit(EXIT_FAILURE);
        }
        int i;
        for(i = 0; i < LINES_NUMBER;i++)
        {
            write(fd[1], text[i], strlen(text[i]));
        }
     checkClose = close(fd[1]);
     if(checkClose == -1)
     {
	perror("Unable to close #1 file descriptor (parent proc)");
        exit(EXIT_FAILURE);
     }
     }

    else if(pid == 0)
    {
        int readRes = 0;
        checkClose = close(fd[1]);
	if(checkClose == -1)
        {
	    perror("Unable to close #1 file descriptor (child proc)");
	    checkClose = close(fd[0]);
	    if(checkClose == -1)
    	    {
	        perror("Unable to close #0 file descriptor (child proc)");
    	    }
    	    exit(EXIT_FAILURE);
        }
        char input[SYMBOLS_TO_READ ];
        printf("\ntext before:\n");
        int i;
        for(i = 0; i < LINES_NUMBER;i++)
        {
            write(STDOUT, text[i], strlen(text[i]));
        }
        printf("\n\ntext after:\n");
        while((readRes = read(fd[0], input, SYMBOLS_TO_READ))>0)
        {
            for(i = 0; i < readRes; i++)
            {
                if(islower(input[i]))
                {
                    input[i] = toupper(input[i]);
                }
            }
            write(STDOUT, input, readRes);
        }
        checkClose = close(fd[0]);
	if(checkClose == -1)
        {
	    perror("Unable to close #0 file descriptor (child proc)");
    	    exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

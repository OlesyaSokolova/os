#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>

#define MAX_LINES_NUMBER 1024
#define BUF_SIZE 256
#define MAX_LINE_LENGTH 256
#define WAIT_TIME 5
#define STDIN 0
#define LINES_NUMBER 3
#define SYMBOLS_TO_READ 100
#define STDOUT 1

int createShiftsTable(char* dataBuffer, off_t fileSize, int*linesLengths,  long* shifts)
int main(int argc, char**argv)
{
    int currentLineLength = 0;
    int currentShift = currentLineLength;
    int lineNumber  = 0;
    shifts[lineNumber] = currentShift;

    off_t i;
    for(i = 0; i < fileSize; i++)
    {
    if(dataBuffer[i] == '\n')
    int pid;
    int fd[2];
    char *text[LINES_NUMBER] = {"\nExample text\n",
                           "abcUPPERghid\n",
                           "last Line oF examPle text"};
    int pipeCheck = pipe(fd);
    if(pipeCheck == -1)
    {
        currentLineLength++;
        linesLengths[lineNumber] = currentLineLength;
        lineNumber++;
        currentShift+=currentLineLength;
        shifts[lineNumber] = currentShift;
        currentLineLength = 0;
    }
    else
    {
        currentLineLength++;
    }
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    return  lineNumber;
}

int askAndPrintLines(int fileDesc, char * dataBuffer, int linesNumber, int* linesLengths, long* shifts)
{
    int lineNumber = -1;
    int readCheck;
    char readBuffer[BUF_SIZE];
    int readNumber = 0;
    int pollCheck;
    int writeCheck;
    printf("This program prints lines from file. To exit type -1 as line number.\n");
    struct pollfd fds;
    fds.fd = STDIN_FILENO;
    fds.events = POLLIN;
    for(;;)
    int checkClose;
    pid = fork();
    if(pid > 0)
    {
        printf("Enter line number (in 5 seconds):\n");

        pollCheck = poll(&fds, 1, WAIT_TIME * 1000);
        if (pollCheck == -1)
        checkClose = close(fd[0]);
        if(checkClose == -1)
        {
            perror("poll");
            return -1;
            perror("Unable to close #0 file descriptor");
            exit(EXIT_FAILURE);
        }
        if (pollCheck == 0)
        int i;
        for(i = 0; i < LINES_NUMBER;i++)
        {
            printf("%s", dataBuffer);
            return -1;
            write(fd[1], text[i], strlen(text[i]));
        }
        readCheck = scanf("%d", &lineNumber);
        if(readCheck == 0)
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
            printf("Bad input. This program works only with numbers!\n");
            if(errno == EINTR)
            {
                printf("Try again.\n");
                continue;
            }
            else
            {
                return -1;
            }
	    perror("Unable to close #1 file descriptor (child proc)");
	    checkClose = close(fd[0]);
	    if(checkClose == -1)
    	    {
	        perror("Unable to close #0 file descriptor (child proc)");
    	    }
    	    exit(EXIT_FAILURE);
        }
        else
        char input[SYMBOLS_TO_READ ];
        printf("\ntext before:\n");
        int i;
        for(i = 0; i < LINES_NUMBER;i++)
        {
            if(lineNumber == -1)
            {
                return -1;
            }
            if(lineNumber < 0)
            {
                printf("Line number shouldn't be less than zero.Try again.\n");
                continue;
            }
            if(lineNumber >= linesNumber)
            {
                printf("Line number should be less than lines number which is %d.\nTry again.\n", linesNumber);
                continue;
            }
            write(STDOUT, text[i], strlen(text[i]));
        }

        lseek(fileDesc, shifts[lineNumber], SEEK_SET);
        int readCheck = read(fileDesc, readBuffer, linesLengths[lineNumber]);
        if(readCheck == -1)
        printf("\n\ntext after:\n");
        while((readRes = read(fd[0], input, SYMBOLS_TO_READ))>0)
        {
            printf("Unable to read this line from file.\n");
             if(errno == EINTR)
            for(i = 0; i < readRes; i++)
            {
                printf("Try again.\n");
                continue;
                if(islower(input[i]))
                {
                    input[i] = toupper(input[i]);
                }
            }
            continue;
        }
        write(STDOUT, readBuffer, linesLengths[lineNumber]);
        if(writeCheck == -1)
        {
            printf("Unable to write this line! Line number: %d", lineNumber);
            continue;
            write(STDOUT, input, readRes);
        }
    }
}
int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fileDesc = open(argv[1], O_RDONLY);
    if(fileDesc == -1)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    int checkClose;
    off_t fileSize = lseek(fileDesc, 0, SEEK_END);
    lseek(fileDesc, 0, SEEK_SET);

    char* dataBuffer = (char*)malloc(sizeof(char)*fileSize);
    if(dataBuffer == NULL)
    {
        perror("Unable to allocate memory for reading from file");
        checkClose  = close(fileDesc);
        if(checkClose == -1)
        checkClose = close(fd[0]);
	if(checkClose == -1)
        {
            perror("Unable to close file");
            exit(EXIT_FAILURE);
	    perror("Unable to close #0 file descriptor (child proc)");
    	    exit(EXIT_FAILURE);
        }
    }
    int checkRead = read(fileDesc, dataBuffer, fileSize);
    if(checkRead == -1)
    else
    {
    free(dataBuffer);
        perror(argv[1]);
        checkClose  = close(fileDesc);
        if(checkClose == -1)
        {
            perror("Unable to close file");
            exit(EXIT_FAILURE);
        }
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    lseek(fileDesc, 0, SEEK_SET);
    long shifts[MAX_LINES_NUMBER];
    int linesLengths[MAX_LINE_LENGTH];

    int realLinesNumber =  createShiftsTable(dataBuffer, fileSize, linesLengths,  shifts);
    int checkWork  = askAndPrintLines(fileDesc, dataBuffer, realLinesNumber, linesLengths, shifts);

    free(dataBuffer);
    checkClose  = close(fileDesc);

    if(checkClose == -1)
    {
        perror("Unable to close file");
        exit(EXIT_FAILURE);
    }
    if(checkWork == -1);
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

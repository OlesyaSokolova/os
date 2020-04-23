#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <sys/mman.h>
#define MAX_LINES_NUMBER 1024
#define BUF_SIZE 256
#define MAX_LINE_LENGTH 256
#define WAIT_TIME 5
#define STDIN 0
#define STDOUT 1

int createShiftsTable(char* dataBuffer, off_t fileSize, int*linesLengths,  long* shifts)
{
    int currentLineLength = 0;
    int currentShift = currentLineLength;
    int lineNumber  = 0;
    shifts[lineNumber] = currentShift;

    off_t i;
    for(i = 0; i < fileSize; i++)
    {
    if(dataBuffer[i] == '\n')
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
    }
    return  lineNumber;
}

int askAndPrintLines(int fileDesc, char * dataBuffer, int linesNumber, int* linesLengths, long* shifts)
{
    int lineNumber = -1;
    int readCheck;
    char* readBuffer;
    int readNumber = 0;
    int pollCheck;
    int writeCheck;
    printf("This program prints lines from file. To exit type -1 as line number.\n");
    struct pollfd fds;
    fds.fd = STDIN_FILENO;
    fds.events = POLLIN;
    for(;;)
    {
        printf("Enter line number (in 5 seconds):\n");

        pollCheck = poll(&fds, 1, WAIT_TIME * 1000);
        if (pollCheck == -1)
        {
            perror("poll");
            return -1;
        }
        if (pollCheck == 0)
        {
            printf("%s", dataBuffer);
            return -1;
        }
        readCheck = scanf("%d", &lineNumber);
        if(readCheck == 0)
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
        }
        else
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
        }

        lseek(fileDesc, shifts[lineNumber], SEEK_SET);
        //int readCheck = read(fileDesc, readBuffer, linesLengths[lineNumber]);
        readBuffer = mmap(0,linesLengths[lineNumber], PROT_READ, MAP_SHARED, fileDesc, 0);
        if(readBuffer == MAP_FAILED)
        {
            printf("Unable to read this line from file.\n");
            continue;
        }
        writeCheck  = write(STDOUT, readBuffer, linesLengths[lineNumber]);
        if(writeCheck == -1)
        {
            printf("Unable to write this line! Line number: %d", lineNumber);
            continue;
        }
        int munmapCheck = munmap(readBuffer, linesLengths[lineNumber]);
        if(munmapCheck == -1)
        {
            perror("Unable to do munmap at function \"askAndPrintLines\".");
            exit(EXIT_FAILURE);
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

    //char* dataBuffer = (char*)malloc(sizeof(char)*fileSize);
    char* dataBuffer = mmap(0, fileSize, PROT_READ, MAP_SHARED, fileDesc, 0);
    if(dataBuffer == MAP_FAILED)
    {
        perror("Unable to read data from file");
        checkClose = close(fileDesc);
        if(checkClose == -1)
        {
            perror("Unable to close file");
            exit(EXIT_FAILURE);
        }
    }
    lseek(fileDesc, 0, SEEK_SET);
    long shifts[MAX_LINES_NUMBER];
    int linesLengths[MAX_LINE_LENGTH];

    int realLinesNumber =  createShiftsTable(dataBuffer, fileSize, linesLengths,  shifts);
    int checkWork  = askAndPrintLines(fileDesc, dataBuffer, realLinesNumber, linesLengths, shifts);

    //free(dataBuffer);
    int munmapCheck = munmap(dataBuffer, fileSize);
    if(munmapCheck == -1)
    {
        perror("Unable to do munmap at \"main\".");
        exit(EXIT_FAILURE);
    }

    checkClose  = close(fileDesc);

    if(checkClose == -1)
    {
        perror("Unable to close file.");
        exit(EXIT_FAILURE);
    }
    if(checkWork == -1);
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
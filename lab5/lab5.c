#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define MAX_LINES_NUMBER 1024
#define MAX_LINE_LENGTH 256
int createShiftsTable(char* dataBuffer, long fileSize, int*linesLengths,  long* shifts)
{
    int currentLineLength = 0;
    int currentShift = currentLineLength;
    int lineNumber  = 0;
    shifts[lineNumber] = currentShift;

    long i;
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

/*void printShiftsTable(int linesNumber, int*linesLengths, long* shifts)
{
    int i = 0;
    printf("No  shift\n");
    for(i = 0; i < linesNumber; i++)
    {
        printf("%d    ", i);
        printf("%ld\n", shifts[i]);
    }
}*/
int askAndPrintLines(int fileDesc, int linesNumber, int* linesLengths, long* shifts)
{
    int lineNumber;
    int readCheck;
    char readBuffer[MAX_LINE_LENGTH];
    printf("This program prints lines from file. To exit type -1 as line number.\n");
    while(1)
    {
        printf("Enter line number:\n");
        readCheck = scanf("%d", &lineNumber);
        if(readCheck == 0)
        {
            printf("Unable to read line number.\n");
            return -1;
        }
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

        lseek(fileDesc, shifts[lineNumber], SEEK_SET);
        int readCheck = read(fileDesc, readBuffer, linesLengths[lineNumber]);
        if(readCheck == -1)
        {
            printf("Unable to read this line from file.\n");
            return -1;
        }
        write(1, readBuffer, linesLengths[lineNumber]);
    }
}
int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("No input file!\n");
        exit(EXIT_FAILURE);
    }

    int fileDesc = open(argv[1], O_RDONLY);
    if(fileDesc == -1)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    long fileSize = lseek(fileDesc, 0, SEEK_END);
    lseek(fileDesc, 0, SEEK_SET);

    char* dataBuffer = (char*)malloc(sizeof(char)*fileSize);
    int checkRead = read(fileDesc, dataBuffer, fileSize);
    if(checkRead == -1)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    lseek(fileDesc, 0, SEEK_SET);
    long shifts[MAX_LINES_NUMBER];
    int linesLengths[MAX_LINE_LENGTH];

    int realLinesNumber =  createShiftsTable(dataBuffer, fileSize, linesLengths,  shifts);
    int checkWork  = askAndPrintLines(fileDesc, realLinesNumber, linesLengths, shifts);

    close(fileDesc);
    free(dataBuffer);
    if(checkWork == -1);
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{

    if(argc < 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char command[BUFSIZ] = "cat ";
    strcat(command, argv[1]);
    strcat(command, " | grep '^$' | wc -l\0");

    FILE * fin;
    fin = popen(command, "r");
    if(fin == NULL)
    {
	    perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    int linesNumber;
    fscanf(fin, "%d", &linesNumber);
    printf("Lines number: %d\n", linesNumber);

    int checkClose = pclose(fin);
    if(checkClose == -1)
    {
        perror("pclose");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

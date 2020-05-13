#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

main(int argc, char**argv)
{
    if(argc < 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid, waitCheck;
    int status;
    pid = fork();
    if (pid == 0)
    {
        int execlCheck = execl("/bin/cat", "cat", argv[1], (char*)0);
        if(execlCheck == -1)
        {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }

    waitCheck = wait(&status);
    if(waitCheck == -1)
    {
        perror("waiting for child process");
        exit(EXIT_FAILURE);
    }

    printf("\nI'm parent and my child (%ld) finished its work.\n", pid);
    exit(EXIT_SUCCESS);
}
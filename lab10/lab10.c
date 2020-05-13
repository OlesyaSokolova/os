#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int status;
    pid_t pid, waitCheck;
    pid = fork();
    if (pid == 0)
    {
        int execCheck = execvp(argv[1], &argv[1]);
        if(execCheck == -1)
        {
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    waitCheck = wait(&status);
    if(waitCheck == -1)
    {
        perror("waiting for child process");
        exit(EXIT_FAILURE);
    }

    wait(&status);
    printf("\nChild exit status: %d\n", WEXITSTATUS(status));
    exit(EXIT_SUCCESS);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char command[BUFSIZ] = "cat ";
	strcat(command, argv[1]);
	strcat(command, " | grep '^$' | wc -l\0");

	FILE * fin;
	fin = popen(command, "r");

	if (fin == NULL)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	int linesNumber;
	fscanf(fin, "%d", &linesNumber);

	int status = pclose(fin);
	if (status == -1)
	{
		perror("pclose error");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status) != 0)
	{
		if (WEXITSTATUS(status) == 0)
		{
			printf("Lines number: %d\n", linesNumber);
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Error: child process returned %d", WEXITSTATUS(status));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror("Child process finished with error");
		exit(EXIT_FAILURE);
	}	
}

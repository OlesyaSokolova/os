#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("File not found!\n");
		exit(EXIT_FAILURE);
	}

	uid_t real_uid, effective_uid;

	real_uid = getuid();
	effective_uid = geteuid();

	printf("Real user id = %d;\nEffective user id = %d.\n", real_uid, effective_uid);

	FILE *file;
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File opened successfully! Now it will be closed.\n");
		fclose(file);
	}

	setuid(real_uid);

	real_uid = getuid();
	effective_uid = geteuid();

	printf("New real user id = %d;\nNew effective user id = %d.\n", real_uid, effective_uid);


	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File opened successfully! Now it will be closed.\n");
		fclose(file);
		exit(EXIT_SUCCESS);
	}
}
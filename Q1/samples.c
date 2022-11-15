#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat buf;

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("usage: samples file numberfrags maxfragsize\n");
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	/*int count =0;
	for (int c = getc(file); c != EOF; c = getc(file))

		// Increment count for this character
		count = count + 1;
	*/

	stat(argv[1], &buf);
	int size = buf.st_size;

	int n = atoi(argv[2]);
	int m = atoi(argv[3]);

	printf("%d\n", n);
	printf("%d\n", m);
	printf("%d\n", size);

	int c = 0;
	int ran =0;

	for (int i = 0; i < n; i++)
	{   
		ran = rand()% (size - m) + 0;
		printf("%d\n", ran);
		fseek(file, ran, SEEK_SET);
		//fseek(file, (rand()% (size - m) + 0), SEEK_SET);
		printf(">");
		for (int j = 0; j < m; j++)
		{
			c = fgetc(file);
			if (feof(file))
			{
				break;
			}

			printf("%c", c);
		}
		printf("<\n");
	}
	return (0);
}

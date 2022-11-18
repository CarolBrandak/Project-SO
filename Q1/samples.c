#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define BIGSIZE 1000

struct stat buf;

int main(int argc, char *argv[])
{
	// size>= n+m
	time_t t;

	if (argc != 4)
	{
		printf("usage: samples file numberfrags maxfragsize\n");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	stat(argv[1], &buf);
	int size = buf.st_size;

	int n = atoi(argv[2]);
	int m = atoi(argv[3]);

	if (size < n + m - 1)
	{
		perror("Error: File doesn't have enough size");
		exit(EXIT_FAILURE);
	}
	
	int c = 0;
	int *indexes;
	// Preenche a array indexes com tudo a 0
	indexes = (int *) malloc (BIGSIZE * sizeof (int));
	
	int repetido = 1;
	int r;
	int cnt = 0;

	for (int i = 0; i < n; i++)
	{
		while(repetido){
			repetido = 0;
			// Faz random do index + 1 porque não pode dar 0
			r = rand() % (size - m + 1) + 1;
			for (int i = 0; i < BIGSIZE; i++)
			{
				if (r == indexes[i]){
					repetido = 1;
					break;
				}
			}
		}
		cnt++;
		// Coloca o index+1 na array para ser diferente de 0
		indexes[cnt] = r;
		// Procura no ficheiro o index podendo este ser 0
		fseek(file, r-1, SEEK_SET);
		printf(">");
		for (int j = 0; j < m; j++)
		{
			c = fgetc(file);
			if (feof(file))
				break;

			printf("%c", c);
		}
		printf("<\n");
		repetido = 1;
	}

	return (0);
}

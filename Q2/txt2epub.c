#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat buf;


int main(int argc, char *argv[])
{
	//printf("%s\n",argv[1]);

	//FILE *file = fopen(argv[1], "r");
	
	int nArgv = argc;
	
	//read n files 
	for(int i=1; i<nArgv; i++) {
		//printf("%d\n",i);
		FILE *file = fopen(argv[i], "r");

		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		
		stat(argv[i], &buf);
		int size = buf.st_size;
		//printf("%d\n", size);


		//convert .txt to .epub




		//add n files to ebooks.zip
	}


	return (0);
}

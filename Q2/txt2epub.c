#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

struct stat buf;


int main(int argc, char *argv[])
{
	//printf("%s\n",argv[1]);

	//FILE *file = fopen(argv[1], "r");
	
	int nArgv = argc;
	pid_t pid = 1;
	
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

		//remove .txt terminator		
		argv[i][sizeof(argv[i])-3] = '\0';


		char *buffer;
		asprintf(&buffer,"pandoc %s.txt --to=epub -o %s.epub --metadata title=\"%s\"", argv[i],argv[i],argv[i]);


		
		//convert .txt to .epub
		if (pid = fork() == 0) 
		{
			system(buffer); 
			return(0);
		}
		
	}

	//add n files to ebooks.zip

	char tozip[] = "zip ebooks.zip ";

	for (int i = 1; i < nArgv; i++)
	{
		strcat(tozip, argv[i]);
		strcat(tozip, ".epub ");
	}
	printf("this: %s",tozip);
	system(tozip);

	
	return(0);
}

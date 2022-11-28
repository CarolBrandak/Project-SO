#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

struct stat buf;

int main(int argc, char *argv[])
{
	//printf("%s\n",argv[1]);

	//FILE *file = fopen(argv[1], "r");
	
	int nArgv = argc;
	pid_t pid = 1;
	
	//read n files 
	for(int i=1; i<argc; i++) {
		// create process and execute pandoc, exec 
		// name, -o ficheiro.epub
		
		//remove .txt terminator		
		argv[i][sizeof(argv[i])-3] = '\0';

		char *buffer;
		asprintf(&buffer,"pandoc %s.txt --to=epub -o %s.epub --metadata title=\"%s\"", argv[i],argv[i],argv[i]);

		//convert .txt to .epub
		system(buffer); 
	}

	//add n files to ebooks.zip
	char tozip[100] = "zip ebooks.zip ";

	for (int i = 1; i < nArgv; i++)
	{
		strcat(tozip, argv[i]);
		strcat(tozip, ".epub ");
	}
	system(tozip);
	
	return(0);
}

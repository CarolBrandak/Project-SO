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
	pid_t pid = 1,wpid;
	int status = 0;
	if (pid = fork() == 0){
		
		//read n files 
		for(int i=1; i<argc; i++) {
			// create process and execute pandoc, exec 
			// name, -o ficheiro.epub
			char *origin; //store origin file
			asprintf(&origin,argv[i]);
			
			//remove .txt terminator		
			argv[i][sizeof(argv[i])-3] = '\0';
			
			char * destination; //store destinantion file
			asprintf(&destination,"%s.epub",argv[i]);

			char * title; //store title 
			asprintf(&title,"title=\"%s\"",argv[i]);

			char *buffer;
			asprintf(&buffer,"%s.txt --to=epub -o %s.epub --metadata title=\"%s\"", argv[i],argv[i],argv[i]);



			char* argument_list[] = {"/bin/pandoc", origin, "--to=epub", "-o", destination, "--metadata", title, NULL};

			//convert .txt to .epub
			execvp("/bin/pandoc",argument_list); 
		}
	}else{

	//wait for all subprocesses to finish
	while ((wpid = wait(&status)) > 0);

	
	char tozip[100];//todo change this to adaptive size

	//change terminator for output files
	for (size_t i = 1; i < nArgv; i++)
	{	
		argv[i][sizeof(argv[i])-3] = '\0';
		strcat(&tozip,argv[i]);
		strcat(&tozip,".epub");
	}
	


	char* argument_list[] = {"/bin/zip", "ebooks.zip", &tozip, NULL};
	printf("%d\n",execvp("/bin/zip",argument_list)); 
	printf("something\n");
	
	}
	return(0);
}

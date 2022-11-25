#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>


struct stat buf;

int main(int argc, char *argv[])
{	
	// Read 3 numbers

	if (argc != 4)
	{
		printf("Error: Not enough info\n");
		exit(EXIT_FAILURE);
	}

	//srand(time(NULL));

	int n = atoi(argv[1]);
	int p = atoi(argv[2]);
	int t = atoi(argv[3]);

	// Create ring of processes 
	char i_char = 1 + '0'; 
	char i1_char = 2 + '0';
	char myfifo[9] = {'p', 'i', 'p', 'e', i_char, 't', 'o', i1_char};
	
	for(int i=1; i<n+1; i++) {
		i_char = i + '0';
		i1_char = (i+1) + '0';
		if(i<n){
			myfifo[4] = i_char;
			myfifo[7] = i1_char;
		}
		else{
			myfifo[4] = n+'0';
			myfifo[7] = 1+'0';
		}
		printf("%s\n", myfifo);
		mkfifo(myfifo,0666);
	}

	//p1 enviar token to p2  etc 




	





	return (0);
}

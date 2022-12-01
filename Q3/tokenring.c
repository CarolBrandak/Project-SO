#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>


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
	int numberOfProcesses = atoi(argv[1]);
	int probabilityBlocked = atoi(argv[2]);
	int timeBlocked = atoi(argv[3]);

	if (numberOfProcesses < 2)
	{
		printf("Error: Not enough processes\n");
		exit(EXIT_FAILURE);
	}

	char i_char = 1 + '0'; 
	char i1_char = 2 + '0';
	char fifoName[9] = {'p', 'i', 'p', 'e', i_char, 't', 'o', i1_char};
	
	//Create the myfifo
	for(int i=1; i<numberOfProcesses+1; i++) {
		i_char = i + '0';
		i1_char = (i+1) + '0';
		if(i<numberOfProcesses){
			fifoName[4] = i_char;
			fifoName[7] = i1_char;
		}
		else{
			fifoName[4] = numberOfProcesses+'0';
			fifoName[7] = 1+'0';
		}
		printf("%s\n", fifoName);
		mkfifo(fifoName,0666);
	}

	// Create ring of fifos 
	for (int i = 1; i <= numberOfProcesses; i++) {

		char nameOfFifo[9] = {'p', 'i', 'p', 'e', 'n', 't', 'o', 'n'};
		
		if (i == numberOfProcesses) //if it is the last fifo sent it back to first
		{
			nameOfFifo[4] = '0' + i;
			nameOfFifo[7] = '0' + 1;
		}else{
			nameOfFifo[4] = '0' + i;
			nameOfFifo[7] = '0' + i + 1;
		}

		mkfifo(nameOfFifo,0666);
	}
	
	//Create ring of processes
	for (int i = 1; i <= numberOfProcesses; i++) {	
		//sleep(3);
		char readFifo[9] = {'p', 'i', 'p', 'e', 'n', 't', 'o', 'n'};
		char writeFifo[9] = {'p', 'i', 'p', 'e', 'n', 't', 'o', 'n'};

		if (i == numberOfProcesses) //if it is the last fifo sent it back to first
		{
			writeFifo[4] = '0' + i;
			writeFifo[7] = '0' + 1;

			readFifo[4] = '0' + i - 1;
			readFifo[7] = '0' + i;
		}else if(i == 1){
			writeFifo[4] = '0' + i;
			writeFifo[7] = '0' + i + 1;

			readFifo[4] = '0' + numberOfProcesses;
			readFifo[7] = '0' + i;
		}else{
			writeFifo[4] = '0' + i;
			writeFifo[7] = '0' + i + 1;

			readFifo[4] = '0' + i - 1;
			readFifo[7] = '0' + i;
		}

		printf("i = %d, write = %s, read = %s\n",i,writeFifo,readFifo);
		
		if (!fork()){
			int token;
			int started = 0;
				
			if (strcmp(writeFifo,"pipe1to2") == 0  && !started){

				started = 1;
				token = 0;
				printf("started with token = %d \n",token);

				int write_fifo = open(writeFifo);
				write(write_fifo, &token, sizeof(token));
				close(writeFifo);
			}
			double r;
			while (1){

				int token_r;
				int read_fifo = open(readFifo);
				if(read(read_fifo, token_r, sizeof(token_r)) == 0){
					close(readFifo);
					continue;
				}
				close(readFifo);

				r = rand() % 101;
				printf("random = %d\n", r);
				
				if ((r/100) < probabilityBlocked){
					sleep(timeBlocked);
					printf("lock on token (val = %d)\n", token_r);
					printf("unlock token\n");
				}

				printf("read from = %s with token = %d \n",readFifo, token_r);
				token_r++;

				int write_fifo = open(writeFifo);
				write(write_fifo, &token_r, sizeof(token_r));
				close(writeFifo);
				printf("write to = %s with token = %d \n",writeFifo, token_r);

			}
		}
	}

	wait(NULL);

    return 0;
}
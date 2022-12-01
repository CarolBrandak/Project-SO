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

  /* mkfifo works as a normal file but can only be edited if both sides are open (2 processes)
  */

	/*char token = '0';
	int c1_wr;
	int cN_rd;
	int p1[2];*/

	c1_wr=dup(p1[1]);
	char i_char = 1 + '0'; 
	char i1_char = 2 + '0';
	char myfifo[9] = {'p', 'i', 'p', 'e', i_char, 't', 'o', i1_char};
	char myfifo2[9] = {'p', 'i', 'p', 'e', i_char, 't', 'o', i1_char};

	// Create ring of processes 
	for (int j=0; j<n; j++) {
		int pid;
		int i=1;
		
	
	
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
		i++;

		char i2_char = i + '0';
		char i3_char = (i+1) + '0';
		if(i<n){
			myfifo2[4] = i2_char;
			myfifo2[7] = i3_char;
		}
		else{
			myfifo2[4] = n+'0';
			myfifo2[7] = 1+'0';
		}
		printf("%s\n", myfifo2);
		mkfifo(myfifo2,0666);

	

		if ((pid = fork()) == 0)
        {   int a=open(myfifo);
          
            int token;
            read(a, &token, sizeof(1));
            token+=1;
			int b = open(myfifo2);
            write(b, &token, sizeof(1));
        
            exit(0);
        }
      
        
    
		i++;
		
	}
	
	char finaltoken;
	char fmkfifo[9]={'p', 'i', 'p', 'e', n, 't', 'o', '1'};
	int final =open(fmkfifo);
    read( final, &finaltoken, sizeof(1));
	printf("%c\n", finaltoken);
   
    int p2[2];
	c1_wr=dup(p1[1]);
	

	// Create ring of processes 
	for (int i=0; i<n; i++) {
		int pid;
		pipe(p2);
        fflush(stdout);
		if ((pid = fork()) == 0)
        {
            close(p1[1]);
            close(p2[0]);
            int token;
            read(p1[1], &token, sizeof(1));
            token+=1;
            write(p2[1], &token, sizeof(1));
            close(p1[0]);
            close(p2[1]);
            exit(0);
        }
        printf("Child %2d = %d\n", n+1, pid);
        
        close(p1[0]);
        close(p1[1]);
        p1[0] = p2[0];
        p1[1] = p2[1];
		
	}
	cN_rd = p2[0];
    close(p2[1]);

    int token= read(p1[1],&token, sizeof(1));
    write(c1_wr, &token, sizeof(1));
    close(c1_wr);
    read(cN_rd, &token, sizeof(1));
    close(cN_rd);
    printf("PID sum = %d\n", 1);
    printf("PID chk = %d\n", 1);

    return 0;
	}

	//p1 enviar token to p2  etc 

  return (0);
}


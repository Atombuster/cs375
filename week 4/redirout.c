#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	
	if (argc < 3) {
		printf("not enuff imformation\n");
		exit(0);
	}//pase the command line
	
	int fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
	dup2(fd, 1);
	//find max of argv[i] = arc - 2
	fprintf(stderr,"argv = %s\n", (argv+2)[0]);
	
	execvp(argv[2], (argv+2));
	
}

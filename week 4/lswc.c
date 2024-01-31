
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char *argv[]){
	int pfd[2];
	
	
	if (pipe(pfd) == -1) {
		perror("pipe");
		exit(0);
	}
	
	pid_t pid = fork();
	
	if (pid == -1) {
		perror("fork");
		exit(0);
	}// fork did not work
	
	if (pid == 0) {
		dup2(pfd[0], 0);
		close(pfd[1]);
		execlp("wc", "wc", "-l", NULL);
		perror("execlp");
		exit(0);
    } else {//^child
		dup2(pfd[1], 1);
		close(pfd[0]);
		
		if (argc == 1){
			execlp("ls", "ls", "-1a", NULL);
		} else {
			execlp("ls", "ls", "-1a", argv[1], NULL);
		}
		perror("execlp");
		exit(0);
	}//^parent
}

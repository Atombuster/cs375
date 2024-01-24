//Austen Turbyne 1/22/2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 2048
#define MAX_WORDS 128

//start
int main(){
	char line[MAX_LINE];
	char *word[MAX_WORDS + 1];
	char *token;
	const char s[2] = " "; //put in stuff to split in strtok
	int i=0;
	
	pid_t pid;
	char cd[] = "cd";
	char EXIT[] = "exit";
	while(1) {
		printf("New prompt: ");
		if (fgets(line, sizeof(line), stdin) != NULL) {
			//printf("Full line: %s", line);//test
			line[strlen(line)-1] =  '\0';//removes \n so it works
	
			//start of token
			token = strtok(line, s);
			//go through the rest of the words
			while (token != NULL) {
				word[i] = token;
				i++;
				//printf("%s\n", word[i-1]);//test
				token = strtok(NULL, s);
				
				
			}
			word[i] = NULL;
			//printf("%d\n", strcmp(word[0], cd));//test
			if (strcmp(word[0], cd) == 0){
				//printf("CD\n");//test
				if (chdir(word[1]) == -1){
					perror("cd failed");
				}
			} else if (strcmp(word[0], EXIT) == 0) {
				exit(1);
			} else {
				pid = fork();
				if (pid == 0) {
					if (execvp(word[0], word) == -1) {
						perror("execvp failed");
						exit(1);
					}
				}
				wait(NULL);
			}
		}//2nd if
		else {
			perror("line error");
		}
		

		
	}
}

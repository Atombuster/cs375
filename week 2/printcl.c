#include <stdio.h>
//argv a pointer to the strings that contain the commands
//argc number of command line arguments
int main(int argc, char *argv[]) {
    for(int i = 0; i < argc; i++) {
        printf("%d: %s\n", i, argv[i]);
    }// loops though number of commands
	// prints out line number and the string that holds the command

    return 0;
} 
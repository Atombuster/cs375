#include <fcntl.h> 
#include <unistd.h> 
#include <errno.h> 
#include <ctype.h>

#define MAX_BUFFER_SIZE 2048
//int toupper(int c);
void perror(const char *s);

int main(int argc, char *argv[]) {
    char buffer[MAX_BUFFER_SIZE]; 
    ssize_t Read;

    if (argc == 1) { //check input file descriptor put it on termanale
        while ((Read = read(0, buffer, MAX_BUFFER_SIZE)) > 0) { 
            write(1, buffer, Read);
        } 
    } else {
        for (int i = 1; i < argc; i++) { 
		//O_RDONLY opens the file for reading
            int fd = open(argv[i], O_RDONLY); 
			toupper(fd);
            if (fd == -1) { 
                perror("Error opening file");
                continue; 
            }//checked for errors

            while ((Read = read(fd, buffer, MAX_BUFFER_SIZE)) > 0) { 
                write(1, buffer, Read); 
		
            }//put the file on termanale

            close(fd); 
        }
    }

    return 0; 
}

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define MAX_BUFFER_SIZE 2048
void perror(const char *s);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(2, "Usage: ./readfile <filename>\n", 29);
        return 1;
    }// if no file is open 

    int fd = open(argv[1], O_RDONLY);
	//open(name, flags); 
	//O_RDONLY opens file for reading only
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
	//ssize_t same as size_t, but is a signed type
	//signed int alow for neg number
    char buffer[MAX_BUFFER_SIZE];
    ssize_t bytesRead = read(fd, buffer, MAX_BUFFER_SIZE);
    if (bytesRead == -1) {
        perror("Error opening file");
        close(fd);
        return 1;
    }//if error

    ssize_t bytesWritten = write(1, buffer, bytesRead);
	//write to command line
    if (bytesWritten == -1) {
        perror("Error writing to standard output");
        close(fd);
        return 1;
    }//if error

    close(fd);
    return 0;
}

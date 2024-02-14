CC = gcc
CFLAGS = -Wall -I. -Wextra
LDFLAGS = 
OBJFILES = myalloc.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	del -f $(OBJFILES) $(TARGET) *.exe
	
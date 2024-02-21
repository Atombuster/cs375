CC = gcc
CFLAGS = -Wall -I. -Wextra
LDFLAGS = 
OBJFILES = myalloc_2.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	del -f $(OBJFILES) $(TARGET) *.exe
	
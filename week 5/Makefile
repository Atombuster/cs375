CC = gcc
CFLAGS = -Wall -I.
LDFLAGS = 
OBJFILES = llist.o 
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	del -f $(OBJFILES) $(TARGET) *.exe
	
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = museum
SOURCES = lab5.c museum.c
HEADERS = museum.h
OBJECTS = $(SOURCES:.c=.o)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
.PHONY: clean
CC = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -Wno-unused-parameter

default:
	$(CC) $(CFLAGS) psumemory.c $(SOURCE) -o memory_project

clean:
	rm memory_project
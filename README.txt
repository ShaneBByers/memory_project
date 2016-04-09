Shane Byers

CMPSC 473 Project 2: Design and evaluation of a user-space memory allocator

11/12/2015

TO RUN:
For first test file:
	make
	./project2
For following test files:
	Open makefile
		Uncomment test file to be used line of code
		Comment out unused test file lines of code
	make
	./project2

This program emulates a memory allocation system including malloc and free. When the caller requests a block of memory, it will call psumalloc which returns a pointer to a block of memory. When the caller is finished using the pointer, it will free it by calling psufree to allow other programs to use that memory. This program simulates a simplified version of all of the functions of malloc and free by utilizing a linked list of free nodes.

Shane Byers

CMPSC 473 Project 2: Design and evaluation of a user-space memory allocator

11/12/2015

TO RUN:
For first test file:
	make
	./a.out
For following test files:
	Open Makefile
		Uncomment test file to be used line of code
		Comment out unused test file lines of code
	make
	./project2

This program emulates a memory allocation system including malloc and free. When the caller requests a block of memory, it will call psumalloc which returns a pointer to a block of memory. When the caller is finished using the pointer, it will free it by calling psufree to allow other programs to use that memory. This program simulates a simplified version of all of the functions of malloc and free by utilizing a linked list of free nodes.

The project consisted of writing the entirety of the psumemory.c file. All other files were provided already completed. The other files exist as a wrapper around psumemory.h and psumemory.c to be able to automatically test the functionality of the written code.

KNOWN ISSUES:

Still need to clean up the code somewhat and possibly modify the output system to include total elapsed time and some other useful information for that specific run of the program.

There are still a couple bugs present whenever the program will seemingly randomly finish with obscure outputs in a small number of cases.

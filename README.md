Shane Byers

CMPSC 473 Project 2: Design and evaluation of a user-space memory allocator

11/12/2015

TO RUN:

> make SOURCE=<path_to_input_file>

> ./memory_project

EXAMPLE:

> make SOURCE=input_files/small_symmetric_worst.c

> ./memory_project

There are eight input files that can be used for testing.
Large Asymmetric Best
Large Asymmetric Worst
Large Symmetric  Best
Large Symmetric  Worst
Small Asymmetric Best
Small Asymmetric Worst
Small Symmetric  Best
Small Symmetric  Worst

Large vs. Small indicates the number of pointers and size of space requested during the malloc and free process.
Asymmetric vs. Symmetric indicates the efficiency that the requests for malloc and free are created.
Best vs. Worst indicates the "best-case" and "worst-case" scenarios for how much free space is available at any given point.

This program emulates a memory allocation system including malloc and free. When the caller requests a block of memory, it will call psumalloc which returns a pointer to a block of memory. When the caller is finished using the pointer, it will free it by calling psufree to allow other programs to use that memory. This program simulates a simplified version of all of the functions of malloc and free by utilizing a linked list of free nodes.

The project consisted of writing the entirety of the psumemory.c file. All other files were provided already completed. The other files exist as a type of wrapper around psumemory.h and psumemory.c to be able to automatically test the functionality of the written code.

KNOWN ISSUES:

Still need to clean up the code somewhat and possibly modify the output system to include total elapsed time and some other useful information for that specific run of the program.

There are still a couple bugs present whenever the program will seemingly randomly finish with obscure outputs in a small number of cases.

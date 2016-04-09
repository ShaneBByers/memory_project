#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>

/* A free node in the linked list */
typedef struct __node_t {
	int size;
	struct __node_t *next;
} node_t;

/* A header that appears before a pointer to describe the pointer's size and a magic number to ensure security */
typedef struct __header_t {
	int size;
	int magic;
} header_t;

// The head of the free node list
node_t *head;

// The algorithm to be used by psumalloc
// Algo == 0 -> Best-Fit
// Algo == 1 -> Worst-Fit
int algo;

// The maximum size of the memory space
int max_size;

int psumeminit(int, int);
void psumemdump();
void combine_free();
node_t * best_fit_finder(int);
node_t * worst_fit_finder(int);
void *psumalloc(int);
int psufree(void *);


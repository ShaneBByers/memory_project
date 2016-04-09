#include "psumemory.h"

int psumeminit(int algo_code, int region_size) {
	head = mmap(NULL, region_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	head->size = region_size - sizeof(node_t);
	head->next = NULL;
	algo = algo_code;
	max_size = head->size;
	return 0;
}

/* Displays free node list information */
void psumemdump() {
	printf("----BEGIN OUTPUT----\n");
	printf("Head Address:%p\n",head);
	printf("$$Free Nodes$$\n");
	node_t * temp_node = head;
	int counter = 0;
	while(temp_node) {
		printf("Node %d:\n",counter);
		printf("  Location: %p\n",temp_node);
		printf("  Size: %d\n",temp_node->size);
		temp_node = temp_node->next;
		counter++;
	}
	printf("----END   OUTPUT----\n\n\n");
}

/* Coalesces free nodes if they are adjascent*/
void combine_free() {
	node_t * loop_node = head;
	node_t * curr_node;
	node_t * prev_node = NULL;
	// Loops through all of the nodes
	while(loop_node) {
		int loop_node_size = loop_node->size;
		curr_node = head;
		// Each node gets compared to every other node
		while(curr_node) {
			if(curr_node == head) {
				prev_node = NULL;
			}
			// If the two nodes being examined are adjascent
			if(curr_node == ((void *)loop_node + loop_node_size)) {
				loop_node->size = loop_node->size + curr_node->size;
				if(!prev_node && curr_node->next) {
					head = curr_node->next;
				} else if(!prev_node && !curr_node->next) {
				} else {
					prev_node->next = curr_node->next;
				}
				loop_node = head;
				curr_node = head;
			} else {
				prev_node = curr_node;
				curr_node = curr_node->next;
			}
		}
		loop_node = loop_node->next;
	}
}

/* Finds the best-fit node in the free node list */
node_t * best_fit_finder(int size) {
	node_t * temp_node = head;
	node_t * best_fit_node = NULL;
	int best_size_diff = max_size;
	int size_diff;
	// Loops through every node in the list
	while(temp_node) {
		size_diff = temp_node->size - (signed int)(size + sizeof(header_t));
		// If the size difference of the new node vs. the requested size is less than the best-fit size
		if(size_diff >= 0 && size_diff < best_size_diff) {
			best_fit_node = temp_node;
			best_size_diff = best_fit_node->size - (signed int)(size + sizeof(header_t));
		}
		temp_node = temp_node->next;
	}
	return best_fit_node;
}

/* Finds the worst-fit node in the free node list */
node_t * worst_fit_finder(int size) {
	node_t * temp_node = head;
	node_t * worst_fit_node = NULL;
	int worst_size_diff = -1;
	int size_diff;
	// Loops through every node in the list
	while(temp_node) {
		size_diff = temp_node->size - (signed int)(size + sizeof(header_t));
		// If the size difference of the new node vs. the requested size is greater than the worst-fit size
		if(size_diff >= 0 && size_diff > worst_size_diff) {
			worst_fit_node = temp_node;
			worst_size_diff = worst_fit_node->size - (signed int)(size + sizeof(header_t));
		}
		temp_node = temp_node->next;
	}
	return worst_fit_node;
}

/* Gives the caller a pointer to a chunk of free memory that is taken off the free node list */
void *psumalloc(int size) {
	if(size > (signed int)(max_size - sizeof(header_t))) {
		return NULL;
	}
	node_t * temp_node;
	// Algo == 0 -> Best-Fit
	// Algo == 1 -> Worst-Fit
	if(algo == 0) {
		temp_node = best_fit_finder(size);
	} else {
		temp_node = worst_fit_finder(size);
	}
	if(!temp_node) {
		return NULL;
	}
	void * return_ptr = (void *)temp_node + sizeof(header_t);
	node_t * loop_node = head;
	node_t * prev_node = NULL;
	// Find the correct node in the list with the previous node pointing to it
	while(loop_node != temp_node) {
		prev_node = loop_node;
		loop_node = loop_node->next;
	}
	header_t * header;
	int temp_size = loop_node->size;
	node_t * temp_next = loop_node->next;
	// Create the header that holds information on the pointer to be returned
	header = (header_t *)loop_node;
	header->size = size;
	header->magic = 473;
	// If currently not at the head of the list
	if(prev_node) {
		loop_node = (node_t *)((void *)loop_node + sizeof(header_t) + size);
		prev_node->next = loop_node;
		loop_node->size = temp_size - sizeof(header_t) - size;
		loop_node->next = temp_next;
	// If currently at the head of the list
	} else {
		head = (node_t *)((void *)head + sizeof(header_t) + size);
		head->size = temp_size - sizeof(header_t) - size;
		head->next = temp_next;
	}
	return return_ptr;
}

/* Puts the passed in ptr back into the free node list, if it exists */
int psufree(void *ptr) {
	if(!ptr) {
		return -1;
	}
	node_t * temp_head = head;
	// Get the header information for the pointer
	header_t * header = (header_t *)((void *)ptr - sizeof(header_t));
	assert(header->magic==473);
	// Put the node onto the head of the free node list
	head = (node_t *)header;
	head->size = header->size + sizeof(header_t);
	head->next = temp_head;
	// Coalesce all of the adjascent free nodes
	combine_free();
	return 0;
}

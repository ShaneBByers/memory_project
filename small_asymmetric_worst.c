//
//  main.c
//  Cmpsc473p2
//
//  Created by Chen Chen on 3/21/15.
//  Copyright (c) 2015 Chen Chen. All rights reserved.
//

#define NUM 100
#include <stdio.h>
#include <time.h>
#include "psumemory.h"

#define NUM 100

typedef struct _test{
    int a;
    char one;
    char two;
} test;

void write_test(test* ptr){
    if (ptr == NULL){
        return;
    }
    ptr->a = 1;
    ptr->one = 'A';
    ptr->two = 'B';
}

void read_test(test* ptr, FILE* f){
    if (ptr == NULL){
        return;
    }
    fprintf(f, "This struct contains: %d, %c and %c. \n", ptr->a, ptr->one, ptr->two);
}

int main(){
    FILE* f = fopen ("test_output6.txt", "w");
    int size;
    int sizeOfRegion = 1 << 20;// 1MB
	int malloccounter = 0;
	int freecounter = 0;
    int a = psumeminit(1, sizeOfRegion);
    if (a == -1){
        fprintf(f, "Initialization failed!\n");
    }
    
    void* pointer_array[16][NUM];
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < NUM; j++){
            pointer_array[i][j] = NULL;
        }
    }

    for (int i = 0; i < 16; i++){
        for (int j = 0; j < NUM; ++j)
        {
            size = rand()%248 + 8;
			long long unsigned int diff;
			struct timespec start, end;

			clock_gettime(CLOCK_MONOTONIC, &start);
            test* a = (test*)psumalloc(size);
			clock_gettime(CLOCK_MONOTONIC, &end);

			diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
			printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
            write_test(a);
            read_test(a, f);
            if (a == NULL){
				malloccounter++;
                fprintf(f, "No. %d: No extra space for allocation in memory!\n", j);
            }
            else{
                pointer_array[i][j] = a;
                fprintf(f, "NO.%d chunk has been allocated, the size is %d bytes\n", j, size);
            }
        }
    }
    
    int half = 16;
    while (half != 0){
        half /= 2;
        int bound;
        if (half){
            bound = half * 2;
        }
        else{
            bound = 1;
        }
        for (int i = half; i < bound ; i++){
            for (int j = 0; j < NUM; j++)
            {
                
				
			int a = psufree(pointer_array[i][j]);
			
                if (a == 0){
                    fprintf(f, "No.%d chunk has been freed. \n", j);
                }
                else{
					freecounter++;
                    fprintf(f, "Can not free No.%d chunk. \n", j);
                }
            }
        }
    }
    fclose(f);
	printf("MALLOC: %d\nFREE: %d\n",malloccounter,freecounter);
    return 0;
}

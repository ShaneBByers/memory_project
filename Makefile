default:
	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter small_asymmetric_best.c psumemory.h psumemory.c

clean:
	rm project2
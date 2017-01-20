default:
	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter small_asymmetric_best.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter small_asymmetric_worst.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter small_symmetric_best.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter small_symmetric_worst.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter large_asymmetric_best.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter large_asymmetric_worst.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter large_symmetric_best.c psumemory.h psumemory.c

#	gcc -g -std=gnu99 project2 -Wall -Wextra -Wno-unused-parameter large_symmetric_worst.c psumemory.h psumemory.c

clean:
	rm project2

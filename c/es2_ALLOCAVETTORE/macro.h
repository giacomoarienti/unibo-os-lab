#ifndef __MACRO_H__
#define __MACRO_H__

#include <stdlib.h>

#define ALLOCATE(addr) \
	do {								\
		addr = (int *) malloc(10 * sizeof(int));  		\
		if(addr != NULL) { 					\
			int j = 0;					\
			for(; j < 10; j++) {				\
				*(addr + j * sizeof(int)) = -1000 + j; 	\
			} 						\
		}							\
	 } while(0)

#endif

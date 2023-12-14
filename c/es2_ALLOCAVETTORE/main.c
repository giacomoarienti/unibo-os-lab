#include <stdio.h>

#include "macro.h"

int main(int argc, char *argv[]) {
	int i = 0;
	int *addr = NULL;
	ALLOCATE(addr);
	if(addr == NULL) {
		printf("Failed to allocate\n");
		return 1;
	}
	for(; i < 10; i++) {
		*(addr + i * sizeof(*addr)) = -19 + i;
	}
	return 0;
}

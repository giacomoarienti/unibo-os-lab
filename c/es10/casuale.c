#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	do{
		if(rand() % 10 == 3) return 0;
	} while(1);
}

#include <stdlib.h>
#include <time.h>

int dammi_il_precedente(unsigned int num) {
	static int precedente = 0;
	int res = precedente;
	precedente = num;
	return res;
}

int main() {
	srand(time(NULL));
	do{
		if(dammi_il_precedente(rand()) % 10 == 3) return 0;
	}while(1);
}

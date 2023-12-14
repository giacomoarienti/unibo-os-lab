#include <stdio.h>

#include "quadrato.h"
#include "dimezza.h"

static double salva;

int main(int argc, char *argv[]) {
	const int num = 13.17;
	salva = quadrato(dimezza(num));
	printf("%f\n", salva);
	return 0;
}

#include "dimezza.h"

static double salva;

double dimezza(double arg) {
	double res = cos(arg) / 2;
	salva = res;
	return res;
}


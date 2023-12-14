#include "quadrato.h"

static double salva;

double quadrato(double arg) {
	double res = arg * arg;
	salva = res;
	return res;
}

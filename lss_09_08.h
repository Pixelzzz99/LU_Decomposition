#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef LSS_09_08_CPP
#define LSS_09_08_CPP

int debug;
int errors;
const double EPSILON;

size_t lss_memsize_09_08(int n);
int lss_09_08(int n, double *A, double *B, double *X);
#endif

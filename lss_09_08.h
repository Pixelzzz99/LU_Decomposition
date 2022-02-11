#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int lss_09_08(FILE *fin, FILE *fout, int debug, int print_mode);
double** readmatrix(int rows, int cols, FILE *file);
double* readvector(int n, FILE *file);
void print(const char* message, int n, double** matrix);
void printVector(const char* message, int n, double* vector);


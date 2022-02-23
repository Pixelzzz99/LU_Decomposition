#include "lss_09_08.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_matrix(double *A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%lf ", A[i * n + j]);
        }
        printf("\n");
    }
}

void print_vector(double *B, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%lf ", B[i]);
    }
    printf("\n");
}

int readMatrix(FILE *file, int n, double** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(!fscanf(file, "%lf", &(*A)[i * n + j]))
            {
                return 0;
            }
        }
    }
    return 1;
}

int readVector(FILE *file, int n, double* b)
{
    for (int i = 0; i < n; i++)
    {
        if(!fscanf(file, "%lf", &b[i]))
        {
            return 0;
        }
    }
    return 1;
}

void help()
{
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n"
            "OPTIONS\n"
            "-d\t"
            "debug mode [default OFF]\n"
            "-e\t"
            "errors [default OFF]\n"
            "-p\t"
            "print matrix [default OFF]\n"
            "-t\t"
            "print execution time [default OFF]\n"
            "-h -?\t"
            "print this help\n"
            "Default input file name \"lss_09_07_in.txt\"\n"
            "Default output file name \"lss_09_07_out.txt\"\n");
}

int is_empty_file(FILE * file)
{
    int c = getc(file);
    if(c == EOF)
    {
        return 1;
    }
    ungetc(c, file);
    return 0;
}

/*
 * A = matrix which read from file
 * B = vector
 * n = size of matrix
 */
int readFile(int* n, double** A, double** B, FILE* file)
{
    if(is_empty_file(file))
    {
        if(errors)
        {
            fprintf(stderr, "Error: empty file\n");
        }
        fclose(file);
        return -4;
    }
    if(!fscanf(file, "%d", n))
    {
        if(errors)
        {
            fprintf(stderr, "Error: wrong format\n");
        }
        fclose(file);
        return -5;
    }
    if(*n < 1)
    {
        if(errors)
        {
            fprintf(stderr, "Error: wrong size\n");
        }
        fclose(file);
        return -5;
    }

    //malloc matrix
    *A = (double*)malloc((*n) * (*n) * sizeof(double));
    //malloc vector
    *B = (double*)malloc(*n * sizeof(double));

    //read matrix
    if(!readMatrix(file, *n, A))
    {
        if(errors)
        {
            fprintf(stderr, "Error: wrong format\n");
        }
        fclose(file);
        return -5;
    }
    //read vector
    if(!readVector(file, *n, *B))
    {
        if(errors)
        {
            fprintf(stderr, "Error: wrong format\n");
        }
        fclose(file);
        return -5;
    }

    fclose(file);
    if(debug)
    {
        printf("Read file success\n");
    }
    return 0;
}

int writeFile(int n, double* x, FILE* file, int status_code)
{
    if(!status_code)
    {
        fprintf(file, "%d\n", n);
        for(int i = 0; i < n; i++)
        {
            fprintf(file, "%1.9lf\n", x[i]);
        }
    }
    else{
        fprintf(file, "%d\n", 0);
    }
    if(debug)
    {
        printf("Write file success\n");
    }
}
int main(int argc, char **argv)
{
    FILE *fin;
    FILE *fout;
    int print = 0;
    int time = 0;
    int count_files = 0;

    for (int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            if(argv[i][1] == 'd')
            {
                debug = 1;
            }
            else if(argv[i][1] == 'e')
            {
                errors = 1;
            }
            else if(argv[i][1] == 'p')
            {
                print = 1;
            }
            else if(argv[i][1] == 't')
            {
                time = 1;
            }
            else if(argv[i][1] == 'h' || argv[i][1] == '?')
            {
                help();
            }
            else
            {
                if(errors)
                {
                    fprintf(stderr, "Error: wrong option\n");
                }
                exit(-3);
            }
        }
        else
        {
            if(i == 1)
            {
                fin = fopen(argv[i], "r");
                count_files++;
            }
            else if(i == 2)
            {
                fout = fopen(argv[i], "w");
                count_files++;
            }
            else
            {
                if(errors)
                {
                    fprintf(stderr, "Error: wrong option\n");
                }
                exit(-3);
            }
        }
    }

    if(count_files == 0)
    {
        if((fin = fopen("lss_09_08_in.txt", "r")) == NULL)
        {
            fprintf(stderr, "Failed to open input file \n");
        }
        if((fout = fopen("lss_09_08_out.txt", "w")) == NULL)
        {
            fprintf(stderr, "Failed to open output file");
        }
    }
    else if(count_files == 1)
    {
        if(errors == 1)
        {
            fprintf(stderr, "You have added 1 file");
        }
        exit(-6);
    }

    int n;
    double *A, *B, *X;
    int readFileStatus = readFile(&n, &A, &B, fin);
    if(readFileStatus == -4)
    {
        if(errors == 1)
        {
            fprintf(stderr, "Error: empty file\n");
        }
        fclose(fout);
        return -4;
    }
    else if(readFileStatus == -5)
    {
        if(errors == 1)
        {
            fprintf(stderr, "Error: wrong format\n");
        }
        fclose(fout);
        return -5;
    }

    if(print)
    {
        print_matrix(A, n);
        print_vector(B, n);
    }
    X = (double*)malloc(n * sizeof(double));
    clock_t start = clock();
    int status_code = lss_09_08(n, A, B, X);
    clock_t end = clock();

    free(A);
    free(B);
    if(status_code == -1)
    {
        if (time)
            printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
        fclose(fout);
        free(X);
        return -1;
    }

    if(print)
    {
        print_vector(X, n);
    }
    writeFile(n, X, fout, status_code);

    if (time)
        printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(fout);
    free(X);
    return 0;
}

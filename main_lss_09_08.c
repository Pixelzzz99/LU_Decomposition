/*#include "lss_09_08.h"*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int debug = 0;
int errors = 0;

void print(const char *message, int n, double** matrix)
{
    printf("%s\n", message);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printVector(const char *message, int n, double* vector)
{
    printf("%s\n", message);
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", vector[i]);
    }
    printf("\n");
}

int readMatrixFromFile(FILE *file, int n, double** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(!fscanf(file, "%lf", &matrix[i][j]));
            {
                return 1;
            }
        }
    }
    return 0;
}

int readVectorFromFile(FILE *file, int n, double** vector)
{
    for (int i = 0; i < n; i++)
    {
        if(!fscanf(file, "%lf", &vector[i]));
        {
            return 1;
        }
    }
    return 0;
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

int len(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int word_eq(const char *word1, const char *word2)
{
    int len_word1 = len(word1);
    int len_word2 = len(word2);
    if (len_word1 != len_word2)
        return -1;
    for (int i = 0; i < len_word1; i++)
        if (word1[i] != word2[i])
            return -1;

    return 0;
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

    if(readMatrixFromFile(file, *n, A)){
        if(errors)
        {
            fprintf(stderr, "Error: wrong format A matrix\n");
        }
        fclose(file);
        return -5;
    }
    if(readVectorFromFile(file, *n, B))
    {
        if(errors)
        {
            fprintf(stderr, "Error: wrong format B vector\n");
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

int main(int argc, char **argv)
{
    FILE *fin;
    FILE *fout;
    int print = 0;
    int time = 0;
    int count_files = 0;

    for (int i = 1; i < argc; i++)
    {
        if (!word_eq(argv[i], "-h") || !word_eq(argv[i], "-?"))
        {
            help();
        }
        else if (!word_eq(argv[i], "-d"))
        {
            debug = 1;
        }
        else if (!word_eq(argv[i], "-e"))
        {
            errors = 1;
        }
        else if (!word_eq(argv[i], "-p"))
        {
            print = 1;
        }
        else if (!word_eq(argv[i], "-t"))
        {
            time = 1;
        }
        else if (argv[i][0] != '-')
        {
            if (i == 1)
            {
                fin = fopen(argv[i], "r");
                count_files++;
            }
            else if (i == 2)
            {
                fout = fopen(argv[i], "w");
                count_files++;
            }
            else if (errors == 1)
            {
                fprintf(stderr, "No such command");
                exit(-3);
            }
        }
        else
        {
            if (errors == 1)
            {
                fprintf(stderr, "No such command");
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
    
    clock_t start = clock();
    /*int status_code = lss_09_08(n, A, B, &X);*/
    clock_t end = clock();

    /*if (status_code == -1)*/
    /*{*/
        /*if (time){*/
            /*printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);*/
        /*}*/
        /*return -1;*/
    /*}*/
    /*if (status_code == 0){*/
        /*fprintf(fout, "%d\n", n);*/
    /*}*/

    if (time)
        printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

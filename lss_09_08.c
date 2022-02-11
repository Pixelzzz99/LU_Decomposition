#include "lss_09_08.h"

double** readmatrix(int rows, int cols, FILE *file)
{
    double **A;
    A = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        A[i] = (double*)malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++)
        {
            double temp = 0;
            fscanf(file, "%lf", &temp);
            A[i][j] = temp;
        }
    }
    return A;
}

double* readvector(int n, FILE *file)
{
    double *b;
    b = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        double temp = 0;
        fscanf(file, "%lf", &temp);
        b[i] = temp;
    }
    return b;
}

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

int lss_09_08(FILE *fin, FILE *fout, int debug, int print_mode)
{
    double eps=1e-14;
    int n;
    double sum = 0;
    // read n size
    fscanf(fin, "%d", &n);
    // read matrix A and vector B
    double** A = readmatrix(n, n, fin);
    double* B = readvector(n, fin);
    if (print_mode)
    {
        print("A", n, A);
        printVector("B", n, B);
    }

    double **L = (double**)malloc(n * sizeof(double*));
    double **U = (double**)malloc(n * sizeof(double*));
    double *X = (double*)malloc(n * sizeof(double));
    
    // LU decomposition
    for(int i = 0; i < n; i++)
    {
        L[i] = (double*)malloc(n * sizeof(double));
        U[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            L[i][j]=0;
            U[i][j]=0;
            if(i == j) U[i][j] = 1;
        }
    }
    
    //Находим первый столбец L[][] и первую строку U[][]
    for(int i = 0; i < n; i++)
    {
        X[i] = 0;
        L[i][0] = A[i][0];
        U[0][i] = A[0][i] / L[0][0];
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            sum = 0;
            for(int k = 0; k < i; k++)
            {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = A[j][i] - sum;
        }

        for(int j = i; j < n; j++)
        {
            sum = 0;
            for(int k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
            if(fabs(L[i][i]-0) > eps)
            {
                U[i][j] = U[i][j] / L[i][i];
            }
            else return -1;
        }
    }
       
    if(debug){
        print("L:", n, L);
        print("U:", n, U);
    }
    
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        for(int j = 0; j < i; j++)
        {
            sum += L[i][j] * X[j];
        }
        X[i] = (B[i] - sum)/L[i][i];
    }

    for(int i= n - 1; i >= 0; i--)
    {
        sum = 0;
        for(int j = i + 1; j < n; j++)
        {
            sum += U[i][j] * X[j];
        }
        X[i] = (X[i] - sum)/U[i][i];
    }
    
    if(print_mode){
        printVector("X:", n, X);
    }

    fprintf(fout, "%d\n", X[0]);
    // print result
    for(int i = 0; i < n; i++)
    {
        fprintf(fout, "%1.9lf\n", X[i]);
    }

    return 0;
}


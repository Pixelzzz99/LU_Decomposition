#include "lss_09_08.h"

int lss_09_08(int n, double *A, double*B, double* X)
{
    double eps=1e-14;
    int n;
    double sum = 0;
    
    if(is_empty_file(fin))
    {
        fclose(fin);
        return -4;
    }

    // read n size
    if(!fscanf(fin, "%d", &n)) 
    {
        fclose(fin);
        return -5;
    }

    if(n <= 0)
    {
        fclose(fin);
        return -5;
    }

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


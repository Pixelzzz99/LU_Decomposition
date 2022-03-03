#include "lss_09_08.h"

int is_equal(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

//A is matrix of size n x n
//B is vector of size n
//X is vector of size n
int lss_09_08(int n, double *A, double*B, double* X)
{
    double sum = 0;
    if(n == 1)
    {
        if(is_equal(A[0], 0))
        {
            if(errors) fprintf(stderr, "Error: not applicable for this system\n");
            return -1;
        }
        X[0] = B[0] / A[0];
        if(debug) printf("System solution is X[0] = %lf\n", X[0]);
        return 0;
    }
    
    
    double **L = (double**)malloc(n * sizeof(double*));
    double **U = (double**)malloc(n * sizeof(double*));

    // LU decomposition
    // Строим матрицу L
    // Строим матрицу U
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
        L[i][0] = A[i*n];
        U[0][i] = A[i] / L[0][0];
    }

    //Находим остальные столбцы L[][] и строки U[][]
    for(int i = 1; i < n; i++)
    {
        //L матрица находится в правой части матрицы A
        for(int j = i; j < n; j++)
        {
            sum = 0;
            for(int k = 0; k < i; k++)
            {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = A[j * n + i] - sum;
        }
        //U матрица находится в левой части матрицы A
        for(int j = i; j < n; j++)
        {
            sum = 0;
            for(int k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i * n + j] - sum;
            //условие для необходимости преобразования матрицы
            if(fabs(L[i][i]-0) > EPSILON)
            {
                U[i][j] = U[i][j] / L[i][i];
            }
            else return -1;
        }
    }

    //Находим вектор X
    //Ly = B
    for(int i = 0; i < n; i++)
    {
        sum = 0;
        for(int j = 0; j < i; j++)
        {
            sum += L[i][j] * X[j];
        }
        //y = B/L
        X[i] = (B[i] - sum)/L[i][i];
    }
    //Ux = y
    for(int i= n - 1; i >= 0; i--)
    {
        sum = 0;
        for(int j = i + 1; j < n; j++)
        {
            sum += U[i][j] * X[j];
        }
        //x = y/U
        X[i] = (X[i] - sum)/U[i][i];
    }

    return 0;
}


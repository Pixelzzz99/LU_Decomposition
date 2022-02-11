#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


void readmatrix(int rows, int cols, FILE *file)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double temp;
            fscanf(file, "%d", &temp);
            arr[i][j] = temp;
        }
    }
}

void print(char *str, int n, double matrix[n][n])
{
    printf("%s\n", str);
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

int main()
{
    FILE *file;
    file = fopen("input.txt", "r");
    if (file == NULL) return 0;
    
    int n;
    double sum = 0;

    fscanf(file, "%d", &n);
    printf("%d\n", n);
    
    double A[n][n];
    readmatrix(n, n, file);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            double temp = A[i][j];
            printf("%lf", );
        }
    }

    double L[n][n];
    double U[n][n];
    

    //Заполняем матрицу
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            L[i][j]=0;
            U[i][j]=0;
            if(i == j) U[i][j] = 1;
        }
    }

    print("L:", n, L);
    print("U:", n, U);

    //Находим первый столбец L[][] и первую строку U[][]
    for(int i = 0; i < n; i++)
    {
        L[i][0] = A[i][0];
        U[0][i] = A[0][i] / L[0][0];
    }

    print("L:", n, L);
    print("U:", n, U);

    
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; i < n; i++)
        {
            if(i >= j)
            {
                sum = 0;
                for(int k = 0; k < j; k++)
                {
                    sum += L[i][k] * U[k][j];
                }
                L[i][j] = A[i][j] - sum;
            }
            else
            {
                sum = 0;
                for(int k = 0; k < i; k++)
                {
                    sum += L[i][k] * U[k][j];
                }
                U[i][j] = (A[i][j] - sum)/L[i][i];
            }
        }
    }
    print("L:", n, L);
    print("U:", n, U);


    return 0;
}


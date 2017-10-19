// Copyright 2017 Georgy Shapchits <gogi.soft.gm@gmail.com> legal

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include "mpi.h"
#include "matrix.c"

#define MATRIX_A_PATH "data/A.csv"
#define MATRIX_B_PATH "data/B.csv"
#define MATRIX_C_PATH "data/C.csv"

int main(int args, char **argc)
{
    int **matrix_a;
    int **matrix_b;
    int **matrix_c;
    int rows, columns, code = 0;

    code = get_matrix_size(MATRIX_A_PATH, &rows, &columns);
    if (code != 0)
    {
        return code;
    }

    code = read_matrix(&matrix_a, MATRIX_A_PATH, rows, columns);
    if (code != 0)
    {
        return code;
    }

    code = read_matrix(&matrix_b, MATRIX_B_PATH, rows, columns);
    if (code != 0)
    {
        return code;
    }

    code = create_matrix(&matrix_c, rows, rows);

#pragma omp parallel
#pragma omp for
    for (int i = 0; i < rows; i++)
    {
#pragma omp for
        for (int j = 0; j < columns; j++)
        {
            int sum = 0;
#pragma omp for
            for (int k = 0; k < rows; k++)
            {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_c[i][j] = sum;
        }
    }

    free(matrix_a);
    free(matrix_b);

    write_matrix(matrix_c, MATRIX_C_PATH, rows, rows);

    free(matrix_c);

    return 0;
}
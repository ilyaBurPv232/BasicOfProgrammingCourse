#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void inputArray(int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

void outputArray(const int *const a, const size_t n) {
    printf("|");
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\b|\n");
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);

    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; ++i)
        free(m->values[i]);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i)
        freeMemMatrix(&ms[i]);
    free(ms->values);
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; ++i) {
        inputArray(m->values[i], m->nCols);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        outputArray(m.values[i], m.nCols);
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i)
        inputMatrix(&ms[i]);
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i)
        outputMatrix(ms[i]);
}

void swapRows(matrix *m, int i1, int i2) {
    assert(i1 < m->nRows || i2 < m->nRows);

    int *temp = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = temp;
}

void swapColumns(matrix *m, int j1, int j2) {
    assert(j1 < m->nCols || j2 < m->nCols);

    for (int i = 0; i < m->nRows; ++i) {
        int temp = m->values[i][j1];
        m->values[i][j1] = m->values[i][j2];
        m->values[i][j2] = temp;
    }
}

int getSum(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += a[i];

    return sum;
}

void insertionSortRowsMatrixByRowCriteria(matrix *m,
                                          int (*criteria)(int *, int)) {
    int temp[m->nRows];
    int mem_num;
    for (int i = 0; i < m->nRows; ++i) {
        int res = criteria(m->values[i], m->nCols);
        temp[i] = res;
    }

    int min_idx;
    for (int j = 0; j < m->nRows; ++j) {
        min_idx = j;
        for (int i = j + 1; i < m->nRows; ++i) {
            if (temp[i] < temp[min_idx]) {
                min_idx = i;
            }
        }
        if (min_idx != j) {
            mem_num = temp[j];
            temp[j] = temp[min_idx];
            temp[min_idx] = mem_num;

            swapRows(m, j, min_idx);
        }
    }
}

void selectionSortColsMatrixByColCriteria(matrix *m, int (*criteria)(int *, int)) {
    int temp[m->nCols];
    for (int i = 0; i < m->nCols; ++i) {
        int temp_column[m->nRows];
        for (int j = 0; j < m->nRows; ++j)
            temp_column[j] = m->values[j][i];


        int result = criteria(temp_column, m->nCols);
        temp[i] = result;
    }

    int min_pos, temp_pos;
    for (int i = 0; i < m->nCols; i++) {
        min_pos = i;
        for (int j = i + 1; j < m->nCols; j++)
            if (temp[min_pos] > temp[j])
                min_pos = j;
        temp_pos = temp[min_pos];
        temp[min_pos] = temp[i];
        temp[i] = temp_pos;

        swapColumns(m, min_pos, i);
    }
}
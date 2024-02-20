#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <memory.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

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
    free(m->values);
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
    printf("\n");
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

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols)
        return false;
    for (int i = 0; i < m1->nRows; ++i) {
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m2->nCols) != 0)
            return false;
    }
    return true;
}

bool isEMatrix(matrix *m) {
    if (!isSquareMatrix(m))

        return false;
    else {

        for (int i = 0; i < m->nRows; ++i) {
            for (int j = 0; j < m->nCols; ++j) {
                if (i != j) {
                    if (m->values[i][j] != 0)

                        return false;

                } else if (m->values[i][j] != 1)

                    return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m))

        return false;
    else {
        for (int i = 0; i < m->nRows; ++i) {
            for (int j = 0; j < m->nCols; ++j) {
                if (i != j && m->values[i][j] != m->values[j][i])

                    return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix *m) {
    matrix temp = getMemMatrix(m->nRows, m->nCols);
    for (int i = 0; i < m->nRows; ++i) {
        for (int j = 0; j < m->nCols; ++j) {
            temp.values[j][i] = m->values[i][j];
        }
    }
    m->values = temp.values;
}

void transposeMatrix(matrix *m) {
    matrix temp = getMemMatrix(m->nCols, m->nRows);
    for (int i = 0; i < m->nRows; ++i) {
        for (int j = 0; j < m->nCols; ++j) {
            temp.values[j][i] = m->values[i][j];
        }
    }
    swap(&m->nRows, &m->nCols);
    m->values = temp.values;

}

position getMinValuePos(matrix m) {
    position p = {0, 0};
    int min = m.values[0][0];
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {

            if (min > m.values[i][j]) {
                min = m.values[i][j];
                p.rowIndex = i;
                p.colIndex = j;
            }
        }
    }
    return p;
}

position getMaxValuePos(matrix m) {
    position p = {0, 0};
    int max = m.values[0][0];
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {

            if (max < m.values[i][j]) {
                max = m.values[i][j];
                p.rowIndex = i;
                p.colIndex = j;
            }
        }
    }
    return p;
}
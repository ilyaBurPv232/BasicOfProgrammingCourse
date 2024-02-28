#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>
#include <stdbool.h>

void task1(matrix *m) {
    int min = getMinValuePos(*m).rowIndex;
    int max = getMaxValuePos(*m).rowIndex;

    swapRows(m, max, min);
}

void test_task1() {
    matrix m = createMatrixFromArray((int[]) {1, 1, 1,
                                              2, 2, 2,
                                              3, 3, 3},
                                     3, 3);

    matrix m_test = createMatrixFromArray((int[]) {3, 3, 3,
                                                   2, 2, 2,
                                                   1, 1, 1},
                                          3, 3);

    task1(&m);

    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

int getMax(int *a, int n) {
    int max = a[0];

    for (int i = 1; i < n; ++i) {
        max = max > a[i] ? max : a[i];
    }

    return max;
}

void sortRowsByMinElement(matrix *m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void task2(matrix *m) {
    sortRowsByMinElement(m);
}

void test_task2() {
    matrix m = createMatrixFromArray((int[]) {12, 9, 9,
                                              11, 9, 9,
                                              10, 9, 9},
                                     3, 3);

    matrix m_test = createMatrixFromArray((int[]) {10, 9, 9,
                                                   11, 9, 9,
                                                   12, 9, 9},
                                          3, 3);

    task2(&m);

    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

int getMin(int *a, int n) {
    int min = a[0];

    for (int i = 1; i < n; ++i) {
        min = min < a[i] ? min : a[i];
    }

    return min;
}

void sortColsByMinElement(matrix *m) {
    selectionSortColsMatrixByColCriteria(m, getMin);
}

void task3(matrix *m) {
    sortColsByMinElement(m);
}

void test_task3() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 2, 4, 3, 3,
                                              2, 5, 1, 8, 2, 7,
                                              6, 1, 4, 4, 8, 3},
                                     3, 6);
    matrix m_test = createMatrixFromArray((int[]) {5, 2, 3, 3, 3, 4,
                                                   5, 1, 2, 2, 7, 8,
                                                   1, 4, 6, 8, 3, 4},
                                          3, 6);

    task3(&m);

    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nRows * m1.nCols == m2.nRows * m2.nCols);
    matrix result = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return result;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    assert(isSymmetricMatrix(m));
    matrix temp = mulMatrices(*m, *m);
    freeMemMatrix(m);
    *m = temp;
}

void task4(matrix *m) {
    getSquareOfMatrixIfSymmetric(m);
}

void test_task4() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 4, 5,
                                              3, 5, 6},
                                     3, 3);

    matrix m_test = createMatrixFromArray((int[]) {14, 25, 31,
                                                   25, 45, 56,
                                                   31, 56, 70},
                                          3, 3);

    task4(&m);

    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == a[j] &&  i != j)
                return false;
        }
    }
    return true;
}

/** изменена в самой библиотеке
long long getSum(int *a, int n){
    long long sum = 0;
    for (int i = 0; i < n; ++i)
        sum += a[i];

    return sum;
}
**/

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long temp_sum[m->nRows];
    for (int i = 0; i < m->nRows; ++i) {
        temp_sum[i] = getSum(m->values[i], m->nCols);
    }
    if (isUnique(temp_sum, m->nRows))
        transposeSquareMatrix(m);
}

void task5(matrix *m) {
    transposeIfMatrixHasNotEqualSumOfRows(m);
}

void test_task5() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},
                                     3, 3);

    matrix m_test = createMatrixFromArray((int[]) {1, 4, 7,
                                                   2, 5, 8,
                                                   3, 6, 9},
                                          3, 3);
    task5(&m);
    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

void test() {
    //test_task1();
    //test_task2();
    //test_task3();
    //test_task4();
    test_task5();
}

int main() {

    test();

    return 0;
}
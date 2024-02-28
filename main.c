#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>

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

void sortRowsByMinElement(matrix *m){
    insertionSortRowsMatrixByRowCriteria(m,getMax);
}

void task2(matrix *m){
    sortRowsByMinElement(m);
}

void test_task2(){
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

void sortColsByMinElement(matrix *m){
    selectionSortColsMatrixByColCriteria(m,getMin);
}

void task3(matrix *m){
    sortColsByMinElement(m);
}

void test_task3(){
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

void test(){
    //test_task1();
    //test_task2();
    test_task3();
}

int main() {

    test();

    return 0;
}
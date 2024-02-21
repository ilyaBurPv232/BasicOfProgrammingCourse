#include "libs/data_structures/matrix/matrix.h"
#include <assert.h>
#include <stdlib.h>


void test_getMemMatrix() {
    matrix m = getMemMatrix(2, 2);
    assert(m.nCols == 2 && m.nRows == 2);
    // проверка выделения памяти
    assert(m.values != NULL);
    freeMemMatrix(&m);

    // проверка на других входных данных
    m = getMemMatrix(2, 9);
    assert(m.nCols == 9 && m.nRows == 2);
    assert(m.values != NULL);

    //освобождаем память
    freeMemMatrix(&m);
}

void test_getMemArrayOfMatrices() {
    matrix *ms = getMemArrayOfMatrices(2, 2, 2);
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 2);
    //проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);

    ms = getMemArrayOfMatrices(9, 5, 2);
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 5);
    // проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);
}

void test_freeMemMatrix() {
    // создаем и чистим массив
    matrix m = getMemMatrix(2, 2);
    freeMemMatrix(&m);
    assert(m.values == NULL);

    //проверка на других данных
    m = getMemMatrix(3, 6);
    freeMemMatrix(&m);
    assert(m.values == NULL);
}

void test_swapRows() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {4, 5, 6,
                                              1, 2, 3,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 2, 3,
                                                   4, 5, 6},
                                           2, 3);
    swapRows(&m, 0, 1);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_swapColumns() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {4, 5, 6,
                                              1, 2, 3,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {5, 4, 6,
                                                    2, 1, 3,},
                                           2, 3);
    swapColumns(&m, 0, 1);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_insertionSortRowsMatrixByRowCriteria() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {3, 3, 3,
                                              1, 1, 1,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {1, 1, 1,
                                                    3, 3, 3,},
                                           2, 3);

    insertionSortRowsMatrixByRowCriteria(&m, getSum);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);

    // исходная матрица (другая матрица на проверку)
    m = createMatrixFromArray((int[]) {3, 3, 3,
                                       1, 1, 1,
                                       1, 1, 1,},
                              3, 3);
    // проверочная матрица
    exp_res = createMatrixFromArray((int[]) {1, 1, 1,
                                             1, 1, 1,
                                             3, 3, 3,},
                                    3, 3);

    insertionSortRowsMatrixByRowCriteria(&m, getSum);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_selectionSortColsMatrixByColCriteria() {
    // исходная матрица
    matrix m = createMatrixFromArray((int[]) {1, 3, 1,
                                              1, 3, 1,},
                                     2, 3);
    // проверочная матрица
    matrix exp_res = createMatrixFromArray((int[]) {1, 1, 3,
                                                    1, 1, 3,},
                                           2, 3);

    selectionSortColsMatrixByColCriteria(&m, getSum);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);

    // исходная матрица (другая матрица на проверку)
    m = createMatrixFromArray((int[]) {2, 1, 1,
                                       2, 1, 1,
                                       2, 1, 1,},
                              3, 3);
    // проверочная матрица
    exp_res = createMatrixFromArray((int[]) {1, 1, 2,
                                             1, 1, 2,
                                             1, 1, 2,},
                                    3, 3);

    selectionSortColsMatrixByColCriteria(&m, getSum);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_isSquareMatrix() {
    // проверка с квадратной матрицей
    matrix m = getMemMatrix(10, 10);
    assert(isSquareMatrix(&m));
    freeMemMatrix(&m);

    // проверка с не квадратной матрицей
    m = getMemMatrix(3, 5);
    assert(!isSquareMatrix(&m));
    freeMemMatrix(&m);
}

void test_areTwoMatricesEqual() {
    matrix m = createMatrixFromArray((int[]) {1, 3, 1,
                                              1, 3, 1,},
                                     2, 3);

    matrix exp_res = createMatrixFromArray((int[]) {1, 3, 1,
                                                    1, 3, 1,},
                                           2, 3);

    // если матрицы равны
    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);

    m = createMatrixFromArray((int[]) {1, 3, 1,
                                       1, 3, 3,},
                              2, 3);

    exp_res = createMatrixFromArray((int[]) {18, 3, 3,
                                             1, 3, 1,},
                                    2, 3);

    // если матрицы не равны
    assert(!areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_isEMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1},
                                     3, 3);
    assert(isEMatrix(&m));

    matrix m1 = createMatrixFromArray((int[]) {
                                              0, 0, 1,
                                              0, 1, 0,
                                              1, 0, 0},
                                      3, 3);
    assert(isEMatrix(&m1) == 0);

    matrix m2 = createMatrixFromArray((int[]) {
                                              0, 0, 1,
                                              0, 1, 0},
                                      2, 3);
    assert(isEMatrix(&m2) == 0);
}

void test_isSymmetricMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 0, 0,
                                             0, 1, 0,
                                             0, 0, 1},
                                     3, 3);
    assert(isSymmetricMatrix(&m));

    matrix m1 = createMatrixFromArray((int[]) {
                                              80, 0, 1,
                                              0, 1, 0,
                                              0, 3, 5},
                                      3, 3);
    assert(isSymmetricMatrix(&m1) == 0);

    matrix m2 = createMatrixFromArray((int[]) {
                                              0, 0, 1,
                                              0, 1, 0},
                                      2, 3);
    assert(isSymmetricMatrix(&m2) == 0);
}

void test_transposeSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 2, 3,
                                             4, 5, 6,
                                             7, 8, 9},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 4, 7,
                                                   2, 5, 8,
                                                   3, 6, 9},
                                           3, 3);

    transposeSquareMatrix(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_transposeMatrix() {
    matrix m = createMatrixFromArray((int[]) {
                                             1, 2, 3,
                                             4, 5, 6,},
                                     2, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
                                                   1, 4,
                                                   2, 5,
                                                   3, 6,},
                                           3, 2);

    transposeMatrix(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_getMinValuePos() {
    //нахождение минимума с 1 значением
    matrix m = createMatrixFromArray((int[]) {1, 1, 1,
                                              1, 3, 0,},
                                     2, 3);
    position p = getMinValuePos(m);

    assert(p.rowIndex == 1 && p.colIndex == 2);
    freeMemMatrix(&m);

    //нахождение минимума с множеством значений
    m = createMatrixFromArray((int[]) {1, 0, 1,
                                       0, 3, 0,},
                              2, 3);
    position p1 = getMinValuePos(m);

    assert(p1.rowIndex == 0 && p1.colIndex == 1);
    freeMemMatrix(&m);
}

void test_getMaxValuePos() {
    //нахождение максимума с 1 значением
    matrix m = createMatrixFromArray((int[]) {1, 0, 1,
                                              1, 3, 9,},
                                     2, 3);
    position p = getMaxValuePos(m);

    assert(p.rowIndex == 1 && p.colIndex == 2);
    freeMemMatrix(&m);

    //нахождение максимума с множеством значений
    m = createMatrixFromArray((int[]) {1, 9, 1,
                                       9, 3, 9,},
                              2, 3);
    position p1 = getMaxValuePos(m);

    assert(p1.rowIndex == 0 && p1.colIndex == 1);
    freeMemMatrix(&m);
}

void test() {
    //тесты взаимодействия с памятью
    test_getMemMatrix();
    test_getMemArrayOfMatrices();
    test_freeMemMatrix();

    //тест перераспределяющих функций
    test_swapRows();
    test_swapColumns();
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();

    //тесты проверочных функций
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();

    //проверка транспонирования
    test_transposeSquareMatrix();
    test_transposeMatrix();

    // тест для нахождения позиции
    test_getMinValuePos();
    test_getMaxValuePos();
}

int main() {

    test();

    return 0;
}
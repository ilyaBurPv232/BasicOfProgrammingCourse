#ifndef UNIKUM_MATRIX_H
#define UNIKUM_MATRIX_H

#include <stdbool.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

// Размещает в динамической памяти матрицу размером nRows на nCols.
// Возвращает матрицу.
matrix getMemMatrix(int nRows, int nCols);

// Размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
// Возвращает указатель на нулевую матрицу.
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

// Освобождает память, выделенную подхранение матрицы m.
// Процесс освобождения изображен на рисунке
void freeMemMatrix(matrix *m);

// освобождает память,
// выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices);

// Ввод матрицы m.
void inputMatrix(matrix *m);

// ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices);

// Вывод матрицы m.
void outputMatrix(matrix m);

// вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices);


// Обмен строк с порядковыминомерами i1 и i2 в матрице m.
void swapRows(matrix *m, int i1, int i2);

// обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix *m, int j1, int j2);

// по идее должна быть в либе array.h, но да ладно
// функция для вычисления суммы для одномерного массива.
int getSum(int *a, int n);

// Считает значение
// функции getSum для каждой строки матрицы. Результаты сохраняются в промежуточный массив.
void insertionSortRowsMatrixByRowCriteria(matrix *m,
                                          int (*criteria)(int *, int));

// Выполняет сортировку выбором столбцов
// матрицы m по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix *m,
                                          int (*criteria)(int *, int));

// возвращает значение ’истина’, если
// матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m);

// проварка на равенство матриц
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

// Проверка на то что является ли матрица единичной
bool isEMatrix(matrix *m);

// проверка матрицы на симметричность
bool isSymmetricMatrix(matrix *m);

// транспонирует квадратную
// матрицу m.
void transposeSquareMatrix(matrix *m);

//транспонирует матрицу m.
void transposeMatrix(matrix *m);

//находит позицию минимума
position getMinValuePos(matrix m);

//находит максимум в матрице
position getMaxValuePos(matrix m);

#endif

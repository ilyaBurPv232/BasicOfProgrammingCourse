#ifndef UNIKUM_MATRIX_H
#define UNIKUM_MATRIX_H


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

//Ввод матрицы m.
void inputMatrix(matrix *m);

//ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices);

//Вывод матрицы m.
void outputMatrix(matrix m);

//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices);


//Обмен строк с порядковыминомерами i1 и i2 в матрице m.
void swapRows(matrix *m, int i1, int i2);

//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix *m, int j1, int j2);

//по идее должна быть в либе array.h, но да ладно
//функция для вычисления суммы для одномерного массива.
int getSum(int *a, int n);

//
void insertionSortRowsMatrixByRowCriteria(matrix *m,
                                          int (*criteria)(int *, int));

//
void selectionSortColsMatrixByColCriteria(matrix *m,
                                          int (*criteria)(int *, int));

#endif

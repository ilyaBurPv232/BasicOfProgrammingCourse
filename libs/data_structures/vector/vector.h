#ifndef UNIKUM_VECTOR_H
#define UNIKUM_VECTOR_H

#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

//возвращает пустой вектор размера capacity
vector createVector(size_t n);

//изменяет текущий объём выделенной памяти
void reserve(vector *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

//освобождает память, выделенную под неиспользуемые элементы.
void shrinkToFit(vector *v);

//освобождает память, выделенную вектору.
void deleteVector(vector *v);

//проверяет пустой ли вектор
bool isEmpty(vector *v);

//проверяет полный ли вектор
bool isFull(vector *v);

//возвращает i элемент вектора v
int getVectorValue(vector *v, size_t i);

//добавляет элемент x в конец вектора
void pushBack(vector *v, int x);

//удаляет последний элемент из вектора
void popBack(vector *v);

//возвращает указатель на index-ый элемент вектора
int* atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора
int* back(vector *v);

//возвращает указатель на нулевой элемент вектора
int* front(vector *v);


#endif

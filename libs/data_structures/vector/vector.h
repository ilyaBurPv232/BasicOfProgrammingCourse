#ifndef UNIKUM_VECTOR_H
#define UNIKUM_VECTOR_H

#include <malloc.h>
#include <stdlib.h>

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

#endif

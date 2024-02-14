#ifndef UNIKUM_VECTORVOID_H
#define UNIKUM_VECTORVOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data;          // указатель на нулевой элемент вектора
    size_t size;         // размер вектора
    size_t capacity;     // вместимость вектора
    size_t baseTypeSize; // размер базового типа:
                         // например, если вектор хранит int -
                         // то поле baseTypeSize = sizeof(int)
                         // если вектор хранит float -
                         // то поле baseTypeSize = sizeof(float)
} vectorVoid;

//создает вектор типа baseTypeSize
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

//изменяет текущий объём выделенной памяти
void reserveV(vectorVoid *v, size_t newCapacity);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid *v);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v);

//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v);

//проверяет пустой ли вектор
bool isEmptyV(vectorVoid *v);

//проверяет полный ли вектор
bool isFullV(vectorVoid *v);

//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

//записывает на index-ый элемент вектора v значение, расположенное по адресу source;
void setVectorValueV(vectorVoid *v, size_t index, void *source);

//удаляет последний элемент
void popBackV(vectorVoid *v);

//добавляет в конец элемент
void pushBackV(vectorVoid *v, void *source);

#endif
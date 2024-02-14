#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "vectorVoid.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    if (n == 0)
        return (vectorVoid) {NULL, 0, n, baseTypeSize};
    vectorVoid v = {malloc(baseTypeSize), 0, n, baseTypeSize};
    if (v.data != NULL)
        return v;
    else {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    //проверка особых случаев
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = newCapacity;
        v->capacity = newCapacity;

    } else if (newCapacity < v->size) {
        v->data = realloc(v->data, v->baseTypeSize * newCapacity);
        v->size = newCapacity;
        v->capacity = newCapacity;

        //если случай обычный
    } else {
        v->data = realloc(v->data, v->baseTypeSize * newCapacity);
        v->capacity = newCapacity;
        if (v->data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }
}

void shrinkToFitV(vectorVoid *v){
    v->data = v->capacity == v->size ?
              v->data :
              realloc(v->data, v->baseTypeSize * (v->capacity = v->size));
}

void clearV(vectorVoid *v){
    v->size = 0;
}

void deleteVectorV(vectorVoid *v){
    free(v->data);
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
}
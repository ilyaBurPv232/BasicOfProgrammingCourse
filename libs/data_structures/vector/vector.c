#include <malloc.h>
#include <stdio.h>
#include "vector.h"


vector createVector(size_t n) {
    if (n == 0)
        return (vector) {NULL, 0, n};

    vector vector1 = {malloc(sizeof(int) * n), 0, n};
    if (vector1.data != NULL)
        return vector1;
    else {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = newCapacity;
        v->capacity = newCapacity;
    } else if (newCapacity < v->size) {
        v->data = realloc(v->data, sizeof(int) * newCapacity);
        v->size = newCapacity;
        v->capacity = newCapacity;
    } else {
        v->data = realloc(v->data, sizeof(int) * newCapacity);
        v->size = newCapacity;
        v->capacity = newCapacity;
        if (v->data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }
}

void clear(vector *v) {
    v->size = 0;
}


void shrinkToFit(vector *v) {
    v->data = v->capacity == v->size ?
              v->data :
              realloc(v->data, sizeof(int) * (v->capacity = v->size));
}

void deleteVector(vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}
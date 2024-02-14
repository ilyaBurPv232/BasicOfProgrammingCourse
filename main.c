#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"

int main() {
    vector v = createVector(6);
    printf("%d %d\n", v.size, v.capacity);
    shrinkToFit(&v);
    printf("%d %d\n", v.size, v.capacity);
    return 0;
}
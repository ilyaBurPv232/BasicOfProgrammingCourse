#include "libs/data_structures/vector/vectorVoid.h"
#include <malloc.h>

int main() {

    vectorVoid v = {malloc(sizeof(float) * 1), 1, 1, sizeof(float)};

    return 0;
}
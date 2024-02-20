#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"

int main() {

    matrix m1 = getMemMatrix(3, 3);
    inputMatrix(&m1);

    if (isSquareMatrix(&m1))
        printf("isGood");

    return 0;
}
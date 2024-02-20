#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"


int main() {

    matrix m1 = getMemMatrix(3, 3);
    inputMatrix(&m1);

    outputMatrix(m1);

    position p = getMaxValuePos(m1);
    printf("%d %d\n",p.rowIndex,p.colIndex);

    return 0;
}
#include "libs/data_structures/matrix/matrix.h"

int main() {

    matrix m = getMemMatrix(3, 3);

    inputMatrix(&m);

    insertionSortRowsMatrixByRowCriteria(&m, getSum);

    outputMatrix(m);

    return 0;
}